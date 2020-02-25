#include <cstring>
#include <cstdlib>
#include <random>
#include <limits>
#include <iostream>
#include <typeinfo>
#include <bsg_manycore_errno.h>
#include <bsg_manycore_cuda.h>
#include <bsg_manycore_printing.h>
#include "../../common.h"
#include <graph_generation/graph.hpp>
#include <graph_generation/csr_blob.hpp>
#include <graph_algorithm/BFS.hpp>
#include <graph_formats/graph.hpp>
#include <graph_formats/vertexset.hpp>
#include <cuda_lite_applications/breadth_first_search.hpp>
#include <cuda_lite_extensions/cuda_call.hpp>

static int cuda_memcpy_to_device
(hb_mc_device_t *device, hb_mc_dma_htod_t *jobs, int count)
{
    for (int i = 0; i < count; i++) {
	hb_mc_dma_htod_t *job = &jobs[i];
	printf("%s: Copying job %d\n", __func__, i);
	CUDA_CALL(hb_mc_device_memcpy(device,
				      (void*)job->d_addr,
				      job->h_addr,
				      job->size,
				      HB_MC_MEMCPY_TO_DEVICE));
    }
    return HB_MC_SUCCESS;
}

static int cuda_memcpy_to_host
(hb_mc_device_t *device, hb_mc_dma_dtoh_t *jobs, int count)
{
    for (int i = 0; i < count; i++) {
	hb_mc_dma_dtoh_t *job = &jobs[i];
	printf("%s: Copying job %d\n", __func__, i);
	CUDA_CALL(hb_mc_device_memcpy(device,
				      job->h_addr,
				      (const void*)job->d_addr,
				      job->size,
				      HB_MC_MEMCPY_TO_HOST));
    }
    return HB_MC_SUCCESS;
}

#include <cuda_lite_extensions/cuda_call.hpp>
#include <misc/array_size.h>

using namespace formats;
using namespace graph_generation;
using namespace graph_algorithm;

static constexpr char KERNEL [] 	= "kernel";
static constexpr hb_mc_dimension_t GRID = {2,2};
static constexpr hb_mc_dimension_t TG	= {2,2};

static constexpr std::size_t DMA_SIZE_THRESHOLD = 4 * 1024;


int kernel_bfs(int argc, char *argv[])
{
    // generate graph and input frontier
    CSRGraph graph_h(20, 4);
    CSRGraph graph_b = graph_h;
    
    printf("Generated a graph %zu byte  graph with %d nodes %d edges\n",
	   graph_h.size_in_bytes(), graph_h.n_nodes(), graph_h.n_edges());

    DenseVertexSet  frontier_out_h(graph_h.n_nodes());
    auto frontier_in_h = SparseVertexSet::RandomFromGraph(graph_h, graph_h.n_nodes()/20);
    auto visited_h = DenseVertexSet::FromSparse(frontier_in_h);

    // cuda init
    hb_mc_device_t CUDA;
    CUDA_CALL(hb_mc_device_init_custom_dimensions(&CUDA, "bfs", 0, hb_mc_dimension(2,2)));

    printf("Loading '%s' on device\n", argv[1]);
    CUDA_CALL(hb_mc_device_program_init(&CUDA, argv[1], "bfs", 0));

    // allocate graph data
    hb_mc_eva_t graph_d, frontier_in_d, frontier_out_d, visited_d;
    CUDA_CALL(hb_mc_device_malloc(&CUDA, graph_h.size_in_bytes(), &graph_d));
    CUDA_CALL(hb_mc_device_malloc(&CUDA, frontier_in_h.size_in_bytes(), &frontier_in_d));
    CUDA_CALL(hb_mc_device_malloc(&CUDA, frontier_out_h.size_in_bytes(), &frontier_out_d));
    CUDA_CALL(hb_mc_device_malloc(&CUDA, visited_h.size_in_bytes(), &visited_d));


    // copy graph to device
    hb_mc_dma_htod_t to_device [] = {
	{
	    .d_addr = graph_d,
	    .h_addr = graph_h.data(),
	    .size   = graph_h.size_in_bytes()
	},
	{
	    .d_addr = frontier_in_d,
	    .h_addr = frontier_in_h.data(),
	    .size   = frontier_in_h.size_in_bytes()
	},
	{
	    .d_addr = visited_d,
	    .h_addr = visited_h.data(),
	    .size   = visited_h.size_in_bytes()
	}
    };

    printf("Copying graph data, input set, and visited array to device\n");

    std::size_t xfer_size_to_device
	= graph_h.size_in_bytes()
	+ visited_h.size_in_bytes()
	+ frontier_in_h.size_in_bytes();

    if (xfer_size_to_device > DMA_SIZE_THRESHOLD)
	CUDA_CALL(hb_mc_device_dma_to_device(&CUDA, to_device, ARRAY_SIZE(to_device)));
    else
	CUDA_CALL(cuda_memcpy_to_device(&CUDA, to_device, ARRAY_SIZE(to_device)));
    
    printf("Done!\n");

    printf("Calling %s\n", KERNEL);

    uint32_t kernel_args [] = {
	graph_d,
	visited_d,	
	frontier_in_d,
	frontier_out_d
    };
    CUDA_CALL(hb_mc_kernel_enqueue(&CUDA, GRID, TG,
				   KERNEL, ARRAY_SIZE(kernel_args), kernel_args));
    CUDA_CALL(hb_mc_device_tile_groups_execute(&CUDA));
    printf("Done!\n");

    auto frontier_out_b = frontier_out_h;
    auto visited_b = visited_h;

    int edges_traversed =
	bfs_sparse_push(graph_b.data(),
			visited_b.data(),
			frontier_in_h.data(),
			frontier_out_b.data());

    printf("%d traversed edges\n", edges_traversed);

    std::size_t xfer_size_to_host
	= visited_h.size_in_bytes()
	+ frontier_out_h.size_in_bytes();
    
    // retrieve the output data from the kernel
    hb_mc_dma_dtoh_t to_host [] = {
	{
	    .d_addr = visited_d,
	    .h_addr = visited_h.data(),
	    .size   = visited_h.size_in_bytes()
	},
	{
	    .d_addr = frontier_out_d,
	    .h_addr = frontier_out_h.data(),
	    .size   = frontier_out_h.size_in_bytes()
	}
    };

    printf("Copying output data to host\n");
    if (xfer_size_to_host > DMA_SIZE_THRESHOLD)
	CUDA_CALL(hb_mc_device_dma_to_host(&CUDA, to_host, ARRAY_SIZE(to_host)));
    else
	CUDA_CALL(cuda_memcpy_to_host(&CUDA, to_host, ARRAY_SIZE(to_device)));
    
    // cuda exit
    CUDA_CALL(hb_mc_device_finish(&CUDA));

    // compare the output
    for (int v = 0; v < graph_h.n_nodes(); v++) {
	if (visited_h[v] != visited_b[v]) {
	    bsg_pr_err("vertex %d: %s visited_h - %s visited_b", v,
		       visited_h[v] == 1 ? "in" : "not in",
		       visited_b[v] == 1 ? "in" : "not in");
	    
	}
    }

    return HB_MC_SUCCESS;
}
					

#ifdef COSIM
void cosim_main(uint32_t *exit_code, char * args) {
    // We aren't passed command line arguments directly so we parse them
    // from *args. args is a string from VCS - to pass a string of arguments
    // to args, pass c_args to VCS as follows: +c_args="<space separated
    // list of args>"
    int argc = get_argc(args);
    char *argv[argc];
    get_argv(args, argc, argv);

#ifdef VCS
    svScope scope;
    scope = svGetScopeFromName("tb");
    svSetScope(scope);
#endif
    int rc = kernel_bfs(argc, argv);
    *exit_code = rc;
    bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
    return;
}
#else
int main(int argc, char ** argv) {
    int rc = kernel_hello_world(argc, argv);
    bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
    return rc;
}
#endif
