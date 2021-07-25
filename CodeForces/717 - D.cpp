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
 
    Matrix(): rows(0), cols(0) {}
 
    Matrix(lli n, lli m): rows(n), cols(m) // Matrix of n rows and m cols
    {
        A.assign(n, vector<T>(m, 0));
    }

    vector<T> &operator[] (int i){ return A[i]; }
    const vector<T> &operator[] (int i) const{ return A[i]; } // To get access without dot

    static Matrix Identity(lli n) // Identity Matrix<T>::Identity(rows)
    {
        Matrix<T> I(n,n);
        for(int i = 0; i<n; i++) I[i][i] = 1;
        return I;
    }

    
    Matrix operator*(const Matrix &B) const{

        assert(cols == B.rows);
        Matrix<T> C(rows, B.cols);
 
        for(int i = 0; i<rows; i++)
            for(int j = 0; j<B.cols; j++)
                for(int k = 0; k<cols; k++)
                    C[i][j] +=  (A[i][k]*B[k][j]);

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

    lli n, X; cin>>n>>X;

    vector<ld> prob(X+1);
    for(auto &p: prob) cin>>p;


    const lli maxXOR = 127;
    Matrix<ld> A(maxXOR+1,maxXOR+1);
    for(int i = 0; i<=maxXOR; i++)
    {
        for(int j = 0; j<=X; j++)
        { 

            if((i^j) > 128) continue;
            
            A[i][i^j] = prob[j];
        }
    }


    //(A^2).printMatrix();

    //A.printMatrix();

    A = A^(n);

    //A.printMatrix();

    cout << fixed << setprecision(10) << (ld)(1 - A[0][0]) << endl;


	return 0;
}

