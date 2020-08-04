#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <vector>
#include <utility>
#include <functional>
using namespace std;
int board[9][9] = { 0, };
int initboard[9][9] = { 0, };
int check[9][9] = { 0, };
int N, M;
int dx[4] = {0,0,-1,1};//좌,우,상,하
int dy[4] = {-1,1,0,0};
int safesum = 0;
/*
 00 01
 10 11

*/
typedef pair <int, int>  PairInt;
queue <PairInt> que;
/*
	초 개념은 없지만 넣어서 풀어보자.
	각 바이러스가 한칸 퍼져나갈 때 1초임.
	bfs로 풀면됨.
*/

void setting() {

}


void reset() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			board[i][j] = initboard[i][j];
			check[i][j] = initboard[i][j];
			if (check[i][j] == -2)  check[i][j] = 0;
		}
	}

}


void SafeSum() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (board[i][j] == 0)
				++safesum;
		}
	}


}

void Debug() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cout << check[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void enter() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> board[i][j];
			if (board[i][j] == 2) {
				que.push({ i,j });
				board[i][j] = -2;
				initboard[i][j] = -2;
//				check[i][j] = 0; 0초 시작
			}
			else if (board[i][j] == 1) {
				board[i][j] = -1;
				initboard[i][j] = -1;
				check[i][j] = -1;
			}
		}
	}

}

void main() {
	enter();
	reset(); //초기화
	setting();//3개 놓기
	while (!que.empty()) {
		PairInt temp = que.front();
		for (int i = 0; i < 4; i++) {
			int nx, ny;
			nx = temp.first + dx[i];
			ny = temp.second + dy[i];
			if (nx >= 1 && ny >= 1 && nx <= N && ny <= M) {
				if (board[nx][ny] == 0) {
					check[nx][ny] = check[temp.first][temp.second] + 1;
					board[nx][ny] = 2;
					que.push({ nx,ny });
				}
			}

		}

		Debug();
		que.pop();
	}

	SafeSum();
	cout << safesum;
	system("pause");
}
