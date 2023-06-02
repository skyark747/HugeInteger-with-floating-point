#pragma once
#include <iostream>
#include <fstream>
using namespace std;
class hugeintegers
{
public:
	hugeintegers();
	hugeintegers(int size);
	hugeintegers(const hugeintegers& H);
	hugeintegers(ifstream& Rdr);
	const hugeintegers& operator=(const hugeintegers&);
	friend ostream& operator<<(ostream&, const hugeintegers&);
	friend istream& operator>>(istream&, hugeintegers&);
	void load(ifstream&);
	int operator[](int) const;
	int& operator[](int);
	hugeintegers& trimf();
	const hugeintegers operator+(const hugeintegers& H) const;
	const hugeintegers& operator+=(const hugeintegers& H);
	const hugeintegers operator-(const hugeintegers& H) const;
	hugeintegers& operator-=(const hugeintegers& H);
	const hugeintegers operator-() const;
	bool operator<(const hugeintegers& H) const;
	bool operator>(const hugeintegers& H) const;
	bool operator<=(const hugeintegers& H) const;
	bool operator>=(const hugeintegers& H) const;
	bool operator==(const hugeintegers& H) const;
	bool operator!=(const hugeintegers& H) const;
	static hugeintegers one();
	static hugeintegers zero();
	hugeintegers& operator++();
	hugeintegers& operator--();
	const hugeintegers operator* (const hugeintegers&);
	hugeintegers& operator*= (const hugeintegers&);
	hugeintegers& operator /= (const hugeintegers&);
	const hugeintegers operator/ (const hugeintegers&);
	const hugeintegers operator% (const hugeintegers&)const;
	hugeintegers operator++(int R);
	hugeintegers operator--(int R);
	~hugeintegers();

	int* Vs;
	int size;
	bool isnegative;
	void assign(const hugeintegers&);
	static void insertatend(int*&, int&, int);
	const hugeintegers Addquantitywise(const hugeintegers&) const;
	const hugeintegers Subquantitywise(const hugeintegers&) const;
	bool lessthanquantitywise(const hugeintegers&) const;
	bool greaterthanquantitywise(const hugeintegers&) const;
	bool equalthanquantitywise(const hugeintegers&) const;
};
