#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli MOD = 1e9 + 7;

struct Matrix{
    vector< vector< lli > > M;
    lli row, col;

    Matrix(): row(0), col(0) {}

    Matrix(lli n, lli m): row(n), col(m)
    {
        M.assign(n, vector<lli>(m, 0));
    }

    Matrix(lli n): row(n), col(n) 
    {
        M.assign(n, vector<lli>(n, 0));
        for(int i = 0; i<row; i++)
        {
            M[i][i] = 1;
        }
    }
    
    Matrix operator *(Matrix B)
    {
        Matrix C = Matrix(row, B.col);
        for(int i = 0; i<row; i++)
            for(int j = 0; j<B.col; j++)
                for(int k = 0; k<col; k++)
                    C.M[i][j] = (C.M[i][j] +  (M[i][k]*B.M[k][j])%MOD)%MOD;
        return C;           
    }

    Matrix operator^(lli e)
    {
        Matrix res(row);
        Matrix aux = *this;
        while(e)
        {
            if(e&1) res = res*aux;
            e>>=1;
            aux = aux*aux;
        }
        return res;
    }

    void printMatrix()
    {
        for(int i = 0; i<row; i++)
        {
            cout<<"|";
            for(int j = 0; j<col; j++)
            {
                cout<<M[i][j]<< (j!=col-1? " ": "");
            }
            cout<<"|\n";
        }
    }

};

int main()
{
    fastIO();
    lli n, b, k, x; cin>>n>>b>>k>>x;
    vector<lli> nums(n);
    map<lli,lli> fr;
    for(auto &x: nums)
    {
        cin>>x;
        fr[x]++;
    }
    Matrix F1 = Matrix(x, 1);

    for(int i = 1; i<=9; i++)
    {
        F1.M[ i%x ][0] += fr[i];
    }

    Matrix T = Matrix(x,x);

    for(int i = 0; i<x; i++)
    {
        for(int j = 1; j<=9; j++)
        {
            T.M[(i*10 + j)%x ][ i ] += fr[j];
        }
    }

    //dp[i][j] Con un numero de i digitos, cuantos con modulo j.
    //T.M[i][j] 

    Matrix FB = (T^(b-1)) * F1;

    cout << FB.M[k][0] << endl;

    return 0;
}