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
 
 
void solve(){
    lli n; cin>>n;
    priority_queue< lli, vector<lli>, greater<lli> > q;
    for(int i = 0; i<n; i++)
    {
        lli x; cin>>x;
        q.push(x);
    }

    lli ans = 0;
    if(q.size() == 1)
    {
        cout << q.top() << endl;
        return;
    }
    while(q.size() >= 2)
    {
        lli x1 = q.top(); q.pop();
        lli x2 = q.top(); q.pop();
        lli suma = x1+x2;
        //cerr << suma << endl;
        q.push(suma);
        ans+=suma;
    }
    cout << ans << endl;
}

int main () {
	//fastIO();
    int t; cin>>t;
    while(t--) solve();
}