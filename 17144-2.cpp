#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <utility>
using namespace std;

int x, y, countt;
int arr[51][51] = { 0, };
pair <int, int> axis;
queue< pair <int, int> > axque;
queue< pair <int, int> > queuee;
queue <int> beforeDust;
int sum = 0;

void makemap() {
	for (int i = 0; i < x + 2; i++) {
		arr[i][0] = -2;
	}
	for (int i = 0; i < y + 2; i++) {
		arr[0][i] = -2;
	}
	for (int i = 0; i < x + 2; i++) {
		arr[i][y+1] = -2;
	}
	for (int i = 0; i < x + 2; i++) {
		arr[x+1][i] = -2;
	}
}

void input(){
	cin >> x >> y >> countt;
	for (int i = 1; i < x + 1; i++) {
		for (int j = 1; j < y + 1; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == -1) {
				axis = make_pair(i, j);
				axque.push(axis);
			}
			if (arr[i][j] >= 5) {
				axis = make_pair(i, j);
				queuee.push(axis);
				beforeDust.push(arr[i][j]);
			}
		}
	}

}
void dustSpread(int x, int y) {
	int a = beforeDust.front() / 5;
	if (arr[x - 1][y] != -2 && arr[x - 1][y] != -1) { 
		arr[x - 1][y] = arr[x - 1][y] + a; 
		arr[x][y] = arr[x][y] - a;
	}
	if (arr[x][y + 1] != -2 && arr[x][y + 1] != -1) {
		arr[x][y + 1] = arr[x][y + 1] + a;
		arr[x][y] = arr[x][y] - a;
	}
	if (arr[x + 1][y] != -2 && arr[x + 1][y] != -1) {
		arr[x + 1][y] = arr[x + 1][y] + a;
		arr[x][y] = arr[x][y] - a;
	}
	if (arr[x][y - 1] != -2 && arr[x][y - 1] != -1) {
		arr[x][y - 1] = arr[x][y - 1] + a;
		arr[x][y] = arr[x][y] - a;
	}
	beforeDust.pop();
}
void Airstream() {
	int x1 = axque.front().first;
	int y1 = axque.front().second;
	axque.pop();
	for (int i = x1-1; i > 1; i--) {
		arr[i][1] = arr[i - 1][1];
	}
	for (int i = 1; i < y; i++) {
		arr[1][i] = arr[1][i + 1];
	}
	for (int i = 1; i < x1; i++) {
		arr[i][y] = arr[i + 1][y];
	}
	for (int i = y; i > 2; i--) {
		arr[x1][i] = arr[x1][i - 1];
	}
	arr[x1][2] = 0;

	int x2 = axque.front().first;
	int y2 = axque.front().second;
	for (int i = x2 + 1; i < x; i++) {
		arr[i][1] = arr[i + 1][1];
	}
	for (int i = y2; i < y; i++) {
		arr[x][i] = arr[x][i + 1];
	}
	for (int i = x; i > x2; i--) {
		arr[i][y] = arr[i - 1][y];
	}
	for (int i = y; i > y2 + 1; i--) {
		arr[x2][i] = arr[x2][i - 1];
	}
	arr[x2][y2 + 1] = 0;
	axque.pop();
}

void draw() {
	for (int i = 1; i < x + 1; i++) {
		for (int j = 1; j < y + 1; j++) {
			cout << arr[i][j] << " ";
	
		}
		cout << endl;
	}
}

void refillqueue() {
	for (int i = 1; i < x + 1; i++) {
		for (int j = 1; j < y + 1; j++) {
			if (arr[i][j] == -1) {
				axis = make_pair(i, j);
				axque.push(axis);
			}
			if (arr[i][j] >= 5) {
				axis = make_pair(i, j);
				queuee.push(axis);
				beforeDust.push(arr[i][j]);
			}
		}
	}
}

int main() {
	input();
	makemap();
	for(int i = 0 ; i < countt; i++){
		while (!queuee.empty()) {
			dustSpread(queuee.front().first, queuee.front().second);
			queuee.pop();
		}
		Airstream();
		refillqueue();
	}

	for (int i = 1; i < x + 1; i++) {
		for (int j = 1; j < y + 1; j++) {
			sum = sum + arr[i][j];
		}
	}
	sum = sum + 2;
	cout << sum;
	system("pause");
}
