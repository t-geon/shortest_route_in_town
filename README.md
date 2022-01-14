# shortest_route_in_town

- introduction
라빈카프 공국에 있는 가게들의 거리와 이름 정보를 이용해 그래프를 형성한다.
그래프를 이용해 BFS, set을 이용한 DIJKSTRA, min heap을 이용한 DIJKSTRA, BELLMANFORD, FLOYD 알고리즘을 이용해 최단경로를 구한다.
최단경로를 구한 후에 정렬 알고리즘을 사용해 경로를 정렬한다.
정렬 알고리즘은 quick, insert, merge, heap, bubble, selection sort를 사용한다. 
마지막으로 각 경로에서 들리는 가게마다 간판명을 연결해 라빈카프 공국 공식 압축 법칙에 따라 문자열을 압축한다.
* 문자열을 비교하는 경우에는 반드시 라빈카프 알고리즘을 사용한다.
* 즉 압축을 할 때와 update를 할 때 라빈카프 알고리즘이 사용된다. 
