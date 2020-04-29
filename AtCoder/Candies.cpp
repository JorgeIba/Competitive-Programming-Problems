#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli n, k; 
vector<lli> candies;


lli funcion(lli index, lli suma)
{
    if(suma == k && index <=n) return 1;
    if(index > n) return 0;

    lli res = 0;
    for(int i = 0; i <= candies[index]; i++)
    {
        res += funcion(index+1, suma + i );
    }
    return res;
}




int main()
{
    fastIO();
    cin>>n>>k;
    candies.resize(n);
    for(auto &x: candies)
    {
        cin>>x;
    }
    lli res = 0;
    for(int i = 0; i<= candies[0]; i++)
    {
        res += funcion(1, i);
    }
    cout<<res<<endl;
    

    return 0;
}