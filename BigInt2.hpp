/* 
   A simple library for doing arithmetic operations on non-negative integer 
   with arbitrary size.
*/

#ifndef BigInt
#define BigInt

#include<bits/stdc++.h>
using namespace std;

vector<unsigned long> toVec(string n, unsigned int nDigits);
vector<unsigned long> toVec(unsigned long n, unsigned long base);

class Bigint {
	public:
		
		unsigned int nDigits;
        unsigned long base;
		
		// vector storing the value
		vector<unsigned long> value;

		// convert a long unsigned int to a Bigint
		explicit Bigint(unsigned long n, unsigned int nDigits = 10); 

		// convert a string of digits to a Bigint
		Bigint(string n, unsigned int nDigits = 10); 
	
		// multiply the value by 10
		void times10(); 

		// multiply the value by 10^n
		void times10(unsigned int n);

		// remove leading zeros
		void remLeadZeros(); 

        // next integer
        void next();
        
        // previous integer, or 0 for 0
        void previous();
	
		// convert the value to a string
		string toString(); 
};

// definition of some operators
bool operator>(Bigint n1, Bigint n2);
bool operator==(Bigint n1, Bigint n2);
bool operator>=(Bigint n1, Bigint n2);
bool operator<(Bigint n1, Bigint n2);
bool operator<=(Bigint n1, Bigint n2);
ostream& operator<<(ostream& out, Bigint n);
Bigint operator+(Bigint n1, Bigint n2);
void operator+=(Bigint &n1, Bigint n2);
Bigint operator-(Bigint n1, Bigint n2); // assumes n2 <= n1
void operator-=(Bigint &n1, Bigint n2);
Bigint operator+(Bigint N, unsigned long n);
Bigint operator+(unsigned long n, Bigint N);
Bigint operator*(unsigned long n, Bigint BN);
Bigint operator*(Bigint BN, unsigned long n);
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
