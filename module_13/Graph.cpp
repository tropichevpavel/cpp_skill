
#include <iostream>

#define SIZE 10

struct Graph {
	int vCount = 0;
	int vArray[SIZE];
	int matrix[SIZE][SIZE];

	Graph() {
		for (int i = 0; i < SIZE; ++i) {
			for (int j = 0; j < SIZE; ++j)
				matrix[i][j] = 0;

			vArray[i] = -1;
		}
	}

	void addVertex(const int& id) {
		vArray[vCount++] = id;
	}

	void addEdge(const int& v1, const int& v2, const int& weight) {
		matrix[v1][v2] = weight;
		matrix[v2][v1] = weight;
	}

	bool vertexExists(const int& id) {
		for (int i = 0; i < vCount; ++i)
			if (vArray[i] == id)
				return true;
		return false;
	}

	bool edgeExists(const int& v1, const int& v2) {
		return matrix[v1][v2] > 0;
	}

	void delVertex(const int& id) {
		for (int i = 0; i < vCount; ++i)
			if (vArray[i] == id)
				vArray[i] = -1;
		--vCount;
		for (int i = 0; i < SIZE; ++i)
			this->delEdge(id, i);
	}

	void delEdge(const int& v1, const int& v2) {
		matrix[v1][v2] = 0;
		matrix[v2][v1] = 0;
	}

	// Реализация прохода графа в глубину

	void depth(const int& start) {
		bool visit[SIZE];
		for (int i = 0; i < SIZE; ++i)
			visit[i] = false;

		depthInner(start, visit);

		std::cout << std::endl;
	}

	void depthInner(const int& current, bool* visit) {

		std::cout << "v" << current << " -> ";
		visit[current] = true;
		for (int i = 0; i < SIZE; ++i)
			if (!visit[i] && edgeExists(current, i))
				depthInner(i, visit);
	}

	// Реализация прохода графа в ширь

	void breadth(const int& start) {
		bool visit[SIZE];
		int queue[SIZE] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
		int qCount = 0;

		for (int i = 0; i < SIZE; ++i) {
			visit[i] = false;
			queue[i] = -1;
		}

		queue[qCount++] = start;
		while (qCount > 0) {
			int current = queue[0];
			--qCount;
			
			for (int i = 0; i < qCount; ++i)
				queue[i] = queue[i + 1];

			visit[current] = true;
			std::cout << "v" << current << " -> ";

			for (int i = 0; i < SIZE; ++i) {
				bool alreadyAdded = false;
				for (int j = 0; j < qCount; ++j)
					if (queue[j] == i) {
						alreadyAdded = true;
						break;
					}

				if (!alreadyAdded && !visit[i] && edgeExists(current, i))
					queue[qCount++] = i;
			}
		}

		std::cout << std::endl;
	}

	// поиск кол-ва путей до каждой вершины

	int pathCount(const int& from, const int& to) {
		bool visit[SIZE];
		for (int i = 0; i < SIZE; ++i)
			visit[i] = false;
		int count = 0;
		pathCountInner(from, to, visit, count);
		return count;
	}

	void pathCountInner(const int& cur, const int& to, bool* visit, int& count) {
		if (cur == to) {
			count++;
			return;
		}

		visit[cur] = true;

		for (int i = 0; i < SIZE; ++i)
			if (!visit[i] && edgeExists(cur, i))
				pathCountInner(i, to, visit, count);

		visit[cur] = false;
	}

	// Поиск минимальной длины пути от выбранной вершины до всех остальных

	void findMinDists(const int& id) {
		int dists[SIZE];
		for (int i = 0; i < SIZE; ++i)
			dists[i] = -1;

		dists[id] = 0;

		bool passed[SIZE];
		for (int i = 0; i < SIZE; ++i)
			passed[i] = false;

		int cur = id;
		int last = -1;
		while (cur != last) {
			passed[last = cur] = true;

			for (int i = 0; i < SIZE; ++i)
				if (edgeExists(cur, i) && (dists[i] == -1 || dists[cur] + matrix[cur][i] < dists[i]))
					dists[i] = dists[cur] + matrix[cur][i];

			for (int i = 0; i < SIZE; ++i)
				if (vertexExists(i) && !passed[i] && dists[i] != -1) {
					cur = i;
					break;
				}
		}

		std::cout << "Dists from " << id << std::endl;
		for (int i = 0; i < SIZE; ++i)
			if (vArray[i] != -1)
				std::cout << "v" << i << " - " << dists[vArray[i]] << std::endl;

		std::cout << std::endl;
	}

	// Поиск матрицы минимальных путей

	void findMinDistsMatrix(const int& id) {
		int weights[SIZE][SIZE];
		for (int i = 0; i < SIZE; ++i)
			for (int j = 0; j < SIZE; ++j)
				if (i == j)
					weights[i][j] = 0;

				else if (edgeExists(i, j))
					weights[i][j] = matrix[i][j];

				else
					weights[i][j] = 10000000;

		for (int k = 0; k < SIZE; ++k)
			if (vArray[k] != -1) {
				int ck = vArray[k];

				for (int i = 0; i < SIZE; ++i) {
					if (vArray[i] == -1 || i == k) continue;

					int ci = vArray[i];
					for (int j = 0; j < SIZE; ++j) {
						if (vArray[j] == -1 || j == i) continue;

						int cj = vArray[j];
						if (weights[ci][ck] + weights[ck][cj] < weights[ci][cj])
							weights[ci][cj] = weights[ci][ck] + weights[ck][cj];
					}
				}
			}

		std::cout << "Dists matrix" << std::endl;
		for (int i = 0; i < SIZE; ++i)
			if (vArray[i] != -1)
				std::cout << "v" << i << " - " << weights[id][vArray[i]] << std::endl;

		std::cout << std::endl;
	}

	// поиск кол-ва путей до каждой вершины

	int pathMin(const int& from, const int& to) {
		bool visit[SIZE];
		for (int i = 0; i < SIZE; ++i)
			visit[i] = false;
		int min = 1000000;
		pathMinInner(from, to, visit, 0, min);
		return min;
	}

	void pathMinInner(const int& cur, const int& to, bool* visit, int path, int& min) {
		if (cur == to) {
			if (path < min) min = path;
			return;
		}

		visit[cur] = true;
		
		for (int i = 0; i < SIZE; ++i)
			if (!visit[i] && edgeExists(cur, i)) 
				pathMinInner(i, to, visit, path + matrix[cur][i], min);

		visit[cur] = false;
	}
};

int main() {

	// Graph g;

	// g.addVertex(0);
	// g.addVertex(1);
	// g.addVertex(2);
	// g.addVertex(3);

	// g.addEdge(0, 1, 5);
	// g.addEdge(0, 2, 4);
	// g.addEdge(0, 3, 11);
	// g.addEdge(1, 2, 8);

	// g.depth(0);
	// g.breadth(0);


	// Graph g;

	// g.addVertex(0);
	// g.addVertex(1);
	// g.addVertex(2);
	// g.addVertex(3);
	// g.addVertex(4);
	// g.addVertex(5);    
	// g.addVertex(6);
	// g.addVertex(7);
	// g.addVertex(8);

	// g.addEdge(0, 1, 1);
	// g.addEdge(0, 2, 1);
	// g.addEdge(0, 3, 1);
	// g.addEdge(2, 5, 1);
	// g.addEdge(1, 4, 1);
	// g.addEdge(4, 3, 1);
	// g.addEdge(5, 3, 1);
	// g.addEdge(4, 7, 1);
	// g.addEdge(3, 6, 1);
	// g.addEdge(3, 7, 1);
	// g.addEdge(3, 8, 1);
	// g.addEdge(5, 8, 1);
	// g.addEdge(8, 6, 1);
	// g.addEdge(7, 6, 1);

	// g.depth(0);
	// g.breadth(0);

	// std::cout << std::endl;
	// std::cout << g.pathCount(0, 6);

	// Graph g;

	// g.addVertex(0);
	// g.addVertex(1);
	// g.addVertex(2);
	// g.addVertex(3);
	// g.addVertex(4);
	// g.addVertex(5);

	// g.addEdge(0, 2, 13);
	// g.addEdge(0, 4, 21);
	// g.addEdge(0, 5, 27);
	// g.addEdge(2, 3, 82);
	// g.addEdge(2, 4, 77);
	// g.addEdge(4, 1, 43);
	// g.addEdge(4, 5, 11);
	// g.addEdge(5, 1, 38);

	// g.findMinDists(0);

	Graph g;
    
    g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);
    
    g.addEdge(0, 2, 13);
    g.addEdge(0, 4, 21);
    g.addEdge(0, 5, 27);
    g.addEdge(2, 3, 82);
    g.addEdge(2, 4, 77);
    g.addEdge(4, 1, 43);
    g.addEdge(4, 5, 11);
    g.addEdge(5, 1, 38); 
    
    g.findMinDistsMatrix(0);
	std::cout << g.pathMin(0, 1);

	return 0;
}