#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
using namespace std;
int T;
int Answer = 0;
int aa;
int sero, karo, dochak;
int change[2001][1501] = { 0, };
int hang = 1;
int MEMORY = 1;
typedef pair <int, int> Pair;
//vector <int> sero_info[1501];
/*
	1열 2열 3열
	각 행마다 이제 열이 변할 수가 있다.
	시간제한 : O(300000000)
	T<=70,N==sero<=1500,k==karo<=2000,m==dochak<=10^5
	행이 필요하다.
	karo 의 갯수만큼 행이 생긴다.

	사다리는 만약에 1 진행한다 치면,
	DFS(행0,열1,cnt0) // 0은 무시한갯수 
	행이 만약에 hang값과 동일하다면
	열이 dochak과 같다면 ans = min(ans,무시한갯수) 
	만약에 ans 가 987654321 라면 ans = -1;
	return ans;
	0행 1열부터 시작해서.
	1행 1열. 
	//  만약에 change[1][1]값이 0이면 DFS(행+1,1열,cnt);
	//	만약에 change[1][1]값이 0이 아니면, CHANGE 갈수도 있고
			DFS(행+1, change[1][1]열,cnt)
			//		무시할거면
			//      무시한갯수 cnt 증가
			DFS(2행, 1열, cnt+1)

	메모이제이션
		벡터 [2001][1501] <Pair <int,int> >  도착점, 무시한갯수.

		해당 좌표에 도착점이 있으면 cnt + 해당 무시한갯수 return;

*/

int mmin(int a, int b) {
	if (a < b) return a;
	else return b;
}

void enter() {
	cin >> sero >> karo >> dochak;
	for (int i = 0; i < karo; i++) {
		int temp_x, temp_y;
		cin >> temp_x >> temp_y;
		change[hang][temp_y] = temp_x;
		change[hang++][temp_x] = temp_y;
	}
}

void initialization() {

	for (int i = 1; i < 2001; i++) {
		for (int j = 1; j < 1501; j++) {
			change[i][j] = 0;
//			Memo[i][j].clear();
		}
	}
	Answer = 0;
	hang = 1;
}
/*
void debug() {
	for (int i = 0; i < hang; i++) {
		for(int j = 1 ; j< sero+1;j++){
			cout << i << "행" << j << "열" << endl;
			cout << "바뀌는 열"<<change[i][j] << endl;
		}
	}
	for (int i = 0; i < dochak_info.size(); i++) {
		cout << "출발 : " << dochak_info[i].first << "도착 :" << dochak_info[i].second << endl;
	}
}
*/
/*
사다리는 만약에 1 진행한다 치면,
DFS(행0,열1,dochak,cnt0) // 0은 무시한갯수
행이 만약에 hang값과 동일하다면
열이 dochak과 같다면 ans = min(ans,무시한갯수)
return ans;
0행 1열부터 시작해서.
1행 1열.
//  만약에 change[1][1]값이 0이면 DFS(행+1,1열,cnt);
//	만약에 change[1][1]값이 0이 아니면, CHANGE 갈수도 있고
DFS(행+1, change[1][1]열,cnt)
//		무시할거면
//      무시한갯수 cnt 증가
DFS(2행, 1열, cnt+1)

DFS 나가서 	만약에 ans 가 987654321 라면 ans = -1;
*/
void DFS(int h, int y, int doch ,int cnt) {
//cout << MEMORY++ << endl;
	cout << h << "행" << y << "열" << endl;
	cout << "무시한 갯수" << cnt << endl;

	if (aa <= cnt) return;

	while(change[h + 1][y] == 0){
		h = h + 1;
		if (h == hang) {
//			cout <<"h : "<< h << endl;
//			cout <<"hang : "<< hang << endl;
			if (y == doch) {
				aa = mmin(aa, cnt);
			}
			return;
		}
	}
	if (change[h + 1][y] != 0){ // 최대 2000번까지 가능.
		int copy_cnt = cnt;
		DFS(h + 1, change[h + 1][y], doch, cnt);
		cnt = copy_cnt;
		DFS(h + 1, y, doch, cnt + 1);
	}
}


int main() {

	int T, test_case;


	

	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		initialization();
		enter();
	//	debug();
		

		for (int i = 0; i < dochak; i++) {
			int s, g;//start,goal
			cin >> s >> g;
			aa = 987654321;
			DFS(0, s, g, 0);//int 형 4개.
			if (aa == 987654321) aa = -1;
			//			cout << aa << endl;
			Answer = Answer + aa;
			



		}
	

		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}
	system("pause");
	return 0;
}