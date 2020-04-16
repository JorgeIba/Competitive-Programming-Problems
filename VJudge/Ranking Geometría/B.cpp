#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

const double PI = acos(-1);
const double eps = 1e-9;

int main()
{
    lli d, h, v, e; cin>>d>>h>>v>>e;
    if(4 * v - (PI*d*d*e) > -eps) int a = 1;
    else 
    {
        cout<<"NO\n"; 
        return 0;
    }

    cout<<"YES\n";
    double res = PI * d * d * h / ( 4*v - PI*d*d*e );
    cout<<fixed<<setprecision(11)<<res<<endl;


    return 0;
}