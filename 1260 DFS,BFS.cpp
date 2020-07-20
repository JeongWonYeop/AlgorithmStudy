#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
#include <functional>
#include <string.h> 
using namespace std;

int N, M, V;
priority_queue<int, vector<int>, greater<int>> que[1001];
priority_queue<int, vector<int>, greater<int>> que2[1001];
int visited[1001] = { 0, };
vector<int> result2;


void DFS(int V) {

	result2.push_back(V);
	visited[V] = 1;
	while(!que[V].empty()){
		if (visited[que[V].top()] != 1) {
			DFS(que[V].top());
		}
		que[V].pop();
	}

}


void BFS(int V) {
	vector<int> result;
	queue <int> BFSQue;
	while(!que2[V].empty()){
		BFSQue.push(que2[V].top());
		que2[V].pop();
	}
	result.push_back(V);
	visited[V] = 1;
	while (!BFSQue.empty()) {
		int bfsfront = BFSQue.front();
		while (!que2[bfsfront].empty()) {
			BFSQue.push(que2[bfsfront].top());
			que2[bfsfront].pop();
		}

		if(visited[bfsfront] != 1){
			result.push_back(bfsfront);
		}
		visited[bfsfront] = 1;
		BFSQue.pop();
	}


	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << " ";
	}
	cout << endl;



}



int main() {
	cin >> N >> M >> V;

	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		que[a].push(b);
		que2[a].push(b);
		que[b].push(a);
		que2[b].push(a);
	}


	DFS(V);
	for (int i = 0; i < result2.size(); i++) {
		cout << result2[i] << " ";
	}
	cout << endl;
	memset(visited, 0, sizeof(visited));
	BFS(V);
}