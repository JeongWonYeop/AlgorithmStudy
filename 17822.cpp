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
//��,��,��,�Ʒ�
/*
00 01
10 11

*/

typedef struct byunsu {
	int x; // x�� ���
	int d; // 0 �ð� 1 �ݽð�
	int k; // ��ĭ
}byunsu;

vector <byunsu> byunsu_;

/*
�������� ū ���� ���� �׷���.

�Է¹ް�.
ȸ���Լ�.
�������
��������� ����� ��. -> ���.

*/

/*
int x; // x�� ���
int d; // 0 �ð� 1 �ݽð�
int k; // ��ĭ
*/
void wheel(int x, int d, int k) {
	for (int i = x; i <= N; i += x) {
		/*
		d�� �ð��� ��,
			index�� 1���� M����. k��ŭ ���Ѵ�.
			���࿡ index+k�� M���� ũ��,
				new_board[i][(index+k)%4] = board[i][index];
			�װԾƴϸ�,
				new_board[i][index+k]  = board[i][index];

		d�� �ݽð��� ��,
			index�� 1���� M����. k ��ŭ ����.
			���࿡ index-k �� 1���� ������,
				new_board[i][M- (index-k)*-1 % M] = board[i][index];
			�װԾƴϸ�,
				new_board[i][index-k] = board[i][index];
			M���� ������ �� �������� 0 �̸� M 1�̸� M-1 2�̸� M-2 3�̸� M-3  M-1�̸� M-(M-1) ��,1
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
				cout << new_x << "," << new_y << "�׸���" << i << "," << j << endl;
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
		cout << "���Ѱ� ���� !!" << endl;
		float average = 0;
		int getsu = 0;
		//��ճ��� ��պ��� ū�Ŵ� -1 �����Ŵ� +1
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
	//cout << "�� �Է� �Ϸ�" << endl;
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