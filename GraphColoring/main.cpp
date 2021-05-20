#include <iostream>
#include <vector>
#define NOT_COLORED -1
#define BASIC 0
#define LF 1

// Struct, that describes single vertex
struct Vertex {
	int id;
	int degree;
	int color;
	std::vector<int> neighbours;
};

// Filling bool array with given value
void fillBoolArray(bool* arr, int size, bool value) {
	for (size_t i = 0; i < size; i++) {
		arr[i] = value;
	}
}

// Sorting graph by degree of vertices (or id)
void sortGraphByDegree(std::vector<Vertex*>& graph) {
	for (size_t i = 0; i < graph.size() - 1; i++) {
		for (size_t j = 0; j < graph.size() - i - 1; j++) {
			if (graph[j + 1]->degree > graph[j]->degree) {
				std::swap(graph[j], graph[j + 1]);
			}
			else if (graph[j + 1]->degree == graph[j]->degree &&
				graph[j + 1]->id < graph[j]->id) {
				std::swap(graph[j], graph[j + 1]);
			}
		}
	}
}

// Sorting graph by id
void sortGraphByID(std::vector<Vertex*>& graph) {
	for (size_t i = 0; i < graph.size() - 1; i++)
	{
		for (size_t j = 0; j < graph.size() - i - 1; j++)
		{
			if (graph[j + 1]->id < graph[j]->id) {
				std::swap(graph[j], graph[j + 1]);
			}
		}
	}
}

// Returns an index of given vertex in graph vector.
int findIndexOfVertex(const std::vector<Vertex*>& graph, int id) {
	for (size_t i = 0; i < graph.size(); i++) {
		if (graph[i]->id == id) return i;
	}
	return 0;
}

// Coloring graph with basic method
int colorGraph(std::vector<Vertex*>& graph) {
	// Bool array, that shows if colors is available
	bool* colorsCheck = new bool[graph.size()];
	fillBoolArray(colorsCheck, graph.size(), true);

	int nColors = 1;
	int highestColor = 0;

	// Coloring first vertex
	graph[0]->color = 0;

	for (size_t i = 1; i < graph.size(); i++) {
		// Checking colors of adjacent vertices
		for (size_t j = 0; j < graph[i]->neighbours.size(); j++) {
			int neighbourID = graph[i]->neighbours[j];
			int neighbourIndex = findIndexOfVertex(graph, neighbourID);
			if (graph[neighbourIndex]->color != NOT_COLORED) {
				colorsCheck[graph[neighbourIndex]->color] = false;
			}
		}
		// Looking for first available color
		for (size_t j = 0; j < graph.size(); j++) {
			if (colorsCheck[j]) {
				graph[i]->color = j;
				if (j > highestColor) {
					nColors++;
					highestColor = j;
				}
				break;
			}
		}
		fillBoolArray(colorsCheck, graph.size(), true);
	}

	delete[] colorsCheck;
	return nColors;
}

// Coloring using LF algorithm
int colorGraphByDegree(std::vector<Vertex*>& graph) {
	sortGraphByDegree(graph);
	int nColors = colorGraph(graph);
	return nColors;
}

// Printing vertices' id and color
void printColors(std::vector<Vertex*>& graph) {
	sortGraphByID(graph);
	for (size_t i = 0; i < graph.size(); i++) {
		std::cout << graph[i]->id << " - " << graph[i]->color << std::endl;
	}
}

int main() {
	int nVertices, mode;
	std::cin >> mode;
	std::cin >> nVertices;
	std::vector<Vertex*> graph;

	// Creating new vertices
	for (size_t i = 0; i < nVertices; i++)
	{
		int degree;
		std::cin >> degree;

		// Creating single vertex
		Vertex* vertex = new Vertex();
		vertex->id = i;
		vertex->degree = degree;
		vertex->color = NOT_COLORED;

		// Parsing adjacent vertices
		for (size_t j = 0; j < degree; j++)
		{
			int neighbour;
			std::cin >> neighbour;
			vertex->neighbours.push_back(neighbour);
		}

		// Adding vertex to the graph
		graph.push_back(vertex);
	}

	std::cout << std::endl;
	int output;

	// Choosing mode
	switch (mode) {
	case BASIC:
		output = colorGraph(graph);
		break;
	case LF:
		output = colorGraphByDegree(graph);
		break;
	default:
		output = colorGraph(graph);
		break;
	}

	std::cout << "hehe" << std::endl;

	// Output
	std::cout << output << std::endl;
	printColors(graph);

	graph.clear();
	return 0;
}