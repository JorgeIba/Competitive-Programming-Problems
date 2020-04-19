#include <bits/stdc++.h>
#define lli long long int

using namespace std;

vector< vector<lli> > matrix(1001,vector<lli>(1001,0));

void dfs(lli i, lli j, lli num, char dir)
{
    //cout<<i<<" "<<j<<endl;
    if(i<0 || j<0 || i>=1000 || j>=1000)
        return;

    matrix[i][j] = num;
    switch(dir)
    {
        case 'A':
            if(matrix[i][j-1] != 0)
                dfs(i+1,j,num+1,'A');
            else
                dfs(i, j-1, num+1,'I');
            break;
        case 'I':
            if(matrix[i-1][j] != 0)
                dfs(i,j-1,num+1,'I');
            else
                dfs(i-1, j, num+1,'U');
            break;
        case 'U':
            if(matrix[i][j+1] != 0)
                dfs(i-1,j,num+1,'U');
            else
                dfs(i, j+1, num+1,'D');
            break;
        case 'D':
            if(matrix[i+1][j] != 0)
                dfs(i,j+1,num+1,'D');
            else
                dfs(i+1, j, num+1,'A');
            break;
    }
}


int main()
{
    matrix[500][500] = 1;
    dfs(500,501,2,'A');
    lli res = 0;

    for(int i = 0; i<=1000; i++)
    {
        res += matrix[i][i] + matrix[1000-i][i];
    }
    res -= 1;
    cout<<res<<endl;
    


    return 0;
}