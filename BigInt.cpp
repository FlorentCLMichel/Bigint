#include "BigInt.hpp"


void printCharTable(int base){
	for(int i=0; i<base; i++){
		if (i < 10){
			cout << (char)(i+'0');
		} else if (i < 36) {
			cout << (char)(i-10+'A');
		} else {
			cout << (char)(i-36+'a');
		}
	}
	cout << endl;
}


vector<char> toVec(string n){
	vector<char> res;
	for(int i=n.size()-1; i>=0; i--){
		if ((n[i] >= '0') && (n[i] <= '9')){
			res.push_back(n[i]-'0');
		} else if ((n[i] >= 'A') && (n[i] <= 'Z')) {
			res.push_back(n[i]+10-'A');
		} else {
			res.push_back(n[i]+36-'a');
		}
	}
	return res;
}


vector<char> toVec(long n, int base){
	vector<char> res;
	char mod;
	while(n>0){
		mod = n % base;
		res.push_back(mod);
		n = (n-mod)/base;
	}
	return res;
}


Bigint::Bigint(long n, int base): base(base){
	value = toVec(n, base);
}


Bigint::Bigint(string n, int base): base(base){
	value = toVec(n);
}
		
void Bigint::times10(){
	value.insert(value.begin(),0);
}


void Bigint::times10(int n){
	for(int i=0; i<n; i++){
		value.insert(value.begin(),0);
	}
}


void Bigint::remLeadZeros(){
	int last = -1;
	for(int i = value.size()-1; i>=0; i--){
		if(value[i] > 0){
			last = i;
			break;
		}
	}
	value.resize(last+1);
}


string Bigint::tostring(){
	string res = "";
	for(int i = value.size()-1; i>=0; i--){
		if (value[i] < 10) {
			res += (char) (value[i]+'0');
		} else if (value[i] < 36) {
			res += (char) (value[i]-10+'A');
		} else {
			res += (char) (value[i]-36+'a');
		}
	}
	return res;
}


bool operator>(Bigint n1, Bigint n2){
	if(n1.value.size() > n2.value.size()){
		return true;
	}
	else if(n1.value.size() < n2.value.size()){
		return false;
	}
	else{
		if(n1.value.size()==0){
			return true;
		}
		for(int i=n1.value.size()-1; i>=0; i--){
			if(n1.value[i] > n2.value[i]){
				return true;
			}
			if(n1.value[i] < n2.value[i]){
				return false;
			}
		}
		return false;
	}
}


bool operator==(Bigint n1, Bigint n2){
	if(n1.value.size() > n2.value.size()){
		return false;
	}
	else if(n1.value.size() < n2.value.size()){
		return false;
	}
	else{
		if(n1.value.size()==0){
			return true;
		}
		for(int i=n1.value.size()-1; i>=0; i--){
			if(n1.value[i] != n2.value[i]){
				return false;
			}
		}
		return true;
	}
}


bool operator>=(Bigint n1, Bigint n2){
	return (n1 > n2) || (n1 == n2);
}


bool operator<(Bigint n1, Bigint n2){
	return !(n2 >= n1);
}


bool operator<=(Bigint n1, Bigint n2){
	return !(n2 > n1);
}


ostream& operator<<(ostream& out, Bigint n){
	if(n.value.size()==0){
		out << '0';
	}
	else{
		for(int i=n.value.size()-1; i>=0; i--){
			if (n.value[i] < 10){
				out << (char) (n.value[i] + '0');
			} else if (n.value[i] < 36) {
				out << (char) (n.value[i] - 10 + 'A');
			} else {
				out << (char) (n.value[i] - 36 + 'a');
			}
		}
	}
}


Bigint operator+(Bigint n1, Bigint n2){
	Bigint res(0, n1.base);
	char retenue = 0;
	int sumDigits = 0;
	int l1 = n1.value.size();
	int l2 = n2.value.size();
	for(int i=0; i<max(l1,l2); i++){
		if((i<l1) && (i<l2)){
			sumDigits = n1.value[i] + n2.value[i] + retenue;
			if(sumDigits >= n1.base){
				sumDigits = sumDigits-n1.base;
				retenue = 1;
			}
			else{
				retenue = 0;
			}
		}
		else if(i < l1){
			sumDigits = n1.value[i] + retenue;
			if(sumDigits >=n1.base){
				sumDigits = sumDigits-n1.base;
				retenue = 1;
			}
			else{
				retenue = 0;
			}
		}
		else if(i < l2){
			sumDigits = n2.value[i] + retenue;
			if(sumDigits >=n1.base){
				sumDigits = sumDigits-n1.base;
				retenue = 1;
			}
			else{
				retenue = 0;
			}
		}
		res.value.push_back(sumDigits);
	}
	if(retenue==1){
		res.value.push_back(1);
	}
	return res;
}


Bigint operator-(Bigint n1, Bigint n2){
	if (n2 > n1) {
		cout << "Can't subtract a Bigint from a smaller Bigint" << endl;
		return Bigint(0, n1.base);
	}
	Bigint res(0, n1.base);
	char retenue = 0;
	int difDigits = 0;
	int l1 = n1.value.size();
	int l2 = n2.value.size();
	for(int i=0; i<max(l1,l2); i++){
		if(i<l2){
			difDigits = n1.value[i] - n2.value[i] - retenue;
			if(difDigits < 0){
				difDigits = difDigits+n1.base;
				retenue = 1;
			}
			else{
				retenue = 0;
			}
		}
		else{
			difDigits = n1.value[i] - retenue;
			if(difDigits < 0){
				difDigits = difDigits+n1.base;
				retenue = 1;
			}
			else{
				retenue = 0;
			}
		}
		res.value.push_back(difDigits);
	}
	if(retenue==1){
		res.value.push_back(1);
	}
	res.remLeadZeros();
	return res;
}


Bigint operator+(Bigint N, unsigned int n){
	Bigint res = N + Bigint(n, N.base);
	return res;
}


Bigint operator+(unsigned int n, Bigint N){
	return N + Bigint(n, N.base);
}


Bigint operator*(unsigned int n, Bigint BN){
	Bigint res(0, BN.base);
	for(int i=0; i<n; i++){
		res = res + BN;
	}
	res.remLeadZeros();
	return res;
}


Bigint operator*(Bigint BN, unsigned int n){
	Bigint res(0, BN.base);
	for(int i=0; i<n; i++){
		res = res + BN;
	}
	res.remLeadZeros();
	return res;
}


Bigint operator*(Bigint n1, Bigint n2){
	Bigint res(0, n1.base);
	Bigint n1Pow10 = n1;
	Bigint temp(0, n1.base);
	for(int i=0; i<n2.value.size(); i++){
		res = res + n2.value[i]*n1Pow10;
		n1Pow10.times10();
	}
	res.remLeadZeros();
	return res;
}


// Bigint factorial(Bigint n){
// 	if(n == Bigint(0, n.base)){
// 		return Bigint(1, n.base);
// 	}
// 	else{
// 		return n*factorial(n-1);
// 	}
// }
// 
// 
// version with tail recursion, seems slightly slower and more memory-consuming
//Bigint factorial_(Bigint &n, Bigint &res){
//	if(n == Bigint(0)){
//		return res;
//	}
//	else{
//		res = n*res;
//		n = n-1;
//		return factorial_(n, res);
//	}
//}
//
//Bigint factorial(Bigint n){
//	Bigint un(1);
//	return factorial_(n,un);
//}
//
//
// loop version
Bigint factorial(Bigint n){
	Bigint res(1, n.base);
	while(n > Bigint(1, n.base)){
		res = n*res;
		n = n - Bigint(1, n.base);
	}
	return res;
}


Bigint pow(Bigint N, unsigned int n){
	Bigint res(1, N.base);
	for(int i=0; i<n; i++){
		res = N*res;
	}
	return res;
}

Bigint operator/(Bigint n1, Bigint n2){
	try{
		Bigint res(0, n1.base);
		if(!(n2>Bigint(0, n1.base))){
			throw 0;
		}
		long s1 = n1.value.size();
		long s2 = n2.value.size();
		if(s1 > s2 + 1){
			Bigint n2_ = n2;
			n2_.times10(s1-s2-1);
			res = n1/n2_;
			res.times10(s1-s2-1);
			res = res +  (n1 - n2*res)/n2;
			return res;
		}
		while(n1 >= n2){
			res = res+1;
			n1 = n1-n2;
		}
		return res;
	}
	catch(int e){
		cout << "I can't divide by zero :(" << endl;
		return Bigint(0, n1.base);
	}
}


// old, less efficient version
//Bigint operator/(Bigint n1, Bigint n2){
//	try{
//		Bigint i(0);
//		if(n2==i){
//			throw 0;
//		}
//		while(n1 >= n2){
//			i = i+1;
//			n1 = n1-n2;
//		}
//		return i;
//	}
//	catch(int e){
//		cout << "I can't divide by zero :(" << endl;
//		return Bigint(0);
//	}
//}


Bigint operator%(Bigint n1, Bigint n2){
	try{
		Bigint i(0, n1.base);
		if(n2==i){
			throw 0;
		}
		Bigint res = n1-(n1/n2)*n2;
		res.remLeadZeros();
		return res;
	}
	catch(int e){
		cout << "I can't divide by zero :(" << endl;
		return Bigint(0, n1.base);
	}
}


bool isPrime(Bigint n){
	if((n.value.size() == 0) || ((n.value.size()==1) && (n.value[0] < 2))){
		return false;
	}
	Bigint k(2, n.base);
	Bigint Zero(0, n.base);
	while(k*k <= n){
		if(n%k == Zero){
			return false;
		}
		k = k+1;
	}
	return true;
}


Bigint nextPrime(Bigint n){
	n = n+1;
	while(!isPrime(n)){
		n=n+1;
	}
	return n;
}


vector<Bigint> firstPrimes(unsigned int n) {
	
	if (n == 0)
		return vector<Bigint>();
	if (n == 1) {
		vector<Bigint> primes = {Bigint(2)};
		return primes; 
	}
	if (n == 2) {
		vector<Bigint> primes = {Bigint(2),Bigint(3)};
		return primes; 
	}

	vector<Bigint> primes = {Bigint(2),Bigint(3)};
	Bigint x(4);
	Bigint zero(0);
	for (int i=2; i<n; i++) {
		bool isNotPrime = true; 
		while (isNotPrime) {
			x = x + 1;
			isNotPrime = false;
			for (int j=0; j<i; j++) {
				if (primes[j] * primes[j] > x) {
					break;
				}
				if (x % primes[j] == zero) {
					isNotPrime = true;
					break;
				}
			}
		}
		primes.push_back(x);
	}
	return primes;
}


Bigint sumDigits(Bigint N){
	Bigint res(0, N.base);
	for (auto& n: N.value){
		res = res + n;
	}
	return res;
}
