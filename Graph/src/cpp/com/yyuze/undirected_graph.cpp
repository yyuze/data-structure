#include<iostream>

struct Vertex {
	char data;
};

struct Edge {
	int dest;
	Edge* next;
};

struct Graph {
	int ver_num;
	int edge_num;
	Vertex* vertex;
	Edge** adj;
};

int index(Graph* g, char data) {
	for (int i = 0; i < g->ver_num; ++i) {
		if (g->vertex[i].data == data) {
			return i;
		}
	}
	return -1;
}

Graph* get_graph(char ver_data[], char edges[][2], int ver_num, int edge_num) {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	g->ver_num = ver_num;
	g->edge_num = edge_num;
	Vertex* vertices = (Vertex*)malloc(sizeof(Vertex)*ver_num);
	for (int i = 0; i < ver_num; ++i) {
		vertices[i].data = ver_data[i];
	}
	g->vertex = vertices;
	//initiate g->adj;
	g->adj = (Edge**)malloc(sizeof(Edge*)*ver_num);
	for (int i = 0; i < ver_num; ++i) {
		g->adj[i] = nullptr;
	}
	int from;
	int to;
	for (int i = 0; i < edge_num; ++i) {
		from = index(g, edges[i][0]);
		to = index(g, edges[i][1]);
		if (g->adj[from] == nullptr) {
			g->adj[from] = (Edge*)malloc(sizeof(Edge));
			g->adj[from]->dest = to;
			g->adj[from]->next = nullptr;
		}
		else {
			Edge* temp = g->adj[from];
			g->adj[from] = (Edge*)malloc(sizeof(Edge));
			g->adj[from]->dest = to;
			g->adj[from]->next = temp;
		}
		if (g->adj[to] == nullptr) {
			g->adj[to] = (Edge*)malloc(sizeof(Edge));
			g->adj[to]->dest = from;
			g->adj[to]->next = nullptr;
		}
		else {
			Edge* temp = g->adj[to];
			g->adj[to] = (Edge*)malloc(sizeof(Edge));
			g->adj[to]->dest = from;
			g->adj[to]->next = temp;
		}
	}

	return g;
}

std::ostream& operator<<(std::ostream& os, Graph& g) {
	Edge* p;
	for (int i = 0; i < g.ver_num; ++i) {
		os << g.vertex[i].data << ":";
		p = g.adj[i];
		while (p != nullptr) {
			os << g.vertex[p->dest].data;
			p = p->next;
		}
		os << std::endl;
	}
	return os;
}

void dfs(Graph* g, int src, int* visited, int* path_to_last) {
	visited[src] = 1;
	Edge* p = g->adj[src];
	while (p != nullptr) {
		if (!visited[p->dest]) {
			path_to_last[p->dest] = src;
			dfs(g, p->dest, visited, path_to_last);
		}
		p = p->next;
	}
}

void path(Graph* g, char src, char target) {
	int from = index(g, src);
	int to = index(g, target);
	int* path_to_last = (int*)malloc(sizeof(int)*g->ver_num);
	int* visited = (int*)malloc(sizeof(int)*g->ver_num);
	for (int i = 0; i < g->ver_num; ++i) {
		visited[i] = 0;
	}
	dfs(g, from, visited, path_to_last);

	int* stack = (int*)malloc(sizeof(int)*g->ver_num);
	int top = -1;
	for (int i = to; i != from; i = path_to_last[i]) {
		stack[++top] = i;
	}
	stack[++top] = from;
	while (top != -1) {
		std::cout << g->vertex[stack[top--]].data;
		if (top != -1) {
			std::cout << " -> ";
		}
		else {
			std::cout << std::endl;
		}
	}
}

void shortest_path(Graph* g, char src, char target) {
	int* visited = (int*)malloc(sizeof(int) * g->ver_num);
	for (int i = 0; i < g->ver_num; ++i) {
		visited[i] = 0;
	}

	int* queue = (int*)malloc(sizeof(int) * g->ver_num);
	int rear = 0;
	int front = 0;
	int* path_to_last = (int*)malloc(sizeof(int)*g->ver_num);

	int from = index(g, src);
	int to = index(g, target);

	queue[rear++] = from;
	visited[from] = 1;
	int last;
	while (front != rear) {
		last = queue[front++];
		Edge* p = g->adj[last];
		while (p != nullptr) {
			if (!visited[p->dest]) {
				queue[rear++] = p->dest;
				path_to_last[p->dest] = last;
				visited[p->dest] = 1;
			}
			p = p->next;
		}
	}

	int* stack = (int*)malloc(sizeof(int)*g->ver_num);
	int top = -1;
	for (int i = to; i != from; i = path_to_last[i]) {
		stack[++top] = i;
	}
	stack[++top] = from;
	while (top != -1) {
		std::cout << g->vertex[stack[top--]].data;
		if (top != -1) {
			std::cout << " -> ";
		}
		else {
			std::cout << std::endl;
		}
	}
}

void dfs(Graph* g, int v, int* marked) {
	marked[v] = 1;
	Edge* p = g->adj[v];
	while (p != nullptr) {
		if (!marked[p->dest]) {
			dfs(g, p->dest, marked);
		}
		p = p->next;
	}
	std::cout << g->vertex[v].data << " ";

}


void get_connected_component(Graph* g) {
	int count = 0;
	int* marked = (int*)malloc(sizeof(int)*g->ver_num);
	for (int i = 0; i < g->ver_num; ++i) {
		marked[i] = 0;
	}
	for (int i = 0; i < g->ver_num; ++i) {
		if (!marked[i]) {
			dfs(g, i, marked);
			std::cout << std::endl;
			count++;
		}
	}
}

int main() {
	char data[] = { 'A','B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' };
	char edge[][2] = {
		{'A','B'},{'A','C'}, {'A','E'}, {'B','D'},
		{'C','D'}, {'C','H'}, {'E','F'},
		{'H','G'}, {'D','F'},  {'D','G'},
	};
	int ver_num = sizeof(data) / sizeof(char);
	int edge_num = sizeof(edge) / sizeof(edge[0]);
	Graph* g = get_graph(data, edge, ver_num, edge_num);

	std::cout << *g << std::endl;

	path(g, 'B', 'H');
	path(g, 'E', 'H');
	shortest_path(g, 'B', 'H');
	shortest_path(g, 'E', 'H');

	get_connected_component(g);

	system("pause");
	return 0;
}