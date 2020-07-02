#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <utility>
#include<string.h>
#include <vector>
#include <algorithm>
using namespace std;


int N, M;
int minest = 2147483647;
int room[50][50] = { 0, };
int newboard[50][50] = { 0, };
vector <pair<int,int>> vec;
pair<int, int> foradd;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
//疎,酔,是,焼掘
// 0引1聖 煽舌 拝 困斗 持失
vector<int> ind;
vector <int> index;
queue <pair<int, int>> que;
queue <pair<int, int>> que2;

void enterNum() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> room[i][j];
			if (room[i][j] == 2) {
				foradd = make_pair(i, j);
				vec.push_back(foradd);
				room[i][j] = -2;
			}
			else if (room[i][j] == 1) {
				room[i][j] = -1;
			}
		}
	}
}

void combination() {
	int ALL = vec.size();
	for (int i = 0; i < ALL; i++) {
		index.push_back(i);
	}

	// M鯵税 1 蓄亜
	for (int i = 0; i<M; i++) {
		ind.push_back(1);
	}
	// vec.size-M鯵 税 0 蓄亜
	for (int i = 0; i<ALL - M; i++) {
		ind.push_back(0);
	}
	// 舛慶
	sort(ind.begin(), ind.end());
	//授伸
	

}
//政遂馬檎 1, 焼艦檎 0.
void isUseful(int x, int y,int * zerocnt) {
	if (x < 0 || y < 0 || x > N - 1 || y > N - 1) return;
	for (int i = 0; i < 4; i++){
		int j = 0;
		if (x + dx[i] >= 0 && x + dx[i] < N && y + dy[i] >= 0 && y + dy[i] < N ) {
			foradd = make_pair(x, y);
			que2.push(foradd);
			return;
		}
		
		// newboard[x + dx[i]][y + dy[i]] == 0 背捜生稽潤, -2 搾醗失 郊戚君什亜 赤希虞亀 朔因娃戚 乞砧 託檎 曽戟鞠惟懐 背爽醸陥. 遁閃蟹哀 焼戚税 爽痕拭 朔因娃 赤聖 凶幻 蓄亜馬亀系 梅奄 凶庚戚陥.
	}
	// 走榎 雌殿澗 舌掘失 赤澗 蕉級精 陥 蓄亜吉 雌殿陥. 舌掘失 蒸澗 蕉級 掻拭.

}

int checkZero() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (newboard[i][j] == 0)
				return 1;
		}
	}
	return 0;
}
void printfordebug() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << newboard[i][j]<<" ";
		}cout << endl;
	}
}

void spread(int x, int y, int cnt, int * zerocnt) {
	int nx;
	int ny;
	if (cnt == 0) {
		++(*zerocnt);
	}

	//if (room[nx][ny] == -1) {
	//}
	if (newboard[x][y] == -2) {
		//朝錘闘 装亜獣佃匝 琶推蒸壱, 陥幻, 背雁 疎妊亀 遁閃蟹亜澗 蝕拝拝 呪 赤惟 泥拭 蓄亜.
		newboard[x][y] = -3;

		for (int i = 0; i < 4; i++) {
			nx = x + dx[i];
			ny = y + dy[i];
			isUseful(nx, ny, zerocnt);
		}

		printfordebug();
		cout << "cnt : " << cnt << endl;
	}
	else if (newboard[x][y] == 0) {
		cout << "0昔走繊 x : " << x <<"y : "<< y<<endl;

		newboard[x][y] = cnt;


		for (int i = 0; i < 4; i++) {
			nx = x + dx[i];
			ny = y + dy[i];
			if (newboard[nx][ny] == 0) {
				++(*zerocnt);
			}
			// zerocnt研 潅形辞, 泥亜 廃腰 希 宜 呪 赤惟 背爽醸壱. 
			// 
			isUseful(nx, ny, zerocnt);

		}

		printfordebug();
		cout << "cnt : " << cnt << endl;
	}



	
}

void solve() {

	combination();


	do {
		cout << "けけけけけけけけけけけけけけけけけ" << endl;
		int cnt = 0;
		int zeroCnt = 1;
		while (!que2.empty()) { que2.pop(); }
		while (!que.empty()){ que.pop();  }
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				newboard[i][j] = room[i][j];
			}
		}
		// 窒径
		for (int i = 0; i<ind.size(); i++) {
			if (ind[i] == 1) {
				foradd = make_pair(vec[i].first, vec[i].second);
				que.push(foradd);

			}
		}
		/*
		1. 背雁 疎妊奄層生稽 坦製殖 獣拙戚艦猿 雁尻備 昔切 級嬢哀 凶 cnt葵 0生稽 級嬢穐陥亜 雌馬疎酔 遁閃蟹哀 蕉級 陥 泥拭 隔嬢爽虞.
		cnt 葵 装亜 獣徹虞.
		
		*/
		while (zeroCnt != 0) {
			zeroCnt = 0;

			while (!que2.empty()) {
				que.push(que2.front());
				cout << que.front().first << "泥2 " << que.front().second;
				que2.pop();
			}

			while (!que.empty()) {
				pair<int, int> tempvec = que.front();
				cout << tempvec.first << "泥1 " << tempvec.second << endl;
				spread(tempvec.first, tempvec.second, cnt, &zeroCnt);
		
				que.pop();
			}
			if (!checkZero()) {
				// 0戚 赤生檎, 1 --> 蒸生檎 0.
				break;
			}
			
			cnt++;
		}
		//伊紫馬奄稽澗 希戚雌 遁閃蟹哀 員戚 蒸陥.
		//己 穿端稽 挫聖凶亀 朔因娃戚 蒸生檎 益闇 置借葵 幻級嬢爽奄.
		if (!checkZero()) {

			minest = min(minest, cnt);
		}

	} while (next_permutation(ind.begin(), ind.end()));

	
}
int main() {
	enterNum();
	solve();
	if (minest == 2147483647) cout << -1;
	else cout << minest;
	system("pause");
}