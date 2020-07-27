#include <bits/stdc++.h>
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

void solve(int t)
{
    int n; cin>>n;
    string shards; cin>>shards;
    int countA = 0, countB = 0;
    for(char c: shards)
    {
        if(c == 'A') countA++;
        else countB++;
    }
    int diff = abs(countA - countB);
    if(diff >= 3)
    {
        cout << "Case #" << t << ": N" << endl;
    }
    else
    {
        cout << "Case #" << t << ": Y" << endl;
    }
}

int main()
{
    fastIO();
    int t; cin>>t;
    for(int i = 1; i<=t; i++)
    {
        solve(i);
    }

    return 0;
}