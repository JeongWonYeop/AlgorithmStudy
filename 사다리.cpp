#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
using namespace std;
int T;
int Answer = 0;
int aa;
int sero, karo, dochak;
int change[2001][1501] = { 0, };
int hang = 1;
int MEMORY = 1;
typedef pair <int, int> Pair;
//vector <int> sero_info[1501];
/*
	1�� 2�� 3��
	�� �ึ�� ���� ���� ���� ���� �ִ�.
	�ð����� : O(300000000)
	T<=70,N==sero<=1500,k==karo<=2000,m==dochak<=10^5
	���� �ʿ��ϴ�.
	karo �� ������ŭ ���� �����.

	��ٸ��� ���࿡ 1 �����Ѵ� ġ��,
	DFS(��0,��1,cnt0) // 0�� �����Ѱ��� 
	���� ���࿡ hang���� �����ϴٸ�
	���� dochak�� ���ٸ� ans = min(ans,�����Ѱ���) 
	���࿡ ans �� 987654321 ��� ans = -1;
	return ans;
	0�� 1������ �����ؼ�.
	1�� 1��. 
	//  ���࿡ change[1][1]���� 0�̸� DFS(��+1,1��,cnt);
	//	���࿡ change[1][1]���� 0�� �ƴϸ�, CHANGE ������ �ְ�
			DFS(��+1, change[1][1]��,cnt)
			//		�����ҰŸ�
			//      �����Ѱ��� cnt ����
			DFS(2��, 1��, cnt+1)

	�޸������̼�
		���� [2001][1501] <Pair <int,int> >  ������, �����Ѱ���.

		�ش� ��ǥ�� �������� ������ cnt + �ش� �����Ѱ��� return;

*/

int mmin(int a, int b) {
	if (a < b) return a;
	else return b;
}

void enter() {
	cin >> sero >> karo >> dochak;
	for (int i = 0; i < karo; i++) {
		int temp_x, temp_y;
		cin >> temp_x >> temp_y;
		change[hang][temp_y] = temp_x;
		change[hang++][temp_x] = temp_y;
	}
}

void initialization() {

	for (int i = 1; i < 2001; i++) {
		for (int j = 1; j < 1501; j++) {
			change[i][j] = 0;
//			Memo[i][j].clear();
		}
	}
	Answer = 0;
	hang = 1;
}
/*
void debug() {
	for (int i = 0; i < hang; i++) {
		for(int j = 1 ; j< sero+1;j++){
			cout << i << "��" << j << "��" << endl;
			cout << "�ٲ�� ��"<<change[i][j] << endl;
		}
	}
	for (int i = 0; i < dochak_info.size(); i++) {
		cout << "��� : " << dochak_info[i].first << "���� :" << dochak_info[i].second << endl;
	}
}
*/
/*
��ٸ��� ���࿡ 1 �����Ѵ� ġ��,
DFS(��0,��1,dochak,cnt0) // 0�� �����Ѱ���
���� ���࿡ hang���� �����ϴٸ�
���� dochak�� ���ٸ� ans = min(ans,�����Ѱ���)
return ans;
0�� 1������ �����ؼ�.
1�� 1��.
//  ���࿡ change[1][1]���� 0�̸� DFS(��+1,1��,cnt);
//	���࿡ change[1][1]���� 0�� �ƴϸ�, CHANGE ������ �ְ�
DFS(��+1, change[1][1]��,cnt)
//		�����ҰŸ�
//      �����Ѱ��� cnt ����
DFS(2��, 1��, cnt+1)

DFS ������ 	���࿡ ans �� 987654321 ��� ans = -1;
*/
void DFS(int h, int y, int doch ,int cnt) {
//cout << MEMORY++ << endl;
	cout << h << "��" << y << "��" << endl;
	cout << "������ ����" << cnt << endl;

	if (aa <= cnt) return;

	while(change[h + 1][y] == 0){
		h = h + 1;
		if (h == hang) {
//			cout <<"h : "<< h << endl;
//			cout <<"hang : "<< hang << endl;
			if (y == doch) {
				aa = mmin(aa, cnt);
			}
			return;
		}
	}
	if (change[h + 1][y] != 0){ // �ִ� 2000������ ����.
		int copy_cnt = cnt;
		DFS(h + 1, change[h + 1][y], doch, cnt);
		cnt = copy_cnt;
		DFS(h + 1, y, doch, cnt + 1);
	}
}


int main() {

	int T, test_case;


	

	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		initialization();
		enter();
	//	debug();
		

		for (int i = 0; i < dochak; i++) {
			int s, g;//start,goal
			cin >> s >> g;
			aa = 987654321;
			DFS(0, s, g, 0);//int �� 4��.
			if (aa == 987654321) aa = -1;
			//			cout << aa << endl;
			Answer = Answer + aa;
			



		}
	

		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}
	system("pause");
	return 0;
}