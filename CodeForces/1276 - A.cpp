#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void solve()
{
    vector<lli> res;
    lli cant = 0;
    string s;
    cin>>s;
    for(lli i=0; i<s.length(); i++)
    {
        if((s[i]=='o')and(s[i+1]=='n')and(s[i+2] == 'e'))
        {
            if((i>=2)and(s[i-1]=='w')and(s[i-2]=='t'))
            {
                cant++;
                res.push_back(i);
            }
            else
            {
                cant++;
                res.push_back(i+1);
            }
            continue;
        }
        if((i>=2)and(s[i-1]=='w')and(s[i-2]=='t')and(s[i]=='o'))
        {
            cant++;
            res.push_back(i-1);
        }
    }

    cout<<cant<<endl;
    if(cant>0)
    {
        for(auto x: res)
        {
            cout<<(x+1)<<" ";
        }
    }
    cout<<endl;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    lli t; 
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}