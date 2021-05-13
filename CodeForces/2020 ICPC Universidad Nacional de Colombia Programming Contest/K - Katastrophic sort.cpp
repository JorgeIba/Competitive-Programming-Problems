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

string s, t; 
int n, m;



int main () {
	fastIO();
    cin>>s>>t;
    n = s.length(), m = t.length();

    int alfPart = 0;
    for(char c: s)
    {
        if(isalpha(c)) alfPart++;
    }
    string ss = s.substr(0,alfPart);
    string tt = t.substr(0, alfPart);

    if(ss == tt)
    {
        int szs = n - alfPart, szt = m-alfPart;
        string sn = s.substr(alfPart, n-alfPart);
        string tn = t.substr(alfPart, m-alfPart);

        if(szs < szt)
        {
            cout << "<\n";
        }
        else if(szs > szt)
        {
            cout << ">\n";
        }
        else
        {
            for(int i = 0; i<szs; i++)
            {
                if(sn[i] < tn[i])
                {
                    cout << "<\n";
                    return 0;
                }
                else if(sn[i] > tn[i])
                {
                    cout << ">\n";
                    return 0;
                }
            }
            cout << "=\n";
        }
        

    }
    else if(ss < tt)
    {
        cout << "<\n";
    }
    else {
        cout << ">\n";
    }
    
    

	return 0;
}