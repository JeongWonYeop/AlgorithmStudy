#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <vector>
#include <utility>
#include <functional>//greater
using namespace std;

int N;
int board[25][25] = { 0, };
int checkk[25][25] = { 0, };
int totalcnt = 0;
queue <pair <int,int> > que;
typedef pair<int, int> Pair;
int dx[4] = {0,0,1,-1};
int dy[4] = {-1,1,0,0};
priority_queue <int, vector<int>, greater<int>> resultque;
int cnt = 0;
/*
00  01
10  11
*/

void DFS(int a, int b) {
	checkk[a][b] = 1;
	++cnt;
	for(int i = 0 ; i < 4;i++){
		int nx = a + dx[i];
		int ny = b + dy[i];
		if (nx >= 0 && ny >= 0 && nx < N && ny < N){
			if (board[nx][ny] == 1 && checkk[nx][ny] != 1) {
				DFS(nx, ny);
			}
		}
	}

}


int main() {
	/*
		check배열.
		1인 원소 모두 큐에 집어 넣고 시작.
		해당 큐를 팝시키면서, 검사해볼 건, 해당 위치를 들른적이 있었는가.
		들른적이 있었다면, continue;
		들른적이 없었다면,
			전체변수totalcnt++;
			합변수 cnt;
			DFS(해당위치)
				nx,ny.
				해당위치체크=1;
				동서남북방향으로 DFS start.
				++cnt;
					포문i=0~3.
					if(각위치가 0이 아니라면, 그리고 들른적이 없다면)
					DFS(동)
					DFS(서)
					DFS(남)
					DFS(북)
			오름차순 벡터에 cnt 추가후, cnt =0으로 초기화.
	*/
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%1d", &board[i][j]);
			if(board[i][j] == 1)que.push({ i,j });
		}
	}
	

	while (!que.empty()) {
		Pair q_f = que.front();
//		cout << q_f.first << " " << q_f.second << endl;
		if (checkk[q_f.first][q_f.second] == 1) {
			que.pop();
			continue;
		}
		else {
			totalcnt++;
			cnt = 0;
			DFS(q_f.first, q_f.second);
			resultque.push(cnt);
//			cout << cnt << endl;


		}
		que.pop();
	}

	// 문제 조건 중에 오름차순...

	cout << resultque.size() << endl;
	
	
	while(!resultque.empty()){
		cout << resultque.top() << endl;
		resultque.pop();
	}

}