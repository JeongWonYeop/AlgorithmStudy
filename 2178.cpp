#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
#include <functional>
#include <string.h> 
using namespace std;
int board[100][100] = { 0, };
int check[100][100] = { 0, };
int N, M;
int dx[4] = {0,0,-1,1};
int dy[4] = {-1,1,0,0};
int finish = 0;
/*
00   01
10   11
*/
queue <pair<int, int>> que;
queue <pair<int, int>> que2;

void seeboard() {

	for (int i = 0; i < N; i++) {

		for (int j = 0; j < M; j++) {
			cout << check[i][j] << " ";
		}
		cout << endl;

	}

}

void pushque() {
	que.push(make_pair(0, 0));
	check[0][0] = 1;
	//que.push({0,0});
}


void bfs() {
		while(!que.empty()){
			pair<int,int> qf = que.front();
			for (int i = 0; i < 4; i++) {
				int nx = qf.first + dx[i];
				int ny = qf.second + dy[i];
				if (nx >= 0 && ny >= 0 && nx < N && ny < M) {
					if(board[nx][ny] == 1 && check[nx][ny] == 0){
						check[nx][ny] = check[qf.first][qf.second] + 1;//초 개념의 새로운 방법
						que.push({ nx,ny });
						if (nx == N - 1 && ny == M - 1) {
							break;
						}
					}

				}
			}
			que.pop();
//			seeboard();
//			cout << endl;
		}

	

	
}



int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for(int j = 0; j < M;j++){
			scanf_s("%1d", &board[i][j]);
		}
	}

	pushque();
	bfs();
	cout << check[N-1][M-1];

   system("pause");
}