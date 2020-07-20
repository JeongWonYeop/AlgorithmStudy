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
	for (int i = 1; i <= day; i++) { // 의문점 : 해당 일자는 그냥 넘어가는 케이스[뜅거져 넘어간 경우와 그보단 덜뜅거져 넘어간 경우와 차례로 넘어간 경우]와, 배정된 일을 하는 케이스를 어떻게 한 자료구조에서 표현하는가?
		cin >> TP[i][0] >> TP[i][1];
		if (i + TP[i][0] <= day+1) { // i일에 배정된 일을 하는 경우.
			arr[i + TP[i][0]] = maxx(arr[i + TP[i][0]], arr[i]+TP[i][1]);
			result = maxx(result, arr[i + TP[i][0]]);
		}
		//i일에 배정된 일을 안하고,  그냥 넘어가는 케이스.
		arr[i + 1] = maxx(arr[i], arr[i + 1]);
		result = maxx(result, arr[i + 1]);
 	}

	cout << result;
}