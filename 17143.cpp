#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
#include <functional>
using namespace std;

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
	int death = 0;
}Shark;



/*
s�� �ݺ��ϰ�,
d�� 1�϶� r�� -- �ǰ�, ���࿡ 0�̸� d�� 2�� �ٲ��ش�
d�� 2�϶� r�� ++ �ǰ�, ���࿡ R�̸� d�� 1�� �ٲ��ش�
d�� 3�϶� c�� ++ �ǰ�, ���࿡ C�̸� d�� 4��
d�� 4�϶� c�� -- , 0�̸� d�� 3��
*/

/* �̺κ� ���� �߸��о �ٽ� ¥���Ѵ�. 2���� �̻� ���� �� �ִ� �ε� ���� �� �ô�.*/
void check_shark(vector <Shark> &shark_i) { // 10^6 ���Ϸ� ¥�� ��
	for (vector <Shark> ::iterator iter = shark_i.begin(); iter != shark_i.end();) {
		
	}
}


void shark_change(vector <Shark> & shark_i) { 
	for (int i = 0; i < shark_i.size(); i++) { // O(N) �ִ� 10000  // O(N)�ȿ��� O(M) ��ŭ �����ϹǷ�, O(NxM) �ִ� 10000x100 100���� ���Ϸ� ¥�� ��.
		int cnt = shark_i[i].s;
		if (cnt == 0) continue;

		if (shark_i[i].d == 1) { 
			if (cnt > (R - 1) * 2) {
				cnt = cnt % ((R - 1) * 2);
			}
			if (cnt == 0) continue;
			if (shark_i[i].r == R) shark_i[i].d = 2;
			if (shark_i[i].r - cnt > 0) {
				shark_i[i].r = shark_i[i].r - cnt;
			}
			else if (shark_i[i].r - cnt <= 0) {
				shark_i[i].r = 1 - (shark_i[i].r - cnt) + 1;
				shark_i[i].d = 2;
			}
		}
		else if (shark_i[i].d == 2) {
			if (cnt > (R - 1) * 2) {
				cnt = cnt % ((R - 1) * 2);
			}
			if (cnt == 0) continue;
			if (shark_i[i].r == 1) shark_i[i].d = 1;
			if (shark_i[i].r + cnt < R + 1) {
				shark_i[i].r = shark_i[i].r + cnt;
			}
			else {
				shark_i[i].r = R - (shark_i[i].r + cnt - R);
				shark_i[i].d = 1;
			}
		}
		else if (shark_i[i].d == 3) {
			if (cnt > (C - 1) * 2) {
				cnt = cnt % ((C - 1) * 2);
			}
			if (cnt == 0) continue;
			if (shark_i[i].c == 1) shark_i[i].d = 4;
			if (shark_i[i].c + cnt < C + 1) {
				shark_i[i].c = shark_i[i].c + cnt;
			}
			else {
				shark_i[i].c = C - (shark_i[i].c + cnt - C);
				shark_i[i].d = 4;
			}

		}
		else if (shark_i[i].d == 4) {
			if (cnt > (C - 1) * 2) {
				cnt = cnt % ((C - 1) * 2);
			}
			if (cnt == 0) continue;
			if (shark_i[i].c == C) shark_i[i].d = 3;
			if (shark_i[i].c - cnt > 0) {
				shark_i[i].c = shark_i[i].c - cnt;
			}
			else if (shark_i[i].r - cnt <= 0) {
				shark_i[i].c = 1 - (shark_i[i].c - cnt) + 1;
				shark_i[i].d = 3;
			}

		}

	

	}
}

void catch_shark(vector <Shark> & shark_i) {
	++people_C;
	priority_queue < int, vector <int>, greater<int> > catch_shark_queue;
	while (!catch_shark_queue.empty()) {
		catch_shark_queue.pop();
	}
	for (int i = 0; i < shark_i.size(); i++) { // O(N) �ִ� 10000
		if (shark_i[i].c == people_C) {
			catch_shark_queue.push(shark_i[i].r);
		}
	}

	for (int i = 0; i < shark_i.size(); i++) { // O(N) �ִ� 10000
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


	//while (people_C < C) { // O(N) �ִ� 100 -> 10^2

		catch_shark(shark_info); // 10^4
		shark_change(shark_info); // 10^4
		check_shark(shark_info); // 

//	} // 10^8 x 10^2 -> 10^10 /10^8(1��) -> ���� ����ص� 100�� -> ���ѽð� 1�� ���� �ʰ��ߴ�.

	

	for (int i = 0; i < shark_info.size(); i++) {
		cout << shark_info[i].r << " " << shark_info[i].c << " " << shark_info[i].s << " " << shark_info[i].d << " " << shark_info[i].z << endl;
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