#define _CRT_SECURE_NO_WARNINGS
#ifndef SOLUTION_H
#define SOLUTION_H

#include <chrono>
#include "Queue.h"
#include "MinHeap.h"
#include "Result.h"
#include "Graph.h"
#include <fstream>
#include<algorithm>
#include<sstream>
#include<cmath>

class Manager
{
private:
    // the filepath for the result log
    const char* RESULT_LOG_PATH = "log.txt";
    // the filepath for the error log


    // the file stream for the result log
    std::ofstream fout;
    // the file stream for the error log
    
    // graph instance to manage the vertics.
    Graph m_graph;

    ifstream fin;
    string con="bubble";

public:
    ~Manager();
    void Run(const char* filepath);
    void PrintError(Result result);

private:
    Result Load(const char* filepath);
    Result Print();
    Result FindPathBfs(int startVertexKey, int endVertexKey);
    Result FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey);
    Result FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey);
    Result FindShortestPathBellmanFord(int startVertexKey, int endVertexKey);
    Result FindShortestPathFloyd();
    Result RabinKarpCompare(string CompareString, string ComparedString);
    Result Update();

    void compression(vector<int> v);

    void sort(string type,int* a,int n);
    void quick(int i, int j, int* v);
    void merge(int* v, int left, int right);
    void merge_sort(int* v, int left, int right);
};

#endif
