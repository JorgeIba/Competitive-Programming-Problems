#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< vector< lli > > Mat(5, vector<lli>(5,-1));
vector< lli > moves;

void read(lli howMuch, lli row)
{
    for(int i = 0; i<howMuch; i++)
    {
        char aux; cin>>aux;
        if(aux == '.') Mat[row][i] = 0;
        else Mat[row][i] = 1;
    }
}

void printMat()
{
    for(auto x: Mat)
    {
        for(auto v: x) cout << v << " ";
        cout << endl;
    }
}

void prep()
{
    read(3, 0); read(4, 1); read(5, 2); read(4, 3); read(3, 4);
}

void getPosibles()
{
    set<lli> uniques;
    vector< vector< lli > > diagonalIzq = { {0, 3, 7}, {1, 4, 8, 12}, {2, 5, 9, 13, 16}, {6, 10, 14, 17}, {11, 15, 18} };
    for(int i = 0; i<5; i++)
    {
        vector<lli> currDiag = diagonalIzq[i];
        for(int j = 0; j < currDiag.size(); j++)
        {
            lli mask = 0;
            for(int k = j; k>=0; k--)
            {
                lli num = currDiag[k];
                mask = mask|(1<<(num));
                moves.push_back(mask);
            }
        }
    }
    
    vector< vector< lli > > horizontal = { {0, 1, 2}, {3, 4, 5, 6}, {7, 8, 9, 10, 11}, {12, 13, 14, 15}, {16, 17, 18}  };
    for(int i = 0; i<5; i++)
    {
        vector<lli> currHori = horizontal[i];
        for(int j = 0; j < currHori.size(); j++)
        {
            lli mask = 0;
            for(int k = j; k>=0; k--)
            {
                lli num = currHori[k];
                mask = mask|(1<<(num));
                if(k==j) continue;
                moves.push_back(mask);
            }
        }
    }
    vector< vector< lli > > diagonalDer = { {7, 12, 16}, {3, 8, 13, 17}, {0, 4, 9, 14, 18}, {1, 5, 10, 15}, {2, 6, 11} };

    for(int i = 0; i<5; i++)
    {
        vector<lli> currDer = diagonalDer[i];
        for(int j = 0; j < currDer.size(); j++)
        {
            lli mask = 0;
            for(int k = j; k>=0; k--)
            {
                lli num = currDer[k];
                mask = mask|(1<<(num));
                if(k==j) continue;
                moves.push_back(mask);
            }
        }
    }

}

lli getMask()
{
    vector< lli > aux;
    for(int i = 0; i<3; i++) aux.push_back(Mat[0][i]);
    for(int i = 0; i<4; i++) aux.push_back(Mat[1][i]);
    for(int i = 0; i<5; i++) aux.push_back(Mat[2][i]);
    for(int i = 0; i<4; i++) aux.push_back(Mat[3][i]);
    for(int i = 0; i<3; i++) aux.push_back(Mat[4][i]);
    lli mask = 0;
    for(int i = 0; i<19; i++)
    {
        if(aux[i])
        {
            mask = mask | (1<<i);
        }
    }
    return mask;
}

int main()
{
    fastIO();
    prep();
    lli maskPrincipal = getMask();
    getPosibles();

    vector< lli > dp((1<<19));
    dp[0] = 0;
    
    for(lli mask = 1; mask < (1<<19); mask++)
    {
        unordered_set<int> toGrundy;
        vector<bool> Grundy(50);
        for(auto move: moves)
        {
            if( (mask & move) == move ) // Es un subconjunto del movimiento -> es un movimiento valido
            {
                //toGrundy.insert( dp[ mask & (~move) ]  );
                Grundy[ dp[ mask & (~move)  ]  ] = true;
            }
        }
        for(int i = 0; i<50; i++)
        {
            if(!Grundy[i])
            {
                dp[mask] = i;
                break;
            }
        }
    }

    if( dp[maskPrincipal] )
    {
        cout << "Karlsson" << endl;
    }
    else
    {
        cout << "Lillebror" << endl;
    }

    return 0;
}