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
typedef struct board_info {
	int xx;
	int yy;
	int sizee;
}B_I;


struct compare0 {
	bool operator()(B_I &a, B_I &c) {
		if (a.xx != c.xx)
			return a.xx > c.xx;
		if(a.yy!=c.yy)
			return a.yy > c.yy;
		return a.sizee > c.sizee;
	}

};
priority_queue <B_I, vector <B_I>, compare0> que0;


void enter() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
			que0.push({ i,j,board[i][j] });
		}
	}
}

void quesee() {
	while (!que0.empty()) {
		cout << que0.top().xx << " " << que0.top().yy << " " <<que0.top().sizee<< endl;

		que0.pop();
	}

}
int main() {
	enter();
	quesee();
	system("pause");
}