#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include <string>
#include <cstring>
using namespace std;
int arr[21][21] = { 0, };
int check5[21][21]= { 0, };
int bfs_check[21][21] = { 0, };
int answer = 987654321;

int x, y, d1, d2, N;
int x2, y2, x3, y3, x4, y4;
typedef pair <int, int> Pair_int;
queue <Pair_int> que;
vector <int> sum;
int temp_sum = 0;
/*
O(10^8)

x = 2, y = 4, d1= 2, d2 = 2로 해서 한번 구현해보기.



*/
int dx[4] = {1,1,-1,-1};
int dy[4] = {-1,1,1,-1};
/*
좌아래 우아래 우위 좌위
좌 우 위 아래
(1,1) (1, 2)
(2,1) (2, 2)
*/
int b_dx[4] = {0,0,-1,1};
int b_dy[4] = {-1,1,0,0};

/*
nx가 x-1,ny 가 y-1 의 좌표가 아니여야함. + x+d1,y+d2+1가 아니여야함,  check[nx][ny]가 5가 아니여야함
각 좌표가 x+d1-1,y+d2+1  가 아니여야함,맨 우측모서리 +1가 아니여야함.
맨우측좌표x+1,맨우측좌표y+1 / 맨 위 좌표x,맨 위 좌표y-1가 아니여야함
맨위좌표x+1,y-1 / 맨좌좌표x-1,y 가 아니여야함.

*/
void enter() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}

}
void bfs(int xx,int yy,int cnt) { //통제값 x,y

	while(!que.empty()){
		Pair_int front = que.front();
		que.pop();
		int bx = front.first;
		int by = front.second;
//		cout << "찍는다 " << endl;
//		cout << "초깃값 bx:" << bx << "by:" << by << endl;
	
		bfs_check[bx][by] = cnt;
		
		for(int i = 0 ; i < 4 ; i ++){
			int nx = bx + b_dx[i];
			int ny = by + b_dy[i];
			if (nx >= 1 && ny >= 1 && nx <= N && ny <= N) {
//				cout << "첫번째 이프" << nx << " " << ny << endl;
				if (nx != xx && ny != yy) {
//					cout << "두번째 이프" << nx << " " << ny << endl;
					if (check5[nx][ny] != 1&&bfs_check[nx][ny] ==0) {
//						cout << " 들어간다 " << endl;
						//cout << nx << " " << ny << endl;
						que.push({ nx,ny });
					}
				}
			}
		}
		

	}
}
void debug() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << bfs_check[i][j] << " ";
		}cout << endl;
	}
}

int main() {
	enter();
	int breakee = 0;
	for (int x = 1; x <= N; x++) {//O(20)
		for(int y = 1 ; y<= N; y++){ // O(20)
			if (y == 1||y==N|| x== N|| x == N-1) continue;
			for (int d1 = 1; d1 <= N - 2; d1++) { //O(20)
				if (y - d1 < 1) continue;
				for (int d2 = 1; d2 <= N- 2; d2++) {//O(20)
					if (x + d1 + d2 > N) continue;
					if (y + d2 > N) continue;

					
					for (int i = 1; i <= 20; i++) {
						memset(check5[i], 0, 21*sizeof(int));
						memset(bfs_check[i], 0, 21* sizeof(int));
					}
					sum.clear();
					/*
					int arr[21][21] = { 0, };
					int check5[21][21] = { 0, };
					int bfs_check[21][21] = { 0, };
					int answer = 987654321;
					*/

					//cout << x << " " << y <<" " << d1 << " " << d2 << endl;


					check5[x][y] = 1;
					int n_x = x;
					int n_y = y;

					for (int i = 0; i < d1; i++) {
						n_x = n_x + dx[0];
						n_y = n_y + dy[0];
						check5[n_x][n_y] = 1;
					}
					x2 = n_x;
					y2 = n_y;
					for (int i = 0; i < d2; i++) {
						n_x = n_x + dx[1];
						n_y = n_y + dy[1];
						check5[n_x][n_y] = 1;
					}
					x3 = n_x;
					y3 = n_y;

					for (int i = 0; i < d1; i++) {
						n_x = n_x + dx[2];
						n_y = n_y + dy[2];
						check5[n_x][n_y] = 1;
					}
					x4 = n_x;
					y4 = n_y;

					for (int i = 0; i < d2; i++) {
						n_x = n_x + dx[3];
						n_y = n_y + dy[3];
						check5[n_x][n_y] = 1;
					}

					que.push({ x,y - 1 });
					bfs(x2, y + 1, 1);
	


					que.push({ x,y + 1 });
					bfs(x4 + 1, y, 2);

					que.push({ x2 + 1,y2 });
					bfs(x2 - 1, y3, 3);

					que.push({ x4 + 1,y4  });
					bfs(x4, y3 - 1, 4);


					for(int k = 0 ; k < 5; k++){
						int t_sum = 0;
						for (int i = 1; i <= N; i++) {
							for (int j = 1; j <= N; j++) {
								if (bfs_check[i][j] == k) {
									t_sum += arr[i][j];
								}
							}
						}

						sum.push_back(t_sum);
					}

				

			//		debug();
			//		cout << endl;
			//		cout << endl;
			//		cout << endl;
			//		cout << sum[0] << " " << sum[1] << " " << sum[2] << " " << sum[3] << " " << sum[4] << endl;
					sort(sum.begin(), sum.end(), less<int>());
					if (answer > sum[4] - sum[0]) {
						answer = sum[4] - sum[0];
					
				//		cout << answer << endl;
					}




				}
			}
		}
	}
	cout << answer;
	system("pause");
}