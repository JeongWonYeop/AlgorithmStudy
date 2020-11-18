#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include <string>
#include <cstring>
using namespace std;
int N, K, m;
int result = 987654321;
vector <int> Ns;
queue <int> left_que;
queue <int> right_que;

void spread(int index, int l_r, int k, int * resultt) {
	int new_index = 0;
	if (l_r == -1) {
		new_index = index - (k - 1);
		if (new_index < 0) {
			if ((index-1) >= 0) {
				*resultt = *resultt + 1;
				return;
			}
			else {
				return;
			}
		}
		*resultt = *resultt + 1;
		left_que.push(new_index);
	}
	else if (l_r == 1) {
		new_index = index + (k - 1);
	//	cout << new_index << endl;
		if (new_index > N-1) {
			if (index + 1 <= N - 1) {
				*resultt = *resultt + 1;
				return;
			}
			else return;
		}
		*resultt = *resultt + 1;
		right_que.push(new_index);
	}


}


int main() {
	cin >> N >> K;
	int temp;
	for (int i = 0; i < N; i++) {
		cin >> temp;
		Ns.push_back(temp);
	}

	vector <int> min(Ns);
	sort(min.begin(), min.end());
	m = min[0];

	for (int i = 0; i < N; i++) {
		if (Ns[i] == m) {
			m = i;
			break;
		}
	}


	for (int i = 0; i < K; i++) {
		int resultt = 0;
		if ((m - i) < 0 || m + K - 1 - i > N) continue;


	//	cout << m - i << " " << m + K - 1 - i << endl;
		resultt++;

		left_que.push(m - i);
		right_que.push(m + K - 1 - i);

		while (!left_que.empty()) {
			spread(left_que.front(), -1, K , &resultt);
			left_que.pop();
		}
	//	cout << "왼쪽 값" << resultt << endl;

		while (!right_que.empty()) {
			spread(right_que.front(), 1, K, &resultt);
			right_que.pop();
		}
	//	cout << "우측더한 값" << resultt << endl;

	//	cout << resultt << endl;
		if (resultt < result) {
	//		cout << resultt << endl;
			result = resultt;
		}
	}


	cout << result;
	system("pause");
}



