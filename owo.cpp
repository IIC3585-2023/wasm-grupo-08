#include <math.h>
#include <cstdint>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <numeric>
#include <fstream>

using std::vector;
using std::cout;
using std::string;
typedef uint32_t u32;

bool compare(u32 t1, u32 t2) {
    return t1 > t2;
}

string ClusterTasks_to_string(vector<vector<u32>> clusterTasks) {
  string result = "[";
  for (const auto& vec : clusterTasks) {
    result += "[";
    for (const auto& elem : vec) {
      result += std::to_string(elem) + ",";
    }
    result.pop_back();  // remove the last comma
    result += "],";
  }
  result.pop_back();  // remove the last comma
  result += "]";
  return result;
}
extern "C" string heuristic(u32 *tasks, u32 num_tasks, u32 num_clusters) {
  std::sort(tasks, tasks + num_tasks, std::greater<u32>());

  vector<u32> completionTimes(num_clusters, 0);
  vector<vector<u32>> clusterTasks(num_clusters);

  for (u32 i =0; i < num_tasks; i++){
    u32 taskTime = tasks[i];
    u32 minCompletionTimeIndex = std::distance(completionTimes.begin(), std::min_element(completionTimes.begin(), completionTimes.end()));
    clusterTasks[minCompletionTimeIndex].push_back(taskTime);
    completionTimes[minCompletionTimeIndex] += taskTime;
  }
  return ClusterTasks_to_string(clusterTasks);
}

extern "C" string encontrarAsignacionOptima(u32 *tasks, u32 num_tasks, u32 num_clusters) {
    // Crear una matriz de dimensiones m x n para almacenar los tiempos de ejecución de cada trabajo en cada cluster
    vector<vector<u32>> tiempos(num_clusters, vector<u32>(num_tasks, 0));

    // Iterar sobre todos los trabajos
    for (int i = 0; i < num_tasks; i++) {
        int minTiempo = std::numeric_limits<u32>::max();
        int mejorCluster = 0;

        // Iterar sobre todos los clusters para encontrar el mejor cluster para el trabajo actual
        for (int j = 0; j < num_clusters; j++) {
            // Calcular el tiempo total de ejecución si se asigna el trabajo actual al cluster j
            int tiempoTotal = std::accumulate(tiempos[j].begin(), tiempos[j].end(), 0) + tasks[i];

            // Si el tiempo total es menor que el mínimo tiempo encontrado hasta ahora, actualizar el mínimo tiempo y el mejor cluster
            if (tiempoTotal < minTiempo) {
                minTiempo = tiempoTotal;
                mejorCluster = j;
            }
        }

        // Asignar el trabajo actual al mejor cluster encontrado
        tiempos[mejorCluster][i] = tasks[i];
    }

    // Devolver la asignación de trabajos a clusters
    return ClusterTasks_to_string(tiempos);
}

extern "C" std::string Addx(int a, int b){
  return "string";
}
extern "C" int main() {

  u32 numbers[]{30, 50, 10, 20, 90};

  int numTasks=5;
  int numClusters=2;

  /*
  std::cout << "Enter the number of tasks: "<< std::endl;
  std::cin >> numTasks;
  std::cout << "Enter the number of clusters: "<< std::endl;
  std::cin >> numClusters;

  std::string xd;
  std::cin >> xd;
  std::cout << xd<< std::endl;
*/
  auto result = heuristic(numbers, numTasks,numClusters);
  auto result1 = encontrarAsignacionOptima(numbers, numTasks,numClusters);
  cout << result << "\n";
  cout << result1 << "\n";
  return 0;
}
