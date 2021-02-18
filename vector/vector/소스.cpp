#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int __main(){
	vector<int> v; //������ ���� ������ ���� ����

	v.push_back(1); //���Ϳ� ���� 1 ����
	v.push_back(2);
	v.push_back(3);

	for(int i = 0; i < v.size(); i++){ // ������ ��� ���� ���
		cout << v[i] << " "; }
	cout << endl;

	v[0] = 10; 
	int n = v[2]; // n�� 3 ����
	v.at(2) = 5; // ������ 3���� ���Ҹ� 5�� ����

	for(int i = 0; i < v.size(); i++){
		cout << v[i] << " "; }
	cout << endl;
	
	return 0;
}

int _main(){
	vector<int> v; //������ ���� ������ ���� ����
	v.push_back(1); //���Ϳ� ���� 1 ����
	v.push_back(2);
	v.push_back(3);

	vector<int>::iterator it; // ���� v�� ���ҿ� ���� ������ it ����
	
	for(it = v.begin(); it != v.end(); it++){ //iterator�� �̿��Ͽ� ��� ���� Ž��
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

	cout << "5���� ������ �Է��ϼ��� >> ";
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
