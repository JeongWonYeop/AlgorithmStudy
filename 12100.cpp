#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
using namespace std;
int N;
int board[20][20];
int dx[4] = { 0,0,1,-1 };
int dy[4] = { -1,1,0,0 };
/*
00  01
10  11
*/
void slide(int orient) {
	for (int i = 0; i < N-1; i++) {
		int xx = i;
		int nxx = xx++;
		while (!nxx == N - 1) {
			if(board[])
			nxx++;
		}
	}
}

void enter() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}
}


void see() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	/*
	����̱�(����) �Լ�
	��,��,��,�Ʒ�
		���� �浹 (�浹�� ���� �����, �浹�� ���� ����*2) 
			�̹� �ѹ� ������ ������ �˻�.
				�ƴ϶�� ����.== ����*2
		�׸����� ����� ä���ֱ�.

----------------------------
<��Ʈ��ŷ..? or �迭�� �����ϴ� ���..?(�޸������̼�,dp)>


	�ټ��� �̵��ؼ� �ִ�.DFS
	��				��				��				�Ʒ� O(2^10) => O(10^2)
��,��,��,�Ʒ�	��,��,��,�Ʒ�	��,��,��,�Ʒ�	��,��,��,�Ʒ�
	*/


	enter();
	see();
	slide(0);
	system("pause");
}