/*
 * This kernel performs a multiplication between a sparse matrix and a 
 * dense vector. Dense vector is represented by two vectors, a list of 
 * non-zero indices, and a list of non-zero values cooresponding to 
 * those indicis. Result is a sparse vector.
 */

// BSG_TILE_GROUP_X_DIM and BSG_TILE_GROUP_Y_DIM must be defined
// before bsg_manycore.h and bsg_tile_group_barrier.h are
// included. bsg_tiles_X and bsg_tiles_Y must also be defined for
// legacy reasons, but they are deprecated.
#define BSG_TILE_GROUP_X_DIM 4
#define BSG_TILE_GROUP_Y_DIM 4
#define bsg_tiles_X BSG_TILE_GROUP_X_DIM
#define bsg_tiles_Y BSG_TILE_GROUP_Y_DIM
#include <bsg_manycore.h>
#include <bsg_tile_group_barrier.h>
#include <cstdint>

#include <spmv.hpp>

INIT_TILE_GROUP_BARRIER(r_barrier, c_barrier,
                        0, BSG_TILE_GROUP_X_DIM-1,
                        0, BSG_TILE_GROUP_Y_DIM-1);


/* 
 * Version 0 
 *  Matrix is divided by it's Y dimensions among tile groups and 
 *  tiles in the tile group, and each tile group performs block_size number of 
 *  row column multiplications and stores block_size results into the sparse result
 *  vector.
 */
template <typename TM, typename TV, typename TR>
int  __attribute__ ((noinline)) spmv (TM* sparse_matrix, 
                                      uint32_t MATRIX_HEIGHT,
                                      uint32_t MATRIX_WIDTH,
                                      int* dense_vector_index,
                                      TV* dense_vector_data,
                                      uint32_t VECTOR_LENGTH,
                                      TR* sparse_vector_result,
                                      uint32_t block_size) {


        const int start = (__bsg_tile_group_id_y * __bsg_grid_dim_x + __bsg_tile_group_id_x) * block_size;
        const int end = MIN (start + block_size, MATRIX_HEIGHT);
        const int num_tiles = bsg_tiles_X * bsg_tiles_Y;

        for (int y = start + __bsg_id; y < end; y += num_tiles) {
                TR sum = 0;
                for (int v = 0; v < VECTOR_LENGTH; v ++) {
                        int x = dense_vector_index[v];
                        sum += sparse_matrix[y * MATRIX_HEIGHT + x] * dense_vector_data[v];
                }
                sparse_vector_result[y] = sum;
        }

        return 0;
}



extern "C" {
        int  __attribute__ ((noinline)) kernel_spmv (int* sparse_matrix, 
                                                     uint32_t MATRIX_HEIGHT,
                                                     uint32_t MATRIX_WIDTH,
                                                     int* dense_vector_index,
                                                     int* dense_vector_data,
                                                     uint32_t VECTOR_LENGTH,
                                                     int* sparse_vector_result,
                                                     uint32_t block_size) {

                int rc;
                bsg_cuda_print_stat_kernel_start();
                bsg_cuda_print_stat_start(0);

                rc = spmv (sparse_matrix,
                           MATRIX_HEIGHT,
                           MATRIX_WIDTH,
                           dense_vector_index,
                           dense_vector_data,
                           VECTOR_LENGTH,
                           sparse_vector_result,
                           block_size);

                bsg_cuda_print_stat_end(0);

                bsg_tile_group_barrier(&r_barrier, &c_barrier);

                bsg_cuda_print_stat_kernel_end();
                return rc;
        }
}
