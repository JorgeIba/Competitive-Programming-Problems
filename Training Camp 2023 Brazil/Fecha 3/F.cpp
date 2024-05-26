#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

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
        for(int j = 0; j<cols; j++) A[row1][j] += ( c * A[row2][j] );
    }

    void scaleRow(lli row, ld k)
    {
        for(int j = 0; j<cols; j++) A[row][j] *= k;
    }

    T inverseMult(T k) {
        return 1 / k;
        // return powerMod(k, MOD-2, MOD);
    }

    T inverseSum(T k) {
        return -k;
        // return (MOD-k % MOD) % MOD;
    }


    void GaussJordan(bool SLE = false, Matrix< T > &ans = NULL) // if inverse, ans = Identity
    {
        for(int row = 0, col = 0; row < rows && col < cols; col++)
        {
            if(A[row][col] == 0)
            {
                int pivot = row;
                for(int i = row + 1; i<rows; i++ ){
                    if( abs( A[i][col] > abs(A[pivot][col]) ) ){
                        pivot = i;
                    }
                }
                if( abs( A[pivot][col] ) > 0  ){ 
                    swapRows(pivot,row);  
                    if(SLE) ans.swapRows(pivot, row);
                } 
                else continue;
            }

            
            T invMult = inverseMult(A[row][row]);
            scaleRow(row, invMult);
            if(SLE){
                ans.scaleRow(row, invMult);
            } 


            for(int i = 0; i<rows; i++) 
            {
                if(i != row && A[i][col] != 0) 
                {
                    T invSum = inverseSum(A[i][col]);
                    addRow(i, row, invSum);
                    if(SLE) ans.addRow(i, row, invSum);
                }
            }
            row++;
        }
    }
};



int main () {
	//fastIO();
	
	int n, k; cin>>n>>k;
    ld p; cin>>p;

    int m = 1 << n;
    Matrix<ld> M(m, m);
    Matrix<ld> A(m, 1);

    int filter = (1 << n) - 1;
    for(int mask = 0; mask < m; mask++){
        if(__builtin_popcount(mask) >= k) {
            M[mask][mask] = 1;
            A[mask][0] = 0;
            continue;
        }

        M[mask][mask] = 1;
        int mask_yes = (mask << 1 | 1) & filter;
        int mask_no = (mask << 1) & filter;
        M[mask][  mask_yes  ] -= p;
        M[mask][  mask_no   ] -= (1 - p);

        A[mask][0] = 1;
    }

    // M.printMatrix();
    // A.printMatrix();

    M.GaussJordan(true, A);

    cout << fixed << setprecision(15);
    cout << A[0][0] << endl;

	return 0;
}

