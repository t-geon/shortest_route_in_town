#include "Manager.h"

Manager::~Manager()
{
    if (fout.is_open())
        fout.close();

}

void Manager::Run(const char* filepath)
{
    fout.open(RESULT_LOG_PATH);

    fin.open(filepath);
    if (!fin)
    {
        cout << "======SYSTEM======" << endl << endl << "CommandFileNotExist" << endl ;
        fout << "======SYSTEM======" << endl << endl << "CommandFileNotExist" << endl ;

        PrintError(CommandFileNotExist);
        return;
    }

    Result re = Success;
    char cmd[32];
    while (!fin.eof())
    {
        fin.getline(cmd, 32);//Read 1 line of command.txt
        if (!strcmp(cmd, "")) { continue; }//Code to repeat the number of lines
        else if (cmd[0] == '/' && cmd[1] == '/') { continue; }// "//"�̸� ��ɾ� �� �д´�
        char* tmp, * tmm;
        strtok_s(cmd, " ", &tmp);//Saved in the character cmd in front of the "" standard, and the remaining characters in the address of tmp
        
        
        if (!strcmp(cmd, "LOAD")) {
            cout << "========LOAD========" << endl<<endl;
            fout << "========LOAD========" << endl << endl;
            re = Load(tmp);
            if (re== Success) { fout << "Success"<<endl ; cout << "Success" << endl; }
            else { fout << "LoadFileNotExist" << endl ; cout << "LoadFileNotExist" << endl; }
            PrintError(re);
        }
        
        else if (!strcmp(cmd, "PRINT")) {
            cout << "========PRINT========" << endl<<endl;
            fout << "========PRINT========" << endl << endl;
            re = Print();
            if (re == GraphNotExist) { fout << "GraphNotExist" << endl; cout << "GraphNotExist" << endl; }

            PrintError(re);
        }

        else if (!strcmp(cmd, "UPDATE")) {
            cout << "========UPDATE========" << endl << endl;
            fout << "========UPDATE========" << endl << endl;
            re = Update();
            if (re == Success) { fout << "Success" << endl; cout << "Success" << endl; }
            else { fout << "FaildtoUpdatePath" << endl; cout<<"FaildtoUpdatePath" << endl; }

            PrintError(re);
        }

        else if (!strcmp(cmd, "BFS")) {
            cout << "========BFS========" << endl<<endl;
            fout << "========BFS========" << endl << endl;
            //��ɾ� ���ں���
            if (!strcmp(tmp,"")) { fout << "VertexKeyNotExist"  << endl; cout << "VertexKeyNotExist" << endl;re= VertexKeyNotExist;}
            else {
                strtok_s(tmp, " ", &tmm);
                if (!strcmp(tmm, "")) { fout << "VertexKeyNotExist"  << endl; cout << "VertexKeyNotExist" << endl; re = VertexKeyNotExist;}
                else {
                    re = FindPathBfs(stoi(tmp), stoi(tmm));
                    if (re == GraphNotExist) { fout << "GraphNotExist" << endl; cout << "GraphNotExist" << endl; }
                    else if(re==InvalidVertexKey) { fout << "InvalidVertexKey" << endl; cout << "InvalidVertexKey" << endl; }
                    else if(re==InvalidAlgorithm) { fout << "InvalidAlgorithm" << endl; cout << "InvalidAlgorithm" << endl; }
                }
            }
            PrintError(re);
        }

        else if (!strcmp(cmd, "DIJKSTRA")) {
            cout << "========DIJKSTRA========" << endl << endl;
            fout << "========DIJKSTRA========" << endl << endl;
            //��ɾ� ���ں���
            if (!strcmp(tmp, "")) { fout << "VertexKeyNotExist" << endl; cout << "VertexKeyNotExist" << endl; re = VertexKeyNotExist;
            }
            else {
                strtok_s(tmp, " ", &tmm);
                if (!strcmp(tmm, "")) { fout << "VertexKeyNotExist" << endl; cout << "VertexKeyNotExist" << endl; re = VertexKeyNotExist;}
                else {
                    re = FindShortestPathDijkstraUsingSet(stoi(tmp), stoi(tmm));
                    if (re == GraphNotExist) { fout << "GraphNotExist" << endl; cout << "GraphNotExist" << endl; }
                    else if (re == InvalidVertexKey) { fout << "InvalidVertexKey" << endl; cout << "InvalidVertexKey" << endl; }
                    else if (re == InvalidAlgorithm) { fout << "InvalidAlgorithm" << endl; cout << "InvalidAlgorithm" << endl; }
                }
            }
            PrintError(re);
        }

        else if (!strcmp(cmd, "DIJKSTRAMIN")) {
            cout << "========DIJKSTRAMIN========" << endl << endl;
            fout << "========DIJKSTRAMIN========" << endl << endl;
            //��ɾ� ���ں���
            if (!strcmp(tmp, "")) { fout << "VertexKeyNotExist" << endl; cout << "VertexKeyNotExist" << endl; re = VertexKeyNotExist;}
            else {
                strtok_s(tmp, " ", &tmm);
                if (!strcmp(tmm, "")) { fout << "VertexKeyNotExist" << endl; cout << "VertexKeyNotExist" << endl; re = VertexKeyNotExist;}
                else {
                    re = FindShortestPathDijkstraUsingMinHeap(stoi(tmp), stoi(tmm));
                    if (re == GraphNotExist) { fout << "GraphNotExist" << endl; cout << "GraphNotExist" << endl; }
                    else if (re == InvalidVertexKey) { fout << "InvalidVertexKey" << endl; cout << "InvalidVertexKey" << endl; }
                    else if (re == InvalidAlgorithm) { fout << "InvalidAlgorithm" << endl; cout << "InvalidAlgorithm" << endl; }
                }
            }
            PrintError(re);
        }

        else if (!strcmp(cmd, "BELLMANFORD")) {
            cout << "========BELLMANFORD========" << endl << endl;
            fout << "========BELLMANFORD========" << endl << endl;
            //��ɾ� ���ں���
            if (!strcmp(tmp, "")) { fout << "VertexKeyNotExist" << endl; cout << "VertexKeyNotExist" << endl; re = VertexKeyNotExist;}
            else {
                strtok_s(tmp, " ", &tmm);
                if (!strcmp(tmm, "")) { fout << "VertexKeyNotExist" << endl; cout << "VertexKeyNotExist" << endl; re = VertexKeyNotExist;}
                else {
                    re = FindShortestPathBellmanFord(stoi(tmp), stoi(tmm));
                    if (re == GraphNotExist) { fout << "GraphNotExist" << endl; cout << "GraphNotExist" << endl; }
                    else if (re == InvalidVertexKey) { fout << "InvalidVertexKey" << endl; cout << "InvalidVertexKey" << endl; }
                    else if (re == NegativeCycleDetected) { fout << "NegativeCycleDetected" << endl; cout << "NegativeCycleDetected" << endl; }
                }
            }
            PrintError(re);
        }

        else if (!strcmp(cmd, "FLOYD")) {
            cout << "========FLOYD========" << endl<<endl;
            fout << "========FLOYD========" << endl << endl;
            re = FindShortestPathFloyd();
            if(re== NegativeCycleDetected){ fout << "NegativeCycleDetected" << endl; cout << "NegativeCycleDetected" << endl; }
            else if(re==GraphNotExist){ fout << "GraphNotExist" << endl; cout << "GraphNotExist" << endl; }
            PrintError(re);
        }

        else if (!strcmp(cmd, "CONFIG")) {
            cout << "========CONFIG LOG========" << endl<<endl;
            //���޵� ���ڰ� ������ ��
            if (!strcmp(tmp, "")) { fout << "InvalidOptionName" << endl; cout << "InvalidOptionName" << endl; re = InvalidOptionName; }
            else {
                tmp = strtok_s(tmp, " ", &tmm);
                if (strcmp(tmp, "-sort")) { fout << "InvalidOptionName" << endl; cout << "InvalidOptionName" << endl; re = InvalidOptionName; }
                else {
                    if (!strcmp(tmm, "quick")) {
                        con = "quick"; re = Success;
                        cout << "Sorted by : " << con << " Sorting" << endl;
                        fout << "Sorted by : " << con << " Sorting" << endl;
                    }
                    else if (!strcmp(tmm, "insert")) {
                        con = "insert"; re = Success;
                        cout << "Sorted by : " << con << " Sorting" << endl;
                        fout << "Sorted by : " << con << " Sorting" << endl;
                    }
                    else if (!strcmp(tmm, "merge")) {
                        con = "merge"; re = Success;
                        cout << "Sorted by : " << con << " Sorting" << endl;
                        fout << "Sorted by : " << con << " Sorting" << endl;
                    }
                    else if (!strcmp(tmm, "heap")) {
                        con = "heap"; re = Success;
                        cout << "Sorted by : " << con << " Sorting" << endl;
                        fout << "Sorted by : " << con << " Sorting" << endl;
                    }
                    else if (!strcmp(tmm, "bubble")) {
                        con = "bubble"; re = Success;
                        cout << "Sorted by : " << con << " Sorting" << endl;
                        fout << "Sorted by : " << con << " Sorting" << endl;
                    }
                    else if (!strcmp(tmm, "selection")) {
                        con = "selection"; re = Success;
                        cout << "Sorted by : " << con << " Sorting" << endl;
                        fout << "Sorted by : " << con << " Sorting" << endl;
                    }
                    else {
                        cout << "InvalidAlgorithmName" << endl;
                        fout << "InvalidAlgorithmName" << endl;
                        re = InvalidAlgorithmName;
                    }
                }
            }
            PrintError(re);
        }

        else
        {
            cout << "========ASTAR========" << endl << endl;
            cout << "NonDefinedCommand" << endl;
            fout << "========ASTAR========" << endl << endl;
            fout << "NonDefinedCommand" << endl;

            PrintError(NonDefinedCommand);
        }
    }
    fin.close();
    return;


}


void Manager::PrintError(Result result)
{
    cout << endl << "=====================" << endl << endl << endl << "=====================" << endl << endl
        << "Error code: " << result << endl << endl << "=====================" << endl << endl;
    fout << endl << "=====================" << endl << endl << endl << "=====================" << endl << endl
        << "Error code: " << result << endl << endl << "=====================" << endl << endl;
    
}


/// <summary>
/// make a graph
/// </summary>
///
/// <param name="filepath">
/// the filepath to read to make the graph
/// </param>
///
/// <returns>
/// Result::Success if load is successful.
/// Result::LoadFileNotExist if file is not exist.
/// </returns>
Result Manager::Load(const char* filepath)
{
    ifstream fi;
    fi.open(filepath);
    if (!fi) {return LoadFileNotExist; }

    int vnum = 0, gsize = 0;
    string name, store,ns1;//����, ����, ���� �̸�����

    //read first line
    char cmd1[100];
    fi.getline(cmd1, 100);
    gsize = stoi(cmd1);// graph size update


    while (!fi.eof())
    {
        fi.getline(cmd1, 100);//Read 1 line of command.txt
        if (!strcmp(cmd1, "")) { continue; }//Code to repeat the number of lines
        char* tmp1, * tmm1, * cmp2;
        strtok_s(cmd1, "/", &tmp1);//cmd1�� /�� ���ڿ�(�����̸�,����) tmp�� /�� ���ڿ�(���)
        
        ns1 = string(cmd1);
        ns1.erase(ns1.size() - 1, 1);
        strtok_s(cmd1, "'", &cmp2);//cmd1�� �̸�, cmp1�� s ���Ǹ�
        name = string(cmd1);
        strtok_s(cmp2, " ", &cmp2);//cmp1�� ���Ǹ�
        store = string(cmp2);

        m_graph.AddVertex(vnum);//vertex ����
        m_graph.FindVertex(vnum)->ns = ns1;//���Ǹ� ����
        m_graph.AddName(vnum, name);//name ����
        m_graph.Addstore(vnum, store);//store ����

        for (int i = 0; i < gsize; i++) {//edge�߰�
            tmm1 = strtok_s(tmp1, " ", &tmp1);//tmm�� " "�� ���ڿ� tmp�� " "�� ���ڿ�
            if (stoi(tmm1) != 0) { m_graph.AddEdge(vnum, i, stoi(tmm1)); }//vnum��° vertex�� edge�߰�
        }
        vnum += 1;
    }
    return Success;
}


/// <summary>
/// print out the graph as matrix form
/// </summary>
///
/// <returns>
/// Result::Success if the printing is successful
/// Result::GraphNotExist if there is no graph
/// </returns>
Result Manager::Print()
{
    if (m_graph.head() == NULL) { return GraphNotExist; }
    else { m_graph.Print(fout); return Success; }
}



/// <summary>
/// find the path from startVertexKey to endVertexKey with BFS (stack and queue)
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindPathBfs(int startVertexKey, int endVertexKey)
{
    if(m_graph.head() == NULL) { return GraphNotExist; }
    if (m_graph.IsNegativeEdge() == 1) { return InvalidAlgorithm; }
    if (m_graph.FindVertex(startVertexKey) == NULL || m_graph.FindVertex(endVertexKey) == NULL) { return InvalidVertexKey; }
    vector<int> v = m_graph.FindPathBfs(startVertexKey, endVertexKey);
    if (v.size() == 0) {
        fout << "�ִ� ��ΰ� ����" << endl; 
        cout << "�ִ� ��ΰ� ����" << endl; return InvalidAlgorithm; }
    //�ִܰ�ΰ� ���� �� ������ ��� ���Ƿ� ����
    else {
        int length = v.back();
        v.pop_back();
        cout << "shortest path: ";
        fout << "shortest path: ";
        for (int i = v.size() - 1; i >= 0; i--) { 
            fout << v[i] << " ";
            cout << v[i] << " "; }//�ڿ��� ���� ����ϸ� ��ε�
       
        int* vv = &v[0];
        sort(con, vv, v.size());

        fout << endl << "path length: " << length << endl;
        cout << endl<<"path length: "<<length<<endl;
        //course�κ� ���
        compression(v);//v���� �ִܰ�� ������ ����Ǿ��ִ�.
    }
    return Success;
}

/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using std::set
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
    if (m_graph.head() == NULL) { return GraphNotExist; }
    if (m_graph.IsNegativeEdge() == 1) { return InvalidAlgorithm; }
    if (m_graph.FindVertex(startVertexKey) == NULL || m_graph.FindVertex(endVertexKey) == NULL) { return InvalidVertexKey; }
    vector<int> v = m_graph.FindShortestPathDijkstraUsingSet(startVertexKey, endVertexKey);
    if (v.size() == 0) { fout << "�ִ� ��ΰ� ����" << endl; cout << "�ִ� ��ΰ� ����" << endl; return InvalidAlgorithm; }
    //�ִܰ�ΰ� ���� �� ������ ��� ���Ƿ� ����
    else {
        int length = v.back();
        v.pop_back();
        fout << "shortest path: "; cout << "shortest path: ";
        for (int i = v.size() - 1; i >= 0; i--) { fout << v[i] << " "; cout << v[i] << " "; }//�ڿ��� ���� ����ϸ� ��ε�

        int* vv = &v[0];
        sort(con, vv, v.size());

        fout << endl << "path length: " << length << endl;
        cout << endl << "path length: " << length << endl;
        //course�κ� ���
        compression(v);//v���� �ִܰ�� ������ ����Ǿ��ִ�.
    }
    
    return Success;
}

/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using MinHeap
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey)
{
    if (m_graph.head() == NULL) { return GraphNotExist; }
    if (m_graph.IsNegativeEdge() == 1) { return InvalidAlgorithm; }
    if (m_graph.FindVertex(startVertexKey) == NULL || m_graph.FindVertex(endVertexKey) == NULL) { return InvalidVertexKey; }
    
    vector<int> v = m_graph.FindShortestPathDijkstraUsingMinHeap(startVertexKey, endVertexKey);
    if (v.size() == 0) { fout << "�ִ� ��ΰ� ����" << endl; cout << "�ִ� ��ΰ� ����" << endl; return InvalidAlgorithm; }
    //�ִܰ�ΰ� ���� �� ������ ��� ���Ƿ� ����
    else {
        int length = v.back();
        v.pop_back();
        fout << "shortest path: ";
        cout << "shortest path: ";
        for (int i = v.size() - 1; i >= 0; i--) { fout << v[i] << " "; cout << v[i] << " "; }//�ڿ��� ���� ����ϸ� ��ε�

        int* vv = &v[0];
        sort(con, vv, v.size());

        fout << endl << "path length: " << length << endl;
        cout << endl << "path length: " << length << endl;
        //course�κ� ���
        compression(v);//v���� �ִܰ�� ������ ����Ǿ��ִ�.
    }

    return Success;
}

/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Bellman-Ford
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::NegativeCycleDetected if exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{

    if (m_graph.head() == NULL) { return GraphNotExist; }
    if (m_graph.FindVertex(startVertexKey) == NULL || m_graph.FindVertex(endVertexKey) == NULL) { return InvalidVertexKey; }
    
    vector<int> v = m_graph.FindShortestPathBellmanFord(startVertexKey, endVertexKey);
    if (v.size() == 0) { return NegativeCycleDetected; } //���� weight�� ����Ŭ�� �ֳ� Ȯ��
    
    else {
        int length = v.back();
        v.pop_back();
        fout << "shortest path: ";
        cout << "shortest path: ";
        for (int i = v.size() - 1; i >= 0; i--) { fout << v[i] << " "; cout << v[i] << " "; }//�ڿ��� ���� ����ϸ� ��ε�

        int* vv = &v[0];
        sort(con, vv,v.size());
        
        fout << endl << "path length: " << length << endl;
        cout << endl << "path length: " << length << endl;
        //course�κ� ���
        compression(v);//v���� �ִܰ�� ������ ����Ǿ��ִ�.
    }
    return Success;
}

Result Manager::FindShortestPathFloyd() {
    if (m_graph.head() == NULL) { return GraphNotExist; }
    vector<vector<int>> v = m_graph.FindShortestPathFloyd();
    if (v.size() == 0) { return NegativeCycleDetected; }
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v.size(); j++) {
            cout << v[i][j] << " ";
            fout << v[i][j] << " ";
        }
        cout << endl;
        fout << endl;
    }
    return Success;
}

Result Manager::RabinKarpCompare(string ComparedString, string CompareString)
{
    int bs = ComparedString.length(), bh = 0;//big length,big hash=0
    int ws = CompareString.length(), wh = 0;//word length, word hash=0
    int power = 1, power_prev = 1, find = 0;
    for (int i = 0; i <= bs - ws; i++) {//ū ���ڿ� ũ��- ã�� �ܾ�ũ�� ��ŭ �ݺ�
        if (i == 0) {
            for (int k = 1; k <= ws; k++) {
                bh = bh + ComparedString[ws - k] * power;//word�� ũ�⸸ŭ �ڿ��� ������ ���鼭 ���ϱ�
                wh = wh + CompareString[ws - k] * power;//word�� �ڿ��� ������ ���ϱ�
                if (k < ws) { power = power * 2; }
            }
        }
        else {
            bh = (bh - ComparedString[i - 1] * power) * 2 + ComparedString[i - 1 + ws];//������ ���ְ� ������ ���ϱ�
        }
        if (bh == wh) {
            for (int q = 0; q < ws; q++) {
                if (ComparedString[i + q] != CompareString[q]) { find = 0; break; }
                else { find += 1; }//������ 1�� �����ش�.
            }
            if (find != 0) {
                return Success;
            }
        }
    }
    return LoadFileNotExist;//ã�� ���� ���� �� ��ȯ �ϴ� ������ ��� LoadFileNotExist�� ����ߴ�.
}


Result Manager::Update() {
     //1. ���� �̸� 5�� �̻� ���� ����(�Ҽ��� �ø��� 10%���� �ϰ� ����.)
    int len1 = 0,  col = 0;
    int m_vSize = m_graph.Size();
    double data = 0, de = 0;
    string a1, b1, temp;
    Vertex* curv = m_graph.head();//head vertex���� ����
    if (curv == NULL) { return FaildtoUpdatePath; }//���� ���� ������ ��
    Vertex* cmpv = m_graph.head()->GetNext();
    if (cmpv == NULL) { return Success; }//������Ʈ �Ұ� ������ ������.

    for (int i = 0; i < m_vSize - 1; i++) {//���� vertex
        for (int j = i + 1; j < m_vSize; j++) {//�񱳵� vertex
            a1 = curv->GetName(); //curv�� �����̸�
            b1 = cmpv->GetName(); //cmpv�� �����̸�
            transform(a1.begin(), a1.end(), a1.begin(), ::tolower);//���ڿ� ��ü �ҹ��ڷ� �ٲٱ�(��ҹ��� ����x)
            transform(b1.begin(), b1.end(), b1.begin(), ::tolower);//���ڿ� ��ü �ҹ��ڷ� �ٲٱ�(��ҹ��� ����x)
            len1 = a1.length(); //curv�� �����̸� ����
            col = 0;
            
            for (int l = 0; len1-l>=5; l++) {
                temp = a1.substr(l, 5);//a1�� l��° ���� 5���� temp�� ���� 
                if (Success == RabinKarpCompare(b1, temp)) {//temp�� b1�� ��
                    if (curv->FindEdge(j) != NULL) {//curv�� edge�� j�ΰ��� edge�� �ִٸ� ����
                        data = curv->FindEdge(j)->GetWeight();//weight double������ �ٲ�
                        if (curv->FindprevEdge(j) != NULL) {//head�� �ƴ� �� �����ϴ� edge�� �� �� ����
                            curv->FindprevEdge(j)->SetNext(curv->FindEdge(j)->GetNext());//�����Ǵ� edge���Ͱ� �����Ǵ� edge ���� ���� ����
                        }
                        else {//head�� �� head �ٲ��ֱ�
                            curv->sethead(curv->GetHeadOfEdge()->GetNext());
                        }
                        delete curv->FindEdge(j);//edge����
                        curv->sizedown();//size 1 ����
                        if (data > 0) { curv->AddEdge(cmpv->GetKey(), ceil(data * 0.9)); }//data�� ����� �� ���ο� edge����
                        else if(data<0){ curv->AddEdge(cmpv->GetKey(), ceil(data * 1.1)); }//data�� ������ �� ���ο� edge����
                        col = 1;//���� ���ڰ� ������ vertex�� �Ѿ���Ѵ�(���� ���ڿ����� �� ���� ���� �־)
                    }
                    if (cmpv->FindEdge(i) != NULL) {//cmpv�� edge�� i�ΰ��� edge�� �ִٸ� ����
                        data = cmpv->FindEdge(i)->GetWeight();//weight double������ �ٲ�
                        if (cmpv->FindprevEdge(i) != NULL) {//head�� �ƴ� �� �����ϴ� edge�� �� �� ����
                            cmpv->FindprevEdge(i)->SetNext(cmpv->FindEdge(i)->GetNext());//�����Ǵ� edge���Ͱ� �����Ǵ� edge ���� ���� ����
                        }
                        else {//head�� �� head �ٲ��ֱ�
                            cmpv->sethead(cmpv->GetHeadOfEdge()->GetNext());
                        }
                        delete cmpv->FindEdge(i);//edge����
                        cmpv->sizedown();//size 1 ����
                        if (data > 0) { cmpv->AddEdge(curv->GetKey(), ceil(data * 0.9)); }//data�� ����� �� ���ο� edge����
                        else if(data<0){ cmpv->AddEdge(curv->GetKey(), ceil(data * 1.1)); }//data�� ������ �� ���ο� edge����
                        col = 1;//���� ���ڰ� ������ vertex�� �Ѿ���Ѵ�(���� ���ڿ����� �� ���� ���� �־)
                    }
                    if (col == 1) { break; }//���� vertex
                }
            }
            cmpv = cmpv->GetNext(); //���ϴ� vertex �̵�
        }
        curv = curv->GetNext();//���� vertex �̵�
        cmpv = curv->GetNext();
    }


    //2. 1���� ���� �̸��� 10���� �����ߴٸ�
    curv = m_graph.head();//head vertex���� ����
    cmpv = m_graph.head()->GetNext();

    for (int i = 0; i < m_vSize - 1; i++) {//���� vertex
        for (int j = i + 1; j < m_vSize; j++) {//�񱳵� vertex
            a1 = curv->GetName(); //curv�� �����̸�
            b1 = cmpv->GetName(); //cmpv�� �����̸�
            transform(a1.begin(), a1.end(), a1.begin(), ::tolower);//���ڿ� ��ü �ҹ��ڷ� �ٲٱ�(��ҹ��� ����x)
            transform(b1.begin(), b1.end(), b1.begin(), ::tolower);//���ڿ� ��ü �ҹ��ڷ� �ٲٱ�(��ҹ��� ����x)
            len1 = a1.length(); //curv�� �����̸� ����
            col = 0;

            for (int l = 0; len1 - l >= 10; l++) {
                temp = a1.substr(l, 10);//a1�� l��° ���� 5���� temp�� ����
                if (Success==RabinKarpCompare(b1, temp)) {//temp�� b1�� ��
                    if (curv->FindEdge(j) != NULL) {//curv�� edge�� j�ΰ��� edge�� �ִٸ� ����
                        data = curv->FindEdge(j)->GetWeight();//weight double������ �ٲ�
                        if (curv->FindprevEdge(j) != NULL) {//head�� �ƴ� �� �����ϴ� edge�� �� �� ����
                            curv->FindprevEdge(j)->SetNext(curv->FindEdge(j)->GetNext());//�����Ǵ� edge���Ͱ� �����Ǵ� edge ���� ���� ����
                        }
                        else {//head�� �� head �ٲ��ֱ�
                            curv->sethead(curv->GetHeadOfEdge()->GetNext());
                        }
                        delete curv->FindEdge(j);//edge����
                        curv->sizedown();//size 1 ����
                        if (data > 0) { curv->AddEdge(cmpv->GetKey(), ceil(data * 0.9)); }//data�� ����� �� ���ο� edge����
                        else if (data < 0) { curv->AddEdge(cmpv->GetKey(), ceil(data * 1.1)); }//data�� ������ �� ���ο� edge����
                        col = 1;//���� ���ڰ� ������ vertex�� �Ѿ���Ѵ�(���� ���ڿ����� �� ���� ���� �־)
                    }
                    if (cmpv->FindEdge(i) != NULL) {//cmpv�� edge�� i�ΰ��� edge�� �ִٸ� ����
                        data = cmpv->FindEdge(i)->GetWeight();//weight double������ �ٲ�
                        if (cmpv->FindprevEdge(i) != NULL) {//head�� �ƴ� �� �����ϴ� edge�� �� �� ����
                            cmpv->FindprevEdge(i)->SetNext(cmpv->FindEdge(i)->GetNext());//�����Ǵ� edge���Ͱ� �����Ǵ� edge ���� ���� ����
                        }
                        else {//head�� �� head �ٲ��ֱ�
                            cmpv->sethead(cmpv->GetHeadOfEdge()->GetNext());
                        }
                        delete cmpv->FindEdge(i);//edge����
                        cmpv->sizedown();//size 1 ����
                        if (data > 0) { cmpv->AddEdge(curv->GetKey(), ceil(data * 0.9)); }//data�� ����� �� ���ο� edge����
                        else if (data < 0) { cmpv->AddEdge(curv->GetKey(), ceil(data * 1.1)); }//data�� ������ �� ���ο� edge����
                        col = 1;//���� ���ڰ� ������ vertex�� �Ѿ���Ѵ�(���� ���ڿ����� �� ���� ���� �־)
                    }
                    if (col == 1) { break; }//���� vertex
                }
            }
            cmpv = cmpv->GetNext(); //���ϴ� vertex �̵�
        }
        curv = curv->GetNext();//���� vertex �̵�
        cmpv = curv->GetNext();
    }
    

    //3. ���Ǹ��� �� �ܾ� �̻� ���� ����
    curv = m_graph.head();//head vertex���� ����
    cmpv = m_graph.head()->GetNext();

    for (int i = 0; i < m_vSize - 1; i++) {//���� vertex
        for (int j = i + 1; j < m_vSize; j++) {//�񱳵� vertex
            a1 = curv->Getstore(); //curv�� ���Ǹ�
            b1 = cmpv->Getstore(); //cmpv�� ���Ǹ�
            transform(a1.begin(), a1.end(), a1.begin(), ::tolower);//���ڿ� ��ü �ҹ��ڷ� �ٲٱ�(��ҹ��� ����x)
            transform(b1.begin(), b1.end(), b1.begin(), ::tolower);//���ڿ� ��ü �ҹ��ڷ� �ٲٱ�(��ҹ��� ����x)
            len1 = a1.length(); //curv�� ���Ǹ� ����
            col = 0;
            
            istringstream iss(a1);
            string token;
            while (getline(iss, token, ' ')) {
                if(Success == RabinKarpCompare(b1,token)){//���Ǹ� ���� �ܾ �ִٸ�

                    if (curv->FindEdge(j) != NULL) {//curv�� edge�� j�ΰ��� edge�� �ִٸ� ����
                        data = curv->FindEdge(j)->GetWeight();//weight double������ �ٲ�
                        if (curv->FindprevEdge(j) != NULL) {//head�� �ƴ� �� �����ϴ� edge�� �� �� ����
                            curv->FindprevEdge(j)->SetNext(curv->FindEdge(j)->GetNext());//�����Ǵ� edge���Ͱ� �����Ǵ� edge ���� ���� ����
                        }
                        else {//head�� �� head �ٲ��ֱ�
                            curv->sethead(curv->GetHeadOfEdge()->GetNext());
                        }
                        delete curv->FindEdge(j);//edge����
                        curv->sizedown();//size 1 ����
                        if (data > 0) { curv->AddEdge(cmpv->GetKey(), ceil(data * 0.8)); }//data�� ����� �� ���ο� edge����
                        else if (data < 0) { curv->AddEdge(cmpv->GetKey(), ceil(data * 1.2)); }//data�� ������ �� ���ο� edge����
                        col = 1;//���� ���ڰ� ������ vertex�� �Ѿ���Ѵ�(���� ���ڿ����� �� ���� ���� �־)
                    }
                    if (cmpv->FindEdge(i) != NULL) {//cmpv�� edge�� i�ΰ��� edge�� �ִٸ� ����
                        data = cmpv->FindEdge(i)->GetWeight();//weight double������ �ٲ�
                        if (cmpv->FindprevEdge(i) != NULL) {//head�� �ƴ� �� �����ϴ� edge�� �� �� ����
                            cmpv->FindprevEdge(i)->SetNext(cmpv->FindEdge(i)->GetNext());//�����Ǵ� edge���Ͱ� �����Ǵ� edge ���� ���� ����
                        }
                        else {//head�� �� head �ٲ��ֱ�
                            cmpv->sethead(cmpv->GetHeadOfEdge()->GetNext());
                        }
                        delete cmpv->FindEdge(i);//edge����
                        cmpv->sizedown();//size 1 ����
                        if (data > 0) { cmpv->AddEdge(curv->GetKey(), ceil(data * 0.8)); }//data�� ����� �� ���ο� edge����
                        else if (data < 0) { cmpv->AddEdge(curv->GetKey(), ceil(data * 1.2)); }//data�� ������ �� ���ο� edge����
                        col = 1;//���� ���ڰ� ������ vertex�� �Ѿ���Ѵ�(���� ���ڿ����� �� ���� ���� �־)
                    }
                }
                if (col == 1) { break; }
            }
            cmpv = cmpv->GetNext(); //���ϴ� vertex �̵�
        }
        curv = curv->GetNext();//���� vertex �̵�
        cmpv = curv->GetNext();
    }
    return Success;
}


void Manager::sort(string type, int* v,int n) {
    if (type == "quick") {
        //chrono::system_clock::time_point start = chrono::system_clock::now();//���� �ð��� start�� ����
        quick(0, n - 1, v);
       // chrono::system_clock::time_point end = chrono::system_clock::now();//���� �ð��� end�� ����
        //chrono::nanoseconds nano = end - start;
    }

    else if (type == "insert") {
        int val,j;
        //chrono::system_clock::time_point start = chrono::system_clock::now();//���� �ð��� start�� ����
        for (int i = 0; i < n; i++) {
            val = v[i];
            for ( j = i - 1; j >= 0; j--) {
                if (v[j] > val) { v[j + 1] = v[j]; continue; }//���ڸ��� �ϳ��� ���鼭 ���ڸ��� �� ũ�� �ڷ� ������
                break;
            }
            v[j + 1] = val; //�� �ڸ��� key���� �ִ´�.
        }
        //chrono::system_clock::time_point end = chrono::system_clock::now();//���� �ð��� end�� ����
       // chrono::nanoseconds nano = end - start;
    }

    else if (type == "merge") {
        //chrono::system_clock::time_point start = chrono::system_clock::now();//���� �ð��� start�� ����
        merge_sort(v, 0, n - 1);
        //chrono::system_clock::time_point end = chrono::system_clock::now();//���� �ð��� end�� ����
        //chrono::nanoseconds nano = end - start;
    }

    else if (type == "heap") {
        MinHeap<int, int> heap;
        //chrono::system_clock::time_point start = chrono::system_clock::now();//���� �ð��� start�� ����
        for (int i = 0; i < n; i++) {heap.Push(v[i], 0);}
        for (int i = 0; i < n; i++) { v[i] = heap.Top().first; heap.Pop(); }
        //chrono::system_clock::time_point end = chrono::system_clock::now();//���� �ð��� end�� ����
       // chrono::nanoseconds nano = end - start;


    }
    else if (type == "bubble") {
        int temp = 0;
        //chrono::system_clock::time_point start = chrono::system_clock::now();//���� �ð��� start�� ����
        //������������
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (v[j] > v[j + 1]) {
                    temp = v[j];
                    v[j] = v[j + 1];
                    v[j + 1] = temp;
                }
            }
        }
        //chrono::system_clock::time_point end = chrono::system_clock::now();//���� �ð��� end�� ����
       // chrono::nanoseconds nano = end - start;
        
    }
    else if (type == "selection") {
        int min, tmp;
        //chrono::system_clock::time_point start = chrono::system_clock::now();//���� �ð��� start�� ����
        for (int i = 0; i < n - 1; i++) {
            min = i;
            for (int j = i + 1; j < n; j++)
            {
                if (v[min] > v[j]) { min = j; }
                tmp = v[min];
                v[min] = v[i];
                v[i] = tmp;
            }
        }
        //chrono::system_clock::time_point end = chrono::system_clock::now();//���� �ð��� end�� ����
       // chrono::nanoseconds nano = end - start;
    }

    fout << endl << endl << "sorted node: ";
    cout <<endl<<endl<< "sorted node: ";
    for (int i = 0; i < n; i++) { cout << v[i] << " ";fout << v[i] << " "; }
    cout << endl; fout << endl;
}

void Manager::quick(int i, int j, int* v) {
    if (i >= j) { return; }
    int pivot = v[(i + j) / 2], left = i, right = j;

    while (left <= right)
    {
        while (v[left] < pivot) { left++; }
        while (v[right] > pivot) { right--; }
        if (left <= right){
            swap(v[left], v[right]);
            right--;
            left++;
        }
    }

    quick(i, right, v);
    quick(left, j, v);
}

void Manager::merge(int* v, int left, int right) {
    int middle = (left + right) / 2;       //���޹��� left�� right�� �߰����� middle�� ����
    int i = left, j = middle + 1, k = left;//i,k�� ���ʿ��� ����, j�� �߰����� ����
    int temp[200];//�����ϴ� ���� �߰��� �����صδ� �迭

    while (i <= middle) {//i�� �߰����� ���� ��
        if (j > right) { break; }//j�� ������ �̵��ϸ� ��
        if (v[i] <= v[j]) {//���ʰ� �߰� ���� ��
            temp[k] = v[i];
            k += 1;
            i += 1;
        }
        else {
            temp[k] = v[j];
            k += 1;
            j += 1;
        }
    }
    if (i > middle) { for (int q = j; q <= right; q++) { temp[k] = v[q]; k += 1; } }
    else { for (int q = i; q <= middle; q++) { temp[k] = v[q]; k += 1; } }
    for (int q = left; q <= right; q++) { v[q] = temp[q]; }
}

void Manager::merge_sort(int* v, int left, int right) {
    int middle;
    if (left >= right) { return; }
    middle = (left + right) / 2;
    merge_sort(v, left, middle);       //��͵���
    merge_sort(v, middle + 1, right);  //��͵���
    merge(v, left, right);
}

void Manager::compression(vector<int> v) {
    string s;
    //1.2���̻� ���ڿ� ����� ���� �� ���ڿ� ����
    //s�� ���ڿ� �����ؼ� �־��ֱ�
    for (int i = 0; i < v.size(); i++) {s.append(m_graph.FindVertex(v[i])->ns);}
    
    string c = s;//c�� s����
    transform(s.begin(), s.end(), s.begin(), tolower);//s�� �ҹ��ڷ� �ٲ۴�.
    cout << c << endl;

    int answer = 0;//answer�� ������ �ܾ����
    int bre = 0, start_point = 0;


    for (int i = 1; i <= s.length() / 2; i++) {//���ڿ� ������ �ݸ� ����.
        bre = 0;
        //���ڿ��� ��ü ���鼭 �ݺ�
        for (int j = 0; j < s.length(); j++) {//���ڿ� ��ü�� ����, j�� 0����
            //�κ� ���ϱ�
            for (int z = i; j + z + i <= s.length(); z++) {//count=0,
                //j��°���� i��ŭ���ڿ� j+z�������� i��° ���ڰ� ������ count 1����
                if (Success==RabinKarpCompare(s.substr(j, i), s.substr(j + z, i))) {
                    answer = i; bre = 1; start_point = j;
                    break;
                }
            }
            if (bre == 1) { break; }
        }
    }

    int i = answer, gap = 0;
    cout << answer<<endl;
    bre = 0;
    //z�� ������ ���� ���� ��ġ+���� ���� ����(ù ���๮�� ���� ��ġ���� Ȯ��)
    for (int z = i + start_point; z + i <= s.length(); z++) {
        if (Success==RabinKarpCompare(s.substr(start_point, i), s.substr(z, i))) {
            c.erase(z - gap, i);//�ҹ��ڷ� �ٲ��� ���� ���ڿ����� ����
            gap = gap + i;//�ҹ��ڷ� �ٲ��� ���� ���ڿ��� ���� ���ϱ� ������ gap���� ���� ���̱�
            z += i;//������ ������ ���ڰ� ������� ������ �ҹ��� ���ڿ����� �׸�ŭ �̵�
            if (bre == 0) { gap -= 1; c.insert(start_point + i, 1, '*'); }//�� �� ���ڿ� *���̱�
            bre = 1;
        }
    }

    
    //2. shop, class, academy�� 1���� ������ �ϱ�
    for (int q = 0; q < 3; q++) {//�� 3�� �ݺ� shop->class->academy
        s = c;
        transform(s.begin(), s.end(), s.begin(), tolower);//s�� �ҹ��ڷ� �ٲ۴�.
        string du="shop";
        if (q == 1) { du = "class"; }
        else if (q == 2) { du = "academy"; }
        int wn = du.length(), col = 0, gap = 0;
        for (int j = 0; j+wn <= s.length(); j++) {//���ڿ� ��ü�� ����, j�� 0����
            if (Success == RabinKarpCompare(s.substr(j, wn), du)) {
                col += 1;
                if(col!=1){
                    c.erase(j - gap, wn);//�ҹ��ڷ� �ٲ��� ���� ���ڿ����� ����
                    gap = gap + wn;//�ҹ��ڷ� �ٲ��� ���� ���ڿ��� ���� ���ϱ� ������ gap���� ���� ���̱�
                }
            }
        }
    }

    fout << endl << "Course : " << c << endl;
    cout << endl << "Course : " << c << endl;
    return;
   

}