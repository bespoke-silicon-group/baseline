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

#ifndef _CL_MANYCORE_REGRESSION_H
#define _CL_MANYCORE_REGRESSION_H

#ifdef __cplusplus

#include <cstdlib>
#include <cstdio>
#include <cstdbool>
#include <cfloat>

#else

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <float.h>

#endif

#include <bsg_manycore_errno.h>
#include <unistd.h>
#include <argp.h>

#ifdef VCS
#include "svdpi.h"
#endif
#define BSG_RED(x) "\033[31m" x "\033[0m"
#define BSG_GREEN(x) "\033[32m" x "\033[0m"
#define BSG_YELLOW(x) "\033[33m" x "\033[0m"

/**
 * bsg_pr_test_info() a version of printf. All regression tests should prefer this function over direct stdio calls.
 */
#define bsg_pr_test_info(fmt, ...)                                      \
        do { printf("BSG INFO: " fmt, ##__VA_ARGS__); fflush(NULL); } while (0)

/**
 * bsg_pr_test_info() a version of printf(stderr,...). All regression tests should prefer this function over direct stdio calls.
 */
#define bsg_pr_test_err(fmt, ...)                                       \
        fprintf(stderr, BSG_RED("BSG ERR: " fmt), ##__VA_ARGS__)

/**
 * bsg_pr_test_pass_fail() prints a success/fail message depending on a test condition
 * @param[in] success_condition a condition which, if true, indicates that the test has passed
 */
#define bsg_pr_test_pass_fail(success_condition)                        \
        printf("BSG REGRESSION TEST %s\n", ((success_condition) ? BSG_GREEN("PASSED") : BSG_RED("FAILED")))

#ifdef __cplusplus
extern "C" {
void cosim_main(uint32_t *exit_code, char * args);
}
#endif

#ifdef COSIM
// Given a string, determine the number of space-separated arguments
static
int get_argc(char * args){
        char *cur = args, prev=' ';
        int count = 1;
        while(*cur != '\0'){
                if((prev == ' ') && (prev != *cur)){
                        count ++;
                }
                prev = *cur;
                ++cur;
        }
        return count;
}

static
void get_argv(char * args, int argc, char **argv){
        int count = 0;
        char *cur = args, prev=' ';

        // First parse the path name. This is not in the argument string because
        // VCS doesn't provide it to us. Instead, we "hack" around it by reading
        // the path from 'proc/self/exe'. The maximum path-name length is 1024,
        // with an extra null character for safety
        static char path[1025] = {'\0'};

        readlink("/proc/self/exe", path, sizeof(path) - 1);
        argv[0] = path;
        count ++;

        // Then we parse the remaining arguments. Arguments are separated by N
        // >= 1 spaces. We only register an argument when the previous character
        // was a space, and the current character is not (so that multiple
        // spaces don't count as multiple arguments). We replace spaces with
        // null characters (\0) so that each argument appears to be an
        // individual string and can be used later, by argparse (and other
        // libraries)
        while(*cur != '\0'){
                if((prev == ' ') && (prev != *cur)){
                        argv[count] = cur;
                        count++;
                }
                prev = *cur;
                if(*cur == ' ')
                        *cur = '\0';
                cur++;
        }
}
#endif // COSIM
static char doc[] = "A regression test for BSG Manycore on F1";

struct arguments_none{
};

struct arguments_name{
        char *testname; // Name of RISC-V Manycore Binary to run
};

struct arguments_path{
        char *path; // Path to RISC-V Manycore Binary to run
        char *name; // Name of Test to Run
};

/*
  args_doc: A description of the non-option command-line arguments that we
  accept.
*/
static char desc_name[] = "<Test Name>";
static char desc_path[] = "<Path to Manycore Binary> <Name of Test>";
static char desc_path_py[] = "<Path to Python Tests Directory> <Name of Test>";
static char desc_none[] = "";
static struct argp_option opts_name[] = {
        {0, 'b', "TEST", 0, "Name of Manycore Test to Run"},
        {0}};
static struct argp_option opts_path[] = {
        {0, 'n', "NAME", 0, "Name of Manycore Test to Run"},
        {0, 'p', "PATH", 0, "Path to RISC-V Manycore Binary"},
        {0}};
static struct argp_option opts_path_py[] = {
        {0, 'n', "NAME", 0, "Name of Manycore Test to Run"},
        {0, 'p', "PATH", 0, "Path to Python Folder"},
        {0}};
static struct argp_option opts_none[] = {{0}};

static error_t parse_name (int key, char *arg, struct argp_state *state){
        struct arguments_name *args = (struct arguments_name *)state->input;
 
        switch (key) 
                {
                case 'b':
                        args->testname = arg;
                        break;
                case ARGP_KEY_ARG:
                        if (state->arg_num == 0){
                                args->testname = arg;
                        }
                        if (state->arg_num > 1){
                                bsg_pr_test_err("Too Many Arguments provided!\n");
                                argp_usage(state);
                        }
                        break;
                case ARGP_KEY_END:
                        if (!args->testname){
                                bsg_pr_test_err("Test Name not provided!\n");
                                argp_usage(state);
                        }
                        break;
                default:
                        return ARGP_ERR_UNKNOWN;
                }
        return 0;
}

static error_t parse_path (int key, char *arg, struct argp_state *state){
        struct arguments_path *args = (struct arguments_path *)state->input;
 
        switch (key) 
                {
                case 'p':
                        args->path = arg;
                        break;
                case 'n':
                        args->name = arg;
                        break;
                case ARGP_KEY_ARG:
                        if (state->arg_num == 0){
                                args->path = arg;
                        }
                        if (state->arg_num == 1){
                                args->name = arg;
                        }
                        if (state->arg_num > 2){
                                bsg_pr_test_err("Too Many Arguments provided!\n");
                                argp_usage(state);
                        }
                        break;
                case ARGP_KEY_END:
                        if (!args->path){
                                bsg_pr_test_err("Executable path not provided!\n");
                                argp_usage(state);
                        }
                        if (!args->name){
                                bsg_pr_test_err("Test Name not provided!\n");
                                argp_usage(state);
                        }
                        break;
                default:
                        return ARGP_ERR_UNKNOWN;
                }
        return 0;
}

static error_t parse_path_py (int key, char *arg, struct argp_state *state){
        return parse_path(key, arg, state);
}

static error_t parse_none (int key, char *arg, struct argp_state *state){
 
        switch (key) 
                {
                case ARGP_KEY_ARG:
                        bsg_pr_test_err("Too Many Arguments provided!\n");
                        argp_usage(state);
                        break;
                default:
                        return ARGP_ERR_UNKNOWN;
                }
        return 0;
}

static struct argp argp_name = {opts_name, parse_name, desc_name, doc};
static struct argp argp_path = {opts_path, parse_path, desc_path, doc};
static struct argp argp_path_py = {opts_path_py, parse_path_py, desc_path_py, doc};
static struct argp argp_none = {opts_none, parse_none, desc_none, doc};

#ifdef VCS
int vcs_main(int argc, char **argv);
void cosim_main(uint32_t *exit_code, char * args) {
        // We aren't passed command line arguments directly so we parse them
        // from *args. args is a string from VCS - to pass a string of arguments
        // to args, pass c_args to VCS as follows: +c_args="<space separated
        // list of args>"
        int argc = get_argc(args);
        char *argv[argc];
        get_argv(args, argc, argv);

        int rc = vcs_main(argc, argv);
        *exit_code = rc;
        bsg_pr_test_pass_fail(rc == HB_MC_SUCCESS);
        return;
}
#endif

#endif
