#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
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
	for (int i = 0; i < N; i++) {
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
		// 출력ss
		//vector <int> a(2, 0);
		//vector은 선언자체가 초기화 포함된 것. 2칸만큼 초기화한답시고
		for (int i = 0; i<ind.size(); i++) {
			if (ind[i] == 1) {
				a.push_back(i);
			}
		}
		cout << "a[0] : " <<a[0] <<"a[1] :  "<< a[1] << endl;
//		sum_f_team = sum_f_team + board[f_team[f]][f_team[s]] + board[f_team[s]][f_team[f]];
//		sum_s_team = sum_s_team + board[s_team[f]][s_team[s]] + board[s_team[s]][s_team[f]];
		cout << "첫번째팀: "<<sum_f_team <<" 두번째팀: " <<sum_s_team << endl;

	} while (next_permutation(ind.begin(), ind.end()));
}

void dfs(int cnt) {
	if (cnt == N/2) {
		vector<int> f_team(N / 2, 0);
		vector<int> s_team(N / 2, 0);
		for (int i = 0; i < N; i++) {
			if (checked[i] == 0) {
				f_team.push_back(i);
				cout << "f_team에 들어갑니다 값 : " << i << endl;
			}
			else {
				s_team.push_back(i);
				cout << "s_team에 들어갑니다 값 : " << i << endl;
			}
		}
		sum_f_team = 0;
		sum_s_team = 0;
		combination(N/2);
		ans = min(ans, abs(sum_f_team - sum_s_team));
		return;
	}

	for (int i = 0; i < N; i++) {
		if (checked[i] == 1) continue;
		checked[i] = 1;
		NUM[cnt] = i;
		cout <<"NUM["<<cnt<<"] 값은 :"<< i << endl;
		dfs(cnt + 1);
		checked[i] = 0;
 	}

}


int main() {
	enter();
	dfs(0);
	cout << ans;
	system("pause");
}