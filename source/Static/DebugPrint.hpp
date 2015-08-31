#pragma once

#ifndef printd
	#ifdef _DEBUG
		#include <stdio.h>
		#define printd(string, ...) printf(string, __VA_ARGS__)
	#else
		#define printd(string, ...) (0)
	#endif
#endif