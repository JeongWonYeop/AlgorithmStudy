#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <utility>
using namespace std;


/*
1. 매 반복마다 체크-> 먹을 수 있는 물고기가 있는가. 없으면 종결.
2. 있다면 타겟팅.(좌표 반환)
3. 갈 수 있는 '길이 없다면' 종결.
*/
int board[20][20] = { 0, };
int s_p[20][20] = { 0, }; // shark_position 상어의 크기와 위치를 표시
int p_f[20][20] = { 0 , };
int shark_size = 2;
int e_f = 0; // eaten_fish
int cnt = -1; // total count
int sizee;
int endd = 0;
int quepop = 0;
int quepop2 = 0;
pair <int, int> foradd;
queue <pair<int, int>> que;
queue <pair<int, int>> que2;
//왼 오른 위 아래
/*
00 01
10 11
*/

int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int sx, sy;


int checkp_f() {
	int ispossible = 0;

	for (int i = 0; i < sizee; i++) {
		for (int j = 0; j < sizee; j++) {
			p_f[i][j] = 0;
		}
	}


	for (int i = 0; i < sizee; i++) {
		for (int j = 0; j < sizee; j++) {
			if (board[i][j] > 0 && board[i][j] < shark_size) {
				p_f[i][j] = 1;
				ispossible = 1;
			}
		}
	}

	for (int i = 0; i < sizee; i++) {
		for (int j = 0; j < sizee; j++) {
			cout << p_f[i][j];
		}
		cout << endl;
	}


	return ispossible;
}



void mc(int X, int Y) {

	// move and check


	/*큐 추가해주기*/
	for (int i = 0; i < 4; i++) {
		int nx = X + dx[i];
		int ny = Y + dy[i];
		if (nx >= 0 && ny >= 0 && nx < sizee && ny < sizee) {
			if (board[nx][ny] == 0 || board[nx][ny] < shark_size) {
				foradd = make_pair(nx, ny);
				que2.push(foradd);
				cout << nx << "and " << ny << endl;
				cout << "추가됨" << endl;

			}
		}
	}

	/*큐 팝 */



}

void enter() {
	cin >> sizee;
	for (int i = 0; i < sizee; i++) {
		for (int j = 0; j < sizee; j++) {
			cin >> board[i][j];
			if (board[i][j] == 9) {
				s_p[i][j] = shark_size;
				sx = i;
				sy = j;
				board[i][j] = 0;
			}
		}
	}
}

int main() {
	enter();

	foradd = make_pair(sx, sy);
	que.push(foradd);


	/*
	먹을수있는 물고기 위치 알려주는 보드
	-> 먹을 수 있는 물고기 0되면 종료 . 매 턴마다 체크
	-> min(cnt,minn) 최신화



	*/
	while (checkp_f()) {

		while (!que2.empty()) {
			que.push(que2.front());
			que2.pop();
		}



		while (!que.empty()) {

			/*연산*/
			//생각해보면, 추가되는 건 여러갠데 큐는 하나씩만 팝되면, 무한반복이나 마찬가지다. 그러므로 이 안에 어떠한 탈출 조건이 있어야한다. break;
			// 여기 문제의 경우에는 그것이 먹을 수 있는 물고기가 더 이상 없을 때라는 조건이 된다.
			int sx = que.front().first;
			int sy = que.front().second;
			cout << sx << " " << sy << endl;
			if (board[sx][sy] == 0) {
				mc(sx, sy);
			}
			else if (board[sx][sy] < shark_size) {
				++e_f;
				if (e_f == shark_size) ++shark_size;
				board[sx][sy] = 0;
				mc(sx, sy);
			}

			que.pop();




		}
		++cnt;
		cout << cnt << endl;
	}
	if (cnt == -1) cout << 0;
	else cout << cnt;
	system("pause");
	/*
	for(int i =0 ; i < 4;i++){
	mc(sx+dx[i],sy+dy[i]);
	while (!que.empty()) {
	mc(que.front().first, que.front().second);
	}
	}*/
}