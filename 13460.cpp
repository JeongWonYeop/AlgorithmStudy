#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

char board[10][10] = { NULL, };
int minest = 987654321;
// 왼 : 0 , 오 : 1 , 위 : 2, 아래 : 3
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

	if (A <= B) {
		return A;
	}
	else if (B < A) {
		return B;
	}
}

void algo(int Rx,int Ry, int Bx,int By,int cnt,int orient) {


	if (cnt > minest) return;
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

	if (redflag == 1 && blueflag == 0) {
		minest = minn(minest, cnt);

		return;
	}
	//파란 구슬 들어갔을 때, 실패에 대한 언급 없었다. 그게 버그 유발.
	if (blueflag == 1) {
		return;
	}
	if (NRx == NBx && NRy == NBy) {

		if (abs((Rx - NRx) + (Ry - NRy)) > abs((Bx - NBx) + (By - NBy))) {
			NRx = NRx - dx[orient];
			NRy = NRy - dy[orient];
		}
		else {
			NBx = NBx - dx[orient];
			NBy = NBy - dy[orient];
		}
	}

	cnt++;
	for(int i = 0 ; i<4; i++){
		if (i == orient) continue; // 같은 방향으로 한번 더 기울이는 거
		if (i == change(orient)) continue; // 180도 반대방향으로 기울이는거
		algo(NRx, NRy, NBx, NBy, cnt, i);
	}
}





int main() {
	enterNum();
	for(int i = 0 ; i<4; i++){
		algo(Rxx,Ryy,Bxx,Byy,1,i);
	}
	if (minest == 987654321) cout << -1;
	else cout << minest;

}