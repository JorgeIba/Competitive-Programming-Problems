#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
    fastIO();
    int n; cin>>n;
    string a, b;
    cin>>a>>b;
    lli cost = 0;
    for(int i = 0; i<n; i++)
    {
        if(a[i] != b[i])
        {
            if(i!=n-1)
            {
                if(b[i] == a[i+1] && b[i+1] == a[i])
                {
                    swap(b[i], b[i+1]);
                    cost++;
                    continue;
                }
            }
            cost++;
        }
    }
    cout<<cost<<endl;
    return 0;
}