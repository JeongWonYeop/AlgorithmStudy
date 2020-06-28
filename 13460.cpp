#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

char board[10][10] = { NULL, };
int min = 987654321;
// �� : 0 , �� : 1 , �� : 2, �Ʒ� : 3
int dx[4] = {0,0,-1,1};
int dy[4] = {-1,1,0,0};
int N, M;
int Rxx, Ryy;
int Bxx, Byy;

void enterNum() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
			if (board[i][j] == 'R')
			{
				Rxx = i;
				Ryy = j;
				board[i][j] = '.';
			}
			if (board[i][j] == 'B')
			{
				Bxx = i;
				Byy = j;
				board[i][j] = '.';
			}
		}
	}

}
int change(int a) {
	if (a == 0) return 1;
	if (a == 1) return 0;
	if (a == 2) return 3;
	if (a == 3) return 2;

}
int abs(int a) {
	if (a < 0) {
		return a = -1 * a;
	}
	return a;
}

int minn(int A, int B) {
	cout << "min �۾���..." << endl;
	if (A <= B) {
		return A;
	}
	else if (B < A) {
		return B;
	}
}

void algo(int Rx,int Ry, int Bx,int By,int cnt,int orient) {
	if (orient == 0) {
		cout << "<<����>>" << endl;
	}
	else if (orient == 1) {
		cout << "<<������>>" << endl;
	}
	else if (orient == 2) {
		cout << "<<����>>" << endl;
	}
	else cout << "<<�Ʒ���>>" << endl;

	if (cnt > min) return;
	if (cnt > 10)  return;
	int redflag = 0;
	int blueflag = 0;
	int NRx = Rx + dx[orient];
	int NRy = Ry + dy[orient];
	int NBx = Bx + dx[orient];
	int NBy = By + dy[orient];
	while (board[NRx][NRy] != '#') {
		if (board[NRx][NRy] == 'O') {
			redflag = 1;
			break;
		}
		NRx = NRx + dx[orient];
		NRy = NRy + dy[orient];
	}
	NRx = NRx - dx[orient];
	NRy = NRy - dy[orient];
	cout << "R��ġ :"<< NRx <<" "<< NRy << endl;

	while (board[NBx][NBy] != '#') {
		if (board[NBx][NBy] == 'O') {
			blueflag = 1;
			break;
		}
		NBx = NBx + dx[orient];
		NBy = NBy + dy[orient];
	}
	NBx = NBx - dx[orient];
	NBy = NBy - dy[orient];
	cout <<"B��ġ :" << NBx <<" "<< NBy << endl;
	if (redflag == 1 && blueflag == 0) {
		min = minn(min, cnt);
		cout << "min �۾� ��ħ" <<min << endl;
		return;
	}
	if (NRx == NBx && NRy == NBy) {
		cout << "������" << endl;
		if (abs((Rx - NRx) + (Ry - NRy)) > abs((Bx - NBx) + (By - NBy))) {
			NRx = NRx - dx[orient];
			NRy = NRy - dy[orient];
		}
		else {
			NBx = NBx - dx[orient];
			NBy = NBy - dy[orient];
		}
	}
	cout << "cnt ��" << cnt << endl;
	cnt++;
	for(int i = 0 ; i<4; i++){
		if (i == orient) continue;
		if (i == change(orient)) continue;
		algo(NRx, NRy, NBx, NBy, cnt, i);
	}
}





int main() {
	enterNum();
	for(int i = 0 ; i<4; i++){
		algo(Rxx,Ryy,Bxx,Byy,1,i);
	}
	if (min == 987654321) cout << -1;
	cout << min;
	system("pause");
}