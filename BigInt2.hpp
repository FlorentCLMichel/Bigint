/* 
   A simple library for doing arithmetic operations on non-negative integers
   with arbitrary size.
*/

#ifndef BigInt
#define BigInt

#include<iostream>
#include<string>
#include<vector>
#include<random>
using namespace std;

vector<unsigned long> toVec(string n, unsigned int nDigits);
vector<unsigned long> toVec(unsigned long n, unsigned long base);

class Bigint {
    
    private:
        
        // number of base-10 digits per Bigint digit
		unsigned int nDigits;
        
        unsigned long base;
		
        // vector storing the value
		vector<unsigned long> value;

	public:

		// convert a long unsigned int to a Bigint
		explicit Bigint(unsigned long n, unsigned int nDigits = 10); 

		// convert a string of digits to a Bigint
		Bigint(string n, unsigned int nDigits); 
		
        // convert a vector to a Bigint
		Bigint(vector<unsigned long>, unsigned int nDigits); 
	
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

        friend bool isPrime(Bigint n); 

        // get a random Bigint between 0 and N-1
        friend Bigint randomBigint(Bigint N, mt19937 &rng);

        // sum of the digits
        friend Bigint sumDigits(Bigint N);

        friend bool operator>(Bigint n1, Bigint n2);
        friend bool operator==(Bigint n1, Bigint n2);
        friend bool operator>=(Bigint n1, Bigint n2);
        friend bool operator<(Bigint n1, Bigint n2);
        friend bool operator<=(Bigint n1, Bigint n2);
        friend ostream& operator<<(ostream& out, Bigint n);
        friend Bigint operator+(Bigint n1, Bigint n2);
        friend void operator+=(Bigint &n1, Bigint n2);
        friend Bigint operator-(Bigint n1, Bigint n2); // assumes n2 <= n1
        friend void operator-=(Bigint &n1, Bigint n2);
        friend Bigint operator+(Bigint N, unsigned long n);
        friend void operator+=(Bigint &N, unsigned long n);
        friend Bigint operator+(unsigned long n, Bigint N);
        friend Bigint operator*(unsigned long n, Bigint BN);
        friend Bigint operator*(Bigint BN, unsigned long n);
        friend Bigint operator*(Bigint n1, Bigint n2);
        friend Bigint factorial(Bigint n); // factorial
        friend Bigint pow(Bigint N, unsigned int n); // power
        friend Bigint operator/(Bigint n1, Bigint n2);
        friend Bigint operator%(Bigint n1, Bigint n2);
};

Bigint nextPrime(Bigint n);
vector<Bigint> firstPrimes(unsigned int n);


#endif
