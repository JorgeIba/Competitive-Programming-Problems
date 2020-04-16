#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n; cin>>n;
    string s;
    cin>>s;
    lli izq = 0, der = 0;
    for(int i=0;i<n; i++)
    {
        if (s[i]=='L') izq++;
        if (s[i]=='R') der++;
    }

    lli res = 1 + izq + der;
    cout<<res<<endl;
    return 0;
}