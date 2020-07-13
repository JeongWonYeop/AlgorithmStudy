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
int dist[20][20] = { 0, };
int ndist[20][20] = { 0, };
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
queue <pair<int, int>> que3;
queue < pair <int, int> > que4;

int mina = 2147483647;
int now_x, now_y;
int iseat = 0;
int mindist;
int resultdist = 0;
//왼 오른 위 아래
/*
00 01
10 11
*/

int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int sx, sy;

void bfss(int a, int b) {
	int minn = 2147483647;
	for (int i = 0; i < 4; i++){
		int na = a + dx[i];
		int nb = b + dy[i];

		if(na >= 0 && nb >= 0 && na < sizee && nb< sizee){
			if (board[na][nb] == 0) {
				ndist[na][nb] = ndist[a][b] + 1;
			}
			if (board[na][nb] > 0 && board[na][nb] < sizee) {
				minn = board[na][nb];
				foradd = make_pair(na, nb);
				que3.push(foradd);
			}
			if (board[na][nb] > sizee) {
				continue;
			}
			if (board[na][nb] == minn) break;
			foradd = make_pair(na, nb);
			que4.push(foradd);
		}

	}
}

void checkp_f() {
	
	while (!que3.empty()) {
		que3.pop();
	}

	for (int i = 0; i < sizee; i++) {
		for (int j = 0; j < sizee; j++) {
			dist[i][j] = 0;
		}
	}

	foradd = make_pair(sx, sy);
	que4.push(foradd);

	while (!que4.empty()) {
		bfss(que4.front().first, que4.front().second);
	}



}



void mc(int X, int Y) {

	// move and check

	/*큐 추가해주기*/
	for (int i = 0; i < 4; i++) {
		int nx = X + dx[i];
		int ny = Y + dy[i];
		if (nx >= 0 && ny >= 0 && nx < sizee && ny < sizee) {
			if (board[nx][ny] == 0 || board[nx][ny] == shark_size) {
				dist[nx][ny] = dist[X][Y] + 1;
			}
			else if (board[nx][ny] > shark_size) continue;
			else if (board[nx][ny] < shark_size){
				if (nx == que3.front().first && ny == que3.front().second) {
					++e_f;
					if (e_f == shark_size) {
						++shark_size;
						e_f = 0;
					}
					que3.pop();
					sx = nx;
					sy = ny;
					board[nx][ny] = 0;
					dist[nx][ny] = dist[X][Y] + 1;
					mindist = dist[nx][ny];
					iseat = 1;
					cout << "물고기의 위치" << nx << ", " << ny << "까지 오는데" << dist[nx][ny] << "만큼의 시간이 걸렸다." << endl;
					break;
				}
			}
			foradd = make_pair(nx, ny);
			que.push(foradd);
		}
	}


	for (int i = 0; i < sizee; i++) {
		for (int j = 0; j < sizee; j++) {
			cout << dist[i][j] << " ";
		}cout << endl;
	}
	cout << endl;
	/*큐 팝 */



}

void enter() {
	cin >> sizee;
	for (int i = 0; i < sizee; i++) {
		for (int j = 0; j < sizee; j++) {
			cin >> board[i][j];
			if (board[i][j] == 9) {
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
		먹을 수 있는 물고기 갱신 함수 : 상어의 크기와 대조해서 먹을 수 있는 물고기 조회하고 그거를 특정 우선순위에 따라서 큐에 넣어둠. -> 1 
		해당 물고기 큐가 텅 비어있으면 종료.
		그게 아니면 반복하는데 뭘 반복하냐하면,
		bfs를 반복해.
			bfs함수 : 네방향으로 퍼져나가면서 , 보드 값 채워주고, 언제까지 반복되냐면, 우선순위큐의 맨 앞에 [x][y]에 도착할 때 까지. 여태까지의 이동거리 + 지금 도착할 때 이동한 거리
			네 방향으로 간 것
			그 방향의 값이 0일 때나 크기가 같은 물고기면, 보드에 이동한 거리를 써주면 된다. 전보드에 써진 값 + 1
			if 작은 물고기면 e_f 늘려주고, if e_f 가 sizee 와 같으면 sharksize++ 해주고 , e_f는 다시 0으로 바꿔준다, 그 보드의 숫자값을 0으로 바꿔준다.
			if 큰 물고기면 continue;
			que.push(nx,ny);
		그러면서 우선순위 큐에 닿을 때까지 
	
	*/
	while (true) {
		checkp_f();
		if (que3.empty()) break;

		foradd = make_pair(sx, sy);
		que.push(foradd);


		while (!que.empty()) {

			/*연산*/
			//생각해보면, 추가되는 건 여러갠데 큐는 하나씩만 팝되면, 무한반복이나 마찬가지다. 그러므로 이 안에 어떠한 탈출 조건이 있어야한다. break;
			// 여기 문제의 경우에는 그것이 먹을 수 있는 물고기가 더 이상 없을 때라는 조건이 된다.
			int tx = que.front().first;
			int ty = que.front().second;
			
			mc(tx, ty);
			
			que.pop();

			if (iseat == 1) {
				while (!que.empty()) que.pop();
				iseat = 0;
				resultdist = resultdist + mindist;
				mindist = 0;
				break;
			}



		}
	}

	cout << resultdist;
	system("pause");
	/*
	for(int i =0 ; i < 4;i++){
	mc(sx+dx[i],sy+dy[i]);
	while (!que.empty()) {
	mc(que.front().first, que.front().second);
	}
	}*/
}