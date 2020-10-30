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
int checked[500][500] = { 0, };
int ans2 = 0;
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


/*왼쪽 위 점을 기준으로 네칸 이동시에 나올 수 있는 최대값 반환함수*/
int tetromino(int x, int y, int cnt) {
	if (cnt == 5) {
		return 0;
	}
	int ans = 0;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx >= 0 && nx < N&&ny >= 0 && ny < M&&checked[nx][ny] ==0) {
		checked[nx][ny] = 1;
		ans = max(ans,board[x][y]+tetromino(nx, ny, cnt + 1));
		//한번 테트로미노 함수 시작되면 cnt가 5가 되기전까진 계속 타고들어가겠네. 라는 생각.

		checked[nx][ny] = 0;
		}
	}
	return ans;
}

int first(int x, int y) {
	if (x + 1 >= 0 && x + 2 >= 0 && x + 1 < N && x + 2 < N && y + 1 >= 0 && y + 1 < M) {
		return board[x][y] + board[x + 1][y] + board[x + 2][y] + board[x + 1][y + 1];
	}
	else return 0;
}
int second(int x, int y) {
	if (x - 1 >= 0 && x - 1 < N && x + 1 >= 0 && x + 1 < N && y + 1 >= 0 && y + 1 < M) {
		return board[x - 1][y + 1] + board[x][y] + board[x][y + 1] + board[x + 1][y + 1];
	}
	else return 0;
}
int third(int x, int y) {
	if (x + 1 >= 0 && x + 1 < N&&y + 1 >= 0 && y + 1 < M&&y + 2 >= 0 && y + 2 < M) {
		return board[x][y] + board[x][y + 1] + board[x][y + 2] + board[x + 1][y + 1];
	}
	else return 0;
}
int forth(int x, int y) {
	if (x - 1 >= 0 && x - 1 < N && y + 1 >= 0 && y + 1 < M && y + 2 >= 0 && y + 2 < M) {
		return board[x][y] + board[x][y + 1] + board[x][y + 2] + board[x - 1][y + 1];
	}
	else return 0;
}
int other_shape(int x,int y) {
	int ans = 0;
	ans = max(ans, first(x, y));
	ans = max(ans, second(x, y));
	ans = max(ans, third(x, y));
	ans = max(ans, forth(x, y));
	return ans;
}
/*


33
43 44
53

   24
33 34
   44

33 34 35
   44

   24
33 34 35


*/



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
	int ans = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			checked[i][j] = 1;
			ans = max(ans,tetromino(i, j, 1));
			checked[i][j] = 0;
			int ans2 = other_shape(i, j);

			ans = max(ans, ans2);

		}
	}
	cout << ans;
}