// Copyright (c) 2019, University of Washington All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// Redistributions of source code must retain the above copyright notice, this list
// of conditions and the following disclaimer.
//
// Redistributions in binary form must reproduce the above copyright notice, this
// list of conditions and the following disclaimer in the documentation and/or
// other materials provided with the distribution.
//
// Neither the name of the copyright holder nor the names of its contributors may
// be used to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
// ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "raytracer.h"
#include "raytracer_defs.h"

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <limits>
#include <iostream>
#include <typeinfo>
#include <vector>

#pragma pack(push, 1)
struct BMPHeader
{
        uint16_t FileType;
        uint32_t FileSize;
        uint16_t Reserved1;
        uint16_t Reserved2;
        uint32_t BitmapOffset;
        uint32_t Size;
        int32_t Width;
        int32_t Height;
        uint16_t Planes;
        uint16_t BitsPerPixel;
        uint32_t Compression;
        uint32_t SizeOfBitmap;
        int32_t HorzResolution;
        int32_t VertResolution;
        uint32_t ColorsUsed;
        uint32_t ColorsImportant;
};
#pragma pack(pop)

void write_image(uint32_t *img)
{
        uint32_t OutputPixelSize = IMAGE_WIDTH * IMAGE_HEIGHT * sizeof(uint32_t);

        BMPHeader header = {};
        header.FileType = 0x4D42;
        header.FileSize = sizeof(header) + OutputPixelSize;
        header.BitmapOffset = sizeof(header);
        header.Size = sizeof(header) - 14;
        header.Width = IMAGE_WIDTH;
        header.Height = IMAGE_HEIGHT;
        header.Planes = 1;
        header.BitsPerPixel = 32;
        header.Compression = 0;
        header.SizeOfBitmap = OutputPixelSize;
        header.HorzResolution = 0;
        header.VertResolution = 0;
        header.ColorsUsed = 0;
        header.ColorsImportant = 0;
        const char *filename = "Scene.bmp";
        FILE *OutFile = fopen(filename, "wb");
        if(OutFile)
        {
                fwrite(&header, sizeof(header), 1, OutFile);
                fwrite(img, OutputPixelSize, 1, OutFile);
                fclose(OutFile);
                bsg_pr_test_info("Wrote image to output file %s.", filename);
        }
        else
        {
                bsg_pr_test_err("Failed to write to output file!");
        }
}

// Order of args: Stride X, Stride Y, Image allocated on device
int setup_argv(hb_mc_device_t *mc, std::vector<uint32_t> &result)
{
        int rc;

        eva_t image_device;
        if(rc = hb_mc_device_malloc(mc, sizeof(uint32_t) * IMAGE_WIDTH * IMAGE_HEIGHT, &image_device))
        {
                bsg_pr_test_err("Failed to allocate image on the manycore.\n");
                return rc;
        }
        result = { mc->mesh->dim.x, mc->mesh->dim.y, static_cast<uint32_t>(image_device) };
        return HB_MC_SUCCESS;
}

int kernel_raytracer(int argc, char **argv)
{
        int rc;
        char *elf, *test_name;
        struct arguments_path args = {};

        argp_parse(&argp_path, argc, argv, 0, 0, &args);
        elf = args.path;
        test_name = args.name;

        bsg_pr_test_info("Running CUDALite Raytracer\n");

        hb_mc_device_t manycore, *mc = &manycore;
        if(rc = hb_mc_device_init(mc, test_name, 0))
        {
                bsg_pr_test_err("Failed to initialize the manycore.\n");
                return rc;
        }
        
        if(rc = hb_mc_device_program_init(mc, elf, "default_allocator", 0))
        {
                bsg_pr_test_err("Failed to initialize the program at %s.\n", elf);
                return rc;
        }

        std::vector<uint32_t> cuda_argv;
        if(rc = setup_argv(mc, cuda_argv))
        {
                bsg_pr_test_err("Failed to setup argument vector.\n");
                return rc;
        }

        hb_mc_dimension_t tilegroup_dim = { cuda_argv[0], cuda_argv[1] };
        hb_mc_dimension_t grid_dim = { 1, 1 };
        
        if(rc = hb_mc_kernel_enqueue(mc, grid_dim, tilegroup_dim, "kernel_raytracer", cuda_argv.size(), cuda_argv.data()))
        {
                bsg_pr_test_err("Failed to enqueue the raytracer kernel.\n");
                return rc;
        }
        
        if(rc = hb_mc_device_tile_groups_execute(mc))
        {
                bsg_pr_test_err("Failed to execute the tile group.\n");
                return rc;
        }

        eva_t img_device = static_cast<eva_t>(cuda_argv.back());
        uint32_t img[IMAGE_HEIGHT * IMAGE_WIDTH];
        if(rc = hb_mc_device_memcpy(mc,
                                    reinterpret_cast<void *>(img),
                                    reinterpret_cast<void *>(static_cast<intptr_t>(img_device)),
                                    sizeof(img),
                                    HB_MC_MEMCPY_TO_HOST))
        {
                bsg_pr_test_err("Failed to copy image back to device.\n");
                return rc;
        }
        
        write_image(img);
        
        if(rc = hb_mc_device_finish(mc))
        {
                bsg_pr_test_err("Failed to deinitialize the manycore.\n");
                return rc;
        }
        return HB_MC_SUCCESS;
}

#ifdef COSIM
void cosim_main(uint32_t *exit_code, char * args)
{
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
        int rc = kernel_raytracer(argc, argv);
        *exit_code = rc;
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return;
}
#else
int main(int argc, char **argv)
{
        int rc = kernel_raytracer(argc, argv);
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return rc;
}
#endif


