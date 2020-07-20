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
	int d[301] = { 0, }; //결과
	int d2[301] = { 0, };
	d[0] = 0; //초기화. d[i] : i계단까지 올라온 계단 합으로 정의.
	/*
		계단을 한칸오르는 케이스 -> 연속해서 세칸오르는 케이스는 없다.,올라도되고,쉬어도되고, 대신에 오를시에 표시.
		계단을 두칸오르는 케이스

		XOXOOX
		XOOXOX
		OXOOX
		OOXOX
		X를 초점으로 해서.

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