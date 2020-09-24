#include <bits/stdc++.h>
using namespace std;

// judge if the group1_ele can match any of element in group2
// @ vvb: relationship matrix
// @ match_num: the matched indeice of group2
// @ matched: in this iteration, if the element in group2 is searched
bool to_match(int group1_ele, vector<int> group1, vector<vector<bool>> vvb, vector<int> &match_num, vector<bool> &matched) {
	int group1_index;
	for (int i = 0; i < group1.size(); i++) {
		if (group1_ele == group1[i]) {
			group1_index = i;
			break;
		}
	}
	for (int i = 0; i < match_num.size(); i++) {
		if (matched[i] == false && vvb[group1_index][i]) {
			matched[i] = true;
			if (match_num[i] == 0 || to_match(match_num[i], group1, vvb, match_num, matched)) {
				match_num[i] = group1_ele;
				return true;
			}
		}
	}
	return false;
}


int main() {
	int N, M;
	cout << "input the numbers of group1 and group2:" << endl;
	while (cin >> N >> M) {
		vector<int> group1(N);
		vector<int> group2(M);
		cout << "input the elements of group1:" << endl;
		for (int i = 0; i < N; i++)
			cin >> group1[i];
		cout << "input the elements of group2:" << endl;
		for (int i = 0; i < M; i++)
			cin >> group2[i];
		cout << "input " << N << " rows to represent the relationship of group1 and group2:" << endl;
		vector<vector<bool>> vvb(N, vector<bool>(M));
		vector<int> match_2to1(M);
		vector<bool> matched(M);
		cin.ignore();
		for (int i = 0; i < N; i++) {
			string s;
			getline(cin, s);
			while (count(s.begin(), s.end(), ' ')) {
				int index = stoi(s.substr(0, s.find(' ')));
				for (int j = 0; j < M; j++)
					if (index == group2[j]) {
						vvb[i][j] = true;
						break;
					}
				s.erase(0, s.find(' ') + 1);
			}
			int index = stoi(s);
			for (int j = 0; j < M; j++)
				if (index == group2[j]) {
					vvb[i][j] = true;
					break;
				}
		}
		int cnt = 0;
		for (int i = 0; i < N; i++) {
			for (int i = 0; i < matched.size(); i++)
				matched[i] = false;
			if (to_match(group1[i], group1, vvb, match_2to1, matched))
				cnt++;
		}
		cout << endl << "maximum number of matches: " << cnt << endl << endl;
	}
	return 0;
}

/*
输入N,M代表合集1和合集2的数量
第二行输入N个数字代表第一个合集的N个编号
第三行输入M个数字代表第二个合集的M个编号
输入N行，每行若干个数据，代表第一个合集中每个元素可匹配的第二个合集的编号

example
input1:
4 3
1 2 3 4
5 6 7
5 6
5 7
5
6 7
ouput1:
3

input2:
8 10
1 2 3 4 5 6 7 8
1 2 3 4 5 6 7 8 9 10
1 2 5
2 5 8
1 5
3 8
7 3 8
1 2 8
7 9
3 9

output2:
7
*/