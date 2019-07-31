// a lab assignment on C++ inheritance and operator overriding
//

#include "stdafx.h"
#include "iostream"
#include "string"
#pragma warning(disable : 4996)
using namespace std;

class Stroka { //base class representing a string
protected:
	char *st;
	int len;
public:
	Stroka() {
		cout << "Empty constructor" << endl;
	}
	Stroka(char *str) {
		len = strlen(str);
		st = new char[len + 1];
		strcpy(st, str);
		cout << "String: " << st << endl;
	}
	// doesn't work properly or, more likely, just poorly implemented
	//Stroka(const Stroka &d) {
	//	len = strlen(d.st);
	//	st = new char[len + 1];
	//	strcpy(st, d.st);
	// cout << "Copy constructor: " << st << endl;
	//}
	int get() {
		len = strlen(st);
		return len;
	}
	void prin() {
		cout << st;
	}
	void clean() {
		*st = NULL;
	}
	~Stroka() {
		delete[] st;
		cout << "Destructed" << endl;
	}
};

class Bit_Stroka : public Stroka { //derived class, a binary representation of the base class string
public:
	/*using Stroka::Stroka;*/
	~Bit_Stroka() {
		delete[] cp;
		binstr = "";
		stch = 0;
		cout << "Derived destructor" << endl;
	}
	Bit_Stroka() {
		cout << "Empty derived constructor" << endl;
	}
	Bit_Stroka(char *s) : Stroka(s) {
		checknum(s);
		cout << "Derived variable: " << s << endl;
	}
	// also is poorly implemented
	//Bit_Stroka(const Bit_Stroka &d) : Stroka(d) {
	//	int ln = strlen(d.cp);
	//	cp = new char[ln + 1];
	//	strcpy(cp, d.cp);
	//	checknum(cp);
	//  cout << "Derived copy: " << cp << endl;
	//}
	//
	bool operator==(const Bit_Stroka& d) {
		if (binstr.compare(d.binstr) == 0) {
			return true;
		}
		else {
			return false;
		}

	}
	void operator = (const Bit_Stroka& d) {
		stch = d.stch;
		binstr = d.binstr;
	}
	Bit_Stroka operator+(const Bit_Stroka& d) { //binary addition
		Bit_Stroka Bit_Stroka;
		Bit_Stroka.stch = this->stch + d.stch;
		/*string first;
		string second;
		first = this->binstr;
		second = d.binstr;*/
		int carry = 0;
		for (int i = 32 - 1; i > 0; i--)
		{
			int firstBit = this->binstr.at(i) - '0';
			int secondBit = d.binstr.at(i) - '0';
			int sum = (firstBit ^ secondBit ^ carry) + '0';

			Bit_Stroka.binstr = (char)sum + Bit_Stroka.binstr;
			carry = (firstBit & secondBit) | (secondBit & carry) | (firstBit & carry);
		}

		if (carry)
			Bit_Stroka.binstr = '1' + Bit_Stroka.binstr;

		return Bit_Stroka;
	}
	void prinnyb() { //print regular number
		cout << stch;
	}
	void prinny() { //print binary number
		cout << binstr;
	}
private:
	char *cp;
	int stch;
	string binstr;

	void checknum(char *stb) {
		//if the string is not a number, empty it
		if (*stb == NULL || ((!isdigit(stb[0])) && (stb[0] != '-') && (stb[0] != '+'))) { *st = NULL; } 
		else {
			char *p;
			stch = strtol(stb, &p, 10);
			binstr = decimal_to_binary(stch);

		}
	}
	string decimal_to_binary(int n) { //convert a number into its binary representation
		int d;
		d = n;
		if (d<0) {
			d = 2147483648 + d;
		}
		string zeroes = "";
		string result = "";
		while (d > 0) {
			result = string(1, (char)(d % 2 + 48)) + result;
			d = d / 2;
		}
		if (n > 0) {
			for (int i = 0; i < (32 - result.size()); i++) {
				zeroes += '0';
			}
			result = zeroes + result;
			return result;
		}
		else {
			return result;
		}
	}
};


int main()
{
	Bit_Stroka test1("20");
	Bit_Stroka test2("2");
	Bit_Stroka test3("");
	cout << endl << "First slagaemoe: ";
	test1.prinnyb();
	cout << " Binary: ";
	test1.prinny();
	cout << endl;
	cout << "Second slagaemoe: ";
	test2.prinnyb();
	cout << " Binary: ";
	test2.prinny();
	cout << endl << endl;
	test3 = test2 + test1;
	cout << endl << "Result: ";
	test3.prinnyb();
	cout << " Binary: ";
	test3.prinny();
	cout << endl << endl;
	system("pause");
	return 0;
}



