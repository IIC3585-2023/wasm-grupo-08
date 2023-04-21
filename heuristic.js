function assignTasksToClustersH(tasks, numClusters) {
  // Step 1: sort tasks in descending order of completion time
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
  return { clusterTasks, totalTime };
}

const tasks = [30, 50, 10, 20, 90];
const numClusters = 2;

// Assign tasks to clusters
const { clusterTasks, totalTime } = assignTasksToClustersH(tasks, numClusters);

// Print the result
console.log("Cluster assignments:", clusterTasks);
console.log("Total time:", totalTime);
