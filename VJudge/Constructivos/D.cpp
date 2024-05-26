#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;



int main () {
	//fastIO();

    int n, p; cin>>n>>p;
    string s; cin>>s;

    vector< array<int, 3> > tides(p);
    for(int i = 0; i < p; i++){
        for(int j = i; j < n; j += p){
            if(s[j] == '0') {
                tides[i][0]++;
            } else if(s[j] == '1') {
                tides[i][1]++;
            } else {
                tides[i][2]++;
            }
        }
    }

    vector<pair<int,int>> changes(p); 
    bool ok = false;
    for(int i = 0; i < p; i++){
        auto [zeros, ones, marks] = tides[i];
        
        if(marks >= 2) ok = true, changes[i] = {1, 1};
        if(zeros > 0 && ones > 0) ok = true;
        if(zeros > 0 && marks > 0) ok = true, changes[i] = {0, 1};
        if(ones > 0 && marks > 0) ok = true, changes[i] = {1, 0};
    }

    if(!ok){
        cout << "No" << endl;
        return 0;
    }

    string ans = s;
    for(int i = 0; i < p; i++){
        for(int j = i; j < n; j += p){
            if(s[j] != '.') continue;

            if(changes[i].first) {
                ans[j] = '0';
                changes[i].first--;
            } else if(changes[i].second){
                ans[j] = '1';
                changes[i].second--;
            } else {
                ans[j] = '0';
            }
        }
    }

    cout << ans << endl;

	return 0;
}

