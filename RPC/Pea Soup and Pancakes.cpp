#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
    //fastIO();
    lli t; cin>>t;  
    string a = "pea soup";
    string b = "pancakes";

    string res;
    bool noHayRespuesta = true;
    while(t--)
    {
        bool flag1 = false, flag2 = false;
        lli n; cin>>n;
        cin.ignore();
        string s;
        getline(cin, s);
        //cout << n << " " << s << endl;
        while(n--)
        {
            string item;
            getline(cin, item);
            if(item == a) flag1 = true;
            if(item == b) flag2 = true;
            if(flag1 && flag2 && noHayRespuesta)
            {
                res = s;
                noHayRespuesta = false;
            }
        }
    }

    if(!noHayRespuesta)
        cout << res << endl;
    else 
        cout << "Anywhere is fine I guess\n";

    return 0;
}