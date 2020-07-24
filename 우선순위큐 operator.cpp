#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
using namespace std;
int N;
int board[20][20];
//priority_queue <B_I, vector <B_I>, compare1> que1;
//priority_queue <B_I, vector <B_I>, compare2> que2;
//priority_queue <B_I, vector <B_I>, compare3> que3;
int dx[4] = { 0,0,-1,1 }; //ÁÂ¿ìÀ§¾Æ·¡
int dy[4] = { -1,1,0,0 };
typedef struct board_info {
	int xx;
	int yy;
	int sizee;
}B_I;
/*
00  01
10  11
*/

struct compare0 {
	bool operator()(B_I &a, B_I &c) {
		if (a.xx != c.xx)
			return a.xx > c.xx;
		return a.yy > c.yy;

	}

};


priority_queue <B_I, vector <B_I>, compare0> que0;

void tilt(int orient) {

}

void enter() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
			B_I foradd = { i,j };
			que0.push(foradd);
		}
	}
}


void see() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

void quesee() {
	while (!que0.empty()) {
		cout << que0.top().xx << " " << que0.top().yy << " " << endl;

		que0.pop();
	}

}
int main() {
	enter();
	quesee();
	system("pause");
}