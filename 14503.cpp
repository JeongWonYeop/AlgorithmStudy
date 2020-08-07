#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
#include <stdlib.h>
using namespace std;
int board[50][50];
int robot_axis[50][50];
//북,동,남,서, 북->서->남->동->북 , 북->남/동->서/남->북/서->동
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
int ans = 0;
int N, M,r_x,r_y,d;
int cnt = 0;
/*
00 01
10 11

cnt 초기화 ->현재위치 청소 -> 왼쪽 바라봄(d값 수정) ->청소가능 -> 이동 -> 처음으로.
								       ->청소불가 cnt++ -> 처음으로
									   -> cnt가 4면 -> 뒤쪽이 벽인지 ? ->벽O ->OFF
																	   ->벽X ->후진.왼쪽바라봄으로.
*/
int backindex(int dd) {
	int b_d;
	switch (dd) {
		case 0:
			b_d = 2;
			break;
		case 1:
			b_d = 3;
			break;

		case 2:
			b_d = 0;
			break;

		case 3:
			b_d = 1;
			break;
	}
	return b_d;
}
int leftindex(int dd) {
	if (dd == 0) {
		return 3;
	}
	else if (dd == 1) {
		return 0;
	}
	else if (dd == 2) {
		return 1;
	}
	else return 2;
}
int ispossible(int x,int y,int orient) {
	int nx = x + dx[orient];
	int ny = y + dy[orient];
	if (nx >= 0 && nx < N && ny >= 0 && ny<M) {
		if (board[nx][ny] != 1&&board[nx][ny] != 2) {
			return 1;
		}
	}
	return 0;
}

int turnleft(int x, int y) {
	while(cnt < 4){
		d = leftindex(d);
		if (ispossible(x,y,d)) return 1;
		else ++cnt;
	}
	return 0;
}

pair<int,int> move(int x, int y, int orient) {
	int nx = x + dx[orient];
	int ny = y + dy[orient];
	pair<int, int> n_axis = { nx,ny };
	return n_axis;
}


void clear(int x, int y) {
	if (board[x][y] == 0) {
		board[x][y] = 2;
		ans = ans + 1;
	}
}
int is_turn_off(int x, int y) {
	int temp_d = backindex(d);
	int nx = x + dx[temp_d];
	int ny = y + dy[temp_d];
	if (board[nx][ny] == 1) {
		return 1;
	}
	else return 0;
	

}
void on(int x, int y) {
	if (x < 0 || x >= N || y < 0 || y >= M) {
		return;
	}
	cnt = 0;
	clear(x, y);
	if (turnleft(x,y)) {
		pair<int, int> n_axis;
		n_axis = move(x, y, d);
		on(n_axis.first, n_axis.second);
	}
	else {
		if (is_turn_off(x,y)) {
			return;
		}
		else {
			on(x+dx[backindex(d)], y+dy[backindex(d)]);
		}
	}
	
}

void enter() {
	cin >> N >> M;
	cin >> r_x >> r_y >> d;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}
}
int main() {
	enter();
	on(r_x,r_y);
	cout << ans;
}