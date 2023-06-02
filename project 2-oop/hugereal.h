#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class hugereal
{
private:
	int* Vs;
	int size;
	int* Ds;
	int s;
	bool isnegative;
	void assign(const hugereal&);
	void insertatend(int* &Vs, int &size, int T) const;
	bool greaterthanquantitywise(const hugereal& H) const;
	bool lessthanquantitywise(const hugereal& H) const;
	bool equalthanquantitywise(const hugereal& H) const;
	const hugereal Subquantitywise(const hugereal& H) const;
	const hugereal Addquantitywise(const hugereal& H) const;
public:
	hugereal();
	hugereal(int si,int sz);
	hugereal(int);
	hugereal(const hugereal& H);
	hugereal(ifstream& Rdr);
	const hugereal& operator=(const hugereal&);
	friend ostream& operator<<(ostream&, const hugereal&);
	friend istream& operator>>(istream&, hugereal&);
	void load(ifstream&);
	hugereal& trimp();
	hugereal& trimd();
	int operator[](int i)const;
	int& operator[](int i);
	const hugereal operator+(const hugereal& H) const;
	const hugereal& operator+=(const hugereal& H);
	const hugereal operator-(const hugereal& H) const;
	const hugereal& operator-=(const hugereal& H);
	const hugereal operator-() const;
	bool operator<(const hugereal& H) const;
	bool operator>(const hugereal& H) const;
	bool operator<=(const hugereal& H) const;
	bool operator>=(const hugereal& H) const;
	bool operator==(const hugereal& H) const;
	bool operator!=(const hugereal& H) const;
	static hugereal one();
	static hugereal zero();
	hugereal& operator++();
	hugereal& operator--();
	const hugereal operator* (const hugereal&);
	hugereal& operator*= (const hugereal&);
	hugereal& operator /= (const hugereal&);
	const hugereal operator/ (const hugereal&);
	const hugereal operator% (const hugereal&)const;
	hugereal operator++(int R);
	hugereal operator--(int R);
	~hugereal();
};
