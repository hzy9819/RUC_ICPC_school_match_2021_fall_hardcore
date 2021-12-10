#include <bits/stdc++.h>
using namespace std;

typedef std::vector <size_t> HyperEdge;

struct Edge {
    size_t to, nxt;
};

struct Graph {
    size_t n, m, d;  /* Indicate the scale(vertex, edge number) of graph */
    size_t * lst;
    Edge * e;        /* Using adjacency list store graph, lst store head pointer */
    size_t * fa;    /* For tree, store graph with father list */

    Graph() {n = 0, m = 0, d = 0, lst = NULL, e = NULL, fa = NULL;}
    Graph(size_t _n, size_t _m) : n(_n), m(_m) {
        d = 0;
        if(n) {
            lst = (size_t *) malloc(n * sizeof(size_t));
            for(size_t i = 0; i < n; ++i)
                lst[i] = -1;
        }
        if(m)
            e = (Edge *) malloc(m * sizeof(Edge));
        fa = NULL;
    }

    void Init(size_t _n, size_t _m) {
        if(n != 0)
            free(lst);
        if(m != 0)
            free(e);
        if(fa != NULL) {
            free(fa);
            fa = NULL;
        }
        
        n = _n, m = _m, d = 0;
        if(n) {
            lst = (size_t *) malloc(n * sizeof(size_t));
            for(size_t i = 0; i < n; ++i)
                lst[i] = -1;
        }
        if(m)
            e = (Edge *) malloc(m * sizeof(Edge));
    }
    void add(size_t x, size_t y);

    ~Graph() {
        if(n != 0)
            free(lst);
        if(m != 0)
            free(e);
        if(fa != NULL)
            free(fa);
    }
};

void Graph::add(size_t x, size_t y) {
    e[d].to = y, e[d].nxt = lst[x], lst[x] = d++;
}

struct Hypergraph
{
    size_t n, m;
    std::vector< HyperEdge > E;

    Hypergraph() {n = m = 0;}
    Hypergraph(size_t _n, size_t _m) : n(_n), m(_m) {}

    void set(size_t _n, size_t _m) {n = _n, m = _m;}
    void add(HyperEdge e) {
        E.push_back(e);
    }
    void max_cardinality_search(size_t * a, size_t * b, size_t * y, size_t * R, size_t & k);
    bool test_zero_fill_in(size_t * b, size_t * y, size_t * R, size_t & k);
    bool build_join_forest(Graph & G);
};

void Hypergraph::max_cardinality_search(size_t * a, size_t * b, size_t * y, size_t * R, size_t & k) {
    size_t size[m], cur = n + 1, top = 0;
    std::queue <size_t> Layer[n + 5];
    std::vector <size_t> rev[n + 5];
    k = 0;
    // HyperEdge::iterator it;

    /* Preprocessing */
    for(size_t i = 0; i < n; ++i) {
        a[i] = -1;        
    }
    for(size_t j = 0; j < m; ++j) {
        for(auto it = E[j].begin(); it != E[j].end(); ++it)
            rev[*it].push_back(j);
        size[j] = 0;
        y[j] = -1;
        Layer[0].push(j);
    }

    while(top != -1) {
        size_t S = -1, tmp;
        while(S == -1) {
            while(top != -1 && Layer[top].empty())
                top--;
            if(top == -1)
                break;
            tmp = Layer[top].front();
            Layer[top].pop();
            if(size[tmp] == top)
                S = tmp;
        }
        if(S == -1)
            break;
        /*b[S] = */++k, R[k] = S, size[S] = -1;
        for(auto it = E[S].begin(); it != E[S].end(); ++it) 
            if(a[*it] == -1) {
                a[*it] = --cur;
                b[*it] = k;
                for(auto _it = rev[*it].begin(); _it != rev[*it].end(); ++_it)
                    if(size[*_it] != -1) {
                        y[*_it] = k;
                        size[*_it] = size[*_it] + 1;
                        if(size[*_it] < E[*_it].size()) {
                            Layer[size[*_it]].push(*_it);
                            top = std::max(top, size[*_it]);
                        } else
                            size[*_it] = -1;
                    }
            }
    }
}

bool Hypergraph::test_zero_fill_in(size_t * b, size_t * y, size_t * R, size_t & k) {
    size_t idx[n+5];
    std::vector <size_t> rev[k + 5];

    for(size_t j = 0; j < m; ++j)
        if(y[j] != -1)
            rev[y[j]].push_back(j);

    for(size_t i = 0; i < n; ++i)
        idx[i] = 0;
    for(size_t i = 1; i <= k; ++i) {
        for(auto it = E[R[i]].begin(); it != E[R[i]].end(); ++it)
            idx[*it] = i;
        for(auto it = rev[i].begin(); it != rev[i].end(); ++it)
            for(auto _it = E[*it].begin(); _it != E[*it].end(); ++_it)
                if(b[*_it] < i && idx[*_it] < i)
                    return false;
    }
    return true;
}


bool Hypergraph::build_join_forest(Graph & G) {
    // size_t a[n], b[n], y[m + 5], R[m + 5], k;
    size_t * a = (size_t *) malloc(sizeof(size_t) * n);
    size_t * b = (size_t *) malloc(sizeof(size_t) * n);
    size_t * y = (size_t *) malloc(sizeof(size_t) * (m+5));
    size_t * R = (size_t *) malloc(sizeof(size_t) * (m+5));
    size_t k;
    this->max_cardinality_search(a, b, y, R, k);
    std::vector <size_t> rev[k + 5];

    if(! this->test_zero_fill_in(b, y, R, k)) {
        // puts("The hypergraph is not acyclic!");
        free(a), free(b), free(y), free(R);
        return false;
    }
    else {
        G.Init(m, (m - 1) * 2);
        for(size_t j = 0; j < m; ++j)
            if(y[j] != -1) {
                G.add(R[y[j]], j), G.add(j, R[y[j]]);
                // printf("%d %d\n", j, R[y[j]]);
            }
    }
    free(a), free(b), free(y), free(R);
    return true;
}

void DataLoader(const char * file_name, Hypergraph & G) {
    FILE * fin = fopen(file_name, "r");
    fin = stdin;
    size_t n, m, sz, tmp;
    fscanf(fin, "%lu %lu", &n, &m);
    G.set(m, n);

    std::vector< std::vector<size_t> > V(n);

    for(size_t i = 0; i < m; ++i) {
        fscanf(fin, "%lu", &sz);
        for(size_t j = 0; j < sz; ++j) {
            fscanf(fin, "%lu", &tmp);
            V[tmp].push_back(i);
        }
    }
    for(size_t i = 0; i < n; ++i)
        G.add(V[i]);
}

int main(int argc, char * argv[]) {
    Hypergraph H;
    Graph G;
    DataLoader(argv[1], H);

    FILE * fout = fopen(argv[2], "w");

    if(H.build_join_forest(G)) {
        fprintf(fout, "YES\n");
        for(size_t i = 0; i < G.n; ++i)
            for(size_t j = G.lst[i]; j != -1; j = G.e[j].nxt)
                if(i < G.e[j].to)
                    fprintf(fout, "%lu %lu\n", i, G.e[j].to);
    }
    else 
        fprintf(fout, "NO\n");
    return 0;
}