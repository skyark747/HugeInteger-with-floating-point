#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "HugeIntegers.h"
using namespace std;

hugeintegers::hugeintegers()
{
	this->size = 0;
	this->Vs = nullptr;
	this->isnegative = false;
}
hugeintegers::hugeintegers(int s)
{
	this->size = s;
	this->Vs = new int[this->size];
}
hugeintegers::hugeintegers(const hugeintegers& H)
{
	assign(H);
}
void hugeintegers::assign(const hugeintegers& H)
{
	this->size = H.size;
	this->Vs = new int[H.size];
	for (int i = 0; i < H.size; i++)
	{
		this->Vs[i] = H.Vs[i];
	}
	this->isnegative = H.isnegative;
}
void hugeintegers::insertatend(int*& Ds, int& s, int T)
{
	int* N = new int[s + 1];
	for (int i = 0; i < s; i++)
	{
		N[i] = Ds[i];
	}
	N[s] = T;
	delete[]Ds;
	s++;
	Ds = N;
}
hugeintegers::hugeintegers(ifstream& Rdr)
{
	this->load(Rdr);
}
void hugeintegers::load(ifstream& Rdr)
{
	char c;
	c = Rdr.peek();
	if (c == '-')
	{
		this->isnegative = true;
		Rdr.ignore();
	}
	else
	{
		this->isnegative = false;
	}
	string Is;
	getline(Rdr, Is);
	this->size = Is.size();
	this->Vs = new int[this->size];
	for (int i = 0; i < this->size; i++)
	{
		this->Vs[this->size - i - 1] = Is[i] - 48;
	}
}
ostream& operator<<(ostream&, const hugeintegers& H)
{
	cout << ((H.isnegative) ? "-" : "+");
	for (int i = 0; i < H.size; i++)
	{
		cout << H.Vs[H.size - i - 1];
	}
	return cout;
}
const hugeintegers& hugeintegers::operator=(const hugeintegers& H)
{
	if (this == &H)
	{
		return *this;
	}
	else
	{
		delete[]this->Vs;
		this->assign(H);
		return  *this;
	}
}
int hugeintegers::operator[](int i)const
{
	if (i >= size)
	{
		return 0;
	}
	return this->Vs[i];
}
int& hugeintegers::operator[](int c)
{
	return this->Vs[c];
}
const hugeintegers hugeintegers::Addquantitywise(const hugeintegers& H) const
{
	hugeintegers R(this->size + 1);
	int carry = 0;
	for (int i = 0; i < R.size; i++)
	{
		int Ans = ((*this)[i] + H[i] + carry) % 10;
		carry = ((*this)[i] + H[i] + carry) / 10;
		R.Vs[i] = Ans;
	}
	R.trimf();
	return R;
}
const hugeintegers hugeintegers::Subquantitywise(const hugeintegers& H) const
{
	hugeintegers R(this->size);
	int carry = 0;
	for (int i = 0; i < R.size; i++)
	{
		int Ans = ((*this)[i] - H[i] - carry) % 10;
		carry = (Ans < 0) ? 1 : 0;
		Ans = (Ans < 0) ? Ans + 10 : Ans;
		R.Vs[i] = Ans;
	}
	R.trimf();
	return R;
}
bool hugeintegers::greaterthanquantitywise(const hugeintegers& H) const
{
	if (this->size > H.size)
	{
		return true;
	}
	else if (this->size == H.size)
	{
		for (int i = this->size - 1; i >= 0; i--)
		{
			if (this->Vs[i] > H.Vs[i])
			{
				return true;
			}
			else if (this->Vs[i] < H.Vs[i])
			{
				return false;
			}
		}
	}
	return false;
}
bool hugeintegers::lessthanquantitywise(const hugeintegers& H) const
{
	return H.greaterthanquantitywise(*this);
}
bool hugeintegers::equalthanquantitywise(const hugeintegers& H) const
{
	int count = 0;
	if (this->size == H.size)
	{
		for (int i = this->size - 1, j = H.size - 1; i >= 0 || j >= 0; i--, j--)
		{
			if (this->Vs[i] == H.Vs[j])
			{
				count++;
			}
		}
		if (count == size)
		{
			return true;
		}
	}
	return false;
}
hugeintegers& hugeintegers::trimf()
{
	stringstream ss;
	for (int i = size - 1; i >= 0; i--)
	{
		ss << Vs[i];
	}
	string R = ss.str();
	int k = 0;
	while (R[k] == '0')
	{
		k++;
	}
	R.erase(0, k);
	this->size = this->size - k;
	for (int i = 0, j = size - 1; i < size || j >= 0; i++, j--)
	{
		Vs[i] = R[j] - 48;
	}
	return *this;
}
const hugeintegers hugeintegers::operator+(const hugeintegers& H) const
{
	if (this->isnegative == H.isnegative)
	{
		if (this->greaterthanquantitywise(H))
		{
			hugeintegers R = this->Addquantitywise(H);
			R.isnegative = this->isnegative;
			return R;
		}
		else if (H.greaterthanquantitywise(*this))
		{
			hugeintegers R = H.Addquantitywise(*this);
			R.isnegative = H.isnegative;
			return R;
		}
		if (this->equalthanquantitywise(H))
		{
			hugeintegers R = this->Addquantitywise(H);
			R.isnegative = this->isnegative;
			return R;
		}
	}
	else if (this->isnegative != H.isnegative)
	{
		if (this->greaterthanquantitywise(H))
		{
			hugeintegers R = this->Subquantitywise(H);
			R.isnegative = this->isnegative;
			return R;
		}
		else if (H.greaterthanquantitywise(*this))
		{
			hugeintegers R = H.Subquantitywise(*this);
			R.isnegative = H.isnegative;
			return R;
		}
		if (this->equalthanquantitywise(H))
		{
			hugeintegers R = this->Subquantitywise(*this);
			R.isnegative = this->isnegative;
			return R;
		}
	}
}
const hugeintegers hugeintegers::operator-() const
{
	hugeintegers R = *this;
	R.isnegative = !R.isnegative;
	return R;
}
const hugeintegers hugeintegers::operator-(const hugeintegers& H) const
{
	return *this + (-H);
}
bool hugeintegers::operator<(const hugeintegers& H) const
{
	if (this->isnegative != H.isnegative)
	{
		return this->isnegative == true;
	}
	else if (this->isnegative == true)
	{
		return this->greaterthanquantitywise(H);
	}
	else
	{
		return this->lessthanquantitywise(H);
	}
}
bool hugeintegers::operator>(const hugeintegers& H) const
{
	return H < *this;
}
bool hugeintegers::operator==(const hugeintegers& H) const
{
	if (this->isnegative == H.isnegative)
	{
		return this->equalthanquantitywise(H);
	}
}
bool hugeintegers::operator!=(const hugeintegers& H) const
{
	if (this->equalthanquantitywise(H))
	{
		return false;
	}
	return true;
}
bool hugeintegers::operator<=(const hugeintegers& H) const
{
	if ((*this < H || *this == H))
	{
		return true;
	}
	return false;
}
bool hugeintegers::operator>=(const hugeintegers& H) const
{
	return H <= *this;
}
hugeintegers hugeintegers::one()
{
	hugeintegers R(1);
	R.Vs[0] = 1;
	return R;
}
hugeintegers hugeintegers::zero()
{
	hugeintegers R(1);
	R.Vs[0] = 0;
	return R;
}
hugeintegers& hugeintegers::operator++()
{
	*this = *this + hugeintegers::one();
	return *this;
}
hugeintegers hugeintegers::operator++(int c)
{
	hugeintegers R = *this;
	R = R + hugeintegers::one();
	return R;
}
hugeintegers& hugeintegers::operator--()
{
	*this = *this - hugeintegers::one();
	return *this;
}
hugeintegers hugeintegers::operator--(int c)
{
	hugeintegers R = *this;
	R = R - hugeintegers::one();
	return R;
}
const hugeintegers& hugeintegers::operator+=(const hugeintegers& H)
{
	*this = *this + H;
	return *this;
}
hugeintegers& hugeintegers::operator-=(const hugeintegers& H)
{
	*this = *this - H;
	return *this;
}
istream& operator>>(istream&, hugeintegers& H)
{
	char c;
	c = cin.peek();
	if (c == '-')
	{
		H.isnegative = true;
		cin.ignore();
	}
	else
	{
		H.isnegative = false;
	}
	string Is;
	getline(cin, Is);
	H.size = Is.size();
	H.Vs = new int[H.size];
	for (int i = 0; i < H.size; i++)
	{
		H.Vs[H.size - i - 1] = Is[i] - 48;
	}
	return cin;
}
const hugeintegers hugeintegers::operator* (const hugeintegers& H)
{
	hugeintegers V;
	hugeintegers A = *this;
	hugeintegers B = H;
	hugeintegers T = hugeintegers::zero();
	hugeintegers count;
	do
	{
		V = A;
		count = hugeintegers::one();
		while (count + count <= B)
		{
			V += V;
			count += count;
		}
		B -= count;
		T += V;
	} while (B >= hugeintegers::zero());
	return T;

}
hugeintegers& hugeintegers::operator*= (const hugeintegers& H)
{
	*this = *this * H;
	return *this;
}
//const hugeintegers hugeintegers::operator* (const hugeintegers& H)
//{
//	hugeintegers R = hugeintegers::zero();
//	for (hugeintegers c = hugeintegers::zero(); c < H; ++c)
//	{
//		R += *this;
//	}
//	return R;
//}
const hugeintegers hugeintegers::operator/ (const hugeintegers& H)
{
	hugeintegers V;
	hugeintegers A = *this;
	hugeintegers B = H;
	hugeintegers T = hugeintegers::zero();
	hugeintegers count;
	do
	{
		V = B;
		count = hugeintegers::one();
		while ((V + V) <= A)
		{
			V += V;
			count += count;
		}
		T += count;
		A -= V;
	} while (A >= hugeintegers::zero());
	return T;
}
hugeintegers& hugeintegers::operator /= (const hugeintegers& H)
{
	*this = *this / H;
	return *this;
}
const hugeintegers hugeintegers::operator% (const hugeintegers& H)const
{
	hugeintegers V;
	hugeintegers A = *this;
	hugeintegers B = H;
	hugeintegers T = hugeintegers::zero();
	hugeintegers count;
	do
	{
		V = B;
		count = hugeintegers::one();
		while ((V + V) <= A)
		{
			V += V;
			count += count;
		}
		T += count;
		A -= V;
	} while (A >= hugeintegers::zero());
	return A;
}
hugeintegers::~hugeintegers()
{
	delete[]Vs;
}