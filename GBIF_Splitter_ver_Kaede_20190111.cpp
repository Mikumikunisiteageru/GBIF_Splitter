#include<iostream>
#include<fstream>
using namespace std;
// Negimoriya
// <yang.yc.allium@gmail.com>

// 20180612
// 20181128 
// 20190110 ver_Kaede

const int mod = 16411, sen = 513;
string hash[mod];
int of_num[mod];
int cnt_cnt[sen], rev[sen];

const int a[12] = {0, 7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 20};
const char tab = '\t';
const string head = "GBIF_ver_Kaede_",
	tail = ".txt";
const char *file_name = "GBIF_Global.txt";
const string headers = "gbifID	family	genus	species	infraspecificEpithet	taxonRank	scientificName	countryCode	locality	decimalLatitude	decimalLongitude	elevation";

int locate (string str) {
	unsigned int t = 0;
	for (unsigned int i = 0; i < str.length(); i ++)
		t = (t * 128 + str[i]) % mod;
	while ((hash[t] != "") && (hash[t] != str))
		t = (t + 1) % mod;
	return t;
}

int main (void) {
	ofstream fout[sen];
	ifstream fin (file_name);
	if (!fin) {
		cout << "INPUT FILE 'GBIF_Global.txt' NOT FOUND!" << endl;
		system("pause");
		return -1;
	}
	for (int i = 0; i < mod; i ++) {
		hash[i] = "";
		of_num[i] = -1;
	}
	string line;
	int n = 0, of_cnt = 0;
	cout << "WORKING! MAY TAKE SOME TIME..." << endl;
	while (getline (fin, line)) {
		if ((n & 16383) == 0) 
			cout << n << endl;
		n ++;
		if (n == 1)
			continue;
		int pos = 0, m = 1;
		int place[23] = {0};
		while ((pos = line.find('\t', place[m-1])) != -1) {
			place[m++] = pos+1;
			if (m >= 22)
				break;
		}
		if (m < 22)
			continue;
		string cntry = line.substr(place[13], place[14]-place[13]-1);
		if (cntry.length() == 0)
			cntry = "Unlabeled";
		int loc = locate(cntry);
		if (hash[loc] == "") {
			hash[loc] = cntry;
			of_num[loc] = of_cnt;
			fout[of_cnt].open((head+cntry+tail).c_str(), ios::out);
			fout[of_cnt] << headers << endl;
			cnt_cnt[of_cnt] = 0;
			rev[of_cnt] = loc;
			of_cnt ++;
		}
		int of_now = of_num[loc];
		cnt_cnt[of_now] ++;
		for (int i = 0; i < 11; i ++) {
			int k = a[i];
			fout[of_now] << line.substr(place[k], place[k+1]-place[k]-1) << tab;
		}
		fout[of_now] << line.substr(place[20], place[21]-place[20]-1) << endl;
	}
	fin.close ();
	for (int i = 0; i < of_cnt; i ++)
		fout[i].close();
	cout << n - 1 << " RECORDS OK!" << endl;
	ofstream fout_rep ("GBIF_ver_Kaede_Report.txt");
	for (int i = 0; i < of_cnt; i ++)
		fout_rep << hash[rev[i]] << tab << cnt_cnt[i] << endl;
	fout_rep.close();
	system("pause");
	return 0;
}
