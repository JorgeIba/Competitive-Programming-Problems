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

vector<lli> prices;

int main () {
	//fastIO();
    prices.resize(3);
    cin>>prices[0]>>prices[1]>>prices[2];

    sort(all(prices));
    lli total = 0, curr = 0;
    for(auto x: prices)
    {
        curr += x;
        if(curr >= 500)
        {
            total += (curr-100);
            curr = 0;
        }
    }
    cout << total + curr << endl;
    
    
	return 0;
}