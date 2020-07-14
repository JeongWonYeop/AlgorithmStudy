#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <stdlib.h>
using namespace std;
int casee = 0;


struct cmp {
	bool operator()(int a,int b) {
		if (abs(a) == abs(b)) return a > b;
		else return abs(a) > abs(b);

	}

};


int main() {
	priority_queue<int, vector<int>, cmp> pq;
	cin >> casee;
	while (casee > 0) {
		int a;
		cin >> a;
		if (a == 0) {
			if(!pq.empty()){
				cout << pq.top() << endl;
				pq.pop();
			}
			else cout << 0 << endl;
		}
		else {
			pq.push(a);
		}


		--casee;
	}


	system("pause");
}