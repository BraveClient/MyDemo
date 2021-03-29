/**
 * @file defines.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once


#define SUCCESS (0)
#define FAILURE (-1)

#include <string>
#include "common.h"


typedef struct
{
	std::string srcIP;
	uint16_t srcPort;
	std::string desIP;
	uint16_t desPort;
	std::string data;
} ST_UDP_DATA;