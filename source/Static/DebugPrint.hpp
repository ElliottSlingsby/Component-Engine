#ifndef print

// Nulls all print statements on release compile

#pragma once
#include <stdio.h>

#ifdef _DEBUG
#define print(string, ...) printf (string, __VA_ARGS__)
#else
#define print(string, ...) (0)
#endif

#endif