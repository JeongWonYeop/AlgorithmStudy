#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <functional>
using namespace std;
int check_board[101][101] = { 0, };
int dx[5] = { 0, -1,1.0,0};
int dy[5] = { 0, 0,0.1,-1};
int R;
int C;
int M;
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
void shark_change(vector <Shark> & shark_i) {
	for (int i = 0; i < shark_i.size(); i++) {
		int cnt = shark_i[i].s;
		while (cnt > 0) {
			if (shark_i[i].d == 1) {
				shark_i[i].r = shark_i[i].r + dx[shark_i[i].d];
				if (shark_i[i].r == 0) shark_i[i].d = 2;
			}
			else if (shark_i[i].d == 2) {
				shark_i[i].r = shark_i[i].r + dx[shark_i[i].d];
				if (shark_i[i].r == R) shark_i[i].d = 1;
			}
			else if (shark_i[i].d == 3) {
				shark_i[i].c = shark_i[i].c + dy[shark_i[i].d];
				if (shark_i[i].c == C) shark_i[i].d = 4;
			}
			else if (shark_i[i].d == 4) {
				shark_i[i].c = shark_i[i].c + dy[shark_i[i].d];
				if (shark_i[i].c == 0) shark_i[i].d = 3;
			}
			cnt--;
		}

	}
}
int main() {

	cin >> R >> C >> M;
	vector <Shark> shark_info;
	for (int i = 0; i < M; i++) {
		int r,c, s, d, z;
		cin >> r >> c >> s>> d >>z;
		shark_info.push_back({ r,c,s,d,z });
	}

	shark_change(shark_info);

	for(int i = 0 ; i < shark_info.size() ; i++){
		cout << shark_info[i].r << " " << shark_info[i].c << " " << shark_info[i].s <<" " <<shark_info[i].d <<" "<< shark_info[i].z <<endl;
	}
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


�������� : 
������� : üũ���� �ʱ�ȭ ,��� ��ǥ �Է�-> 2�� ��ǥ. -> ���� �˻� �� ���� ���� erase.
��������� : ���� �˻� �� C�� (people_C)1�� �ش� ���� ũ�� result+size ���ְ�, erase.
people_C ������Ű�鼭 �ݺ�. C+1�� �Ǳ�������.

*/