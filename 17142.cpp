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
vector <int> index;
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
	for (int i = 0; i < ALL; i++) {
		index.push_back(i);
	}

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

int checkZero() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (newboard[i][j] == 0)
				return 1;
		}
	}
	return 0;
}
void printfordebug() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << newboard[i][j]<<" ";
		}cout << endl;
	}
}

void spread(int x, int y, int orient, int cnt, int * zerocnt) {
	int nx = x + dx[orient];
	int ny = y + dy[orient];
	if (nx < 0 || ny < 0 || nx > N-1 || ny > N-1 ) return;
	//if (room[nx][ny] == -1) {
	//}
	if (newboard[nx][ny] == -2) {
		foradd = make_pair(nx, ny);
		que2.push(foradd);
		newboard[nx][ny] = -3;
	}
	else if (newboard[nx][ny] == 0) {
		cout << "nx : " << nx <<"ny : "<< ny<<endl;
		++(*zerocnt);
		newboard[nx][ny] = cnt;
		foradd = make_pair(nx, ny);
		que2.push(foradd);
	}
	printfordebug();
	cout << "cnt : " << cnt<< endl;
}

void solve() {

	combination();


	do {
		cout << "ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ" << endl;
		int cnt = 1;
		int zeroCnt = 1;
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

		while (zeroCnt != 0) {
			zeroCnt = 0;
			
			while (!que2.empty()) {
				que.push(que2.front());
				cout << que.front().first << "큐2 " << que.front().second;
				que2.pop();
			}
			while (!que.empty()) {
				pair<int, int> tempvec = que.front();
				cout << tempvec.first << "큐1 " << tempvec.second << endl;
				
				for (int i = 0; i < 4; i++) {
					spread(tempvec.first, tempvec.second, i, cnt, &zeroCnt);
				}
				que.pop();
			}
			++cnt;
		}
		if (!checkZero()) {
			--cnt;
			minest = min(minest, --cnt);
		}

	} while (next_permutation(ind.begin(), ind.end()));

	
}
int main() {
	enterNum();
	solve();
	if (minest == 2147483647) cout << -1;
	else cout << minest;
	system("pause");
}