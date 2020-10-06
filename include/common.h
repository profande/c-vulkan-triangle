#pragma once

#include <stdint.h>

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8  bool8;  
typedef uint32 bool32;

#define true  (bool8)1
#define false (bool8)0

typedef float  float32;
typedef double float64;

#define internal static
#define persist static

#ifdef _WIN32
    #define inline __forceinline
#elif
    #define inline __attribute__((always_inline))
#endif

#define array_length(arr) sizeof(arr) / sizeof(arr[0])