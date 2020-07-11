#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;


/*
	1. 매 반복마다 체크-> 먹을 수 있는 물고기가 있는가. 없으면 종결.
	2. 있다면 타겟팅.(좌표 반환)
	3. 갈 수 있는 '길이 없다면' 종결.
	4. 먹을 수 있는 물고기 큐에 담고, 행 오름차순, 열 오름차순. 정렬하고. front인거 담아두기
	5. 각각 퍼져나갈 때 해당 좌표여야 없어지게.
	6. 없어진 다음에는 정렬한 큐 팝.
*/
int board[20][20] = { 0, };
int s_p[20][20] = { 0, }; // shark_position 상어의 크기와 위치를 표시
int p_f[20][20] = { 0 , };
int e_f = 0; // eaten_fish
int sizee;
int endd = 0;

pair <int, int> foradd;
queue <pair<int, int>> que;
queue <pair<int, int>> que2;
vector <int> row;
vector <int> col;
queue <pair<int, int>> que3;
int result = 0;
//왼 오른 위 아래
/*
	00 01
	10 11
*/

int dx[4] = {0,0,-1,1};
int dy[4] = {-1,1,0,0};
int sx, sy;



int checkp_f(int newboard[][20],int shark_size) {
	int ispossible = 0;

	for (int i = 0; i < sizee; i++) {
		for (int j = 0; j < sizee; j++) {
			p_f[i][j] = 0;
		}
	}

	while (!que3.empty()) {
		que3.pop();
	}


	for (int i = 0; i < sizee; i++) {
		for (int j = 0; j < sizee; j++) {
			if (newboard[i][j] > 0 && newboard[i][j] < shark_size) {
				foradd = make_pair(i, j);
				que3.push(foradd);
				p_f[i][j] = 1;
				ispossible = 1;
				cout << "aa " << endl;
			}
		}
	}



	return ispossible;
}



void mc(int X, int Y, int newboard[][20], int cnt,int orient,int e_f,int shark_size) {

	cout << "cnt : " <<  cnt <<endl;
	// move and check
	if (que3.empty()) {
		result = cnt;
		return;
	}		
	
	int nx = X + dx[orient];
	int ny = Y + dy[orient];
	if (nx >= 0 && ny >= 0 && nx < sizee && ny < sizee) {
		if (newboard[nx][ny] == 0) {
			for (int i = 0; i< 4; i++) {
				mc(nx, ny, newboard, ++cnt, i,e_f,shark_size);
			}
			return;
		}
		else if (newboard[nx][ny] < shark_size) {
			newboard[nx][ny] = 0;
			++e_f;
			if (e_f == shark_size) {
				++shark_size;
				e_f = 0;
			}
			if (checkp_f(newboard,shark_size) != 1) {
				for (int i = 0; i < 4; i++) {
					mc(nx, ny, newboard, ++cnt, i,e_f,shark_size);
				}
				return;
			}

		}
	}

	
	/*큐 추가해주기
	for (int i = 0; i < 4; i++) {
		int nx = X + dx[i];
		int ny = Y + dy[i];
		if (nx >= 0 && ny >= 0 && nx < sizee && ny < sizee){
			if (board[nx][ny] == 0 || board[nx][ny] < shark_size) {
				foradd = make_pair(nx, ny);
				que2.push(foradd);
				cout << nx << "and "<<ny<<endl;
				cout << "추가됨" << endl;

			}
		}
	}
	*/
	/*큐 팝 */



}

void enter() {
	cin >> sizee;
	for (int i = 0; i < sizee; i++) {
		for (int j = 0; j < sizee; j++) {
			cin >> board[i][j];
			if (board[i][j] == 9) {
				s_p[i][j] = 2;
				sx = i;
				sy = j;
				board[i][j] = 0;
			}
		}
	}
}

int main() {
	enter();
	int shark_first_size = 2;
	checkp_f(board, shark_first_size);
	for(int i = 0 ; i< 4; i++){
		mc(sx, sy, board, 0, i, 0, shark_first_size);
	}

	/*
	먹을수있는 물고기 위치 알려주는 보드
	-> 먹을 수 있는 물고기 0되면 종료 . 매 턴마다 체크
	-> min(cnt,minn) 최신화

	

	while (checkp_f()) {

		while (!que2.empty()) {
			que.push(que2.front());
			que2.pop();
		}



		while (!que.empty()) {

			
			//생각해보면, 추가되는 건 여러갠데 큐는 하나씩만 팝되면, 무한반복이나 마찬가지다. 그러므로 이 안에 어떠한 탈출 조건이 있어야한다. break;
			// 여기 문제의 경우에는 그것이 먹을 수 있는 물고기가 더 이상 없을 때라는 조건이 된다.
			int sx = que.front().first;
			int sy = que.front().second;
			cout << sx << " " << sy << endl;
			if (board[sx][sy] == 0) {
				mc(sx, sy);
			}
			else if (sx == que3.front().first && sy == que3.front().second) {
				++e_f;
				if (e_f == shark_size) {
					++shark_size;
					e_f = 0;
				}
				board[sx][sy] = 0;
				que3.pop();
				cout << sx << " 퍼퍼퍼펑 " << sy << endl;
				mc(sx, sy);

			}

			que.pop();




		}
		++cnt;
		cout << cnt << endl;
	}
	*/
	cout << result << endl;
	system("pause");
	/*
		for(int i =0 ; i < 4;i++){
		mc(sx+dx[i],sy+dy[i]);
		while (!que.empty()) {
			mc(que.front().first, que.front().second);
		}
	}*/
}