#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <utility>
#include <queue>
#include <vector>
#include <functional>
#include <string.h>
using namespace std;

typedef pair<int, int> Pair_int;
/*
	0.5��
	1�￡ 1��. = 10 ^ 8 = 100000000
*/
int r, c, k;
int A[101][101];
int copy_A[101][101];
int b_r = 3;
int b_c = 3;
int check[101];
struct cmp {
	bool operator()(Pair_int a, Pair_int b) {
		
		if (a.first == b.first) {
			return a.second < b.second;
		}
		else return a.first < b.first;
	}
};

priority_queue <Pair_int,vector<Pair_int>,cmp> p_queue;
void enter() {
	cin >> r >> c >> k;

	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			int temp;
			cin >> temp;
			A[i][j] = temp;
		}
	}
}

void R_cal() {
	//�������迭�ʱ�ȭ
	for (int i = 1; i <= b_r; i++) {
		memcpy(copy_A[i], A[i], sizeof(int)*b_c+1); //sizeof(int)*b_c+1�� 4�ε�, �׷��߸� 0~3���� ���ڸ� ī���Ѵ�.
	}
	for (int i = 1; i <= b_r; i++) {
		memset(A[i],0, sizeof(int)*b_c+1); //memset�� memcpy�� ������ ������ size�� 0 ���� �ش� size���� �� ũ�⸦ COPY or SET �ϴ� ���̴�.
	}										// 4�� 0~3

	for (int i = 1; i <= b_r; i++) {
		memset(check, 0, sizeof(check));
		for (int j = 1; j <= b_c; j++) {
			if (copy_A[i][j] == 0) {
				break;
			}
			else if (check[copy_A[i][j]] == 1) {
				continue; 
			}
			int su = copy_A[i][j];
			int deung_jang = 1;
			if(j+1 <= 100 && j+1 <=b_c){
				for (int k = j+1; k <= b_c; k++) {
					if (copy_A[i][k] == su) {
						++deung_jang;
						check[su] = 1;
					}
				}
			}
			p_queue.push({ su,deung_jang });
			cout << "push(��,����)" << su << " " << deung_jang << endl;
		}
		int c = 1;
		while (!p_queue.empty()) {
			Pair_int temp = p_queue.top();
			A[i][c++] = temp.first;
			A[i][c++] = temp.second;
			p_queue.pop();
		}
		if (--c > b_c) {
			b_c = c;
		}


	}
}

void C_cal() {


}

int main() {
	enter();
	R_cal();
	for (int i = 1; i <= b_r; i++) {
		for (int j = 1; j <= b_c; j++) {
			cout << A[i][j] << " ";
		}cout << endl;
	}
	system("pause");
}