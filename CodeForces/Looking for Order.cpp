
#include <bits/stdc++.h>
#define lli int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define x first
#define y second

using namespace std;

const lli maxN = 25, INF = 1e9;
lli dist[maxN][maxN];
int pointsx[27];
int pointsy[27];

lli dp[(1<<maxN)];
lli n; 
int recorrido[16777230][3];

lli getDist(int &i, int &j)
{
    int x1 = pointsx[i], x2 = pointsx[j];
    int y1 = pointsy[i], y2 = pointsy[j];
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

void build()
{
    for(int i = 0; i<n; i++)
    {
        for(int j = i+1; j<n; j++)
        {
            dist[j][i] = dist[i][j] = getDist(i, j);
        }
    }
}


int main()
{
    fastIO();
    lli xs, ys; cin>>xs>>ys;
    cin>>n;
    pointsx[n] = xs, pointsy[n] = ys;
    
    for(int i = 0; i<n; i++)
    {
        cin>>pointsx[i]>>pointsy[i];
        dist[n][i] = dist[i][n] =  getDist(n, i);
    }
    build();

    dp[0] = 0;
    int i = 0;
    for(int mask = 1; mask< (1<<n); mask++)
    {
        dp[mask] = INF;
        for(; i<n; i++)
        {
            if( (mask&(1<<i))  )
            {
                lli aux1 = dp[mask ^ (1<<i)] + 2*dist[n][i];
                if(aux1 <= dp[mask])
                {
                    dp[mask] = aux1;
                    recorrido[mask][0] = mask^(1<<i);
                    recorrido[mask][1] = i;
                    recorrido[mask][2] = -1;
                }
                
                for(int j = 0; j<n; j++)
                {
                    if(  (mask&(1<<j)) )
                    {
                        lli aux =  dist[n][i] + dist[i][j] + dist[j][n] + dp[mask^(1<<i)^(1<<j)];
                        if(aux <= dp[mask] )
                        {
                            dp[mask] = aux;
                            recorrido[mask][0] = mask^(1<<i)^(1<<j);
                            recorrido[mask][1] = i;
                            recorrido[mask][2] = j;
                        }
                    }
                }
                break;
            }
        }
    }
    lli curr = (1<<n) - 1;
    cout<< dp[curr] << endl;
    while(curr)
    {
        cout<<0<<" ";
        if(recorrido[curr][2] == -1)
        {
            cout<< recorrido[curr][1]+1<<" ";
        }
        else
        {
            cout << recorrido[curr][1]+1 <<" "<<recorrido[curr][2]+1<<" ";
        }
        curr = recorrido[curr][0];
    }
    cout<< 0 << endl;
    


    return 0;
}