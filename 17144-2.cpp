#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
using namespace std;
int A[50][50];
int checked[50][50] = { 0, };
int temp_cal[50][50] = { 0, };
int dx[4] = {0,0,-1,1};
int dy[4] = {-1,1,0,0};
vector < pair<int,int> > w_m;
typedef pair <int,int> Pair_int;
queue <Pair_int> temp_xy;
int sum = 0;
/*
좌,우,위,아래
00 01
10 11
*/
int R, C, T;
void enter() {
	cin >> R >> C >> T;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> A[i][j];
			if (A[i][j] > 0) {
				checked[i][j] = 1;
			}
			else if (A[i][j] == -1) {
				checked[i][j] = -1;
				w_m.push_back({ i,j });
			}
		}
	}

}

void start() {
	int cnt;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (checked[i][j] == 1) {
				if (A[i][j] / 5 == 0) continue;
				cnt = 0;
				for(int k = 0 ; k <4;k++){
					int n_x = i + dx[k];
					int n_y = j + dy[k];
					if (n_x >= 0 && n_x < R && n_y >= 0 && n_y < C && checked[n_x][n_y] != -1) {
						temp_cal[n_x][n_y] += A[i][j] / 5;
						++cnt;
						temp_xy.push({ n_x,n_y });
					}
;				}
				A[i][j] = A[i][j] - ((A[i][j] / 5) * cnt);
			}
		}
	}

	while (!temp_xy.empty()) {
		Pair_int t_xy;
		t_xy =temp_xy.front();
		checked[t_xy.first][t_xy.second] = 1;
		temp_xy.pop();
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (checked[i][j] == 1) {
				A[i][j] += temp_cal[i][j];
			}
		}
	}

	
}
void initialize() {
	memset(temp_cal, 0, sizeof(temp_cal));
}

void debug() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cout << A[i][j] << " ";
		}cout << endl;
	}
	cout << endl << endl;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cout << checked[i][j] << " ";
		}cout << endl;
	}

}


void wind() {
	/*
	2,0
	"왼쪽을 기준으로"
	2,0 <- 1,0 <- 0,0 
	0,0 <- 0,1 <- 0,2 <- 0,3 <- 0,4 <- 0,5 <- 0,6 <- 0,7
	0,7 <- 1,7 <- 2,7
	2,7 <- 2,6 <- 2,5 <- 2,4 <- 2,3 <- 2,2 <- 2,1 <- 2,0



	*/
	int u_x, u_y, d_x, d_y;
	u_x = w_m[0].first;
	u_y = w_m[0].second;
	d_x = w_m[1].first;
	d_y = w_m[1].second;
//	cout << u_x <<" " <<u_y << endl;
//	cout << d_x << " " << d_y << endl;

	for (int i = u_x; i > 0; i--) {
		A[i][u_y] = A[i - 1][u_y];
		checked[i][u_y] = checked[i - 1][u_y];
	}
	for (int i = 0; i < C-1; i++) {
		A[0][i] = A[0][i + 1];
		checked[0][i] = checked[0][i + 1];
	}
	for (int i = 0; i < u_x; i++) {
		A[i][C - 1] = A[i + 1][C - 1];
		checked[i][C - 1] = checked[i + 1][C - 1];
	}
	for (int i = C - 1; i > 0; i--) {
		if (i == 1) {
			A[u_x][i] = 0;
			checked[u_x][i] = 0;
		}
		else { 
			A[u_x][i] = A[u_x][i - 1];
			checked[u_x][i] = checked[u_x][i - 1];
		}
	}
	A[u_x][u_y] = -1;
	checked[u_x][u_y] = -1;
	/*
	3 0

	3,0 <- 4,0 <- 5,0 <- 6,0 
	6,0 <-6,1 <- 6,2 <- 6,3 <- 6,4 <- 6,5 <- 6,6 <- 6,7
	6,7<- 5,7<-4,7<-3,7
	3,7<- 3,6<-3,5<-3,4<-3,3<-3,2<-3,1<-3,0
	*/
	
	for (int i = d_x; i < R - 1; i++) {
		A[i][0] = A[i + 1][0];
		checked[i][0] = checked[i + 1][0];
	}
	for (int i = 0; i < C - 1; i++) {
		A[R - 1][i] = A[R - 1][i + 1];
		checked[R - 1][i] = checked[R - 1][i + 1];
	}
	for (int i = R - 1; i > d_x; i--) {
		A[i][C - 1] = A[i - 1][C - 1];
		checked[i][C - 1] = checked[i - 1][C - 1];
	}
	for (int i = C - 1; i > 0; i--) {
		if (i == 1) {
			A[d_x][i] = 0;
			checked[d_x][i] = 0;
		}
		else {
			A[d_x][i] = A[d_x][i - 1];
			checked[d_x][i] = checked[d_x][i - 1];
		}
	}
	A[d_x][d_y] = -1;
	checked[d_x][d_y] = -1;


}
void sum_cal() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (checked[i][j] == 1) {
				sum += A[i][j];
			}
		}
	}

}

int main() {
	enter();
	for(int i = 0; i < T; i++){
		initialize();
		start();
		wind();
	}

	sum_cal();
	cout << sum;
	system("pause");
}