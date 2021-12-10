#ifndef HYPERG_CPP_HZY
#define HYPERG_CPP_HZY

#include <queue>
#include "Hypergraph.h"


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

bool Hypergraph::check_acyclic() {
    size_t a[n], b[n], y[m], R[m], k;
    this->max_cardinality_search(a, b, y, R, k);
    return this->test_zero_fill_in(b, y, R, k);
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
        /*
        for(size_t i = 0; i < n; ++i)
            printf("%lu ", a[i]);
        puts("");        

        for(size_t i = 0; i < n; ++i)
            printf("%lu ", b[i]);
        puts("");

        for(size_t j = 1; j <= k; ++j)
            printf("%lu ", R[j]);
        puts("");

        for(size_t j = 0; j < m; ++j)
            printf("%lu ", y[j]);
        puts("");
        */
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

void Dfs_build_fa(size_t t, Graph & G, size_t * fa) {
    for(size_t i = G.lst[t]; i != -1; i = G.e[i].nxt)
        if(fa[G.e[i].to] == -1) {
            fa[G.e[i].to] = t;
            Dfs_build_fa(G.e[i].to, G, fa);
        }
}

void Graph::check_connectivity_T(std::vector <std::vector <size_t> > & V, std::vector <bool> & res) {
    build_fa();
    size_t vis[n] ;

    for(size_t i = 0; i < n; ++i)
        vis[i] = -1;
    res.clear();

    size_t cnt = 0;
    for(auto v = V.begin(); v != V.end(); ++v, ++cnt) {
        for(auto it = v->begin(); it != v->end(); ++it)
            vis[*it] = cnt;
        size_t flag = 0;
        for(auto it = v->begin(); it != v->end(); ++it)
            if(fa[*it] == -1 || vis[fa[*it]] != cnt) {
                flag++;
                if(flag > 1)
                    break;
            }
        if(flag != 1)
            res.push_back(0);
        else
            res.push_back(1);
    }
}

bool Hypergraph::check_join_forest(Graph & G) {
    /*
        The judge problem is to check some vertex (vertex induced tree) set on  a tree is connected or not.
        Here is an algorithm of check problem with time-complexity \sum |V|:
            1.convert the tree into a rooted tree and represent it with father[x];
            2.vertex set V is connected if and only if exactly 1 vertex's father do not appear in V.
    */
    if(G.n != m || G.m != (m - 1) * 2)
        return false;
    size_t fa[m], vis[n];
    std::vector <size_t> V[n];

    for(size_t j = 0; j < m; ++j) {
        fa[j] = -1;
        for(auto it = E[j].begin(); it != E[j].end(); ++it)
            V[*it].push_back(j);
    }
    for(size_t i = 0; i < n; ++i)
        vis[i] = -1, fa[i] = -1;

    fa[0] = 0;
    Dfs_build_fa(0, G, fa);
    fa[0] = -1;

    for(size_t i = 0; i < n; ++i) {
        for(auto it = V[i].begin(); it != V[i].end(); ++it)
            vis[*it] = i;
        bool flag = 0; // record the only 1 vertex do not appear
        for(auto it = V[i].begin(); it != V[i].end(); ++it)
            if(fa[*it] == -1 || vis[fa[*it]] != i) {
                if(flag)
                    return false;
                flag = 1;
            }
        if(!flag)
            return false;
    }

    return true;
}

void Graph::build_fa() {
    /*
        Use deep first search to build a dfs tree for the graph
    */
    if(fa != NULL)
        return ;
    fa = (size_t *) malloc(sizeof(size_t) * (n + 5));
    for(size_t i = 0; i < n; ++i)
        fa[i] = -1;
    fa[0] = 0;
    Dfs_build_fa(0, *this, fa);    
    fa[0] = -1;
}

void Graph::add(size_t x, size_t y) {
    e[d].to = y, e[d].nxt = lst[x], lst[x] = d++;
}

void Graph::max_cardinality_search(size_t * a) {
    size_t size[n], cur = n, top = 0;
    std::queue <size_t> Layer[n + 5];
    for(size_t i = 0; i < n; ++i)
        size[i] = 0, Layer[0].push(i);
    while(cur) {
        size_t v = -1, tmp;
        while(v == -1) {
            while(Layer[top].empty())
                    top--;
            tmp = Layer[top].front();
            Layer[top].pop();
            if(size[tmp] == top)
                v = tmp;
        }
        a[v] = cur, size[v] = -1;
        for(size_t i = lst[v]; i != -1; i = e[i].nxt) 
            if(size[e[i].to] != -1) {
                size_t w = e[i].to;
                size[w] = size[w] + 1;
                Layer[size[w]].push(w);
        }
        cur--;
        top++;
    }
}

bool Graph::test_zero_fill_in(size_t * a) {
    size_t a_[n + 5], f[n], idx[n], w;
    for(size_t i = 0; i < n; ++i)
        a_[a[i]] = i;
    for(size_t i = 1; i <= n; ++i) {
        w = a_[i], f[w] = w, idx[w] = i;
        for(size_t j = lst[w]; j != -1; j = e[j].nxt) 
            if(a[e[j].to] < i) {
                size_t v = e[j].to;
                idx[v] = i;
                if(f[v] == v)
                    f[v] = w;
            }
        for(size_t j = lst[w]; j = -1; j = e[j].nxt)
            if(a[e[j].to] < i && idx[f[e[j].to]] < i)
                return false;
    }
    return true;
}

bool Graph::check_chordal() {
    size_t a[n];
    this->max_cardinality_search(a);
    return this->test_zero_fill_in(a);
}

#endif