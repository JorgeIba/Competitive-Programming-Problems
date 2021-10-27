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


vector<vector<lli>> sieveDivs(lli n)
{
    vector< vector<lli> > divs(n+1);
    for(lli i = 1; i<=n; i++)
    {
        for(lli j = 1; i*j <= n; j++)
        {
            divs[i*j].push_back(i);
        }
    }
    return divs;
}

lli getSolutions(vector<lli> &divs, lli n)
{
    lli sum = 0;
    for(auto d: divs)
    {
        lli a = n/d;
        if((a+d)%4 == 0)
        {
            lli k = (a+d)/4;
            if(k < a && a < 4*k)
                sum++;
        }
    }
    return sum;
}


const int maxN = 5e7;

int main () {
	//fastIO();
    time_t begin = clock();

    auto divs = sieveDivs(maxN);

    lli ans = 0;
    for(int i = 1; i<maxN; i++)
    {
        lli countSolutions = getSolutions(divs[i], i);
        if(countSolutions == 1) ans++;
    }
    cout << ans << endl;

    cout << "Time: " << (double)(clock() - begin) / CLOCKS_PER_SEC << endl;


	return 0;
}

