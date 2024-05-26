#include<bits/stdc++.h>
#define forn(i,n) for(int i = 0; i < n; i++)
#define fi first
#define se second
#define lli long long int
#define pb push_back
#define fastIO() ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

const int MAXN = 70000;
const int L = 0;
const int R = 32767 + 32768;

int A[MAXN];

pair<int,int> parse(string &line){
	int is_greater = line[2] == '>';
	string num;
	int i;
	for(i = 5; i < line.size(); i++){
		if(line[i] == ' ') break;
		num.pb(line[i]);
	}
	string remline;
	for(; i < line.size(); i++)
		remline.pb(line[i]);
	if(remline.size() < 10){
		if(is_greater) return {stoi(num) + 32768, R};
		return {L, stoi(num) + 32768};
	}
	string num2;
	for(i = 9; i < remline.size(); i++){
		if(remline[i] == ' ') break;
		num2.pb(remline[i]);
	}
	return {stoi(num) + 32768, stoi(num2) + 32768};
}

void print(const vector<pair<int,int>> &ans){
	if(ans.size() == 1 && ans[0].fi == L && ans[0].se == R){
		cout << "true" << endl;
		return;
	}
	for(int i = 0; i < ans.size(); i++){
		if(ans[i].fi == L){
			cout << "x <= " << ans[i].se - 32768;
		}
		else if(ans[i].se == R){
			cout << "x >= " << ans[i].fi - 32768; 
		}
		else{
			cout << "x >= " << ans[i].fi - 32768 << " && x <= " << ans[i].se - 32768;
		}
		if((i + 1) < ans.size())
			cout << " ||";
		cout << endl;
	}
}

int main() {
	//fastIO();

	freopen("hard.in", "r", stdin);
	freopen("hard.out", "w", stdout);

	string line;
	bool no_ans = true;
	while(getline(cin, line)){
		auto range = parse(line);
		if(range.fi > range.se){
			// no_ans = true;
            continue;
		} else {
            no_ans = false;
        }
		// cout << "range: " << range.fi - 32768 << ' ' << range.se - 32768 << endl;
		A[range.fi]++;
		A[range.se + 1]--;


	}
	if(no_ans){
		cout << "false" << endl;
		return 0;
	}


	int pelota = 0;
	for(int i = 0; i <= R; i++) {
		pelota += A[i];
		A[i] = pelota;
	}
		
	
	vector<pair<int,int>> ans;

	for(int i = 0; i <= R;){
		if(A[i] == 0){
			i++;
			continue;
		}
		int j = 0;
		while((i + j <= R) && A[i + j] > 0){
			// cout << A[i + j];
			j++;
			// cout << i + j << endl;
		}
		ans.pb({i, i + j - 1});
		// cout << "aqui " << ans.size()  << endl;
		// cout << i << ' ' << i + j - 1 << endl;
		i += j;
	}
	// for(auto p:ans) cout << p.fi - 32768 << ' ' << p.se - 32768 << endl;
	print(ans);
	return 0;
}
