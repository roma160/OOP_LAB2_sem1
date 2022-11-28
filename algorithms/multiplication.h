#pragma once

#include "longint.h"

class multiplication
{
public:
	static longint karatsuba(const longint& a, const longint& b);
	static longint toomcook(const longint& a, const longint& b);
};

