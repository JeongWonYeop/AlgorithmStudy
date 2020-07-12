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
int s_p[20][20] = { 0, }; // shark_position ����� ũ��� ��ġ�� ǥ��
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
//�� ���� �� �Ʒ�
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


	/*ť �߰����ֱ�*/
	for (int i = 0; i < 4; i++) {
		int nx = X + dx[i];
		int ny = Y + dy[i];
		if (nx >= 0 && ny >= 0 && nx < sizee && ny < sizee) {
			if (board[nx][ny] == 0 || board[nx][ny] < shark_size) {
				foradd = make_pair(nx, ny);
				que2.push(foradd);
				cout << nx << "and " << ny << endl;
				cout << "�߰���" << endl;

			}
		}
	}

	/*ť �� */



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
	�������ִ� ����� ��ġ �˷��ִ� ����
	-> ���� �� �ִ� ����� 0�Ǹ� ���� . �� �ϸ��� üũ
	-> min(cnt,minn) �ֽ�ȭ



	*/
	while (checkp_f()) {

		while (!que2.empty()) {
			que.push(que2.front());
			que2.pop();
		}



		while (!que.empty()) {

			/*����*/
			//�����غ���, �߰��Ǵ� �� �������� ť�� �ϳ����� �˵Ǹ�, ���ѹݺ��̳� ����������. �׷��Ƿ� �� �ȿ� ��� Ż�� ������ �־���Ѵ�. break;
			// ���� ������ ��쿡�� �װ��� ���� �� �ִ� ����Ⱑ �� �̻� ���� ����� ������ �ȴ�.
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