#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <queue>
#include <functional>
#include <utility>
using namespace std;

vector<int>::iterator a;
vector<int> b;
int aaa = 0;

void dfs(vector<int>::iterator aa) {
	if (aa == b.end()) {
		cout << "����.end()�� ���� �ݺ��� Ż���� �����ϴ�" << endl;

	}
	aaa++;
	cout << "���� : "<< aaa << endl;
	cout << "�� :" <<(*aa) << endl;
	dfs(++aa);

}


int main() {
	b.push_back(1);
	b.push_back(2);
	b.push_back(3);
	dfs(b.begin());
	system("pause");
}