#include <bits/stdc++.h>

using namespace std;

long long stringToLong(string s) {
	stringstream ss(s);
	long long res;
	ss >> res;
	return res;
}

vector<string> split(string s, char delimiter) {
	stringstream ss(s);
	vector<string> res;
	string data;
	while (getline(ss, data, delimiter)) {
		res.push_back(data);
	}
	return res;
}
int main() {
	ifstream reader("./../data/english/data.txt");
	ofstream writer("./../data/english/history.txt");
	string line;
	while (getline(reader, line)) {
		vector<string> vt = split(line, '|');
		writer << vt[4];
		writer << "|";
		writer << "2";
		writer << "|";
		writer << vt[0];
		writer << "\n";
	}

	reader.close();
	writer.close();

	return 0;
}
