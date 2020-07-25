#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <vector>
#include <functional>//greater
#include <utility>//pair
#include <stdlib.h>
using namespace std;
int N, K, L;
int result = 0;
int time = 0;
int check[101][101] = { 0, }; //�����������ڸ� �޸������̼� -> �����ָ� ������ �����ؼ� �ð����⵵ �������Ѵ�.
int apple[101][101] = { 0, }; //����� ��ġ
pair <int, char> foradd;
typedef pair<int,int> pairint;
typedef pair<int, char> pairintchar;
queue <pair<int, char>> orient_que;
queue <pair<int, int>> snake_que;
pairint snake; //���� �Ӹ�
pairint nsnake = make_pair(1, 1);
int index = 1;
//��,������,�Ʒ�,����
//0,1,2,3
//  ��
//L�϶� --index; D�϶� ++index;
//L�� -1�̸� index=3 D�� 4�̸� index=0;
int dx[4] = { -1,0,1,0};
int dy[4] = { 0,1,0,-1};

/*
00 01 02 03
10 11 12 13
20 21 22 23
30 31 32 33
*/





/*
	���� ���°�, ���� ��ȯ���ִ� ��, ��� �Դ°�, �ʰ� �����ڿ� ����Ǵ� ��,ĭ ������ ������ ����Ǵ°�,�ڽ��� ���� �ε����� ����Ǵ°�.
	O(10^8) ����
*/

void change_orient(char LD) {
	if (LD == 'L') {
		--index;
		if (index == -1) index = 3;
	}
	else if (LD == 'D') {
		++index;
		if (index == 4) index = 0;
	}
}

void snake_move() {
	snake = make_pair(1, 1);
	while (true) {
		++result;
		if (!orient_que.empty()) { 
			pairintchar orient = orient_que.front(); 
			if (result-1 == orient.first) { //3�� ��ġ�� ���� ������ȯ�� ���� �ν������Ƿ�, ���������δ� 4�ʴ뿡 ��ȭ.
				change_orient(orient.second); 
				orient_que.pop();
			}
		}

		int nx = snake.first + dx[index];
		int ny = snake.second + dy[index];
		if (nx < 1 || ny < 1 || nx > N || ny > N || check[nx][ny] == 1) break;
		snake_que.push({nx,ny});
		check[nx][ny] = 1;
		snake = make_pair(nx, ny);
		if (apple[nx][ny] == 1) {
			/*
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++) {
					cout << check[i][j] << " ";

				}cout << endl;
			}
			cout << endl;
			*/
			continue;
		}
		check[snake_que.front().first][snake_que.front().second] = 0;
		snake_que.pop();

		/*
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				cout << check[i][j] << " ";

			}cout << endl;
		}
		cout << endl;
		*/
	}
	

}

void enter() {
	cin >> N;
	cin >> K;
	for (int i = 0; i < K; i++) {
		int a_x, a_y;
		cin >> a_x >> a_y;
		apple[a_x][a_y] = 1;
	}
	cin >> L;
	for (int i = 0; i < L; i++) {
		int t;
		char DL;
		cin >> t >> DL;
		orient_que.push({ t,DL });
	}
	snake_que.push({ 1, 1 });
	check[1][1] = 1;
	
}


int main() {
	enter();
	snake_move();
	cout << result;
}