#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <functional>
using namespace std;
int check_board[101][101] = { 0, };
int dx[5] = { 0, -1,1.0,0};
int dy[5] = { 0, 0,0.1,-1};
int R;
int C;
int M;
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
void shark_change(vector <Shark> & shark_i) {
	for (int i = 0; i < shark_i.size(); i++) {
		int cnt = shark_i[i].s;
		while (cnt > 0) {
			if (shark_i[i].d == 1) {
				shark_i[i].r = shark_i[i].r + dx[shark_i[i].d];
				if (shark_i[i].r == 0) shark_i[i].d = 2;
			}
			else if (shark_i[i].d == 2) {
				shark_i[i].r = shark_i[i].r + dx[shark_i[i].d];
				if (shark_i[i].r == R) shark_i[i].d = 1;
			}
			else if (shark_i[i].d == 3) {
				shark_i[i].c = shark_i[i].c + dy[shark_i[i].d];
				if (shark_i[i].c == C) shark_i[i].d = 4;
			}
			else if (shark_i[i].d == 4) {
				shark_i[i].c = shark_i[i].c + dy[shark_i[i].d];
				if (shark_i[i].c == 0) shark_i[i].d = 3;
			}
			cnt--;
		}

	}
}
int main() {

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
x, y , 상어마리수
x1,y1,스피드,이동방향(1:위,2:아래,3:오,4:왼),크기
x2,y2
x3,y3

한번 반복때. 사람은 한칸 넘어가고 그 라인에 상어 중 가장 행이 위쪽행이 녀석이 먹힌다.
상어도 움직인다.

만약에 같은좌표에 있는 상어발생시에 크기 작은 상어는 없어진다.

초기 좌표<구조체 벡터> -> 사람 움직임(캐치)
상어움직임<구조체 백터>-> 상어정리 -> 사람 움직임(캐치) <반복>


상어움직임 : 
상어정리 : 체크보드 초기화 ,상어 좌표 입력-> 2인 좌표. -> 벡터 검색 후 작은 벡터 erase.
사람움직임 : 벡터 검색 후 C가 (people_C)1인 해당 벡터 크기 result+size 해주고, erase.
people_C 증가시키면서 반복. C+1이 되기전까지.

*/