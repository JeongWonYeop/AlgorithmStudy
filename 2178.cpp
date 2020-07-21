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
int cnt = 1;
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
			cout << board[i][j] << " ";
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
	while(finish == 0){
		++cnt;
		while(!que2.empty()){
			que.push({ que2.front().first, que2.front().second });
			que2.pop();
		}
		while(!que.empty()){
			pair<int,int> qf = que.front();
			for (int i = 0; i < 4; i++) {
				int nx = qf.first + dx[i];
				int ny = qf.second + dy[i];
				if (nx >= 0 && ny >= 0 && nx < N && ny < M) {
					if(board[nx][ny] == 1 && check[nx][ny] != 1){
						board[nx][ny] = cnt;
						check[nx][ny] = 1;
						que2.push({ nx,ny });
						if (nx == N - 1 && ny == M - 1) {
							finish = 1;
							break;
						}
					}

				}
			}
			que.pop();
		}

		seeboard();
		cout << endl;

	}
}



int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		int tempp;
		cin >> tempp;
		for(int j = M-1; j>=0;j--){
			if (tempp % 10 == 0)
				board[i][j] = 0;
			else if(tempp % 10 == 1)
				board[i][j] = 1;
			tempp = tempp /10;
		}
	}

	pushque();
	bfs();
	cout << cnt;

	system("pause");
}