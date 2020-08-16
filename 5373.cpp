#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
#include <string>
using namespace std;
int up[3][3] = { 0, };
int down[3][3] = { 0, };
int left_[3][3] = { 0, };
int right_[3][3] = { 0, };
int front[3][3] = { 0, };
int back[3][3] = { 0, };
/*
	입력받고
	방향별로 배열에 담아.
	바꿔치기만 해주면 돼.
	그런다음에, 맨 윗면 출력해주기.
	색깔별로 정수형 숫자 매칭 시켜주자.(약속)
	w : 0
	y : 1
	r : 2
	o : 3
	g : 4
	b : 5


*/
void initialization() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			down[i][j] = 1;
			left_[i][j] = 4;
			right_[i][j] = 5;
			front[i][j] = 2;
			back[i][j] = 3;
		}
	}
}

void enter() {
	string a;
	for (int i = 0; i < 3; i++) {
		cin >> a;
		cout << a;
	}
}



int main() {
	initialization();
	enter();
	system("pause");

}