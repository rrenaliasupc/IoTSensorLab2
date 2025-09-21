#pragma once

#include "_project_config.h"
#ifdef __has_attribute
#define HAVE_ATTRIBUTE(x) __has_attribute(x)
#else
#define HAVE_ATTRIBUTE(x) 0
#endif
#if HAVE_ATTRIBUTE(aligned) || (defined(__GNUC__) && !defined(__clang__))
#define DATA_ALIGN_ATTRIBUTE __attribute__((aligned(4)))
#else
#define DATA_ALIGN_ATTRIBUTE
#endif

// automatically configure network
#define TF_NUM_OPS 2
#define TF_NUM_INPUTS 300
#define TF_NUM_OUTPUTS 2
#define TF_OP_FULLYCONNECTED
#define TF_OP_SOFTMAX

/** model size = 5048 bytes **/
extern const unsigned char __model_model_tflite[] DATA_ALIGN_ATTRIBUTE;
