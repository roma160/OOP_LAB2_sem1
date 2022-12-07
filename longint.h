#pragma once
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <tuple>

using namespace std;

class longint
{
public:
	typedef char dt;
	const static dt base = 10;

private:
	vector<dt> buffer;
	bool negative;

	void copy_init(const vector<dt>& copy_buff, bool copy_negative);
	void move_init(vector<dt>&& move_buff, bool move_negative);

	friend void linear(longint& a, const longint& b, bool negation);
	friend void sum(longint& a, const longint& b);
	friend void subtract(const longint& fr, const longint& wh, longint& res);

	friend void dmul(longint& a, dt b);
	friend longint trivial_mul(const longint& a, const longint& b);
	friend class multiplication;
	friend longint r_karatsuba(const longint& a, const longint& b);
	friend longint r_toomcook(const longint& a, const longint& b);
	friend longint r_shengage(const longint& a, const longint& b);

	friend class division;
	friend tuple<longint, longint> toom(const longint& a, const longint& b);

	friend class primality;
	friend bool lehmer(const longint& n);
	friend bool miller(const longint& n, size_t num);
	friend bool strassen(const longint& n, size_t num);

public:
	longint(long n = 0);

	longint(const vector<dt>& copy_buffer, bool copy_negative);
	longint(vector<dt>&& move_buffer, bool move_negative);
	longint(const longint& to_copy);
	longint(longint&& to_move);

	longint& operator=(const longint& to_copy);
	longint& operator=(longint&& to_move);

	friend ostream& operator<<(ostream& out, const longint& n);
	friend istream& operator>>(istream& in, longint& n);

	string to_string() const;

	inline dt& operator[](size_t i);
	inline const dt& operator[](size_t i) const;

	inline longint& operator<<=(size_t i);
	inline longint& operator>>=(size_t i);
	friend longint operator<<(const longint& a, size_t i);
	friend longint operator>>(const longint& a, size_t i);

	void normalize();
	void denormalize(size_t to_size);

	friend dt cmp(const longint& a, const longint& b);

	friend longint operator+(const longint& a, const longint& b);
	friend longint& operator+=(longint& a, const longint& b);
	friend longint operator-(const longint& a, const longint& b);
	friend longint& operator-=(longint& a, const longint& b);
	friend longint operator*(const longint& a, const longint& b);
	friend longint& operator*=(longint& a, const longint& b);
	friend longint operator/(const longint& a, const longint& b);
	friend longint& operator/=(longint& a, const longint& b);
	friend longint operator%(const longint& a, const longint& b);
	friend longint& operator%=(longint& a, const longint& b);

	static longint long_pow(const longint& n, const longint& p);
};