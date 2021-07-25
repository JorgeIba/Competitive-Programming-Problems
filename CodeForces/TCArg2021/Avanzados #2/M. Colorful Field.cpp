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


lli n, m, k, t; 

lli get_number(lli x, lli y)
{
    return (x-1)*m + y;
}


bool is_lower(pair<lli,lli> p, lli x, lli y)
{
    if( get_number(p.first, p.second) <= get_number(x, y) ) return true;
    return false;
}



string opt(lli cell)
{
    if(cell == 1) return "Carrots";
    else if(cell == 2) return "Kiwis";
    else return "Grapes";
}


int main () {
	//fastIO();
    cin>>n>>m>>k>>t;

    vector< pair<lli,lli> > wasted(k);
    set< pair<lli,lli> > wasted_set;

    for(auto &x: wasted)
    {
        cin>>x.first>>x.second;
        wasted_set.insert(x);
    }


    for(int i = 0; i < t; i++)
    {
        lli x, y; cin>>x>>y;
        if(wasted_set.count({x,y}))
        {
            cout << "Waste\n"; continue;
        }

        lli lower = 0;
        for(int j = 0; j < k; j++)
        {
            if(is_lower(wasted[j], x, y))
            {
                lower++;
            }
        }

        lli number_cell = get_number(x, y);

        //cout << lower << " " << number_cell << " ";
        cout << opt( (number_cell - lower)%3 ) << endl;
    }

	


	return 0;
}

