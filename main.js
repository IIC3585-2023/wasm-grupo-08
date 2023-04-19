import { readFileSync, writeFile } from 'fs';


// Función para encontrar la asignación óptima de trabajos a clusters
function encontrarAsignacionOptima(n, jobTimes, m) {
    // Crear una matriz de dimensiones m x n para almacenar los tiempos de ejecución de cada trabajo en cada cluster
    const tiempos = Array.from({ length: m }, () => Array(n).fill(0));
  
    // Iterar sobre todos los trabajos
    for (let i = 0; i < n; i++) {
      let minTiempo = Infinity;
      let mejorCluster = 0;
  
      // Iterar sobre todos los clusters para encontrar el mejor cluster para el trabajo actual
      for (let j = 0; j < m; j++) {
        // Calcular el tiempo total de ejecución si se asigna el trabajo actual al cluster j
        let tiempoTotal = tiempos[j].reduce((acumulador, tiempo) => acumulador + tiempo, 0) + jobTimes[i];
  
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
  
 //const response( )

  // Ejemplo de uso

  //Reading file input.txt
  const content = readFileSync("input.txt", {encoding:'utf8', flag:'r'});
  const contentAsList = content.split(" ");
  const n = Number(contentAsList[0]); //tareas
  const m = Number(contentAsList[1]); //workers
  const jobTimes = contentAsList.slice(2).map(Number);
  
  const asignacionOptima = encontrarAsignacionOptima(n, jobTimes, m);
  for (let j = 0; j < asignacionOptima.length; j++) {
    let counter = 0;
    let cluster = "Cluster " + (j+1) + ": ";
    for (let i = 0; i < asignacionOptima[j].length; i++) {
        if (asignacionOptima[j][i]==0){continue;}
        let tarea=  "T" + (i+1) + " ";
        counter+= asignacionOptima[j][i];
        cluster+= tarea;
    }
    console.log(cluster);
}