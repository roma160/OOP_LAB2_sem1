#include "division.h"

tuple<longint, longint> division::toom(const longint& a, const longint& b)
{
    longint exponent{ 10 }, mantissa{ 1 };

    for (int i = 0; i < 6; ++i) {
        mantissa = longint(2) * exponent * mantissa - b * mantissa * mantissa;
        exponent = exponent * exponent;
    }

    size_t log = exponent.buffer.size() - 1;
    mantissa = mantissa * a;
    mantissa.denormalize(log + 1);
    longint int_part(vector<longint::dt>(mantissa.buffer.begin() + log, mantissa.buffer.end()), false),
			float_part(vector<longint::dt>(mantissa.buffer.begin(), mantissa.buffer.begin() + log), false);
    return { int_part, float_part };
}
