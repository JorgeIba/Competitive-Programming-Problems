#include <bits/stdc++.h>
#define lli long long int

using namespace std;
int main()
{
    vector<lli> letters(26);
    string s; cin>>s;
    for(auto c: s)
    {
        letters[c-'a']++;
    }
    lli cont = 0;
    for(auto x: letters)
    {
        if(x&1)
        {
            cont++;
        }
    }

    if((cont&1)or(cont==0))
    {
        cout<<"First\n";
    }
    else
    {
        cout<<"Second\n";
    }
    

    return 0;
}