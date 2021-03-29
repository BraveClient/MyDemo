/**
 * @file common.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-31
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "defines.h"

// used to pack structures
#define PACKED __attribute__((__packed__))

// used to weaken symbols
#define WEAK __attribute__((__weak__))

// used to mark a function that may be unused in some builds
#define UNUSED_FUNCTION __attribute__((unused))

#ifdef __GNUC__
 #define WARN_IF_UNUSED __attribute__ ((warn_unused_result))
#else
 #define WARN_IF_UNUSED
#endif