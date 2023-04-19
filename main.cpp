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

std::vector<std::vector<int>> encontrarAsignacionOptima(int n, const std::vector<int>& jobTimes, int m) {
    // Crear una matriz de dimensiones m x n para almacenar los tiempos de ejecución de cada trabajo en cada cluster
    std::vector<std::vector<int>> tiempos(m, std::vector<int>(n, -1));
  
    // Iterar sobre todos los trabajos
    for (int i = 0; i < n; i++) {
        int minTiempo = std::numeric_limits<int>::max();
        int mejorCluster = 0;
  
        // Iterar sobre todos los clusters para encontrar el mejor cluster para el trabajo actual
        for (int j = 0; j < m; j++) {
            // Calcular el tiempo total de ejecución si se asigna el trabajo actual al cluster j
//          int tiempoTotal = accumulate(tiempos[j].begin(), tiempos[j].end(), 0) + jobTimes[i];
            int tiempoTotal = 0; 
            for (int i = 0; i < n; i++) {
                if (tiempos[j][i] != -1) {
                    tiempoTotal += tiempos[j][i];
                } 
            }
            tiempoTotal += jobTimes[i];
  
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