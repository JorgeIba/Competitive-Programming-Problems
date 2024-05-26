#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


int main () {
	//fastIO();

    lli n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;


    multiset<lli> m;
    for(auto x: nums) m.insert(x);


    lli ans = 0;
    while(m.size() > 1) {
        ans++;
        lli lowest = *m.begin();
        lli greatest = *m.rbegin();

        m.erase(m.find(greatest));

        lli mod = greatest % lowest;
        if(mod > 0) {
            m.insert(mod);
        }
    }

    cout << ans << endl;


	return 0;
}

