#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void solve()
{
    lli n; cin>>n;
    string s; cin>>s;
    map< pair<lli,lli> , lli> last;
    pair<lli,lli> current = {0,0};
    last[current] = 0;
    lli res = s.length() + 1, l = -2, r = -2;
    for(int i=0; i<s.length(); i++)
    {
        char c = s[i];
        switch (c)
        {
            case 'R': 
                current.first ++;
                break;
            case 'L':
                current.first--;
                break;
            case 'U':
                current.second++;
                break;
            case 'D':
                current.second--;
        }
        
        if( last.find(current) != last.end()   )
        {
            //cout<<current.first<<" "<<current.second<<" "<<i<<" "<<last[current]<<endl;
            lli dist = i - last[current];
            if(dist < res)
            {
                res = dist;
                l = last[current];
                r = i;
            }
        }
        last[current] = i+1;
        //cout<<current.first<<" "<<current.second<<" "<<last[current]<<endl;

    }
    if((l < 0) and (r < 0) )
    {
        cout<<-1<<endl;
        return;
    }

    cout<<(l+1)<<" "<<(r+1)<<endl;
    
    
    

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
    return 0;
}