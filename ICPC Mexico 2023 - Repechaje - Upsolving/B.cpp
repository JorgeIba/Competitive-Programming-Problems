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

    int n; cin>>n;
    vector<int> nums(n);

    for(auto &x: nums) cin>>x;

    vector<int> pos(n+1);
    forn(i, n) 
        pos[nums[i]] = i;


    vector<bool> visited(n+1);
    int subs = 0;
    forn(i, n){
        if(visited[i]) continue;

        subs++;
        int j = i;
        visited[j] = true;

        while(pos[nums[j]+1] > j){
            j = pos[nums[j]+1];
            visited[j] = true;
        }
    }


    int ans = 0;
    while((1 << ans) < subs) ans++;

    cout << ans << endl;


	return 0;
}

