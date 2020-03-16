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
#include <bsg_tile_group_barrier_template.hpp>
#include <bsg_striped_array.hpp>
#include <cstdint>

#include <spmv.hpp>

using namespace bsg_manycore;

/* 
 * Version 2 
 * This version loads the dense vector into tile group shared memory,
 * to reduce the redundant access latency to the dense vector.
 * This version also uses the new template barrier library.
 */
template <int MATRIX_HEIGHT, int MATRIX_WIDTH, int VECTOR_LENGTH, typename TM, typename TV, typename TR>
int  __attribute__ ((noinline)) spmv_vector_sh_mem (TM* sparse_matrix, 
                                                    int* dense_vector_index,
                                                    TV* dense_vector_data,
                                                    TR* sparse_vector_result,
                                                    uint32_t block_size) {

        bsg_barrier <bsg_tiles_Y, bsg_tiles_X> barrier;

        TileGroupStripedArray <int, VECTOR_LENGTH, bsg_tiles_X, bsg_tiles_Y, 1> sh_vector_index;
        TileGroupStripedArray <TV, VECTOR_LENGTH, bsg_tiles_X, bsg_tiles_Y, 1> sh_vector_data;

        const int start = (__bsg_tile_group_id_y * __bsg_grid_dim_x + __bsg_tile_group_id_x) * block_size;
        const int end = MIN (start + block_size, MATRIX_HEIGHT);
        const int num_tiles = bsg_tiles_X * bsg_tiles_Y;


        // Load vector index and data into shared memory
        for (int iter_x = __bsg_id; iter_x < VECTOR_LENGTH; iter_x += num_tiles) {
                sh_vector_index[iter_x] = dense_vector_index[iter_x];
                sh_vector_data[iter_x] = dense_vector_data[iter_x];
        }

        barrier.sync();


        for (int y = start + __bsg_id; y < end; y += num_tiles) {
                TR sum = 0;
                for (int v = 0; v < VECTOR_LENGTH; v ++) {
                        int x = sh_vector_index[v];
                        sum += sparse_matrix[y * MATRIX_HEIGHT + x] * sh_vector_data[v];
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

                bsg_barrier<bsg_tiles_Y, bsg_tiles_X>  barrier;

                int rc;
                bsg_cuda_print_stat_kernel_start();
                bsg_cuda_print_stat_start(0);

                rc = spmv_vector_sh_mem<64,64,32> (sparse_matrix,
                                                   dense_vector_index,
                                                   dense_vector_data,
                                                   sparse_vector_result,
                                                   block_size);

                bsg_cuda_print_stat_end(0);

                barrier.sync();

                bsg_cuda_print_stat_kernel_end();
                return rc;
        }
}
