#include <bits/stdc++.h>
#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(lli i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< vector< lli > > STs;
vector< vector< lli > > lazy;
const lli maxN = 100010;

//10
void propagate(lli id, lli idx, lli l, lli r, lli value)
{

    if(value == -1) STs[idx][id] = 0;
    else STs[idx][id] = (r-l+1)*value; //Suma
    if(l!=r)
    {
        lazy[idx][2*id] = value;
        lazy[idx][2*id + 1] = value;
    }
}
//16
void update(lli id, lli idx, lli l, lli r, lli start, lli end, lli value)
{
    if(lazy[idx][id] != 0){
        propagate(id, idx, l, r, lazy[idx][id]);
        lazy[idx][id] = 0;
    }
    if( end < l || r < start) return;
    if ( start <= l && r <= end) propagate(id, idx,  l, r, value);
    else{
        lli mid = (l+r)/2;
        update(2*id, idx, l, mid, start, end, value);
        update(2*id+1, idx,  mid+1, r, start, end, value);
        STs[idx][id] = STs[idx][2*id] + STs[idx][2*id + 1];
    }
}
//14
lli query(lli id, lli idx, lli l, lli r, lli start, lli end) 
{
    if(lazy[idx][id] != 0){
        propagate(id, idx, l, r, lazy[idx][id]);
        lazy[idx][id] = 0;
    }
    if( end < l || r < start) return 0;
    if ( start <= l && r <= end  ) return STs[idx][id];
    else{
        lli mid = l + (r-l)/2;
        return query(2*id, idx, l, mid, start, end) + query(2*id+1, idx, mid+1, r, start, end);
    }
}

void prec()
{
    STs.resize(27, vector< lli >(4*maxN));
    lazy.resize(27, vector< lli >(4*maxN, -1));
}

lli n, q; 

void printAns()
{
    vector< char > ans(n+1);
    for(lli i = 1; i<=n; i++)
    {
        for(lli j = 0; j <= 26; j++)
        {
            //isThere?
            lli isThere = query(1, j, 1, n, i, i);
            assert(isThere <= 1);
            if(isThere)
            {
                assert(isThere == 1);
                //cout << i << " "<< (char)(j+'a') << " " << isThere << endl;
                ans[i] = j + 'a';
            }
        }
    }

    for(lli i = 1; i<=n; i++) cout << ans[i];
    cout << endl;
}

int main()
{
    fastIO();
    prec();
    cin>>n>>q;
    string s; cin>>s;
    for(lli i = 1; i<=n; i++)
    {
        lli idx = s[i-1] - 'a';
        update(1, idx, 1, n, i, i, 1);
    }

    for(lli j = 0; j<q; j++)
    {
        lli l, r, orden; cin>>l>>r>>orden;
        if(orden == 1) // de menor a mayor
        {
            lli curr = l;
            for(lli i = 0; i<=26; i++) //Por cada caracter
            {
                lli howMuch = query(1, i ,1, n, l, r);
                if(howMuch == 0) continue;
                //cout << (char)(i+'a') << " " << howMuch << endl;
                update(1, i, 1, n, l, r, -1);
                //cout << curr << " " << curr + howMuch - 1 << endl;
                update(1, i, 1, n, curr, curr + howMuch - 1, 1);

                curr = curr + howMuch;
            }
            //cout << j << endl;
            //printAns();
        }
        else
        {
            lli curr = l;
            for(lli i = 26; i>=0; i--) //Por cada caracter
            {
                lli howMuch = query(1, i ,1, n, l, r);
                if(howMuch == 0) continue;
                //cout << (char)(i+'a') << " " << howMuch << endl;
                update(1, i, 1, n, l, r, -1);
                //cout << curr << " " << curr + howMuch - 1 << endl;
                update(1, i, 1, n, curr, curr + howMuch - 1, 1);

                curr = curr + howMuch;
            }
            //cout << j << endl;
            //printAns();
        }
    }

    printAns();
    
    

    return 0;
}