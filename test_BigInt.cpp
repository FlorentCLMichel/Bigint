// optional argument: base

#include "BigInt.hpp"

int main(int argc, char **argv){

	// We work in base 10 by default
	int base = 10;

	// The base can also be provided as argument
	if (argc > 1) {
		base = stoi(argv[1]);
	}

	// print the character table
	cout << "Character table:" << endl;
	printCharTable(base);

	// ask for two arbitrary-size integers n1 and n2 and a “small” integer n 
	// (n must fit within an int)
	// for the subtraction to work, n2 must be no larger than n1
	cout << "n1 (BigInt): ";
	string n1_;
	cin >> n1_;
	cout << "n2 (BigInt): ";
	string n2_;
	cin >> n2_;
	cout << "n? (Int) ";
	int n;
	cin >> n;

	// convert the strings n1_ and n2_ as arbitrary-size integers
	Bigint n1(n1_, base);
	Bigint n2(n2_, base);

	// print the sum, difference, product, Euclidean division, and modulo
	cout << "n1 + n2 = " << n1+n2 << endl;
	cout << "n1 - n2 = " << n1-n2 << endl;
	cout << "n1 * n2 = " << n1*n2 << endl;
	cout << "n1 // n2 = " << n1/n2 << endl;
	cout << "n1 % n2 = " << n1%n2 << endl;

	// see if n1 and n2 are prime
	if(isPrime(n1)){
		cout << n1 << " is prime" << endl;
	} else{
		cout << n1 << " is not prime" << endl;
	}
	if(isPrime(n2)){
		cout << n2 << " is prime" << endl;
	} else{
		cout << n2 << " is not prime" << endl;
	}

	// print n1 to the power n
	cout << "n1 ^ n = " << pow(n1, n) << endl;

	// print n1!
	Bigint facn1 = factorial(n1);
	cout << "n1! = " << facn1 << endl;

	// print the sum of digits of n1
	cout << "sum of the digits of n1!: " << sumDigits(facn1) << endl;

	// print the first few prime numbers
	cout << "How many primes would you like?" << endl;
	int nPrimes;
	cin >> nPrimes;
	cout << "Here they are:" << endl;
	vector<Bigint> primes = firstPrimes(nPrimes);
	for(int i=1; i<=nPrimes-1; i++){
		cout << primes[i] << ", ";
	}
	cout << primes[nPrimes-1] << endl;
}
