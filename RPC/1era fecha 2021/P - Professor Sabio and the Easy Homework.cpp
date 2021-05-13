#include<bits/stdc++.h>
#define forn(i,n) for(int i = 0; i < n; i++)
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

typedef long double ld;
typedef long long int lli;
typedef vector<int> vi;

int val[10];
bool used[10];
string M[3][3];
int ma[3][3];

bool check(){
	/*
	forn(i, 3){
		forn(j, 3){
			if(M[i][j].size() == 1)
				ma[i][j] = val[M[i][j][0] - 'A'];
			else
				ma[i][j] = val[M[i][j][0] - 'A'] * 10 + val[M[i][j][1] - 'A'];
		}
	}
	*/
	auto get_val = [&](int i, int j){
		if(M[i][j].size() == 1)
			return val[M[i][j][0] - 'A'];
		else
			return val[M[i][j][0] - 'A'] * 10 + val[M[i][j][1] - 'A'];
	};
	forn(i, 3){
		if(get_val(i, 2) != (get_val(i, 0) + get_val(i, 1))) return false;
		if(get_val(2, i) != (get_val(0, i) - get_val(1, i))) return false;
	}
	return true;
}

void solve(int x){
	if(x == 6){
		if(check()){
			forn(i, 5)
				cout << val[i] << ' ';
			cout << val[5] << endl;
		}
		return;
	}
	forn(i, 10){
		if(used[i]) continue;
		used[i] = true;
		val[x] = i;
		solve(x + 1);
		used[i] = false;
	}
}

int main(){
	fastIO();
	int t;
	cin >> t;
	forn(c, t){
		forn(i, 3)
			forn(j, 3)
			cin >> M[i][j];
		cout << "Case #" << c + 1 << ":\n";
		solve(0);
		cout << endl;
	}
	/* M[0][0] = "AA"; */
	/* forn(i, 200) solve(0); */
	return 0;
}
