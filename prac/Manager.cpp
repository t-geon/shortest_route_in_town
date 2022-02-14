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
        else if (cmd[0] == '/' && cmd[1] == '/') { continue; }// "If it is "//", the command is not read.
        char* tmp, * tmm;
        strtok_s(cmd, " ", &tmp);//Saved in the character cmd in front of the "" standard, and the remaining characters in the address of tmp
        
        //select LOAD
        if (!strcmp(cmd, "LOAD")) {
            cout << "========LOAD========" << endl<<endl;
            fout << "========LOAD========" << endl << endl;
            re = Load(tmp);
            if (re== Success) { fout << "Success"<<endl ; cout << "Success" << endl; }
            else { fout << "LoadFileNotExist" << endl ; cout << "LoadFileNotExist" << endl; }
            PrintError(re);
        }
        
        //select PRINT
        else if (!strcmp(cmd, "PRINT")) {
            cout << "========PRINT========" << endl<<endl;
            fout << "========PRINT========" << endl << endl;
            re = Print();
            if (re == GraphNotExist) { fout << "GraphNotExist" << endl; cout << "GraphNotExist" << endl; }

            PrintError(re);
        }

        //select UPDATE 
        else if (!strcmp(cmd, "UPDATE")) {
            cout << "========UPDATE========" << endl << endl;
            fout << "========UPDATE========" << endl << endl;
            re = Update();
            if (re == Success) { fout << "Success" << endl; cout << "Success" << endl; }
            else { fout << "FaildtoUpdatePath" << endl; cout<<"FaildtoUpdatePath" << endl; }

            PrintError(re);
        }

        //select BFS
        else if (!strcmp(cmd, "BFS")) {
            cout << "========BFS========" << endl<<endl;
            fout << "========BFS========" << endl << endl;
            
            //Insufficient command arguments
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

        //select DIJKSTRA
        else if (!strcmp(cmd, "DIJKSTRA")) {
            cout << "========DIJKSTRA========" << endl << endl;
            fout << "========DIJKSTRA========" << endl << endl;
            
            //Insufficient command arguments
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

        //select DIJKSTRAMIN
        else if (!strcmp(cmd, "DIJKSTRAMIN")) {
            cout << "========DIJKSTRAMIN========" << endl << endl;
            fout << "========DIJKSTRAMIN========" << endl << endl;
            
            //Insufficient command arguments
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

        //select BELLMANFORD
        else if (!strcmp(cmd, "BELLMANFORD")) {
            cout << "========BELLMANFORD========" << endl << endl;
            fout << "========BELLMANFORD========" << endl << endl;
            
            //Insufficient command arguments
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

        //select FLOYD
        else if (!strcmp(cmd, "FLOYD")) {
            cout << "========FLOYD========" << endl<<endl;
            fout << "========FLOYD========" << endl << endl;
            re = FindShortestPathFloyd();
            if(re== NegativeCycleDetected){ fout << "NegativeCycleDetected" << endl; cout << "NegativeCycleDetected" << endl; }
            else if(re==GraphNotExist){ fout << "GraphNotExist" << endl; cout << "GraphNotExist" << endl; }
            PrintError(re);
        }

        //select CONFIG
        else if (!strcmp(cmd, "CONFIG")) {
            cout << "========CONFIG LOG========" << endl<<endl;
            
            //Insufficient command arguments
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

// <summary>
// make a graph
// </summary>
//
// <param name="filepath">
// the filepath to read to make the graph
// </param>
//
// <returns>
// Result::Success if load is successful.
// Result::LoadFileNotExist if file is not exist.
// </returns>
Result Manager::Load(const char* filepath)
{
    ifstream fi;
    fi.open(filepath);
    if (!fi) {return LoadFileNotExist; }

    int vnum = 0, gsize = 0;
    string name, store,ns1;//Store, owner, signboard name

    //read first line
    char cmd1[100];
    fi.getline(cmd1, 100);
    gsize = stoi(cmd1);// graph size update


    while (!fi.eof())
    {
        fi.getline(cmd1, 100);//Read 1 line of command.txt
        if (!strcmp(cmd1, "")) { continue; }//Code to repeat the number of lines
        char* tmp1, * tmm1, * cmp2;
        strtok_s(cmd1, "/", &tmp1);//cmd1 is the string before / (owner name, sign) tmp is the string after / (cost)
        
        ns1 = string(cmd1);
        ns1.erase(ns1.size() - 1, 1);
        strtok_s(cmd1, "'", &cmp2);//cmd1 is the name, cmp1 is the s sign name
        name = string(cmd1);
        strtok_s(cmp2, " ", &cmp2);//cmp1 is the sign name
        store = string(cmp2);

        m_graph.AddVertex(vnum);
        m_graph.FindVertex(vnum)->ns = ns1;//Save sign name
        m_graph.AddName(vnum, name);//save name
        m_graph.Addstore(vnum, store);

        for (int i = 0; i < gsize; i++) {//add edge
            tmm1 = strtok_s(tmp1, " ", &tmp1);//tmm is the string before " " tmp is the string after " "
            if (stoi(tmm1) != 0) { m_graph.AddEdge(vnum, i, stoi(tmm1)); }//Add edge to vnumth vertex
        }
        vnum += 1;
    }
    return Success;
}


// <summary>
// print out the graph as matrix form
// </summary>
//
// <returns>
// Result::Success if the printing is successful
// Result::GraphNotExist if there is no graph
// </returns>
Result Manager::Print()
{
    if (m_graph.head() == NULL) { return GraphNotExist; }
    else { m_graph.Print(fout); return Success; }
}



// <summary>
// find the path from startVertexKey to endVertexKey with BFS (stack and queue)
// </summary>
//
// <param name="startVertexKey">
// the start vertex key
// </param>
// <param name="endVertexKey">
// the end vertex key
// </param>
//
// <returns>
// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
// Result::Success otherwise.
// </returns>
Result Manager::FindPathBfs(int startVertexKey, int endVertexKey)
{
    if(m_graph.head() == NULL) { return GraphNotExist; }
    if (m_graph.IsNegativeEdge() == 1) { return InvalidAlgorithm; }
    if (m_graph.FindVertex(startVertexKey) == NULL || m_graph.FindVertex(endVertexKey) == NULL) { return InvalidVertexKey; }
    vector<int> v = m_graph.FindPathBfs(startVertexKey, endVertexKey);
    if (v.size() == 0) {
        fout << "there is no shortest path" << endl; 
        cout << "there is no shortest path" << endl; return InvalidAlgorithm; }
    //Error setting when there is no shortest path
    else {
        int length = v.back();
        v.pop_back();
        cout << "shortest path: ";
        fout << "shortest path: ";
        for (int i = v.size() - 1; i >= 0; i--) { 
            fout << v[i] << " ";
            cout << v[i] << " "; }//If you output from the back, it will be routed.
       
        int* vv = &v[0];
        sort(con, vv, v.size());

        fout << endl << "path length: " << length << endl;
        cout << endl<<"path length: "<<length<<endl;
        //output of course part
        compression(v);//v is stored in the order of the shortest path.
    }
    return Success;
}

// <summary>
// find the shortest path from startVertexKey to endVertexKey with Dijkstra using std::set
// </summary>
//
// <param name="startVertexKey">
// the start vertex key
// </param>
// <param name="endVertexKey">
// the end vertex key
// </param>
//
// <returns>
// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
// Result::Success otherwise.
// </returns>
Result Manager::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
    if (m_graph.head() == NULL) { return GraphNotExist; }
    if (m_graph.IsNegativeEdge() == 1) { return InvalidAlgorithm; }
    if (m_graph.FindVertex(startVertexKey) == NULL || m_graph.FindVertex(endVertexKey) == NULL) { return InvalidVertexKey; }
    vector<int> v = m_graph.FindShortestPathDijkstraUsingSet(startVertexKey, endVertexKey);
    if (v.size() == 0) { fout << "there is no shortest path" << endl; cout << "there is no shortest path" << endl; return InvalidAlgorithm; }
    else {
        int length = v.back();
        v.pop_back();
        fout << "shortest path: "; cout << "shortest path: ";
        for (int i = v.size() - 1; i >= 0; i--) { fout << v[i] << " "; cout << v[i] << " "; }

        int* vv = &v[0];
        sort(con, vv, v.size());

        fout << endl << "path length: " << length << endl;
        cout << endl << "path length: " << length << endl;

        compression(v);
    }
    return Success;
}

// <summary>
// find the shortest path from startVertexKey to endVertexKey with Dijkstra using MinHeap
// </summary>
//
// <param name="startVertexKey">
/// the start vertex key
// </param>
// <param name="endVertexKey">
// the end vertex key
// </param>
//
// <returns>
// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
// Result::Success otherwise.
// </returns>
Result Manager::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey)
{
    if (m_graph.head() == NULL) { return GraphNotExist; }
    if (m_graph.IsNegativeEdge() == 1) { return InvalidAlgorithm; }
    if (m_graph.FindVertex(startVertexKey) == NULL || m_graph.FindVertex(endVertexKey) == NULL) { return InvalidVertexKey; }
    
    vector<int> v = m_graph.FindShortestPathDijkstraUsingMinHeap(startVertexKey, endVertexKey);
    if (v.size() == 0) { fout << "there is no shortest path" << endl; cout << "there is no shortest path" << endl; return InvalidAlgorithm; }
    else {
        int length = v.back();
        v.pop_back();
        fout << "shortest path: ";
        cout << "shortest path: ";
        for (int i = v.size() - 1; i >= 0; i--) { fout << v[i] << " "; cout << v[i] << " "; }

        int* vv = &v[0];
        sort(con, vv, v.size());

        fout << endl << "path length: " << length << endl;
        cout << endl << "path length: " << length << endl;
        
        compression(v);
    }
    return Success;
}

// <summary>
// find the shortest path from startVertexKey to endVertexKey with Bellman-Ford
// </summary>
//
// <param name="startVertexKey">
// the start vertex key
// </param>
// <param name="endVertexKey">
// the end vertex key
// </param>
//
// <returns>
// Result::InvalidVertexKey or Result::GraphNotExist or Result::NegativeCycleDetected if exception has occurred.
// Result::Success otherwise.
// </returns>
Result Manager::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{

    if (m_graph.head() == NULL) { return GraphNotExist; }
    if (m_graph.FindVertex(startVertexKey) == NULL || m_graph.FindVertex(endVertexKey) == NULL) { return InvalidVertexKey; }
    
    vector<int> v = m_graph.FindShortestPathBellmanFord(startVertexKey, endVertexKey);
    if (v.size() == 0) { return NegativeCycleDetected; } //음수 weight인 싸이클이 있나 확인
    
    else {
        int length = v.back();
        v.pop_back();
        fout << "shortest path: ";
        cout << "shortest path: ";
        for (int i = v.size() - 1; i >= 0; i--) { fout << v[i] << " "; cout << v[i] << " "; }//뒤에서 부터 출력하면 경로됨

        int* vv = &v[0];
        sort(con, vv,v.size());
        
        fout << endl << "path length: " << length << endl;
        cout << endl << "path length: " << length << endl;
        //course부분 출력
        compression(v);//v에는 최단경로 순으로 저장되어있다.
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
    for (int i = 0; i <= bs - ws; i++) {//큰 문자열 크기- 찾는 단어크기 만큼 반복
        if (i == 0) {
            for (int k = 1; k <= ws; k++) {
                bh = bh + ComparedString[ws - k] * power;//word의 크기만큼 뒤에서 앞으로 오면서 더하기
                wh = wh + CompareString[ws - k] * power;//word도 뒤에서 앞으로 더하기
                if (k < ws) { power = power * 2; }
            }
        }
        else {
            bh = (bh - ComparedString[i - 1] * power) * 2 + ComparedString[i - 1 + ws];//이전꺼 빼주고 다음꺼 더하기
        }
        if (bh == wh) {
            for (int q = 0; q < ws; q++) {
                if (ComparedString[i + q] != CompareString[q]) { find = 0; break; }
                else { find += 1; }//같으면 1을 더해준다.
            }
            if (find != 0) {
                return Success;
            }
        }
    }
    return LoadFileNotExist;//찾는 것이 없을  반환 하는 오류가 없어서 LoadFileNotExist로 대신했다.
}


Result Manager::Update() {
     //1. 주인 이름 5개 이상 같은 가게(소수점 올림을 10%에서 하고 뺐다.)
    int len1 = 0,  col = 0;
    int m_vSize = m_graph.Size();
    double data = 0, de = 0;
    string a1, b1, temp;
    Vertex* curv = m_graph.head();//head vertex에서 시작
    if (curv == NULL) { return FaildtoUpdatePath; }//비교할 값이 없으면 끝
    Vertex* cmpv = m_graph.head()->GetNext();
    if (cmpv == NULL) { return Success; }//업데이트 할게 없으면 끝난다.

    for (int i = 0; i < m_vSize - 1; i++) {//기준 vertex
        for (int j = i + 1; j < m_vSize; j++) {//비교될 vertex
            a1 = curv->GetName(); //curv의 주인이름
            b1 = cmpv->GetName(); //cmpv의 주인이름
            transform(a1.begin(), a1.end(), a1.begin(), ::tolower);//문자열 전체 소문자로 바꾸기(대소문자 구분x)
            transform(b1.begin(), b1.end(), b1.begin(), ::tolower);//문자열 전체 소문자로 바꾸기(대소문자 구분x)
            len1 = a1.length(); //curv의 주인이름 길이
            col = 0;
            
            for (int l = 0; len1-l>=5; l++) {
                temp = a1.substr(l, 5);//a1의 l번째 부터 5글자 temp에 저장 
                if (Success == RabinKarpCompare(b1, temp)) {//temp와 b1을 비교
                    if (curv->FindEdge(j) != NULL) {//curv의 edge에 j로가는 edge가 있다면 수정
                        data = curv->FindEdge(j)->GetWeight();//weight double형으로 바꿈
                        if (curv->FindprevEdge(j) != NULL) {//head가 아닐 때 삭제하는 edge의 앞 뒤 연결
                            curv->FindprevEdge(j)->SetNext(curv->FindEdge(j)->GetNext());//삭제되는 edge전것과 삭제되는 edge 다음 것을 연결
                        }
                        else {//head일 때 head 바꿔주기
                            curv->sethead(curv->GetHeadOfEdge()->GetNext());
                        }
                        delete curv->FindEdge(j);//edge삭제
                        curv->sizedown();//size 1 감소
                        if (data > 0) { curv->AddEdge(cmpv->GetKey(), ceil(data * 0.9)); }//data가 양수일 때 새로운 edge생성
                        else if(data<0){ curv->AddEdge(cmpv->GetKey(), ceil(data * 1.1)); }//data가 음수일 때 새로운 edge생성
                        col = 1;//같은 문자가 있으면 vertex를 넘어가야한다(같은 문자열에서 또 같을 수도 있어서)
                    }
                    if (cmpv->FindEdge(i) != NULL) {//cmpv의 edge에 i로가는 edge가 있다면 수정
                        data = cmpv->FindEdge(i)->GetWeight();//weight double형으로 바꿈
                        if (cmpv->FindprevEdge(i) != NULL) {//head가 아닐 때 삭제하는 edge의 앞 뒤 연결
                            cmpv->FindprevEdge(i)->SetNext(cmpv->FindEdge(i)->GetNext());//삭제되는 edge전것과 삭제되는 edge 다음 것을 연결
                        }
                        else {//head일 때 head 바꿔주기
                            cmpv->sethead(cmpv->GetHeadOfEdge()->GetNext());
                        }
                        delete cmpv->FindEdge(i);//edge삭제
                        cmpv->sizedown();//size 1 감소
                        if (data > 0) { cmpv->AddEdge(curv->GetKey(), ceil(data * 0.9)); }//data가 양수일 때 새로운 edge생성
                        else if(data<0){ cmpv->AddEdge(curv->GetKey(), ceil(data * 1.1)); }//data가 음수일 때 새로운 edge생성
                        col = 1;//같은 문자가 있으면 vertex를 넘어가야한다(같은 문자열에서 또 같을 수도 있어서)
                    }
                    if (col == 1) { break; }//다음 vertex
                }
            }
            cmpv = cmpv->GetNext(); //비교하는 vertex 이동
        }
        curv = curv->GetNext();//기준 vertex 이동
        cmpv = curv->GetNext();
    }


    //2. 1적용 이후 이름이 10글자 동일했다면
    curv = m_graph.head();//head vertex에서 시작
    cmpv = m_graph.head()->GetNext();

    for (int i = 0; i < m_vSize - 1; i++) {//기준 vertex
        for (int j = i + 1; j < m_vSize; j++) {//비교될 vertex
            a1 = curv->GetName(); //curv의 주인이름
            b1 = cmpv->GetName(); //cmpv의 주인이름
            transform(a1.begin(), a1.end(), a1.begin(), ::tolower);//문자열 전체 소문자로 바꾸기(대소문자 구분x)
            transform(b1.begin(), b1.end(), b1.begin(), ::tolower);//문자열 전체 소문자로 바꾸기(대소문자 구분x)
            len1 = a1.length(); //curv의 주인이름 길이
            col = 0;

            for (int l = 0; len1 - l >= 10; l++) {
                temp = a1.substr(l, 10);//a1의 l번째 부터 5글자 temp에 저장
                if (Success==RabinKarpCompare(b1, temp)) {//temp와 b1을 비교
                    if (curv->FindEdge(j) != NULL) {//curv의 edge에 j로가는 edge가 있다면 수정
                        data = curv->FindEdge(j)->GetWeight();//weight double형으로 바꿈
                        if (curv->FindprevEdge(j) != NULL) {//head가 아닐 때 삭제하는 edge의 앞 뒤 연결
                            curv->FindprevEdge(j)->SetNext(curv->FindEdge(j)->GetNext());//삭제되는 edge전것과 삭제되는 edge 다음 것을 연결
                        }
                        else {//head일 때 head 바꿔주기
                            curv->sethead(curv->GetHeadOfEdge()->GetNext());
                        }
                        delete curv->FindEdge(j);//edge삭제
                        curv->sizedown();//size 1 감소
                        if (data > 0) { curv->AddEdge(cmpv->GetKey(), ceil(data * 0.9)); }//data가 양수일 때 새로운 edge생성
                        else if (data < 0) { curv->AddEdge(cmpv->GetKey(), ceil(data * 1.1)); }//data가 음수일 때 새로운 edge생성
                        col = 1;//같은 문자가 있으면 vertex를 넘어가야한다(같은 문자열에서 또 같을 수도 있어서)
                    }
                    if (cmpv->FindEdge(i) != NULL) {//cmpv의 edge에 i로가는 edge가 있다면 수정
                        data = cmpv->FindEdge(i)->GetWeight();//weight double형으로 바꿈
                        if (cmpv->FindprevEdge(i) != NULL) {//head가 아닐 때 삭제하는 edge의 앞 뒤 연결
                            cmpv->FindprevEdge(i)->SetNext(cmpv->FindEdge(i)->GetNext());//삭제되는 edge전것과 삭제되는 edge 다음 것을 연결
                        }
                        else {//head일 때 head 바꿔주기
                            cmpv->sethead(cmpv->GetHeadOfEdge()->GetNext());
                        }
                        delete cmpv->FindEdge(i);//edge삭제
                        cmpv->sizedown();//size 1 감소
                        if (data > 0) { cmpv->AddEdge(curv->GetKey(), ceil(data * 0.9)); }//data가 양수일 때 새로운 edge생성
                        else if (data < 0) { cmpv->AddEdge(curv->GetKey(), ceil(data * 1.1)); }//data가 음수일 때 새로운 edge생성
                        col = 1;//같은 문자가 있으면 vertex를 넘어가야한다(같은 문자열에서 또 같을 수도 있어서)
                    }
                    if (col == 1) { break; }//다음 vertex
                }
            }
            cmpv = cmpv->GetNext(); //비교하는 vertex 이동
        }
        curv = curv->GetNext();//기준 vertex 이동
        cmpv = curv->GetNext();
    }
    

    //3. 간판명이 한 단어 이상 같은 가게
    curv = m_graph.head();//head vertex에서 시작
    cmpv = m_graph.head()->GetNext();

    for (int i = 0; i < m_vSize - 1; i++) {//기준 vertex
        for (int j = i + 1; j < m_vSize; j++) {//비교될 vertex
            a1 = curv->Getstore(); //curv의 간판명
            b1 = cmpv->Getstore(); //cmpv의 간판명
            transform(a1.begin(), a1.end(), a1.begin(), ::tolower);//문자열 전체 소문자로 바꾸기(대소문자 구분x)
            transform(b1.begin(), b1.end(), b1.begin(), ::tolower);//문자열 전체 소문자로 바꾸기(대소문자 구분x)
            len1 = a1.length(); //curv의 간판명 길이
            col = 0;
            
            istringstream iss(a1);
            string token;
            while (getline(iss, token, ' ')) {
                if(Success == RabinKarpCompare(b1,token)){//간판명에 같은 단어가 있다면

                    if (curv->FindEdge(j) != NULL) {//curv의 edge에 j로가는 edge가 있다면 수정
                        data = curv->FindEdge(j)->GetWeight();//weight double형으로 바꿈
                        if (curv->FindprevEdge(j) != NULL) {//head가 아닐 때 삭제하는 edge의 앞 뒤 연결
                            curv->FindprevEdge(j)->SetNext(curv->FindEdge(j)->GetNext());//삭제되는 edge전것과 삭제되는 edge 다음 것을 연결
                        }
                        else {//head일 때 head 바꿔주기
                            curv->sethead(curv->GetHeadOfEdge()->GetNext());
                        }
                        delete curv->FindEdge(j);//edge삭제
                        curv->sizedown();//size 1 감소
                        if (data > 0) { curv->AddEdge(cmpv->GetKey(), ceil(data * 0.8)); }//data가 양수일 때 새로운 edge생성
                        else if (data < 0) { curv->AddEdge(cmpv->GetKey(), ceil(data * 1.2)); }//data가 음수일 때 새로운 edge생성
                        col = 1;//같은 문자가 있으면 vertex를 넘어가야한다(같은 문자열에서 또 같을 수도 있어서)
                    }
                    if (cmpv->FindEdge(i) != NULL) {//cmpv의 edge에 i로가는 edge가 있다면 수정
                        data = cmpv->FindEdge(i)->GetWeight();//weight double형으로 바꿈
                        if (cmpv->FindprevEdge(i) != NULL) {//head가 아닐 때 삭제하는 edge의 앞 뒤 연결
                            cmpv->FindprevEdge(i)->SetNext(cmpv->FindEdge(i)->GetNext());//삭제되는 edge전것과 삭제되는 edge 다음 것을 연결
                        }
                        else {//head일 때 head 바꿔주기
                            cmpv->sethead(cmpv->GetHeadOfEdge()->GetNext());
                        }
                        delete cmpv->FindEdge(i);//edge삭제
                        cmpv->sizedown();//size 1 감소
                        if (data > 0) { cmpv->AddEdge(curv->GetKey(), ceil(data * 0.8)); }//data가 양수일 때 새로운 edge생성
                        else if (data < 0) { cmpv->AddEdge(curv->GetKey(), ceil(data * 1.2)); }//data가 음수일 때 새로운 edge생성
                        col = 1;//같은 문자가 있으면 vertex를 넘어가야한다(같은 문자열에서 또 같을 수도 있어서)
                    }
                }
                if (col == 1) { break; }
            }
            cmpv = cmpv->GetNext(); //비교하는 vertex 이동
        }
        curv = curv->GetNext();//기준 vertex 이동
        cmpv = curv->GetNext();
    }
    return Success;
}


void Manager::sort(string type, int* v,int n) {
    if (type == "quick") {
        //chrono::system_clock::time_point start = chrono::system_clock::now();//현재 시간을 start에 저장
        quick(0, n - 1, v);
       // chrono::system_clock::time_point end = chrono::system_clock::now();//현재 시간을 end에 저장
        //chrono::nanoseconds nano = end - start;
    }

    else if (type == "insert") {
        int val,j;
        //chrono::system_clock::time_point start = chrono::system_clock::now();//현재 시간을 start에 저장
        for (int i = 0; i < n; i++) {
            val = v[i];
            for ( j = i - 1; j >= 0; j--) {
                if (v[j] > val) { v[j + 1] = v[j]; continue; }//앞자리를 하나씩 보면서 앞자리가 더 크면 뒤로 보내기
                break;
            }
            v[j + 1] = val; //그 자리에 key값을 넣는다.
        }
        //chrono::system_clock::time_point end = chrono::system_clock::now();//현재 시간을 end에 저장
       // chrono::nanoseconds nano = end - start;
    }

    else if (type == "merge") {
        //chrono::system_clock::time_point start = chrono::system_clock::now();//현재 시간을 start에 저장
        merge_sort(v, 0, n - 1);
        //chrono::system_clock::time_point end = chrono::system_clock::now();//현재 시간을 end에 저장
        //chrono::nanoseconds nano = end - start;
    }

    else if (type == "heap") {
        MinHeap<int, int> heap;
        //chrono::system_clock::time_point start = chrono::system_clock::now();//현재 시간을 start에 저장
        for (int i = 0; i < n; i++) {heap.Push(v[i], 0);}
        for (int i = 0; i < n; i++) { v[i] = heap.Top().first; heap.Pop(); }
        //chrono::system_clock::time_point end = chrono::system_clock::now();//현재 시간을 end에 저장
       // chrono::nanoseconds nano = end - start;


    }
    else if (type == "bubble") {
        int temp = 0;
        //chrono::system_clock::time_point start = chrono::system_clock::now();//현재 시간을 start에 저장
        //오름차순정렬
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (v[j] > v[j + 1]) {
                    temp = v[j];
                    v[j] = v[j + 1];
                    v[j + 1] = temp;
                }
            }
        }
        //chrono::system_clock::time_point end = chrono::system_clock::now();//현재 시간을 end에 저장
       // chrono::nanoseconds nano = end - start;
        
    }
    else if (type == "selection") {
        int min, tmp;
        //chrono::system_clock::time_point start = chrono::system_clock::now();//현재 시간을 start에 저장
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
        //chrono::system_clock::time_point end = chrono::system_clock::now();//현재 시간을 end에 저장
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
    int middle = (left + right) / 2;       //전달받은 left와 right의 중간지점 middle에 저장
    int i = left, j = middle + 1, k = left;//i,k는 왼쪽에서 증가, j는 중간에서 증가
    int temp[200];//정렬하는 값을 중간에 저장해두는 배열

    while (i <= middle) {//i가 중간까지 오면 끝
        if (j > right) { break; }//j가 끝까지 이동하면 끝
        if (v[i] <= v[j]) {//왼쪽과 중간 값을 비교
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
    merge_sort(v, left, middle);       //재귀동작
    merge_sort(v, middle + 1, right);  //재귀동작
    merge(v, left, right);
}

void Manager::compression(vector<int> v) {
    string s;
    //1.2번이상 문자열 등장시 가장 긴 문자열 압축
    //s에 문자열 연결해서 넣어주기
    for (int i = 0; i < v.size(); i++) {s.append(m_graph.FindVertex(v[i])->ns);}
    
    string c = s;//c에 s저장
    transform(s.begin(), s.end(), s.begin(), tolower);//s를 소문자로 바꾼다.
    cout << c << endl;

    int answer = 0;//answer는 압축할 단어길이
    int bre = 0, start_point = 0;


    for (int i = 1; i <= s.length() / 2; i++) {//문자열 길이의 반만 돈다.
        bre = 0;
        //문자열을 전체 돌면서 반복
        for (int j = 0; j < s.length(); j++) {//문자열 전체를 돈다, j는 0부터
            //부분 비교하기
            for (int z = i; j + z + i <= s.length(); z++) {//count=0,
                //j번째부터 i만큼문자와 j+z에서부터 i번째 문자가 같으면 count 1증가
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
    //z는 압축할 문자 시작 위치+압축 문자 길이(첫 압축문자 다음 위치부터 확인)
    for (int z = i + start_point; z + i <= s.length(); z++) {
        if (Success==RabinKarpCompare(s.substr(start_point, i), s.substr(z, i))) {
            c.erase(z - gap, i);//소문자로 바뀌지 않은 문자열에서 삭제
            gap = gap + i;//소문자로 바뀌지 않은 문자열은 삭제 안하기 때문에 gap으로 길이 줄이기
            z += i;//삭제를 했으면 문자가 사라지기 때문에 소문자 문자열에서 그만큼 이동
            if (bre == 0) { gap -= 1; c.insert(start_point + i, 1, '*'); }//맨 앞 문자에 *붙이기
            bre = 1;
        }
    }

    
    //2. shop, class, academy는 1번만 나오게 하기
    for (int q = 0; q < 3; q++) {//총 3번 반복 shop->class->academy
        s = c;
        transform(s.begin(), s.end(), s.begin(), tolower);//s를 소문자로 바꾼다.
        string du="shop";
        if (q == 1) { du = "class"; }
        else if (q == 2) { du = "academy"; }
        int wn = du.length(), col = 0, gap = 0;
        for (int j = 0; j+wn <= s.length(); j++) {//문자열 전체를 돈다, j는 0부터
            if (Success == RabinKarpCompare(s.substr(j, wn), du)) {
                col += 1;
                if(col!=1){
                    c.erase(j - gap, wn);//소문자로 바뀌지 않은 문자열에서 삭제
                    gap = gap + wn;//소문자로 바뀌지 않은 문자열은 삭제 안하기 때문에 gap으로 길이 줄이기
                }
            }
        }
    }

    fout << endl << "Course : " << c << endl;
    cout << endl << "Course : " << c << endl;
    return;
}
