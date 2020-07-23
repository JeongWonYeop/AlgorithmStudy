#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
using namespace std;
int N;
int board[20][20];
int dx[4] = { 0,0,1,-1 };
int dy[4] = { -1,1,0,0 };
/*
00  01
10  11
*/
void slide(int orient) {
	for (int i = 0; i < N-1; i++) {
		int xx = i;
		int nxx = xx++;
		while (!nxx == N - 1) {
			if(board[])
			nxx++;
		}
	}
}

void enter() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}
}


void see() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	/*
	기울이기(방향) 함수
	좌,우,위,아래
		먼저 충돌 (충돌한 블럭은 빈공백, 충돌된 블럭은 숫자*2) 
			이미 한번 합쳐진 블럭인지 검사.
				아니라면 합쳐.== 숫자*2
		그리고나서 빈공백 채워주기.

----------------------------
<백트래킹..? or 배열에 저장하는 방법..?(메모이제이션,dp)>


	다섯번 이동해서 최댓값.DFS
	좌				우				위				아래 O(2^10) => O(10^2)
좌,우,위,아래	좌,우,위,아래	좌,우,위,아래	좌,우,위,아래
	*/


	enter();
	see();
	slide(0);
	system("pause");
}