#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
using namespace std;
int N;
int board[20][20];
//priority_queue <B_I, vector <B_I>, compare1> que1;
//priority_queue <B_I, vector <B_I>, compare2> que2;
//priority_queue <B_I, vector <B_I>, compare3> que3;
int dx[4] = { 0,0,-1,1 }; //좌우위아래
int dy[4] = { -1,1,0,0 };
int check[20][20] = { 0, };
typedef struct board_info {
	int xx;
	int yy;
	int sizee;
}B_I;
/*
00  01
10  11
*/

struct compare0 { //좌측열 기준
	bool operator()(B_I &a, B_I &c) {
		if (a.xx != c.xx)
			return a.xx > c.xx;
		if (a.yy != c.yy)
			return a.yy > c.yy;
		return a.sizee > c.sizee;
	}
};

struct compare1 { //우측열 기준
	bool operator()(B_I &a, B_I &c) {
		if (a.xx != c.xx)
			return a.xx > c.xx;
		if (a.yy != c.yy)
			return a.yy < c.yy;
		return a.sizee > c.sizee;
	}
};

struct compare2 {//가장 윗행 기준
	bool operator()(B_I &a, B_I &c) {
		if (a.xx != c.xx)
			return a.xx > c.xx;
		if (a.yy != c.yy)
			return a.yy > c.yy;
		return a.sizee > c.sizee;
	}
};

struct compare3 { // 가장 아래행 기준
	bool operator()(B_I &a, B_I &c) {
		if (a.xx != c.xx)
			return a.xx < c.xx;
		if (a.yy != c.yy)
			return a.yy > c.yy;
		return a.sizee > c.sizee;
	}
};



priority_queue <B_I, vector <B_I>, compare0> que0; //좌측열기준
priority_queue <B_I, vector <B_I>, compare1> que1; //우측열기준
priority_queue <B_I, vector <B_I>, compare2> que2; //위행기준
priority_queue <B_I, vector <B_I>, compare3> que3; //아래행기준
void mix(int orient) {


	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = 0;
			check[i][j] = 0;
		}
	}

	if (orient == 0) {
		while (!que0.empty()) {
			B_I first = que0.top();
			que0.pop();
			B_I second = que0.top();
			que0.pop();

			board[first.xx][first.yy] = first.sizee;
			board[second.xx][second.yy] = second.sizee;


			if (first.xx != second.xx) {
				que0.push({ second.xx,second.yy,second.sizee });
				continue;
			}
			int nx = first.xx;
			int nsize = first.sizee;
			if (board[nx][first.yy] == board[nx][second.yy]) {
				board[nx][first.yy] =nsize*2;
				board[second.xx][second.yy] = 0;
			}
		}
	}
	else if (orient == 1) {
		while (!que1.empty()) {
			B_I first = que1.top();
			que1.pop();
			int ny = first.yy;
			while (board[first.xx][++ny] == 0 && ny != N) {}
			board[first.xx][--ny] = first.sizee;
		}
	}
	else if (orient == 2) {
		while (!que2.empty()) {
			B_I first = que2.top();
			que2.pop();
			int nx = first.xx;
			while (board[--nx][first.yy] == 0 && nx != -1) {}
			board[++nx][first.yy] = first.sizee;
		}
	}
	else {
		while (!que3.empty()) {
			B_I first = que3.top();
			que3.pop();
			int nx = first.xx;
			while (board[++nx][first.yy] == N && nx != -1) {}
			board[--nx][first.yy] = first.sizee;
		}
	}


	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			que0.push({ i,j,board[i][j] });
			que1.push({ i,j,board[i][j] });
			que2.push({ i,j,board[i][j] });
			que3.push({ i,j,board[i][j] });
		}
	}



}
void tilt(int orient) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = 0;
		}
	}
	if (orient == 0) {
		while(!que0.empty()){
			B_I first = que0.top();
			que0.pop();
			int ny = first.yy ;
			while (board[first.xx][--ny] == 0 && ny !=-1) {}
			board[first.xx][++ny] = first.sizee;
		}
	}
	else if (orient == 1) {
		while (!que1.empty()) {
			B_I first = que1.top();
			que1.pop();
			int ny = first.yy;
			while (board[first.xx][++ny] == 0 && ny != N) {}
			board[first.xx][--ny] = first.sizee;
		}
	}
	else if (orient == 2) {
		while (!que2.empty()) {
			B_I first = que2.top();
			que2.pop();
			int nx = first.xx;
			while (board[--nx][first.yy] == 0 && nx != -1) {}
			board[++nx][first.yy] = first.sizee;
		}
	}
	else {
		while (!que3.empty()) {
			B_I first = que3.top();
			que3.pop();
			int nx = first.xx;
			while (board[++nx][first.yy] == N && nx != -1) {}
			board[--nx][first.yy] = first.sizee;
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			que0.push({ i,j,board[i][j] });
			que1.push({ i,j,board[i][j] });
			que2.push({ i,j,board[i][j] });
			que3.push({ i,j,board[i][j] });
		}
	}


}

void enter() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
			if(board[i][j] != 0){
				B_I foradd = { i,j,board[i][j] };
				que0.push(foradd);
				que1.push(foradd);
				que2.push(foradd);
				que3.push(foradd);
			}
		}
	}
}


void see() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

void quesee() {
	cout << "[que0]좌측열기준" << endl;
	while (!que0.empty()) {
		cout << que0.top().xx <<" "<<que0.top().yy<<" "<<que0.top().sizee<< endl;
		que0.pop();
	}
	cout << "[que1]우측열기준" << endl;
	while (!que1.empty()) {
		cout << que1.top().xx << " " << que1.top().yy << " " << que1.top().sizee << endl;
		que1.pop();
	}
	cout << "[que2]위행기준" << endl;
	while (!que2.empty()) {
		cout << que2.top().xx << " " << que2.top().yy << " " << que2.top().sizee << endl;
		que2.pop();
	}
	cout << "[que3]아래행기준" << endl;
	while (!que3.empty()) {
		cout << que3.top().xx << " " << que3.top().yy << " " << que3.top().sizee << endl;
		que3.pop();
	}

}
int main() {
	/*
	7.25
		- 기울이는 기능 ,합치는 기능 필요할 것이다.
			- 합치는 기능은 먼저 조건검사를 통해서 해당 블록의 블록이 합쳐진 적이 있는지를 먼저 검사한다.
		- 뭘만들어야할지랑, 시간복잡도만 고려한다.

	7.24
		·기울이는 기능 ,합치는 기능 필요할 것이다.
			- 합치는 기능은 먼저 조건검사를 통해서 해당 블록의 블록이 합쳐진 적이 있는지를 먼저 검사한다.
	
	7.23
	자료구조 : 모든 블록의 위치가 담겨있는 큐.
		큐의 데이터 타입은 구조체로 {int x,int y, int number}.
		

	기울이기(방향) 함수
	좌,우,위,아래
		먼저 충돌 (충돌한 블럭은 빈공백, 충돌된 블럭은 숫자*2) 
			같은 행이고
			숫자가 같고
			사이에 0말고는 없으면
			이미 한번 합쳐진 블럭인지 검사. -> 
				아니라면 합쳐.== 숫자*2
		그리고나서 빈공백 채워주기.

----------------------------
<백트래킹..? or 배열에 저장하는 방법..?(메모이제이션,dp)>


	다섯번 이동해서 최댓값.DFS
	좌				우				위				아래 O(2^10) => O(10^2)
좌,우,위,아래	좌,우,위,아래	좌,우,위,아래	좌,우,위,아래
	*/


	enter();
//	quesee();
//	tilt(0); // 0:좌,1:우,2:위,3:아래
	tilt(0);
	mix(0);
	tilt(0);
//	tilt(2);
//	tilt(3);
	see();
	system("pause");
}