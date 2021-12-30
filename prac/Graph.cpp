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



//���� �߰��� �Լ�
void Graph::AddName(int vertexKey,string name) {//�̸��� �߰��ϴ� �Լ�
    Vertex* cur = FindVertex(vertexKey);
    if (cur == NULL) { return; }
    else { cur->SetName(name); }
}
void Graph::Addstore(int vertexKey, string store) {//�̸��� �߰��ϴ� �Լ�
    Vertex* cur = FindVertex(vertexKey);
    if (cur == NULL) {return; }
    else { cur->Setstore(store); }
}



/// add vertex with vertexNum at the end of the linked list for the vertics
// �̹� �ִ� key���� ������ ���� ���� ���� ����(�ؾ��ϸ� �� ��� ����� ä��°ɷ��ϱ�)
void Graph::AddVertex(int vertexKey) {
    Vertex* cur = m_pVHead;
    Vertex* inv = new Vertex(vertexKey);//�̷��� �ص� �ʱ�ȭ �ǳ�? ine�� ������ vertex
    
    if (cur == NULL) { m_pVHead = inv;}//�׷����� ��������� head�� �ֱ�
    else {
        while (cur->GetKey() < vertexKey && cur->GetNext() != NULL) {//�����Ϸ��� key���� cut�� key�� ũ�� cur->next�� NULL�� �ƴϸ�
            if(cur->GetNext()->GetKey()> vertexKey){
                inv->SetNext(cur->GetNext());//cur�� next�� �ִٸ� inv�� next�� ����
                cur->SetNext(inv);//cur�� next�� ine �ֱ�
                m_vSize += 1;//size 1 ����
                return;
            }
            cur = cur->GetNext();//cur�� next�� �̵�
        }
        cur->SetNext(inv);//cur�� next�� ine �ֱ�
    }
    m_vSize += 1;//size 1 ����
    return;
}

/// add edge from the vertex which the number is startVertexKey to the vertex which the number is endVertexKey
void Graph::AddEdge(int startVertexKey, int endVertexKey, int weight) {
    Vertex* cur = FindVertex(startVertexKey);
    if (cur == NULL) { cout << "���� vertex�� �������� ����" << endl; return; }
    else { cur->AddEdge(endVertexKey, weight); }
}

/// get the vertex which the key is vertexNum
Vertex* Graph::FindVertex(int key) {
    Vertex* cur = m_pVHead;
    if (cur == NULL) { return NULL; }//graph�� ����ִ�

    //�˸��� ���� vertexã��(key������), key���� cur�� key�� cur�� next�� ������ cur�� next�� �̵�
    while (cur->GetKey() < key && cur->GetNext() != NULL) { cur = cur->GetNext(); }

    if (cur->GetKey()== key) { return cur;}//�ش� vertex�� ��ȯ
    else { return NULL; }//ã�� vertex����
}

/// get the number of the vertics
int Graph::Size() const {return m_vSize;}

/// memory free for the vertics
void Graph::Clear() {
    Vertex* c=m_pVHead;
    Vertex* s = NULL;
    while (c != NULL) {
        s = c->GetNext();
        delete c;
        c = s;
    }
}

/// print out the graph as matrix form
void Graph::Print(std::ofstream& fout) {
    Vertex* curv = m_pVHead;//head vertex���� ����
    
    while (curv != NULL) {//vertex ���
        for (int i = 0; i < m_vSize; i++) {//��� vertex ���
            Edge* cure = curv->FindEdge(i);//���� vertex�� i�� edgeã��
            if (cure == NULL) { fout << "0 "; cout << "0 "; }//������ 0���
            else { fout << cure->GetWeight() << " "; cout << cure->GetWeight() << " "; }//������ weight ���
        }
        fout << endl;
        cout << endl;
        curv = curv->GetNext();//curv �̵�
    }
}

/// check whether the graph has negative edge or not.
bool Graph::IsNegativeEdge() {//��� edgeȮ��
    Vertex* curv = m_pVHead;//head vertex���� ����

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

/// find the path from startVertexKey to endVertexKey with BFS (stack)
std::vector<int> Graph::FindPathBfs(int startVertexKey, int endVertexKey) {
    Queue<int> q;
    int endnum = 0,length=0;
    vector<int> v;//������ ����
    vector<int> v1;//����� ����
    Edge* cure = FindVertex(startVertexKey)->GetHeadOfEdge();//���� vertex�� �������ִ� vertex�� ù��° edge, cure�� ����
    q.push(startVertexKey);//queue�� ù��° vertex�ֱ�
    v.push_back(startVertexKey);
    v1.push_back(startVertexKey);
    while (!q.empty()) {
        int qn = q.val[q.front];
        cure = FindVertex(qn)->GetHeadOfEdge();
        q.pop();
        //cout << qn << endl;
        while (cure!= NULL&&endnum==0) {
            vector<int>::iterator it = find(v.begin(), v.end(), cure->GetKey());//it�� qn�� ��ġ����, ������ end��ġ
            if(it==v.end()){//vector�� ���� ���̸�
                q.push(cure->GetKey());//qn vertex�� ������ vertex�� queue�� �ֱ�
                //length = length + cure->GetWeight();//����� �����ش�.
                v1.push_back(qn);
                v.push_back(cure->GetKey());//�湮 ǥ��
                if (cure->GetKey() == endVertexKey) { endnum = 1; break; }
            }
            cure = cure->GetNext();
        }
    }

    if (endnum != 1) { vector<int>em; return em; }//�ִ� ��ΰ� ������ �� ���� ����

    int c = 0,s=0;
    vector<int> res;//�������
    s = v1.back();
    res.push_back(v.back());//���������� res�� �ֱ�
    c = v.back();
    length = length + FindVertex(s)->FindEdge(c)->GetWeight();//��� ��� �߰�
    while (c!=startVertexKey) {//�Ųٷ� �̵�
        c = v.back();
        if (s == c) {//������� �ٸ� �������� ���ٸ�(��� ���������)
            s = v1.back();
            if (s != c) {
                res.push_back(c);
                length = length + FindVertex(s)->FindEdge(c)->GetWeight(); //��� ��� �߰�
            }
            if (s == startVertexKey) {//���� ����� ���� �Դٸ�
                res.push_back(s);
                break;
            }
        }
        v1.pop_back();
        v.pop_back();
    }
    res.push_back(length);//�ǵڿ��� ���, ���������� ������ �ϸ� ��ε�

    return res;
}

/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using std::set
std::vector<int> Graph::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey) {
    int* length=new int[m_vSize];//��� ����
    int* prev_vertex = new int[m_vSize];//�ִ� ��� ����
    int endnum = 0;

    fill(length, length + m_vSize, IN_FINITY);//length���� IN_FINITY�� ����

    set<pair<int,int>> s;//first�� ���, second�� ������
    Edge* cure = FindVertex(startVertexKey)->GetHeadOfEdge();//���� vertex�� �������ִ� vertex�� ù��° edge, cure�� ����


    //����� �־��ֱ�
    s.insert(make_pair(0, startVertexKey));
    length[startVertexKey] = 0;//������ �Ÿ�

    while (!s.empty()) {
        int n = s.begin()->second;//�ּ� ����� ��θ� �����´�.
        s.erase(s.begin());

        if (n == endVertexKey) { endnum = 1; break; }//���������� �ִܰ�ΰ� ���¸� ��

        cure = FindVertex(n)->GetHeadOfEdge();//cure�� �̵��� vertex�� ù��° edge ����      
        

        while (cure != NULL) {
            int next = cure->GetKey();
            int weight = cure->GetWeight();

            if (length[next] > length[n] + weight) {//���� ����� �Ÿ����� n�� ���İ� �� �� ª����
                if (length[next] != IN_FINITY) { s.erase(make_pair(length[next], next)); }// �̹� set�� �ִ� ��ο��� �� ª�� ��ΰ� ������ �� ���� set �����
                length[next] = length[n] + weight;
                prev_vertex[next] = n;
                s.insert(make_pair(length[next], next));
            }
            cure = cure->GetNext();//���� ���
        }
    }

    vector<int> v;//�ִ� ��� ����
    //��ΰ� ���� ��
    if (endnum != 1) { cout << "��ΰ� ����" << endl; vector<int> b; return b;}
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
    int* length = new int[m_vSize];//��� ����
    int* prev_vertex = new int[m_vSize];//�ִ� ��� ����
    int endnum = 0,dump=0;

    fill(length, length + m_vSize, IN_FINITY);//length���� IN_FINITY�� ����

    MinHeap<int, int> h;//first�� ���, second�� ������
    Edge* cure = FindVertex(startVertexKey)->GetHeadOfEdge();//���� vertex�� �������ִ� vertex�� ù��° edge, cure�� ����


    //����� �־��ֱ�
    h.Push(0, startVertexKey);
    length[startVertexKey] = 0;//������ �Ÿ�

    while (!h.IsEmpty()) {
        int n = h.Top().second;//�ּҺ���� vetext ��������
        h.Pop();//�ּ� �� �����
        if (n == endVertexKey) { endnum = 1; break; }//���������� �ִܰ�ΰ� ���¸� ��

        cure = FindVertex(n)->GetHeadOfEdge();//cure�� �̵��� vertex�� ù��° edge ����      

        while (cure != NULL) {
            int next = cure->GetKey();
            int weight = cure->GetWeight();

            if (length[next] > length[n] + weight) {//���� ����� �Ÿ����� n�� ���İ� �� �� ª����
                if (length[next] != IN_FINITY) { dump=1; }// �̹� heap�� �ִ� ��ο��� �� ª�� ��ΰ� ������ �� dump=1
                length[next] = length[n] + weight;
                prev_vertex[next] = n;
                if (dump == 1) { h.DecKey(next, length[next]); dump = 0; }//�� ª�� ��θ� ã���� ��
                else { h.Push(length[next], next); }
            }
            cure = cure->GetNext();//���� ���
        }
    }

    vector<int> v;//�ִ� ��� ����
    //��ΰ� ���� ��
    if (endnum != 1) { cout << "��ΰ� ����" << endl; vector<int> b; return b; }
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
    fill(d, d + m_vSize, IN_FINITY);//d ���� IN_FINITY�� ����
    int* p = new int[m_vSize];
    fill(p,p + m_vSize, -1);//p���� -1�� ����

    d[startVertexKey] = 0;//������ 0���� �ʱ�ȭ

    Vertex* curv = m_pVHead;//���� vertex ����
    Edge* cure = curv->GetHeadOfEdge();//���� vertex�� ù��° edge����
    for (int z = 0; z < m_vSize - 1; z++) {
        curv = m_pVHead;//���� vertex ����
        for (int i = 0; i < m_vSize; i++) {//��� vertex�ݺ�
            cure = curv->GetHeadOfEdge();//���� vertex�� ù��° edge����
            if (d[curv->GetKey()] != IN_FINITY) {//�湮�ߴ� ���̸� Ȯ��
                while (cure != NULL) {//�ϳ��� vertex�� ���� vertex�湮
                    int v = cure->GetKey();//������
                    int weight = cure->GetWeight();//���
                    int w = curv->GetKey();//�����

                    if (d[v] > d[w] + weight) {//�����ؼ� ���� ��찡 ����� ������
                        d[v] = d[w] + weight;//��� ����
                        p[v] = w;//����� ���ŵǾ��ٸ� �������� ���� vertex�� p�� ����
                    }
                    cure = cure->GetNext();//���� edge
                }
            }
            curv = curv->GetNext();//���� vertex
        }
    }
    
    curv = m_pVHead;
    for (int i = 0; i < m_vSize; i++) {//��� vertex�ݺ�
        cure = curv->GetHeadOfEdge();
        if (d[curv->GetKey()] != IN_FINITY) {//�湮�ߴ� ���̸� Ȯ��
            while (cure != NULL) {//�ϳ��� vertex�� ���� vertex�湮
                int v = cure->GetKey();//������
                int weight = cure->GetWeight();//���
                int w = curv->GetKey();//�����

                if (d[v] > d[w] + weight) {//n-1�� �ϰ� �� �ڿ� ��κ�ȭ�� �ִ°��(��������Ŭ)
                    vector<int> b; return b;//�� vector��ȯ
                }
                cure = cure->GetNext();//���� edge
            }
        }
        curv = curv->GetNext();//���� vertex
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
            if (i == j) { a[i][j]=0; }//�ڱ� �ڽſ��� ���� ���� 0
            else { a[i][j] = IN_FINITY; }
        }
    }

    Vertex* curv = m_pVHead;//head vertex���� ����
    while (curv != NULL) {//vertex ���
        Edge* cure = curv->GetHeadOfEdge();//���� vertex�� i�� edgeã��
        while (cure != NULL) {
            a[curv->GetKey()][cure->GetKey()] = cure->GetWeight();//a[�������][��������]=���
            cure = cure->GetNext();
        }
        curv = curv->GetNext();
    }


    for (int k = 0; k < m_vSize; k++) {
        for (int i = 0; i < m_vSize; i++) {//��� vertex�ݺ�
            for (int j = 0; j < m_vSize; j++) {
                if (a[i][j] > a[i][k] + a[k][j]) { a[i][j] = a[i][k] + a[k][j]; }
            }
        }
    }
 
    for (int i = 0; i < m_vSize; i++) {//���� ����Ŭ Ȯ���ϴ� �ݺ���
        if (a[i][i] < 0) { vector<vector<int>> s; return s; }//�ڱ� �ڽ����� ���� ���� ������ �Ǹ� ��������Ŭ ���� ��
    }
    
    return a;
}


