#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;



int main() {
	/*
		내가 알기로 벡터의 erase를 이용해도, size()는 변해도 capacity()는 불변하는걸로 알고 있다.
		그런데 capacity()는 말그대로 하드웨어적인 메모리확보를 의미하는 것이지. 주솟값과는 무관하다.
		말하고싶은 것은, 1[0] 2[1] 3[2]에서 1[0] 삭제하고 나면 2[0] 3[1] 이 된다는 것이다.
	*/
	vector <int> arr;
	vector <int> arr2;
	arr.push_back(1);
	arr.push_back(2);
	arr.push_back(3);

	for(int i = 0 ; i<arr.size();i++)
	cout << arr[i] << " ";
	cout << endl;
	
	//반복문을 통해서 erase 할 때.
	//틀린 예
	for(int i = 0 ; i<arr.size(); i++){
		arr.erase(arr.begin()+i);
	}

	for (int i = 0; i<arr.size(); i++)
		cout << arr[i] << " ";
	cout << endl;

	arr2.push_back(1);
	arr2.push_back(2);
	arr2.push_back(3);
	//옳은 예
	for (vector<int>::iterator iter = arr2.begin(); iter != arr2.end(); ) {
		if(*iter == 2){
			iter = arr2.erase(iter);
			//삭제하고 다음 위칫값(주솟값) 반환
		}else iter++;
	}

	for (int i = 0; i<arr2.size(); i++)
		cout << arr2[i] << " ";
	cout << endl;

	system("pause");

}