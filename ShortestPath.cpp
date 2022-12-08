/*
 Developer: Niraj Nepal
 Date: 12/08/2022
 Description: Finds Shortest Path from one Star System to another.
 Credits: Tutor Lucas helped with some errors in the Edge Class.
NOT FINISHED YET...

*/


#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

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
        pq->push_back(0); //insert dummy element at 0
        map = unordered_map<Key, int>(); //initialize map
    }

    IMaxPQ(Key keys[], int n) { //initialize pq with keys
        pq = new vector<Key>(keys, keys + n); //initialize pq
        pq->push_back(0); //insert dummy element at 0
        map = unordered_map<Key, int>(); //initialize map
        N = n;
        for (int k = N / 2; k >= 1; k--) sink(k); //heapify
    }

    void print() {
        for (int i = N; i >= 1; i--) //print pq in reverse order
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

    void sink(int k) { // move element down heap
        Key x = (*pq)[k]; // save element to be sunk
        while (2 * k <= N) { // while there is a left child
            int j = 2 * k; // left child
            if (j < N && CmpKey::compare((*pq)[j], (*pq)[j + 1]) < 0) // if right child is larger
                j++; // right child
            if (CmpKey::compare(x, (*pq)[j]) >= 0) break;// if x is larger than both children
            (*pq)[k] = (*pq)[j]; // move child up
            map[(*pq)[k]] = k;// update map
            k = j; // move down
        }
        (*pq)[k] = x; // insert at proper place
        map[(*pq)[k]] = k;// update map
    }
    bool isEmpty() { return N == 0; }
    int size() { return N; }
    Key max() { return (*pq)[1]; }

    void insert(Key x) {
        N++;
        pq->push_back(x); //add x, and percolate it up to maintain heap invariant
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
        map[(*pq)[1]] = 1; //update map after every operation on the key
        pq->pop_back(); //remove last element
        return max;
    }

    void change(Key x) {
        int k = map[x]; //get index of x
        swim(k); //swim x to maintain heap invariant
        sink(k); //sink x to maintain heap invariant
        map[(*pq)[k]] = k; //update map after every operation on the key
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
    void getName() { cout << name << endl; }
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
    static int compare(Vertex_ptr v, Vertex_ptr w) { //compare two vertex pointers
        return v->getPriority() - w->getPriority(); //compare priorities
    }
};

typedef IMaxPQ<Vertex_ptr, CmpVertexPtrs> PriorityQueue;

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

void visit(Vertex_ptr v, PriorityQueue pq);

void findSP(Vertex_ptr s, Vertex_ptr d) {
    PriorityQueue pq; //priority queue
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

void visit(Vertex_ptr v, PriorityQueue pq) {
    v->setMark(true); //mark vertex as visited
    for (Edge_ptr p : v->getNeighbors()) {
        Vertex_ptr x = p->getV();
        if (x->getMark()) //if neighbor is visited
            continue; //skip
        if (!x->getInFringe() || x->getPriority() > v->getPriority() + p->getD() + p->getW()) { //if neighbor is not in fringe or priority of neighbor is greater than priority of vertex + distance to neighbor + wormholes to neighbor
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

void printPath(Vertex_ptr v) {
    if (v->getParentEdge() == NULL) {
        v->getName();
        return;
    }
    printPath(v->getParentEdge()->getV());
    v->getName();
}


int main() {
    int n, dt, wmh;
    string sourceStr, destStr, vStr, wStr;
    cin >> n >> sourceStr >> destStr; //get maximum number of wormholes and source and destination vertices

    Vertex_ptr source = find_vertex(sourceStr); //find source vertex
    Vertex_ptr dest = find_vertex(destStr); //find destination vertex
    string inputLine;
    while (getline(cin, inputLine)) {
        if (inputLine.empty()) {
            break;
        }

        stringstream ss(inputLine);
        ss >> vStr >> wStr >> dt >> wmh;
        Vertex_ptr vv = find_vertex(vStr); //find vertex v
        Vertex_ptr ww = find_vertex(wStr); //find vertex w
        vv->addNeighbor(new Edge(ww, dt, wmh)); //add edge from v to w
        ww->addNeighbor(new Edge(vv, dt, wmh)); //add edge from w to v
    }
    findSP(source, dest); //find shortest path from source to destination
    cout << "distance is: " << dest->getPriority() << endl; //print distance
    return 0;
}  

