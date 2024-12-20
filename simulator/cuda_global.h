#ifndef CUDA_H
#define CUDA_H

#define DEFAULT_THREAD_COUNT_PER_BLOCK 256
#define DTCPB DEFAULT_THREAD_COUNT_PER_BLOCK
#define DEFAULT_THREAD_COUNT_PER_BLOCK_2D 16
#define DTCPB2D DEFAULT_THREAD_COUNT_PER_BLOCK_2D

#define CUDA_CHECK(call) \
    { \
        cudaError_t err = call; \
        if (err != cudaSuccess) { \
            fprintf(stderr, "CUDA error in %s at line %d: %s\n", \
                                __FILE__, __LINE__, cudaGetErrorString(err)); \
            exit(err); \
        } \
    }

#endif