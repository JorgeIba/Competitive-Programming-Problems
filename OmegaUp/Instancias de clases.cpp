#include <bits/stdc++.h>
#define lli long long int

using namespace std;


int main()
{   
    /*
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    */
    lli n, a; cin>>n>>a;
    map<string, int> frequency;
    map<string, string> toPointing;

    for(int i = 0; i<n; i++)
    {
        //frequency[s] ++;
        //toPointing[s] = s;
    }

    for(int i = 0; i<a; i++)
    {
        string v1, basura, v2; cin>>v1>>basura>>v2;
        v2.pop_back();
        string aux = toPointing[v1];
        frequency[aux] --;
        toPointing[v1] = v2;
        frequency[v2]++;
    }

    lli cont=0;
    for(auto x: frequency)
    {
        if(x.second==0) continue;
        cont++;
    }
    cout<<cont<<endl;

    return 0;
}
    