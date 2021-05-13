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

string s;

vector<lli> fr[26];

int main () {
	fastIO();
    cin>>s;
    for(int i = 0; i<(int)s.length(); i++)
    {
        char c = s[i];
        fr[c-'a'].push_back(i);
    }


    lli q; cin>>q;
    while(q--)
    {
        string t; cin>>t;
        int n = t.length();

        lli j = 0, i = 0;
        while(true)
        {
            char c = t[j];
            auto itr = lower_bound( all(fr[c - 'a']), i);
            if(itr == fr[c-'a'].end()) break;
            else
            {
                i = *itr + 1;
                j++;    
            }
            if(j==n) break;
        }

        if(j == 0)
        {
            cout << "IMPOSSIBLE\n";
        }
        else
        {
            cout << t.substr(0, j) << endl;
        }
        
    }
    

    

	return 0;
}