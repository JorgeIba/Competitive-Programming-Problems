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


multiset<lli> get_rems(lli n)
{
    multiset<lli> rems;
    
    for(int i = 2; n>0; i++)
    {
        rems.insert(n % i);
        n /= i;
    }
    return rems;
}

vector<lli> get_urems(lli n)
{
    vector<lli> rems;

    for(int i = 2; n>0; i++)
    {
        rems.push_back(n % i);
        n /= i;
    }
    return rems;
}


int main () {
	//fastIO();

    map< multiset<lli>, lli > frs;

    multiset<lli> check = {0, 2, 2, 3, 5};
    
    for(lli i = 1; i<=1e5; i++)
    {
        frs[ get_rems(i) ]++;
        
        if(get_rems(i) == check)
        {
            cout << i <<": ";
            for(auto x: get_urems(i)) cout << x << " ";
            cout << endl;
        }
        
    }

    //cout << frs[ get_rems(120) ] << endl;



	return 0;
}