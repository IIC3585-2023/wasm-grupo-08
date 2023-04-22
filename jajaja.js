var factory = require("./owo.js");

const tasksArray = new Uint32Array([1, 2, 3, 4, 5]);
const t0 = Date.now();
const result = assignTasksToClustersH(tasksArray, 2);
const t1 = Date.now();
console.log(`Result: ${result}`);
console.log((t1 - t0) / 1000);
// WASM
factory()
  .then((instance) => {
    const ptr = instance._malloc(tasksArray.byteLength);
    instance.HEAPU32.set(tasksArray, ptr >> 2);
    const resultCpp = instance.ccall(
      "heuristic",
      "string",
      ["number", "number", "number"],
      [ptr, 5, 2]
    );
    instance._free(ptr);
    console.log(`Result: ${resultCpp}`);
  })
  .catch((e) => {
    console.log(e);
  });

//   const ptr = Module._malloc(tasksArray.byteLength);
//   Module.HEAPU32.set(tasksArray, ptr >> 2);
//   const resultCpp = Module.ccall(
//     "heuristic",
//     "string",
//     ["number", "number", "number"],
//     [ptr, 5, 2]
//   );
//   Module._free(ptr);
//   console.log(`Result: ${resultCpp}`);

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

  return { clusterTasks };
}
