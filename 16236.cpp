#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <utility>
using namespace std;


/*
1. �� �ݺ����� üũ-> ���� �� �ִ� ����Ⱑ �ִ°�. ������ ����.
2. �ִٸ� Ÿ����.(��ǥ ��ȯ)
3. �� �� �ִ� '���� ���ٸ�' ����.
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
//�� ���� �� �Ʒ�
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

	/*ť �߰����ֱ�*/
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
					cout << "������� ��ġ" << nx << ", " << ny << "���� ���µ�" << dist[nx][ny] << "��ŭ�� �ð��� �ɷȴ�." << endl;
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
	/*ť �� */



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
		���� �� �ִ� ����� ���� �Լ� : ����� ũ��� �����ؼ� ���� �� �ִ� ����� ��ȸ�ϰ� �װŸ� Ư�� �켱������ ���� ť�� �־��. -> 1 
		�ش� ����� ť�� �� ��������� ����.
		�װ� �ƴϸ� �ݺ��ϴµ� �� �ݺ��ϳ��ϸ�,
		bfs�� �ݺ���.
			bfs�Լ� : �׹������� ���������鼭 , ���� �� ä���ְ�, �������� �ݺ��ǳĸ�, �켱����ť�� �� �տ� [x][y]�� ������ �� ����. ���±����� �̵��Ÿ� + ���� ������ �� �̵��� �Ÿ�
			�� �������� �� ��
			�� ������ ���� 0�� ���� ũ�Ⱑ ���� ������, ���忡 �̵��� �Ÿ��� ���ָ� �ȴ�. �����忡 ���� �� + 1
			if ���� ������ e_f �÷��ְ�, if e_f �� sizee �� ������ sharksize++ ���ְ� , e_f�� �ٽ� 0���� �ٲ��ش�, �� ������ ���ڰ��� 0���� �ٲ��ش�.
			if ū ������ continue;
			que.push(nx,ny);
		�׷��鼭 �켱���� ť�� ���� ������ 
	
	*/
	while (true) {
		checkp_f();
		if (que3.empty()) break;

		foradd = make_pair(sx, sy);
		que.push(foradd);


		while (!que.empty()) {

			/*����*/
			//�����غ���, �߰��Ǵ� �� �������� ť�� �ϳ����� �˵Ǹ�, ���ѹݺ��̳� ����������. �׷��Ƿ� �� �ȿ� ��� Ż�� ������ �־���Ѵ�. break;
			// ���� ������ ��쿡�� �װ��� ���� �� �ִ� ����Ⱑ �� �̻� ���� ����� ������ �ȴ�.
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