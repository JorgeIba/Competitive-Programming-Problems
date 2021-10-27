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


bool check(string &s, string &t, int idx_pref, int idx_suff)
{
    for(int i = idx_pref; i<idx_suff; i++)
    {
        //cout << s << " " << t << " " << i+1 << " " << i << endl;
        if(s[i+1] != t[i])
        {
            return false;
        }
    }
    return true;
}


int main () {
	//fastIO();
    int n; cin>>n;
    string s; cin>>s;
    string t; cin>>t;

    int idx_pref = 0;
    for(idx_pref = 0; idx_pref < n && s[idx_pref] == t[idx_pref] ; idx_pref++);

    int idx_suff = n-1;
    for(idx_suff = n-1; idx_suff >= 0 && s[idx_suff] == t[idx_suff] ; idx_suff--);
	
    if(idx_pref == idx_suff)
    {
        cout << 2 << endl;
        return 0;
    }

    bool check1 = check(s, t, idx_pref, idx_suff), check2 = check(t, s, idx_pref, idx_suff);

    cout << check1 + check2 << endl;





	return 0;
}

