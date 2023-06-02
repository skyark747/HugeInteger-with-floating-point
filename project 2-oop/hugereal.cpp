#include "hugereal.h"
#include "hugeintegers.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

hugereal::hugereal()
{
	this->Vs = NULL;
	this->Ds = nullptr;
	this->s = 0;
	this->size = 0;
	this->isnegative = false;
}
hugereal::hugereal(int Size,int Sz)
{
	this->size = Size;
	this->s = Sz;
	this->Vs = new int[Size];
	this->Ds = new int[Size];
}
hugereal::hugereal(const hugereal& H)
{
	assign(H);
}
void hugereal::assign(const hugereal& H)
{
	this->size = H.size;
	this->Vs = new int[size];
	for (int i = 0; i < size; i++)
	{
		Vs[i] = H.Vs[i];
	}
	this->s = H.s;
	this->Ds = new int[s];
	for (int i = 0; i < size; i++)
	{
		Ds[i] = H.Ds[i];
	}
	this->isnegative = H.isnegative;
}
void hugereal::load(ifstream& Rdr)
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
	getline(Rdr, Is, '.');
	this->size = Is.size();
	this->Vs = new int[this->size];
	int i;
	for (i = 0; i < Is.size(); i++)
	{
		if (Is[i] >= 'A' && Is[i] <= 'Z')
		{
			this->Vs[this->size - i - 1] = Is[i] - 55;
		}
		else if (Is[i] >= '0' && Is[i] <= '9')
		{
			this->Vs[this->size - i - 1] = Is[i] - 48;
		}
	}
	string Cs;
	getline(Rdr, Cs);
	this->s = Cs.size();
	this->Ds = new int[this->s];
	for (int j = 0; j < Cs.size(); j++)
	{
		if (Cs[j] >= 'A' && Cs[j] <= 'Z')
		{
			this->Ds[this->size - j - 1] = Cs[j] - 55;
		}
		else if (Cs[j] >= '0' && Cs[j] <= '9')
		{
			this->Ds[this->s - j - 1] = Cs[j] - 48;
		}
	}

}
void hugereal::insertatend(int* &Vs, int &size, int T) const
{
	int* New = new int[size + 1];
	for (int i = 0; i < this->size; i++)
	{
		New[i] = Vs[i];
	}
	New[size] = T;
	delete[]Vs;
	size++;
	Vs = New;
}
hugereal::hugereal(ifstream& Rdr)
{
	this->load(Rdr);
}
ostream& operator<<(ostream&, const hugereal& H)
{
	cout << ((H.isnegative) ? "-" : "+");
	for (int i = 0; i < H.size; i++)
	{
		cout << H.Vs[H.size-i-1];
	}
	cout << ".";
	for (int i = 0; i < H.s; i++)
	{
		cout << H.Ds[H.s - i - 1];
	}
	return cout;
}
istream& operator>>(istream&, hugereal& H)
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
	getline(cin, Is, '.');
	H.size = Is.size();
	H.Vs = new int[H.size];
	int i = 0;
	for (i = 0; i < H.size; i++)
	{
		H.Vs[H.size - i - 1] = Is[i] - 48;
	}
	string Cs;
	getline(cin, Cs);
	H.s = Cs.size();
	H.Ds = new int[H.s];
	for (int j = 0; j < H.s; j++)
	{
		H.Ds[H.s - j - 1] = Cs[j] - 48;
	}
	return cin;
}
const hugereal& hugereal::operator=(const hugereal& H)
{
	if (this == &H)
	{
		return *this;
	}
	else
	{
		delete[]this->Vs;
		delete[]this->Ds;
		this->assign(H);
		return  *this;
	}
}
hugereal& hugereal::trimp()
{
	stringstream ss;
	for (int i = this->size-1; i >= 0; i--)
	{
		ss << this->Vs[i];
	}
	string R = ss.str();
	int k = 0;
	while (R[k] == '0')
	{
		k++;
	}
	R.erase(0, k);
	this->size = this->size - k;
	for (int i = 0, j = size-1; i < size || j >= 0; i++, j--)
	{
		Vs[i] = R[j] - 48;
	}

	return *this;
}
hugereal& hugereal::trimd()
{
	stringstream ss;
	for (int i = this->s - 1; i >= 0; i--)
	{
		ss << this->Ds[i];
	}
	string R = ss.str();
	int k = 0;
	while (R[k] == '0')
	{
		k++;
	}
	R.erase(0, k);
	this->s = this->s - k;
	for (int i = 0, j = s - 1; i < s || j >= 0; i++, j--)
	{
		Ds[i] = R[j] - 48;
	}
	return *this;
}
int hugereal::operator[](int i)const
{
	if (i >= size)
	{
		return 0;
	}
	return (this->Vs[i]);
}
int& hugereal::operator[](int c)
{
	return this->Vs[c];
}
const hugereal hugereal::Addquantitywise(const hugereal& H) const
{
	hugereal R(this->size+1, this->s);
	int carry = 0;
	if (this->s > H.s)
	{
		for (int i = 0; i < R.s; i++)
		{
			int Ans = (this->Ds[this->s-i-1] + H.Ds[i] + carry) % 10;
			carry = (this->Ds[this->s-i-1] + H.Ds[H.s-i-1] + carry) / 10;
			carry = (Ans < 0) ? 1 : 0;
			Ans = (Ans < 0) ? Ans + 10 - carry : Ans;
			R.Ds[R.s-i-1] = Ans;
		}
	}
	else if (this->s < H.s)
	{
		for (int i = 0; i <= R.s; i++)
		{
			int Ans = (this->Ds[i] + H.Ds[H.s-i-1] + carry) % 10;
			carry = (this->Ds[i] + H.Ds[H.s-i-1] + carry) / 10;
			carry = (Ans < 0) ? 1 : 0;
			Ans = (Ans < 0) ? Ans + 10 - carry : Ans;
			R.Ds[R.s-i-1] = Ans;
		}
	}
	else if (this->s == H.s)
	{
		for (int i = 0; i < R.s; i++)
		{
			int Ans = (this->Ds[i] + H.Ds[i] + carry) % 10;
			carry = (this->Ds[i] + H.Ds[i] + carry) / 10;
			R.Ds[i] = Ans;
		}
	}
	for (int i = 0; i < R.size; i++)
	{
		int Ans = (this->Vs[i] + H.Vs[i] + carry) % 10;
		carry = (this->Vs[i] + H.Vs[i] + carry) / 10;
		carry = (Ans < 0) ? 1 : carry;
		Ans = (Ans < 0) ? Ans + 10-carry-1 : Ans;
		R.Vs[i] = Ans;
	}
	R.trimp();
	return R;
}
const hugereal hugereal::Subquantitywise(const hugereal& H) const
{
	hugereal R(this->size, this->s);
	int carry = 0;
	if (this->s > H.s)
	{
		for (int i = 0; i < R.s; i++)
		{
			int Ans = (this->Ds[this->s - i - 1] - H.Ds[i] - carry) % 10;
			carry = (Ans < 0) ? 1 : 0;
			Ans = (Ans < 0) ? Ans + 10: Ans;
			R.Ds[R.s - i - 1] = Ans;
		}
	}
	else if (this->s < H.s)
	{
		for (int i = 0; i < R.s; i++)
		{
			int Ans = (this->Ds[i] - H.Ds[H.s - i - 1] - carry) % 10;
			carry = (Ans < 0) ? 1 : 0;
			Ans = (Ans < 0) ? Ans + 10: Ans;
			R.Ds[R.s - i - 1] = Ans;
		}
	}
	else if (this->s == H.s)
	{
		for (int i = 0; i < R.s; i++)
		{
			int Ans = (this->Ds[i] - H.Ds[i] - carry) % 10;
			carry = (Ans < 0) ? 1 : 0;
			Ans = (Ans < 0)?Ans + 10:Ans;
			R.Ds[i] = Ans;
		}
	}

	for (int i = 0; i < R.size; i++)
	{
		H.Vs[H.size] = 0;
		int Ans = (this->Vs[i] - H.Vs[i] - carry) % 10;
		carry = (Ans < 0) ? 1 : 0;
		Ans = (Ans < 0) ? Ans + 10 : Ans;
		R.Vs[i] = Ans;
	}
	if (*R.Vs == 0)
	{

	}
	else
	R.trimp();
	return R;
}
bool hugereal::greaterthanquantitywise(const hugereal& H) const
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
	if (this->s < H.s)
	{
		return true;
	}
	else if(this->s==H.s)
	{
		for (int i = this->s - 1; i >= 0; i--)
		{
			if (this->Ds[i] > H.Ds[i])
			{
				return true;
			}
			else if (this->Ds[i] < H.Ds[i])
			{
				return false;
			}
		}
	}
	return false;
}
bool hugereal::lessthanquantitywise(const hugereal& H) const
{
	return H.greaterthanquantitywise(*this);
}
bool hugereal::equalthanquantitywise(const hugereal& H) const
{
	if (!this->greaterthanquantitywise(H) && !this->lessthanquantitywise(H))
	{
		return true;
	}
	return false;
}
const hugereal hugereal::operator+(const hugereal& H) const
{
	if (this->isnegative == H.isnegative)
	{
		if (this->greaterthanquantitywise(H))
		{
			hugereal R = this->Addquantitywise(H);
			R.isnegative = this->isnegative;
			return R;
		}
		else if (H.greaterthanquantitywise(*this))
		{
			hugereal R = H.Addquantitywise(*this);
			R.isnegative = H.isnegative;
			return R;
		}
		if (this->equalthanquantitywise(H))
		{
			hugereal R = this->Addquantitywise(H);
			R.isnegative = this->isnegative;
			return R;
		}
	}
	else if (this->isnegative != H.isnegative)
	{
		if (this->greaterthanquantitywise(H))
		{
			hugereal R = this->Subquantitywise(H);
			R.isnegative = this->isnegative;
			return R;
		}
		else if (H.greaterthanquantitywise(*this))
		{
			hugereal R = H.Subquantitywise(*this);
			R.isnegative = H.isnegative;
			return R;
		}
		if (this->equalthanquantitywise(H))
		{
			hugereal R = this->Subquantitywise(*this);
			R.isnegative = this->isnegative;
			return R;
		}
	}
}
const hugereal hugereal::operator-() const
{
	hugereal R = *this;
	R.isnegative = !R.isnegative;
	return R;
}
const hugereal hugereal::operator-(const hugereal& H) const
{
	return *this + (-H);
}
const hugereal& hugereal::operator+=(const hugereal& H)
{
	*this = *this + H;
	return *this;
}
const hugereal& hugereal::operator-=(const hugereal& H)
{
	*this = *this - H;
	return *this;
}
bool hugereal::operator<(const hugereal& H) const
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
bool hugereal::operator>(const hugereal& H) const
{
	return H < *this;
}
bool hugereal::operator<=(const hugereal& H) const
{
	if (*this < H || *this == H)
	{
		return true;
	}
	return false;
}
bool hugereal::operator==(const hugereal& H) const
{
	if (this->isnegative == H.isnegative)
	{
		return this->equalthanquantitywise(H);
	}
}
bool hugereal::operator>=(const hugereal& H) const
{
	return H <= *this;
}
bool hugereal::operator!=(const hugereal& H) const
{
	if (this->equalthanquantitywise(H))
	{
		return false;
	}
	return true;
}
hugereal hugereal::one()
{
	hugereal R(1,1);
	R.Vs[0] = 1;
	R.Ds[0] = 0;
	return R;
}
hugereal hugereal::zero()
{
	hugereal R(1,1);
	R.Vs[0] = 0;
	R.Ds[0] = 0;
	return R;
}
hugereal& hugereal::operator++()
{
	*this = *this + hugereal::one();
	return *this;
}
hugereal& hugereal::operator--()
{
	*this = *this - hugereal::one();
	return *this;
}
hugereal hugereal::operator++(int c)
{
	hugereal R;
	R = *this;
	R = R + hugereal::one();
	return R;
}
hugereal hugereal::operator--(int c)
{
	hugereal R;
	R = *this;
	R = R - hugereal::one();
	return R;
}

const hugereal hugereal::operator*(const hugereal& H)
{
	int* Fs = new int[this->size + this->s]; int c1 = 0;
	int* Gs = new int[H.size + H.s]; int c2 = 0;
	int i;
	for (i = 0; i < this->s; i++)
	{
		Fs[i] = this->Ds[i]; c1++;
	}
	for (int j = i,k=0; j < this->size||k<this->size; j++,k++)
		Fs[j] = this->Vs[k];

	int it;
	for (it = 0; it < H.s; it++) 
	{
		Gs[it] = H.Ds[it]; c2++;
	}
	for (int j = it, k = 0; j < H.size || k < H.size; j++, k++)
		Gs[j] = H.Vs[k];

	hugeintegers T(this->size + this->s);
	hugeintegers Y(H.size + H.s);

	for (int i = 0; i < this->size + this->s; i++)
		T.Vs[i] = Fs[i];
	for (int i = 0; i < H.size + H.s; i++)
		Y.Vs[i] = Gs[i];

	hugeintegers R = T * Y;
	int Dp = c1 + c2;
	hugereal Rs(R.size-Dp,Dp);
	for (int i = 0; i < Dp; i++)
	{
		Rs.Ds[i] = R.Vs[i];
	}
	for (int i = Dp,j=0; i < Rs.size||j<Rs.size; i++,j++)
	{
		Rs.Vs[j] = R.Vs[i];
	}
	delete[]Fs; delete[]Gs;
	return Rs;
}
hugereal& hugereal::operator*=(const hugereal& H)
{
	*this = *this * H;
	return *this;
}
hugereal::~hugereal()
{

}