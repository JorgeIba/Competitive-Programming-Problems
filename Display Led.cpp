#include <bits/stdc++.h>
#define lli long long int

using namespace std;


vector< string > mapa;
vector< vector<bool> > check;
lli n, m;

int main()
{   
    
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin>>n>>m;
    mapa.resize(n);
    check.assign(n, vector<bool> (m, false));


    for(int i = 0; i < n; i++)
    {
        cin >> mapa[i];
    }

    lli mini = 10000000LL, maxi = -1;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if((mapa[i][j] == 'X') and (!check[i][j]))
            {
                lli contx=0;
                for(int x = j; x<m; x++)
                {
                    if(mapa[i][x] == '0')
                    {
                        break;  
                    } 
                    else
                    {
                        contx++;
                        check[i][x] = true;
                    }
                }

                lli conty = 0;
                for(int y = i; y<n; y++)
                {
                    if(mapa[y][j] == '0') break;
                    else
                    {
                        conty++;
                        check[y][j] = true;
                    }
                }

                
                for(int a = 0; a<conty; a++)
                {
                    for(int b = 0; b <contx; b++)
                    {
                        mapa[i+a][j+b] = true;
                        //cout<<"("<<(i+a)<<","<<(j+b)<<") ";
                    }
                    //cout<<endl;
                }    
                //cout<<endl<<endl;
                
                
                lli area = contx * conty;
                if(area > 0)
                {
                    maxi = max(maxi, area);
                    mini = min(mini, area);
                }
            }
        }
    }

    cout<<maxi<<endl<<mini<<endl;

}

