#include <iostream>
#include <fstream>
#include "hugereal.h"
using namespace std;

void loadallnumbers(hugereal*& H, string fname, int& size)
{
	ifstream Rdr(fname);
	Rdr >> size;
	H = new hugereal[size];
	for (int i = 0; i < size; i++)
	{
		while (Rdr.peek() == '\n')
		{
			Rdr.ignore();
		}
		H[i].load(Rdr);
	}
}
void printallnumbers(hugereal* H, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << H[i] << " " << endl;
	}
}
void main()
{
	hugereal* H;
	int size;
	loadallnumbers(H, "Text.txt", size);
	hugereal R;
	int i, j; int op;
	while (true)
	{
		printallnumbers(H, size);
		cout << "1.addition:" << endl;
		cout << "2.subtraction:" << endl;
		cout << "3.faster addition:" << endl;
		cout << "4.faster subtraction:" << endl;
		cout << "5.lessthan:" << endl;
		cout << "6.greater than:" << endl;
		cout << "7.greater than equal to:" << endl;
		cout << "8.less than equal to:" << endl;
		cout << "9.increment:" << endl;
		cout << "10.decrement:" << endl;
		cout << "11.equaliy:" << endl;
		cout << "12.Multiply:" << endl;
		cout << "13.post increment:" << endl;
		cout << "14.post decrement:" << endl;
		cout << "15.Multiply *=:" << endl;
		cout << "\n";
		
		cout << "select operation:" << endl;
		cin >> op;

		cout << "Select your numbers:" << endl;
		cin >> i >> j;

		switch (op)
		{

		case 1:
			R = H[i - 1] + H[j - 1];
			cout <<"Ans = "<< R << endl;
			break;
		case 2:
			R = H[i - 1] - H[j - 1];
			cout << "Ans = "<<R;
			cout << endl;
			break;
		case 3:
		{
			H[i - 1] += H[j - 1];

			cout << endl;

			break;
		}
		case 4:
		{
			H[i - 1] -= H[j - 1];
			cout << endl;
			break;
		}
		case 5:
		{
			if (H[i - 1] < H[j - 1])
			{
				cout << H[i - 1] << " is smaller..." << endl;
			}
			else
			{
				cout << H[j - 1] << " is smaller..." << endl;
			}
			break;
		}
		case 6:
		{
			if (H[i - 1] > H[j - 1])
			{
				cout << H[i - 1] << " is greater..." << endl;
			}
			else
			{
				cout << H[j - 1] << " is greater..." << endl;
			}
			break;
		}
		case 7:
		{
			if (H[i - 1] >= H[j - 1])
			{
				cout << H[i - 1] << " is greater or equal..." << endl;
			}
			else
			{
				cout << H[j - 1] << " is greater or equal..." << endl;
			}
			break;
		}
		case 8:
		{
			if (H[i - 1] <= H[j - 1])
			{
				cout << H[i - 1] << " is less or equal..." << endl;
			}
			else
			{
				cout << H[j - 1] << " is less or equal..." << endl;
			}
			break;
		}
		case 9:
		{
			++H[i - 1];
			cout << endl;
			break;
		}
		case 10:
		{
			--H[j - 1];
			cout << endl;
			break;
		}
		case 11:
		{
			if (H[i - 1] == H[j - 1])
			{
				cout << "both are equal" << endl;
			}
			else
			{
				cout << "unequal" << endl;
			}
			break;
		}
		case 12:
		{
			cout << H[i - 1] * H[j - 1] << endl;
			break;
		}
		case 13:
		{
			cout << H[i - 1]++ << endl;;
			break;
		}
		case 14:
		{
			cout << H[i - 1]-- << endl;;
			break;
		}
		case 15:
		{
			H[i - 1]*=H[j-1];
			break;
		}
		}
	}
}