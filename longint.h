#pragma once
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class longint
{
private:
	const static char base = 10;

	vector<char> buffer;
	bool negative;

	void copy_init(const vector<char>& copy_buff, bool copy_negative);
	void move_init(vector<char>&& move_buff, bool move_negative);

public:
	longint(long n = 0);

	longint(const vector<char>& copy_buffer, bool copy_negative);
	longint(vector<char>&& move_buffer, bool move_negative);
	longint(const longint& to_copy);
	longint(longint&& to_move);

	friend ostream& operator<<(ostream& out, const longint& n);
	friend istream& operator>>(istream& in, longint& n);

	string to_string() const;
};