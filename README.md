# Welcome to My Mouse
***

## Task
The task is to implement a pathfinding algortihm and print a path given a map.

## Description
We read the map from the file and convert map to bit map (1, 0) to find the path\
and print it to the stdout. To find shortest path in bit map we use\
BFS(Breadth-First Search), which is a graph traversal algorithm that explores\
all cell of converted bit map. The algorithm starts at a given vertex, marks\
it as visited, and adds it to a queue. Then, it visits all the adjacent vertices\of the current vertex that have not been visited yet and marks them as visited,\
and adds them to the queue. The algorithm repeats this process until it reachs\
the target.
After target was determined, program startes going upward by cells that was\
marked as visited until program reachs source. When we completed collecting\
coordinates of path we give it print.

## Installation
Get a copy, run make in the root folder, run scripts to generate maps.

## Usage
Give a file with a map in it as the argument to the executable.
```
./my_mouse map.txt
```

### The Core Team
Timur Timak,\
Akbar Usmonov

<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px'></span>



 git remote add origin https://github.com/akbarjonUsmonov/My_mouse.git
 git branch -M main
 git push -u origin mainecho "# My_mouse" >> README.md
 git init
 git add README.md
 git commit -m "first commit"
 git branch -M main
 git remote add origin https://github.com/akbarjonUsmonov/My_mouse.git