#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
#include <functional>
using namespace std;
int result = 0;

int maxx(int a, int b) {
	return a > b ? a : b;
}


int main() {
	int day;
	cin >> day;
	int arr[17] = { 0, };
	int TP[17][2] = { 0 ,};
	for (int i = 1; i <= day; i++) { // �ǹ��� : �ش� ���ڴ� �׳� �Ѿ�� ���̽�[�ް��� �Ѿ ���� �׺��� ���ް��� �Ѿ ���� ���ʷ� �Ѿ ���]��, ������ ���� �ϴ� ���̽��� ��� �� �ڷᱸ������ ǥ���ϴ°�?
		cin >> TP[i][0] >> TP[i][1];
		if (i + TP[i][0] <= day+1) { // i�Ͽ� ������ ���� �ϴ� ���.
			arr[i + TP[i][0]] = maxx(arr[i + TP[i][0]], arr[i]+TP[i][1]);
			result = maxx(result, arr[i + TP[i][0]]);
		}
		//i�Ͽ� ������ ���� ���ϰ�,  �׳� �Ѿ�� ���̽�.
		arr[i + 1] = maxx(arr[i], arr[i + 1]);
		result = maxx(result, arr[i + 1]);
 	}

	cout << result;
}