/*
You should use the standard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
using namespace std;
int T;
int N;
int K;
int ans = 987654321;
vector <int> sik[2];
vector <int> sum_v;
priority_queue <int, vector<int>, greater<int> > pq[2];

void enter() {
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		int temp;
		cin >> temp;
		pq[0].push(temp);
	}
	for (int i = 0; i < N; i++) {
		int temp;
		cin >> temp;
		pq[1].push(temp);
	}

}

void initializaiton() {
	sik[0].clear();
	sik[1].clear();
	sum_v.clear();
}

/*
61 34
61 33
61 14
61 13

64 33
64 13

31 14
31 13


*/
void vectorhwa() {
	for (int i = 0; i < K; i++) {
		sik[0].push_back(pq[0].top());
		sik[1].push_back(pq[1].top());
		pq[1].pop();
		pq[0].pop();
	}

}

int main(int argc, char** argv)
{
	int test_case;
	cin >> T;

	for (test_case = 0; test_case < T; test_case++)
	{

		enter();
		initializaiton();
		vectorhwa();
		sort(sik[0].begin(), sik[0].end(), less<int>());
		sort(sik[1].begin(), sik[1].end(), greater<int>());
		for (int i = 0; i < K; i++) {
			sum_v.push_back(sik[0][i] + sik[1][i]);
		}
		sort(sum_v.begin(), sum_v.end(), greater<int>()); // 벡터 소트가 이렇게 편할줄이야.
//		cout << sum_v[0] << endl;



		while (!pq[0].empty())pq[0].pop();
		while (!pq[1].empty())pq[1].pop();
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		Implement your algorithm here.
		The answer to the case will be stored in variable Answer.
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////

		// Print the answer to standard output(screen).
		cout << "Case #" << test_case + 1 << endl;
		cout << sum_v[0] << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}