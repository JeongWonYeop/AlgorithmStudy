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
����� �����ϼ��� ������ �������ش�.
������ ����°� �߿��ϴ�.
��,�Ʒ�,��,��
1 2 3 4


��� ������ ���࿡ �� ���.
�����ġ - 1 == (5-1) == 4 < 20(���ǵ�)
������ȯ �� ���,
6 - �����ġ == 6 - 1 == 5 < 20-4(���ǵ�)
������ȯ ��
�����ġ - 1 == 6 - 1 == 5 <(20-4)-5
���� ��
6- �����ġ == 6 - 1 == 5 < ((20-4)-5)-5
���� ��
�����ġ - 1 == 6 - 1 == 5 > (((20-4)-5)-5)-5 =1
����״��. ��, �����ġ���� ���ش�. 6-1 = 5

----------------------------------------------------

��� ������ ���࿡ �� ���.
�����ġ - 1 == (5-1) == 4 < 8(���ǵ�)
������ȯ �� ���,
6 - �����ġ == 6 - 1 == 5 > 8-4(���ǵ�)
����״�� ��, 8-4�� �����ġ���� �����ش�. --> 1+4

----------------------------------------------------

��� ������ ���࿡ �� ���.
�����ġ - 1 == (5-1) == 4 < 11(���ǵ�)
������ȯ �� ���,
6 - �����ġ == 6 - 1 == 5 < 11-4(���ǵ�)
����״�� ��, 8-4�� �����ġ���� �����ش�. --> 1+4
�¶��,
�����ġ - 1 == 6 - 1 == 5 > 11-4-5
����״�� '��', --> �����ġ���� ���ش� 6 - 2 = '4'

��� ������ ���� �¶��,
���ǵ尡 3�̶��,
�����ġ -1 == 4-1[��������ǥ] == 3 >= 3 ���, ��.
	4-3 = 1 ����״��.
�ƴ϶�� ����ٲ��, ex) ���ǵ� 8. �����ġ-1==5-1 == 3 < 8
	8- 3�� ����, 6[������ǥ]- �����ġ == 6-1 == 5 >= 5 ���. ��
		��. �����ġ ���ϱ� 5 == 6.


		ó���� ������ �¶��, �����ġ - 1 �Ѵ���, �װ� ���࿡ ���ǵ庸�� >= �ϸ� ��. �����ġ - ���ǵ�. ��.
			�װ� �ƴϸ�,�����ġ-1 ��ŭ�� ���ǵ忡�� ���ش�. �״���, �� ���ǵ带 ������
			������ǥ - ��ó����ǥ �� / ���� ������ ��, 0�ϰ�� ����ٲ��. �����ġ+%�Ѱ�.
														1�ϰ�� ����״�ΰ�. �����ġ���� % �� ���� ���ش�.

		
		ó���� ������ ����, ���� - �����ġ �Ѵ���, �װ� ���� ���ǵ庸�� >= �ϸ� ��. �����ġ + ���ǵ�. ��.
			�װ� �ƴϸ�, ����-�����ġ ��ŭ�� ���ǵ忡�� ���ش�. �״���, �� ���ǵ带 ������
			������ǥ - ��ó����ǥ ��  / ���� ������ ��, 0�ϰ�� ����ٲ��. �����ġ���� % �� ���� ���ش�.
														1�ϰ�� ����״�ΰ�, �����ġ+%�Ѱ�.
														
														
		ó���� ������ �����,  �����ġ - 1[��ó��] �Ѵ���, �װ� ���࿡ ���ǵ庸�� >= �ϸ� ��. �����ġ - ���ǵ�. ��.
			�װ� �ƴϸ�,�����ġ-1 ��ŭ�� ���ǵ忡�� ���ش�. �״���, �� ���ǵ带 ������
			������ǥ - ��ó����ǥ �� / ���� ������ ��, 0�ϰ�� ����ٲ��. �����ġ+%�Ѱ�.
														1�ϰ�� ����״�ΰ�. �����ġ���� % �� ���� ���ش�.


		ó���� ������ �Ʒ����, �ೡ - �����ġ �Ѵ���, �װ� ���� ���ǵ庸�� >= �ϸ� ��. �����ġ + ���ǵ�. ��.
			�װ� �ƴϸ�, ����-�����ġ ��ŭ�� ���ǵ忡�� ���ش�. �״���, �� ���ǵ带 ������
			������ǥ - ��ó����ǥ ��  / ���� ������ ��, 0�ϰ�� ����ٲ��. �����ġ���� % �� ���� ���ش�.
														1�ϰ�� ����״�ΰ�, �����ġ+%�Ѱ�.





*/
int shark_position[101][101] = { 0, };
int shark_size[101][101] = { 0, };
int shark_speed[101][101] = { 0, };
int shark_orient[101][101] = { 0, }; //1�� 2�Ʒ� 3�� 4��
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
				if (shark_orient[i][j] == 1) {//��,�Ʒ�,��,��
					cout << "��" << endl;
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
					cout << "��" << endl;
					/*
					ó���� ������ ����, ���� - �����ġ �Ѵ���, �װ� ���� ���ǵ庸�� >= �ϸ� ��. �����ġ + ���ǵ�. ��.
					�װ� �ƴϸ�, ����-�����ġ ��ŭ�� ���ǵ忡�� ���ش�. �״���, �� ���ǵ带 ������
					������ǥ - ��ó����ǥ ��  / ���� ������ ��, 0�ϰ�� ����ٲ��. �����ġ���� % �� ���� ���ش�.
					1�ϰ�� ����״�ΰ�, �����ġ+%�Ѱ�.
														
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
							if (evenn(t_shark_speed / (C - 1))) {//¦��
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
							else { //Ȧ���� ��
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
					cout << "��" << endl;
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
					ó���� ������ �¶��, �����ġ - 1 �Ѵ���, �װ� ���࿡ ���ǵ庸�� >= �ϸ� ��. �����ġ - ���ǵ�. ��.
					�װ� �ƴϸ�,�����ġ-1 ��ŭ�� ���ǵ忡�� ���ش�. �״���, �� ���ǵ带 ������
					������ǥ - ��ó����ǥ �� / ���� ������ ��, 0�ϰ�� ����ٲ��. �����ġ+%�Ѱ�.
					1�ϰ�� ����״�ΰ�. �����ġ���� % �� ���� ���ش�.

		
				
														
					ó���� ������ �����,  �����ġ - 1[��ó��] �Ѵ���, �װ� ���࿡ ���ǵ庸�� >= �ϸ� ��. �����ġ - ���ǵ�. ��.
					�װ� �ƴϸ�,�����ġ-1 ��ŭ�� ���ǵ忡�� ���ش�. �״���, �� ���ǵ带 ������
					������ǥ - ��ó����ǥ �� / ���� ������ ��, 0�ϰ�� ����ٲ��. �����ġ+%�Ѱ�.
					1�ϰ�� ����״�ΰ�. �����ġ���� % �� ���� ���ش�.


					ó���� ������ �Ʒ����, �ೡ - �����ġ �Ѵ���, �װ� ���� ���ǵ庸�� >= �ϸ� ��. �����ġ + ���ǵ�. ��.
					�װ� �ƴϸ�, ����-�����ġ ��ŭ�� ���ǵ忡�� ���ش�. �״���, �� ���ǵ带 ������
					������ǥ - ��ó����ǥ ��  / ���� ������ ��, 0�ϰ�� ����ٲ��. �����ġ���� % �� ���� ���ش�.
					1�ϰ�� ����״�ΰ�, �����ġ+%�Ѱ�.

				
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