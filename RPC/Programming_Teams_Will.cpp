#include <bits/stdc++.h>

#define lli long long int
#define ld double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

template <typename T>
struct Matrix{
    vector< vector< T > > A;
    int rows, cols;

    //* ///////// INIT & STATICS //////////////////////
 
    Matrix(): rows(0), cols(0) {}
 
    Matrix(int n, int m): rows(n), cols(m) // Matrix of n rows and m cols
    {
        A.assign(n, vector<T>(m));
    }
 
    vector<T> &operator[] (int i){ return A[i]; }
    const vector<T> &operator[] (int i) const{ return A[i]; } // To get access without dot

    static Matrix Identity(int n) // Identity Matrix<T>::Identity(rows)
    {
        Matrix<T> I(n,n);
        for(int i = 0; i<n; i++) I[i][i] = 1;
        return I;
    }

    //* /////////////////// Operators ////////////////////////

    Matrix operator-(const Matrix &B) const
    {
        assert(rows == B.rows && cols == B.cols);
        Matrix<T> C(rows,cols);
        for(int i = 0; i<rows; i++)
            for(int j = 0; j<cols; j++)
                C[i][j] = A[i][j] - B[i][j];
        return C;
    }
    
    Matrix operator*(const Matrix &B) const{

        assert(cols == B.rows);
        Matrix<T> C(rows, B.cols);
 
        for(int i = 0; i<rows; i++)
            for(int j = 0; j<B.cols; j++)
                for(int k = 0; k<cols; k++)
                    C[i][j] += (A[i][k]*B[k][j]);

        return C;           
    }
 
    //* ///////////// Operaciones Elementales  ///////////////////

    void swapRows(int i, int j){ swap(A[i], A[j]); } 

    void addRow(int row1, int row2, T c)
    {
        for(int j = 0; j<rows; j++) A[row1][j] += ( c * A[row2][j] );
    }

    void scaleRow(int row, ld k)
    {
        for(int j = 0; j<rows; j++) A[row][j] *= k;
    }


    //* ///////////////// GAUSS - JORDAN //////////////////////////

    int GaussJordan(bool SLE = false, Matrix< T > &ans = NULL) // if inverse, ans = Identity
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
};

int main()
{
    fastIO();
    int n, m; cin>>n>>m;

    Matrix<ld> M(m-n,n), N(n,n), V(n,1), I = Matrix<ld>::Identity(n);
    // M es la matriz donde se ponen lo que le toca a cada "m" (filas), como dependen de cada "n" wey, entonces la 
    // dimesion es de m*n, donde m son los morrillos que no dan dulces

    //N es la matriz donde va lo que le toca a cada morrillo que si da paletas, por eso la matriz aqui es de size n*n

    // V son las valores que tienen los morrillos, al inicio V se rellena con las paletas que tienen al inicio

    // La respuesta se va a encontrar en la matriz:   M * N^0 * V_0  +  M * N^1 * V_0 + M * N^2 * V_0 + ...
    // Que es igual a M * (I-N)^1 * V_0 por la formulita de serio geometrica donde el ^1 representa la matriz inversa

    for(int i = 0; i<n; i++)
    {
        int v, e; cin>>v>>e;
        V[i][0] = v; // Se llena la matriz V inicial
        while(e--)
        {
            ld per;
            int index; cin>>index>>per; index--;
            if( index < n ) // Los que reparten
            {
                N[index][i] = per;
            }
            else // Los que no reparten 
            {
                M[index-n][i] = per;
            }
        }
    }

    Matrix<ld> inverse = Matrix<ld>::Identity(n);

    (I-N).GaussJordan(true, inverse); // Se hace Gauss Jordan sobre la matriz I-N, y las mismas operaciones que se le realicen
                                      // Se aplican a la matriz identidad, para asi obtener la matriz inversa de I-N
    
    M = M * (inverse * V);
    // M = (M*inverse)*V no entra
    
    
    cout<<fixed<<setprecision(7);
    for(int i = 0; i<m; i++)
    {
        if(i<n) cout<<0<<endl;
        else cout<<M[i-n][0]<<endl;
    }

    

    return 0;
}