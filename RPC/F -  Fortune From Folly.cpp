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

    Matrix operator*(lli k) const{
        Matrix<T> C(rows, cols);
        for(int i = 0; i<rows; i++)
            for(int j = 0; j<cols; j++)
                C[i][j] = k*A[i][j];
        return C;
    }
    
    Matrix operator*(const Matrix &B) const{

        assert(cols == B.rows);
        Matrix<T> C(rows, B.cols);
 
        for(int i = 0; i<rows; i++)
            for(int j = 0; j<B.cols; j++)
                for(int k = 0; k<cols; k++)
                    C[i][j] += + (A[i][k]*B[k][j]);

        return C;           
    }
 
    Matrix operator^(lli e) const{
        Matrix<T> res = Matrix<T>::Identity(rows);
        Matrix<T> aux = *this;
        while(e)
        {
            if(e&1) res = res*aux;
            e>>=1;
            aux = aux*aux;
        }
        return res;
    }

    Matrix operator+(const Matrix &B) const{
        assert(rows == B.rows && cols == B.cols);
        Matrix<T> C(rows, cols);
        for(int i = 0; i<rows; i++)
            for(int j = 0; j<cols; j++)
                C[i][j] = A[i][j] + B[i][j];
        return C;
    }

    //* ///////////// Gauss-Jordan ///////////////////

    void swapRows(lli i, lli j){ swap(A[i], A[j]); }

    void addRow(lli row1, lli row2, T c)
    {
        for(int j = 0; j<rows; j++) A[row1][j] += ( c * A[row2][j] );
    }

    void scaleRow(lli row, ld k)
    {
        for(int j = 0; j<rows; j++) A[row][j] *= k;
    }

    void GaussJordan(bool SLE = false, Matrix< T > &ans = NULL) // if inverse, ans = Identity
    {
        for(int row = 0, col = 0; row < rows && col < cols; col++)
        {
            if(A[row][col] == 0)
            {
                int pivot = row;
                for(int i = row + 1; i<rows; i++ )
                {
                    if( abs( A[i][col] > abs(A[pivot][col]) ) ) //* Selecciona la Pivot como el numero mas grande (Heuristico)
                    {
                        pivot = i;
                    }
                }
                if( abs( A[pivot][col] ) > 0  ) //* Si el numero mas grande no es cero, swapea las dos filas
                { 
                    swapRows(pivot,row);  
                    if(SLE)  ans.swapRows(pivot, row);
                } 
                else continue;
            }

            { //* Re-escalea la fila, para que el pivote sea 1.
                ld inverseMult = 1 / A[row][row];
                scaleRow(row, inverseMult);
                if(SLE) ans.scaleRow(row, inverseMult);
            }


            for(int i = 0; i<rows; i++) //* Se realizan combinaciones lineales para que los otros numeros sean 0 excepto el pivote
            {
                if(i != row && A[i][col] != 0) //* No se agrega a el mismo ni cuando es 0 ya
                {
                    ld inverseSum = -A[i][col];
                    addRow(i, row, inverseSum);
                    if(SLE) ans.addRow(i, row, inverseSum);
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

        // n_dp[  msk >> 1              ] += (1-p)*dp[msk];
        // n_dp[ (msk >> 1)|(1<<(n-1))  ] +=     p*dp[msk];

int main () {
	//fastIO();

    int n, k; cin>>n>>k;
    ld p; cin>>p;

    Matrix<ld> A(1<<n, 1<<n);
    Matrix<ld> T(1<<n, 1);

    for(int msk = 0; msk < (1<<n); msk++){
        
        if(__builtin_popcount(msk) >= k){
            A[msk][msk] = 1;
            T[msk][0] = 0;
        } else {
            A[msk][msk>>1] += (1-p);
            A[msk][(msk >> 1)|(1<<(n-1))] += p;
            A[msk][msk] += -1;
            T[msk][0] = -1;
        }
    }


    Matrix<ld> I = Matrix<ld>::Identity(1<<n);
    A.GaussJordan(true, I);

    cout << fixed <<  setprecision(10) << (I * T)[0][0] << endl;



	return 0;
}

