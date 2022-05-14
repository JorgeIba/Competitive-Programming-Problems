#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n, k; cin>>n>>k;
    if(k>n) cout<<"IMPOSSIBLE\n";
    else if (k<n)
    {
        if(k<3) cout<<"IMPOSSIBLE\n";
        else
        {
            string s(n, 'a');
            for(int i = 1; i<n; i++)
            {
                if(s[i-1] == 'a') s[i] = 'b';
                if(s[i-1] == 'b') s[i] = 'c';
                if(s[i-1] == 'c') s[i] = 'a';
            }
            lli ocupo = k - 3;

            for(int i = n-ocupo; i<n; i++)
            {
                s[i] = 'd';
            }
            cout<<s<<endl;
        }
        
    }
    else
    {
        string s(n, 'a');
        cout<<s<<endl;
    }
    
    
    return 0;
}