#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <queue>
using namespace std;

int sizee = 2;
int N;
int space[20][20] = { 0, };
int shark[20][20] = { 0, };
int visited[20][20] = { 0, };
int oindex; // 0 ~ 3
int x[4] = { -1,0,1,0 };
int y[4] = { 0,-1,0,1 };
int s_x, s_y;
int eat = 0;
int minnum = 1000000000;
queue <pair <int, int> > edible;


void enter() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> space[i][j];
		}
	}
}



bool is_block(int xx, int yy) {
	int isblock = 1;
	for (int i = 0; i < 4; i++) {
		if (xx + x[i] == -1 || xx + x[i] == N || yy + y[i] == -1 || yy + y[i] == N)
			continue;
		else if (space[xx + x[i]][yy + y[i]] > sizee)
			continue;
		else isblock = 0;
	}
	return isblock;
}

bool is_possible() {
	int ispossible = 0;
	//size ���� ���� ��� �� ť�� ����.
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (space[i][j] > 0 &&space[i][j] <= sizee) {
				pair <int, int> add;
				add = make_pair(i, j);
				edible.push(add);
				cout << "���հ� ��ġ�̿�" << add.first <<add.second<< endl;
			}
		}
	}

	while (!edible.empty()) { // ��������� 0 ��������� 1
		if (!is_block(edible.front().first, edible.front().second)){
			cout <<"���� ���հ� �ּ�"<< edible.front().first << edible.front().second << endl;
			ispossible = 1;
		}
		edible.pop();
	}

	return ispossible;

}
void find_shark() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (space[i][j] == 9) {
				s_x = i;
				s_y = j;
				return;
			}
		}
	}
}
void dfs(int sizee, int xx,int yy, int count) {
	cout << "[�������]" << count << endl;
	if (is_possible() == 0){
		cout << "��" <<count << endl;
	}
	for (int i = 0; i < 4; i++) {
		if (xx + x[i] != -1 && xx + x[i] < N && yy + y[i] != -1 && yy + y[i] < N && visited[xx + x[i]][yy + y[i]] != 1) {
			if (space[xx + x[i]][yy + y[i]] == 0) {
				cout << "0  ����, ������ġ" << xx << yy<< endl;
				shark[xx + x[i]][yy + y[i]] = 9;
				shark[xx][yy] = 0;
				visited[xx + x[i]][yy + y[i]] = 1;

				dfs(sizee, xx + x[i], yy + y[i], ++count);


			}
			if (space[xx + x[i]][yy + y[i]] == sizee) {
				cout << "���ϻ����� ����" << endl;
				shark[xx + x[i]][yy + y[i]] = 9;
				shark[xx][yy] = 0;
				visited[xx + x[i]][yy + y[i]] = 1;

				dfs(sizee, xx + x[i], yy + y[i], ++count);

			}
			else if (space[xx + x[i]][yy + y[i]]>0 && space[xx + x[i]][yy + y[i]] < sizee) {
				eat = eat + 1;
				if (eat == sizee) { 
					sizee = sizee + 1; 
					eat = 0;
				}
				cout << "���� ������ �Դ� �ܰ� ����" << endl;
				shark[xx + x[i]][yy + y[i]] = 9;
				shark[xx][yy] = 0;
				space[xx + x[i]][yy + y[i]] = 0;
				visited[xx + x[i]][yy + y[i]] = 1;

				dfs(sizee, xx + x[i], yy + y[i], ++count);

			}
		
		}
	}
	visited[xx][yy] = 0;
	cout << xx << yy << "���������ϴ�"<< endl;
}

int main() {
	int result;
	enter();
	find_shark();
	shark[s_x][s_y] = 9;
	space[s_x][s_y] = 0;
	visited[s_x][s_y] = 1;
	dfs(sizee, s_x, s_y,0);
	system("pause");
}