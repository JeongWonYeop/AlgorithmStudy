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
//좌,우,위,아래
// 0과1을 저장 할 벡터 생성
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


	// M개의 1 추가
	for (int i = 0; i<M; i++) {
		ind.push_back(1);
	}
	// vec.size-M개 의 0 추가
	for (int i = 0; i<ALL - M; i++) {
		ind.push_back(0);
	}
	// 정렬
	sort(ind.begin(), ind.end());
	//순열
	

}
//유용하면 1, 아니면 0.
void isUseful(int x, int y,int * zerocnt) {
	if (x < 0 || y < 0 || x > N - 1 || y > N - 1) return;
	for (int i = 0; i < 4; i++){
		int j = 0;
		if (x + dx[i] >= 0 && x + dx[i] < N && y + dy[i] >= 0 && y + dy[i] < N ) {
			foradd = make_pair(x, y);
			que2.push(foradd);
			return;
		}
		
		// newboard[x + dx[i]][y + dy[i]] == 0 해줌으로써, -2 비활성 바이러스가 있더라도 빈공간이 모두 차면 종료되게끔 해주었다. 퍼져나갈 아이의 주변에 빈공간 있을 때만 추가하도록 했기 때문이다.
	}
	// 지금 상태는 장래성 있는 애들은 다 추가된 상태다. 장래성 없는 애들 중에.

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
		//카운트 증가시켜줄 필요없고, 다만, 해당 좌표도 퍼져나가는 역할할 수 있게 큐에 추가.
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
			// zerocnt를 늘려서, 큐가 한번 더 돌 수 있게 해주었고. 
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
		// 출력
		for (int i = 0; i<ind.size(); i++) {
			if (ind[i] == 1) {
				foradd = make_pair(vec[i].first, vec[i].second);
				que.push(foradd);

			}
		}
		/*
		1. 해당 좌표기준으로 처음엔 시작이니까 당연히 인자 들어갈 때 cnt값 0으로 들어갔다가 상하좌우 퍼져나갈 애들 다 큐에 넣어주라.
		cnt 값 증가 시키라.
		
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
				// 0이 있으면, 1 --> 없으면 0.
				break;
			}
			
			cnt++;
		}
		//검사하기로는 더이상 퍼져나갈 곳이 없다.
		//맵 전체로 봤을때도 빈공간이 없으면 그건 최솟값 만들어주기.
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