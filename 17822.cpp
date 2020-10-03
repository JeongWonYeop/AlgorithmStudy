#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <utility>
#include <functional>
using namespace std;
int N, M, T;
int board[51][51] = { 0, };
int new_board[51][51] = { 0, };
int dx[4] = {0,0,-1,1};
int dy[4] = {1,-1,0,0};
//우,좌,위,아래
/*
00 01
10 11

*/

typedef struct byunsu {
	int x; // x의 배수
	int d; // 0 시계 1 반시계
	int k; // 몇칸
}byunsu;

vector <byunsu> byunsu_;

/*
구현보다 큰 숲을 먼저 그려라.

입력받고.
회전함수.
연산수행
연산수행한 결과의 합. -> 출력.

*/

/*
int x; // x의 배수
int d; // 0 시계 1 반시계
int k; // 몇칸
*/
void wheel(int x, int d, int k) {
	for (int i = x; i <= N; i += x) {
		/*
		d가 시계일 때,
			index가 1부터 M까지. k만큼 더한다.
			만약에 index+k가 M보다 크면,
				new_board[i][(index+k)%4] = board[i][index];
			그게아니면,
				new_board[i][index+k]  = board[i][index];

		d가 반시계일 때,
			index가 1부터 M까지. k 만큼 뺀다.
			만약에 index-k 가 1보다 작으면,
				new_board[i][M- (index-k)*-1 % M] = board[i][index];
			그게아니면,
				new_board[i][index-k] = board[i][index];
			M으로 나눴을 때 나머지가 0 이면 M 1이면 M-1 2이면 M-2 3이면 M-3  M-1이면 M-(M-1) 즉,1
		*/
		if (d == 0) {
			for (int index = 1; index <= M; index++) {
				if (index + k > M) {
					new_board[i][(index + k) % M] = board[i][index];
				}
				else {
					new_board[i][index + k] = board[i][index];
				}
			}
		}
		else {
			for (int index = 1; index <= M; index++) {
				if (index - k < 1) {
					new_board[i][M - ((index - k)*-1) % M] = board[i][index];
				}
				else {
					new_board[i][index - k] = board[i][index];
				}
			}
		}
	}
}

void enter() {
	cin >> N >> M >> T;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> board[i][j];
			new_board[i][j] = board[i][j];
		}
	}
	for (int i = 0; i < T; i++) {
		int x_;
		int d_;
		int k_;
		cin >> x_ >> d_ >> k_;
		byunsu_.push_back({ x_,d_,k_ });
	}
}
void debug() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cout << new_board[i][j]<<" ";
		}cout << endl;
	}

}
void yunsan() {
	int injub = 0;
	queue <pair<int, int>> que;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			int new_x;
			int new_y;
			for (int k = 0; k < 4; k++) {
				new_x = i + dx[k];
				new_y = j + dy[k];
				if (new_x == 0 || new_y == 0 || new_x == N + 1) continue;
				if (new_y == M + 1) new_y = 1;
				if (new_board[new_x][new_y] == new_board[i][j] && new_board[new_x][new_y]!=0) {
				cout << new_x << "," << new_y << "그리고" << i << "," << j << endl;
					injub = 1;
					que.push({ i,j});
				}
			}
			while (!que.empty()) {
				pair<int,int> p = que.front();
				int temp;
				temp = new_board[p.first][p.second];
				new_board[p.first][p.second] = 0;
				debug();
				cout << endl << endl;
				que.pop();
				for (int k = 0; k < 4; k++) {
					new_x = p.first + dx[k];
					new_y = p.second + dy[k];
					if (new_x == 0 || new_y == 0 || new_x == N + 1) continue;
					if (new_y == M + 1) new_y = 1;
					if (temp == new_board[new_x][new_y] && temp != 0) {
						que.push({ new_x,new_y });
					}

				}

			}
		}
	}
	if (injub == 0) {
		cout << "변한게 없다 !!" << endl;
		float average = 0;
		int getsu = 0;
		//평균내서 평균보다 큰거는 -1 작은거는 +1
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (new_board[i][j] != 0) {
					average += new_board[i][j];
					getsu++;
				}
			}
		}
		average = average / getsu;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (new_board[i][j] != 0) {
					if (new_board[i][j] > average)new_board[i][j] = new_board[i][j] - 1;
					else if (new_board[i][j] < average) new_board[i][j] = new_board[i][j] + 1;
				}
			}
		}
		debug();
	}
}

int get_sum() {
	int answer = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (new_board[i][j] != 0) answer = answer + new_board[i][j];
		}
	}
	return answer;
}
int main() {
	enter();
	//cout << "값 입력 완료" << endl;
	for (vector<byunsu> ::iterator iter = byunsu_.begin(); iter != byunsu_.end();) {
		cout << (*iter).x <<" " <<(*iter).d <<" " <<(*iter).k << endl;
		wheel((*iter).x, (*iter).d, (*iter).k);
		yunsan();
		for (int i = 1; i <= N; i++) {
			memcpy(board[i], new_board[i], sizeof(int)*M+1);
		}
		iter++;
	}
	int answer = get_sum();
	cout << (int)answer;
	system("pause");
}