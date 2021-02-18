#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int __main(){
	vector<int> v; //정수만 삽입 가능한 벡터 생성

	v.push_back(1); //벡터에 정수 1 삽입
	v.push_back(2);
	v.push_back(3);

	for(int i = 0; i < v.size(); i++){ // 벡터의 모든 원소 출력
		cout << v[i] << " "; }
	cout << endl;

	v[0] = 10; 
	int n = v[2]; // n에 3 저장
	v.at(2) = 5; // 벡터의 3번재 원소를 5로 변경

	for(int i = 0; i < v.size(); i++){
		cout << v[i] << " "; }
	cout << endl;
	
	return 0;
}

int _main(){
	vector<int> v; //정수만 삽입 가능한 벡터 생성
	v.push_back(1); //벡터에 정수 1 삽입
	v.push_back(2);
	v.push_back(3);

	vector<int>::iterator it; // 벡터 v의 원소에 대한 포인터 it 선언
	
	for(it = v.begin(); it != v.end(); it++){ //iterator를 이용하여 모든 원소 탐색
		int n = *it;
		n = n*2;
		*it = n;
	}

	for(it = v.begin(); it != v.end(); it++){
		cout << *it << ' ';
	}
	cout << endl;

	return 0;
}

int main(){
	vector<int> v;

	cout << "5개의 정수를 입력하세요 >> ";
	for(int i = 0; i < 5; i++){
		int n;
		cin >> n;
		v.push_back(n);
	}

	sort(v.begin(), v.end());
	
	vector<int>::iterator it;
	for(it = v.begin(); it != v.end(); it++){
		cout << *it << ' ';
	}
	cout << endl;

	return 0;
}
