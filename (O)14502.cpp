#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <vector>
#include <utility>
#include <functional>
using namespace std;
int makeboard[9][9] = { 0, };
int board[9][9] = { 0, };
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
	시간초과 : 10^8 *2
*/


void SafeSum() { //64
	int tempsum = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (makeboard[i][j] == 0)
				++tempsum;
		}
	}

	if (tempsum > safesum) {
		safesum = tempsum;
	}

}
void initboard(){ //64
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			makeboard[i][j] = board[i][j];
			if (makeboard[i][j] == -2) {
				que.push({ i,j });
			}
		}
	}
}
/*
void Debug() { 
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cout << check[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
*/

void BFS() {
	initboard(); //64
	while (!que.empty()) { //64
		PairInt temp = que.front();
		for (int i = 0; i < 4; i++) { //64*4 = 240
			int nx, ny;
			nx = temp.first + dx[i];
			ny = temp.second + dy[i];
			if (nx >= 1 && ny >= 1 && nx <= N && ny <= M) {
				if (makeboard[nx][ny] == 0) {
					check[nx][ny] = check[temp.first][temp.second] + 1;
					makeboard[nx][ny] = 2;
					que.push({ nx,ny });
				}
			}

		}

//		Debug();
		que.pop();
	}

	SafeSum();

}

void setting(int cnt) {
	/*
		바로 백트래킹이로구나.
	*/
	if (cnt == 3) {
		BFS();
		return;
	}


	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (board[i][j] == 0) {
				board[i][j] = -1;
				check[i][j] = -1;
				setting(cnt + 1);//64*64*64 =262,144
				board[i][j] = 0;
				check[i][j] = 0;
			}
		}
	}


}


void enter() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> board[i][j];
			if (board[i][j] == 2) {
				board[i][j] = -2;
//				check[i][j] = 0; // 0초에서 출발
			}
			else if (board[i][j] == 1) {
				board[i][j] = -1;
				check[i][j] = -1;
			}
		}
	}

}

int main() {
	enter();
	setting(0);//3개 놓기

	cout << safesum;

}
