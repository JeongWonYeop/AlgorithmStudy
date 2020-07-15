#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
#include <functional>
using namespace std;
int check_board[101][101] = { 0, };
int dx[5] = { 0, -1,1,0,0 };
int dy[5] = { 0,0,0,1,-1 };
int R;
int C;
int M;
int people_C = 0;
int result = 0;
pair <int, int> foradd;
queue <pair <int, int>> temp_que;
/*
위 아 오 왼

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
s번 반복하고,
d가 1일때 r가 -- 되고, 만약에 0이면 d를 2로 바꿔준다
d가 2일때 r가 ++ 되고, 만약에 R이면 d를 1로 바꿔준다
d가 3일때 c가 ++ 되고, 만약에 C이면 d를 4로
d가 4일때 c가 -- , 0이면 d를 3로
*/

/* 이부분 문제 잘못읽어서 다시 짜야한다. 2마리 이상 있을 수 있다 인데 없다 로 봤다.*/
void check_shark(vector <Shark> &shark_i) {
	priority_queue < pair<int,int>, vector <pair<int, int>>, less<pair<int, int>> > less_sharklist;
	for (int i = 1; i < R + 1; i++) {
		for (int j = 1; j < C + 1; j++) {
			check_board[i][j] = 0;
		}
	}

	for (int i = 0; i < shark_i.size(); i++) {
		++check_board[shark_i[i].r][shark_i[i].c];
		if (check_board[shark_i[i].r][shark_i[i].c] == 2) {
			 foradd = { shark_i[i].r , shark_i[i].c };
			 temp_que.push(foradd);
		}
	}

	while (!temp_que.empty()) {
		for (int i = 0; i < shark_i.size(); i++) {
			if (shark_i[i].r == temp_que.front().first && shark_i[i].c == temp_que.front().second) {
				less_sharklist.push({ shark_i[i].z , i});
			}
		}
		less_sharklist.pop();
		priority_queue <int, vector<int>, less<int>> t_q;
		while (!less_sharklist.empty()) {
			t_q.push(less_sharklist.top().second);
			less_sharklist.pop();
		}
		while (!t_q.empty()) {
			shark_i.erase(shark_i.begin() + t_q.top());
			t_q.pop();
		}


		temp_que.pop();
	}






}


void shark_change(vector <Shark> & shark_i) {
	for (int i = 0; i < shark_i.size(); i++) {
		int cnt = shark_i[i].s;
		while (cnt > 0) {
			if (shark_i[i].d == 1) {
				shark_i[i].r = shark_i[i].r + dx[shark_i[i].d];
				if (shark_i[i].r == 0) {
					++shark_i[i].r;
					++shark_i[i].r;
					shark_i[i].d = 2;
				}
			}
			else if (shark_i[i].d == 2) {
				shark_i[i].r = shark_i[i].r + dx[shark_i[i].d];
				if (shark_i[i].r == R + 1) {
					--shark_i[i].r; // 갔던거 취소하므로, 그자리 유지.
					--shark_i[i].r; // 다시 한칸 튕겨져나와야되므로.
					shark_i[i].d = 1;
				}
			}
			else if (shark_i[i].d == 3) {
				shark_i[i].c = shark_i[i].c + dy[shark_i[i].d];
				if (shark_i[i].c == C + 1) {
					--shark_i[i].c;
					--shark_i[i].c;
					shark_i[i].d = 4;
				}
			}
			else if (shark_i[i].d == 4) {
				shark_i[i].c = shark_i[i].c + dy[shark_i[i].d];
				if (shark_i[i].c == 0) {
					++shark_i[i].c;
					++shark_i[i].c;
					shark_i[i].d = 3;
				}
			}
			cnt--;
		}

	}
}

void catch_shark(vector <Shark> & shark_i) {
	++people_C;
	priority_queue < int, vector <int>, greater<int> > catch_shark_queue;
	while (!catch_shark_queue.empty()) {
		catch_shark_queue.pop();
	}
	for (int i = 0; i < shark_i.size(); i++) {
		if (shark_i[i].c == people_C) {
			catch_shark_queue.push(shark_i[i].r);
		}
	}

	for (int i = 0; i < shark_i.size(); i++) {
		if (shark_i[i].c == people_C && shark_i[i].r == catch_shark_queue.top()) {
			result = result + shark_i[i].z;
			shark_i.erase(shark_i.begin() + i);
		}
	}

}

int main() {

	cin >> R >> C >> M;
	vector <Shark> shark_info;
	for (int i = 0; i < M; i++) {
		int r, c, s, d, z;
		cin >> r >> c >> s >> d >> z;
		shark_info.push_back({ r,c,s,d,z });

	}


	while (people_C < C) {

		catch_shark(shark_info);
		shark_change(shark_info);
		check_shark(shark_info);

	}

	

		cout << result << endl;


	system("pause");

}
/*
x, y , 상어마리수
x1,y1,스피드,이동방향(1:위,2:아래,3:오,4:왼),크기
x2,y2
x3,y3

한번 반복때. 사람은 한칸 넘어가고 그 라인에 상어 중 가장 행이 위쪽행이 녀석이 먹힌다.
상어도 움직인다.

만약에 같은좌표에 있는 상어발생시에 크기 작은 상어는 없어진다.

초기 좌표<구조체 벡터> -> 사람 움직임(캐치)
상어움직임<구조체 백터>-> 상어정리 -> 사람 움직임(캐치) <반복>


사람움직임 : 벡터 검색 후 C가 (people_C)1인 해당 벡터 크기 result+size 해주고, erase.
상어움직임 :
상어정리 : 체크보드 초기화 ,상어 좌표 입력-> 2인 좌표. -> 벡터 검색 후 작은 벡터 erase.

people_C 증가시키면서 반복. C+1이 되기전까지.

*/