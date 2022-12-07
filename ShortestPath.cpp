/*
NOT FINISHED YET...

*/


#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

template <class Key, class CmpKey>
class IMaxPQ {
private:
    vector<Key>* pq; //heap-ordered complete binary tree
    unordered_map<Key, int> map; //map from key to index in pq
    int N = 0; //number of elements on pq
public:
    IMaxPQ() {
        pq = new vector<Key>(); //initialize pq
        pq->insert(pq->begin(), 0); //insert dummy element at 0
    }

    IMaxPQ(Key keys[], int n) { //initialize pq with keys
        pq = new vector<Key>(keys, n); //initialize pq
        pq->insert(pq->begin(), 0); //insert dummy element at 0
        N = n;
        for (int k = N / 2; k >= 1; k--) sink(k); //heapify
    }

    void print() {
        for (int i = 1; i <= N; i++) //print pq
            cout << (*pq)[i] << " ";
        cout << endl;
    }

    void swim(int k) { //move element up heap
        Key x = (*pq)[k];
        while (k > 1 && CmpKey::compare((*pq)[k / 2], x) < 0) {
            (*pq)[k] = (*pq)[k / 2]; //exchange with parent
            map[(*pq)[k]] = k; //update map
            k = k / 2; //move up
        }
        (*pq)[k] = x; //insert at proper place
        map[(*pq)[k]] = k; //update map
    }

    void sink(int k) {
        Key x = (*pq)[k];
        while (2 * k <= N) {
            int j = 2 * k;
            if (j < N && CmpKey::compare((*pq)[j], (*pq)[j + 1]) < 0)
                j++;
            if (CmpKey::compare(x, (*pq)[j]) >= 0) break;
            (*pq)[k] = (*pq)[j];
            map[(*pq)[k]] = k;
            k = j;
        }
        (*pq)[k] = x;
        map[(*pq)[k]] = k;
    }
    bool isEmpty() { return N == 0; }
    int size() { return N; }
    Key max() { return (*pq)[1]; }

    void insert(Key x) {
        N++;
        pq->insert(pq->end(), x); //add x, and percolate it up to maintain heap invariant
        map[(*pq)[N]] = N; //update map
        swim(N);
    }

    Key delMax() {
        Key max = (*pq)[1]; //get max
        Key t = (*pq)[1]; //exchange with last element
        (*pq)[1] = (*pq)[N];
        (*pq)[N] = t;
        map[(*pq)[1]] = 1; //update map
        map[(*pq)[N]] = N; //update map
        N--;
        sink(1); //sink new root to maintain heap invariant
        pq->pop_back(); //remove last element
        return max;
    }

    void change(Key x) {
        int k = map[x]; //get index of x
        swim(k); //swim x to maintain heap invariant
        sink(k); //sink x to maintain heap invariant
    }

};

class Vertex;
class Edge;
typedef Vertex* Vertex_ptr;
typedef Edge* Edge_ptr;

class Vertex {
public:
    string name;
    int num;
    bool mark;
    int priority;
    bool inFringe;
    Edge_ptr parentEdge;
    vector<Edge_ptr>* neighbors;
    Vertex(string name, int num) {
        this->name = name;
        this->num = num;
        /*mark = false;
        priority = 0;
        inFringe = false;
        parentEdge = NULL;*/
        neighbors = new vector<Edge_ptr>();
    }
    void setMark(bool mark) { this->mark = mark; }
    bool getMark() { return mark; }
    void setPriority(int priority) { this->priority = priority; }
    int getPriority() { return priority; }
    void setInFringe(bool inFringe) { this->inFringe = inFringe; }
    bool getInFringe() { return inFringe; }
    void setParentEdge(Edge_ptr parentEdge) { this->parentEdge = parentEdge; }
    Edge_ptr getParentEdge() { return parentEdge; }
    void addNeighbor(Edge_ptr edge) { neighbors->push_back(edge); }
    vector<Edge_ptr>& getNeighbors() { return *neighbors; } //return reference to vector

};

unordered_map<string, Vertex_ptr> vertex_map; //map from vertex name to vertex pointer

Vertex_ptr find_vertex(string s) { //look at this again
    Vertex_ptr v = vertex_map[s]; //look up vertex pointer in map
    if (v != NULL) //if vertex pointer is not null
        return v; //return vertex pointer
    return (vertex_map[s] = new Vertex(s, vertex_map.size())); //else, create new vertex pointer, add to map, and return
}

class CmpVertexPtrs {
public:
    static int compare(Vertex_ptr v, const Vertex_ptr w) {
        return w->getPriority() - v->getPriority();
    }
};

class Edge {
public:
    Vertex_ptr v;
    int d, w;
    Edge(Vertex_ptr v, int d, int w) {
        this->v = v;
        this->d = d;
        this->w = w;
    }
    Vertex_ptr getV() { return v; }
    int getD() { return d; }
    int getW() { return w; }
};

void visit(Vertex_ptr v, IMaxPQ<Vertex_ptr, CmpVertexPtrs>& pq);

void findSP(Vertex_ptr s, Vertex_ptr d) {
    IMaxPQ<Vertex_ptr, CmpVertexPtrs> pq; //priority queue
    s->setPriority(0); //set priority of source to 0
    visit(s, pq); //visit source
    while (!pq.isEmpty()) {
        Vertex_ptr v = pq.delMax(); //get vertex with highest priority
        //visit(v, pq); //visit vertex
        if (v == d) //if destination is reach
            return;
        v->setInFringe(false);
        visit(v, pq); //visit vertex
    }
}

void visit(Vertex_ptr v, IMaxPQ<Vertex_ptr, CmpVertexPtrs>& pq) {
    v->setMark(true); //mark vertex as visited
    for (Edge_ptr p : v->getNeighbors()) {
        Vertex_ptr x = p->getV();
        if (x->getMark()) //if neighbor is visited
            continue; //skip
        if (!x->getInFringe() || x->getPriority() > v->getPriority() + p->getD() + p->getW()) { //if neighbor is not in fringe or priority of neighbor is greater than priority of vertex + distance to neighbor + wormholes to neighbor) {
            x->setPriority(v->getPriority() + p->getD()); //set priority of neighbor
            x->setParentEdge(new Edge(v, p->getD(), p->getW())); //set parent edge of neighbor
            if (!x->getInFringe()) //if neighbor is not in fringe
                pq.insert(x); //insert neighbor into fringe
            else
                pq.change(x); //else, change priority of neighbor in fringe
            x->setInFringe(true); //set neighbor as in fringe
        }
    }
}

int main() {
    string sourceStr, destStr, vStr, wStr;
    int n, dt, wmh; //n = number of vertices, dt = distance, wmh = number of wormholes

    cin >> n >> sourceStr >> destStr; //get number of vertices, source, and destination

    Vertex_ptr source = find_vertex(sourceStr); //find source vertex
    Vertex_ptr dest = find_vertex(destStr); //find destination vertex

   /* while (cin >> vStr >> wStr >> dt >> wmh) {
        Vertex_ptr vv = find_vertex(vStr); //find vertex v
        Vertex_ptr ww = find_vertex(wStr); //find vertex w
        vv->addNeighbor(new Edge(ww, dt, wmh)); //add edge from v to w
        ww->addNeighbor(new Edge(vv, dt, wmh)); //add edge from w to v
    }

    findSP(source, dest); //find shortest path from source to destination
    cout << "distance is: " << dest->getPriority() << endl; //print distance

    return 0;
}*/


    for(int i = 0; i < n; i++){
        cin >> vStr >> wStr >> d >> wmh; //get vertex names, distance, and number of wormholes
        Vertex_ptr v = find_vertex(vStr); //find vertex
        Vertex_ptr w = find_vertex(wStr); //find vertex
        v->addNeighbor(new Edge(w, d, wmh)); //add edge to vertex
        w->addNeighbor(new Edge(v, d, wmh)); //add edge to vertex
    }

    findSP(source, dest); //find shortest path from source to destination

    if(dest->getParentEdge() == NULL) //if destination has no parent edge
        cout << "NO" << endl; //print NO
    else{
        cout << "YES" << endl; //print YES
        vector<Edge_ptr> path; //create vector to store path
        Edge_ptr e = dest->getParentEdge(); //get parent edge of destination
        while(e != NULL){ //while parent edge is not null
            path.push_back(e); //add parent edge to path
            e = e->getV()->getParentEdge(); //get parent edge of parent edge's vertex
        }
        for(int i = path.size() - 1; i >= 0; i--){ //print path
            cout << path[i]->getV()->name << " " << path[i]->getW()->name << " " << path[i]->getD() << " " << path[i]->getW() << endl;
        }
    }

    return 0;

}

