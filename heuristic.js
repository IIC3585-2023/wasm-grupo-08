function assignTasksToClustersH(tasks, numClusters) {
  // Step 1: sort tasks in descending order of completion time
  const start = performance.now();
  tasks.sort((a, b) => b - a);

  // Step 2: initialize array of completion times for each cluster
  const completionTimes = new Array(numClusters).fill(0);

  // Step 3: assign tasks to clusters
  const clusterTasks = new Array(numClusters).fill().map(() => []);
  for (const task of tasks) {
    const minCompletionTimeIndex = completionTimes.indexOf(
      Math.min(...completionTimes)
    );
    clusterTasks[minCompletionTimeIndex].push(task);
    completionTimes[minCompletionTimeIndex] += task;
  }

  // Step 4: return results
  const totalTime = Math.max(...completionTimes);
  const end = performance.now();
  const duration = end - start;

  return { clusterTasks, totalTime, duration };
}
const tasks = [5, 3, 2, 4, 1];
const numClusters = 3;

// Assign tasks to clusters
const { clusterTasks, totalTime } = assignTasksToClustersH(tasks, numClusters);

// Print the result
console.log("Cluster assignments:", clusterTasks);
console.log("Total time:", totalTime);
