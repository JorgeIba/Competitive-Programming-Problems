#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;


int main()
{   
    fastIO();
    vector< char > possibles, aux;


    for(char c = 'a'; c<='z'; c++)
        //possibles.push_back(c);
    
    for(char c = 'a'; c<='z'; c++)
        aux.push_back(c);

    for(int i = 0; i<10; i++) possibles.push_back('?');
    random_shuffle(all(possibles));
    random_shuffle(all(aux));

    lli n = 1e5, m = 10, t = possibles.size(), ta = aux.size();
    srand(time(NULL));

    string s;
    for(int i = 1; i<=n; i++)
    {
        int r = rand() % t;
        cout << possibles[r];
    }
    cout << endl;
    for(int i = 1; i<=m; i++)
    {
        int r = rand() % ta;
        cout << aux[r];
    }
    cout << endl;


    return 0;
}
