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
vector <int> result;
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
				return;
			}
		}
	}

}


int main() {
	/*
		check�迭.
		1�� ���� ��� ť�� ���� �ְ� ����.
		�ش� ť�� �˽�Ű�鼭, �˻��غ� ��, �ش� ��ġ�� �鸥���� �־��°�.
		�鸥���� �־��ٸ�, continue;
		�鸥���� �����ٸ�,
			��ü����totalcnt++;
			�պ��� cnt;
			DFS(�ش���ġ)
				nx,ny.
				�ش���ġüũ=1;
				�������Ϲ������� DFS start.
				++cnt;
					����i=0~3.
					if(����ġ�� 0�� �ƴ϶��, �׸��� �鸥���� ���ٸ�)
					DFS(��)
					DFS(��)
					DFS(��)
					DFS(��)
			�������� ���Ϳ� cnt �߰���, cnt =0���� �ʱ�ȭ.
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
		cout << q_f.first << " " << q_f.second << endl;
		if (checkk[q_f.first][q_f.second] == 1) {
			continue;
		}
		else {
			totalcnt++;
			cnt = 0;
			DFS(q_f.first, q_f.second);
			result.push_back(cnt);
			cout << cnt << endl;


		}

		que.pop();
	}



	cout << totalcnt << "�̰Ŷ�" << result.size() << "�̰Ŷ� ���� ������ ����" << endl;
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl;
	}

	system("pause");
}