#include "Graph.h"
#include "MinHeap.h"
#include "Queue.h"
#include <set>
#include<cmath>
#include<iostream>
#include<sstream>
#include<algorithm>
#define DFS_FIRST_PATH

Graph::Graph()
{
    m_pVHead = NULL;
    m_vSize = 0;
}
Graph::~Graph()
{
    delete m_pVHead;
    m_vSize = 0;
}


void Graph::AddName(int vertexKey,string name) {//add name
    Vertex* cur = FindVertex(vertexKey);
    if (cur == NULL) { return; }
    else { cur->SetName(name); }
}
void Graph::Addstore(int vertexKey, string store) {//add name
    Vertex* cur = FindVertex(vertexKey);
    if (cur == NULL) {return; }
    else { cur->Setstore(store); }
}


/// add vertex with vertexNum at the end of the linked list for the vertics
void Graph::AddVertex(int vertexKey) {
    Vertex* cur = m_pVHead;
    Vertex* inv = new Vertex(vertexKey);
    
    if (cur == NULL) { m_pVHead = inv;}//If the graph is empty, put it in the head
    else {
        while (cur->GetKey() < vertexKey && cur->GetNext() != NULL) {//If the key value to be inserted is larger than the key value of cut and cur->next is not NULL,
            if(cur->GetNext()->GetKey()> vertexKey){
                inv->SetNext(cur->GetNext());//If cur's next exists, it is connected to inv's next.
                cur->SetNext(inv);//Put ine in cur's next
                m_vSize += 1;
                return;
            }
            cur = cur->GetNext();//move cur to next
        }
        cur->SetNext(inv);//Put ine in cur's next
    }
    m_vSize += 1;//size increase
    return;
}

// add edge from the vertex which the number is startVertexKey to the vertex which the number is endVertexKey
void Graph::AddEdge(int startVertexKey, int endVertexKey, int weight) {
    Vertex* cur = FindVertex(startVertexKey);
    if (cur == NULL) { cout << "no start vertex" << endl; return; }
    else { cur->AddEdge(endVertexKey, weight); }
}

// get the vertex which the key is vertexNum
Vertex* Graph::FindVertex(int key) {
    Vertex* cur = m_pVHead;
    if (cur == NULL) { return NULL; }//empty graph

    while (cur->GetKey() < key && cur->GetNext() != NULL) { cur = cur->GetNext(); }

    if (cur->GetKey()== key) { return cur;}
    else { return NULL; }//No vertices to find
}

// get the number of the vertics
int Graph::Size() const {return m_vSize;}

// memory free for the vertics
void Graph::Clear() {
    Vertex* c=m_pVHead;
    Vertex* s = NULL;
    while (c != NULL) {
        s = c->GetNext();
        delete c;
        c = s;
    }
}

// print out the graph as matrix form
void Graph::Print(std::ofstream& fout) {
    Vertex* curv = m_pVHead;//start at head vertex
    
    while (curv != NULL) {
        for (int i = 0; i < m_vSize; i++) {
            Edge* cure = curv->FindEdge(i);//Find the edge whose arrival vertex is i
            if (cure == NULL) { fout << "0 "; cout << "0 "; }
            else { fout << cure->GetWeight() << " "; cout << cure->GetWeight() << " "; }
        }
        fout << endl;
        cout << endl;
        curv = curv->GetNext();
    }
}

// check whether the graph has negative edge or not.
bool Graph::IsNegativeEdge() {
    Vertex* curv = m_pVHead;

    while (curv != NULL) {
        Edge* cure = curv->GetHeadOfEdge();
        while (cure != NULL) {
            if (cure->GetWeight() < 0) { return 1; }
            cure=cure->GetNext();
        }
        curv=curv->GetNext();
    }

    return 0;
}

// find the path from startVertexKey to endVertexKey with BFS (stack)
std::vector<int> Graph::FindPathBfs(int startVertexKey, int endVertexKey) {
    Queue<int> q;
    int endnum = 0,length=0;
    vector<int> v;//save destination
    vector<int> v1;//save origin
    Edge* cure = FindVertex(startVertexKey)->GetHeadOfEdge();//Store the first edge among vertices adjacent to the start vertex in cure
    q.push(startVertexKey);//Put the first vertex in the queue
    v.push_back(startVertexKey);
    v1.push_back(startVertexKey);
    while (!q.empty()) {
        int qn = q.val[q.front];
        cure = FindVertex(qn)->GetHeadOfEdge();
        q.pop();
        //cout << qn << endl;
        while (cure!= NULL&&endnum==0) {
            vector<int>::iterator it = find(v.begin(), v.end(), cure->GetKey());//Store the position of qn in it, if there is no end position
            if(it==v.end()){
                q.push(cure->GetKey());//Putting vertices adjacent to qn vertices into the queue
                //length = length + cure->GetWeight();
                v1.push_back(qn);
                v.push_back(cure->GetKey());//visit sign
                if (cure->GetKey() == endVertexKey) { endnum = 1; break; }
            }
            cure = cure->GetNext();
        }
    }

    if (endnum != 1) { vector<int>em; return em; }//Returns an empty vector if there is no shortest path

    int c = 0,s=0;
    vector<int> res;//Save result
    s = v1.back();
    res.push_back(v.back());//put in final destination res
    c = v.back();
    length = length + FindVertex(s)->FindEdge(c)->GetWeight();
    while (c!=startVertexKey) {
        c = v.back();
        if (s == c) {//If the origin is the same as the destination (a route is created)
            s = v1.back();
            if (s != c) {
                res.push_back(c);
                length = length + FindVertex(s)->FindEdge(c)->GetWeight(); 
            }
            if (s == startVertexKey) {//If you have come to the original place of departure
                res.push_back(s);
                break;
            }
        }
        v1.pop_back();
        v.pop_back();
    }
    res.push_back(length);

    return res;
}

// find the shortest path from startVertexKey to endVertexKey with Dijkstra using std::set
std::vector<int> Graph::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey) {
    int* length=new int[m_vSize]; //save cost
    int* prev_vertex = new int[m_vSize];//save shortest path
    int endnum = 0;

    fill(length, length + m_vSize, IN_FINITY);//Store all length as IN_FINITY

    set<pair<int,int>> s;//First is the cost, second is the destination
    Edge* cure = FindVertex(startVertexKey)->GetHeadOfEdge();

    //enter the starting point
    s.insert(make_pair(0, startVertexKey));
    length[startVertexKey] = 0;

    while (!s.empty()) {
        int n = s.begin()->second;//Get the path with the least cost.
        s.erase(s.begin());

        if (n == endVertexKey) { endnum = 1; break; }//If the shortest route to the destination is found, it is over.

        cure = FindVertex(n)->GetHeadOfEdge();//Save the first edge of the moved vertex to cure    
        

        while (cure != NULL) {
            int next = cure->GetKey();
            int weight = cure->GetWeight();

            if (length[next] > length[n] + weight) {//If it is shorter when traversing n than the originally stored distance
                if (length[next] != IN_FINITY) { s.erase(make_pair(length[next], next)); }
                length[next] = length[n] + weight;
                prev_vertex[next] = n;
                s.insert(make_pair(length[next], next));
            }
            cure = cure->GetNext();//next path
        }
    }

    vector<int> v;

    if (endnum != 1) { cout << "no path" << endl; vector<int> b; return b;}
    else {
        int index = endVertexKey;
        //cout << endVertexKey;
        v.push_back(endVertexKey);
        for (int q = 0; q < m_vSize; q++) {
            if (prev_vertex[index] == startVertexKey) { 
                //cout << "<- "<<startVertexKey; 
                v.push_back(startVertexKey);
                break; 
            }
            //cout << "<- "<<prev_vertex[index];
            v.push_back(prev_vertex[index]);
            index = prev_vertex[index];   
        }
    }
    //cout <<endl<< length[endVertexKey] << endl;
    v.push_back(length[endVertexKey]);
    return v;
}


// find the shortest path from startVertexKey to endVertexKey with Dijkstra using MinHeap
std::vector<int> Graph::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey) {
    int* length = new int[m_vSize];//save cost
    int* prev_vertex = new int[m_vSize];
    int endnum = 0,dump=0;

    fill(length, length + m_vSize, IN_FINITY);

    MinHeap<int, int> h;
    Edge* cure = FindVertex(startVertexKey)->GetHeadOfEdge();

    //enter the starting point
    h.Push(0, startVertexKey);
    length[startVertexKey] = 0;//starting point distance

    while (!h.IsEmpty()) {
        int n = h.Top().second;//Get vetext at the lowest cost
        h.Pop();//pop Minimum Value
        if (n == endVertexKey) { endnum = 1; break; }//If the shortest route to the destination is found, it is over.

        cure = FindVertex(n)->GetHeadOfEdge();//Save the first edge of the vertex moved to cure

        while (cure != NULL) {
            int next = cure->GetKey();
            int weight = cure->GetWeight();

            if (length[next] > length[n] + weight) {//If traversing n is shorter than the original distance,
                if (length[next] != IN_FINITY) { dump=1; }// dump=1 for shorter path
                length[next] = length[n] + weight;
                prev_vertex[next] = n;
                if (dump == 1) { h.DecKey(next, length[next]); dump = 0; }
                else { h.Push(length[next], next); }
            }
            cure = cure->GetNext();
        }
    }

    vector<int> v;//save shortest path
    
    if (endnum != 1) { cout << "no path" << endl; vector<int> b; return b; }
    else {
        int index = endVertexKey;
        //cout << endVertexKey;
        v.push_back(endVertexKey);
        for (int q = 0; q < m_vSize; q++) {
            if (prev_vertex[index] == startVertexKey) {
                //cout << "<- "<<startVertexKey; 
                v.push_back(startVertexKey);
                break;
            }
            //cout << "<- "<<prev_vertex[index];
            v.push_back(prev_vertex[index]);
            index = prev_vertex[index];
        }
    }
    v.push_back(length[endVertexKey]);
    return v;
}

// find the shortest path from startVertexKey to endVertexKey with Bellman-Ford
std::vector<int> Graph::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey) {
    int* d = new int[m_vSize];
    fill(d, d + m_vSize, IN_FINITY);
    int* p = new int[m_vSize];
    fill(p,p + m_vSize, -1);//Save all p as -1

    d[startVertexKey] = 0;

    Vertex* curv = m_pVHead;
    Edge* cure = curv->GetHeadOfEdge();
    for (int z = 0; z < m_vSize - 1; z++) {
        curv = m_pVHead;
        for (int i = 0; i < m_vSize; i++) {//repeat all vertices
            cure = curv->GetHeadOfEdge();
            if (d[curv->GetKey()] != IN_FINITY) {
                while (cure != NULL) {//Visiting adjacent vertices
                    int v = cure->GetKey();
                    int weight = cure->GetWeight();
                    int w = curv->GetKey();

                    if (d[v] > d[w] + weight) {
                        d[v] = d[w] + weight;
                        p[v] = w;
                    }
                    cure = cure->GetNext();
                }
            }
            curv = curv->GetNext();
        }
    }
    
    curv = m_pVHead;
    for (int i = 0; i < m_vSize; i++) {//모든 vertex반복
        cure = curv->GetHeadOfEdge();
        if (d[curv->GetKey()] != IN_FINITY) {//방문했던 곳이면 확인
            while (cure != NULL) {//하나의 vertex의 인접 vertex방문
                int v = cure->GetKey();//도착지
                int weight = cure->GetWeight();//비용
                int w = curv->GetKey();//출발지

                if (d[v] > d[w] + weight) {//n-1번 하고 난 뒤에 경로변화가 있는경우(음수싸이클)
                    vector<int> b; return b;//빈 vector반환
                }
                cure = cure->GetNext();//다음 edge
            }
        }
        curv = curv->GetNext();//다음 vertex
    }
    
    vector<int> v;
    int index = endVertexKey;
    v.push_back(endVertexKey);
    for (int q = 0; q < m_vSize; q++) {
        if (p[index] == startVertexKey) {
            v.push_back(startVertexKey);
            break;
        }
        v.push_back(p[index]);
        index = p[index];
    }
    v.push_back(d[endVertexKey]);
    return v;
}

std::vector<vector<int> > Graph::FindShortestPathFloyd() {
    vector<vector<int> > a(m_vSize,vector<int>(m_vSize,0));
    //initialization
    for (int i = 0; i < m_vSize; i++) {
        for (int j = 0; j < m_vSize; j++) {
            if (i == j) { a[i][j]=0; }//자기 자신에게 가는 것은 0
            else { a[i][j] = IN_FINITY; }
        }
    }

    Vertex* curv = m_pVHead;//head vertex에서 시작
    while (curv != NULL) {//vertex 출력
        Edge* cure = curv->GetHeadOfEdge();//도착 vertex가 i인 edge찾기
        while (cure != NULL) {
            a[curv->GetKey()][cure->GetKey()] = cure->GetWeight();//a[출발정점][도착정점]=비용
            cure = cure->GetNext();
        }
        curv = curv->GetNext();
    }


    for (int k = 0; k < m_vSize; k++) {
        for (int i = 0; i < m_vSize; i++) {//모든 vertex반복
            for (int j = 0; j < m_vSize; j++) {
                if (a[i][j] > a[i][k] + a[k][j]) { a[i][j] = a[i][k] + a[k][j]; }
            }
        }
    }
 
    for (int i = 0; i < m_vSize; i++) {//음수 사이클 확인하는 반복문
        if (a[i][i] < 0) { vector<vector<int>> s; return s; }//자기 자신으로 가는 값이 음수가 되면 음수사이클 생긴 것
    }
    
    return a;
}


