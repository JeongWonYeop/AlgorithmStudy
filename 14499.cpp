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
Intpair square; //지도상 주사위 위치
int dx[5] = {999,0,0,-1,1};//X,동,서,북,남
int dy[5] = {999,1,-1,0,0};
int N, M, r, c, K;
/*
00 01
10 11
*/
/*
주사위가 방향별로 구를 때 구현.
지도상에서 현재 주사위의 위치를 표시해주는 것 구현.
주사위의 바닥면과 지도상의 교체 구현.
시간제한 : 10^8*2              10^7 *10(연산갯수) 허용
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
	1:동
	2:서
	3:북
	4:남
	사실 자료구조보다 더 초점은 약속을 어떻게 할것인가?
	배열을 써도되지.
	    
	    5
	1 2 3 4
	    6
		
	index = 1 : 윗면
	index = 2 : 왼쪽면
	index = 3 : 바닥면
	index = 4 : 오른쪽면
	index = 5 : 뒷면
	index = 6 : 앞면
	index 기준
	바뀔부분 : 현재부분
	왼쪽 : 3:2 2:1 1:4 4:3
	오른쪽 : 3:4 2:3 1:2 4:1
	위쪽 : 3:5 2:2 1:6 4:4 5:1 6:3
	아래쪽 : 3:6 2:2 1:5 4:4 5:3 6:1
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
	이동한 칸에 쓰여 있는 수가 0이면, 주사위의 바닥면에 쓰여 있는 수가 칸에 복사된다. 
	0이 아닌 경우에는 칸에 쓰여 있는 수가 주사위의 바닥면으로 복사되며, 칸에 쓰여 있는 수는 0이 된다.
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