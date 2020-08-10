#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <queue>
#include <cstring>
#include <string>
#include <functional>
#include <utility>
using namespace std;
int N, M, H;
typedef pair <int, int> PairInt;
int vec[11][31] = { 0, }; //좌->우
int vec2[11][31] = { 0, }; //우->좌
int checked[11][31] = { 0, };
int ans = 987654321;
int goal = 0;
/*
	사다리 내려가는 함수(출발번호)
	가로선 서로 겹치는지 아닌지 검사하는 함수.
	추가하는 가로선이 3 초과가 되면 return, 다 돌았는데도 안되면 -1.
	추가된 개수가 3초과도 아니고, 모든 i세로선 결과 i면 해당 갯수와 현재까지 최소 갯수를 비교해서 최소갯수 최신화. 


*/


void enter_line(int x,int y) {
	vec[x][y] = 1;
	vec2[x][y + 1] = 1;
	checked[x][y] = 1;
	checked[x][y+1] = 1;
}

void remove_line(int x, int y) {
	vec[x][y] = 0;
	vec2[x][y + 1] = 0;
	checked[x][y] = 0;
	checked[x][y + 1] = 0;
}

void enter() {
	cin >> N >> M >> H; // H행, N열 , 변화되는지점의 갯수 M
	for (int i = 0; i < M; i++) {
		int x, y; //y열 x행
		cin >> x >> y;
		enter_line(x, y);
	}
}

void degug1() {
	/*
	for (int i = 1; i < N+1; i++) {
		if (!vec2[i].empty()) {
			vector <int> ::iterator v_iter = vec2[i].begin();
			for (; v_iter != vec2[i].end(); v_iter++) {
				cout << i << "번째 세로선에" << (*v_iter) << "행에서 변화" << endl;
			}

		}
	}
	*/
}

void ladder_gotounder(int N,int depth) {//N열, depth 행
	if (depth == H + 1) {
		goal = N;
		return;
	}
	
	int n_N = N;
	
	if (vec[depth][N] == 1) {
		n_N = N + 1;
	}
	else if(vec2[depth][N] == 1){
		n_N = N - 1;
	}

	ladder_gotounder(n_N, depth + 1);
}

//겹치면 1 반환
int is_checked(int x,int y) {
	if (checked[x][y] == 1) return 1;
	if (checked[x][y + 1] == 1) return 1;
	else return 0;
}
//모든 i세로선이 i결과.
int all_pass() {
	int a = 0;
	for (int i = 1; i < N + 1; i++) {
	//	cout << i << "세로선 결과 : " << ladder_gotounder(i, 0) << endl; 실수 2: 주어진 힌트를 왜 안봤어? 디버깅 과정에서 그 답안지로 문제점을 바로 찾아냈잖아. 그걸 왜 니가 풀고 있냐~
		ladder_gotounder(i, 0);
		if (goal == i) {
			a++;
		}
	}
	if (a == N) return 1;
	else return 0;
}

int min(int a,int b) {
	if (a < b) return a;
	else return b;

}


void dfs(int cnt) {

	if (all_pass()) {
		ans = min(ans, cnt-1);
	//	cout << "<<<<<<<<<<"<<cnt - 1<<">>>>>>>>>>" << endl;
		return;
	}
	if (cnt == 4) return;
	for (int i = 1; i < H+1; i++) {
		for (int j = 1; j < N+1; j++) {
	//		cout << "-------"<<cnt<<"--------" << endl;
			if (!is_checked(i, j)) {
				enter_line(i, j);
	//			cout << i << " " << j<<endl;
				dfs(cnt + 1);
				remove_line(i, j);
			}
			
		}
	}




}

int main() {
	enter();
	dfs(1);
	if (ans == 987654321) ans = -1;
	cout << ans;
}