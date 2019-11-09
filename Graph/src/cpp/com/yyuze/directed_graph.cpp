#include<iostream>

struct Vertex {
	char data;
};

struct Edge {
	int dest;
	Edge* next;
};

struct Digraph {
	Vertex* vertex;
	Edge** adj;
	int ver_num;
	int edge_num;
};

int index(Digraph* g, char ver_data) {
	for (int i = 0; i < g->ver_num; ++i) {
		if (g->vertex[i].data == ver_data) {
			return i;
		}
	}
	return -1;
}

Digraph* get_digraph(char vertex_data[], char edges[][2], int ver_num, int edge_num) {
	Digraph* g = (Digraph*)malloc(sizeof(Digraph));
	g->vertex = (Vertex*)malloc(sizeof(Vertex)*ver_num);
	g->adj = (Edge**)malloc(sizeof(Edge*)*ver_num);
	g->ver_num = ver_num;
	g->edge_num = edge_num;

	for (int i = 0; i < ver_num; ++i) {
		g->vertex[i].data = vertex_data[i];
		g->adj[i] = nullptr;
	}

	for (int i = 0; i < edge_num; ++i) {
		int from = index(g, edges[i][0]);
		int to = index(g, edges[i][1]);
		Edge* temp = g->adj[from];
		Edge* e = (Edge*)malloc(sizeof(Edge));
		e->dest = to;
		g->adj[from] = e;
		e->next = temp;
	}
	return g;
}

std::ostream& operator<<(std::ostream& os, Digraph* g) {
	for (int i = 0; i < g->ver_num; ++i) {
		os << g->vertex[i].data << ": ";
		Edge* p = g->adj[i];
		while (p != nullptr) {
			os << g->vertex[p->dest].data;
			p = p->next;
		}
		os << std::endl;
	}
	return os;
}

void dfs(Digraph* g, int vertex_index, int* marked, int* stack, int* top) {
	marked[vertex_index] = 1;
	Edge* p = g->adj[vertex_index];
	while (p != nullptr) {
		if (!marked[p->dest]) {
			dfs(g, p->dest, marked, stack, top);
		}
		p = p->next;
	}
	stack[++*top] = vertex_index;
}

int* get_topologic_order(Digraph* g) {
	int* queue = (int*)malloc(sizeof(int)*g->ver_num);
	int top = -1;
	int* marked = (int*)malloc(sizeof(int)*g->ver_num);
	for (int i = 0; i < g->ver_num; ++i) {
		marked[i] = 0;
	}
	for (int i = 0; i < g->ver_num; ++i) {
		if (!marked[i]) {
			dfs(g, i, marked, queue, &top);
		}
	}
	//reverse
	for (int i = 0; i <= top/2; ++i) {
		int temp = queue[i];
		queue[i] = queue[top - i];
		queue[top - i] = temp;
	}
	return queue;
}

void dfs(Digraph* g, int vertex_index, int* marked) {
	marked[vertex_index] = 1;
	std::cout << g->vertex[vertex_index].data << " ";
	Edge* p = g->adj[vertex_index];
	while (p != nullptr) {
		if (!marked[p->dest]) {
			dfs(g, p->dest, marked);
		}
		p = p->next;
	}
}

Digraph* get_reverse_digraph(Digraph* g) {
	Digraph* g_t = (Digraph*)malloc(sizeof(Digraph));
	g_t->vertex = (Vertex*)malloc(sizeof(Vertex)*g->ver_num);
	g_t->adj = (Edge**)malloc(sizeof(Edge*)*g->ver_num);
	g_t->ver_num = g->ver_num;
	g_t->edge_num = g->edge_num;

	for (int i = 0; i < g_t->ver_num; ++i) {
		g_t->adj[i] = nullptr;
		g_t->vertex[i].data = g->vertex[i].data;
	}

	for (int i = 0; i < g->ver_num; ++i) {
		Edge* p = g->adj[i];
		while (p != nullptr) {
			Edge* e = (Edge*)malloc(sizeof(Edge));
			e->dest = i;
			e->next = nullptr;
			Edge* temp = g_t->adj[p->dest];
			g_t->adj[p->dest] = e;
			e->next = temp;
			p = p->next;
		}
	}
	return g_t;
}


//Kosoraju algorithm
void get_strongly_connected_component(Digraph* g) {
	int* dfs_order = get_topologic_order(get_reverse_digraph(g));
	int* marked = (int*)malloc(sizeof(int)*g->ver_num);
	int scc_count = 0;
	for (int i = 0; i < g->ver_num; ++i) {
		marked[i] = 0;
	}
	for (int i = 0; i < g->ver_num; ++i) {
		if (!marked[dfs_order[i]]) {
			std::cout << scc_count << ": ";
			dfs(g, dfs_order[i], marked);
			std::cout << std::endl;
			scc_count++;
		}
	}
}



int main() {
	char data[] = { 'A','B','C','D','E','F','G','H','I' };
	char edge[][2] = { 
		{'A','B'},{'B','C'},
		{'H','E'},{'E','D'},{'D','A'},
		{'F','C'},{'F','G'},{'H','G'},
		{'B','E'},{'D','B'},{'H','I'},
		{'I','H'},{'I','A'}
	};
	int ver_num = sizeof(data) / sizeof(char);
	int edge_num = sizeof(edge) / sizeof(char[2]);
	Digraph* g = get_digraph(data, edge, ver_num, edge_num);
	std::cout << g << std::endl;
	get_strongly_connected_component(g);
	

	system("pause");
	return 0;
}