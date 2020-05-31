#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

int n, pluss, minuss, mul, divv;
int minNum = 2147483648;
int maxNum = -2147483647;
int num[12];

void dfs(int pl, int mi, int mu, int di, int index, int result) {
	if (index == n) {
		if (minNum > result) {
			minNum = result;
		}
		if (maxNum < result) {
			maxNum = result;
		}
		return;
	}
	if (pluss > pl) 
	{
		dfs(pl + 1, mi, mu, di, index + 1, result + num[index]);
	}
	if (minuss > mi)
	{
		dfs(pl, mi + 1, mu, di, index + 1, result - num[index]);
	}
	if (mul > mu) {
		dfs(pl, mi, mu + 1, di, index + 1, result*num[index]);
	}
	if (divv > di) {
		dfs(pl, mi, mu, di+1, index + 1, result / num[index]);
	}
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> num[i];
	}
	cin >> pluss >> minuss >> mul >> divv;
	dfs(0, 0, 0, 0, 1, num[0]);

	cout << maxNum << endl;
	cout << minNum << endl;

}