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
	<int,int> ����[n][n] = �ش� ��ǥ�� ���� �ȿ��� ����� n��°������ ����. 

	<int, int>����[n] = n�� ���� ��ǥ.
	�ش� ���͸� �̿��ؼ� 1��° �����̰� 2��° �����̰�.


*/
int N, K;
int board[13][13] = { 0, };//board[0]�� ������.
int target_sum[13][13] = { 0, };
vector<Pair_int> board_info[13][13];
vector<Pair_int> target_x_y ;
int END = 0;
int ANSWER = 987654321;
int dx[5] = {-999,0,0,-1,1}; // [0]�� ������.
int dy[5] = {-999,1,-1,0,0};
/*
�� �� �� �Ʒ�
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

	target_x_y.push_back({ 0,0 }); //0�� ������.
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
						//�� �� �� �Ʒ�
		cin >> temp_x >> temp_y >> temp_orient;
		target_sum[temp_x][temp_y]++;
		board_info[temp_x][temp_y].push_back({ i,temp_orient });
		/*
		1 1 1��°���� �����̵�
		2 3 2��°���� �����̵�
		3 1 3��°���� �����̵�
		4 2 4��°���� �����̵�
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
	�� 1ȸ)
	1~K����
	1��ǥ �����ؼ�. �ش� ���忡�� 1�� ã��������, �ش� ������ �˾Ƴ� ����. �ش� ���� ���󰡺��� ��/��/�� ����.



	�̵��Ѱ� ������̸�, 
		�Ųٷ��ؼ� �Ѱ��ְ�

	�̵��Ѱ� �ĺ���̸�,
		����reverse �Ѵ��� �׹������� �̵��϶�.
		���࿡ �̵��ߴµ� �װ͵� �ĺ���̸�
			�ٽ� ���϶�.

	�̵��Ѱ� �����̸�,
		�Ѱ����.

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
			//cout << "turn�� �� :" <<turn << endl;
			int xx = (*i).first;
		//	cout << "xx :" << xx << endl;
			int yy = (*i).second;
		//	cout << "yy :" << yy << endl;
			int pos = find_num(board_info[xx][yy], turn);
		//	cout<<pos<<endl;
		//	cout << "��ġ :" << pos << endl;
			int Num = board_info[xx][yy][pos-1].first;
			int Orient = board_info[xx][yy][pos-1].second;
		//	cout << "Num :" << Num << endl;
	//	cout << "Orient :" << Orient << endl;
			int n_xx = xx + dx[Orient];
		//	cout << "n_xx : " << n_xx << endl;
			int n_yy = yy + dy[Orient]; 
		//	cout << "n_yy : " << n_yy << endl;
			if (n_xx >= 1 && n_xx <= N && n_yy >=1 && n_yy <=N){
				if (board[n_xx][n_yy] == 0) { //���
					for (vector <Pair_int>::iterator j = board_info[xx][yy].begin() + pos - 1; j < board_info[xx][yy].end(); j++) {
						board_info[n_xx][n_yy].push_back({(*j).first,(*j).second});
						target_sum[n_xx][n_yy] ++;
						target_sum[xx][yy]--;
						if (is_End(n_xx, n_yy) == 1) {
							END = 1;
							break;
						};
						//cout << "���� ? -- 2" << endl;
						for (int k = 1; k < target_x_y.size(); k++) {
							if ((*j).first == k) {
 								target_x_y[k].first = n_xx;
								target_x_y[k].second = n_yy;
							}
						}
					}
					board_info[xx][yy].erase(board_info[xx][yy].begin()+ pos - 1, board_info[xx][yy].end());
					if (END == 1) break;
				}else if (board[n_xx][n_yy] == 1) { //������ 0  1  2  3
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
				//	cout << "���� ? ? ? 5 "<< endl;
					board_info[xx][yy].erase(board_info[xx][yy].begin() + pos - 1, board_info[xx][yy].end());
					if (END == 1) break;
				}
				else { // �Ķ��� 
					n_xx = xx + dx[reverse(Orient)];
					n_yy = yy + dy[reverse(Orient)];
					board_info[xx][yy][pos - 1].second = reverse(board_info[xx][yy][pos - 1].second);
					if (board[n_xx][n_yy] == 2 || n_xx>N || n_yy>N ||n_xx <1 ||n_yy<1) {
					}
					else if (board[n_xx][n_yy] == 1) { //������ 0  1  2  3
							
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
					else if (board[n_xx][n_yy] == 0) { //���

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
					else if (board[n_xx][n_yy] == 1) { //������ 0  1  2  3
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
					else if (board[n_xx][n_yy] == 0) { //���
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

	playturn(); //1000�� �ʰ��Ǹ� -1
	if (ANSWER == 987654321) {
		cout << -1;
	}
	else {
		cout << ANSWER;
	}
	system("pause");
}