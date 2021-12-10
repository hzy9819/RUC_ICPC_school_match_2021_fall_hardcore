#ifndef HYPERG_H_HZY
#define HYPERG_H_HZY

#include <unordered_set>
#include <vector>


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
    void max_cardinality_search(size_t * a);
    void build_fa();
    void check_connectivity_T(std::vector <std::vector <size_t> > & V, std::vector <bool> & res);
    bool test_zero_fill_in(size_t * a);
    bool check_chordal();

    ~Graph() {
        if(n != 0)
            free(lst);
        if(m != 0)
            free(e);
        if(fa != NULL)
            free(fa);
    }
};

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
    bool check_acyclic();
    bool build_join_forest(Graph & G);
    bool check_join_forest(Graph & G);
};





#endif