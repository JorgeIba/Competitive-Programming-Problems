#include<bits/stdc++.h>
#define lli long long int

using namespace std;


const double PI = acos(-1);

void solve()
{
    lli n, l, d, t; cin>>n>>l>>d>>t;
    lli r = d*t;
    double theta = 2*PI/n;
    double aux = 2* tan(theta/2);
    double a = l / aux;
    double A = a * l * n / 2;
    double res = A + r*l*n + PI*r*r;
    cout<<fixed<<setprecision(14)<<res<<endl;
}


int main()
{
    lli t; cin>>t;
    while(t--) solve();
    return 0;
}