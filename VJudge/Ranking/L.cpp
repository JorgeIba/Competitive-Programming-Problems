#include <bits/stdc++.h>
#define lli long long int

using namespace std;
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n, k; cin>>n>>k;
    vector<lli> numeros(n);
    for(auto &x: numeros)
    {
        cin>>x;
    }

    if(k==1)
    {
        cout<<1<<" "<<1<<endl;
        return 0;
    }

    lli l=0, r = -1, res = 10000000000000LL;
    lli rl = -2, rr = -2;
    map<lli,lli> frequency;
    while(r<n)
    {
        if(frequency.size() < k)
        {
            r++;
            lli aux = numeros[r];
            frequency[aux]++;
        }

        else if(frequency.size() == k)
        {
            if( (r-l+1) < res )
            {
                res = r-l+1;
                rl = l;
                rr = r;
                /*
                cout<<l<<" "<<r<<endl;
                cout<<"Wacha que pedo:\n";
                for(auto x: frequency)
                {
                    cout<<x.first<<" "<<x.second<<endl;
                }
                //cout<<r<<" "<<l<<endl;
                */
            }
            lli aux = numeros[l];
            frequency[aux]--;
            l++;
            if(frequency[aux] <= 0)
            {
                frequency.erase(aux);
            }
        }
    
    }
    cout<<(rl+1)<<" "<<(rr+1)<<endl;

    return 0;
}