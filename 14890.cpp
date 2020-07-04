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
사용되었는지를 checked[][]동일 크기 배열 있어야겠다.
행을 검사하는 함수.
열을 검사하는 함수.
*/
int board[50][50];
int checked[50][50] = { 0, };
int L;
int N;
//우측:0 아래측:1
int dx[2] = {0,1};
int dy[2] = {1,0};
int endd;
int cnt = 0;
/*
	0.쭉 일정한 경우 cnt ++;
	
	맨 끝열은 해줄 게 없다.
	앞쪽열에서 함수들어갈 때 다 고려해주기 때문.

	1.현재열보다 다음열이 커졌을 때
	1-1.높이차이가 1보다 크면 continue;
	1-2.그외 : 1이면
	for( int k = 0; k < L ; k++){
		if(i-k < 0) endd = 1;
		if(checked[i-k] == 1)endd = 1;
	}
	//다 통과했으면 check 해주기
	for( int k = 0; k < L ; k++){
		checked[i-k] = 1;
	}


	2.현재열보다 다음열이 작아졌을 때
	2-1.높이차이가 1보다 크면 continue;
	2-2. 그외 : 1이면
	checked[i+1]가 1이면 continue;
	for( int k = 0; k < L ; k++){
	if(i+ (k+1) >= N) return 0;
	if(checked[i+(k+1)] == 1)return 0;
	}
	//다 통과했으면 check 해주기
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
			//다 통과했으면 check 해주기
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
			//다 통과했으면 check 해주기
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
			//다 통과했으면 check 해주기
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
			//다 통과했으면 check 해주기
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
				cout << "몇행 몇열 : " << i << " " << j << endl;
				break;
			}
		}

		if (endd != 1) {
			++cnt;
			cout << "증가하는 행 : " << i<<endl;
		}
	}

}
void colcheck() {
	for (int i = 0; i < N; i++) {
		endd = 0;
		for (int j = 0; j < N-1; j++) {
			colcheck2(j, i);
			if (endd == 1) {
				cout << "몇행 몇열 : " << j << " " << i << endl;
				break;
			
			}
		}

		if (endd != 1) {
			++cnt;
			cout << "증가하는 열 : " << i << endl;
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