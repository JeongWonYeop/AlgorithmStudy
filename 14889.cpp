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
	�ش� �� �� �� �ѹ��� ����� ��,���� �ߺ��ؼ� ���Ұ���.
	S01+S10 - S21+S12 �̰� �ȵȴٴ¸�. 1�� ���� �ߺ����� �������ϱ�.

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
	// 0��1�� ���� �� ���� ����
	vector<int> ind;

	// k=2, 2���� �����ϱ�
	int k = 2;

	// k���� 1 �߰�
	for (int i = 0; i<k; i++) {
		ind.push_back(1);
	}

	// n-k�� 0 �߰�
	for (int i = 0; i<n - k; i++) {
		ind.push_back(0);
	}

	// ����
	sort(ind.begin(), ind.end());

	//����
	do {
		// ���ss
		//vector <int> a(2, 0);
		//vector�� ������ü�� �ʱ�ȭ ���Ե� ��. 2ĭ��ŭ �ʱ�ȭ�Ѵ�ð�
		for (int i = 0; i<ind.size(); i++) {
			if (ind[i] == 1) {
				a.push_back(i);
			}
		}
		cout << "a[0] : " <<a[0] <<"a[1] :  "<< a[1] << endl;
//		sum_f_team = sum_f_team + board[f_team[f]][f_team[s]] + board[f_team[s]][f_team[f]];
//		sum_s_team = sum_s_team + board[s_team[f]][s_team[s]] + board[s_team[s]][s_team[f]];
		cout << "ù��°��: "<<sum_f_team <<" �ι�°��: " <<sum_s_team << endl;

	} while (next_permutation(ind.begin(), ind.end()));
}

void dfs(int cnt) {
	if (cnt == N/2) {
		vector<int> f_team(N / 2, 0);
		vector<int> s_team(N / 2, 0);
		for (int i = 0; i < N; i++) {
			if (checked[i] == 0) {
				f_team.push_back(i);
				cout << "f_team�� ���ϴ� �� : " << i << endl;
			}
			else {
				s_team.push_back(i);
				cout << "s_team�� ���ϴ� �� : " << i << endl;
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
		cout <<"NUM["<<cnt<<"] ���� :"<< i << endl;
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