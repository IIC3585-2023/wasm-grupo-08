#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono> // for timing

using namespace std;
using namespace std::chrono;

struct Task {
    int completionTime;
};

bool compare(Task t1, Task t2) {
    return t1.completionTime > t2.completionTime;
}

struct Cluster {
    int completionTime = 0;
    vector<Task> tasks;
};

struct Result {
    vector<Cluster> clusterTasks;
    int totalTime;
};

Result assignTasksToClustersH(vector<Task> tasks, int numClusters) {
    // Step 1: sort tasks in descending order of completion time
    sort(tasks.begin(), tasks.end(), compare);

    // Step 2: initialize array of completion times for each cluster
    vector<int> completionTimes(numClusters, 0);

    // Step 3: assign tasks to clusters
    vector<Cluster> clusterTasks(numClusters);
    for (Task task : tasks) {
        int minCompletionTimeIndex = min_element(completionTimes.begin(), completionTimes.end()) - completionTimes.begin();
        clusterTasks[minCompletionTimeIndex].tasks.push_back(task);
        clusterTasks[minCompletionTimeIndex].completionTime += task.completionTime;
        completionTimes[minCompletionTimeIndex] += task.completionTime;
    }

    // Step 4: return results
    int totalTime = *max_element(completionTimes.begin(), completionTimes.end());
    return { clusterTasks, totalTime };
}

int main() {
    int numTasks, numClusters;
    std::cout << "Enter the number of tasks: "<< std::endl;
    std::cin >> numTasks;
    std::cout << "Enter the number of clusters: "<< std::endl;
    std::cin >> numClusters;

    vector<Task> tasks(numTasks);
    for (int i = 0; i < numTasks; i++) {
        cout << "Enter the completion time of task " << i + 1 << ": "<< std::endl;
        cin >> tasks[i].completionTime;
    }

    // Time the assignTasksToClustersH function
    auto start = high_resolution_clock::now();
    Result result = assignTasksToClustersH(tasks, numClusters);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    // Print results
    cout << "Cluster Tasks:" << endl;
    for (int i = 0; i < numClusters; i++) {
        cout << "Cluster " << i << ": ";
        for (Task task : result.clusterTasks[i].tasks) {
            cout << task.completionTime << " ";
        }
        cout << endl;
    }
    cout << "Total Time: " << result.totalTime << endl;
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

    return 0;
}

