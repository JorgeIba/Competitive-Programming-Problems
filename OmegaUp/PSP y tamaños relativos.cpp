#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n; cin>>n;
    vector<double> values(n);
    vector<double> lns(n);
    for(auto &x: values)
    {
        cin>>x;
        x = abs(x);
    }
    double avg = 0, var = 0;
    for(int i = 0; i < n; i++)
    {
        avg += log(values[i]);
    }
    avg /= n;
    for(int i = 0; i < n; i++)
    {
        var += ((log(values[i])) - avg)*((log(values[i])) - avg);
    }
    var /= (n-1);

    double est = sqrt(var);
    double VS = exp( abs(avg - 2*est) );
    double S = exp( abs(avg - est) );
    double M = exp( abs(avg) );
    double L = exp( abs(avg + est) );
    double VL = exp( abs(avg+2*est));

    cout<<fixed<<setprecision(2)<<VS<<endl<<S<<endl<<M<<endl<<L<<endl<<VL<<endl;



    return 0;
}