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
    if (v.size() == 0) { return NegativeCycleDetected; } //Check if there are cycles with negative weights
    
    else {
        int length = v.back();
        v.pop_back();
        fout << "shortest path: ";
        cout << "shortest path: ";
        for (int i = v.size() - 1; i >= 0; i--) { fout << v[i] << " "; cout << v[i] << " "; }

        int* vv = &v[0];
        sort(con, vv,v.size());
        
        fout << endl << "path length: " << length << endl;
        cout << endl << "path length: " << length << endl;

        compression(v);
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
    for (int i = 0; i <= bs - ws; i++) {//Large string size - repeat as many words as you find
        if (i == 0) {
            for (int k = 1; k <= ws; k++) {
                bh = bh + ComparedString[ws - k] * power;//Add from back to front by the size of a word
                wh = wh + CompareString[ws - k] * power;//Add word from back to front
                if (k < ws) { power = power * 2; }
            }
        }
        else {
            bh = (bh - ComparedString[i - 1] * power) * 2 + ComparedString[i - 1 + ws];//Subtract the previous one and add the next one
        }
        if (bh == wh) {
            for (int q = 0; q < ws; q++) {
                if (ComparedString[i + q] != CompareString[q]) { find = 0; break; }
                else { find += 1; }//If equal, add 1.
            }
            if (find != 0) {
                return Success;
            }
        }
    }
    return LoadFileNotExist;//LoadFileNotExist error occurs when nothing is found
}


Result Manager::Update() {
    int len1 = 0,  col = 0;
    int m_vSize = m_graph.Size();
    double data = 0, de = 0;
    string a1, b1, temp;
    Vertex* curv = m_graph.head();//start at head vertex
    if (curv == NULL) { return FaildtoUpdatePath; }//If there is no value to compare
    Vertex* cmpv = m_graph.head()->GetNext();
    if (cmpv == NULL) { return Success; }  

    for (int i = 0; i < m_vSize - 1; i++) {//standard vertex
        for (int j = i + 1; j < m_vSize; j++) {//vertices to be compared
            a1 = curv->GetName(); //curv's owner name
            b1 = cmpv->GetName(); //cmpv owner name
            transform(a1.begin(), a1.end(), a1.begin(), ::tolower);//Convert entire string to lowercase (case sensitive x)
            transform(b1.begin(), b1.end(), b1.begin(), ::tolower);//Convert entire string to lowercase (case sensitive x)
            len1 = a1.length(); //length of curv's hostname
            col = 0;
            
            for (int l = 0; len1-l>=5; l++) {
                temp = a1.substr(l, 5);//Stored in temp for 5 characters from the lth of a1
                if (Success == RabinKarpCompare(b1, temp)) {//compare temp and b1
                    if (curv->FindEdge(j) != NULL) {//Fix if the edge of the curv has an edge going to j
                        data = curv->FindEdge(j)->GetWeight();//Convert to weight double
                        if (curv->FindprevEdge(j) != NULL) {//Concatenate before and after the edge to be deleted when it is not the head
                            curv->FindprevEdge(j)->SetNext(curv->FindEdge(j)->GetNext());//Connecting the front and back of the edge to be deleted
                        }
                        else {
                            curv->sethead(curv->GetHeadOfEdge()->GetNext());
                        }
                        delete curv->FindEdge(j);
                        curv->sizedown();
                        if (data > 0) { curv->AddEdge(cmpv->GetKey(), ceil(data * 0.9)); }
                        else if(data<0){ curv->AddEdge(cmpv->GetKey(), ceil(data * 1.1)); }
                        col = 1;
                    }
                    if (cmpv->FindEdge(i) != NULL) {
                        data = cmpv->FindEdge(i)->GetWeight();
                        if (cmpv->FindprevEdge(i) != NULL) {
                            cmpv->FindprevEdge(i)->SetNext(cmpv->FindEdge(i)->GetNext());
                        }
                        else {
                            cmpv->sethead(cmpv->GetHeadOfEdge()->GetNext());
                        }
                        delete cmpv->FindEdge(i);
                        cmpv->sizedown();
                        if (data > 0) { cmpv->AddEdge(curv->GetKey(), ceil(data * 0.9)); }//Create a new edge when data is positive
                        else if(data<0){ cmpv->AddEdge(curv->GetKey(), ceil(data * 1.1)); }//Create a new edge when data is negative
                        col = 1;
                    }
                    if (col == 1) { break; }
                }
            }
            cmpv = cmpv->GetNext();
        }
        curv = curv->GetNext();
        cmpv = curv->GetNext();
    }


    //2. If the name is the same 10 characters after applying 1
    curv = m_graph.head();
    cmpv = m_graph.head()->GetNext();

    for (int i = 0; i < m_vSize - 1; i++) {
        for (int j = i + 1; j < m_vSize; j++) {
            a1 = curv->GetName();
            b1 = cmpv->GetName();
            transform(a1.begin(), a1.end(), a1.begin(), ::tolower);
            transform(b1.begin(), b1.end(), b1.begin(), ::tolower);
            len1 = a1.length(); 
            col = 0;

            for (int l = 0; len1 - l >= 10; l++) {
                temp = a1.substr(l, 10);
                if (Success==RabinKarpCompare(b1, temp)) {
                    if (curv->FindEdge(j) != NULL) {
                        data = curv->FindEdge(j)->GetWeight();
                        if (curv->FindprevEdge(j) != NULL) {
                            curv->FindprevEdge(j)->SetNext(curv->FindEdge(j)->GetNext());
                        }
                        else {
                            curv->sethead(curv->GetHeadOfEdge()->GetNext());
                        }
                        delete curv->FindEdge(j);
                        curv->sizedown();
                        if (data > 0) { curv->AddEdge(cmpv->GetKey(), ceil(data * 0.9)); }
                        else if (data < 0) { curv->AddEdge(cmpv->GetKey(), ceil(data * 1.1)); }
                        col = 1;
                    }
                    if (cmpv->FindEdge(i) != NULL) {
                        data = cmpv->FindEdge(i)->GetWeight();
                        if (cmpv->FindprevEdge(i) != NULL) {
                            cmpv->FindprevEdge(i)->SetNext(cmpv->FindEdge(i)->GetNext());
                        }
                        else {
                            cmpv->sethead(cmpv->GetHeadOfEdge()->GetNext());
                        }
                        delete cmpv->FindEdge(i);
                        cmpv->sizedown();
                        if (data > 0) { cmpv->AddEdge(curv->GetKey(), ceil(data * 0.9)); }
                        else if (data < 0) { cmpv->AddEdge(curv->GetKey(), ceil(data * 1.1)); }
                        col = 1;
                    }
                    if (col == 1) { break; }
                }
            }
            cmpv = cmpv->GetNext();
        }
        curv = curv->GetNext();
        cmpv = curv->GetNext();
    }
    

    //3. ???????????? ??? ?????? ?????? ?????? ??????
    curv = m_graph.head();//head vertex?????? ??????
    cmpv = m_graph.head()->GetNext();

    for (int i = 0; i < m_vSize - 1; i++) {//?????? vertex
        for (int j = i + 1; j < m_vSize; j++) {//????????? vertex
            a1 = curv->Getstore(); //curv??? ?????????
            b1 = cmpv->Getstore(); //cmpv??? ?????????
            transform(a1.begin(), a1.end(), a1.begin(), ::tolower);//????????? ?????? ???????????? ?????????(???????????? ??????x)
            transform(b1.begin(), b1.end(), b1.begin(), ::tolower);//????????? ?????? ???????????? ?????????(???????????? ??????x)
            len1 = a1.length(); //curv??? ????????? ??????
            col = 0;
            
            istringstream iss(a1);
            string token;
            while (getline(iss, token, ' ')) {
                if(Success == RabinKarpCompare(b1,token)){//???????????? ?????? ????????? ?????????

                    if (curv->FindEdge(j) != NULL) {//curv??? edge??? j????????? edge??? ????????? ??????
                        data = curv->FindEdge(j)->GetWeight();//weight double????????? ??????
                        if (curv->FindprevEdge(j) != NULL) {//head??? ?????? ??? ???????????? edge??? ??? ??? ??????
                            curv->FindprevEdge(j)->SetNext(curv->FindEdge(j)->GetNext());//???????????? edge????????? ???????????? edge ?????? ?????? ??????
                        }
                        else {//head??? ??? head ????????????
                            curv->sethead(curv->GetHeadOfEdge()->GetNext());
                        }
                        delete curv->FindEdge(j);//edge??????
                        curv->sizedown();//size 1 ??????
                        if (data > 0) { curv->AddEdge(cmpv->GetKey(), ceil(data * 0.8)); }//data??? ????????? ??? ????????? edge??????
                        else if (data < 0) { curv->AddEdge(cmpv->GetKey(), ceil(data * 1.2)); }//data??? ????????? ??? ????????? edge??????
                        col = 1;//?????? ????????? ????????? vertex??? ??????????????????(?????? ??????????????? ??? ?????? ?????? ?????????)
                    }
                    if (cmpv->FindEdge(i) != NULL) {//cmpv??? edge??? i????????? edge??? ????????? ??????
                        data = cmpv->FindEdge(i)->GetWeight();//weight double????????? ??????
                        if (cmpv->FindprevEdge(i) != NULL) {//head??? ?????? ??? ???????????? edge??? ??? ??? ??????
                            cmpv->FindprevEdge(i)->SetNext(cmpv->FindEdge(i)->GetNext());//???????????? edge????????? ???????????? edge ?????? ?????? ??????
                        }
                        else {//head??? ??? head ????????????
                            cmpv->sethead(cmpv->GetHeadOfEdge()->GetNext());
                        }
                        delete cmpv->FindEdge(i);//edge??????
                        cmpv->sizedown();//size 1 ??????
                        if (data > 0) { cmpv->AddEdge(curv->GetKey(), ceil(data * 0.8)); }//data??? ????????? ??? ????????? edge??????
                        else if (data < 0) { cmpv->AddEdge(curv->GetKey(), ceil(data * 1.2)); }//data??? ????????? ??? ????????? edge??????
                        col = 1;//?????? ????????? ????????? vertex??? ??????????????????(?????? ??????????????? ??? ?????? ?????? ?????????)
                    }
                }
                if (col == 1) { break; }
            }
            cmpv = cmpv->GetNext(); //???????????? vertex ??????
        }
        curv = curv->GetNext();//?????? vertex ??????
        cmpv = curv->GetNext();
    }
    return Success;
}


void Manager::sort(string type, int* v,int n) {
    if (type == "quick") {
        //chrono::system_clock::time_point start = chrono::system_clock::now();//?????? ????????? start??? ??????
        quick(0, n - 1, v);
       // chrono::system_clock::time_point end = chrono::system_clock::now();//?????? ????????? end??? ??????
        //chrono::nanoseconds nano = end - start;
    }

    else if (type == "insert") {
        int val,j;
        //chrono::system_clock::time_point start = chrono::system_clock::now();//?????? ????????? start??? ??????
        for (int i = 0; i < n; i++) {
            val = v[i];
            for ( j = i - 1; j >= 0; j--) {
                if (v[j] > val) { v[j + 1] = v[j]; continue; }//???????????? ????????? ????????? ???????????? ??? ?????? ?????? ?????????
                break;
            }
            v[j + 1] = val; //??? ????????? key?????? ?????????.
        }
        //chrono::system_clock::time_point end = chrono::system_clock::now();//?????? ????????? end??? ??????
       // chrono::nanoseconds nano = end - start;
    }

    else if (type == "merge") {
        //chrono::system_clock::time_point start = chrono::system_clock::now();//?????? ????????? start??? ??????
        merge_sort(v, 0, n - 1);
        //chrono::system_clock::time_point end = chrono::system_clock::now();//?????? ????????? end??? ??????
        //chrono::nanoseconds nano = end - start;
    }

    else if (type == "heap") {
        MinHeap<int, int> heap;
        //chrono::system_clock::time_point start = chrono::system_clock::now();//?????? ????????? start??? ??????
        for (int i = 0; i < n; i++) {heap.Push(v[i], 0);}
        for (int i = 0; i < n; i++) { v[i] = heap.Top().first; heap.Pop(); }
        //chrono::system_clock::time_point end = chrono::system_clock::now();//?????? ????????? end??? ??????
       // chrono::nanoseconds nano = end - start;


    }
    else if (type == "bubble") {
        int temp = 0;
        //chrono::system_clock::time_point start = chrono::system_clock::now();//?????? ????????? start??? ??????
        //??????????????????
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (v[j] > v[j + 1]) {
                    temp = v[j];
                    v[j] = v[j + 1];
                    v[j + 1] = temp;
                }
            }
        }
        //chrono::system_clock::time_point end = chrono::system_clock::now();//?????? ????????? end??? ??????
       // chrono::nanoseconds nano = end - start;
        
    }
    else if (type == "selection") {
        int min, tmp;
        //chrono::system_clock::time_point start = chrono::system_clock::now();//?????? ????????? start??? ??????
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
        //chrono::system_clock::time_point end = chrono::system_clock::now();//?????? ????????? end??? ??????
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
    int middle = (left + right) / 2;       //???????????? left??? right??? ???????????? middle??? ??????
    int i = left, j = middle + 1, k = left;//i,k??? ???????????? ??????, j??? ???????????? ??????
    int temp[200];//???????????? ?????? ????????? ??????????????? ??????

    while (i <= middle) {//i??? ???????????? ?????? ???
        if (j > right) { break; }//j??? ????????? ???????????? ???
        if (v[i] <= v[j]) {//????????? ?????? ?????? ??????
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
    merge_sort(v, left, middle);       //????????????
    merge_sort(v, middle + 1, right);  //????????????
    merge(v, left, right);
}

void Manager::compression(vector<int> v) {
    string s;
    //1.2????????? ????????? ????????? ?????? ??? ????????? ??????
    //s??? ????????? ???????????? ????????????
    for (int i = 0; i < v.size(); i++) {s.append(m_graph.FindVertex(v[i])->ns);}
    
    string c = s;//c??? s??????
    transform(s.begin(), s.end(), s.begin(), tolower);//s??? ???????????? ?????????.
    cout << c << endl;

    int answer = 0;//answer??? ????????? ????????????
    int bre = 0, start_point = 0;


    for (int i = 1; i <= s.length() / 2; i++) {//????????? ????????? ?????? ??????.
        bre = 0;
        //???????????? ?????? ????????? ??????
        for (int j = 0; j < s.length(); j++) {//????????? ????????? ??????, j??? 0??????
            //?????? ????????????
            for (int z = i; j + z + i <= s.length(); z++) {//count=0,
                //j???????????? i??????????????? j+z???????????? i?????? ????????? ????????? count 1??????
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
    //z??? ????????? ?????? ?????? ??????+?????? ?????? ??????(??? ???????????? ?????? ???????????? ??????)
    for (int z = i + start_point; z + i <= s.length(); z++) {
        if (Success==RabinKarpCompare(s.substr(start_point, i), s.substr(z, i))) {
            c.erase(z - gap, i);//???????????? ????????? ?????? ??????????????? ??????
            gap = gap + i;//???????????? ????????? ?????? ???????????? ?????? ????????? ????????? gap?????? ?????? ?????????
            z += i;//????????? ????????? ????????? ???????????? ????????? ????????? ??????????????? ????????? ??????
            if (bre == 0) { gap -= 1; c.insert(start_point + i, 1, '*'); }//??? ??? ????????? *?????????
            bre = 1;
        }
    }

    
    //2. shop, class, academy??? 1?????? ????????? ??????
    for (int q = 0; q < 3; q++) {//??? 3??? ?????? shop->class->academy
        s = c;
        transform(s.begin(), s.end(), s.begin(), tolower);//s??? ???????????? ?????????.
        string du="shop";
        if (q == 1) { du = "class"; }
        else if (q == 2) { du = "academy"; }
        int wn = du.length(), col = 0, gap = 0;
        for (int j = 0; j+wn <= s.length(); j++) {//????????? ????????? ??????, j??? 0??????
            if (Success == RabinKarpCompare(s.substr(j, wn), du)) {
                col += 1;
                if(col!=1){
                    c.erase(j - gap, wn);//???????????? ????????? ?????? ??????????????? ??????
                    gap = gap + wn;//???????????? ????????? ?????? ???????????? ?????? ????????? ????????? gap?????? ?????? ?????????
                }
            }
        }
    }

    fout << endl << "Course : " << c << endl;
    cout << endl << "Course : " << c << endl;
    return;
}
