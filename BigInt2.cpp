#include "BigInt2.hpp"


vector<unsigned long> toVec(string n, unsigned int nDigits){

	vector<unsigned long> res;

    unsigned int i = n.size();
	while (i>0){
        unsigned long cur_num = 0;
        unsigned int j = 0;
        unsigned long factor = 1;
        while ((i>0) && (j<nDigits)) {
            cur_num += (n[i-1] - '0') * factor;
            i -= 1;
            j += 1;
            factor *= 10;
        }
        res.push_back(cur_num);
	}

	return res;
}


vector<unsigned long> toVec(unsigned long n, unsigned long base){
    vector<unsigned long> res;
    while(n > 0) {
        res.push_back(n % base);
        n /= base;
    }
	return res;
}


Bigint::Bigint(unsigned long n, unsigned int nDigits): nDigits(nDigits){
    base = 1;
    for (int i=0; i<nDigits; i++) {
        base *= 10;
    }
	value = toVec(n, base);
}


Bigint::Bigint(string n, unsigned int nDigits): nDigits(nDigits){
    base = 1;
    for (int i=0; i<nDigits; i++) {
        base *= 10;
    }
	value = toVec(n, nDigits);
}


Bigint::Bigint(vector<unsigned long> n, unsigned int nDigits): nDigits(nDigits){
    base = 1;
    for (int i=0; i<nDigits; i++) {
        base *= 10;
    }
	value = n;
}
		

void Bigint::times10(){
	value.insert(value.begin(),0);
}


void Bigint::times10(unsigned int n){
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


void Bigint::next() {
    if (value.size() == 0) {
        value.push_back(1);
        return;
    }
    bool ret = true;
    int i = 0;
    while (ret && (i < value.size())) {
        long next_val = value[i] + 1;
        if (next_val == base) {
            value[i] = 0;
        } else {
            value[i] = next_val;
            ret = 0;
        }
        i += 1;
    }
}


void Bigint::previous() {
    if (value.size() == 0) {
        return;
    }
    bool ret = true;
    int i = 0;
    while (ret && (i < value.size())) {
        if (value[i] == 0) {
            value[i] = base-1;
        } else {
            value[i] -= 1;
            ret = false;
            if (value[i] == 0) {
                value.pop_back();
            }
        }
        i += 1;
    }
}


string Bigint::toString() {
	string res = "";
	for(unsigned int i = value.size(); i>0; i--){
        if (i < value.size()) {
            long value10 = value[i-1];
            if (value10 == 0) {
                value10 = 1;
            }
            value10 *= 10;
            while(value10 < base) {
                res += "0";
                value10 *= 10;
            }
        }
        res += to_string(value[i-1]);
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


bool operator<(Bigint n1, Bigint n2){
	return n2 > n1;
}


bool operator>=(Bigint n1, Bigint n2){
	return !(n1 < n2);
}


bool operator<=(Bigint n1, Bigint n2){
	return !(n1 > n2);
}


ostream& operator<<(ostream& out, Bigint n){
	if(n.value.size()==0){
		out << '0';
	}
	else{
        out << n.toString();
	}
    return out;
}


Bigint operator+(Bigint n1, Bigint n2){
	Bigint res(0, n1.nDigits);
	long retenue = 0;
	long sumDigits = 0;
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


void operator+=(Bigint &n1, Bigint n2){
	long retenue = 0;
	long sumDigits = 0;
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
		    n1.value[i] = sumDigits;
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
		    n1.value[i] = sumDigits;
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
		    n1.value.push_back(sumDigits);
		}
	}
	if(retenue==1){
		n1.value.push_back(1);
	}
}


Bigint operator-(Bigint n1, Bigint n2){
	if (n2 > n1) {
		cout << "Can't subtract a Bigint from a smaller Bigint" << endl;
		return Bigint(0, n1.nDigits);
	}
	Bigint res(0, n1.nDigits);
	long retenue = 0;
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


void operator-=(Bigint &n1, Bigint n2){
	if (n2 > n1) {
		cout << "Can't subtract a Bigint from a smaller Bigint" << endl;
	}
	long retenue = 0;
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
		n1.value[i] = difDigits;
	}
    n1.remLeadZeros();
}


Bigint operator+(Bigint N, unsigned long n){
	Bigint res = N + Bigint(n, N.nDigits);
	return res;
}


void operator+=(Bigint &N, unsigned long n){
	N += Bigint(n, N.nDigits);
}


Bigint operator+(unsigned long n, Bigint N){
	return N + Bigint(n, N.nDigits);
}


Bigint operator*(unsigned long n, Bigint BN){
	Bigint res(0, BN.nDigits);
    while (n>0) {
        if (n%2) {
            res += BN;
        }
        BN += BN;
        n /= 2; 
    }
	res.remLeadZeros();
	return res;
}


Bigint operator*(Bigint BN, unsigned long n){
	Bigint res(0, BN.nDigits);
    while (n>0) {
        if (n%2) {
            res += BN;
        }
        BN += BN;
        n /= 2; 
    }
	res.remLeadZeros();
	return res;
}


Bigint operator*(Bigint n1, Bigint n2){
	Bigint res(0, n1.nDigits);
	Bigint n1Pow10 = n1;
	for(int i=0; i<n2.value.size(); i++){
		res = res + n2.value[i]*n1Pow10;
		n1Pow10.times10();
	}
	res.remLeadZeros();
	return res;
}


Bigint factorial(Bigint n){
	Bigint res(1, n.nDigits);
    Bigint one(1, n.nDigits);
	while(n > one){
		res = n*res;
		n.previous();
	}
	return res;
}


Bigint pow(Bigint N, unsigned int n){
	Bigint res(1, N.nDigits);
	for(int i=0; i<n; i++){
		res = N*res;
	}
	return res;
}

Bigint operator/(Bigint n1, Bigint n2){
	try{
		Bigint res(0, n1.nDigits);
		if(!(n2>Bigint(0, n1.nDigits))){
			throw 0;
		}
		unsigned long s1 = n1.value.size();
		unsigned long s2 = n2.value.size();
		if(s1 > s2 + 1){
			Bigint n2_ = n2;
			n2_.times10(s1-s2-1);
			res = n1/n2_;
			res.times10(s1-s2-1);
			res += (n1 - n2*res)/n2;
			return res;
		}
        long pow2 = 0;
        vector<Bigint> n2pow2 {n2};
        while (n1 >= n2) {
            n2pow2.push_back(n2);
            pow2 += 1;
            n2 += n2;
        }
        for (long i=0; i<=pow2; i++) {
            res += res;
            if (n1 >= n2) {
                res.next();
                n1 -= n2;
            }
            n2 = n2pow2.back();
            n2pow2.pop_back();
        }
		return res;
	}
	catch(int e){
		cout << "I can't divide by zero :(" << endl;
		return Bigint(0, n1.nDigits);
	}
}


Bigint operator%(Bigint n1, Bigint n2){
	try{
		Bigint i(0, n1.nDigits);
		if(n2==i){
			throw 0;
		}
		Bigint res = n1-(n1/n2)*n2;
		res.remLeadZeros();
		return res;
	}
	catch(int e){
		cout << "I can't divide by zero :(" << endl;
		return Bigint(0, n1.nDigits);
	}
}


bool isPrime(Bigint n){
	if((n.value.size() == 0) || ((n.value.size()==1) && (n.value[0] < 2))){
		return false;
	}
	Bigint k(2, n.nDigits);
	Bigint Zero(0, n.nDigits);
    unsigned int m = 1;
	while(k*k <= n){
		if(n%k == Zero){
			return false;
		}
		k = k+m;
        if (m == 1) 
            m = 2;
	}
	return true;
}


Bigint nextPrime(Bigint n){
	n.next();
	while(!isPrime(n)){
		n.next();
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
	vector<Bigint> primesSquared = {Bigint(4),Bigint(9)};
	Bigint x(3);
	Bigint zero(0);
	for (int i=2; i<n; i++) {
		bool isNotPrime = true; 
		while (isNotPrime) {
			x += 2;
			isNotPrime = false;
			for (int j=0; j<i; j++) {
				if (primesSquared[j] > x) {
					break;
				}
				if (x % primes[j] == zero) {
					isNotPrime = true;
					break;
				}
			}
		}
		primes.push_back(x);
		primesSquared.push_back(x*x);
	}
	return primes;
}


Bigint sumDigits(Bigint N){
	Bigint res(0, N.nDigits);
	for (auto& n: N.value){
		res = res + n;
	}
	return res;
}


Bigint randomBigint(Bigint N, mt19937 &rng) {
    uniform_int_distribution<unsigned long> dist(0, N.base-1);
    uniform_int_distribution<unsigned long> dist_l(0, N.value[N.value.size()-1]);
    vector<unsigned long> vec_numbers;
    const unsigned int n_numbers = N.value.size();
    for (int i=0; i<n_numbers-1; i++) {
        vec_numbers.push_back(dist(rng));
    }
    vec_numbers.push_back(dist_l(rng));
    Bigint res(vec_numbers, N.nDigits);
    while (res >= N) {
        for (int i=0; i<n_numbers-1; i++) {
            res.value[i] = dist(rng);
        }
        res.value[n_numbers-1] = dist_l(rng);
    }
    res.remLeadZeros();
    return res;
}
