#ifndef BLOCKRSA_H
#define BLOCKRSA_H

#include"mytool.h"

BigINTs build_rsa_system(BigINT p, BigINT q){// 최소 40분 이상 예상
	cout << "build_rsa_system" << endl;
	//BigINT p = gen_prime(); //512비트
	//BigINT q = gen_prime();
	BigINT N = p * q; //1024비트
	p[0] -=1;
	q[0] -=1;
	BigINT PHI = p * q; //1024비트

	BigINT E;
	E.push_back((1<<16) + 1);
	BigINT D = inverse(PHI, E);

	BigINTs z;
	z.push_back(E);
	z.push_back(D);
	z.push_back(N);
	z.push_back(PHI);
	
	cout << "finish building" << endl;
	return z;
}

BigINT block_Enc(BigINT val, BigINT E, BigINT N){
	if(val > N){
		cout << "val is big !" << endl;
		exit(0);
	}
	cout << "encryption" << endl;
	return mod_pow(val, E, N);
}

BigINT block_Dec(BigINT val, BigINT D, BigINT N){
	if(val > N){
		cout << "val is big !" << endl;
		exit(0);
	}
	cout << "decryption" << endl;
	return mod_pow(val, D, N);
}




#endif