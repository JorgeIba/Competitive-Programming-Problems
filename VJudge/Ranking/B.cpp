#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n, k; cin>>n>>k;
    vector< string > cadenas(n);
    set<string> check;
    for(auto &x: cadenas)
    {
        cin>>x;
        check.insert(x);
    }

    lli res = 0;

    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            string buscar = "";
            for(int q = 0; q<k; q++)
            {
                char up = cadenas[i][q];
                char down = cadenas[j][q];
                //cout<<up<<" "<<down<<endl;

                if( up == 'S'  )
                {
                    if(down == 'S')
                    {
                        buscar += 'S';
                    }
                    else if (down == 'E')
                    {
                        buscar += 'T';
                    }
                    else
                    {
                        buscar += "E";
                    }
                }
                else if ( up == 'E' )
                {
                    if(down == 'E')
                    {
                        buscar += 'E';
                    }
                    else if (down == 'S')
                    {
                        buscar += 'T';
                    }
                    else
                    {
                        buscar += 'S';
                    }
                }
                else //up == "T"
                {
                    if(down == 'T')
                    {
                        buscar += 'T';
                    }
                    else if (down == 'S')
                    {
                        buscar += 'E';
                    }
                    else
                    {
                        buscar += 'S';
                    }
                }
            }

            if(check.count(buscar))
            {
                //cout<<buscar<<endl;
                res++;
            }

        }
        //string asd = cadenas[i];
        //check.erase(asd);
    }

    cout<<(res/3)<<endl;



    return 0;
}