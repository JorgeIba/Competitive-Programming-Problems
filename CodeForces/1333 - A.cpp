#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

int main()
{
    /*
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    */
    lli t; cin>>t;
    while(t--)
    {
        lli n, m; cin>>n>>m;
        string s(m, 'B');
        s[0] = 'W';
        cout<<s<<endl;
        for(int i = 0; i<(n-1); i++)
        {
            string a(m, 'B');
            cout<<a<<endl;
        }

    }

}