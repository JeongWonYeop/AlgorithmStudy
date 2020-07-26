#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
using namespace std;

int map[20][20] = { 0, };
queue <int> que;
typedef pair<int, int> Intpair;
int squareinfo[7] = { 0, };
int temp[7] = { 0, };
Intpair square; //������ �ֻ��� ��ġ
int dx[5] = {999,0,0,-1,1};//X,��,��,��,��
int dy[5] = {999,1,-1,0,0};
int N, M, r, c, K;
/*
00 01
10 11
*/
/*
�ֻ����� ���⺰�� ���� �� ����.
�����󿡼� ���� �ֻ����� ��ġ�� ǥ�����ִ� �� ����.
�ֻ����� �ٴڸ�� �������� ��ü ����.
�ð����� : 10^8*2              10^7 *10(���갹��) ���
*/
void debug() {
	cout << "  " << squareinfo[5] << " "<<endl;
	cout << squareinfo[1] << squareinfo[2] << squareinfo[3] << squareinfo[4] << endl;
	cout << "  " << squareinfo[6] << " " << endl;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout<<map[i][j]<<" ";
		}cout << endl;
	}cout << endl;
}


void enter() {
	cin >> N >> M >> r >> c >> K; //K= 1000, N,M =20
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
	square = make_pair(r, c);
	squareinfo[3] = map[square.first][square.second];
	cout << square.first << " " << square.second << " " << map[square.first][square.second];
	map[square.first][square.second] = 0;
	for (int i = 0; i < K; i++) {//10^3
		int orient_num;
		cin >> orient_num;
		que.push(orient_num);
	}
}

void play(int orient) {
	r = r + dx[orient];
	c = c + dy[orient];
	if (r<0 || c<0 || r>N - 1 || c>M - 1) return;
	/*
	1:��
	2:��
	3:��
	4:��
	��� �ڷᱸ������ �� ������ ����� ��� �Ұ��ΰ�?
	�迭�� �ᵵ����.
	    
	    5
	1 2 3 4
	    6
		
	index = 1 : ����
	index = 2 : ���ʸ�
	index = 3 : �ٴڸ�
	index = 4 : �����ʸ�
	index = 5 : �޸�
	index = 6 : �ո�
	index ����
	�ٲ�κ� : ����κ�
	���� : 3:2 2:1 1:4 4:3
	������ : 3:4 2:3 1:2 4:1
	���� : 3:5 2:2 1:6 4:4 5:1 6:3
	�Ʒ��� : 3:6 2:2 1:5 4:4 5:3 6:1
	*/

	for (int i = 0; i < 7; i++) {
		temp[i] = squareinfo[i];
	}

	
	if (orient == 1) {
		
		squareinfo[3] = temp[2];
		squareinfo[2] = temp[1];
		squareinfo[1] = temp[4];
		squareinfo[4] = temp[3];
	}
	else if (orient == 2) {
		squareinfo[3] = temp[4];
		squareinfo[2] = temp[3];
		squareinfo[1] = temp[2];
		squareinfo[4] = temp[1];
	}
	else if (orient == 3) {
		squareinfo[3] = temp[5];
		squareinfo[1] = temp[6];
		squareinfo[5] = temp[1];
		squareinfo[6] = temp[3];
	}
	else {
		squareinfo[3] = temp[6];
		squareinfo[1] = temp[5];
		squareinfo[5] = temp[3];
		squareinfo[6] = temp[1];
	}

	/*
	�̵��� ĭ�� ���� �ִ� ���� 0�̸�, �ֻ����� �ٴڸ鿡 ���� �ִ� ���� ĭ�� ����ȴ�. 
	0�� �ƴ� ��쿡�� ĭ�� ���� �ִ� ���� �ֻ����� �ٴڸ����� ����Ǹ�, ĭ�� ���� �ִ� ���� 0�� �ȴ�.
	*/
	if (map[r][c] == 0) {
		map[r][c] = squareinfo[3];
	}
	else {
		squareinfo[3] = map[r][c];
		map[r][c] = 0;
	}



	//for debug
	debug();

	cout << squareinfo[1] << endl;


}


int main() {
	enter();
	while (!que.empty()) {
		int orient = que.front();
		play(orient);
		que.pop();
	}
	system("pause");
}