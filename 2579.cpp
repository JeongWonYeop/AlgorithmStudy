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
	int dp[301] = { 0, }; //결과
	//초기화. dp[i] : i계단까지 올라온 계단 합으로 정의.



	for (int i = 1; i <= N; i++) {
		cin >> floor[i];
	}
	/*
	OXO
	OOX
	XOO
	*/
	dp[1] = floor[1];
	dp[2] = maxx(floor[1] + floor[2], floor[2]);
	dp[3] = maxx(floor[2] + floor[3], floor[1] + floor[3]);


	/*
	_______________/dp/XO
	______________/dp/XOO

	*/
	for (int i = 4; i <= N; i++) {
		dp[i] = maxx(dp[i - 2] + floor[i], dp[i - 3] + floor[i - 1] + floor[i]);
	}



	cout << dp[N] << endl;
	system("pause");
}