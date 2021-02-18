#include<iostream>
#include<string>
using namespace std;

template <class T>
class MyStack{
	int tos; //top of stack
	T data[100]; // T Ÿ���� �迭 , ������ ũ��� 100
public:
	MyStack();
	void push(T element); // element�� data [] �迭�� ����
	T pop(); // ������ ž�� �ִ� �����͸� data[] �迭���� ����
};

template <class T>
MyStack<T>::MyStack(){ //������
	tos = -1; // ������ �������
}

template <class T>
void MyStack<T>::push(T element){
	if(tos == 99){
		cout << "stack full";
		return ;
	}
	tos++;
	data[tos] = element;
}

template <class T>
T MyStack<T>::pop(){
	T retData;
	if(tos == -1){
		cout << "stack empty";
		return 0; // ����ǥ��
	}
	retData = data[tos--];
	return retData;
}

//int main(){
//	MyStack<int> iStack; // int �� �����ϴ� ����
//	iStack.push(3);
//	cout << iStack.pop() << endl;
//
//	MyStack<double> dStack;
//	dStack.push(3.5);
//	cout << dStack.pop() << endl;
//
//	MyStack<char> *p = new MyStack<char>(); // char�� �����ϴ� ����
//	p->push('a');
//	cout << p->pop() << endl;
//	delete p;
//}

class Point{
	int x, y;
public:
	Point(int x=0, int y=0){ this->x = x; this->y = y; }
	void show(){ cout << '(' << x << ',' << y << ')' << endl; }
};

int main(){
	MyStack<Point> pointStack;
	Point a(2,3), b;
	pointStack.push(a); // ����Ǿ� ����
	b = pointStack.pop();
	b.show();

	MyStack<Point*> pStack;
	pStack.push(new Point(10,20));
	Point* pPoint = pStack.pop();
	pPoint->show();

	MyStack<string> stringStack;
	string s = "C++";
	stringStack.push(s);
	stringStack.push("java");
	cout << stringStack.pop() << ' ';
	cout << stringStack.pop() << endl;
	cout << stringStack.pop() << endl;
}

