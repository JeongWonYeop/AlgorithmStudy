#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
#include <functional>
using namespace std;
int check_board[101][101] = { 0, };
int dx[5] = { 0, -1,1,0,0 };
int dy[5] = { 0,0,0,1,-1 };
int R;
int C;
int M;
int people_C = 0;
int result = 0;
pair <int, int> foradd;
queue <pair <int, int>> temp_que;
/*
�� �� �� ��

0 0  0 1
1 0  1 1

*/
typedef struct shark {
	int r;
	int c;
	int s;
	int d;
	int z;
}Shark;




/*
s�� �ݺ��ϰ�,
d�� 1�϶� r�� -- �ǰ�, ���࿡ 0�̸� d�� 2�� �ٲ��ش�
d�� 2�϶� r�� ++ �ǰ�, ���࿡ R�̸� d�� 1�� �ٲ��ش�
d�� 3�϶� c�� ++ �ǰ�, ���࿡ C�̸� d�� 4��
d�� 4�϶� c�� -- , 0�̸� d�� 3��
*/

/* �̺κ� ���� �߸��о �ٽ� ¥���Ѵ�. 2���� �̻� ���� �� �ִ� �ε� ���� �� �ô�.*/
void check_shark(vector <Shark> &shark_i) {
	priority_queue < pair<int,int>, vector <pair<int, int>>, less<pair<int, int>> > less_sharklist;
	for (int i = 1; i < R + 1; i++) {
		for (int j = 1; j < C + 1; j++) {
			check_board[i][j] = 0;
		}
	}

	for (int i = 0; i < shark_i.size(); i++) {
		++check_board[shark_i[i].r][shark_i[i].c];
		if (check_board[shark_i[i].r][shark_i[i].c] == 2) {
			 foradd = { shark_i[i].r , shark_i[i].c };
			 temp_que.push(foradd);
		}
	}

	while (!temp_que.empty()) {
		for (int i = 0; i < shark_i.size(); i++) {
			if (shark_i[i].r == temp_que.front().first && shark_i[i].c == temp_que.front().second) {
				less_sharklist.push({ shark_i[i].z , i});
			}
		}
		less_sharklist.pop();
		priority_queue <int, vector<int>, less<int>> t_q;
		while (!less_sharklist.empty()) {
			t_q.push(less_sharklist.top().second);
			less_sharklist.pop();
		}
		while (!t_q.empty()) {
			shark_i.erase(shark_i.begin() + t_q.top());
			t_q.pop();
		}


		temp_que.pop();
	}






}


void shark_change(vector <Shark> & shark_i) {
	for (int i = 0; i < shark_i.size(); i++) {
		int cnt = shark_i[i].s;
		while (cnt > 0) {
			if (shark_i[i].d == 1) {
				shark_i[i].r = shark_i[i].r + dx[shark_i[i].d];
				if (shark_i[i].r == 0) {
					++shark_i[i].r;
					++shark_i[i].r;
					shark_i[i].d = 2;
				}
			}
			else if (shark_i[i].d == 2) {
				shark_i[i].r = shark_i[i].r + dx[shark_i[i].d];
				if (shark_i[i].r == R + 1) {
					--shark_i[i].r; // ������ ����ϹǷ�, ���ڸ� ����.
					--shark_i[i].r; // �ٽ� ��ĭ ƨ�������;ߵǹǷ�.
					shark_i[i].d = 1;
				}
			}
			else if (shark_i[i].d == 3) {
				shark_i[i].c = shark_i[i].c + dy[shark_i[i].d];
				if (shark_i[i].c == C + 1) {
					--shark_i[i].c;
					--shark_i[i].c;
					shark_i[i].d = 4;
				}
			}
			else if (shark_i[i].d == 4) {
				shark_i[i].c = shark_i[i].c + dy[shark_i[i].d];
				if (shark_i[i].c == 0) {
					++shark_i[i].c;
					++shark_i[i].c;
					shark_i[i].d = 3;
				}
			}
			cnt--;
		}

	}
}

void catch_shark(vector <Shark> & shark_i) {
	++people_C;
	priority_queue < int, vector <int>, greater<int> > catch_shark_queue;
	while (!catch_shark_queue.empty()) {
		catch_shark_queue.pop();
	}
	for (int i = 0; i < shark_i.size(); i++) {
		if (shark_i[i].c == people_C) {
			catch_shark_queue.push(shark_i[i].r);
		}
	}

	for (int i = 0; i < shark_i.size(); i++) {
		if (shark_i[i].c == people_C && shark_i[i].r == catch_shark_queue.top()) {
			result = result + shark_i[i].z;
			shark_i.erase(shark_i.begin() + i);
		}
	}

}

int main() {

	cin >> R >> C >> M;
	vector <Shark> shark_info;
	for (int i = 0; i < M; i++) {
		int r, c, s, d, z;
		cin >> r >> c >> s >> d >> z;
		shark_info.push_back({ r,c,s,d,z });

	}


	while (people_C < C) {

		catch_shark(shark_info);
		shark_change(shark_info);
		check_shark(shark_info);

	}

	

		cout << result << endl;


	system("pause");

}
/*
x, y , ������
x1,y1,���ǵ�,�̵�����(1:��,2:�Ʒ�,3:��,4:��),ũ��
x2,y2
x3,y3

�ѹ� �ݺ���. ����� ��ĭ �Ѿ�� �� ���ο� ��� �� ���� ���� �������� �༮�� ������.
�� �����δ�.

���࿡ ������ǥ�� �ִ� ���߻��ÿ� ũ�� ���� ���� ��������.

�ʱ� ��ǥ<����ü ����> -> ��� ������(ĳġ)
��������<����ü ����>-> ������� -> ��� ������(ĳġ) <�ݺ�>


��������� : ���� �˻� �� C�� (people_C)1�� �ش� ���� ũ�� result+size ���ְ�, erase.
�������� :
������� : üũ���� �ʱ�ȭ ,��� ��ǥ �Է�-> 2�� ��ǥ. -> ���� �˻� �� ���� ���� erase.

people_C ������Ű�鼭 �ݺ�. C+1�� �Ǳ�������.

*/