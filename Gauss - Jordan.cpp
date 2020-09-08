#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

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
 
    Matrix(lli n): rows(n), cols(n) // Square Matrix of nxn
    {
        A.assign(n, vector<T>(n, 0));
        for(int i = 0; i<rows; i++)
        {
            A[i][i] = 1;
        }
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

    Matrix operator+(lli k) const{
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

    lli GaussJordan(bool SLE = false, vector< ld > &ans = NULL)
    {
        for(int row = 0, col = 0; row < rows && col < cols; col++)
        {
            if(A[row][col] == 0) //* Checa si el pivot es cero
            {
                lli pivot = row;
                for(lli i = row + 1; i<rows; i++ )
                {
                    if( abs( A[i][col] > abs(A[pivot][col]) ) ) //* Selecciona la Pivot como el numero mas grande (Heuristico)
                    {
                        pivot = i;
                    }
                }
                if( abs( A[pivot][col] ) > 0  ) //* Si el numero mas grande no es cero, swapea las dos filas
                { 
                    swapRows(pivot,row);  
                    if(SLE)  swap(ans[pivot], ans[row]);
                } 
                else continue;
            }

            { //* Re-escalea la fila, para que el pivote sea 1.
                ld inverseMult = 1 / A[row][row];
                scaleRow(row, inverseMult);
                if(SLE) ans[row]*=inverseMult;
            }


            for(int i = 0; i<rows; i++) //* Se realizan combinaciones lineales para que los otros numeros sean 0 excepto el pivote
            {
                if(i != row && A[i][col] != 0) //* No se agrega a el mismo ni cuando es 0 ya
                {
                    ld inverseSum = -A[i][col];
                    addRow(i, row, inverseSum);
                    if(SLE) ans[i] += inverseSum*ans[row];
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

int main()
{
    //fastIO();
    Matrix<ld> A(4,4);
    A[0] = {5,2,1,0};
    A[1] = {4, 0, 19, 20};
    A[2] = {3, 2, 0, 4};
    A[3] = {4, 2, 5, 1};

    vector< ld > ans = {4, 15, 0, 7};

    A.printMatrix();
    A.GaussJordan(true, ans);
    A.printMatrix();
    for(int i = 0; i<4; i++)
    {
        cout<<ans[i] << endl;
    }


    return 0;
}