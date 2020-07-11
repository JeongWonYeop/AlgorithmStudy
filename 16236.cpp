#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;


/*
	1. �� �ݺ����� üũ-> ���� �� �ִ� ����Ⱑ �ִ°�. ������ ����.
	2. �ִٸ� Ÿ����.(��ǥ ��ȯ)
	3. �� �� �ִ� '���� ���ٸ�' ����.
	4. ���� �� �ִ� ����� ť�� ���, �� ��������, �� ��������. �����ϰ�. front�ΰ� ��Ƶα�
	5. ���� �������� �� �ش� ��ǥ���� ��������.
	6. ������ �������� ������ ť ��.
*/
int board[20][20] = { 0, };
int s_p[20][20] = { 0, }; // shark_position ����� ũ��� ��ġ�� ǥ��
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
//�� ���� �� �Ʒ�
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

	
	/*ť �߰����ֱ�
	for (int i = 0; i < 4; i++) {
		int nx = X + dx[i];
		int ny = Y + dy[i];
		if (nx >= 0 && ny >= 0 && nx < sizee && ny < sizee){
			if (board[nx][ny] == 0 || board[nx][ny] < shark_size) {
				foradd = make_pair(nx, ny);
				que2.push(foradd);
				cout << nx << "and "<<ny<<endl;
				cout << "�߰���" << endl;

			}
		}
	}
	*/
	/*ť �� */



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
	�������ִ� ����� ��ġ �˷��ִ� ����
	-> ���� �� �ִ� ����� 0�Ǹ� ���� . �� �ϸ��� üũ
	-> min(cnt,minn) �ֽ�ȭ

	

	while (checkp_f()) {

		while (!que2.empty()) {
			que.push(que2.front());
			que2.pop();
		}



		while (!que.empty()) {

			
			//�����غ���, �߰��Ǵ� �� �������� ť�� �ϳ����� �˵Ǹ�, ���ѹݺ��̳� ����������. �׷��Ƿ� �� �ȿ� ��� Ż�� ������ �־���Ѵ�. break;
			// ���� ������ ��쿡�� �װ��� ���� �� �ִ� ����Ⱑ �� �̻� ���� ����� ������ �ȴ�.
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
				cout << sx << " �������� " << sy << endl;
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