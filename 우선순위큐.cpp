#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <functional>//for greater
using namespace std;
priority_queue<int> pq;
typedef pair<int, int> Pair;

struct cmp {
	bool operator()(Pair x, Pair y) {
		return x.first > y.first;
	}
};


int main() {
	priority_queue< Pair, vector<Pair>,greater<Pair>> pq;
	pq.push(make_pair(1, 2));
	pq.push(make_pair(2, 3));
	pq.push(make_pair(4, 1));
	pq.push(make_pair(6, 2));
	pq.push(make_pair(7, 7));
	pq.push(make_pair(8, 9));
	pq.push(make_pair(8, 8));
	pq.push(make_pair(8, 7));
	pq.push(make_pair(8, 6));


	while (!pq.empty()) {
		cout << pq.top().first <<" "<<pq.top().second<<endl;
		pq.pop();
	}

	system("pause");
}