#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <utility>
#include <functional>
using namespace std;
typedef pair<int, int> Pair_int;

/*
	<int,int> 벡터[n][n] = 해당 좌표의 벡터 안에는 방향과 n번째말인지 정보. 

	<int, int>벡터[n] = n인 말의 좌표.
	해당 벡터를 이용해서 1번째 움직이고 2번째 움직이고.


*/
int N, K;
int board[13][13] = { 0, };//board[0]은 사용안함.
int target_sum[13][13] = { 0, };
vector<Pair_int> board_info[13][13];
vector<Pair_int> target_x_y ;
int END = 0;
int ANSWER = 987654321;
int dx[5] = {-999,0,0,-1,1}; // [0]은 사용안함.
int dy[5] = {-999,1,-1,0,0};
/*
우 좌 위 아래
0 0 / 0 1
1 0 / 1 1

*/
int reverse(int index) {
	if (index == 1) return 2;
	else if (index == 2) return 1;
	else if (index == 3)return 4;
	else {
		return 3;
	}
}
void enter() {

	target_x_y.push_back({ 0,0 }); //0은 사용안함.
	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
		}
	}

	for (int i = 1; i <= K; i++) {
		int temp_x;
		int temp_y;
		int temp_orient;//1  2  3   4 
						//우 좌 위 아래
		cin >> temp_x >> temp_y >> temp_orient;
		target_sum[temp_x][temp_y]++;
		board_info[temp_x][temp_y].push_back({ i,temp_orient });
		/*
		1 1 1번째말이 우측이동
		2 3 2번째말이 위쪽이동
		3 1 3번째말이 우측이동
		4 2 4번째말이 좌측이동
		*/
		target_x_y.push_back({ temp_x,temp_y });
		/*
			target_x_y[0]
		*/
	}

}
void debug() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << target_sum[i][j] << " ";
		}cout << endl;
	}
	cout << endl << endl;
}


/*
	턴 1회)
	1~K까지
	1좌표 추적해서. 해당 보드에서 1을 찾은다음에, 해당 방향을 알아낸 다음. 해당 방향 따라가봐서 빨/파/흰 구분.



	이동한게 빨블록이면, 
		거꾸로해서 넘겨주고

	이동한게 파블록이면,
		방향reverse 한다음 그방향으로 이동하라.
		만약에 이동했는데 그것도 파블록이면
			다시 빽하라.

	이동한게 흰블록이면,
		넘겨줘라.

*/
int is_End(int xx,int yy) {
	if (target_sum[xx][yy] == 4) return 1;
	else return 0;
}
int find_num(vector <Pair_int> &a,int num) {
	int return_num = 0;
	for (vector<Pair_int> ::iterator i = a.begin(); i < a.end(); i++) {//O(10)
		return_num++;
		if ((*i).first == num) {
			return return_num;
		}
	}
}

void playturn() {
	int cnt = 0;

	while (true) {//1000
		int turn = 1;
		cnt++;
		//cout << "----------CNT :" << cnt << "---------" << endl;
		for (vector <Pair_int>::iterator i = target_x_y.begin() + 1; i < target_x_y.end(); i++) { //O(10)
			//cout << "turn의 값 :" <<turn << endl;
			int xx = (*i).first;
		//	cout << "xx :" << xx << endl;
			int yy = (*i).second;
		//	cout << "yy :" << yy << endl;
			int pos = find_num(board_info[xx][yy], turn);
		//	cout<<pos<<endl;
		//	cout << "위치 :" << pos << endl;
			int Num = board_info[xx][yy][pos-1].first;
			int Orient = board_info[xx][yy][pos-1].second;
		//	cout << "Num :" << Num << endl;
	//	cout << "Orient :" << Orient << endl;
			int n_xx = xx + dx[Orient];
		//	cout << "n_xx : " << n_xx << endl;
			int n_yy = yy + dy[Orient]; 
		//	cout << "n_yy : " << n_yy << endl;
			if (n_xx >= 1 && n_xx <= N && n_yy >=1 && n_yy <=N){
				if (board[n_xx][n_yy] == 0) { //흰색
					for (vector <Pair_int>::iterator j = board_info[xx][yy].begin() + pos - 1; j < board_info[xx][yy].end(); j++) {
						board_info[n_xx][n_yy].push_back({(*j).first,(*j).second});
						target_sum[n_xx][n_yy] ++;
						target_sum[xx][yy]--;
						if (is_End(n_xx, n_yy) == 1) {
							END = 1;
							break;
						};
						//cout << "여기 ? -- 2" << endl;
						for (int k = 1; k < target_x_y.size(); k++) {
							if ((*j).first == k) {
 								target_x_y[k].first = n_xx;
								target_x_y[k].second = n_yy;
							}
						}
					}
					board_info[xx][yy].erase(board_info[xx][yy].begin()+ pos - 1, board_info[xx][yy].end());
					if (END == 1) break;
				}else if (board[n_xx][n_yy] == 1) { //빨간색 0  1  2  3
					for (vector <Pair_int>::iterator j = board_info[xx][yy].end()-1; j >= board_info[xx][yy].begin()+ pos-1; j--) {

						board_info[n_xx][n_yy].push_back({ (*j).first,(*j).second });
						target_sum[n_xx][n_yy] ++;
						target_sum[xx][yy]--;
						if (is_End(n_xx, n_yy) == 1) {
							END = 1;
							break;
						};

						for (int k = 1; k < target_x_y.size(); k++) {
							if ((*j).first == k) {
				//				cout << k << endl;
				//				cout << n_xx << " " << n_yy << endl;
								target_x_y[k].first = n_xx;
								target_x_y[k].second = n_yy;
							}
						}
						if (j == board_info[xx][yy].begin() + pos - 1) break;
					}
				//	cout << "여기 ? ? ? 5 "<< endl;
					board_info[xx][yy].erase(board_info[xx][yy].begin() + pos - 1, board_info[xx][yy].end());
					if (END == 1) break;
				}
				else { // 파란색 
					n_xx = xx + dx[reverse(Orient)];
					n_yy = yy + dy[reverse(Orient)];
					board_info[xx][yy][pos - 1].second = reverse(board_info[xx][yy][pos - 1].second);
					if (board[n_xx][n_yy] == 2 || n_xx>N || n_yy>N ||n_xx <1 ||n_yy<1) {
					}
					else if (board[n_xx][n_yy] == 1) { //빨간색 0  1  2  3
							
							for (vector <Pair_int>::iterator j = board_info[xx][yy].end() - 1; j >= board_info[xx][yy].begin() + pos - 1; j--) {
							board_info[n_xx][n_yy].push_back({ (*j).first,(*j).second });
							target_sum[n_xx][n_yy] ++;
							target_sum[xx][yy]--;
							if (is_End(n_xx, n_yy) == 1) {
								END = 1;
								break;
							};
			
							for (int k = 1; k < target_x_y.size(); k++) {
								if ((*j).first == k) {
									target_x_y[k].first = n_xx;
									target_x_y[k].second = n_yy;
								}
							}
							if (j == board_info[xx][yy].begin() + pos - 1) break;
						}
						board_info[xx][yy].erase(board_info[xx][yy].begin() + pos - 1, board_info[xx][yy].end());
						if (END == 1) break;
					}
					else if (board[n_xx][n_yy] == 0) { //흰색

					//	cout << n_xx << " " << n_yy << endl;
						for (vector <Pair_int>::iterator j = board_info[xx][yy].begin() + pos - 1; j < board_info[xx][yy].end(); j++) {
							board_info[n_xx][n_yy].push_back({ (*j).first,(*j).second });
							target_sum[n_xx][n_yy] ++;
							target_sum[xx][yy]--;
							if (is_End(n_xx, n_yy) == 1) {
								END = 1;
								break;
							};


							for (int k = 1; k < target_x_y.size(); k++) {
								if ((*j).first == k) {
									target_x_y[k].first = n_xx;
									target_x_y[k].second = n_yy;
								}
							}

						
						}
						board_info[xx][yy].erase(board_info[xx][yy].begin() + pos - 1, board_info[xx][yy].end());
						if (END == 1) break;
					}
				}
			}
			else {
					n_xx = xx + dx[reverse(Orient)];
					n_yy = yy + dy[reverse(Orient)];
					board_info[xx][yy][pos - 1].second = reverse(board_info[xx][yy][pos - 1].second);
				
					if (board[n_xx][n_yy] == 2) {
					}
					else if (board[n_xx][n_yy] == 1) { //빨간색 0  1  2  3
						for (vector <Pair_int>::iterator j = board_info[xx][yy].end() - 1; j >= board_info[xx][yy].begin() + pos - 1; j--) {
							board_info[n_xx][n_yy].push_back({ (*j).first,(*j).second });
							target_sum[n_xx][n_yy] ++;
							target_sum[xx][yy]--;
							if (is_End(n_xx, n_yy) == 1) {
								END = 1;
								break;
							};
				
							for (int k = 1; k < target_x_y.size(); k++) {
								if ((*j).first == k) {
									target_x_y[k].first = n_xx;
									target_x_y[k].second = n_yy;
								}
							}
							if (j == board_info[xx][yy].begin() + pos - 1) {
								(*j).second = reverse(board_info[xx][yy][pos - 1].second);
								break;
							}
						}
						board_info[xx][yy].erase(board_info[xx][yy].begin() + pos - 1, board_info[xx][yy].end());
						if (END == 1) break;
					}
					else if (board[n_xx][n_yy] == 0) { //흰색
						for (vector <Pair_int>::iterator j = board_info[xx][yy].begin() + pos - 1; j < board_info[xx][yy].end(); j++) {
							board_info[n_xx][n_yy].push_back({ (*j).first,(*j).second });
							target_sum[n_xx][n_yy] ++;
							target_sum[xx][yy]--;
				//			cout << board_info[xx][yy][pos - 1].second << endl;
							if (is_End(n_xx, n_yy) == 1) {
								END = 1;
								break;
							};
						
							for (int k = 1; k < target_x_y.size(); k++) {
								if ((*j).first == k) {
									target_x_y[k].first = n_xx;
									target_x_y[k].second = n_yy;
								}
							}
						}
						board_info[xx][yy].erase(board_info[xx][yy].begin() + pos - 1, board_info[xx][yy].end());
						if (END == 1) break;
					}
				
			}

		
			//debug();
			turn++;
		}
		if (END == 1) {
			ANSWER = cnt;
			break;
		}
		if (cnt > 1000) break;
	}


}


int main() {
	enter();

	//debug();

	playturn(); //1000번 초과되면 -1
	if (ANSWER == 987654321) {
		cout << -1;
	}
	else {
		cout << ANSWER;
	}
	system("pause");
}