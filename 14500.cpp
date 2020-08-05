#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
using namespace std;
int N, M;
int board[500][500] = { 0, };
int checked[500][500] = { 0. };
int ans = 0;
/*우 좌 위 아래*/
int dx[4] = {0,0,-1,1};
int dy[4] = {1,-1,0,0};
/*
00 01
10 11
*/
int max(int a,int b) {
	if (a > b) {
		return a;
	}
	else return b;
}

int tetromino(int x, int y, int cnt) {
	if (cnt == 5) {
		return 0;
	}
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx >= 0 && nx < N&&ny >= 0 && ny < M&&checked[nx][ny] ==0) {
			checked[nx][ny] = 1;
			ans = max(ans,board[x][y]+tetromino(nx, ny, cnt + 1));
			// 빠져나오기전(cnt==5)까지는 아래의 return은 닿을 일 없다.
			checked[nx][ny] = 0;
		}
	}
	return ans;
}

void other_shape(int x,int y) {

}


void enter() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}
}


int main() {
	enter();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			checked[i][j] = 1;
			tetromino(i, j, 1);
			checked[i][j] = 0;
			other_shape(i, j);
		}
	}
}