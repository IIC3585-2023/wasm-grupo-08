#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <fstream>
#include <sstream> 
#include <numeric>
using namespace std;
#include <string>
#include <cstring>  


const int INF = numeric_limits<int>::max();

// Función auxiliar para imprimir la matriz de asignación
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int x : row) {
            cout << x << "\t";
        }
        cout << endl;
    }
}

// Función auxiliar para encontrar la asignación óptima utilizando el algoritmo de asignación húngara
vector<int> hungarianAlgorithm(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();

    // Inicialización
    vector<int> u(n + 1, 0);
    vector<int> v(m + 1, 0);
    vector<int> p(m + 1, 0);
    vector<int> way(m + 1, 0);

    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0;
        vector<int> minv(m + 1, INF);
        vector<bool> used(m + 1, false);

        // Búsqueda de una cadena aumentante
        do {
            used[j0] = true;
            int i0 = p[j0], delta = INF, j1;
            for (int j = 1; j <= m; ++j) {
                if (!used[j]) {
                    int cur = matrix[i0-1][j-1] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }
            for (int j = 0; j <= m; ++j) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);

        // Actualización de las etiquetas
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0 != 0);
    }

    // Construcción de la asignación
    vector<int> assignment(n, -1);
    for (int j = 1; j <= m; ++j) {
        if (p[j] != 0) {
            assignment[p[j]-1] = j-1;
        }
    }
    return assignment;
}

// Función principal que resuelve el problema de asignación óptima de jobs a un conjunto de clusters computacionales
vector<vector<int>> optimalJobAssignment(int n, const vector<int>& jobTimes, int m) {
    // Construcción de la matriz de tiempos
    vector<vector<int>> matrix(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = jobTimes[i];
        }
    }

    // Ejecución del algoritmo de asignación húngara
    vector<int> assignment = hungarianAlgorithm(matrix);

    // Construcción de la lista de trabajos asignados a cada cluster
    vector<vector<int>> clusters(m);
    for (int i = 0; i < n; ++i) {
        int j = assignment[i];
        if (j != -1) {
            clusters[j].push_back(i);
        }
    }

    return clusters;
}

// Ejemplo de uso
/*
int main() {
    // Apertura del archivo de entrada
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "No se pudo abrir el archivo de entrada" << endl;
        return 1;
    }

    // Lectura de los datos de entrada desde el archivo
    int n, m;
    inputFile >> n >> m;
    vector<int> jobTimes(n);
    for (int i = 0; i < n; ++i) {
        inputFile >> jobTimes[i];
    }

    // Cierre del archivo de entrada
    inputFile.close();

    // Resolución del problema y escritura de la salida a la consola
    vector<vector<int>> clusters = optimalJobAssignment(n, jobTimes, m);

    for (int j = 0; j < m; ++j) {
        cout << "Cluster " << j+1 << ": ";
        for (int i : clusters[j]) {
            cout << "T" << i+1 << " ";
        }
        cout << endl;
    }
    
    std::cout << "Hello World" << std::endl;
    return 0;
}
*/
std::vector<std::vector<int>> encontrarAsignacionOptima(int n, const std::vector<int>& jobTimes, int m) {
    // Crear una matriz de dimensiones m x n para almacenar los tiempos de ejecución de cada trabajo en cada cluster
    std::vector<std::vector<int>> tiempos(m, std::vector<int>(n, 0));
  
    // Iterar sobre todos los trabajos
    for (int i = 0; i < n; i++) {
        int minTiempo = std::numeric_limits<int>::max();
        int mejorCluster = 0;
  
        // Iterar sobre todos los clusters para encontrar el mejor cluster para el trabajo actual
        for (int j = 0; j < m; j++) {
            // Calcular el tiempo total de ejecución si se asigna el trabajo actual al cluster j
            int tiempoTotal = accumulate(tiempos[j].begin(), tiempos[j].end(), 0) + jobTimes[i];
  
            // Si el tiempo total es menor que el mínimo tiempo encontrado hasta ahora, actualizar el mínimo tiempo y el mejor cluster
            if (tiempoTotal < minTiempo) {
                minTiempo = tiempoTotal;
                mejorCluster = j;
            }
        }
  
        // Asignar el trabajo actual al mejor cluster encontrado
        tiempos[mejorCluster][i] = jobTimes[i];
    }
  
    // Devolver la asignación de trabajos a clusters
    return tiempos;
}

int main() {
    // Ejemplo de uso
    //int n = 5;
    //std::vector<int> jobTimes = {30, 50, 10, 20, 90};
    //int m = 2;
    ifstream MyReadFile("input.txt");
    int n, m;
    MyReadFile >> n >> m;
    vector<int> jobTimes(n);
    for (int i = 0; i < n; ++i) {
        MyReadFile >> jobTimes[i];
    }
    std::vector<std::vector<int>> asignacion = encontrarAsignacionOptima(n, jobTimes, m);

    // Imprimir la asignación de trabajos a clusters
    for (int j = 0; j < m; j++) {
        std::cout << "Cluster " << j << ": ";
        for (int i = 0; i < n; i++) {
            if (asignacion[j][i] > 0) {
                std::cout << "T" << i+1 << " ";
            }
        }
        std::cout << std::endl;
    }


    return 0;
}