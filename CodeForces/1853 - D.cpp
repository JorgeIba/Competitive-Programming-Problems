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


void main_(){

    int n; cin>>n;
    vector<pair<int,int>> nums(n);
    forn(i, n) {
        cin>>nums[i].first;
        nums[i].second = i;
    }

    sort(all(nums));
    deque<pair<int,int>> dq(all(nums));

    vector<int> ans(n);
    bool ok = true;

    int matches = 0;
    while(!dq.empty()){
        if(dq.front().first - matches == 0){
            ans[dq.front().second] = -SZ(dq);
            dq.pop_front();
            continue;
        }

        if(dq.back().first - matches == SZ(dq)){
            ans[dq.back().second] = SZ(dq);
            dq.pop_back();
            matches++;
            continue;
        }

        ok = false;
        break;
    }

    if(!ok) {
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;
    for(auto x: ans) cout << x << " ";
    cout << endl;

}

int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

