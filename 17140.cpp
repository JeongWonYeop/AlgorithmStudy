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
	0.5초
	1억에 1초. = 10 ^ 8 = 100000000
*/
int r, c, k;
int A[101][101];
int copy_A[101][101];
int b_r = 3;
int b_c = 3;
int check[101];
struct cmp {
	bool operator()(Pair_int a, Pair_int b) { 
		if (a.second == b.second) {
			return a.first > b.first;
		}

		return a.second > b.second;

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
	//이차원배열초기화
//	cout << "R연산" << endl;
	for (int i = 1; i <= b_r; i++) {
		memcpy(copy_A[i], A[i], sizeof(int)*b_c+1); //sizeof(int)*b_c+1는 4인데, 그래야만 0~3까지 인자를 카피한다.
	}
	for (int i = 1; i <= b_r; i++) {
		memset(A[i],0, sizeof(int)*b_c+1); //memset과 memcpy의 마지막 인자인 size는 0 부터 해당 size까지 의 크기를 COPY or SET 하는 것이다.
	}										// 4면 0~3

	for (int i = 1; i <= b_r; i++) {
		memset(check, 0, sizeof(check));
		for (int j = 1; j <= b_c; j++) {
			if (copy_A[i][j] == 0) {
				continue;
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
	//		cout << "push(수,등장)" << su << " " << deung_jang << endl;
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
	//이차원배열초기화
//	cout << "C연산" << endl;
	for (int i = 1; i <= b_r; i++) {
		memcpy(copy_A[i], A[i], sizeof(int)*b_c + 1); //sizeof(int)*b_c+1는 4인데, 그래야만 0~3까지 인자를 카피한다.
	}
	for (int i = 1; i <= b_r; i++) {
		memset(A[i], 0, sizeof(int)*b_c + 1); //memset과 memcpy의 마지막 인자인 size는 0 부터 해당 size까지 의 크기를 COPY or SET 하는 것이다.
	}										// 4면 0~3
	for (int i = 1; i <= b_c; i++) {
		memset(check, 0, sizeof(check));
		for (int j = 1; j <= b_r; j++) {
			if (copy_A[j][i] == 0) {
				continue;
			}
			else if (check[copy_A[j][i]] == 1) {
				continue;
			}
			int su = copy_A[j][i];
			int deung_jang = 1;
			if (j + 1 <= 100 && j + 1 <= b_r) {
				for (int k = j + 1; k <= b_r; k++) {
					if (copy_A[k][i] == su) {
						++deung_jang;
						check[su] = 1;
					}
				}
			}
			p_queue.push({ su,deung_jang });
//			cout << "push(수,등장)" << su << " " << deung_jang << endl;
		}
		int r = 1;
		while (!p_queue.empty()) {
			Pair_int temp = p_queue.top();
			A[r++][i] = temp.first;
			A[r++][i] = temp.second;
			p_queue.pop();
		}
		if (--r > b_r) {
			b_r = r;
		}


	}

}

int main() {
	enter();
	int time = 0;
	while (A[r][c] != k) {
		++time;
		if (time > 100) {
			time = -1;
			break;
		}
		if (b_r >= b_c) {
			R_cal();
		}
		else C_cal();

		/*
		for (int i = 1; i <= b_r; i++) {
			for (int j = 1; j <= b_c; j++) {
				cout << A[i][j] << " ";
			}cout << endl;
		}
		*/
	}
	cout << time;
	system("pause");
}