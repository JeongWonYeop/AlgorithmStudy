#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
#include <string>
#include <cstring>
using namespace std;
int N, M; // 2<= N <= 50, 1<= M <=13
int board[51][51] = { 0, };
int check[51][51] = { 0, };
int checked[51][51] = { 0, }; // 1�� ǥ�õƴ��� ����
bool visited[13];
vector <int> check_home;
typedef pair <int, int> PairInt;
vector <PairInt> vec2;
vector <PairInt> vec1;
vector <int> result;
int dx[4] = {0,0,-1,1};
int dy[4] = {1,-1,0,0};
int M_sum = 0;
int N_cnt = 0;
int ans = 987654321;
/*
	00 01
	10 11
	��,��,��,��

	BFS�� ���ؼ� �������� ��, 1�� ������ŭ ��� 2�� �������� ��. M���� 2������ ���� ��. 
	BFS�� ���ؼ� �������� ��, 1�� ������ŭ ��� 2�� �������� ��. M���� 2������ �� ���� ��. 
		��Ʈ��ŷ �̿��ؼ�, 2���� C M   -->  �ּ��� ��

	������ ���� ��ȣ�� ǥ���صα�.
	�׷��� �ش� ������ ����� ���� 2�� ������ üũ�ǰ�.
	
	--------------------------------

	�ݴ�� ġŲ���� ���� �����ϰ� ġŲ������ ������ BFS �ϴ� ���.
	�ش� ���� ��ǥ�� ������ �ش� ��ǥ checked �ؼ� �ߺ����� üũ�Ǵ��� ����.
	���࿡ üũ�� ���� ������ ���� ������ ���ٸ�, BFS�� ����.




*/


void enter() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
			if (board[i][j] == 2) {
				vec2.push_back({ i,j });
				board[i][j] = 0;
			}
			if (board[i][j] == 1) {
				vec1.push_back({ i,j });
			}
		}
	}

}

void debug() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << check[i][j] << " ";
		}cout << endl;
	}
	cout << endl;
}

void chi_to_home(int cnt) {
	



}

int min(int a, int b) {
	if (a > b) return b;
	else return a;
}
int abs(int a) {
	if (a < 0) return a * -1;
	else return a;
}

int distance(PairInt a, PairInt b) {
	return abs(a.first - b.first) + abs(a.second - b.second);
}

void DFS(int cnt,int selected) {
	if (selected == M) {
		int tempResult = 0;
		for (int i = 0; i < vec1.size(); i++) {//�翬�� ��� ����žߵǴ� �κ�
			int dist = 987654321;
			for (int j = 0; j < vec2.size(); j++) { // ���õ� ġŲ���� ����ž���.
				if(visited[j])
					dist = min(dist,distance(vec1[i], vec2[j]));
			}
			tempResult += dist;
			
		}
		ans = min(ans, tempResult);		
		return;
	}
	if (cnt == vec2.size()) return;
	//���������� ����
	visited[cnt] = true;
	DFS(cnt + 1, selected + 1);
	//���������� ����X
	visited[cnt] = false;
	DFS(cnt + 1, selected);

}

int main() {
	enter();
	DFS(0, 0);
	cout << ans;
}