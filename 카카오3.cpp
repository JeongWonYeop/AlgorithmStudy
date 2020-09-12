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

string info_[50000][4];
int i_info[50000];
/*
지원자가 지원서에 입력한 4가지의 정보와 획득한 코딩테스트 점수를 하나의 문자열로 구성한 값의 배열 info,
개발팀이 궁금해하는 문의조건이 문자열 형태로 담긴 배열 query가 매개변수로 주어질 때,

개발언어 직군 경력 소울푸드 점수

*/
vector<int> solution(vector<string> info, vector<string> query) {
	vector<int> answer;

	for (int i = 0; i < query.size(); i++) {
		int temp = 0;//foradd

		for (int j = 0; j<3; j++) query[i].replace(query[i].find(" and "), 5, " ");
		// cout << query[i] << endl;
		string com_c[4];

		for (int k = 0; k < 4; k++) {
			com_c[k] = query[i].substr(0, query[i].find(" "));
			query[i].erase(query[i].begin(), query[i].begin() + query[i].find(" ") + 1);
		}
		//	cout << endl;
		//	cout << query[i] << endl;


		int com_i = stoi(query[i]);






		// 비교대상 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

		for (int kk = 0; kk < info.size(); kk++) {
			if (info_[kk][0].empty()|| info_[kk][1].empty()|| info_[kk][2].empty()|| info_[kk][3].empty()) {

				int ttend = 0;
				for (int p = 0; p < 4; p++) {
					info_[kk][p] = info[kk].substr(0, info[kk].find(" "));
					info[kk].erase(info[kk].begin(), info[kk].begin() + info[kk].find(" ") + 1);
					if (info_[kk][p] != com_c[p]&&com_c[p] != "-" ) {
						ttend = 1;
					}
				}

				if (ttend == 1) break;

				i_info[kk] = stoi(info[kk]);

				if ((info_[kk][0] == com_c[0] || com_c[0] == "-") && (info_[kk][1] == com_c[1] || com_c[1] == "-") && (info_[kk][2] == com_c[2] || com_c[2] == "-") && (info_[kk][3] == com_c[3] || com_c[3] == "-") && i_info[kk] >= com_i) {
					++temp;
				}




			}
			else {
				if ((info_[kk][0] == com_c[0] || com_c[0] == "-") && (info_[kk][1] == com_c[1] || com_c[1] == "-") && (info_[kk][2] == com_c[2] || com_c[2] == "-") && (info_[kk][3] == com_c[3] || com_c[3] == "-") && i_info[kk] >= com_i) {
					++temp;
				}
				//cout << "내용이있음";
			}

		}






		answer.push_back(temp);
			cout << temp << endl;
	}








	return answer;
}


int main() {
//	string str1 = "java and backend and junior and pizza 100";
//	for(int i = 0; i<3;i++)	str1.replace(str1.find(" and "),5," ");
//	cout << str1 << endl;

/*
	string str2 = "java backend junior pizza 150";
	cout<< str2.substr(0, str2.find(" "));
	str2.erase(str2.begin(), str2.begin() + str2.find(" ")+1);
	cout << str2.substr(0, str2.find(" "));
	str2.erase(str2.begin(), str2.begin() + str2.find(" ") + 1);
	cout << str2.substr(0, str2.find(" "));
	str2.erase(str2.begin(), str2.begin() + str2.find(" ") + 1);
	cout << str2.substr(0, str2.find(" "));
	str2.erase(str2.begin(), str2.begin() + str2.find(" ") + 1);
	cout << endl;
	cout << str2 << endl;
	int a = stoi(str2);
	cout << a + 1<<endl;
	*/
	cout << solution({ "java backend junior pizza 150","python frontend senior chicken 210","python frontend senior chicken 150","cpp backend senior pizza 260","java backend junior chicken 80","python backend senior chicken 50" }, { "java and backend and junior and pizza 100","python and frontend and senior and chicken 200","cpp and - and senior and pizza 250","- and backend and senior and - 150","- and - and - and chicken 100","- and - and - and - 150" }).front();
	
	
	system("pause");
}
