#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;



int main() {
	/*
		���� �˱�� ������ erase�� �̿��ص�, size()�� ���ص� capacity()�� �Һ��ϴ°ɷ� �˰� �ִ�.
		�׷��� capacity()�� ���״�� �ϵ�������� �޸�Ȯ���� �ǹ��ϴ� ������. �ּڰ����� �����ϴ�.
		���ϰ���� ����, 1[0] 2[1] 3[2]���� 1[0] �����ϰ� ���� 2[0] 3[1] �� �ȴٴ� ���̴�.
	*/
	vector <int> arr;
	arr.push_back(1);
	arr.push_back(2);
	arr.push_back(3);
	for(int i = 0 ; i<arr.size();i++)
	cout << arr[i] << " ";
	cout << endl;

	arr.erase(arr.begin());
	arr.erase(arr.begin()+1);

	for (int i = 0; i<arr.size(); i++)
		cout << arr[i] << " ";
	cout << endl;
	system("pause");

}