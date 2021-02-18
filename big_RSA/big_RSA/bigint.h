#ifndef BIGINT_H
#define BIGINT_H

#include<vector>
#include<cassert>
using namespace std;

typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;

class BigINT : public vector<uint32>{
protected:
	BigINT mul_Big_and_Small(uint32 sb, int n);
	BigINT abs_add(BigINT &b);
	BigINT abs_sub(BigINT &d);
	int abs_big(BigINT &b);
public:
	int sign;
	BigINT(){ sign = 1; }
	int cnt_bit();

	void cut_zero();
	bool operator>(BigINT &b);
	bool operator<(BigINT &b);
	bool operator==(BigINT &b);
	bool operator!=(BigINT &b);
	bool operator>=(BigINT &b);
	bool operator<=(BigINT &b);
	void operator+=(BigINT &b);
	BigINT operator+(BigINT &b);
	BigINT operator-(BigINT &b);
	BigINT operator*(BigINT &b);
	BigINT operator/(BigINT &b);
	BigINT operator%(BigINT &b);
	void operator>>=(int n);
	void operator<<=(int n);
	void show();
};

void BigINT::cut_zero(){
	BigINT &a = *this;

	while(a.size() > 1){
		iterator it = a.end()-1;
		if(*it == 0) a.erase(it);
		else break;
	}
}

int BigINT::abs_big(BigINT &b){
	BigINT &a = *this;

	if(a.size() > b.size()) return 1;
	else if(a.size() < b.size()) return -1;
	else{
		for(int i = a.size()-1; i >= 0; i--){
			if(a[i] == b[i]) continue;
			else if(a[i] > b[i]){ return 1; }
			else if(a[i] < b[i]){ return -1; }
		}
		return 0; // ���񰪰���
	}
}

bool BigINT::operator>(BigINT &b){
	BigINT &a = *this;
	assert(!(a.empty()) && !b.empty());
	a.cut_zero();
	b.cut_zero();

	if(a.sign > b.sign) return true; // 1 > -1
	else if(a.sign < b.sign) return false; // -1 < 1

	//��ȣ�������
	int abs = a.abs_big(b);
	if(abs == 0) return false;

	abs *= a.sign;//����

	if(abs == 1) return true;
	else return false;
}

bool BigINT::operator==(BigINT &b){
	BigINT &a = *this;
	assert(!(a.empty()) && !b.empty());
	a.cut_zero();
	b.cut_zero();

	if(a.size() != b.size()) return false;
	else if(a.sign != b.sign) return false;
	else{
		for(int i = 0; i < a.size(); i++){
			if(a[i] == b[i]) continue;
			else if(a[i] != b[i]) return false;
		}
		return true;
	}
}

bool BigINT::operator<(BigINT &b){
	BigINT &a = *this;
	assert(!(a.empty()) && !b.empty());
	a.cut_zero();
	b.cut_zero();

	if(a>b || a==b) return false;
	else return true;
}

bool BigINT::operator!=(BigINT &b){
	BigINT &a = *this;
	assert(!(a.empty()) && !b.empty());
	a.cut_zero();
	b.cut_zero();

	if(a == b) return false;
	else return true;
}

bool BigINT::operator>=(BigINT &b){
	BigINT &a = *this;
	assert(!(a.empty()) && !b.empty());
	a.cut_zero();
	b.cut_zero();

	if(a < b) return false;
	else return true;
}

bool BigINT::operator<=(BigINT &b){
	BigINT &a = *this;
	assert(!(a.empty()) && !b.empty());
	a.cut_zero();
	b.cut_zero();

	if(a > b) return false;
	else return true;
}

BigINT BigINT::abs_add(BigINT &b){
	BigINT &a = *this;

	bool big = (a.size() > b.size())? 1 : 0;

	BigINT c = big? a : b; // ū��
	BigINT d = !big? a : b; // ������
	//ū�ſ� ������ ���Ұ���

	int sm_len = d.size();
	int big_len = c.size();

	bool carryup = 0;
	for(int i = 0; i < sm_len; i++){
		uint64 temp = (uint64)c[i] + d[i] + carryup;
		c[i] = temp; //32��Ʈ��ŭ �߸�
		carryup = temp>>32;
	}
	for(int i = sm_len; i < big_len; i++){
		if(!carryup) break;
		uint64 temp = (uint64)c[i] + carryup;
		c[i] = temp; //32��Ʈ��ŭ �߸�
		carryup = temp>>32;
	}
	if(carryup) c.push_back(1); // 10�ڸ�+10�ڸ� = 11�ڸ�  �� ���

	return c;
}

BigINT BigINT::abs_sub(BigINT &d){
	BigINT c = *this; // ū��
	//ū�ſ� ������ ������

	int sm_len = d.size();
	int big_len = c.size();

	int carrydown = 0;
	for(int i = 0; i < sm_len; i++){
		uint64 temp = ((uint64)1<<32) + c[i] - d[i] - carrydown;
		c[i] = temp; //32��Ʈ��ŭ �߸�
		carrydown = !(temp>>32);
	}
	for(int i = sm_len; i < big_len; i++){
		if(!carrydown) break;
		uint64 temp = ((uint64)1<<32) + c[i] - carrydown;
		c[i] = temp; //32��Ʈ��ŭ �߸�
		carrydown = !(temp>>32);
	}

	c.cut_zero();

	return c;
}

void BigINT::operator+=(BigINT &b){
	BigINT &a = *this;
	assert(!(a.empty()) && !(b.empty()));
	a.cut_zero();
	b.cut_zero();

	if(a.sign == b.sign){ //��ȣ�� ���� ���
		a = a.abs_add(b);
	}
	else{//��ȣ�� �ٸ����
		int abs = a.abs_big(b);//���񰪺�

		if(abs == 0){
			a.clear();
			a.sign = 1;
			a.push_back(0);
		}
		else if(abs == 1){
			a = a.abs_sub(b);
		}
		else{// -3 + 9 // 3 + -9
			a = b.abs_sub(a);
			a.sign = b.sign;
		}
	}
}

BigINT BigINT::operator+(BigINT &b){
	BigINT &a = *this;
	assert(!(a.empty()) && !(b.empty()));
	a.cut_zero();
	b.cut_zero();
	BigINT c;

	if(a.sign == b.sign){ //��ȣ�� ���� ���
		c = a.abs_add(b);
		c.sign = a.sign;
	}
	else{//��ȣ�� �ٸ����
		int abs = a.abs_big(b);//���񰪺�

		if(abs == 0){
			c.push_back(0);
		}
		else if(abs == 1){
			c = a.abs_sub(b);
			c.sign = a.sign;
		}
		else{// -3 + 9 // 3 + -9
			c = b.abs_sub(a);
			c.sign = b.sign;
		}
	}

	return c;
}

BigINT BigINT::operator-(BigINT &b){
	BigINT &a = *this;
	assert(!(a.empty()) && !(b.empty()));
	a.cut_zero();
	b.cut_zero();

	BigINT c;

	if(a.sign != b.sign){ // 1 - -1 // -1 - 1
		c = a.abs_add(b);
		c.sign = a.sign;
	}
	else{//��ȣ�� ���� ��� // 1 - 1 // -1 - -1
		int abs = a.abs_big(b);//���񰪺�

		if(abs == 0){
			c.push_back(0);
		}
		else if(abs == 1){
			c = a.abs_sub(b);
			c.sign = a.sign;
		}
		else{// -9 - -12 // 9 - 12
			c = b.abs_sub(a);
			c.sign = -1 * b.sign;
		}
	}

	return c;
}

BigINT BigINT::mul_Big_and_Small(uint32 sb, int n){
	BigINT &a = *this;

	BigINT c;

	uint32 carryup = 0; // 10�������  6*4 = 24 ��  '2' //���⼱ 2^32����
	for(int i = 0; i < a.size(); i++){
		uint64 temp = (uint64)a[i] * sb + carryup;
		carryup = temp>>32; //���������� //6*4 = 24 ��  '2'
		c.push_back(temp); // 6*4 = 24 ��  '4' //�����÷κκ��� �߸�
	}
	if(carryup > 0) c.push_back(carryup); // 25 * 4 �̸� 2�ڸ����� 3�ڸ���

	for(int i = 0; i < n; i++) c.insert(c.begin(), 0); //�ڸ��� ���� //����Ʈ

	c.cut_zero();

	return c;
}

BigINT BigINT::operator*(BigINT &b){
	BigINT a = *this;
	assert(!(a.empty()) && !(b.empty()));
	a.cut_zero();
	b.cut_zero();

	BigINT c;
	c.push_back(0);

	for(int i = 0; i < b.size(); i++){
		BigINT temp = a.mul_Big_and_Small(b[i], i);
		c = c + temp;
	}

	c.sign = a.sign * b.sign;
	if(c.size() == 1 && c[0] == 0) c.sign = 1;

	return c;
}

BigINT BigINT::operator/(BigINT &b){
	BigINT &a = *this;
	assert(!(a.empty()) && !b.empty());
	a.cut_zero(); // 000423 -> 423
	b.cut_zero();
	assert(b.size() > 1 || b[0] != 0); // div by 0

	BigINT dividend = a;
	dividend.sign = 1;
	BigINT divisor = b;
	divisor.sign = 1;
	BigINT q;
	q.push_back(0);
	
	if(divisor > dividend) return q;

	int a_bit = a.cnt_bit(); //��Ʈ�� ��� // 8�̸� 1000�̹Ƿ� 4
	int b_bit = b.cnt_bit();
	int amt_shift = a_bit - b_bit; //��Ʈ�� ����

	divisor <<= amt_shift; //������ a�� ��Ʈ�� ����

	for(int i = amt_shift; i >= 0; i--){ // �˰���
		divisor.sign = -1 * dividend.sign;
		dividend += divisor;
		q <<= 1;
		if(dividend.sign == 1) q[0] += 1;
		divisor >>= 1;
	}

	q.sign = a.sign * b.sign;
	return q;
}

int BigINT::cnt_bit(){
	BigINT a = *this;

	int tot = (a.size()-1) * 32;

	uint32 last = a[a.size()-1];
	while(last > 0){
		tot++;
		last >>= 1;
	}

	return tot;
}

void BigINT::operator<<=(int n){
	BigINT &a = *this;
	for(int i = 0; i < n/32; i++) a.insert(a.begin(), 0);

	int m = n%32;
	if(m){
		uint32 carryup_send = 0;
		uint32 carryup_recv = 0;
		for(int i = 0; i < a.size(); i++){
			carryup_send = a[i] >> (32 - m);
			a[i] <<= m;
			a[i] |= (uint32)carryup_recv;
			carryup_recv = carryup_send;
		}
		if(carryup_recv) a.push_back(carryup_recv);
	}
}

void BigINT::operator>>=(int n){
	BigINT &a = *this;
	for(int i = 0; i < n/32; i++) a.erase(a.begin());

	int m = n%32;
	if(m){
		uint32 carrydown_send = 0;
		uint32 carrydown_recv = 0;
		for(int i = a.size()-1; i >= 0; i--){
			carrydown_send = a[i] << (32 - m);
			a[i] >>= m;
			a[i] |= (uint32)carrydown_recv;
			carrydown_recv = carrydown_send;
		}
	}

	a.cut_zero();
}

BigINT BigINT::operator%(BigINT &b){
	BigINT &a = *this;
	assert(!(a.empty()) && !b.empty());
	a.cut_zero(); // 000423 -> 423
	b.cut_zero();
	assert(b.size() > 1 || b[0] != 0); // div by 0
	assert(b.sign == 1);

	BigINT r = a; //���������� ������
	r.sign = 1;
	BigINT divisor = b;

	int a_bit = a.cnt_bit(); //��Ʈ�� ��� // 8�̸� 1000�̹Ƿ� 4
	int b_bit = b.cnt_bit();
	int amt_shift = a_bit - b_bit; //��Ʈ�� ����

	divisor <<= amt_shift; //������ a�� ��Ʈ�� ���� // 0.1s

	for(int i = amt_shift; i >= 0; i--){ // �˰���
		divisor.sign = -1 * r.sign;
		r += divisor; 
		divisor >>= 1; 
	}
	r.sign *= a.sign;

	if(r.sign == -1) r += b; //�������� �����ΰ�� ����� ������� // b�� ����� �����

	return r;
}

void BigINT::show(){
	BigINT &a = *this;

	cout << "sign : " << a.sign << endl;
	cout << "size() : " << a.size() << endl;
	for(int i = a.size()-1; i >= 0; i--){
		cout << a[i] << " ";
	}
	cout << endl;
	cout << endl;
}

#endif