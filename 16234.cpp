#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <functional>
#include <utility>
using namespace std;
int a;

/*
ex 4x4
	체크.
		가로세로별 검사는 순차적으로 다해주되, 나라갯수,인구수 더해질 때만. 중복으로 더해지지 않게 방지.
	
	가로전용.
	o o o x
	o o o x
	o o o x
	o o o x

	세로전용
	o o o o
	o o o o
	o o o o
	x x x x 
	.

*/



void enter() {
	cin >> a;

}

void debug() {
	cout << a;
}
///욕심내지말고, 교만하지말고.
//모든 환경을 경배하라. 환경 투입은 의사선택과 같다. 본인도 모르는 의사선택이 있으면 깜짝놀라며 주의(경계)하라.
int main() {
	enter();
	debug();
	system("pause");