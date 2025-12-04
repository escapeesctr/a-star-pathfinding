# A* Pathfinding Algorithm in C++

A console-based implementation of the A* pathfinding algorithm with visualization.

## Features 
- A* pathfinding algorithm implementation
- Grid-based navigation
- Obstacle avoidance
- Path cost calculation (gCost, hCost, fCost)
- Console visualization of grid and path

## Algorithm Details
- **Heuristic:** Euclidean distance
- **Node expansion:** 8-directional movement
- **Cost calculation:** gCost (distance from start) + hCost (heuristic to goal)

## Usage
1. Run the program
2. See the grid representation (# = obstacle, . = empty)
3. Algorithm finds path from (0,0) to (9,9)
4. Path coordinates displayed in console

## Code Structure
- `Node` class: Represents each grid cell
- `AStar` class: Contains the pathfinding logic
- `heuristic()`: Calculates Euclidean distance
- `findPath()`: Implements A* algorithm

## Example Output
Grid (# = obstacle, . = empty):
. . . . . . . . . .
. . . . . . . . . .
. . # # # . . . . .
. . . . . . . . . .
. . . . . . . . . .
. . . . . # # # . .
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .

Path found! Length: 11 steps
Path coordinates:
(0,0) (1,1) (2,2) (3,3) (4,4) (5,5) (6,6) (7,7) (8,8) (9,9)


## What I Learned
- A* algorithm implementation
- Object-Oriented Programming in C++
- Heuristic functions
- Grid-based problem solving
- Path reconstruction

## Future Improvements
- Graphical visualization (SFML)
- Different heuristics (Manhattan, Diagonal)
- Dynamic obstacle adding
- Real-time path updating
