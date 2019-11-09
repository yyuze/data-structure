#include<iostream>

struct Vertex {
	char data;
};

struct Edge {
	int src;
	int dest;
	double weight;
	Edge* next;
};

bool operator<(Edge& e1, Edge& e2) {
	return e1.weight < e2.weight;
}

bool operator>(Edge& e1, Edge& e2) {
	return e1.weight > e2.weight;
}

struct Graph {
	Vertex* vertex;
	Edge** adj;
	int ver_num;
	int edge_num;
};

struct PQ {
	Edge** buf;
	int size;
};

std::ostream& operator<<(std::ostream& os, Graph* g) {
	for (int i = 0; i < g->ver_num; ++i) {
		os << g->vertex[i].data << " : ";
		Edge* index = g->adj[i];
		while (index != nullptr) {
			os << "(" << g->vertex[index->dest].data << "," << index->weight << ") ";
			index = index->next;
		}
		os << std::endl;
	}
	return os;
}

int index_of(char data, Graph* g) {
	for (int i = 0; i < g->ver_num; ++i) {
		if (g->vertex[i].data == data) {
			return i;
		}
	}
	return -1;
}

Graph* init_graph(char data[], char edge[][2], double weights[], int ver_num, int edge_num) {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	g->vertex = (Vertex*)malloc(sizeof(Vertex) * ver_num);
	g->ver_num = ver_num;
	g->adj = (Edge**)malloc(sizeof(Edge*) * ver_num);
	g->edge_num = edge_num;
	for (int i = 0; i < ver_num; ++i) {
		g->vertex[i].data = data[i];
		g->adj[i] = nullptr;
	}
	for (int i = 0; i < edge_num; ++i) {
		int src = index_of(edge[i][0], g);
		int dest = index_of(edge[i][1], g);
		Edge* e = (Edge*)malloc(sizeof(Edge));
		e->src = src;
		e->dest = dest;
		e->weight = weights[i];
		Edge* temp = g->adj[src];
		g->adj[src] = e;
		e->next = temp;
	}
	return g;
}

PQ* init_pq(int capacity) {
	PQ* pq = (PQ*)malloc(sizeof(PQ));
	pq->buf = (Edge**)malloc(sizeof(Edge*) * capacity + 1);
	for (int i = 0; i > capacity + 1; ++i) {
		pq->buf[i] = nullptr;
	}
	pq->size = 0;
	return pq;
}

void enqueue(PQ* pq, Edge* e) {
	pq->buf[++pq->size] = e;
	int pos = pq->size;
	while (pos/2 >= 1) {
		int cmp = pos / 2;
		if (pq->buf[cmp] < pq->buf[pos]) {
			break;
		}
		else {
			Edge* temp = pq->buf[cmp];
			pq->buf[cmp] = pq->buf[pos];
			pq->buf[pos] = temp;
			pos = cmp;
		}
	}
}

Edge* dequeue(PQ* pq) {
	Edge* r = pq->buf[1];
	pq->buf[1] = pq->buf[pq->size];
	pq->buf[pq->size] = nullptr;
	pq->size--;
	int pos = 1;
	while (pos * 2 <= pq->size) {
		int cmp = pos * 2;
		if (cmp + 1 <= pq->size) {
			if (pq->buf[cmp] > pq->buf[cmp + 1]) {
				cmp += 1;
			}
		}
		if (pq->buf[pos] < pq->buf[cmp]) {
			break;
		}
		else {
			Edge* temp = pq->buf[cmp];
			pq->buf[cmp] = pq->buf[pos];
			pq->buf[pos] = temp;
			pos *= 2;
		}
	}
	return r;
}

void pirnt_SPT(Graph* g, int src, double* dist_to, Edge** edge_to) {
	for (int i = 0; i < g->ver_num; ++i) {
		if (i == src) {
			continue;
		}
		Edge** stack = (Edge**)malloc(sizeof(Edge*) * (g->ver_num - 1));
		int top = -1;
		for (Edge* e = edge_to[i]; e != nullptr; e = edge_to[e->src]) {
			stack[++top] = e;
		}
		std::cout << "to " << g->vertex[i].data << ": ";
		if (top != -1) {
			std::cout << g->vertex[src].data;
			while (top != -1) {
				Edge* e = stack[top--];
				std::cout << "->" << g->vertex[e->dest].data;
				std::cout << "(" << e->weight << ")";
			}
		}
		std::cout << std::endl;
	}
}

void get_SPT_Dijkstra(Graph* g, int src) {
	double* dist_to = (double*)malloc(sizeof(double) * g->ver_num);
	for (int i = 0; i < g->ver_num; ++i) {
		dist_to[i] = INFINITY;
	}
	Edge** edge_to = (Edge**)malloc(sizeof(Edge*) * g->ver_num);
	for (int i = 0; i < g->ver_num; ++i) {
		edge_to[i] = nullptr;
	}
	PQ* pq = init_pq(g->edge_num);
	Edge* p = g->adj[src];
	dist_to[src] = 0;
	while (p != nullptr) {
		enqueue(pq, p);
		p = p->next;
	}
	while (pq->size != 0) {
		Edge* e = dequeue(pq);
		int src = e->src;
		int dest = e->dest;
		double cost = e->weight;
		if (dist_to[dest] > dist_to[src] + cost) {
			edge_to[dest] = e;
			dist_to[dest] = dist_to[src] + cost;
			p = g->adj[dest];
			while (p != nullptr) {
				enqueue(pq, p);
				p = p->next;
			}
		}
	}
	pirnt_SPT(g, src, dist_to, edge_to);
}

void dfs(Graph* g, int src, Edge** edge_to, double* dist_to) {
	Edge* p = g->adj[src];
	while (p != nullptr) {
		if (dist_to[p->dest] > dist_to[p->src] + p->weight) {
			dist_to[p->dest] = dist_to[p->src] + p->weight;
			edge_to[p->dest] = p;
		}
		dfs(g, p->dest, edge_to, dist_to);
		p = p->next;
	}
}

void get_SPT_dfs(Graph* g, int src) {
	Edge** edge_to = (Edge**)malloc(sizeof(Edge*) * g->ver_num);
	double* dist_to = (double*)malloc(sizeof(double) * g->ver_num);
	for (int i = 0; i < g->ver_num; ++i) {
		edge_to[i] = nullptr;
		dist_to[i] = INFINITY;
	}
	dist_to[src] = 0;
	dfs(g, src, edge_to, dist_to);
	pirnt_SPT(g, src, dist_to, edge_to);
}

void get_SPT_bfs(Graph* g, int src) {
	Edge** edge_to = (Edge**)malloc(sizeof(Edge) * g->ver_num);
	double* dist_to = (double*)malloc(sizeof(double) * g->ver_num);
	for(int i = 0; i < g->ver_num; ++i){
		edge_to[i] = nullptr;
		dist_to[i] = INFINITY;
	}
	Edge** q = (Edge**)malloc(sizeof(Edge*) * g->edge_num);
	int front = 0;
	int rear = 0;

	Edge* p = g->adj[src];
	dist_to[src] = 0;
	while (p != nullptr) {
		q[rear++] = p;
		p = p->next;
	}
	while (front != rear) {
		Edge* e = q[front++];
		p = g->adj[e->dest];
		while (p != nullptr) {
			q[rear++] = p;
			p = p->next;
		}
		if (dist_to[e->dest] > dist_to[e->src] + e->weight) {
			dist_to[e->dest] = dist_to[e->src] + e->weight;
			edge_to[e->dest] = e;
		}
	}
	pirnt_SPT(g, src, dist_to, edge_to);
}

int main() {
	char data[] = { 'A','B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' };
	char edge[][2] = {
		{'A','C'},{'C','H'} ,{'A','B'} ,{'D','C'},
		{'B','D'},{'G','D'},{'A','E'},
		{'F','E'},{'D','F'},{'E','I'},{'F','I'}
	};
	double weights[] = { 7.1, 2, 3, 2.5, 1.5, 4, 2.3, 4.6, 5.5, 8, 10 };
	int ver_num = sizeof(data) / sizeof(char);
	int edge_num = sizeof(edge) / sizeof(char[2]);

	Graph* g = init_graph(data, edge, weights, ver_num, edge_num);
	std::cout << g << std::endl;

	get_SPT_Dijkstra(g, index_of('G', g));
	std::cout << std::endl;

	get_SPT_dfs(g, index_of('G', g));
	std::cout << std::endl;

	get_SPT_bfs(g, index_of('G', g));
	std::cout << std::endl;

	system("pause");
	return 0;
}