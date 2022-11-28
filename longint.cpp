#include "longint.h"
#include "algorithms/multiplication.h"

#include <algorithm>

using dt = longint::dt;


void longint::copy_init(const vector<dt>& copy_buff, bool copy_negative)
{
	buffer = vector<dt>(copy_buff);
	negative = copy_negative;
	normalize();
}

void longint::move_init(vector<dt>&& move_buff, bool move_negative)
{
	buffer = move(move_buff);
	negative = move_negative;
	normalize();
}


longint::longint(long n): buffer(0), negative(false)
{
	if(n < 0)
	{
		negative = true;
		n = -n;
	}

	do
	{
		buffer.push_back(n % base);
		n /= base;
	} while (n);
}

longint::longint(const vector<dt>& copy_buffer, bool copy_negative = false)
{ copy_init(copy_buffer, copy_negative); }
longint::longint(vector<dt>&& move_buffer, bool move_negative = false)
{ move_init(move(move_buffer), move_negative); }
longint::longint(const longint& to_copy)
{ copy_init(to_copy.buffer, to_copy.negative); }
longint::longint(longint&& to_move)
{ move_init(move(to_move.buffer), to_move.negative); }
longint& longint::operator=(const longint& to_copy)
{
	copy_init(to_copy.buffer, to_copy.negative);
	return *this;
}
longint& longint::operator=(longint&& to_move)
{
	move_init(move(to_move.buffer), to_move.negative);
	return *this;
}

string longint::to_string() const
{
	stringstream s;
	if (negative) s << '-';
	for (size_t i = buffer.size(); i > 0; i--)
		s << (dt) (buffer[i - 1] + '0');
	return s.str();
}

dt& longint::operator[](size_t i)
{ return buffer[i]; }
const dt& longint::operator[](size_t i) const
{ return buffer[i]; }

longint& longint::operator<<=(const size_t i)
{
	if (buffer.size() == 1 && buffer[0] == 0)
		return *this;

	buffer.insert(buffer.begin(), i, 0);
	return *this;
}
longint& longint::operator>>=(const size_t i)
{
	if (i == 0 || (buffer.size() == 1 && buffer[0] == 0))
		return *this;

	const size_t l = buffer.size();
	for(size_t j = i; j < l; j++)
		buffer[j - i] = buffer[j];
	buffer.resize(l - i);
	return *this;
}

longint operator<<(const longint& a, size_t i)
{
	longint ret(a);
	ret <<= i;
	return ret;
}

longint operator>>(const longint& a, size_t i)
{
	longint ret(a);
	ret >>= i;
	return ret;
}

void longint::normalize()
{
	size_t l = buffer.size();
	while (l > 1 && buffer[l - 1] == 0) l--;
	buffer.resize(l);
	if (l == 1 && buffer[0] == 0)
		negative = false;
}

void longint::denormalize(size_t to_size)
{ buffer.insert(buffer.end(), to_size - buffer.size(), 0); }

ostream& operator<<(ostream& out, const longint& n)
{
	out << n.to_string();
	return out;
}

istream& operator>>(istream& in, longint& n)
{
	string buff;
	in >> buff;

	const bool negative = buff[0] == '-';
	vector<dt> buffer(buff.size() - negative);
	for (size_t i = 0; i < buff.size() - negative; i++)
		buffer[i] = buff[buff.size() - i - 1] - '0';

	n.move_init(move(buffer), negative);
	return in;
}

dt cmp(const longint& a, const longint& b)
{
	if (a.buffer.size() != b.buffer.size())
		return a.buffer.size() > b.buffer.size() ? 1 : -1;

	for (size_t i = a.buffer.size(); i > 0; i--)
		if (a.buffer[i - 1] != b.buffer[i - 1])
			return a.buffer[i - 1] > b.buffer[i - 1] ? 1 : -1;

	return 0;
}

void sum(longint& a, const longint& b)
{
	const size_t m = b.buffer.size();
	if(a.buffer.size() < m)
		a.buffer.resize(b.buffer.size());

	dt buff = 0;
	for(size_t i = 0; i < m; i++)
	{
		buff += a[i] + b[i];
		a[i] = buff % longint::base;
		buff /= longint::base;
	}
	if (buff == 0) return;

	for(size_t i = m; buff > 0 && i < a.buffer.size(); i++)
	{
		buff += a[i];
		a[i] = buff % longint::base;
		buff /= longint::base;
	}
	if (buff != 0) a.buffer.push_back(buff);
}
void subtract(const longint& fr, const longint& wh, longint& res)
{
	dt buff = 0;
	for (size_t i = 0; i < wh.buffer.size(); i++)
	{
		if (fr[i] >= wh[i] + buff)
		{
			res[i] = fr[i] - wh[i] - buff;
			buff = 0;
			continue;
		}

		// BASE_DEPENDENT
		res[i] = longint::base + fr[i] - wh[i] - buff;
		buff = 1;
	}
	for (size_t i = wh.buffer.size(); buff > 0; i++)
	{
		if (fr[i] >= buff)
		{
			res[i] = fr[i] - buff;
			break;
		}

		// BASE_DEPENDENT
		res[i] = longint::base + fr[i] - buff;
		buff = 1;
	}

	res.normalize();
}

void linear(longint& a, const longint& b, bool sign)
{
	sign ^= b.negative;
	if (a.negative == sign)
	{
		sum(a, b);
		return;
	}

	// In this case doing subtraction
	if (cmp(a, b) >= 0)
		subtract(a, b, a);
	else
	{
		longint buff(b.buffer, !a.negative);
		subtract(b, a, buff);
		a = move(buff);
	}
}

longint operator+(const longint& a, const longint& b)
{
	longint buff = a;
	linear(buff, b, false);
	return move(buff);
}

longint& operator+=(longint& a, const longint& b)
{
	linear(a, b, false);
	return a;
}

longint operator-(const longint& a, const longint& b)
{
	longint buff = a;
	linear(buff, b, true);
	return move(buff);
}

longint& operator-=(longint& a, const longint& b)
{
	linear(a, b, true);
	return a;
}

void dmul(longint &a, const dt b)
{
	dt buff = 0;
	for (size_t i = 0; i < a.buffer.size(); i++)
	{
		buff += a[i] * b;
		a[i] = buff % longint::base;
		buff /= longint::base;
	}
	if (buff != 0) a.buffer.push_back(buff);
}

longint trivial_mul(const longint& a, const longint& b)
{
	longint ret = 0;
	longint buff;
	for(size_t i = 0; i < b.buffer.size(); i++)
	{
		buff = a;
		dmul(buff, b[i]);
		buff <<= i;
		sum(ret, buff);
	}
	ret.negative = a.negative ^ b.negative;
	return ret;
}

longint operator*(const longint& a, const longint& b)
{ return multiplication::karatsuba(a, b); }

longint operator/(const longint& a, const longint& b)
{
	switch (cmp(a, b))
	{
	case -1:
		return 0;
	case 0:
		return a.negative ^ b.negative ? -1 : 1;
	}

	vector<dt> ret(0);
	const size_t l = a.buffer.size();
	ret.reserve(l);
	longint buff(0);
	dt d;
	for(size_t i = 0; i < l; i++)
	{
		buff <<= 1;
		buff += a[l - i - 1];
		if (cmp(buff, b) >= 0)
		{
			d = 0;
			while (cmp(buff, b) >= 0)
			{
				subtract(buff, b, buff);
				d++;
			}
			ret.push_back(d);
		}
		else ret.push_back(0);
	}

	reverse(ret.begin(), ret.end());
	return move(longint(move(ret), a.negative ^ b.negative));
}
