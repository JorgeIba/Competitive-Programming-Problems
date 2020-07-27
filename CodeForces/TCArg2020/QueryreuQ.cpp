#include <bits/stdc++.h>
#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;


lli Manacher(string &s, lli n)
{
    vector<int> d1(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
            k++;
        }
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }

    vector<int> d2(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
            k++;
        }
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k ;
        }
    }
    lli ans = 0;
    for(auto x: d1) ans+=x;
    for(auto x: d2) ans+=x;

    return ans;
    
}


int main()
{
    fastIO();
    lli n; cin>>n;
    string s; cin>>s;
    string aux;
    for(char c: s)
    {
        if(c!='-')
        {
            aux.push_back(c);
        }
        else
        {
            aux.pop_back();
        }
        //cout << aux << " " << Manacher(aux, aux.size()) << endl;
        //cout << aux << " ";
        cout << Manacher(aux, aux.size()) << " ";
        //cout << endl;
    }
    
    

    return 0;
}