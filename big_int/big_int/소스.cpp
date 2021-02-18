#include<iostream>
#include<vector>
#include<cassert>
using namespace std;

typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;

class BigINT : public vector<uint32>{
protected:
	BigINT mul_Big_and_Small(uint32 sb, int n);
	BigINT abs_add(BigINT b);
	BigINT abs_sub(BigINT b);
	int cnt_bit();
	BigINT bit_to_BigINT(vector<bool> quo);
public:
	int sign;
	BigINT(){ sign = 1; }
	//BigINT(BigINT &x) : vector<uint32>(x){ this->sign = x.sign; }

	void cut_zero();
	bool operator>(BigINT b);
	bool operator<(BigINT b);
	bool operator==(BigINT b);
	bool operator!=(BigINT b);
	bool operator>=(BigINT b);
	bool operator<=(BigINT b);
	BigINT operator+(BigINT b);
	BigINT operator-(BigINT b);
	BigINT operator*(BigINT b);
	BigINT operator/(BigINT b);
	BigINT operator%(BigINT b);
	void operator>>=(int n);
	void operator<<=(int n);
};

void BigINT::cut_zero(){
	BigINT &a = *this;

	while(a.size() > 1){
		iterator it = a.end()-1;
		if(*it == 0) a.erase(it);
		else break;
	}
}

bool BigINT::operator>(BigINT b){
	BigINT a = *this;
	assert(!(a.empty()) && !b.empty());
	a.cut_zero();
	b.cut_zero();

	if(a.sign > b.sign) return true; // 1 > -1
	else if(a.sign < b.sign) return false; // -1 < 1

	bool abs;

	if(a.size() > b.size()) abs = true;
	else if(a.size() < b.size()) abs = false;
	else{
		bool flag = 1;
		for(int i = a.size()-1; i >= 0; i--){
			if(a[i] == b[i]) continue;
			else if(a[i] > b[i]){ abs = true; flag = 0; break; }
			else if(a[i] < b[i]){ abs = false; break; }
		}
		if(flag) abs = false;
	}

	if(a.sign == 1) return abs;
	else return !abs;
}

bool BigINT::operator==(BigINT b){
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

bool BigINT::operator<(BigINT b){
	BigINT &a = *this;
	assert(!(a.empty()) && !b.empty());
	a.cut_zero();
	b.cut_zero();

	if(a>b || a==b) return false;
	else return true;
}

bool BigINT::operator!=(BigINT b){
	BigINT &a = *this;
	assert(!(a.empty()) && !b.empty());
	a.cut_zero();
	b.cut_zero();

	if(a == b) return false;
	else return true;
}

bool BigINT::operator>=(BigINT b){
	BigINT &a = *this;
	assert(!(a.empty()) && !b.empty());
	a.cut_zero();
	b.cut_zero();

	if(a < b) return false;
	else return true;
}

bool BigINT::operator<=(BigINT b){
	BigINT &a = *this;
	assert(!(a.empty()) && !b.empty());
	a.cut_zero();
	b.cut_zero();

	if(a > b) return false;
	else return true;
}

BigINT BigINT::abs_add(BigINT b){
	BigINT a = *this;
	assert(!(a.empty()) && !b.empty());
	a.cut_zero();
	b.cut_zero();

	int len = (a.size() > b.size())? a.size() : b.size();

	BigINT c;

	int carryup = 0;
	for(int i = 0; i < len; i++){
		uint64 A = (i+1 <= a.size())? a[i] : 0; // �ڱ⺸�� ���� �ڸ����ϰ�� 0���� // 00435
		uint64 B = (i+1 <= b.size())? b[i] : 0;

		uint64 temp = A + B + carryup;
		if(temp > UINT32_MAX){ // carry�߻��ΰ� // 10������� ���ڸ���10�̻��ΰ�
			carryup = 1;
			c.push_back(temp - UINT32_MAX - 1); // 2^32 - (2^32-1) -1 = 0 // uint64 -> uint32
		}
		else{
			carryup = 0;
			c.push_back(temp);
		}
	}
	if(carryup == 1) c.push_back(1); // 10�ڸ�+10�ڸ� = 11�ڸ�  �� ���

	c.cut_zero();
	
	return c;
}

BigINT BigINT::abs_sub(BigINT b){
	BigINT a = *this;
	assert(!(a.empty()) && !b.empty());
	a.cut_zero();
	b.cut_zero();

	BigINT c;

	int carrydown = 0;
	for(int i = 0; i < a.size(); i++){
		uint64 A = (i+1 <= a.size())? a[i] : 0; // �ڱ⺸�� ���� �ڸ����ϰ�� 0���� // 00435
		uint64 B = (i+1 <= b.size())? b[i] : 0;

		uint64 temp = ((uint64)UINT32_MAX+1 + A) - B - carrydown; // ���ڸ����� �ϴ� ���� ������
		if(temp <= UINT32_MAX){ // carry�߻��ΰ� // 10������� 0~9�ΰ�
			carrydown = 1; // 
			c.push_back(temp); // uint64 -> uint32
		}
		else{
			carrydown = 0;
			c.push_back(temp - ((uint64)UINT32_MAX+1));
		}
	}
	for(int i = c.size()-1; i >= 1; i--){ // 000423 -> 423
		if(c[i] == 0) c.erase(c.end()-1);
		else break;
	}

	c.cut_zero();

	return c;
}

BigINT BigINT::operator+(BigINT b){
	BigINT a = *this;
	a.cut_zero();
	b.cut_zero();
	BigINT c;

	if(a.sign == b.sign){
		c = a.abs_add(b);
		c.sign = a.sign;
	}
	else{
		int a_sign = a.sign; int b_sign = b.sign;
		a.sign = 1; b.sign = 1;

		if(a == b) c.push_back(0);
		else if(a > b){
			c = a.abs_sub(b);
			c.sign = a_sign;
		}
		else{
			c = b.abs_sub(a);
			c.sign = b_sign;
		}
	}

	c.cut_zero();

	return c;
}

BigINT BigINT::operator-(BigINT b){
	BigINT a = *this;
	a.cut_zero();
	b.cut_zero();

	BigINT c;

	if(a.sign != b.sign){ // 1 - -1 // -1 - 1
		int a_sign = a.sign;
		a.sign = 1; b.sign = 1;
		c = a.abs_add(b);
		c.sign = a_sign;
	}
	else{
		int a_sign = a.sign; int b_sign = b.sign;
		a.sign = 1; b.sign = 1;

		if(a == b) c.push_back(0);
		else if(a > b){ // -2 - -1 // 2 - 1
			c = a.abs_sub(b);
			c.sign = a_sign;
		}
		else{ // -9 - -12 // 9 - 12
			c = b.abs_sub(a);
			c.sign = -1*b_sign;
		}
	}

	c.cut_zero();

	return c;
}

BigINT BigINT::mul_Big_and_Small(uint32 sb, int n){
	BigINT a = *this;
	a.cut_zero();

	BigINT c;

	uint32 carryup = 0; // 10�������  6*4 = 24 ��  '2' //���⼱ 2^32����
	for(int i = 0; i < a.size(); i++){
		uint64 temp = (uint64)a[i] * sb + carryup;
		carryup = temp/((uint64)UINT32_MAX+1); //���������� //6*4 = 24 ��  '2'
		c.push_back(temp%((uint64)UINT32_MAX+1)); // 6*4 = 24 ��  '4'
	}
	if(carryup > 0) c.push_back(carryup); // 25 * 4 �̸� 2�ڸ����� 3�ڸ���

	for(int i = 0; i < n; i++) c.insert(c.begin(), 0); //�ڸ��� ���� //����Ʈ

	c.cut_zero();

	return c;
}

BigINT BigINT::operator*(BigINT b){
	BigINT a = *this;
	assert(!(a.empty()) && !b.empty());
	a.cut_zero();
	b.cut_zero();

	BigINT c;
	c.push_back(0);

	for(int i = 0; i < b.size(); i++){
		c = c + a.mul_Big_and_Small(b[i], i);
	}

	c.sign = a.sign * b.sign;
	if(c.size() == 1 && c[0] == 0) c.sign = 1;

	c.cut_zero();

	return c;
}

BigINT BigINT::operator/(BigINT b){
	BigINT a = *this;
	assert(!(a.empty()) && !b.empty());
	a.cut_zero(); // 000423 -> 423
	b.cut_zero();
	assert(b.size() > 1 || b[0] != 0); // div by 0

	int a_sign = a.sign; int b_sign = b.sign;
	a.sign = 1; b.sign = 1;

	BigINT c;

	if(a < b){
		c.push_back(0);
		return c;
	}


	int a_bit = a.cnt_bit(); //��Ʈ�� ��� // 8�̸� 1000�̹Ƿ� 4
	int b_bit = b.cnt_bit();
	int amt_shift = a_bit - b_bit; //��Ʈ�� ����

	vector<bool> quo_bit; // ���� �Ѻ�Ʈ�� ��
	for(int i = 0; i < amt_shift; i++) b <<= 1; //������ a�� ��Ʈ�� ����

	for(int i = amt_shift; i >= 0; i--){ // �˰���
		b.sign = -1 * a.sign;
		a = a + b;
		if(a.sign == 1) quo_bit.push_back(1);
		else quo_bit.push_back(0);
		b >>= 1;
	}

	c = bit_to_BigINT(quo_bit); // bit -> BigINT

	c.sign = a_sign * b_sign;
	c.cut_zero();
	return c;
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

	for(int j = 0; j < n; j++){
		bool carryup_send = 0;
		bool carryup_recv = 0;
		for(int i = 0; i < a.size(); i++){
			carryup_send = (uint32)1<<31 & a[i];
			a[i] <<= 1;
			a[i] |= carryup_recv;
			carryup_recv = carryup_send;
		}
		if(carryup_recv) a.push_back(1);
	}
}

void BigINT::operator>>=(int n){
	BigINT &a = *this;

	for(int j = 0; j < n; j++){
		bool carrydown_send = 0;
		bool carrydown_recv = 0;
		for(int i = a.size()-1; i >= 0; i--){
			carrydown_send = 1 & a[i];
			a[i] >>= 1;
			a[i] |= (uint32)carrydown_recv << 31;
			carrydown_recv = carrydown_send;
		}
	}

	a.cut_zero();
}

BigINT BigINT::bit_to_BigINT(vector<bool> quo){
	BigINT q;
	q.push_back(0);
	for(int i = 0; i < quo.size(); i++){
		q <<= 1;
		q[0] |= quo[i];
	}

	return q;
}

BigINT BigINT::operator%(BigINT b){
	BigINT a = *this;
	assert(!(a.empty()) && !b.empty());
	a.cut_zero(); // 000423 -> 423
	b.cut_zero();
	assert(b.size() > 1 || b[0] != 0); // div by 0
	assert(b.sign == 1);

	int a_sign = a.sign;
	a.sign = 1;

	BigINT r = a;
	BigINT divisor = b;

	int a_bit = a.cnt_bit(); //��Ʈ�� ��� // 8�̸� 1000�̹Ƿ� 4
	int b_bit = b.cnt_bit();
	int amt_shift = a_bit - b_bit; //��Ʈ�� ����
	
	for(int i = 0; i < amt_shift; i++) divisor <<= 1; //������ a�� ��Ʈ�� ����

	for(int i = amt_shift; i >= 0; i--){ // �˰���
		divisor.sign = -1 * a.sign;
		a = a + divisor; 
		divisor >>= 1; 

		if(a.sign == 1) r = a; //�������� ����ΰ�츸 ����
	}

	r.sign = a_sign;
	if(r.sign == -1) r = r + b; //�������� �����ΰ�� ����� �������

	r.cut_zero();
	return r;
}

int main(){
	BigINT a;
	a.push_back(0);
	a.push_back(2);
	a.push_back(UINT32_MAX);
	a.push_back(2);
	a.push_back(1);
	a.sign = -1;

	uint64 bb = (uint64)UINT32_MAX + 1;
	bb /= 2;

	BigINT b;
	b.push_back(9);
	b.push_back(UINT32_MAX);
	b.push_back(9);
	//b.push_back(bb);
	b.sign = 1;

	BigINT c;
	//BigINT d = *(new BigINT(a));

	c = a % b;
	//c = c / b;

	cout << "c.sign : " << c.sign << endl;
	cout << "c.size() : " << c.size() << endl;
	for(int i = c.size()-1; i >= 0; i--){
		cout << c[i] << " ";
	}
	cout << endl;
	//cout << *(c.end()-1) << endl;

	return 0;
}