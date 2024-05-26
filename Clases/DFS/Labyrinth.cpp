#include <bits/stdc++.h>
 
using namespace std;

const int MAXN = 1000 + 100;

char mat[MAXN][MAXN];
int dist[MAXN][MAXN];
pair<int,int> parent[MAXN][MAXN];
int n, m; 

// Función que me permite saber si las coordenadas {x, y} están dentro de la matriz
bool isInside(int x, int y){
    return (0 <= x && x < n && 0 <= y && y < m);
}

int main () {	
    cin>>n>>m;

    int A_i, A_j, B_i, B_j;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin>>mat[i][j];

            // Registro la posición de A
            if(mat[i][j] == 'A'){
                A_i = i;
                A_j = j;
            }

            // Registro la posición de B
            if(mat[i][j] == 'B'){
                B_i = i;
                B_j = j;
            }
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            // Si dist[x][y] = -1
            // Significa que el nodo {x, y} no lo he visitado
            dist[i][j] = -1;
        }
    }


    queue< pair<int,int> > q;

    q.push({A_i, A_j});
    dist[A_i][A_j] = 0;

    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        // Puedo irme a la izquierda?
        if(isInside(x, y-1) && mat[x][y-1] != '#' && dist[x][y-1] == -1){
            dist[x][y-1] = dist[x][y] + 1;
            parent[x][y-1] = {x, y};

            q.push({x, y-1});
        }

        // Puedo irme a la derecha?
        if(isInside(x, y+1) && mat[x][y+1] != '#' && dist[x][y+1] == -1){
            dist[x][y+1] = dist[x][y] + 1;
            parent[x][y+1] = {x, y};

            q.push({x, y+1});
        }

        // Puedo irme arriba?
        if(isInside(x-1, y) && mat[x-1][y] != '#' && dist[x-1][y] == -1){
            dist[x-1][y] = dist[x][y] + 1;
            parent[x-1][y] = {x, y};

            q.push({x-1, y});
        }

        // Puedo irme abajo?
        if(isInside(x+1, y) && mat[x+1][y] != '#' && dist[x+1][y] == -1){
            dist[x+1][y] = dist[x][y] + 1;
            parent[x+1][y] = {x, y};

            q.push({x+1, y});
        }
    }

    if(dist[B_i][B_j] == -1){
        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;
    cout << dist[B_i][B_j] << endl;

    int curr_i = B_i;
    int curr_j = B_j;
    int shortest_distance = dist[B_i][B_j];
    vector< char > path;
    for(int i = 0; i < shortest_distance; i++){
        int prev_node_i = parent[curr_i][curr_j].first;
        int prev_node_j = parent[curr_i][curr_j].second;


        if(prev_node_i != curr_i) {
            if(curr_i - prev_node_i == -1){
                // Signica que tengo algo del estilo
                // {x, y} => {x-1, y}
                // Es decir, me moví hacia arriba
                path.push_back('U');
            } else {
                path.push_back('D');
            }
        } else {
            
            if(curr_j - prev_node_j == -1){
                // Significa que tengo algo del estilo
                // {x, y} => {x, y-1}
                // Es decir, me movi hacia la izquierda
                path.push_back('L');
            } else {
                path.push_back('R');
            }
        }

        curr_i = prev_node_i;
        curr_j = prev_node_j;
    }

    // Como va a estar al revés (porque me estoy yendo desde B a A)
    // Le hacemos un reverse a la respuesta
    reverse(path.begin(), path.end());

    for(int i = 0; i < (int)path.size(); i++){
        cout << path[i];
    }
    cout << endl;


	return 0;
}

