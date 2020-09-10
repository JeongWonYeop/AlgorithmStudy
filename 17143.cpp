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
상어위치 - 1 == 6 - 1 == 5 > (((20-4)-5)-5)-5 =1
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

상어 방향이 만약 좌라면,
스피드가 3이라면,
상어위치 -1 == 4-1[열시작좌표] == 3 >= 3 라면, 끝.
	4-3 = 1 방향그대로.
아니라면 방향바뀌고, ex) 스피드 8. 상어위치-1==5-1 == 3 < 8
	8- 3가 남고, 6[열끝좌표]- 상어위치 == 6-1 == 5 >= 5 라면. 끝
		우. 상어위치 더하기 5 == 6.


		처음에 방향이 좌라면, 상어위치 - 1 한다음, 그게 만약에 스피드보다 >= 하면 끝. 상어위치 - 스피드. 끝.
			그게 아니면,상어위치-1 만큼을 스피드에서 빼준다. 그다음, 그 스피드를 가지고
			열끝좌표 - 열처음좌표 로 / 몫을 구했을 때, 0일경우 방향바뀌고. 상어위치+%한값.
														1일경우 방향그대로고. 상어위치에서 % 한 값을 빼준다.

		
		처음에 방향이 우라면, 열끝 - 상어위치 한다음, 그게 만약 스피드보다 >= 하면 끝. 상어위치 + 스피드. 끝.
			그게 아니면, 열끝-상어위치 만큼을 스피드에서 빼준다. 그다음, 그 스피드를 가지고
			열끝좌표 - 열처음좌표 로  / 몫을 구했을 때, 0일경우 방향바뀌고. 상어위치에서 % 한 값을 빼준다.
														1일경우 방향그대로고, 상어위치+%한값.
														
														
		처음에 방향이 위라면,  상어위치 - 1[행처음] 한다음, 그게 만약에 스피드보다 >= 하면 끝. 상어위치 - 스피드. 끝.
			그게 아니면,상어위치-1 만큼을 스피드에서 빼준다. 그다음, 그 스피드를 가지고
			열끝좌표 - 열처음좌표 로 / 몫을 구했을 때, 0일경우 방향바뀌고. 상어위치+%한값.
														1일경우 방향그대로고. 상어위치에서 % 한 값을 빼준다.


		처음에 방향이 아래라면, 행끝 - 상어위치 한다음, 그게 만약 스피드보다 >= 하면 끝. 상어위치 + 스피드. 끝.
			그게 아니면, 열끝-상어위치 만큼을 스피드에서 빼준다. 그다음, 그 스피드를 가지고
			열끝좌표 - 열처음좌표 로  / 몫을 구했을 때, 0일경우 방향바뀌고. 상어위치에서 % 한 값을 빼준다.
														1일경우 방향그대로고, 상어위치+%한값.





*/
int shark_position[101][101] = { 0, };
int shark_size[101][101] = { 0, };
int shark_speed[101][101] = { 0, };
int shark_orient[101][101] = { 0, }; //1위 2아래 3우 4좌
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
int evenn(int a) {
	if (a % 2 == 0)
		return 1;
	else return 0;
}

void change_orient(int a, int b) {
	if (shark_orient[a][b] == 1) {
		shark_orient[a][b] = 2;
	}
	else if (shark_orient[a][b] == 2) {
		shark_orient[a][b] = 1;
	}
	else if (shark_orient[a][b] == 3) {
		shark_orient[a][b] = 4;
	}
	else if (shark_orient[a][b] == 4) {
		shark_orient[a][b] = 3;
	}
}
void shark_move() {
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (shark_position[i][j] > 0) {
				int t_shark_speed = shark_speed[i][j];
				if (shark_orient[i][j] == 1) {//위,아래,우,좌
					cout << "위" << endl;
					int row = i - 1;
					if (row >= t_shark_speed) {
						shark_position[i][j]--;
						if (shark_position[i - t_shark_speed][j] > 0) {
							if (shark_size[i][j] > shark_size[i - t_shark_speed][j]) {
								shark_size[i - t_shark_speed][j] = shark_size[i][j];
								shark_speed[i - t_shark_speed][j] = shark_speed[i][j];
								shark_position[i - t_shark_speed][j]++;
							}

						}else shark_position[i- t_shark_speed][j]++;
						

						continue;
					}
					else {
						t_shark_speed -= row;
						if (evenn(t_shark_speed / (R - 1))) {
							change_orient(i, j);
							shark_position[i][j]--;
							if (shark_position[1 + t_shark_speed % (R - 1)][j] > 0) {
								if (shark_size[i][j] > shark_size[1 + t_shark_speed % (R - 1)][j]) {
									shark_size[1 + t_shark_speed % (R - 1)][j] = shark_size[i][j];
									shark_speed[1 + t_shark_speed % (R - 1)][j] = shark_speed[i][j];
									shark_position[1 + t_shark_speed % (R - 1)][j]++;
								}

							}else shark_position[1 + t_shark_speed % (R-1)][j]++;
						}
						else {
							shark_position[i][j]--;		
							if (shark_position[R - t_shark_speed % (R - 1)][j] > 0) {
								if (shark_size[i][j] > shark_size[R - t_shark_speed % (R - 1)][j]) {
									shark_size[R - t_shark_speed % (R - 1)][j] = shark_size[i][j];
									shark_speed[R - t_shark_speed % (R - 1)][j] = shark_speed[i][j];
									shark_position[R - t_shark_speed % (R - 1)][j]++;
								}

							}
							else shark_position[R - t_shark_speed % (R-1)][j]++;
						}
					}
				}
				else if (shark_orient[i][j] == 2) {
					int Row = R - i;
					if (Row >= t_shark_speed) {
						shark_position[i][j]--;
						if (shark_position[i + t_shark_speed][j] > 0) {
							if (shark_size[i][j] > shark_size[i + t_shark_speed][j]) {
								shark_size[i + t_shark_speed][j] = shark_size[i][j];
								shark_speed[i + t_shark_speed][j] = shark_speed[i][j];
								shark_position[i + t_shark_speed][j]++;
							}

						}
						else shark_position[i + t_shark_speed][j]++;
						continue;
					}
					else {
						t_shark_speed -= Row;
						if (evenn(t_shark_speed / (R - 1))) {
							change_orient(i, j);
							shark_position[i][j]--;
							if (shark_position[R - t_shark_speed % (R - 1)][j] > 0) {
								if (shark_size[i][j] > shark_size[R - t_shark_speed % (R - 1)][j]) {
									shark_size[R - t_shark_speed % (R - 1)][j] = shark_size[i][j];
									shark_speed[R - t_shark_speed % (R - 1)][j] = shark_speed[i][j];
									shark_position[R - t_shark_speed % (R - 1)][j]++;
								}

							}
							else shark_position[R - t_shark_speed % (R - 1)][j]++;
						}
						else {
							shark_position[i][j]--;
							if (shark_position[1 + t_shark_speed % (R - 1)][j] > 0) {
								if (shark_size[i][j] > shark_size[1 + t_shark_speed % (R - 1)][j]) {
									shark_size[1 + t_shark_speed % (R - 1)][j] = shark_size[i][j];
									shark_speed[1 + t_shark_speed % (R - 1)][j] = shark_speed[i][j];
									shark_position[1 + t_shark_speed % (R - 1)][j]++;
								}

							}
							else shark_position[1 + t_shark_speed % (R - 1)][j]++;
						}
					}
				}
				else if (shark_orient[i][j] == 3) {
					cout << "우" << endl;
					/*
					처음에 방향이 우라면, 열끝 - 상어위치 한다음, 그게 만약 스피드보다 >= 하면 끝. 상어위치 + 스피드. 끝.
					그게 아니면, 열끝-상어위치 만큼을 스피드에서 빼준다. 그다음, 그 스피드를 가지고
					열끝좌표 - 열처음좌표 로  / 몫을 구했을 때, 0일경우 방향바뀌고. 상어위치에서 % 한 값을 빼준다.
					1일경우 방향그대로고, 상어위치+%한값.
														
					*/
					int col = C - j;
						if (col >= t_shark_speed) {
							shark_position[i][j]--;
							if (shark_position[i][j + t_shark_speed] > 0) {
								
								if (shark_size[i][j] > shark_size[i][j + t_shark_speed]) {
									shark_size[i][j + t_shark_speed] = shark_size[i][j];
									shark_speed[i][j + t_shark_speed] = shark_speed[i][j];
									shark_position[i][j + t_shark_speed]++;
								}

							}
							else shark_position[i][j + t_shark_speed]++;
							continue;
						}
						else {
							t_shark_speed -= col;
							if (evenn(t_shark_speed / (C - 1))) {//짝수
								change_orient(i, j);
								shark_position[i][j]--;
								if (shark_position[i][C - t_shark_speed % (C - 1)] > 0) {
									if (shark_size[i][j] > shark_size[i][C - t_shark_speed % (C - 1)]) {
										shark_size[i][C - t_shark_speed % (C - 1)] = shark_size[i][j];
										shark_speed[i][C - t_shark_speed % (C - 1)] = shark_speed[i][j];
										shark_position[i][C - t_shark_speed % (C - 1)]++;
									}

								}
								else shark_position[i][C - t_shark_speed % (C - 1)]++;
							}
							else { //홀수일 때
								shark_position[i][j]--; 
								if (shark_position[i][1 + t_shark_speed % (C - 1)] > 0) {
									if (shark_size[i][j] > shark_size[i][1 + t_shark_speed % (C - 1)]) {
										shark_size[i][1 + t_shark_speed % (C - 1)] = shark_size[i][j];
										shark_speed[i][1 + t_shark_speed % (C - 1)] = shark_speed[i][j];
										shark_position[i][1 + t_shark_speed % (C - 1)]++;
									}

								}
								else shark_position[i][1 + t_shark_speed % (C - 1)]++;
							}
						}


				}else if (shark_orient[i][j] == 4) {
					cout << "좌" << endl;
					int col = j - 1;
					if (col >= t_shark_speed) {
						shark_position[i][j]--;
						if (shark_position[i][j - t_shark_speed] > 0) {
							if (shark_size[i][j] > shark_size[i][j - t_shark_speed]) {
								shark_size[i][j - t_shark_speed] = shark_size[i][j];
								shark_speed[i][j - t_shark_speed] = shark_speed[i][j];
								shark_position[i][j - t_shark_speed]++;
							}

						}
						else shark_position[i][j - t_shark_speed]++;
						continue;
					}
					else {
						t_shark_speed -= col;
						if (evenn(t_shark_speed / (C-1))) {
							change_orient(i,j);
							shark_position[i][j]--;
							if (shark_position[i][1 + t_shark_speed % (C - 1)] > 0) {
								if (shark_size[i][j] > shark_size[i][1 + t_shark_speed % (C - 1)]) {
									shark_size[i][1 + t_shark_speed % (C - 1)] = shark_size[i][j];
									shark_speed[i][1 + t_shark_speed % (C - 1)] = shark_speed[i][j];
									shark_position[i][1 + t_shark_speed % (C - 1)]++;
								}

							}
							else shark_position[i][1 + t_shark_speed % (C-1)]++;
						}
						else {
							shark_position[i][j]--;
							if (shark_position[i][C - t_shark_speed % (C - 1)] > 0) {
								if (shark_size[i][j] > shark_size[i][C - t_shark_speed % (C - 1)]) {
									shark_size[i][C - t_shark_speed % (C - 1)] = shark_size[i][j];
									shark_speed[i][C - t_shark_speed % (C - 1)] = shark_speed[i][j];
									shark_position[i][C - t_shark_speed % (C - 1)]++;
								}

							}
							else shark_position[i][C - t_shark_speed % (C-1)]++;
						}
					}
				}

				/*
					처음에 방향이 좌라면, 상어위치 - 1 한다음, 그게 만약에 스피드보다 >= 하면 끝. 상어위치 - 스피드. 끝.
					그게 아니면,상어위치-1 만큼을 스피드에서 빼준다. 그다음, 그 스피드를 가지고
					열끝좌표 - 열처음좌표 로 / 몫을 구했을 때, 0일경우 방향바뀌고. 상어위치+%한값.
					1일경우 방향그대로고. 상어위치에서 % 한 값을 빼준다.

		
				
														
					처음에 방향이 위라면,  상어위치 - 1[행처음] 한다음, 그게 만약에 스피드보다 >= 하면 끝. 상어위치 - 스피드. 끝.
					그게 아니면,상어위치-1 만큼을 스피드에서 빼준다. 그다음, 그 스피드를 가지고
					열끝좌표 - 열처음좌표 로 / 몫을 구했을 때, 0일경우 방향바뀌고. 상어위치+%한값.
					1일경우 방향그대로고. 상어위치에서 % 한 값을 빼준다.


					처음에 방향이 아래라면, 행끝 - 상어위치 한다음, 그게 만약 스피드보다 >= 하면 끝. 상어위치 + 스피드. 끝.
					그게 아니면, 열끝-상어위치 만큼을 스피드에서 빼준다. 그다음, 그 스피드를 가지고
					열끝좌표 - 열처음좌표 로  / 몫을 구했을 때, 0일경우 방향바뀌고. 상어위치에서 % 한 값을 빼준다.
					1일경우 방향그대로고, 상어위치+%한값.

				
				*/
			}
		}
	}
}
/*
4 6 1
4 1 10 3 0

4 6 1
4 1 10 4 0

4 6 1
4 3 10 2 0

4 6 1
4 1 10 1 0


4 6 8
4 1 3 3 8
1 3 5 2 9
2 4 8 4 1
4 5 0 1 4
3 3 1 2 7
1 5 8 4 3
3 6 2 1 2
2 2 2 3 5
*/
int main() {
	while(true){
		enter();
		debug();

		shark_move();
		debug();
		shark_move();
		debug();
	}
	system("pause");
}