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
	vector <int> arr2;
	arr.push_back(1);
	arr.push_back(2);
	arr.push_back(3);

	for(int i = 0 ; i<arr.size();i++)
	cout << arr[i] << " ";
	cout << endl;
	
	//�ݺ����� ���ؼ� erase �� ��.
	//Ʋ�� ��
	for(int i = 0 ; i<arr.size(); i++){
		arr.erase(arr.begin()+i);
	}

	for (int i = 0; i<arr.size(); i++)
		cout << arr[i] << " ";
	cout << endl;

	arr2.push_back(1);
	arr2.push_back(2);
	arr2.push_back(3);
	//���� ��
	for (vector<int>::iterator iter = arr2.begin(); iter != arr2.end(); ) {
		if(*iter == 2){
			iter = arr2.erase(iter);
			//�����ϰ� ���� ��ĩ��(�ּڰ�) ��ȯ
		}else iter++;
	}

	for (int i = 0; i<arr2.size(); i++)
		cout << arr2[i] << " ";
	cout << endl;

	system("pause");

}