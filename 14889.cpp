#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include <string.h>
using namespace std;
int board[20][20] = { 0, };
int checked[20] = { 0, };
int NUM[20] = { 0, };
vector <int> f_team;
vector <int> s_team;
int N;
int ans = 987654321;
int sum_f_team = 0;
int sum_s_team = 0;
vector <int> a;
/*
	해당 행 열 중 한번씩 사용한 행,열은 중복해서 사용불가함.
	S01+S10 - S21+S12 이건 안된다는말. 1이 지금 중복으로 사용됐으니까.

*/
int min(int a, int b) {
	if (a > b)return b;
	else return a;
}
int abs(int a) {
	if (a < 0) return a*-1;
	else return a;
}
void enter() {
	cin >> N;
	for (int i = 0; i < N; i++) {//O(400)
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}
}
void combination(int n) {
	// 0과1을 저장 할 벡터 생성
	vector<int> ind;

	// k=2, 2개를 뽑으니까
	int k = 2;

	// k개의 1 추가
	for (int i = 0; i<k; i++) {
		ind.push_back(1);
	}

	// n-k의 0 추가
	for (int i = 0; i<n - k; i++) {
		ind.push_back(0);
	}

	// 정렬
	sort(ind.begin(), ind.end());

	//순열
	do {
		// 출력
		a.clear();
		for (int i = 0; i<ind.size(); i++) {
			if (ind[i] == 1) {
				a.push_back(i);
			}
		}
//		cout << "a[0] : " <<a[0] <<"a[1] :  "<< a[1] << endl;

		sum_f_team = sum_f_team + board[f_team[a[0]]][f_team[a[1]]] + board[f_team[a[1]]][f_team[a[0]]];
		sum_s_team = sum_s_team + board[s_team[a[0]]][s_team[a[1]]] + board[s_team[a[1]]][s_team[a[0]]];
//		cout << "첫번째팀: "<<sum_f_team <<" 두번째팀: " <<sum_s_team << endl;

	} while (next_permutation(ind.begin(), ind.end()));
}

void start() {

	vector<int> ind;
	int k = N / 2;
	for (int i = 0; i < k; i++) {
		ind.push_back(1);
	}
	for (int i = 0; i < N - k; i++) {
		ind.push_back(0);
	}
	sort(ind.begin(), ind.end());

	do {
		memset(checked, 0, sizeof(checked));
		for (int i = 0; i<ind.size(); i++) {
			if (ind[i] == 1) {
				checked[i] = 1;
			}
		}

		f_team.clear();
		s_team.clear();

		for (int i = 0; i < N; i++) {
			if (checked[i] == 0) {
				f_team.push_back(i);
				//				cout << "f_team에 들어갑니다 값 : " << i << endl;
			}
			else {
				s_team.push_back(i);
				//				cout << "s_team에 들어갑니다 값 : " << i << endl;
			}
		}
		sum_f_team = 0;
		sum_s_team = 0;
		combination(N / 2);
		ans = min(ans, abs(sum_f_team - sum_s_team));

	} while (next_permutation(ind.begin(),ind.end()));



}


int main() {
	enter();
	start();
	cout << ans;
	system("pause");
}