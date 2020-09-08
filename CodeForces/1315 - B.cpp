#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

void solve()
{
    lli a,b,p; cin>>a>>b>>p;
    string s; cin>>s;

    char pos1, pos2='z';
    bool flag=false;
    lli res = s.length()-1;
    for(int i=s.length()-2; i>=0; i--)
    {
        pos1 = s[i];
        if(pos1 != pos2)
        {
            pos2 = pos1;
            flag = false;
        }
        else
        {
            if(p>=0)
            {
                res = i;
            }
        }
        
        if(!flag)
        {
            lli cobro = 0;
            if(pos1 == 'A')
            {
                cobro = a;
            }
            else
            {
                cobro = b;
            }
            if(p - cobro >= 0)
            {
                p -= cobro;
                res = i;
            }
            else
            {
                cout<<(res+1)<<endl;
                return;
            }
            
            flag = true;
        }
    }

    cout<<(res + 1)<<endl;

}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }


}
