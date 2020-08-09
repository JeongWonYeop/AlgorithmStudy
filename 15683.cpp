#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <queue>
#include <functional>
#include <utility>
#include <cstring>
using namespace std;
int dx[4] = {0,0,-1,1};
int dy[4] = {-1,1,0,0};
int N, M;
int board[8][8];
int checked[8][8];
int copy_checked[8][8];

int ans = 987654321;


/*
00 01
10 11
*/
/*
	좌표와 방향을 찍어주면 해당 방향으로 CCTV를 비추는 함수 하나.
		CCTV(1~5)은 통과되고,
		벽은 막힌다.
	DFS,백트래킹으로 풀거고, vector==end()이면은 checked이용해서 최소인 값 최신화&&return, 
	갔다가 와서는 checked를 가기전 상태 만들어주기.
		각 층마다 copy_checked가 있어야겠다.
	1번의 경우 4가지(포문) 갔다와서는 이전의 보드판으로 바꿔줘야해.(N,M 최대 8이니까 시간복잡도 그렇게 안커)
	사각지대 합 구해주는 함수 하나.
*/
typedef struct Info{
	int x;
	int y;
	int v; //cctv_value
}Info;

vector <Info> vec_cctv;


//orient : 0:좌 , 1:우 , 2:위 , 3:아래
void detect(int x, int y, int orient) {
	int nx = x + dx[orient];
	int ny = y + dy[orient];
	if (nx >= 0 && ny >= 0 && nx < N&&ny < M) {
		if (board[nx][ny] == 6) return;
		if (board[nx][ny] == 1 || board[nx][ny] == 2 || board[nx][ny] == 3 || board[nx][ny] == 4 || board[nx][ny] == 5) {
			detect(nx, ny, orient);
			return;
		}
		checked[nx][ny] = -1;
		detect(nx, ny, orient);
	}

}
int min(int a,int b) {
	if (a < b) return a;
	else return b;
}
void ex_cctv() {
	int temp_ans = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (checked[i][j] == 0) {
				++temp_ans;
			}
		}
	}

	ans = min(ans, temp_ans);
}



void debug() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << checked[i][j] << " ";
		}cout << endl;
	}
	cout << endl;
}
void DFS(vector <Info>::iterator iter, int depth) {
	if (iter == vec_cctv.end()) {
//		debug();
		ex_cctv();
		return;
	}
	int x, y, cctv_num;
	x = (*iter).x;
	y = (*iter).y;
	cctv_num = (*iter).v;
//	cout << "CCTV번호 : "<<(*iter).v << endl;

	memcpy(copy_checked, checked, sizeof(checked));
	switch (cctv_num) {
	case 1:
		for (int i = 0; i < 4; i++) {
			vector <Info>::iterator temp_iter = iter;
			detect(x, y, i);
			DFS(++temp_iter,depth+1);
			memcpy(checked, copy_checked, sizeof(copy_checked));
		}
		break;
	case 2:

		for(int i = 0 ; i<2; i++){
			vector <Info>::iterator temp_iter = iter;
			if(i == 0){
				detect(x, y, 0);
				detect(x, y, 1);
			}
			else {
				detect(x, y, 2);
				detect(x, y, 3);
			}
			DFS(++temp_iter,depth+1);
			memcpy(checked, copy_checked, sizeof(copy_checked));
		}
		break;
	case 3:
		//0:좌 1:우 2:위 3:아래

		for (int i = 0; i < 4; i++) {
			vector <Info>::iterator temp_iter = iter;
			if (i == 0) {//위,우
				detect(x, y, 2);
				detect(x, y, 1);
			}
			else if (i == 1) {//우,아래
				detect(x, y, 1);
				detect(x, y, 3);
			}
			else if (i == 2) {//아래,좌
				detect(x, y, 3);
				detect(x, y, 0);
			}
			else {//좌,위
				detect(x, y, 0);
				detect(x, y, 2);
			}
			DFS(++temp_iter,depth+1);
			memcpy(checked, copy_checked, sizeof(copy_checked));
		}
		break;
	case 4:
	
		//0:좌 1:우 2:위 3:아래
		for (int i = 0; i < 4; i++) {
			vector <Info>::iterator temp_iter = iter;
			if (i == 0) {//좌,위,우
				detect(x, y, 0);
				detect(x, y, 1);
				detect(x, y, 2);
			}
			else if (i == 1) {//위,우,아래
				detect(x, y, 1);
				detect(x, y, 2);
				detect(x, y, 3);
			}
			else if (i == 2) {//우,아래,좌
				detect(x, y, 1);
				detect(x, y, 3);
				detect(x, y, 0);
			}
			else {//아래,좌,위
				detect(x, y, 3);
				detect(x, y, 0);
				detect(x, y, 2);
			}
			DFS(++temp_iter,depth+1);
			memcpy(checked, copy_checked, sizeof(copy_checked));
		}
		break;
	case 5:
		vector <Info>::iterator temp_iter = iter;
		detect(x, y, 0);
		detect(x, y, 1);
		detect(x, y, 2);
		detect(x, y, 3);
		DFS(++temp_iter,depth+1);
		memcpy(checked, copy_checked, sizeof(copy_checked));
		break;

	}





}


void enter() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
			if(board[i][j] > 0&& board[i][j]<6){
				vec_cctv.push_back({ i,j,board[i][j] });
				checked[i][j] = -1;
			}
			if(board[i][j] == 6) checked[i][j] = -1;
		}
	}
}


int main() {
	enter();
	DFS(vec_cctv.begin(),0);
	cout << ans;
	system("pause");
}