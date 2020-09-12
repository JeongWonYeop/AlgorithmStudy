#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <cstring>
#include <utility>
#include <functional>
#include <string>
#include <vector>
using namespace std;
/*
	oreders의 모든 구성 읽은다음, 모든 구성이 하나씩 들어있는 하나의 벡터로 새롭게 구성해라.
	그거를 조합으로 이제 하나씩 ex.2 3 4 5뽑아라.
		기존의 orders를 하나하나 비교하면서 각 구성별로 포함돼있는거 비교해보라 만약 2이상되는순간 후보벡터에 추가하고 return.



*/
int check_course[50] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,0 };

vector<string> solution(vector<string> orders, vector<int> course) {
	vector<string> answer;
	vector<char> new_arr;
	for (int i = 0; i < orders.size(); i++) {
		for (int j = 0; j < orders[i].size(); j++) {
			char t_c = orders[i][j];
			int temp = 0;
			for (int p = 0; p < new_arr.size(); p++) {
				if (new_arr.at(p) == t_c) {
					temp = 1;
				}
			}
			if (temp == 0) {
				new_arr.push_back(t_c);
			}
		}
	}


	/*
	for (int p = 0; p < new_arr.size(); p++) {
		cout << new_arr[p] << endl;
	}
	*/
	sort(course.begin(), course.end(), greater<int>());
	for(int co = 0 ; co < course.size(); co++){
		vector<int> a;
		vector<char> combi_arr;
		int n = new_arr.size();
		// 0과1을 저장 할 벡터 생성
		vector<int> ind;

		// k=2, 2개를 뽑으니까
		int k = course[co];

		// k개의 1 추가
		for (int i = 0; i<k; i++) {
			ind.push_back(1);
		}

		// n-k의 0 추가
		for (int i = 0; i<n - k; i++) {
			ind.push_back(0);
		}

		// 정렬
		sort(ind.begin(), ind.end());
		int imeu = 1;
		//순열
		do {
			
			combi_arr.clear();
			for (int i = 0; i<ind.size(); i++) {
				if (ind[i] == 1) {
					combi_arr.push_back(new_arr[i]);
				}
			}

			/*
				for (int i = 0; i < combi_arr.size(); i++) {
					cout << combi_arr[i] << " ";
				}cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
				*/
				int total_sum = 0;
				vector<int> or_num_list;
				or_num_list.clear();
				for (int or_num = 0; or_num < orders.size(); or_num++) {//여기가 이제 하나의 orders안에 x,y가있는가판별
		
					int temp_sum = 0;
					for (int j = 0; j < orders[or_num].size(); j++) { // orders 구성 파헤치는중.
						for (int i = 0; i < combi_arr.size(); i++) {//이거는 x,y뽑아낸것.
			//				cout << combi_arr[i] << "와" << orders[or_num][j] << endl;
							if (combi_arr[i] == orders[or_num][j]) {
								++temp_sum;
								or_num_list.push_back(or_num);
							}
						}
					}
					if (temp_sum == combi_arr.size()) { // x,y가 있더라 하는거지.
						++total_sum;
					}

				}


				//cout << endl;
			
					//	cout << "있더라하는거지"<<total_sum << endl;
					if (total_sum >= 2) {
						int alsame = 0;

						for (int p = 1; p < or_num_list.size(); p++) {
							if (check_course[or_num_list[0]] != check_course[or_num_list[p]]) {
								alsame = -1;
								break;
							}
						}
						if (alsame == 0) continue;

							for (int i = 0; i < or_num_list.size(); i++) {
								check_course[or_num_list[i]] = 1;
								cout <<" "<<i<<" "<< or_num_list[i] << " ";
							}
							string for_add;
							for (int i = 0; i < combi_arr.size(); i++) {
								string a;
								a.push_back(combi_arr[i]);
								for_add = for_add + a;
							}
							answer.push_back(for_add);
					

							cout << endl;
						
					}
				


			
		} while (next_permutation(ind.begin(), ind.end()));

	}

	for (int i = 0; i < answer.size(); i++) {
		for (int j = 0; j < answer[i].size(); j++) {
			cout << answer[i][j];
		}cout << endl;
	}

	return answer;
}


int main() {
	cout << solution({ "ABCFG", "AC", "CDE", "ACDE", "BCFG", "ACDEH" }, { 2,3,4 }).empty();
	system("pause");
}
