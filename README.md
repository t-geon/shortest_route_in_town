# shortest_route_in_town

- introduction
라빈카프 공국에 있는 가게들의 거리와 이름 정보를 이용해 그래프를 형성한다.
그래프를 이용해 BFS, set을 이용한 DIJKSTRA, min heap을 이용한 DIJKSTRA, BELLMANFORD, FLOYD 알고리즘을 이용해 최단경로를 구한다.
최단경로를 구한 후에 정렬 알고리즘을 사용해 경로를 정렬한다.
정렬 알고리즘은 quick, insert, merge, heap, bubble, selection sort를 사용한다. 
마지막으로 각 경로에서 들리는 가게마다 간판명을 연결해 라빈카프 공국 공식 압축 법칙에 따라 문자열을 압축한다.
 -> 문자열을 비교하는 경우에는 반드시 라빈카프 알고리즘을 사용한다.
 -> 즉 압축을 할 때와 update를 할 때 라빈카프 알고리즘이 사용된다. 

1. 최단경로 알고리즘

1) BFS
 
BFS는 원래 너비 우선 탐색으로 그래프 탐색 방법이다. 원래는 시작점을 입력받아 시작 정점으로부터 가까운 정점을 먼저 방문하고 멀리 떨어진 정점은 나중에 방문하는 순회 방법으로 queue를 사용한다. 즉 시작 정점에서 인접한 정점들을 모두 queue에 넣고 queue의 맨 앞 요소로 이동한 뒤 queue에서 pop한다. 그리고 이동한 vertex에서 인접한 vertex를 queue에 전부 넣는다. 위와 같은 동작을 반복해 queue가 빌 때까지 반복한다.
이번에는 최단경로를 찾는 용도로 사용되기 때문에 원래는 queue에 있는 값에서 가장 작은 값으로 이동하는 것을 반복해야 한다. 하지만 issue에서 비용은 생각하지 않고 구현하라고 했기 때문에 시작 정점에서부터 bfs동작을 하면서 각 이동시에 시작점과 도착점을 저장한다. 도착 정점에 도착했을 때 저장해둔 정보를 기준으로 거꾸로 탐색해서 경로를 찾을 수 있다. 
![image](https://user-images.githubusercontent.com/88877637/149549421-0d2f8949-f705-47bb-b289-5d87ea294aa7.png)

위와 같은 그래프가 있을 때 1에서 5로 가는 최단 경로를 구하는 방법은 다음과 같다. 첫번째로 1을 queue에 넣고 뺀 뒤 기준 정점을 1으로 설정하고 1의 인접한 2, 3, 4 정점을 순서대로 queue에 넣는다. 기준 정점이 queue의 front인 2가 기준이 되고 2를 queue에서 뺀다. 2의 인접점을 넣는데 없기 때문에 3이 기준이 되고 queue에서 빠진다. 3에서 인접한 점은 5이기 때문에 도착지점으로 탐색을 마친다.
이때 총 이동경로는 출발점에는 1 1 1 3이 저장되어 있고 도착점에는 2 3 4 5가 저장되어 있다. 3->5 가 마지막으로 거꾸로 올라가면서 3에 도착하는 edge를 찾아야한다. 1->3이 해당 edge가 되며 도착지가 출발지점과 같기 때문에 경로는 1 3 5가 된다.

2) DIJKSTRA (set)
 
 다익스트라 알고리즘은 다이나믹 프로그래밍을 활용한 최단경로 탐색 알고리즘으로 가장 많이 사용되는 알고리즘 중 하나이다. 다익스트라 알고리즘은 하나의 최단거리는 여러 개의 최단거리로 이루어질 수 있기 때문에 이전까지 구한 최단 거리 정보를 그대로 사용한다는 특징이 있다.
    ![image](https://user-images.githubusercontent.com/88877637/149549537-ea388393-7ec0-4070-a247-f2096adf7e2b.png)
위 와 같은 그래프에서 1에서 2로가는 최단거리를 구한다면 길이를 저장하는 배열에 IN_FINITY를 모두 초기화 시키고, 비용을 first로 하고 도착지를 second로 하는 pair를 set에 넣고 시작한다. 즉 출발지인 1을 넣을 때는 비용은 0이고 도착지는 1이다. 총 set이 빌 때까지 반복하며 중간에 도착지가 나오면 반복을 종료한다. 첫번째 요소가 set에서 나오면서 1에 인접한 vertex로 가는 비용을 계산해서 이미 저장되어 있는 비용과 비교해 경로를 거쳤을 때 더 작은 비용이 드는 경우에 비용과 vertex를 pair로 만들어 set에 넣어준다. 이때 prev_vertex에 어디에서 이동한 것인지 저장한다. 즉 1이 저장된다.
set은 자동적으로 key값에 따라 정렬되기 때문에 2,3,4로 가는 비용 중 가장 작은 4로 이동한다. 또한 이때 4로 이동하는 pair가 set에서 지워지고 4에서 6으로 이동하는 pair가 set에 들어간다. 이때 1에서 2로 이동하는 경로가 최소가 된다. set에서 2로 이동하는 pair를 뺀다. 나온 값이 도착지점과 같기 때문에 끝난다. 하나의 반복문이 끝나고 나면 prev_vertex를 확인하는 반복문을 동해 각 정점 별 최단 경로와 도착지의 최단경로를 역추적해 경로를 출력했다. 즉 1 2로 출력된다.

    
3) DIJKSTRA (minheap)

4) BELLMANFORD

5) FLOYD

2. Rabin-Karp

3. 정렬 알고리즘
    - Quick sort


    - Insert sort


    - Merge sort


    - Heap sort


    - Bubble sort


    - Selection sort

