#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int mp(char a)
{
    switch(a)
    {
        case 'A':
            return 0;
        case 'B':
            return 1;
        case 'C':
            return 2;
        case 'D':
            return 3;
    }
}

int mp2(char f)
{
    if(f=='F') return 0;
    return 1;
}

char mp3(int a)
{
    switch(a)
    {
        case 0:
            return 'A';
        case 1:
            return 'B';
        case 2:
            return 'C';
        case 3:
            return 'D';
    }
}



void solve()
{
    lli q, m; cin>>q>>m;
    vector< vector< int > > questions(q, vector<int>(4,-1));
    forn(i,0,m)
    {
        forn(j,0,q)
        {
            char a, ac; cin>>a>>ac;
            questions[j][mp(a)] = mp2(ac);
        }
    }
    forn(i,0,q)
    {
        int cont = 0;
        int last = -1;
        bool flag = false;
        forn(j,0, 4){
            if(questions[i][j]==1) 
            {
                if(i==q-1)
                {
                    cout<<mp3(j);    
                }
                else
                {
                    cout<<mp3(j)<<" ";
                }
                flag = true;
                break;
            }
            if(questions[i][j] == -1)
            {
                last = j;
                cont++;
            }
        }
        if(!flag)
        {
            if(cont == 1)
            {
                if(i==q-1)
                {
                    cout<<mp3(last);    
                }
                else
                {
                    cout<<mp3(last)<<" ";
                }
                continue;
            }
            else
            {
                if(i==q-1)
                {
                    cout<<"?";
                }
                else
                {
                    cout<<"? ";
                }
            }
            
        }
    }
    cout<<endl;
        
}



int main()
{
    fastIO();
    lli t; cin>>t;
    while (t--)
    {
        solve();
    }

    return 0;
}