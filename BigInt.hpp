/* 
   A simple library for doing arithmetic operations on non-negative integer 
   with arbitrary size. Integers are implemented as vectors of digits. This 
   implementation is not designed with efficiency in mind and is rather slow 
   compared with dedicated libraries. Instead, it is aimed at showing how 
   arbitrary-size arithmetic can be performed using a simple approach. 
   All operations involving two Bigints assume they have the same base.
*/

#ifndef BigInt
#define BigInt

#include<bits/stdc++.h>
using namespace std;

// print the characters used as digits
void printCharTable(int base);

//// convert a string of digits to a vector 
//vector<char> toVec(string n); 
//
//// convert an integer in base 10 to a vector
//vector<char> toVec(long n); 

class Bigint {
	public:
		
		// Base to be used. The value 10 corresponds to usual decimal numbers. The 
		// values 2 and 16 correspond, for instance, to binary and hexadecimal numbers, 
		// respectively. The library is designed to work with bases between 2 and 62, 
		// using digits between 0 and 9 then capital Latin letters and then lowercase
		// letters. Larger bases may work, but could give unexpected results. 
		int base;
		
		// vector storing the value
		vector<char> value;

		// convert a long int to a Bigint
		explicit Bigint(long n, int base = 10); 

		// convert a string of digits to a Bigint
		Bigint(string n, int base = 10); 
	
		// multiply the value by 10
		void times10(); 

		// multiply the value by 10^n
		void times10(int n);

		// remove leading zeros
		void remLeadZeros(); 
	
		// convert the value to a string
		string tostring(); 
};

// definition of some operators
bool operator>(Bigint n1, Bigint n2);
bool operator==(Bigint n1, Bigint n2);
bool operator<(Bigint n1, Bigint n2);
bool operator>=(Bigint n1, Bigint n2);
bool operator<=(Bigint n1, Bigint n2);
ostream& operator<<(ostream& out, Bigint n);
Bigint operator+(Bigint n1, Bigint n2);
Bigint operator-(Bigint n1, Bigint n2); // assumes n2 <= n1
Bigint operator+(Bigint N, unsigned int n);
Bigint operator+(unsigned int n, Bigint N);
Bigint operator*(unsigned int n, Bigint BN);
Bigint operator*(Bigint BN, unsigned int n);
Bigint operator*(Bigint n1, Bigint n2);
Bigint factorial(Bigint n); // factorial
Bigint pow(Bigint N, unsigned int n); // power
Bigint operator/(Bigint n1, Bigint n2);
Bigint operator%(Bigint n1, Bigint n2);

// finding prime numbers
bool isPrime(Bigint n); 
Bigint nextPrime(Bigint n);
vector<Bigint> firstPrimes(unsigned int n);

// sum of the digits
Bigint sumDigits(Bigint N);

#endif
