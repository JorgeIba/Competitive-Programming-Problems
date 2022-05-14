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

string f(lli k)
{
    if(k == 1) return "2";
    if(k % 2 == 0)
    {
        return "(" + f(k/2) + ")^2";
    }
    else
    {
        return "(2*" + f(k-1) + ")";
    }
}



int main () {
	fastIO();
    lli t; cin>>t;

    while(t--)
	{
        lli k; cin>>k;
        cout << f(k) << endl;
    }


	return 0;
}

