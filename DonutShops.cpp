#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <utility>
#include <stack>
#include<string.h>
using namespace std;


int main() {
	int testcase;
	int price[3];
	int answer[2] = { 0, };
	cin >> testcase;
	while( testcase-- > 0 ){
		for(int i = 0 ; i < 2 ; i++)answer[i] = 0;
		cin >> price[0] >> price[1] >> price[2];
	
		for(int i = 1 ; i <= 1000000000 ; i++){
			if (price[0] >= price[2]) answer[0] = -1;
			if (price[0] <= (price[2] / price[1])) {
				answer[1] = -1;
			}
			int endpoint;
			endpoint = price[1];
			if (i < endpoint) {
				if (i*price[0] < price[2]) answer[0] = i;
			}
		
			if (i*price[0] > price[2]) answer[1] = price[1];

			if (answer[0] != 0 && answer[1] != 0) break;
		}

		cout << answer[0] << " " << answer[1] << endl;

	}

	/*

4 5 20
2 2 3
1000000000 1000000000 1000000000

5 10 4
-1 20

8 -1
1 2
-1 1000000000

*/
}