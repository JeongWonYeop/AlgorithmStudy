#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
#include <string>
using namespace std;
int up[3][3] = { 0, };
int down[3][3] = { 0, };
int left_[3][3] = { 0, };
int right_[3][3] = { 0, };
int front[3][3] = { 0, };
int back[3][3] = { 0, };
int copy_u[3][3] = { 0, };
int copy_d[3][3] = { 0, };
int copy_l[3][3] = { 0, };
int copy_r[3][3] = { 0, };
int copy_f[3][3] = { 0, };
int copy_b[3][3] = { 0, };
/*
	입력받고
	방향별로 배열에 담아.
	바꿔치기만 해주면 돼.
	그런다음에, 맨 윗면 출력해주기.
	색깔별로 정수형 숫자 매칭 시켜주자.(약속)
	w : 0      
	y : 1
	r : 2
	o : 3
	g : 4
	b : 5

	a : U: 0, D: 1, F: 2, B: 3, L: 4, R: 5
	b : 1 : + 0 : -


*/
void initialization() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			down[i][j] = 1;
			left_[i][j] = 4;
			right_[i][j] = 5;
			front[i][j] = 2;
			back[i][j] = 3;
		}
	}
}

void rotate(int a,int b) {
	/*
		a : U: 0, D: 1, F: 2, B: 3, L: 4, R: 5
		b : 1 : + 0 : -
		L과 R은 back의 경우에 달라진다. 왜냐하면 해당 블록을 바라볼 때 관점이기 때문에.

	*/
	if (a == 0) {
		if (b == 1) {
			up[0][0] = copy_u[2][0];
			up[0][1] = copy_u[1][0];
			up[0][2] = copy_u[0][0];
			up[1][0] = copy_u[2][1];
			up[1][2] = copy_u[0][1];
			up[2][0] = copy_u[2][2];
			up[2][1] = copy_u[1][2];
			up[2][2] = copy_u[0][2];
			front[0][0] = copy_r[0][0];
			front[0][1] = copy_r[0][1];
			front[0][2] = copy_r[0][2];
			left_[0][0] = copy_f[0][0];
			left_[0][1] = copy_f[0][1];
			left_[0][2] = copy_f[0][2];
			back[0][0] = copy_l[0][0];
			back[0][1] = copy_l[0][1];
			back[0][2] = copy_l[0][2];
			right_[0][0] = copy_b[0][0];
			right_[0][1] = copy_b[0][1];
			right_[0][2] = copy_b[0][2];

		}
		else {
			up[2][0] = copy_u[0][0];
			up[1][0] = copy_u[0][1];
			up[0][0] = copy_u[0][2];
			up[2][1] = copy_u[1][0];
			up[0][1] = copy_u[1][2];
			up[2][2] = copy_u[2][0];
			up[1][2] = copy_u[2][1];
			up[0][2] = copy_u[2][2];
			front[0][0] = copy_l[0][0];
			front[0][1] = copy_l[0][1];
			front[0][2] = copy_l[0][2];
			left_[0][0] = copy_b[0][0];
			left_[0][1] = copy_b[0][1];
			left_[0][2] = copy_b[0][2];
			back[0][0] = copy_r[0][0];
			back[0][1] = copy_r[0][1];
			back[0][2] = copy_r[0][2];
			right_[0][0] = copy_f[0][0];
			right_[0][1] = copy_f[0][1];
			right_[0][2] = copy_f[0][2];
		}
	}
	/*
	a : U: 0, D: 1, F: 2, B: 3, L: 4, R: 5
	b : 1 : + 0 : -
	L과 R은 back의 경우에 달라진다. 왜냐하면 해당 블록을 바라볼 때 관점이기 때문에.

	*/
	else if (a == 1) {
		if (b == 1) {
			down[0][0] = copy_d[2][0];
			down[0][1] = copy_d[1][0];
			down[0][2] = copy_d[0][0];
			down[1][0] = copy_d[2][1];
			down[1][2] = copy_d[0][1];
			down[2][0] = copy_d[2][2];
			down[2][1] = copy_d[1][2];
			down[2][2] = copy_d[0][2];
			front[2][0] = copy_r[2][0];
			front[2][1] = copy_r[2][1];
			front[2][2] = copy_r[2][2];
			left_[2][0] = copy_f[2][0];
			left_[2][1] = copy_f[2][1];
			left_[2][2] = copy_f[2][2];
			back[2][0] = copy_l[2][0];
			back[2][1] = copy_l[2][1];
			back[2][2] = copy_l[2][2];
			right_[2][0] = copy_b[2][0];
			right_[2][1] = copy_b[2][1];
			right_[2][2] = copy_b[2][2];
		}
		else {
			down[2][0] = copy_d[0][0];
			down[1][0] = copy_d[0][1];
			down[0][0] = copy_d[0][2];
			down[2][1] = copy_d[1][0];
			down[0][1] = copy_d[1][2];
			down[2][2] = copy_d[2][0];
			down[1][2] = copy_d[2][1];
			down[0][2] = copy_d[2][2];
			front[2][0] = copy_l[2][0];
			front[2][1] = copy_l[2][1];
			front[2][2] = copy_l[2][2];
			left_[2][0] = copy_b[2][0];
			left_[2][1] = copy_b[2][1];
			left_[2][2] = copy_b[2][2];
			back[2][0] = copy_r[2][0];
			back[2][1] = copy_r[2][1];
			back[2][2] = copy_r[2][2];
			right_[2][0] = copy_f[2][0];
			right_[2][1] = copy_f[2][1];
			right_[2][2] = copy_f[2][2];
		}
	}
	/*
	a : U: 0, D: 1, F: 2, B: 3, L: 4, R: 5
	b : 1 : + 0 : -
	L과 R은 back의 경우에 달라진다. 왜냐하면 해당 블록을 바라볼 때 관점이기 때문에.

	*/
	else if(a == 2){
		if(b == 1){
			front[0][0] = copy_f[2][0];
			front[0][1] = copy_f[1][0];
			front[0][2] = copy_f[0][0];
			front[1][0] = copy_f[2][1];
			front[1][2] = copy_f[0][1];
			front[2][0] = copy_f[2][2];
			front[2][1] = copy_f[1][2];
			front[2][2] = copy_f[0][2];
			up[2][0] = copy_l[2][0];
			up[2][1] = copy_l[2][1];
			up[2][2] = copy_l[2][2];
			left_[0][2] = copy_d[0][0];
			left_[1][2] = copy_d[0][1];
			left_[2][2] = copy_d[0][2];
			right_[0][0] = copy_u[2][0];
			right_[1][0] = copy_u[2][1];
			right_[2][0] = copy_u[2][2];
			down[0][0] = copy_r[0][0];
			down[0][1] = copy_r[1][0];
			down[0][2] = copy_r[2][0];

		}
		else {
			front[2][0] = copy_f[0][0];
			front[1][0] = copy_f[0][1];
			front[0][0] = copy_f[0][2];
			front[2][1] = copy_f[1][0];
			front[0][1] = copy_f[1][2];
			front[2][2] = copy_f[2][0];
			front[1][2] = copy_f[2][1];
			front[0][2] = copy_f[2][2];
			up[2][0] = copy_r[0][0];
			up[2][1] = copy_r[1][0];
			up[2][2] = copy_r[2][0];
			left_[0][2] = copy_u[2][0];
			left_[1][2] = copy_u[2][1];
			left_[2][2] = copy_u[2][2];
			right_[0][0] = copy_d[0][0];
			right_[1][0] = copy_d[0][1];
			right_[2][0] = copy_d[0][2];
			down[2][0] = copy_l[2][0];
			down[2][1] = copy_l[2][1];
			down[2][2] = copy_l[2][2];
		}
	}
	/*
	a : U: 0, D: 1, F: 2, B: 3, L: 4, R: 5
	b : 1 : + 0 : -
	L과 R은 back의 경우에 달라진다. 왜냐하면 해당 블록을 바라볼 때 관점이기 때문에.

	*/
	else if (a == 3) {//b
		if (b == 1) {//front 기준에서 바라볼 때의 시계방향
			back[0][0] = copy_b[2][0];
			back[0][1] = copy_b[1][0];
			back[0][2] = copy_b[0][0];
			back[1][0] = copy_b[2][1];
			back[1][2] = copy_b[0][1];
			back[2][0] = copy_b[2][2];
			back[2][1] = copy_b[1][2];
			back[2][2] = copy_b[0][2];
			up[0][0] = copy_l[0][0];
			up[0][1] = copy_l[1][0];
			up[0][2] = copy_l[2][0];
			left_[0][0] = copy_d[2][0];
			left_[1][0] = copy_d[2][1];
			left_[2][0] = copy_d[2][2];
			right_[0][2] = copy_u[0][0];
			right_[1][2] = copy_u[0][1];
			right_[2][2] = copy_u[0][2];
			down[2][0] = copy_r[0][2];
			down[2][1] = copy_r[1][2];
			down[2][2] = copy_r[2][2];
		}
		else {//front 기준에서 바라볼 때의 반시계방향
			back[2][0] = copy_b[0][0];
			back[1][0] = copy_b[0][1];
			back[0][0] = copy_b[0][2];
			back[2][1] = copy_b[1][0];
			back[0][1] = copy_b[1][2];
			back[2][2] = copy_b[2][0];
			back[1][2] = copy_b[2][1];
			back[0][2] = copy_b[2][2];
			up[0][0] = copy_r[0][2];
			up[0][1] = copy_r[1][2];
			up[0][2] = copy_r[2][2];
			left_[0][0] = copy_u[0][0];
			left_[1][0] = copy_u[0][1];
			left_[2][0] = copy_u[0][2];
			right_[0][2] = copy_d[2][0];
			right_[1][2] = copy_d[2][1];
			right_[2][2] = copy_d[2][2];
			down[2][0] = copy_l[0][0];
			down[2][1] = copy_l[1][0];
			down[2][2] = copy_l[2][0];

		}
	}
	/*
	a : U: 0, D: 1, F: 2, B: 3, L: 4, R: 5
	b : 1 : + 0 : -
	L과 R은 back의 경우에 달라진다. 왜냐하면 해당 블록을 바라볼 때 관점이기 때문에.

	*/
	else if (a == 4) {//l
		if (b == 1) {
			left_[0][0] = copy_l[2][0];
			left_[0][1] = copy_l[1][0];
			left_[0][2] = copy_l[0][0];
			left_[1][0] = copy_l[2][1];
			left_[1][2] = copy_l[0][1];
			left_[2][0] = copy_l[2][2];
			left_[2][1] = copy_l[1][2];
			left_[2][2] = copy_l[0][2];
			up[0][0] = copy_b[0][0];
			up[1][0] = copy_b[1][0];
			up[2][0] = copy_b[2][0];
			front[0][0] = copy_u[0][0];
			front[1][0] = copy_u[1][0];
			front[2][0] = copy_u[2][0];
			down[0][0] = copy_f[0][0];
			down[1][0] = copy_f[1][0];
			down[2][0] = copy_f[2][0];
			back[0][2] = copy_d[0][0];
			back[1][2] = copy_d[1][0];
			back[2][2] = copy_d[2][0];
		}
		else {
			left_[2][0] = copy_l[0][0];
			left_[1][0] = copy_l[0][1];
			left_[0][0] = copy_l[0][2];
			left_[2][1] = copy_l[1][0];
			left_[0][1] = copy_l[1][2];
			left_[2][2] = copy_l[2][0];
			left_[1][2] = copy_l[2][1];
			left_[0][2] = copy_l[2][2];
			up[0][0] = copy_f[0][0];
			up[1][0] = copy_f[1][0];
			up[2][0] = copy_f[2][0];
			front[0][0] = copy_d[0][0];
			front[1][0] = copy_d[1][0];
			front[2][0] = copy_d[2][0];
			down[0][0] = copy_b[0][0];
			down[1][0] = copy_b[1][0];
			down[2][0] = copy_b[2][0];
			back[0][2] = copy_u[0][0];
			back[1][2] = copy_u[1][0];
			back[2][2] = copy_u[2][0];
		}
	}
	else if (a == 5) {//r
		if (b == 1) {
			right_[0][0] = copy_r[2][0];
			right_[0][1] = copy_r[1][0];
			right_[0][2] = copy_r[0][0];
			right_[1][0] = copy_r[2][1];
			right_[1][2] = copy_r[0][1];
			right_[2][0] = copy_r[2][2];
			right_[2][1] = copy_r[1][2];
			right_[2][2] = copy_r[0][2];
			up[0][2] = copy_b[0][2];
			up[1][2] = copy_b[1][2];
			up[2][2] = copy_b[2][2];
			front[0][2] = copy_u[0][2];
			front[1][2] = copy_u[1][2];
			front[2][2] = copy_u[2][2];
			down[0][2] = copy_f[0][2];
			down[1][2] = copy_f[1][2];
			down[2][2] = copy_f[2][2];
			back[0][2] = copy_d[0][2];
			back[1][2] = copy_d[1][2];
			back[2][2] = copy_d[2][2];
		}
		else {
			right_[2][0] = copy_r[0][0];
			right_[1][0] = copy_r[0][1];
			right_[0][0] = copy_r[0][2];
			right_[2][1] = copy_r[1][0];
			right_[0][1] = copy_r[1][2];
			right_[2][2] = copy_r[2][0];
			right_[1][2] = copy_r[2][1];
			right_[0][2] = copy_r[2][2];
			up[0][2] = copy_f[0][2];
			up[1][2] = copy_f[1][2];
			up[2][2] = copy_f[2][2];
			front[0][2] = copy_d[0][2];
			front[1][2] = copy_d[1][2];
			front[2][2] = copy_d[2][2];
			down[0][2] = copy_b[0][2];
			down[1][2] = copy_b[1][2];
			down[2][2] = copy_b[2][2];
			back[0][2] = copy_u[0][2];
			back[1][2] = copy_u[1][2];
			back[2][2] = copy_u[2][2];
		}
	}
}

int main() {
	initialization();
	int N;
	cin >> N;
	int copy_up[3][3];
	memcpy(copy_up, up, sizeof(up));
	int copy_dn[3][3];
	memcpy(copy_dn, down, sizeof(down));
	int copy_le[3][3];
	memcpy(copy_le, left_, sizeof(left_));
	int copy_rt[3][3];
	memcpy(copy_rt, right_, sizeof(right_));
	int copy_fr[3][3];
	memcpy(copy_fr, front, sizeof(front));
	int copy_ba[3][3];
	memcpy(copy_ba, back, sizeof(back));
	

	while (N>0) {
		string a;
		int num;
		cin >> num;
		memcpy(up, copy_up, sizeof(copy_up));
		memcpy(down, copy_dn, sizeof(copy_dn));
		memcpy(left_, copy_le, sizeof(copy_le));
		memcpy(right_, copy_rt, sizeof(copy_rt));
		memcpy(front, copy_fr, sizeof(copy_fr));
		memcpy(back, copy_ba, sizeof(copy_ba));
		for (int i = 0; i < num; i++) {
			cin >> a;
			/*
			int copy_u[3][3] = { 0, };
			int copy_d[3][3] = { 0, };
			int copy_l[3][3] = { 0, };
			int copy_r[3][3] = { 0, };
			int copy_f[3][3] = { 0, };
			int copy_b[3][3] = { 0, };
			*/
			memcpy(copy_u, up, sizeof(up));
			memcpy(copy_d, down, sizeof(down));
			memcpy(copy_l, left_, sizeof(left_));
			memcpy(copy_r, right_, sizeof(right_));
			memcpy(copy_f, front, sizeof(front));
			memcpy(copy_b, back, sizeof(back));
			/*
			a : U: 0, D: 1, F: 2, B: 3, L: 4, R: 5
			b : 1 : + 0 : -

			*/
			if (a[0] == 'U') {
				if (a[1] == '+') {
					/*
					0 1 2   6 3 0
					3 4 5   7 4 1
					6 7 8   8 5 2
					*/
					rotate(0,1);

				}
				else {
					rotate(0, 0);


				}
			}
			else if (a[0] == 'D') {
				if (a[1] == '+') {
					/*
					0 1 2   6 3 0
					3 4 5   7 4 1
					6 7 8   8 5 2
					*/
					rotate(1, 0);

				}
				else {
					rotate(1, 1);


				}
			}
			else if (a[0] == 'F') {
				if (a[1] == '+') {
					/*
					0 1 2   6 3 0
					3 4 5   7 4 1
					6 7 8   8 5 2
					*/
					rotate(2, 1);

				}
				else {
					rotate(2, 0);


				}
			}
			else if (a[0] == 'B') {
				if (a[1] == '+') {
					/*
					0 1 2   6 3 0
					3 4 5   7 4 1
					6 7 8   8 5 2
					*/
					rotate(3, 0);

				}
				else {
					rotate(3, 1);


				}
			}
			else if (a[0] == 'L') {
				if (a[1] == '+') {
					/*
					0 1 2   6 3 0
					3 4 5   7 4 1
					6 7 8   8 5 2
					*/
					rotate(4, 1);

				}
				else {
					rotate(4, 0);


				}
			}
			else if (a[0] == 'R') {
				if (a[1] == '+') {
					/*
					0 1 2   6 3 0
					3 4 5   7 4 1
					6 7 8   8 5 2
					*/
					rotate(5,0);

				}
				else {
					rotate(5,1);


				}
			}

			cout << endl;
			cout << "up" << endl;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (up[i][j] == 0) cout << 'w';
					if (up[i][j] == 1) cout << 'y';
					if (up[i][j] == 2) cout << 'r';
					if (up[i][j] == 3) cout << 'o';
					if (up[i][j] == 4) cout << 'g';
					if (up[i][j] == 5) cout << 'b';
				}cout << endl;
			}
			cout << "back" << endl;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (back[i][j] == 0) cout << 'w';
					if (back[i][j] == 1) cout << 'y';
					if (back[i][j] == 2) cout << 'r';
					if (back[i][j] == 3) cout << 'o';
					if (back[i][j] == 4) cout << 'g';
					if (back[i][j] == 5) cout << 'b';
				}cout << endl;
			}

			cout << "left" << endl;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (left_[i][j] == 0) cout << 'w';
					if (left_[i][j] == 1) cout << 'y';
					if (left_[i][j] == 2) cout << 'r';
					if (left_[i][j] == 3) cout << 'o';
					if (left_[i][j] == 4) cout << 'g';
					if (left_[i][j] == 5) cout << 'b';
				}cout << endl;
			}
			cout << "front" << endl;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (front[i][j] == 0) cout << 'w';
					if (front[i][j] == 1) cout << 'y';
					if (front[i][j] == 2) cout << 'r';
					if (front[i][j] == 3) cout << 'o';
					if (front[i][j] == 4) cout << 'g';
					if (front[i][j] == 5) cout << 'b';
				}cout << endl;
			}
			cout << "right" << endl;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (right_[i][j] == 0) cout << 'w';
					if (right_[i][j] == 1) cout << 'y';
					if (right_[i][j] == 2) cout << 'r';
					if (right_[i][j] == 3) cout << 'o';
					if (right_[i][j] == 4) cout << 'g';
					if (right_[i][j] == 5) cout << 'b';
				}cout << endl;
			}
			cout << "down" << endl;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (down[i][j] == 0) cout << 'w';
					if (down[i][j] == 1) cout << 'y';
					if (down[i][j] == 2) cout << 'r';
					if (down[i][j] == 3) cout << 'o';
					if (down[i][j] == 4) cout << 'g';
					if (down[i][j] == 5) cout << 'b';
				}cout << endl;
			}
		}

		N--;
	}
	/*
	w : 0
	y : 1
	r : 2
	o : 3
	g : 4
	b : 5*/

	system("pause");

}