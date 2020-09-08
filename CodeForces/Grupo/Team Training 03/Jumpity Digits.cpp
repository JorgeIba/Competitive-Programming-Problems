#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli n;
vector<lli> res;

void check(lli i1, lli j1, vector<lli> nums)
{
    vector<lli> aux = nums;
    swap(aux[i1], aux[j1]);
    if(aux[0] == 0) return;
    for(int i = 0; i<n; i++)
    {
        if(aux[i] < nums[i])
        {
            for(int j = 0; j<n; j++)
            {
                if(aux[j] > res[j])
                {
                    res = aux;
                }
            }
            return;
        }
        else if (aux[i] > nums[i])
        {
            return;
        }
    }   
    return;
}



int main()
{
    fastIO();
    string s; cin>>s;
    n = s.length();

    string ALV(n,'0');

    for(int i = 0; i<n; i++)
    {
        for(int j = i+1; j<n; j++)
        {
            string aux = s;

            swap(aux[i], aux[j]);
            if(aux[0] == '0') continue;
            if( aux.compare(s) < 0 )
            {
                if(aux.compare(ALV) > 0)
                {
                    ALV = aux;
                }
            }
        }
    }
    ////////////////////////////
    if(ALV[0] ==  '0')
    {
        cout<<-1<<endl;
        return 0;
    }
    ////////////////////////////

    for(auto x: ALV)
    {
        cout<<x;
    }
    cout<<endl;

    return 0;
}