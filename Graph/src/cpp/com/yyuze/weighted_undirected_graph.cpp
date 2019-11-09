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

bool operator<(Edge& e1, Edge& e2){
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
	Edge** e;
	int size;
};

PQ* init_queue(int capacity) {
	PQ* r = (PQ*)malloc(sizeof(PQ));
	r->e = (Edge**)malloc(sizeof(Edge*)*(capacity + 1));
	for (int i = 0; i < capacity + 1; ++i) {
		r->e[i] = nullptr;
	}
	r->size = 0;
	return r;
}

void enqueue(PQ* pq, Edge* e) {
	pq->e[++pq->size] = e;
	int pos = pq->size;
	while (pos / 2 >= 1) {
		int cmp = pos / 2;
		if (*pq->e[pos] > *pq->e[cmp]) {
			break;
		}
		Edge* temp = pq->e[cmp];
		pq->e[cmp] = pq->e[pos];
		pq->e[pos] = temp;
		pos = cmp;
	}
}

Edge* dequeue(PQ* pq) {
	Edge* r = pq->e[1];
	pq->e[1] = pq->e[pq->size];
	pq->e[pq->size--] = nullptr;
	int pos = 1;
	while (pos * 2 <= pq->size) {
		int sc = pos * 2;
		if (sc + 1 <= pq->size) {
			if (*pq->e[sc] > *pq->e[sc + 1]) {
				sc += 1;
			}
		}
		if (*pq->e[pos] < *pq->e[sc]) {
			break;
		}
		Edge* temp = pq->e[sc];
		pq->e[sc] = pq->e[pos];
		pq->e[pos] = temp;
		pos = sc;
	}
	return r;
}

bool is_pq_empty(PQ* q) {
	return q->size == 0;
}

double get_weight_sum(Edge** mst, int ver_num) {
	double sum = 0;
	for (int i = 0; i < ver_num - 1; ++i) {
		sum += mst[i]->weight;
	}
	return sum;
}

Graph* get_MST_lazy_Prim(Graph* g) {
	

	int enqueue_count = 0;
	int dequeue_count = 0;

	int* marked = (int*)malloc(sizeof(g->ver_num));
	Edge** result = (Edge**)malloc(sizeof(Edge*) * (g->ver_num - 1));
	int count = 0;
	for (int i = 0; i < g->ver_num; ++i) {
		marked[i] = 0;
	}

	PQ* q = init_queue(g->edge_num);
	Edge* p = g->adj[0];
	while (p != nullptr) {
		enqueue(q, p);
		p = p->next;

		enqueue_count++;

	}
	marked[0] = 1;
	while (!is_pq_empty(q)) {
		Edge* e = dequeue(q);

		dequeue_count++;

		if (marked[e->src] && marked[e->dest]) {
			continue;
		}
		result[count++] = e;
		marked[e->dest] = 1;
		p = g->adj[e->dest];
		while (p != nullptr) {
			if (!marked[p->dest]) {
				enqueue(q, p);

				enqueue_count++;

			}
			p = p->next;
		}
	}

	Graph* mst = (Graph*)malloc(sizeof(Graph));
	mst->vertex = g->vertex;
	mst->ver_num = g->ver_num;
	mst->edge_num = count;
	mst->adj = (Edge**)malloc(sizeof(Edge*)*mst->ver_num);
	for (int i = 0; i < mst->ver_num; ++i) {
		mst->adj[i] = nullptr;
	}
	for (int i = 0; i < count; ++i) {
		Edge* e = (Edge*)malloc(sizeof(Edge));
		e->src = result[i]->src;
		e->dest = result[i]->dest;
		e->weight = result[i]->weight;
		Edge* temp = mst->adj[e->src];
		mst->adj[e->src] = e;
		mst->adj[e->src]->next = temp;
		
		e = (Edge*)malloc(sizeof(Edge));
		e->src = result[i]->dest;
		e->dest = result[i]->src;
		e->weight = result[i]->weight;
		temp = mst->adj[e->src];
		mst->adj[e->src] = e;
		mst->adj[e->src]->next = temp;
	}

	std::cout << "enqueue: " << enqueue_count << std::endl;
	std::cout << "dequeue: " << dequeue_count << std::endl;

	return mst;
}

Graph* get_MST_eager_Prim(Graph* g) {


	int enqueue_count = 0;
	int dequeue_count = 0;


	PQ* pq = init_queue(g->edge_num);
	Edge** result_set = (Edge**)malloc(sizeof(Edge*) * (g->ver_num - 1));
	int count = 0;
	int* marked = (int*)malloc(sizeof(int)*g->ver_num);
	double* cost_to = (double*)malloc(sizeof(double)*g->ver_num);
	for (int i = 0; i < g->ver_num; ++i) {
		marked[i] = 0;
		cost_to[i] = INT_MAX;
	}
	Edge* p = g->adj[0];
	marked[0] = 1;
	cost_to[0] = 0;
	while (p != nullptr) {
		enqueue(pq, p);
		cost_to[p->dest] = p->weight;
		p = p->next;


		enqueue_count++;

	}
	while (!is_pq_empty(pq)) {
		p = dequeue(pq);

		dequeue_count++;

		if (marked[p->dest] && marked[p->src]) {
			continue;
		}
		result_set[count++] = p;
		marked[p->dest]= 1;
		p = g->adj[p->dest];
		while (p != nullptr) {
			if (!marked[p->dest]) {
				if (p->weight < cost_to[p->dest]) {
					cost_to[p->dest] = p->weight;
					enqueue(pq, p);

					enqueue_count++;

				}
			}
			p = p->next;
		}
	}

	Graph* r = (Graph*)malloc(sizeof(Graph));
	r->vertex = g->vertex;
	r->ver_num = g->ver_num;
	r->edge_num = count;
	r->adj = (Edge**)malloc(sizeof(Edge*) * r->ver_num);
	for (int i = 0; i < r->ver_num; ++i) {
		r->adj[i] = nullptr;
	}

	for (int i = 0; i < count; ++i) {
		Edge* e1 = (Edge*)malloc(sizeof(Edge));
		e1->dest = result_set[i]->dest;
		e1->src = result_set[i]->src;
		e1->weight = result_set[i]->weight;
		
		Edge* temp = r->adj[e1->src];
		r->adj[e1->src] = e1;
		e1->next = temp;

		Edge* e2 = (Edge*)malloc(sizeof(Edge));
		e2->dest = result_set[i]->src;
		e2->src = result_set[i]->dest;
		e2->weight = result_set[i]->weight;
		
		temp = r->adj[e2->src];
		r->adj[e2->src] = e2;
		e2->next = temp;
	}


	std::cout << "enqueue: " << enqueue_count << std::endl;
	std::cout << "dequeue: " << dequeue_count << std::endl;

	return r;
}

void dfs(Graph* g, int pos, int* marked) {
	marked[pos] = 1;
	Edge* p = g->adj[pos];
	while (p != nullptr) {
		if (!marked[p->dest]) {
			dfs(g, p->dest, marked);
		}
		p = p->next;
	}
}

bool is_connected(Graph* g, int src, int dest) {
	int* marked = (int*)malloc(sizeof(int) * g->ver_num);
	for (int i = 0; i < g->ver_num; ++i) {
		marked[i] = 0;
	}
	dfs(g, src, marked);
	return marked[dest];
}


Graph* get_MST_Kruskal(Graph* g) {
	Graph* mst = (Graph*)malloc(sizeof(Graph));
	mst->vertex = g->vertex;
	mst->ver_num = g->ver_num;
	mst->edge_num = 0;
	mst->adj = (Edge**)malloc(sizeof(Edge*)*mst->ver_num);
	for (int i = 0; i < mst->ver_num; ++i) {
		mst->adj[i] = nullptr;
	}

	PQ* pq = (PQ*)malloc(sizeof(PQ));
	pq->e = (Edge**)malloc(sizeof(Edge*)*(g->edge_num));
	pq->size = 0;
	for (int i = 0; i < mst->ver_num - 1; ++i) {
		pq->e[i] = nullptr;
	}
	for (int i = 0; i < g->ver_num; ++i) {
		Edge* p = g->adj[i];
		while (p != nullptr) {
			if (p->dest > p->src) {
				enqueue(pq, p);
			}	
			p = p->next;
		}
	}
	while (mst->edge_num != mst->ver_num - 1) {
		Edge* p = dequeue(pq);
		if (is_connected(mst, p->src, p->dest)) {
			continue;
		}
		else {
			Edge* e1 = (Edge*)malloc(sizeof(Edge));
			e1->src = p->src;
			e1->dest = p->dest;
			e1->weight = p->weight;
			Edge* temp = mst->adj[e1->src];
			mst->adj[e1->src] = e1;
			e1->next = temp;

			Edge* e2 = (Edge*)malloc(sizeof(Edge));
			e2->src = p->dest;
			e2->dest = p->src;
			e2->weight = p->weight;
			temp = mst->adj[e2->src];
			mst->adj[e2->src] = e2;
			e2->next = temp;
			
			mst->edge_num++;
		}
	}
	return mst;
}


std::ostream& operator<<(std::ostream& os, Graph* g) {
	for (int i = 0; i < g->ver_num; ++i) {
		os << g->vertex[i].data << ": ";
		Edge* p = g->adj[i];
		while (p != nullptr) {
			os << "(" << g->vertex[p->dest].data << "," << p->weight << ")";
			p = p->next;
		}
		os << std::endl;
	}
	return os;
}

int index(Graph* g, char data) {
	for (int i = 0; i < g->ver_num; ++i) {
		if (g->vertex[i].data == data) {
			return i;
		}
	}
	return -1;
}

Graph* init_graph(char ver_data[], char edge_data[][2] , double weights[], int ver_num, int edge_num) {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	g->vertex = (Vertex*)malloc(sizeof(Vertex)*ver_num);
	g->adj = (Edge**)malloc(sizeof(Edge*)*ver_num);
	g->ver_num = ver_num;
	g->edge_num = edge_num;
	for (int i = 0; i < ver_num; ++i) {
		g->vertex[i].data = ver_data[i];
		g->adj[i] = nullptr;
	}
	for (int i = 0; i < edge_num; ++i) {
		int from = index(g, edge_data[i][0]);
		int to = index(g, edge_data[i][1]);
		double weight = weights[i];
		Edge* e1 = (Edge*)malloc(sizeof(Edge));
		e1->dest = to;
		e1->src = from;
		e1->weight = weight;
		e1->next = nullptr;
		
		Edge* e2 = (Edge*)malloc(sizeof(Edge));
		e2->dest = from;
		e2->src = to;
		e2->weight = weight;
		e2->next = nullptr;

		Edge* temp = g->adj[e1->src];
		g->adj[e1->src] = e1;
		e1->next = temp;

		temp = g->adj[e2->src];
		g->adj[e2->src] = e2;
		e2->next = temp;

	}
	return g;
}


int main() {
	char data[] = {'A','B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
	char edge[][2] = { 
		{'A','C'},{'C','H'} ,{'A','B'} ,{'C','D'},
		{'B','D'},{'D','G'},{'H','G'},{'A','E'},
		{'E','F'},{'F','D'},{'E','I'},{'I','F'}
	};
	double weights[] = { 1.3, 2, 3, 2.5, 1.5, 4, 6, 2.3, 4.6, 5.5, 8, 10 };
	int ver_num = sizeof(data) / sizeof(char);
	int edge_num = sizeof(edge) / sizeof(char[2]);

	Graph* g = init_graph(data, edge, weights, ver_num, edge_num);
	std::cout << g << std::endl;

	Graph* mst = get_MST_lazy_Prim(g);
	std::cout << mst << std::endl;

	Graph* mst2 = get_MST_eager_Prim(g);
	std::cout << mst2 << std::endl;


	Graph* mst3 = get_MST_Kruskal(g);
	std::cout << mst3 << std::endl;

	system("pause");
	return 0;
}