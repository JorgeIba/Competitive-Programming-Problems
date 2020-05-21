#include <bits/stdc++.h>
#define lli long long int

using namespace std;

vector< vector<lli> >  matrix;
vector< pair<lli,lli> > ans;
lli t; 

bool checkLinea(int i, int j)
{
    lli countingUp = 0, countingDown = 0;
    lli iUp = i-1, iDown = i+1;
    while(iUp>=0 and (matrix[iUp][j]==0))
    {
        countingUp++;
        iUp--;
    }
    while(iDown< t and (matrix[iDown][j]==0))
    {
        countingDown++;
        iDown++;
    }
    /////////////////////////////////////
    lli countingLeft = 0, countingRight = 0;
    lli jLeft = j-1, jRight = j+1;
    while(jLeft>=0 and (matrix[i][jLeft]==0))
    {
        countingLeft++;
        jLeft--;
    }
    while(jRight< t and (matrix[i][jRight]==0))
    {
        countingRight++;
        jRight++;
    }

    if((countingRight + countingLeft + 1 >= 5) or (countingDown + countingUp + 1 >= 5)) 
    {
        ans.push_back({i+1,j+1});
        return true;
    }
    return false;
}

void checkDiag(int i, int j)
{
    lli iUp = i-1, iDown = i+1, jLeft = j-1, jRight = j+1;
    lli diagIzqUp = 0, diagDerUp = 0, diagIzqDown = 0, diagDerDown = 0;
    while( iUp >= 0 and jLeft>=0 and (matrix[iUp][jLeft]==0) )
    {
        diagIzqUp++;
        iUp--;
        jLeft--;
    }
    iUp = i-1, jLeft = j-1;
    while( iUp >= 0 and jRight < t and (matrix[iUp][jRight]==0) )
    {  
        diagDerUp++;
        iUp--;
        jRight++;
    }
    iUp=i-1, jRight = j+1;
    while( iDown < t and jLeft>=0 and (matrix[iDown][jLeft]==0) )
    {
        diagIzqDown++;
        iDown++;
        jLeft--;
    }
    iDown = i+1, jLeft = i-1;
    while( iDown <t and jRight<t and (matrix[iDown][jRight]==0) )
    {
        diagDerDown++;
        iDown++;
        jRight++;
    }
    if( (diagIzqUp + diagDerDown + 1 >=5) or (diagDerUp + diagIzqDown + 1 >=5))
    {
        //cout<<diagIzqUp <<" "<<diagDerDown<<"-----"<<diagIzqDown<<" "<<diagDerUp<<endl;
        ans.push_back({i+1,j+1});
    }
    return;

}



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    matrix.assign( t, vector<lli> (t,-1) );
    lli n; cin>>n;
    for(int i = 0; i<n; i++)
    {
        lli x,y,type; cin>>x>>y>>type;
        x--, y--;
        matrix[x][y] = type;
    }

    for(int i = 0; i<t; i++)
    {
        for(int j = 0; j < t; j++)
        {
            if(matrix[i][j] == -1)
            {
                if( checkLinea(i,j) ) 
                {
                    continue;
                }
                else
                {
                    checkDiag(i,j);
                }
            }
        }
    }
    for(auto x: ans)
    {
        cout<<x.first<<" "<<x.second<<endl;
    }

    return 0;
}