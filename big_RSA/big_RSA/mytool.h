#ifndef MYTOOL_H
#define MYTOOL_H

#include"bigint.h"
#include<cstdlib> //rand
#include<ctime> //time

class BigINTs : public vector<BigINT>{};

BigINT mod_pow(BigINT a, BigINT b, BigINT m){ // x = (a^b) % m
	assert(b.sign == 1);
	cout << "mod_pow";

	int cnt = 0;

	BigINT x;
	x.push_back(1);
	while(b[0] > 0){
		if(cnt%5 == 0) cout << ".";
		if(b[0] & 1) x = (x * a) % m;
		b >>= 1;
		a = (a * a) % m;
		cnt++;
	}
	
	cout << endl;
	return x;
}

BigINT gcd(BigINT a, BigINT b){
	assert(a.sign == 1);
	assert(b.sign == 1);

	if(b.size() == 1 && b[0] == 0) return a;

	return gcd(b, a % b);
}

uint32 rand_32(){

	uint32 r = 0;
	for(int i = 0; i < 4; i++){
		r <<= 8;
		r |= rand()%0x100;
	}

	return r;
}

BigINT rand_512(){
	BigINT r;
	for(int i = 0; i < 16; i++) r.push_back(rand_32());

	return r;
}

bool check_prime(BigINT &p){// 7
	cout << "check_prime" << endl;
	BigINT p2 = p; // 7 - 1 = 6
	p2[0] -= 1; //0 일리가 없음

	int shift = 0; // 1
	while(!(p2[0] & 1)){
		p2 >>= 1;
		shift++;
	}
	// p2는 6 -> 3 // shift == 1
	for(int i = 0; i < 10; i++){
		cout << "check_prime시도_" << i << endl;
		BigINT r; //4 % 7
		BigINT temp; // gcd(7, 4) == 1
		for(int i = 0; i < 100; i++){
			r = rand_512() % p;
			if(r.size() == 1 && r[0] < 2) r[0] += 2;
			temp = gcd(p, r);
			if(temp.size() != 1 || temp[0] != 1) return false;
		}

		BigINT t1; // 1 % 7
		t1.push_back(1);
		BigINT t2 = p - t1; // 6 % 7 == -1 % 7

		temp = mod_pow(r, p2, p); // 4^3 % 7 // 4^6 % 7 == 1 이면 4^3 % 7 == +-1 // 역도 성립

		int sh = shift;
		bool flag = false;
		do{
			if(temp == t1 || temp == t2) flag = true;
			temp = (temp * temp) % p;
		}while(sh-- > 0);
		if(!flag) return false;
	}// (너무적지만)10번 시도했는데도 pseudo prime이면 소수라 본다.

	cout << "Prime !" << endl;
	return true;
}

BigINT gen_prime(){ // 최소 16분 예상
	cout << "gen_prime" << endl;
	BigINT p;
	for(int i = 0; i < 1000; i++){
		cout << endl;
		cout << "gen_prime시도_" << i << endl;
		p = rand_512();
		if(!(p[0] & 1)) p[0] += 1; //짝수면 홀수로 만든다.
		p.show();
		if(check_prime(p)){
			cout << "gen_prime끝" << endl;
			return p;
		}
	}
	cout << "gen_prime실패 " << endl;
	assert(1==2);
}

BigINTs EEA(BigINT a, BigINT b){ //a*s + b*t = r //gcd(a,b) = r
	// if(mode == 0) return s1;
	assert(a > b);
	BigINT r1 = a;
	BigINT r2 = b;
	BigINT s1;
	s1.push_back(1);
	BigINT s2;
	s2.push_back(0);
	BigINT t1 = s2;
	BigINT t2 = s1;

	BigINT q;
	int cnt = 0;
	while(r2.size() > 1 || r2[0] != 0){
		q = r1 / r2;

		BigINT temp;
		BigINT temp2;

		temp = q * r2;
		temp2 = r1 - temp;
		r1 = r2;
		r2 = temp2;

		temp = q * s2;
		temp2 = s1 - temp;
		s1 = s2;
		s2 = temp2;

		temp = q * t2;
		temp2 = t1 - temp;
		t1 = t2;
		t2 = temp2;
	}

	BigINTs z;
	z.push_back(s1);
	z.push_back(t1);
	z.push_back(r1);

	return z;
}

BigINT inverse(BigINT phi, BigINT e){ //a*s + b*t = r
	BigINTs z = EEA(phi, e);
	BigINT d = z[1]; // b가 e 라면 t 는 d
	if(d.sign == -1) d += phi;
	
	return d;
}

#endif