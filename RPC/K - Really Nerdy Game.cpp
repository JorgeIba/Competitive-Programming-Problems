#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


const lli MOD = 10007;


lli powerMod(lli a, lli b, lli mod){
    lli res = 1;
    while(b) {
        if(b & 1) res = res * a  % mod;
        b >>= 1;
        a = a * a  % mod;
    }
    return res;
}



template <typename T>
struct Matrix{
    vector< vector< T > > A;
    lli rows, cols;

    //* ///////// INIT & STATICS //////////////////////
 
    Matrix(): rows(0), cols(0) {}
 
    Matrix(lli n, lli m): rows(n), cols(m) // Matrix of n rows and m cols
    {
        A.assign(n, vector<T>(m));
    }

    vector<T> &operator[] (int i){ return A[i]; }
    const vector<T> &operator[] (int i) const{ return A[i]; } // To get access without dot

    static Matrix Identity(lli n) // Identity Matrix<T>::Identity(rows)
    {
        Matrix<T> I(n,n);
        for(int i = 0; i<n; i++) I[i][i] = 1;
        return I;
    }

    //* /////////////////// Operators ////////////////////////
    //* ///////////// Gauss-Jordan ///////////////////

    void swapRows(lli i, lli j){ swap(A[i], A[j]); }

    void addRow(lli row1, lli row2, T c)
    {
        for(int j = 0; j<cols; j++) (A[row1][j] += ( c * A[row2][j] % MOD )) %= MOD;
    }

    void scaleRow(lli row, T k)
    {
        for(int j = 0; j<cols; j++) A[row][j] = A[row][j] * k % MOD;
    }

    T inverseMult(T k) {
        // return 1 / k;
        return powerMod(k, MOD-2, MOD);
    }

    T inverseSum(T k) {
        // return -k;
        return (MOD-k % MOD) % MOD;
    }


    void GaussJordan(bool SLE = false, Matrix< T > &ans = NULL) // if inverse, ans = Identity
    {
        for(int row = 0, col = 0; row < rows && col < cols; col++)
        {
            if(A[row][col] == 0)
            {
                int pivot = row;
                for(int i = row + 1; i<rows; i++ ){
                    if( abs( A[i][col] > abs(A[pivot][col]) ) ){ //* Selecciona la Pivot como el numero mas grande (Heuristico)
                        pivot = i;
                    }
                }
                if( abs( A[pivot][col] ) > 0  ){ //* Si el numero mas grande no es cero, swapea las dos filas
                    swapRows(pivot,row);  
                    if(SLE) ans.swapRows(pivot, row);
                } 
                else continue;
            }

            //* Re-escalea la fila, para que el pivote sea 1.
            T invMult = inverseMult(A[row][row]);
            scaleRow(row, invMult);
            if(SLE){
                ans.scaleRow(row, invMult);
            } 


            for(int i = 0; i<rows; i++) //* Se realizan combinaciones lineales para que los otros numeros sean 0 excepto el pivote
            {
                if(i != row && A[i][col] != 0) //* No se agrega a el mismo ni cuando es 0 ya
                {
                    T invSum = inverseSum(A[i][col]);
                    addRow(i, row, invSum);
                    if(SLE) ans.addRow(i, row, invSum);
                }
            }
            row++;
        }
    }

        //* //////////////////////////////////////////////
    void printMatrix()
    {
        for(int i = 0; i<rows; i++)
        {
            cout<<"|";
            for(int j = 0; j<cols; j++)
            {
                cout<<A[i][j]<< (j!=cols-1? " ": "");
            }
            cout<<"|\n";
        }
        cout << endl;
    } 
};



int main () {
	fastIO();
	lli n, d, w, l; cin>>n>>d>>w>>l;

    Matrix<lli> A(n, n), T(n, 1);

    vector<lli> win(w), loses(l);

    for(auto &x: win) cin>>x;
    for(auto &x: loses) cin>>x;


    vector<int> visited(n);
    for(auto &x: win) visited[x-1] = 1;
    for(auto &x: loses) visited[x-1] = -1;


    lli prob = powerMod(d, MOD-2, MOD);


    for(int i = 0; i < n; i++) {
        if(visited[i] != 0) {
            A[i][i] = 1;
            T[i][0] = visited[i] == 1 ? 1 : 0;
            continue;
        }

        for(int j = 1; j <= d; j++) {
            int idx = (i + j) % n;
            if(idx == i) continue;
            A[i][idx] += prob;
        }

        
        lli laps = d / n;
        lli left = laps * prob;
        lli mult = (1 - left) % MOD;
        if(mult < 0) mult += MOD;

        for(int j = 0; j < n; j++) {
            if(j == i) continue;
            A[i][j] = A[i][j] * powerMod(mult, MOD-2, MOD) % MOD;
        }

        A[i][i] = MOD-1;
    }



    // A.printMatrix();
    A.GaussJordan(true, T);
    
    // T.printMatrix();
    cout << T[0][0] << endl;


	return 0;
}

