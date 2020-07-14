#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <utility>
#include <functional>
using namespace std;


/*
1. �� �ݺ����� üũ-> ���� �� �ִ� ����Ⱑ �ִ°�. ������ ����.
2. �ִٸ� Ÿ����.(��ǥ ��ȯ)
3. �� �� �ִ� '���� ���ٸ�' ����.
*/
int board[20][20] = { 0, };
int dist[20][20] = { 0, };
int ndist[20][20] = { 0, };
int check_ndist[20][20] = { 0, };
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
priority_queue <pair<int, int>,vector<pair<int,int>>,greater<pair<int,int>>> que3;
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


void checkp_f(int sx, int sy) {
	while (!que4.empty()) {
		que4.pop();
	}
	while (!que3.empty()) {
		que3.pop();
	}
	for (int i = 0; i < sizee; i++) {
		for (int j = 0; j < sizee; j++) {
			ndist[i][j] = 0;
			check_ndist[i][j] = 0;
		}
	}
	que4.push({ sx,sy });
	int minn = 987654321;

	while(!que4.empty()){
		int aa = 0;
		for (int i = 0; i < sizee; i++) {
			for (int j = 0; j < sizee; j++) {
				if (board[i][j] > 0 && board[i][j] < shark_size) {
					aa = 1;
				}
			}
		}
		if (aa == 0) return;
		for(int i = 0 ; i < 4 ; i++){
			int ssx = que4.front().first;
			int ssy = que4.front().second;
			int nsx = que4.front().first + dx[i];
			int nsy = que4.front().second + dy[i];
			
			if (nsx >= 0 && nsy >= 0 && nsx < sizee && nsy < sizee && check_ndist[nsx][nsy] != 1) {
				if (ndist[ssx][ssy] + 1 > minn) return;
			
				if (board[nsx][nsy] == 0) {
					ndist[nsx][nsy] = ndist[ssx][ssy] + 1;
				}
				else if (board[nsx][nsy] == shark_size) {
					ndist[nsx][nsy] = ndist[ssx][ssy] + 1;
				}
				else if (board[nsx][nsy] > shark_size) continue;
				else if (board[nsx][nsy] > 0 && board[nsx][nsy] < shark_size) {
					ndist[nsx][nsy] = ndist[ssx][ssy] + 1;
					que3.push({ nsx,nsy });
				cout << "que3�� �Է�" << nsx << "��" << nsy << endl;
					minn = ndist[nsx][nsy];

				}
				
				for (int i = 0; i < sizee; i++) {
					for (int j = 0; j < sizee; j++) {
						cout << ndist[i][j] << " ";
					}cout << endl;
				}
				cout << endl;
			
				check_ndist[ssx][ssy] = 1;
				que4.push({ nsx,nsy });
				

			}
		}
		que4.pop();
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
				if (nx == que3.top().first && ny == que3.top().second) {
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
//					cout << "������� ��ġ" << nx << ", " << ny << "���� ���µ�" << dist[nx][ny] << "��ŭ�� �ð��� �ɷȴ�." << endl;
					break;
				}
			}
			foradd = make_pair(nx, ny);
			que.push(foradd);
		}
	}

	/*
	for (int i = 0; i < sizee; i++) {
		for (int j = 0; j < sizee; j++) {
			cout << dist[i][j] << " ";
		}cout << endl;
	}
	cout << endl;
	*/




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
		checkp_f(sx,sy);

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
				break;
			}



		}
	}

	cout << mindist;
	system("pause");
	/*
	for(int i =0 ; i < 4;i++){
	mc(sx+dx[i],sy+dy[i]);
	while (!que.empty()) {
	mc(que.front().first, que.front().second);
	}
	}*/
}