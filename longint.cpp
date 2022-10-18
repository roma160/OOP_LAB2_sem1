#include "longint.h"

void longint::copy_init(const vector<char>& copy_buff, bool copy_negative)
{
	buffer = vector<char>(copy_buff);
	negative = copy_negative;
}

void longint::move_init(vector<char>&& move_buff, bool move_negative)
{
	buffer = move(move_buff);
	negative = move_negative;
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

longint::longint(const vector<char>& copy_buffer, bool copy_negative)
{ copy_init(copy_buffer, copy_negative); }
longint::longint(vector<char>&& move_buffer, bool move_negative)
{ move_init(move(move_buffer), move_negative); }
longint::longint(const longint& to_copy)
{ copy_init(to_copy.buffer, to_copy.negative); }
longint::longint(longint&& to_move)
{ move_init(move(to_move.buffer), to_move.negative); }

string longint::to_string() const
{
	stringstream s;
	if (negative) s << '-';
	for (size_t i = buffer.size(); i > 0; i--)
		s << (char) (buffer[i - 1] + '0');
	return s.str();
}

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
	vector<char> buffer(buff.size() - negative);
	for (size_t i = 0; i < buff.size() - negative; i++)
		buffer[i] = buff[buff.size() - i - 1] - '0';

	n.move_init(move(buffer), negative);
	return in;
}
