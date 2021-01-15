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

vector<lli> ans(10);

void calculate(vector<lli> v, int look)
{
    int n = v.size();
    map<lli,lli> fr;
    fr[0] = 1;

    lli acum = 0, answer = 0;

    for(int i = 0; i<n; i++)
    {
        acum = (acum + v[i])%9;
        lli falta = (acum - look)%9;
        if(falta < 0) falta+=9;
        answer += fr[falta];
        fr[acum]++;
    }
    ans[look] = answer;
}


int main()
{
    fastIO();
    lli n; cin>>n;
    string s; cin>>s;
    VLL v(n);
    for(int i = 0; i<n; i++) v[i] = (s[i] - '0');
    
    lli cnt = 0;
    for(int i = 0; i<n; i++)
    {
        if(v[i] == 0) cnt++;
        else
        {
            ans[0] += cnt*(cnt+1)/2;
            cnt = 0;
        }
    }
    if(cnt) ans[0] += cnt*(cnt+1)/2;
    

    for(int i = 1; i<=9; i++)
    {
        calculate(v, i);
    }
    
    for(int i = 0; i<=9; i++)
    {
        if(i == 9)  cout << ans[9] - ans[0] << endl;
        else
        {
            cout << ans[i] << " ";
        }
    }
    
    return 0;
}
