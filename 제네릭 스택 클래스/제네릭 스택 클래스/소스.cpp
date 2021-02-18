#include<iostream>
#include<string>
using namespace std;

template <class T>
class MyStack{
	int tos; //top of stack
	T data[100]; // T 타입의 배열 , 스택의 크기는 100
public:
	MyStack();
	void push(T element); // element를 data [] 배열에 삽입
	T pop(); // 스택의 탑에 있는 데이터를 data[] 배열에서 리턴
};

template <class T>
MyStack<T>::MyStack(){ //생성자
	tos = -1; // 스택은 비어있음
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
		return 0; // 오류표시
	}
	retData = data[tos--];
	return retData;
}

//int main(){
//	MyStack<int> iStack; // int 만 저장하는 스택
//	iStack.push(3);
//	cout << iStack.pop() << endl;
//
//	MyStack<double> dStack;
//	dStack.push(3.5);
//	cout << dStack.pop() << endl;
//
//	MyStack<char> *p = new MyStack<char>(); // char만 저장하는 스택
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
	pointStack.push(a); // 복사되어 저장
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

