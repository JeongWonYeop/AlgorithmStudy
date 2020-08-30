#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <functional>
#include <utility>
using namespace std;
int N;
int board[50][50] = { 0, };
int checked[50][50] = { 0, };
int L;
int R;
int dx[4] = {0,0,-1,1};
int dy[4] = {-1,1,0,0};
int yunhab[2501] = { 0, };
int temp_sum = 0;
int temp = 0;
int is_end = 0;
/*
��/��/��/�Ʒ�
00 01
10 11

*/
typedef pair <int, int>  Pair_int;

queue <Pair_int> x_y;
/*
ex 4x4
	üũ.
		���μ��κ� �˻�� ���������� �����ֵ�, ���󰹼�,�α��� ������ ����. �ߺ����� �������� �ʰ� ����.
	
	��������.
	o o o x
	o o o x
	o o o x
	o o o x

	��������
	o o o o
	o o o o
	o o o o
	x x x x 
	
	�ð����� : 10^ 8 * 2
	BFS
	�̹� checked �̸�, ť�� �߰���������,
	checked �ȵ������鼭, L,R ���� ���̸� ����+1 , ť�� �߰�.
	checekd �ȵ������鼭, L,R ���� ���̸� ������ �����ϰ� , ť�� �߰�.
*/



void enter() {
	cin >> N>>L>>R;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}
}
int abs(int a) {
	if (a < 0) return a * -1;
	else return a;
}
void debug() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << checked[i][j] << " ";
		}cout << endl;
	}
	cout << endl;
	cout << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << board[i][j] << " ";
		}cout << endl;
	}
}
///��ɳ�������, ������������.
//��� ȯ���� ����϶�. ȯ�� ������ �ǻ缱�ð� ����. ���ε� �𸣴� �ǻ缱���� ������ ��¦���� ����(���)�϶�.

void BFS() {
	while(!x_y.empty()){
		Pair_int front = x_y.front();
		int bx = front.first;
		int by = front.second;
		++temp;
		temp_sum = temp_sum + board[bx][by];
		
		for(int i  = 0 ; i < 4; i++){
			int nx = bx + dx[i];
			int ny = by + dy[i];
			if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
				if (checked[nx][ny] == 0) {
					if (abs(board[bx][by] - board[nx][ny]) >= L && abs(board[bx][by] - board[nx][ny]) <= R) {
						checked[nx][ny] = checked[bx][by];
						x_y.push({ nx,ny });
						is_end = 1;
					}
				}
			}
			else continue;
		}

		x_y.pop();
	}
}
int main() {
	enter();
	int sum = 0;
	while(true){
		is_end = 0;
		int Number_yunhab = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				checked[i][j] = 0;
			}
		}
		for(int i = 0 ; i < N; i++){//50
			for(int j = 0 ; j < N; j++){//50
				if(checked[i][j] == 0){
					Number_yunhab = Number_yunhab + 1;
					x_y.push({ i,j });
					checked[i][j] = Number_yunhab;
					temp = 0;
					temp_sum = 0;
					BFS();
					yunhab[Number_yunhab] = temp_sum / temp;
//					cout << yunhab[Number_yunhab] << endl;
//					cout << Number_yunhab << endl;
				}
			}
		}
		if (is_end == 0) break;
		++sum;
		for (int i = 0; i < N; i++) {//50
			for (int j = 0; j < N; j++) {//50
				for (int k = 1; k <= Number_yunhab; k++) {//2500
					if (checked[i][j] == k) {
						board[i][j] = yunhab[k];
					}
				}
			}
		}


//		debug();
	}
	cout << sum;
	system("pause");
}