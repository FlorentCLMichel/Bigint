// optional argument: number of digits per number

#include "BigInt2.hpp"

int main(int argc, char **argv){

	int nDigits = 10;

	if (argc > 1) {
		nDigits = stoi(argv[1]);
	}

	// ask for two arbitrary-size integers n1 and n2 and a “small” integer n 
	// (n must fit within an int)
	// for the subtraction to work, n2 must be no larger than n1
	cout << "n1 (BigInt): ";
	string n1_;
	cin >> n1_;
	cout << "n2 (BigInt): ";
	string n2_;
	cin >> n2_;
	cout << "n? (Int): ";
	int n;
	cin >> n;

	// convert the strings n1_ and n2_ as arbitrary-size integers
	Bigint n1(n1_, nDigits);
	Bigint n2(n2_, nDigits);

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

    // random number
    random_device rd;
    mt19937 gen(rd());
    unsigned int nRN;
    string maxRN_s;
    cout << "Number of random numbers:" << endl;
    cin >> nRN;
    cout << "Maximum number:" << endl; 
    cin >> maxRN_s;
    Bigint maxRN(maxRN_s, nDigits);
    uniform_int_distribution<unsigned long> dist(0, 10); //
    for (int i=0; i<nRN-1; i++) {
        cout << randomBigint(maxRN+1, gen) << ", ";
    }
    cout << randomBigint(maxRN+1, gen) << endl;

	// print the first few prime numbers
	cout << "Number of primes:" << endl;
	unsigned int nPrimes;
	cin >> nPrimes;
    if (nPrimes > 1) {
	    cout << "The first " << nPrimes << " primes are:" << endl;
    } else if (nPrimes == 1) {
        cout << "The first prime is:" << endl;
    }
	vector<Bigint> primes = firstPrimes(nPrimes);
	for(int i=0; i<nPrimes-1; i++){
		cout << primes[i] << ", ";
	}
	cout << primes[nPrimes-1] << endl;
}
