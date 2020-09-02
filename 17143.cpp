#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <utility>
#include <functional>
using namespace std;

/*
어려운 문제일수록 기준을 안정해준다.
기준을 만드는게 중요하다.
위,아래,우,좌
1 2 3 4


상어 방향이 만약에 좌 라면.
상어위치 - 1 == (5-1) == 4 < 20(스피드)
방향전환 우 라면,
6 - 상어위치 == 6 - 1 == 5 < 20-4(스피드)
방향전환 좌
상어위치 - 1 == 6 - 1 == 5 <(20-4)-5
방향 우
6- 상어위치 == 6 - 1 == 5 < ((20-4)-5)-5
방향 좌
상어위치 - 1 == 6 - 1 == 5 > (((20-4)-5)-5)-5 
방향그대로. 좌, 상어위치에서 빼준다. 6-1 = 5

----------------------------------------------------

상어 방향이 만약에 좌 라면.
상어위치 - 1 == (5-1) == 4 < 8(스피드)
방향전환 우 라면,
6 - 상어위치 == 6 - 1 == 5 > 8-4(스피드)
방향그대로 우, 8-4를 상어위치에서 더해준다. --> 1+4

----------------------------------------------------

상어 방향이 만약에 좌 라면.
상어위치 - 1 == (5-1) == 4 < 11(스피드)
방향전환 우 라면,
6 - 상어위치 == 6 - 1 == 5 < 11-4(스피드)
방향그대로 우, 8-4를 상어위치에서 더해준다. --> 1+4
좌라면,
상어위치 - 1 == 6 - 1 == 5 > 11-4-5
방향그대로 '좌', --> 상어위치에서 빼준다 6 - 2 = '4'


*/
int shark_position[101][101] = { 0, };
int shark_size[101][101] = { 0, };
int shark_speed[101][101] = { 0, };
int shark_orient[101][101] = { 0, };
int R, C, M;


void enter() {
	cin >> R >> C >> M;
	for (int i = 0; i < M; i++) {
		int r,c,s,d,z;
		cin >> r>> c>>s>>d>>z;
		shark_position[r][c]++;
		shark_speed[r][c] = s;
		shark_orient[r][c] = d;
		shark_size[r][c] = z;
	}
}

void debug() {
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cout << shark_position[i][j] << " ";
		}cout << endl;
	}

}

int main() {
	enter();
	debug();
	system("pause");
}