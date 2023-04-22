#include <math.h>
#include <cstdint>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <numeric>
using std::vector;
using std::cout;
using std::string;
typedef uint32_t u32;

bool compare(u32 t1, u32 t2) {
    return t1 > t2;
}

extern "C" char* ClusterTasks_to_char(vector<vector<u32>> clusterTasks) {
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

  char* charArr = new char[result.size() + 1];
  std::copy(result.begin(), result.end(), charArr);
  charArr[result.size()] = '\0';
  return charArr;
}

extern "C" char* heuristic(u32 *tasks, u32 num_tasks, u32 num_clusters) {
  std::sort(tasks, tasks + num_tasks, std::greater<u32>());

  vector<u32> completionTimes(num_clusters, 0);
  vector<vector<u32>> clusterTasks(num_clusters);

  for (u32 i =0; i < num_tasks; i++){
    u32 taskTime = tasks[i];
    u32 minCompletionTimeIndex = std::distance(completionTimes.begin(), std::min_element(completionTimes.begin(), completionTimes.end()));
    clusterTasks[minCompletionTimeIndex].push_back(taskTime);
    completionTimes[minCompletionTimeIndex] += taskTime;
  }
  return ClusterTasks_to_char(clusterTasks);
}
