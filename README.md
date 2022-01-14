# shortest_route_in_town

- introduction
라빈카프 공국에 있는 가게들의 거리와 이름 정보를 이용해 그래프를 형성한다.
그래프를 이용해 BFS, set을 이용한 DIJKSTRA, min heap을 이용한 DIJKSTRA, BELLMANFORD, FLOYD 알고리즘을 이용해 최단경로를 구한다.
최단경로를 구한 후에 정렬 알고리즘을 사용해 경로를 정렬한다.
정렬 알고리즘은 quick, insert, merge, heap, bubble, selection sort를 사용한다. 
마지막으로 각 경로에서 들리는 가게마다 간판명을 연결해 라빈카프 공국 공식 압축 법칙에 따라 문자열을 압축한다.
 -> 문자열을 비교하는 경우에는 반드시 라빈카프 알고리즘을 사용한다.
 -> 즉 압축을 할 때와 update를 할 때 라빈카프 알고리즘이 사용된다. 

1) 최단경로 알고리즘

    - BFS
 
BFS는 원래 너비 우선 탐색으로 그래프 탐색 방법이다. 원래는 시작점을 입력받아 시작 정점으로부터 가까운 정점을 먼저 방문하고 멀리 떨어진 정점은 나중에 방문하는 순회 방법으로 queue를 사용한다. 즉 시작 정점에서 인접한 정점들을 모두 queue에 넣고 queue의 맨 앞 요소로 이동한 뒤 queue에서 pop한다. 그리고 이동한 vertex에서 인접한 vertex를 queue에 전부 넣는다. 위와 같은 동작을 반복해 queue가 빌 때까지 반복한다.
이번에는 최단경로를 찾는 용도로 사용되기 때문에 원래는 queue에 있는 값에서 가장 작은 값으로 이동하는 것을 반복해야 한다. 하지만 issue에서 비용은 생각하지 않고 구현하라고 했기 때문에 시작 정점에서부터 bfs동작을 하면서 각 이동시에 시작점과 도착점을 저장한다. 도착 정점에 도착했을 때 저장해둔 정보를 기준으로 거꾸로 탐색해서 경로를 찾을 수 있다. 
 
위와 같은 그래프가 있을 때 1에서 5로 가는 최단 경로를 구하는 방법은 다음과 같다. 첫번째로 1을 queue에 넣고 뺀 뒤 기준 정점을 1으로 설정하고 1의 인접한 2, 3, 4 정점을 순서대로 queue에 넣는다. 기준 정점이 queue의 front인 2가 기준이 되고 2를 queue에서 뺀다. 2의 인접점을 넣는데 없기 때문에 3이 기준이 되고 queue에서 빠진다. 3에서 인접한 점은 5이기 때문에 도착지점으로 탐색을 마친다.
이때 총 이동경로는 출발점에는 1 1 1 3이 저장되어 있고 도착점에는 2 3 4 5가 저장되어 있다. 3->5 가 마지막으로 거꾸로 올라가면서 3에 도착하는 edge를 찾아야한다. 1->3이 해당 edge가 되며 도착지가 출발지점과 같기 때문에 경로는 1 3 5가 된다.

 
위와 같은 그래프가 있을 때 1에서 5로 가는 최단 경로를 구하는 방법은 다음과 같다. 첫번째로 1을 queue에 넣고 뺀 뒤 기준 정점을 1으로 설정하고 1의 인접한 2, 3, 4 정점을 순서대로 queue에 넣는다. 기준 정점이 queue의 front인 2가 기준이 되고 2를 queue에서 뺀다. 2의 인접점을 넣는데 없기 때문에 3이 기준이 되고 queue에서 빠진다. 3에서 인접한 점은 5이기 때문에 도착지점으로 탐색을 마친다.
이때 총 이동경로는 출발점에는 1 1 1 3이 저장되어 있고 도착점에는 2 3 4 5가 저장되어 있다. 3->5 가 마지막으로 거꾸로 올라가면서 3에 도착하는 edge를 찾아야한다. 1->3이 해당 edge가 되며 도착지가 출발지점과 같기 때문에 경로는 1 3 5가 된다.

    - DIJKSTRA (set)

    - DIJKSTRA (minheap)

    - BELLMANFORD

    - FLOYD

2) Rabin-Karp

3) 정렬 알고리즘
    - Quick sort


    - Insert sort


    - Merge sort


    - Heap sort


    - Bubble sort


    - Selection sort

