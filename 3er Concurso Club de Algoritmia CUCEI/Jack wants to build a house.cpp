#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
    //fastIO();
    string s, t; cin>>s>>t;
    lli cont = 0;
    lli idx = 0;

    if(s.length() < t.length())
    {
        swap(s,t);
    }
    cout<<s<<"\n"<<t<<endl;

    for(int i = 0; i<s.length(); i++)
    {
        if(s[i] != t[idx])
        {
            cont++;
        }
        else
        {
            idx++;
        }
    }

    if(cont <=3)
    {
        cout<<"Yes\n";
    }
    else
    {
        cout<<"No\n";
    }
    
    cout<<cont<<endl;

    return 0;
}