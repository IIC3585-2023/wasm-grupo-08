#include <math.h>
#include <cstdint>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
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
  std::sort(tasks, tasks + num_tasks);

  vector<u32> completionTimes(num_clusters, 0);
  vector<vector<u32>> clusterTasks(num_clusters);

  for (u32 i =0; i < num_tasks; i++){
    u32 taskTime = tasks[i];
    u32 minCompletionTimeIndex = std::distance(completionTimes.begin(), std::min_element(completionTimes.begin(), completionTimes.end()));
    clusterTasks[minCompletionTimeIndex].push_back(taskTime);
    completionTimes[minCompletionTimeIndex] += taskTime;
  }

//   std::cout << "Cluster tasks: " << std::endl;
//   for (const auto& cluster : clusterTasks) {
//     std::cout << "  ";
//     for (u32 taskTime : cluster) {
//         std::cout << taskTime << " ";
//     }
//     std::cout << std::endl;
//   }
  return ClusterTasks_to_string(clusterTasks);
}




int main() {
  u32 numbers[]{2, 2, 2};
  auto result = heuristic(numbers, 3, 2);
  cout << result;
}
