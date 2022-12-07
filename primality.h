#pragma once
#include "longint.h"

class primality
{
public:

	static bool lehmer(const longint& n);
	static bool miller(const longint& n, size_t num);
	static bool strassen(const longint& n, size_t num);
};

