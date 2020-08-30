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
int N, M, K;
int A[11][11] = { 0, };
int engergy[11][11] = { 0, };
int result = 0;
int checked[11][11] = { 0, };
int dx[8] = {-1,-1,-1,0,0,1,1,1};
int dy[8] = {-1,0,1,-1,1,-1,0,1};
int season = 1;
/*
00 01 02
10 11 12
20 21 22

*/
typedef pair <int, int> Pair_int;
queue <Pair_int> for_increase;
queue <Pair_int> que;
/*
typedef struct tree {
	int x;
	int y;
	int age;
}Tree;

Tree tree_info[100];


먼저, 한번이라도 언급된 자리에는 checked 를 통해서 체크해두고,
해당 체크해둔 곳을 tree_info로 찾아가는 구성.
tree_info는 벡터이기 때문에, 해당 tree_info[x][y]에는 1개 이상의 값이 담긴다.
그것을 오름차순 정렬하여, 해당 땅의 양분과의 관계를 따져볼 생각.


*/
vector <int> tree_info[11][11];

void enter() {
	cin >> N >> M >> K;
	for (int i = 1; i < N+1; i++) {
		for (int j = 1; j < N+1; j++) {
			cin >> A[i][j];
		}
	}

	int x, y, z;
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> z;
		checked[x][y] = 1;
		tree_info[x][y].push_back(z);
	}
	result = M;
}


void intialization() {
	memset(checked, 0, sizeof(checked));
	result = 0;
}

void make_que() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (checked[i][j] == 1) {
				que.push({i,j});
			}
		}
	}
}

void start() {
	cout << endl;
	cout << season++ << "년이 지난 뒤의 상황" << endl;
	cout << endl;
	while (!que.empty()) {
		Pair_int frontt = que.front();
		int t_x = frontt.first;
		int t_y = frontt.second;
		int t_energy = 0;
		sort(tree_info[t_x][t_y].begin(), tree_info[t_x][t_y].end(), less<int>());
		cout << "현재 양분 : " << engergy[t_x][t_y] << endl;
		for (vector<int> ::iterator iter = tree_info[t_x][t_y].begin(); iter != tree_info[t_x][t_y].end(); ) {
			if (engergy[t_x][t_y] >= *iter) {
				cout << "x : " << t_x << "y : " << t_y << "에 위치한 나무 나이 " << *iter << "가 양분을 먹고 나이 1 먹을 것." << endl;
				engergy[t_x][t_y] = engergy[t_x][t_y] - *iter;

				(*iter)++;
				iter++;
			}else {
				cout << "x : " << t_x << "y : " << t_y << "에 위치한 나무 나이 " << *iter << "가 사망" << endl;
				t_energy = t_energy  + (*iter) / 2;
				iter = tree_info[t_x][t_y].erase(iter);
			}
		}


		engergy[t_x][t_y] = engergy[t_x][t_y] + t_energy;

		if(!tree_info[t_x][t_y].empty()){
		//★★★★★	cout << sizeof(tree_info[t_x][t_y]) << endl; --> tree_info[t_x][t_y].size(); ★★★★★
		//	cout << tree_info[t_x][t_y].size() << endl;
			for (int i = 0; i < tree_info[t_x][t_y].size(); i++) {
				checked[t_x][t_y] = 1;
				if (tree_info[t_x][t_y][i] % 5 == 0) {
					cout << "증식을 시작한다 그 값은 :";
					for_increase.push({ t_x,t_y });
					cout << tree_info[t_x][t_y][i] << endl;
			
				}
			}
		}




		que.pop();
	}
	while(!for_increase.empty()){
		for (int j = 0; j < 8; j++) {
			int n_t_x = for_increase.front().first + dx[j];
			int n_t_y = for_increase.front().second + dy[j];
			if (n_t_x >= 1 && n_t_x <= 10 && n_t_y >= 1 && n_t_y <= 10) {
				//						cout << n_t_x << " " << n_t_y << endl;
				checked[n_t_x][n_t_y] = 1;
				tree_info[n_t_x][n_t_y].push_back(1);
			}
		}
		for_increase.pop();
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			engergy[i][j] = engergy[i][j] + A[i][j];
		}
	}
}
void first_energy() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			engergy[i][j] = 5;
		}
	}
}

void sum_cal(){
	make_que();
	while (!que.empty()) {
		Pair_int frontt = que.front();
		int t_x = frontt.first;
		int t_y = frontt.second;
		result = result + tree_info[t_x][t_y].size();
//		cout << tree_info[t_x][t_y].size() << endl;


		que.pop();
	}

}

int main() {
	enter();
	first_energy();

	for(int i = 0 ; i < K ; i++){
		make_que();
		intialization(); // checked 초기화.
		start();
	}


	sum_cal();
	//debug();
	cout << result;
	system("pause");
}