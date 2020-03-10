# Voronoi Diagrams

This project was done as an assignment for CPSC 221 at the University of British Columbia. It simulates the pointillistic effect using a mathematical construct called a Voronoi Diagram, based on points randomly selected from the given photograph. The technique we’re using to partition the image is very similar to a classic [Flood Fill](https://en.wikipedia.org/wiki/Flood_fill) algorithm, run from several points simultaneously. A center’s fill simply stops when it runs into any region of the image that has already been colored.

Following is the sample output. I drew the maple leaf using both Breath First Search and Depth First Search:
- Original image:  
![alt text](https://github.com/minhducubc97/Voronoi-diagrams/blob/master/originals/leaf.png)
- Breath First Search:  
![alt text](https://github.com/minhducubc97/Voronoi-diagrams/blob/master/images/bfssolidleaf.gif)
- Depth First Search:  
![alt text](https://github.com/minhducubc97/Voronoi-diagrams/blob/master/images/dfssolidleaf.gif)