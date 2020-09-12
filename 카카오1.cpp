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


string solution(string new_id) {




	for (int i = 0; i < new_id.size(); i++) {
		int temp_c = new_id.at(i);
		if (temp_c >= 65 && temp_c <= 90) {
			string t_a;
			char a = temp_c += 32;
			t_a.push_back(a);
			new_id.replace(new_id.begin() + i, new_id.begin() + i+1, t_a);
		}
	}

	for (int i = 0; i < new_id.size(); i++) {
		int temp_c = new_id.at(i);
		//알파벳 소문자, 숫자, 빼기(-), 밑줄(_), 마침표(.)를 제외한 모든 문자를 제거합니다.
		if ((temp_c >= 97 && temp_c <= 122) || (temp_c >= 48 && temp_c <= 57) || temp_c == 45 || temp_c == 95 || temp_c == 46) {
		}else {
			new_id.erase(new_id.begin()+i);
			i--;
		}
		//if(new_id.at(i) == );
	}

	for (int i = 0; i < new_id.size(); i++) {
		int temp_c = new_id.at(i);
		if (temp_c == 46) {
			if(i+1 < new_id.size()){
				int temp_c2 = new_id.at(i + 1);
				if (temp_c2 == 46) {
					new_id.erase(new_id.begin() + (i + 1));

					i--;
				}
			}
		}
	}

	if(!new_id.empty()){
		if (new_id.at(0) == '.') {
			new_id.erase(new_id.begin() + 0);
		}
	}
	if (!new_id.empty()) {
		if (new_id.at(new_id.size() - 1) == '.') {
			new_id.erase(new_id.begin() + new_id.size() - 1);
		}
	}


	if (new_id.empty()) {
		new_id.push_back('a');
	}


	if (new_id.size() >= 16) {
		new_id.erase(15);
	}

	if (!new_id.empty()) {
		if (new_id.at(new_id.size() - 1) == '.') {
			new_id.erase(new_id.begin() + new_id.size() - 1);
		}
	}


	if (!new_id.empty()) {
		while (new_id.size() <= 2 && new_id.size() >= 1) {
			new_id.push_back(new_id.at(new_id.size()-1));
		}
	}
	string answer = new_id;
	return answer;
}

int main() {

	cout << solution("aABSDdefghijklmn.p");
	system("pause");
}
