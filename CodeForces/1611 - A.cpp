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

void solve()
{
    lli n; cin>>n;

    string ns = to_string(n);
    lli first_digit  = stoi(string(1, ns[0]));
    
    if(n % 2 == 0)
    {
        cout << 0 << endl;
        return;
    }

    if(first_digit % 2 == 0)
    {
        cout << 1 << endl;
        return;
    }

    for(int i = 1; i < SZ(ns); i++)
    {
        if( stoi(string(1, ns[i])) % 2 == 0 )
        {
            cout << 2 << endl;
            return;
        }
    }

    cout << -1 << endl;
    return;



}


int main () {
	fastIO();
    lli t; cin>>t;

    while(t--) solve();	


	return 0;
}

