#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
using namespace std;


int main() {
	int arr[50] = { 0, };
	int a = 3;
	vector <int> av(0,0);
	av.push_back(1);
	av.push_back(2);
	av.push_back(3);
	av.push_back(4);
	cout << arr[a] << endl;
	vector <int> ::iterator avi = av.begin();

	for (; avi != av.end(); avi++) {
		cout << *avi << endl;
	}
	cout << av[a] << endl;
	system("pause");

}