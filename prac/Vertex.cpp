#include "Vertex.h"

Vertex::Vertex() {
	m_key = -1;
	m_size = 0;
	m_pEHead = NULL; //�����Ҵ� �ؾ��ϳ�?
	m_pNext = NULL;
}
Vertex::Vertex(int key) {
	m_key = key;
	m_size = 0;
	m_pEHead = NULL;
	m_pNext = NULL;
}

Vertex::~Vertex() {
	delete m_pNext;
	delete m_pEHead;
}


//���� �߰��Ѱ�
void Vertex::SetName(string name) { Name = name; }
void Vertex::Setstore(string s) { store = s; }


Edge* Vertex::FindEdge(int endvertex) {
	Edge* cure = m_pEHead;//head vertex���� ����

	while (cure != NULL) {//vertex ���
		if (cure->GetKey() == endvertex) { return cure; }
		cure = cure->GetNext();//curv �̵�
	}
	return NULL;
}

Edge* Vertex::FindprevEdge(int endvertex) {
	Edge* cure = m_pEHead;//head vertex���� ����
	Edge* prev = NULL;//head vertex���� ����
	while (cure != NULL) {//vertex ���
		if (cure->GetKey() == endvertex) { return prev; }
		prev = cure;
		cure = cure->GetNext();//curv �̵�
	}
	return NULL;
}



/// set the next pointer of this vertex
void Vertex::SetNext(Vertex* pNext) {m_pNext = pNext;}

/// get the key of this vertex
int Vertex::GetKey() const {return m_key;}

/// get the next pointer of this vertex
Vertex* Vertex::GetNext() const {return m_pNext;}

/// get the number of the edges
int Vertex::Size() const { return m_size; }

/// add edge with edgeNum at the end of the linked list for the edges
/// the key of the vertex for the edge
/// the weight of the edge
void Vertex::AddEdge(int edgeKey, int weight) {
	Edge* cur = m_pEHead;
	Edge* ine=new Edge(edgeKey, weight);//�̷��� �ص� �ʱ�ȭ �ǳ�? ine�� ������ edge

	if (cur == NULL) { m_pEHead = ine; }//ù edge�̸� m_pEHead�� ����

	else {
		if (cur->GetKey() > edgeKey) {//�����ϴ°� ���� ���� key�̸�
			ine->SetNext(cur);
			m_pEHead = ine;
			return;
		}
		while (cur->GetKey() < edgeKey && cur->GetNext() != NULL) {
			if (cur->GetNext()->GetKey() > edgeKey) {
				ine->SetNext(cur->GetNext());
				cur->SetNext(ine);
				m_size += 1;
				return;
			}
			cur = cur->GetNext();
		}
		cur->SetNext(ine);
	}
	m_size += 1;
	return;
}


/// get the head pointer of the edge
Edge* Vertex::GetHeadOfEdge() const {return m_pEHead;}


/// memory free for edges
void Vertex::Clear() {
	Edge* c = m_pEHead;
	Edge* s = c->GetNext();
	while (c != NULL) {
		s = c->GetNext();
		delete c;
		c = s;
	}
	m_pEHead = NULL;
	m_pNext = NULL;
}