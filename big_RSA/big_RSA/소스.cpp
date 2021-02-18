#include<iostream>
#include"blockrsa.h"
using namespace std;

int main(){
	srand(time(0));
	clock_t start, end;

	BigINT p;
	p.push_back(4059233385);
	p.push_back(1988500166);
	p.push_back(2037306500);
	p.push_back(3128398335);
	p.push_back(2012815195);
	p.push_back(2422601661);
	p.push_back(3911107514);
	p.push_back(277486864);
	p.push_back(543726228);
	p.push_back(3848537964);
	p.push_back(1089008254);
	p.push_back(3442896168);
	p.push_back(3300134450);
	p.push_back(495335937);
	p.push_back(4167213837);
	p.push_back(1000345749);

	BigINT q;
	q.push_back(3329779009);
	q.push_back(3126702262);
	q.push_back(2439520244);
	q.push_back(1932575325);
	q.push_back(2236780190);
	q.push_back(252290788);
	q.push_back(3758086475);
	q.push_back(3898829721);
	q.push_back(792467500);
	q.push_back(3908916785);
	q.push_back(3680099095);
	q.push_back(223895363);
	q.push_back(2645271302);
	q.push_back(3963466444);
	q.push_back(681622);
	q.push_back(724840362);

	start = clock();
	BigINTs rsa = build_rsa_system(p, q);
	end = clock();
	cout << "time : " << end-start << endl;
	cout << endl;

	BigINT E = rsa[0];
	BigINT D = rsa[1];
	BigINT N = rsa[2];
	BigINT PHI = rsa[3];


	cout << endl;
	BigINT val = rand_512();
	cout << "평문" << endl;
	val.show();

	start = clock();
	val = block_Enc(val, E, N);
	end = clock();
	cout << "time : " << end-start << endl;
	cout << "암호문" << endl;
	val.show();

	start = clock();
	val = block_Dec(val, D, N);
	end = clock();
	cout << "time : " << end-start << endl;
	cout << "복호문" << endl;
	val.show();

	return 0;
}