#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void solve()
{
    lli n, k; cin>>n>>k;
    if(k%3==0)
    {
        lli check = n % (k+1);
        if((check % 3 == 0)and(check != k))
        {
            cout<<"Bob\n";
            return;
        }
    }
    else
    {
       if(n%3==0)
        {
            cout<<"Bob\n";
            return;
        }
    }
    cout<<"Alice\n";
    
    

}

lli checkMEX(vector<lli> n)
{
    int j = 0;
    for(int i = 0; i<3; i++)
    {
        for(auto x: n)
        {
            if(x==j)
            {
                j++;
                break;
            }
        }
    }
    return j;
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
    /*
    
    vector<lli> arreglo(60);
    arreglo[0] = 0;
    lli k = 9;
    for(int i = 1; i<60; i++)
    {
        vector<lli> mex;
        if(i-1 >= 0)
        {
            mex.push_back(arreglo[i-1]);
        }
        if(i-2 >= 0)
        {
            mex.push_back(arreglo[i-2]);
        }
        if(i-k >= 0)
        {
            mex.push_back(arreglo[i-k]);
        }
        arreglo[i] = checkMEX(mex);
    }    

    for(int i = 0; i<60; i++)
    {
        cout<<i<<" "<<arreglo[i]<<endl;;
    }
    
    */
    return 0;
}