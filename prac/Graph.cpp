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

/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using std::set
std::vector<int> Graph::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey) {
    int* length=new int[m_vSize];//비용 저장
    int* prev_vertex = new int[m_vSize];//최단 경로 저장
    int endnum = 0;

    fill(length, length + m_vSize, IN_FINITY);//length전부 IN_FINITY로 저장

    set<pair<int,int>> s;//first는 비용, second는 도착지
    Edge* cure = FindVertex(startVertexKey)->GetHeadOfEdge();//시작 vertex에 인접해있는 vertex중 첫번째 edge, cure에 저장


    //출발지 넣어주기
    s.insert(make_pair(0, startVertexKey));
    length[startVertexKey] = 0;//시작점 거리

    while (!s.empty()) {
        int n = s.begin()->second;//최소 비용인 경로를 가져온다.
        s.erase(s.begin());

        if (n == endVertexKey) { endnum = 1; break; }//도착지까지 최단경로가 나온면 끝

        cure = FindVertex(n)->GetHeadOfEdge();//cure에 이동한 vertex의 첫번째 edge 저장      
        

        while (cure != NULL) {
            int next = cure->GetKey();
            int weight = cure->GetWeight();

            if (length[next] > length[n] + weight) {//원래 저장된 거리보다 n을 거쳐갈 때 더 짧으면
                if (length[next] != IN_FINITY) { s.erase(make_pair(length[next], next)); }// 이미 set에 있는 경로에서 더 짧은 경로가 나왔을 때 원래 set 지우기
                length[next] = length[n] + weight;
                prev_vertex[next] = n;
                s.insert(make_pair(length[next], next));
            }
            cure = cure->GetNext();//다음 경로
        }
    }

    vector<int> v;//최단 경로 저장
    //경로가 없을 때
    if (endnum != 1) { cout << "경로가 없다" << endl; vector<int> b; return b;}
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


/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using MinHeap
std::vector<int> Graph::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey) {
    int* length = new int[m_vSize];//비용 저장
    int* prev_vertex = new int[m_vSize];//최단 경로 저장
    int endnum = 0,dump=0;

    fill(length, length + m_vSize, IN_FINITY);//length전부 IN_FINITY로 저장

    MinHeap<int, int> h;//first는 비용, second는 도착지
    Edge* cure = FindVertex(startVertexKey)->GetHeadOfEdge();//시작 vertex에 인접해있는 vertex중 첫번째 edge, cure에 저장


    //출발지 넣어주기
    h.Push(0, startVertexKey);
    length[startVertexKey] = 0;//시작점 거리

    while (!h.IsEmpty()) {
        int n = h.Top().second;//최소비용인 vetext 가져오기
        h.Pop();//최소 값 지우기
        if (n == endVertexKey) { endnum = 1; break; }//도착지까지 최단경로가 나온면 끝

        cure = FindVertex(n)->GetHeadOfEdge();//cure에 이동한 vertex의 첫번째 edge 저장      

        while (cure != NULL) {
            int next = cure->GetKey();
            int weight = cure->GetWeight();

            if (length[next] > length[n] + weight) {//원래 저장된 거리보다 n을 거쳐갈 때 더 짧으면
                if (length[next] != IN_FINITY) { dump=1; }// 이미 heap에 있는 경로에서 더 짧은 경로가 나왔을 때 dump=1
                length[next] = length[n] + weight;
                prev_vertex[next] = n;
                if (dump == 1) { h.DecKey(next, length[next]); dump = 0; }//더 짧은 경로를 찾았을 때
                else { h.Push(length[next], next); }
            }
            cure = cure->GetNext();//다음 경로
        }
    }

    vector<int> v;//최단 경로 저장
    //경로가 없을 때
    if (endnum != 1) { cout << "경로가 없다" << endl; vector<int> b; return b; }
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

/// find the shortest path from startVertexKey to endVertexKey with Bellman-Ford
std::vector<int> Graph::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey) {
    int* d = new int[m_vSize];
    fill(d, d + m_vSize, IN_FINITY);//d 전부 IN_FINITY로 저장
    int* p = new int[m_vSize];
    fill(p,p + m_vSize, -1);//p전부 -1로 저장

    d[startVertexKey] = 0;//시작지 0으로 초기화

    Vertex* curv = m_pVHead;//시작 vertex 저장
    Edge* cure = curv->GetHeadOfEdge();//시작 vertex의 첫번째 edge저장
    for (int z = 0; z < m_vSize - 1; z++) {
        curv = m_pVHead;//시작 vertex 저장
        for (int i = 0; i < m_vSize; i++) {//모든 vertex반복
            cure = curv->GetHeadOfEdge();//시작 vertex의 첫번째 edge저장
            if (d[curv->GetKey()] != IN_FINITY) {//방문했던 곳이면 확인
                while (cure != NULL) {//하나의 vertex의 인접 vertex방문
                    int v = cure->GetKey();//도착지
                    int weight = cure->GetWeight();//비용
                    int w = curv->GetKey();//출발지

                    if (d[v] > d[w] + weight) {//경유해서 가는 경우가 비용이 적으면
                        d[v] = d[w] + weight;//비용 갱신
                        p[v] = w;//비용이 갱신되었다면 도착지의 이전 vertex를 p에 저장
                    }
                    cure = cure->GetNext();//다음 edge
                }
            }
            curv = curv->GetNext();//다음 vertex
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


