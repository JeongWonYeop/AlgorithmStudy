#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <functional>
#include <utility>
using namespace std;
int a;

/*
ex 4x4
	üũ.
		���μ��κ� �˻�� ���������� �����ֵ�, ���󰹼�,�α��� ������ ����. �ߺ����� �������� �ʰ� ����.
	
	��������.
	o o o x
	o o o x
	o o o x
	o o o x

	��������
	o o o o
	o o o o
	o o o o
	x x x x 
	.

*/



void enter() {
	cin >> a;

}

void debug() {
	cout << a;
}
///��ɳ�������, ������������.
//��� ȯ���� ����϶�. ȯ�� ������ �ǻ缱�ð� ����. ���ε� �𸣴� �ǻ缱���� ������ ��¦���� ����(���)�϶�.
int main() {
	enter();
	debug();
	system("pause");