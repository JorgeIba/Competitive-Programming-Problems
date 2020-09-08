#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

void solve()
{
    lli n; cin>>n;
    bitset< 32 > m = n;
    set<lli> check;
    //cout << m.to_string() << endl;
    bitset< 32 > aux = m;
    for(int l = 0, r = 4; r<32+4; l++, r++)
    {
        bitset< 32 > operar = ((1<<(5)) - 1);
        bitset<32> ans = aux&operar;
        check.insert((lli)ans.to_ulong());
        lli last = aux[31];
        aux<<=1;
        aux[0] = last;
    }
    if(check.size() == 32)
    {
        cout << "yes\n";
    }
    else
    {
        cout << "no\n";
    }
}


int main () {
	fastIO();
    lli t; cin>>t;
    while(t--) solve();
	return 0;
}