#include <bits/stdc++.h>
#define lli long long int

using namespace std;

lli arreglo[100015];

void solve()
{
    lli n, k; cin>>n>>k;
    lli l = 0, r = 100001LL;
    lli res = -1;
    while(l<=r)
    {
        lli mid = l + (r-l)/2;
        if( arreglo[mid] == k  )
        {
            res = mid;
            break;
        }
        else if (arreglo[mid] < k)
        {
            l = mid+1;
        }
        else
        {
            res = mid;
            r = mid-1;
        }
    }
    lli pos1 = res;
    lli pos2 = k - arreglo[res-1];
    string s(n, 'a');
    reverse(s.begin(), s.end());
    s[pos1] = 'b';
    s[pos2-1] = 'b';
    reverse(s.begin(), s.end());
    cout<<s<<endl;
    


}


int main()
{
    ios_base::sync_with_stdio(false);
    cout.tie(0);
    cout.tie(0);
    lli t; cin>>t;
    arreglo[0] = 0;
    for(int i = 1; i<100001; i++ )
    {
        arreglo[i] = arreglo[i-1] + i;
    }

    while(t--)
    {
        solve();
    }


    return 0;
}