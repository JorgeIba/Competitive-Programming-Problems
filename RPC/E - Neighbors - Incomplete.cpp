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


vector< vector<int> > M;
int masksCol[15];
int masksRow[15];
int n, k;
const int MARK = 100;


void printM() {
    for(int i = 0; i < 2*n-1; i++) {
        for(int j = 0; j < 2*n-1; j++) {
            cout << M[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}


bool checkRow(int num, int row) {
    return !((1LL<<num) & masksRow[row]);
}

bool checkCol(int num, int col) {
    return !((1LL<<num) & masksCol[col]);
}

bool checkVecindario(int row, int col) {
    bool up = true;
    if(row > 0) {
        if( M[2*row-1][2*col] == MARK ){
            if((abs(M[2*row][2*col] - M[2*(row-1)][2*col]) != 1))
                up = false;
        } else {
            if((abs(M[2*row][2*col] - M[2*(row-1)][2*col]) == 1))
                up = false;
        }
    }

    bool left = true;
    if(col > 0) {
        if(M[2*row][2*col-1]) {
            if((abs(M[2*row][2*col] -  M[2*row][2*(col-1)] ) != 1)) 
                left = false;
        } else {
            if((abs(M[2*row][2*col] -  M[2*row][2*(col-1)] ) == 1)) 
                left = false;
        }
    }
    return up && left;
}


bool checkVecindarioDer(int row, int col) {
    if(col < n-2) {
        if(M[2*row][2*col+1]) {
            return true;
        }
    }
    return false;
}

bool checkVecindarioAba(int row, int col) {
    if(row < n-2) {
        if(M[2*row+1][2*col]) {
            return true;
        }
    }
    return false;
}



bool solve(int row, int col) {
    if(col >= n) return solve(row+1, 0);
    if(row >= n) {
        return true;
    }

    if(M[2*row][2*col]) {
        if(checkVecindario(row, col)) {
            if(solve(row, col+1)) return true;
        }
    } else {
        // cout << row << " " << col << endl;
        for(int d = 1; d <= n; d++) {
        
            if(!(checkRow(d, row) && checkCol(d, col))) continue;
            
            M[2*row][2*col] = d;
            masksRow[row] |= (1ll << d);
            masksCol[col] |= (1ll << d);


            bool flagAba = true, flagDer = true;
            
            if(checkVecindarioAba(row, col)) {
                vector<int> options;
                if(d > 1) options.push_back(d-1);
                if(d < n) options.push_back(d+1);

                flagAba = false;
                for(auto option: options){
                    if( option == M[2*(row+1)][2*col] || checkCol(option, col))
                        flagAba = true;
                }
            } else {
                int auxMask = masksCol[col];
                if(d > 1) auxMask |= (1LL << (d-1));
                if(d < n) auxMask |= (1LL << (d+1));

                auxMask ^= (1 << (n-1))-1;
                flagAba = auxMask;
            }

        
            if(checkVecindarioDer(row, col)) {
                vector<int> options;
                if(d > 1) options.push_back(d-1);
                if(d < n) options.push_back(d+1);

                flagDer = false;
                for(auto option: options){
                    if( option == M[2*row][2*(col+1)] || checkRow(option, row))
                        flagDer = true;
                }
            } else {
                int auxMask = masksRow[row];
                if(d > 1) auxMask |= (1LL << (d-1));
                if(d < n) auxMask |= (1LL << (d+1));

                auxMask ^= (1 << (n-1))-1;
                flagDer = auxMask;
            }


            if(flagAba && flagDer && checkVecindario(row, col)) {
                if(solve(row, col+1)) return true;
            }


            M[2*row][2*col] = 0;
            masksRow[row] &= ~(1ll << d);
            masksCol[col] &= ~(1ll << d);
        }
    }
    return false;
}



int main () {
	// fastIO();

    

    cin>>n>>k;


    time_t start = clock();

    M.assign(2*n, vector<int>(2*n));

    for(int i = 0; i < 2*n-1; i++) {
        string s; cin>>s;
        if(i % 2 == 0) { // horizontal
            lli y = i;
            for(int x = 0; x < n; x++) {
                if(s[x] == '1') {
                    M[y][2*x+1] = MARK;
                }
            }
        } else { // vertical
            lli y = i;
            for(int x = 0; x < n; x++) {
                if(s[x] == '1') {
                    M[y][2*x] = MARK;
                }
            }
        }
    }


    for(int i = 0; i < k; i++) {   
        int row, col, val; cin>>row>>col>>val; row--, col--;
        M[2*row][2*col] = val;
        masksCol[col] = masksCol[col] | (1LL << val);
        masksRow[row] = masksRow[row] | (1ll << val);
    }


    solve(0, 0);

    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << M[2*i][2*j] << " ";
        }
        cout << endl;
    }
    

    cout << (double)(clock() - start) / CLOCKS_PER_SEC << endl;


	return 0;
}

