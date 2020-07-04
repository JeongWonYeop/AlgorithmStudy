#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <utility>
#include<string.h>
#include <vector>
#include <algorithm>
using namespace std;


/*
���Ǿ������� checked[][]���� ũ�� �迭 �־�߰ڴ�.
���� �˻��ϴ� �Լ�.
���� �˻��ϴ� �Լ�.
*/
int board[50][50];
int checked[50][50] = { 0, };
int L;
int N;
//����:0 �Ʒ���:1
int dx[2] = {0,1};
int dy[2] = {1,0};
int endd;
int cnt = 0;
/*
	0.�� ������ ��� cnt ++;
	
	�� ������ ���� �� ����.
	���ʿ����� �Լ��� �� �� ������ֱ� ����.

	1.���翭���� �������� Ŀ���� ��
	1-1.�������̰� 1���� ũ�� continue;
	1-2.�׿� : 1�̸�
	for( int k = 0; k < L ; k++){
		if(i-k < 0) endd = 1;
		if(checked[i-k] == 1)endd = 1;
	}
	//�� ��������� check ���ֱ�
	for( int k = 0; k < L ; k++){
		checked[i-k] = 1;
	}


	2.���翭���� �������� �۾����� ��
	2-1.�������̰� 1���� ũ�� continue;
	2-2. �׿� : 1�̸�
	checked[i+1]�� 1�̸� continue;
	for( int k = 0; k < L ; k++){
	if(i+ (k+1) >= N) return 0;
	if(checked[i+(k+1)] == 1)return 0;
	}
	//�� ��������� check ���ֱ�
	for( int k = 0; k < L ; k++){
	checked[i+(k+1)] = 1;
	}
	
	
	*/

void rowcheck2(int rx, int ry) {
	int nx = rx + dx[0];
	int ny = ry + dy[0];
	if (board[rx][ry] == board[nx][ny]) return;
	if (board[rx][ry] < board[nx][ny]){
		if (board[nx][ny] - board[rx][ry] > 1) { endd = 1; return; }
		else {
			for (int k = 0; k < L; k++) {
				if (ry - k < 0) { endd = 1; return; }
				if (checked[rx][ry - k] == 1) { endd = 1; return; }
			}
			//�� ��������� check ���ֱ�
			for (int k = 0; k < L; k++) {
				checked[rx][ry - k] = 1;
			}
		}
	}

	if (board[rx][ry] > board[nx][ny]) {
		if (board[rx][ry] - board[nx][ny] > 1) { endd = 1; return; }
		else {
			for (int k = 0; k < L; k++) {
				if (ry + (k + 1)>=N) { endd = 1; return; }
				if (checked[rx][ry + (k + 1)] == 1) { endd = 1; return; }
			}
			//�� ��������� check ���ֱ�
			for (int k = 0; k < L; k++) {
				checked[rx][ry + (k + 1)] = 1;
			}
		}
	}

}
void colcheck2(int rx,int ry) {
	int nx = rx + dx[1];
	int ny = ry + dy[1];
	if (board[rx][ry] == board[nx][ny]) return;
	if (board[rx][ry] < board[nx][ny]) {
		if (board[nx][ny] - board[rx][ry] > 1) { endd = 1; return; }
		else {
			for (int k = 0; k < L; k++) {
				if (rx - k < 0) { endd = 1; return; }
				if (checked[rx-k][ry] == 1) { endd = 1; return; }
			}
			//�� ��������� check ���ֱ�
			for (int k = 0; k < L; k++) {
				checked[rx-k][ry] = 1;
			}
		}
	}

	if (board[rx][ry] > board[nx][ny]) {
		if (board[rx][ry] - board[nx][ny] > 1) { endd = 1; return; }
		else {
			for (int k = 0; k < L; k++) {
				if (rx + (k + 1) >= N) { endd = 1; return; }
				if (checked[rx + (k + 1)][ry] == 1) { endd = 1; return; }
			}
			//�� ��������� check ���ֱ�
			for (int k = 0; k < L; k++) {
				checked[rx + (k + 1)][ry] = 1;
			}
		}
	}

}

void rowcheck() {
	for (int i = 0; i < N; i++) {
		endd = 0;
		for (int j = 0; j < N-1; j++) {
			rowcheck2(i,j);
			if (endd == 1) {
				cout << "���� � : " << i << " " << j << endl;
				break;
			}
		}

		if (endd != 1) {
			++cnt;
			cout << "�����ϴ� �� : " << i<<endl;
		}
	}

}
void colcheck() {
	for (int i = 0; i < N; i++) {
		endd = 0;
		for (int j = 0; j < N-1; j++) {
			colcheck2(j, i);
			if (endd == 1) {
				cout << "���� � : " << j << " " << i << endl;
				break;
			
			}
		}

		if (endd != 1) {
			++cnt;
			cout << "�����ϴ� �� : " << i << endl;
		}

	}
}

void enter() {
	cin >> N >> L;
	for(int i = 0; i < N ; i++){
		for(int j = 0; j< N; j++){
			cin >> board[i][j];
		}
	}
}

int main() {
	enter();
	rowcheck();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j< N; j++) {
			checked[i][j] = 0;
		}
	}
	colcheck();
	cout << cnt;
	system("pause");
}