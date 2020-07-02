#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <utility>
#include<string.h>
#include <vector>
#include <algorithm>
using namespace std;


int N, M;
int minest = 2147483647;
int room[50][50] = { 0, };
int newboard[50][50] = { 0, };
vector <pair<int,int>> vec;
pair<int, int> foradd;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
//��,��,��,�Ʒ�
// 0��1�� ���� �� ���� ����
vector<int> ind;

queue <pair<int, int>> que;
queue <pair<int, int>> que2;

void enterNum() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> room[i][j];
			if (room[i][j] == 2) {
				foradd = make_pair(i, j);
				vec.push_back(foradd);
				room[i][j] = -2;
			}
			else if (room[i][j] == 1) {
				room[i][j] = -1;
			}
		}
	}
}

void combination() {
	int ALL = vec.size();


	// M���� 1 �߰�
	for (int i = 0; i<M; i++) {
		ind.push_back(1);
	}
	// vec.size-M�� �� 0 �߰�
	for (int i = 0; i<ALL - M; i++) {
		ind.push_back(0);
	}
	// ����
	sort(ind.begin(), ind.end());
	//����
	

}
//�����ϸ� 1, �ƴϸ� 0.
void isUseful(int x, int y,int * zerocnt) {
	if (x < 0 || y < 0 || x > N - 1 || y > N - 1) return;
	for (int i = 0; i < 4; i++){
		int j = 0;
		if (x + dx[i] >= 0 && x + dx[i] < N && y + dy[i] >= 0 && y + dy[i] < N ) {
			foradd = make_pair(x, y);
			que2.push(foradd);
			return;
		}
		
		// newboard[x + dx[i]][y + dy[i]] == 0 �������ν�, -2 ��Ȱ�� ���̷����� �ִ��� ������� ��� ���� ����ǰԲ� ���־���. �������� ������ �ֺ��� ����� ���� ���� �߰��ϵ��� �߱� �����̴�.
	}
	// ���� ���´� �巡�� �ִ� �ֵ��� �� �߰��� ���´�. �巡�� ���� �ֵ� �߿�.

}

int checkZero() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (newboard[i][j] == 0)
				return 1;
		}
	}
	return 0;
}

void spread(int x, int y, int cnt, int * zerocnt) {
	int nx;
	int ny;
	if (cnt == 0) {
		++(*zerocnt);
	}

	//if (room[nx][ny] == -1) {
	//}
	if (newboard[x][y] == -2) {
		//ī��Ʈ ���������� �ʿ����, �ٸ�, �ش� ��ǥ�� ���������� ������ �� �ְ� ť�� �߰�.
		newboard[x][y] = -3;

		for (int i = 0; i < 4; i++) {
			nx = x + dx[i];
			ny = y + dy[i];
			isUseful(nx, ny, zerocnt);
		}
		++(*zerocnt);

	}
	else if (newboard[x][y] == 0) {


		newboard[x][y] = cnt;
		

		for (int i = 0; i < 4; i++) {
			nx = x + dx[i];
			ny = y + dy[i];
			if (newboard[nx][ny] == 0) {
				++(*zerocnt);
			}
			// zerocnt�� �÷���, ť�� �ѹ� �� �� �� �ְ� ���־���. 
			// 
			isUseful(nx, ny, zerocnt);

		}
	}



	
}

void solve() {

	combination();


	do {
		int cnt = 0;
		int zeroCnt = 1;
		while (!que2.empty()) { que2.pop(); }
		while (!que.empty()){ que.pop();  }
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				newboard[i][j] = room[i][j];
			}
		}
		// ���
		for (int i = 0; i<ind.size(); i++) {
			if (ind[i] == 1) {
				foradd = make_pair(vec[i].first, vec[i].second);
				que.push(foradd);

			}
		}
		/*
		1. �ش� ��ǥ�������� ó���� �����̴ϱ� �翬�� ���� �� �� cnt�� 0���� ���ٰ� �����¿� �������� �ֵ� �� ť�� �־��ֶ�.
		cnt �� ���� ��Ű��.
		
		*/
		while (zeroCnt != 0) {
			zeroCnt = 0;
			while (!que2.empty()) {
				que.push(que2.front());
				que2.pop();
			}

			while (!que.empty()) {
				pair<int, int> tempvec = que.front();
				spread(tempvec.first, tempvec.second, cnt, &zeroCnt);
		
				que.pop();
			}
			if (!checkZero()) {
				// 0�� ������, 1 --> ������ 0.
				break;
			}
			
			cnt++;
		}
		//�˻��ϱ�δ� ���̻� �������� ���� ����.
		//�� ��ü�� �������� ������� ������ �װ� �ּڰ� ������ֱ�.
		if (!checkZero()) {

			minest = min(minest, cnt);
		}

	} while (next_permutation(ind.begin(), ind.end()));

	
}
int main() {
	enterNum();
	solve();
	if (minest == 2147483647) cout << -1;
	else cout << minest;
}