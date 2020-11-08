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

lli t(int n)
{
    return (1LL*n*(n+1)) / 2;
}

lli p(int n)
{
    return (1LL*n*(3*n-1))/2;
}

lli h(int n)
{
    return (1LL*n*(2*n-1));
}


int main () {
	//vector<int> Triangle;
    set<int> Pentagonal, Hexagonal;
    const int maxN = 1e5;

    for(int i = 1; i<=maxN; i++)
    {
        Hexagonal.insert(h(i));
        Pentagonal.insert(p(i));
        if( Hexagonal.count(t(i)) && Pentagonal.count(t(i)) )
        {
            cout << i << " " << t(i) << endl;
        }
    }


    
	return 0;
}