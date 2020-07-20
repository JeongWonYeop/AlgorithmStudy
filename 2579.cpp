#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
#include <functional>
#include <string.h> 
using namespace std;
int N;


int maxx(int a, int b) {
	return a > b ? a : b;
}


int main() {

	cin >> N;
	int floor[301] = { 0, };
	int d[301] = { 0, }; //���
	int d2[301] = { 0, };
	d[0] = 0; //�ʱ�ȭ. d[i] : i��ܱ��� �ö�� ��� ������ ����.
	/*
		����� ��ĭ������ ���̽� -> �����ؼ� ��ĭ������ ���̽��� ����.,�ö󵵵ǰ�,����ǰ�, ��ſ� �����ÿ� ǥ��.
		����� ��ĭ������ ���̽�

		XOXOOX
		XOOXOX
		OXOOX
		OOXOX
		X�� �������� �ؼ�.

	*/
	for (int i = 1; i <= N; i++) {
		cin >> floor[i];
	}

	for (int i = 0; i <= N - 1; i++) {
		if ((i + 1) == 1) {
			d[i + 1] = floor[i + 1];
		}
		d[i + 1] = maxx(d[i] + floor[i + 1], d[i + 1]);//XO
		d[i + 1] = maxx(floor[i] + d[i + 1], d[i + 1]);//OX
	}


	for (int i = 0; i <= N-1; i++) {
		if ((i + 1) == 1) {
			d2[i + 1] = 0;
		}
		d2[i + 1] = maxx(d2[i] + floor[i + 1], d2[i + 1]);//XO
		d2[i + 1] = maxx(floor[i] + d2[i + 1], d2[i + 1]);//OX
	}


	cout << maxx(d[N], d2[N]) << endl;
	system("pause");
}