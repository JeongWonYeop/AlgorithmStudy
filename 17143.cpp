#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <functional>
using namespace std;
int check_board[101][101] = { 0, };



typedef struct shark {
	int r;
	int c;
	int s;
	int d;
	int z;
}Shark;


int main() {
	int R;
	int C;
	int M;
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