#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
#include <string>
#include <cstring>
#include <stack>
using namespace std;
int N;

int checked[101][101] = { 0, };
int dx[4] = {0,-1,0,1};
int dy[4] = {1,0,-1,0};
typedef pair<int, int> PairInt;
int sum = 0;
/*
	00 01
	10 11

*/


/*
	좌표를 입력받는데, 변수에 넣을 땐 x좌표,y좌표 입력받은 반대로 설정해줘야돼.
	드래곤커브를 그린다.
	네꼭지점이 모두 드래곤커브인 것의 개수를 출력한다.
*/

typedef struct four {
	int y;
	int x;
	int orient;
	int gen;
}four;

vector <four> dragon_curve;

void enter() {
	cin >> N;
	for (int i = 0; i < N; i++) {
			four temp;
			cin >> temp.y;
			cin >> temp.x;
			cin >> temp.orient;
			cin >> temp.gen;
			dragon_curve.push_back(temp);
	}
}

void draw(vector <int> &orient2,int x,int y) {
	int nx = x;
	int ny = y;
	checked[x][y] = 1;
	for (int i = 0; i < orient2.size(); i++) {
		nx = nx + dx[orient2[i]];
		ny = ny + dy[orient2[i]];
		checked[nx][ny] = 1;
	}
}

void draw_dragon_curve(int x,int y,int orient, int gen) {
	vector <int> orient2;
	orient2.push_back(orient);
	for(int i = 0 ; i < gen; i++){
		for (int i = orient2.size() - 1; i >= 0; i--) {
			if (orient2[i] + 1 == 4) {
				orient2.push_back(0);
				continue;
			}
			orient2.push_back(orient2[i] + 1);
		}
	}

	draw(orient2,x,y);
}
void debug() {
	/*
	1 0 0 
	0 0 0

	*/
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (checked[i][j] == 1 && checked[i][j + 1] == 1 && checked[i + 1][j] == 1 && checked[i + 1][j + 1] == 1) {
				++sum;
			}
		}
	}


}
int main() {
	enter();
	for (int i = 0; i <N; i++) {
			draw_dragon_curve(dragon_curve[i].x,dragon_curve[i].y,dragon_curve[i].orient,dragon_curve[i].gen);
	}
	debug();
	cout << sum;
	system("pause");
}