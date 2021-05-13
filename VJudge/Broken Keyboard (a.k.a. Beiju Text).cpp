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


int main () {
	fastIO();

    string s;
    while(cin>>s)
    {
        int n = s.length();
        string aux;
        vector<pair<int, string>> ss;
        int l = 0, r = 0, idx = 0;
        for(int i = 0; i<n; i++)
        {
            if(s[i] != '[' && s[i] != ']') aux += s[i];
            else if(s[i] == '[')
            {
                ss.push_back({idx, aux});
                idx = --l;
                aux.clear();
            }
            else if(s[i] == ']'){
                ss.push_back({idx, aux});
                idx = ++r;
                aux.clear();
            }
        }

        if(SZ(aux)) ss.push_back({idx, aux});

        sort(all(ss));

        string ans;

        for(auto x: ss)
        {
            for(auto c: x.second) ans += c;
        }
        cout << ans << endl;
    }


	return 0;
}