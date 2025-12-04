#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

class Node {
public:
	int x, y;
	bool obstacle;
	bool visited;
	float gCost;
	float hCost;
	Node* parent;

	Node(int x, int y) : x(x), y(y), obstacle(false), visited(false),
		gCost(INFINITY), hCost(0), parent(nullptr) {
	}

	float fCost() const { return gCost + hCost; }
};

class AStar {
private:
	std::vector<std::vector<Node>> grid;
	int width, height;

	float heuristic(Node* a, Node* b) {

		return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2));
	}
public:
	AStar(int w, int h) : width(w), height(h) {
		for (int y = 0; y < height; y++) {
			std::vector<Node> row;
			for (int x = 0; x < width; x++) {
				row.push_back(Node(x, y));
			}
			grid.push_back(row);
		}
	}

	void setObstacle(int x, int y) {
		if (x >= 0 && x < width && y >= 0 && y < height) {
			grid[y][x].obstacle = true;
		}
	}

	std::vector<Node*> findPath(int startX, int startY, int endX, int endY) {

		for (auto& row : grid) {
			for (auto& node : row) {
				node.visited = false;
				node.gCost = INFINITY;
				node.parent = nullptr;
			}
		}

		Node* start = &grid[startY][startX];
		Node* end = &grid[endY][endX];

		std::vector<Node*> openSet;
		start->gCost = 0;
		start->hCost = heuristic(start, end);
		openSet.push_back(start);

		while (!openSet.empty()) {

			Node* current = openSet[0];
			int currentIndex = 0;
			for (int i = 1; i < openSet.size(); i++) {
				if (openSet[i]->fCost() < current->fCost()) {
					current = openSet[i];
					currentIndex = i;
				}
			}

			if (current == end) {
				std::vector<Node*> path;
				while (current != nullptr) {
					path.push_back(current);
					current = current->parent;
				}
				std::reverse(path.begin(), path.end());
				return path;
			}

			openSet.erase(openSet.begin() + currentIndex);
			current->visited = true;

			for (int dy = -1; dy <= 1; dy++) {
				for (int dx = -1; dx <= 1; dx++) {
					if (dx == 0 && dy == 0) continue;

					int nx = current->x + dx;
					int ny = current->y + dy;

					if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
						Node* neighbor = &grid[ny][nx];

						if (neighbor->obstacle || neighbor->visited) continue;

						float newGCost = current->gCost + heuristic(current, neighbor);

						if (newGCost < neighbor->gCost) {
							neighbor->gCost = newGCost;
							neighbor->hCost = heuristic(neighbor, end);
							neighbor->parent = current;

							bool inOpenSet = false;
							for (auto node : openSet) {
								if (node == neighbor) {
									inOpenSet = true;
									break;
								}
							}
							if (!inOpenSet) {
								openSet.push_back(neighbor);
							}
						}
					}
				}
			}
		}

		return {};
	}

	void printGrid() {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				if (grid[y][x].obstacle) std::cout << "# ";
				else std::cout << ". ";
			}
			std::cout << std::endl;
		}
	}
};

int main() {
	std::cout << "=== A* PATHFINDING VISULIZER ===\n";

	AStar astar(10, 10);

	astar.setObstacle(2, 2);
	astar.setObstacle(3, 2);
	astar.setObstacle(4, 2);
	astar.setObstacle(5, 5);
	astar.setObstacle(6, 5);
	astar.setObstacle(7, 5);

	std::cout << "\nGrid (# = obstacle, . = empty):\n";
	astar.printGrid();

	std::cout << "\nFinding path from (0,0) to (9,9)...\n";
	auto path = astar.findPath(0, 0, 9, 9);

	if (!path.empty()) {
		std::cout << "Path found! Length: " << path.size() << " steps\n";
		std::cout << "Path coordinates:\n";
		for (auto node : path) {
			std::cout << "(" << node->x << "," << node->y << ") ";
		}
		std::cout << std::endl;
	}
	else {
		std::cout << "No path found!\n";
	}

	return 0;

}