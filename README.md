# shortest_route_in_town

라빈카프 공국에 있는 가게들의 거리와 이름 정보를 이용해 그래프를 형성한다.
최단경로 알고리즘인 BFS, set을 이용한 DIJKSTRA, min heap을 이용한 DIJKSTRA, BELLMANFORD, FLOYD를 이용해 최단경로를 구한다.
최단경로를 구한 후에 정렬 알고리즘을 사용해 경로를 정렬한다.
정렬 알고리즘은 quick, insert, merge, heap, bubble, selection sort를 사용한다. 
마지막으로 각 경로에서 들리는 가게마다 간판명을 연결해 라빈카프 공국 공식 압축 법칙에 따라 문자열을 압축한다.
 -> 문자열을 비교하는 경우에는 반드시 라빈카프 알고리즘을 사용한다.
 -> 즉 압축을 할 때와 update를 할 때 라빈카프 알고리즘이 사용된다. 

# 최단경로 알고리즘
1. BFS

BFS는 너비 우선 탐색으로 그래프 탐색 방법이다.
시작점으로부터 가까운 점을 먼저 방문하고 멀리 떨어진 정점은 나중에 방문하는 순회 방법으로 queue를 사용한다.
- 시작점에서 인접한 정점들을 모두 queue에 넣는다.
- queue의 맨 앞 요소로 이동한 뒤 queue에서 pop한다.
- 이동한 vertex에서 인접한 vertex를 queue에 전부 넣는다.
- 위와 같은 동작을 queue가 빌 때까지 반복한다.
최단경로를 찾는 용도로 사용되기 때문에 원래는 queue에 있는 값에서 가장 작은 값으로 이동하는 것을 반복해야 한다.
하지만 비용은 생각하지 않고 구현했기 때문에 이동시에 시작점과 도착점을 저장한다.
도착 정점에 도착했을 때 저장해둔 정보를 기준으로 거꾸로 탐색해서 경로를 찾을 수 있다. 

![image](https://user-images.githubusercontent.com/88877637/149550057-abe72134-3bc4-47d8-a8fd-78fc37763afb.png)

example) 위와 같은 그래프가 있을 때 1에서 5로 가는 최단 경로를 구하는 방법은 다음과 같다.
- 1을 queue에 넣고 뺀 뒤 기준점을 1으로 설정하고 1의 인접한 2, 3, 4 정점을 순서대로 queue에 넣는다.
- 기준점은 queue의 front인 2가 된다. 2를 queue에서 뺀다. 
- 2의 인접점은 없기 때문에 queue에 넣지 않는다.
- 기준점은 3된다. 3을 queue에서 뺀다.
- 3에서 인접한 점은 5이기 때문에 도착지점으로 탐색을 마친다.
이때 총 이동경로는 반대로 접근해서 찾는다.
3->5 가 마지막이므로 거꾸로 올라가면서 3에 도착하는 edge를 찾아야한다.
1->3이 해당 edge가 되며 도착지가 출발지점과 같기 때문에 경로는 1 3 5가 된다.


2. DIJKSTRA (set)
 
 다익스트라 알고리즘은 다이나믹 프로그래밍을 활용한 최단경로 탐색 알고리즘으로 가장 많이 사용되는 알고리즘 중 하나이다.
 다익스트라 알고리즘에서 하나의 최단거리는 여러 개의 최단거리로 이루어질 수 있다.
 때문에 이전까지 구한 최단 거리 정보를 그대로 사용한다는 특징이 있다.
 
   ![image](https://user-images.githubusercontent.com/88877637/149550039-1fea5af6-562b-4a61-8347-4959468fc2e1.png)
   
example) 위와 같은 그래프에서 1에서 2로가는 최단거리를 구해보자
- 길이를 저장하는 배열에 IN_FINITY를 모두 초기화 시킨다
- 비용을 first로 하고 도착지를 second로 하는 pair를 set에 넣고 시작한다.
-> 즉 출발지인 1을 넣을 때는 비용은 0이고 도착지는 1이다.
- 총 set이 빌 때까지 반복하며 중간에 도착지가 나오면 반복을 종료한다.
- 첫번째 요소를 set에서 빼면서 1에 인접한 vertex로 가는 비용을 계산한다.
- 이미 저장되어 있는 비용과 비교한 뒤, 해당 경로를 거쳤을 때 더 작은 비용이 드는 경우에 비용과 vertex를 pair로 만들어 set에 넣어준다
-> 이때 prev_vertex에 어디에서 이동한 것인지 저장한다. 즉 1이 저장된다.
- set은 자동적으로 key값에 따라 정렬되기 때문에 2,3,4로 가는 비용 중 가장 작은 4로 이동한다. 또한 이때 4로 이동하는 pair가 set에서 지워지고 4에서 6으로 이동하는 pair가 set에 들어간다. 이때 1에서 2로 이동하는 경로가 최소가 된다. set에서 2로 이동하는 pair를 뺀다. 나온 값이 도착지점과 같기 때문에 끝난다. 하나의 반복문이 끝나고 나면 prev_vertex를 확인하는 반복문을 동해 각 정점 별 최단 경로와 도착지의 최단경로를 역추적해 경로를 출력했다. 즉 1 2로 출력된다.

    
- DIJKSTRA (minheap)

DIJKSTRAMIN은 위에서 설명한 DIJKSTRA와 동일한 기능을 한다. DIJKSTRA와 다른 점은 가장 작은 비용으로 이동할 때 가장 작은 값이 무엇인지 알 수 있도록 정렬해주는 요소가 무엇인지의 차이이다. DIJKSTRA는 set으로 값을 정렬하고 DIJKSTRAMIN은 min heap으로 값을 정렬한다.
DIJKSTRA에서와 같은 예제로 설명해보겠다.
1에서 2로가는 최단거리를 구한다면 길이를 저장하는 배열에 IN_FINITY를 모두 초기화 시키고, 비용을 첫번째 인자로 하고 도착지를 두번째 인자로 해 push를 이용해 min heap에 넣고 시작한다. 즉 출발지인 1을 넣을 때는 비용은 0이고 도착지는 1이다. 총 min heap이 빌 때까지 반복하며 중간에 도착지가 나오면 반복을 종료한다. 첫번째 요소가 min heap에서 나오면서 1에 인접한 vertex로의 비용 원래 비용과 경유하는 비용을 계산해 더 작은 값을 vertex와 함께 min heap에 넣어준다 즉 2,3,4가 들어간다. 이때 prev_vertex에 어디에서 이동한 것인지 저장한다. 즉 1이 저장된다.
min heap은 push할 때 key값에 따라 정렬되기 때문에 2,3,4로 가는 비용 중 가장 작은 4로 이동하면서 min heap에서 지워지고 4에서 6으로 이동하는 경로가 min heap에 들어간다. 이때 1에서 2로 이동하는 경로가 최소가 된다. min heap에서 2로 이동하는 경로를 뺀다. 나온 값이 도착지점과 같기 때문에 끝난다. 하나의 반복문이 끝나고 나면 prev_vertex를 확인하는 반복문을 동해 각 정점 별 최단 경로와 도착지의 최단경로를 역추적해 경로를 출력했다. 즉 1 2로 출력된다.

- BELLMANFORD

벨만 포드 알고리즘이란 최단 경로를 구하는 알고리즘으로 모든 경로를 여러 번 계산하기 때문에 다익스트라 알고리즘에 비해서 시간이 오래 걸린다. 하지만 간선의 비용이 음수일 때에도 음수 사이클이 발생하지 않는다면 문제없이 사용할 수 있다는 장점이 있다.
벨만 포드 알고리즘은 각 정점의 값을 무한대로 저장하고 이전 위치는 -1으로 저장하고 시작한다. d의 시작점에 0을 넣고 시작한다. 벨만포드 알고리즘은 모든 정점을 기준으로 1번이라도 방문했던 곳이면 동작하고 아니면 다음 정점으로 넘어간다.

![image](https://user-images.githubusercontent.com/88877637/149550100-0bc5a23c-0438-47e8-9a46-4c1475df9ea4.png)

위와 같은 그래프에서 1에서 3으로 가는 최단경로라면 d의 1자리를 0을 넣고 d[2]=2 d[3]=8, d[4]=1이 된다. 다음은 2에서 1으로가는 값을 본다, d[1]에 2를 넣으려고 하지만 d[1]=0이기 때문에 넣지 못한다. 다음은 3차례이다. d[6]=9, d[5]=16이 된다. 다음은 4차례이다. d[6]=9에서 4로 바뀐다. 다음은 5차례이다. d[6]=4이기 때문에 25로 바뀌지 않는다. 다음은 6차례이다. d[3]=8에서 5로 바뀐다. d[5]=16에서 13으로 바뀐다. 이렇게 1바퀴가 돈 것으로 보면 된다. 이와 같은 반복을 총 n-1번을 하면서 해당 정점의 값이 경유를 했을 때 더 작아지면 값을 갱신하고 p에 이전 위치를 저장한다. n-1번 했을 때 값이 최단경로의 비용으로 볼 수 있고 p를 통해 경로를 알 수 있다. 벨만 포드에서 예외처리 해야 할 음수 사이클은 n-1번의 반복을 한 뒤에 1번 더 위 동작을 실행해보면 알 수 있다. 즉 1번 더 반복했을 때 정점의 값이 달라지는 경우가 있다면 음수 사이클이 존재하는 것이다.

- FLOYD
다른 알고리즘들과는 달리 모든 정점 쌍에 대해 최단 거리를 구하고 음의 비용을 갖는 간선이 있어도 사용할 수 있다. 플로이드 알고리즘은 s에서 e까지 이동할 때 최단거리를 구한다. 이때 중간 경유지인 w를 이용한다. 즉 s에서 w까지의 최단거리와 w에서 e까지의 최단거리를 이용한다.
플로이드 알고리즘을 구현하기 위해서는 일단 2차원 배열을 선언한다. 형식은 a[출발점][도착점]으로 보면된다. 때문에 a[1][1]이라면 0을 저장하고 나머지는 무한대를 저장해 배열을 초기화한다.
그래프를 통해 직접 연결된 값들을 각 위치에 알맞게 초기화한다. 만약 연결되어 있지 않다면 무한대로 초기화 되어있다.
for문 3개를 통해 반복하면서 현재 저장되어 있는 값과 중간 지점을 경유해서 같을 때를 비교해 경유해서 간 경우가 더 비용이 적다면 a[i][j]위치에 a[i][k]+a[k][j]를 저장한다.
음수 사이클을 확인하는 방법은 a[i][i]가 0보다 작으면 음수 사이클이 있는 것이다.

![image](https://user-images.githubusercontent.com/88877637/149550247-b5676320-d7ed-41af-829c-62df8115e8f4.png)

위와 같은 그래프가 있다면

0	4	-1	8 /
INF	0	-2	-10 /
INF	INF	0	3 /
INF	INF	INF	0 /   -> 초기화를 한번 돌 때

0	4	-1	-6 /
INF	0	-2	-10 /
INF	INF	0	3 /
INF	INF	INF	0 /  -> 가장 큰 반복문을 2번 돌았을 때

0	4	-1	-6 /
INF	0	-2	-10 /
INF	INF	0	3 /
INF	INF	INF	0 /   -> 가장 큰 반복문을 3번 돌았을 때


2. Rabin-Karp

라빈-카프 알고리즘은 해시를 사용해 긴 데이터를 짧은 데이터로 바꿔 준 뒤 짧은 데이터를 비교해 같은 문자인지 확인하고 다른 문자여도 같은 문자일 수 있기 때문에 한번 더 문자를 하나 하나 비교해 같은 지 확인해 같은 문자열을 찾아내는 알고리즘이다. 해시를 하는 방법도 다양하게 있지만 라빈카프에서는 문자의 아스키코드 값에 2의 제곱 수를 차례대로 곱하여 더해준 해시방법을 사용했다. 문자가 다르더라도 간혹 해시 값이 같게 나올 수 있다.
첫번째로 큰 문자열의 크기-작은 문자열의 크기만큼 반복하는 반복문안에 작은 문자열의 길이만큼 반복하는 반복문을 만들어 뒤에서부터 앞으로 2의 제곱수를 문자의 아스키코드를 곱해 더해 해시를 구해준다. 처음에는 추가만 해주면 되고 처음이 아니라면 앞의 문자1개의 해시 값을 빼고 뒤의 해시 값을 더해줘야 한다. 만약 해시 값이 같다면 각각의 문자를 비교해준 뒤 같으면 success를 반환하고 같지 않으면 LoadFileExist(임의로 설정한 오류)가 반환된다.
abacabacaaba와 abacaaba를 예로 들자면 작은 문자열의 해시는 24833으로 고정되어 있고 큰 문자열을 이동하면서 해시를 계산한다.
첫번째 큰 문자열의 해시는 24837이므로 작은 문자열의 해시와 다르다.
두번째 큰 문자열의 해시는 24939이므로 작은 문자열의 해시와 다르다
세번째 큰 문자열의 해시는 24833으로 작은 문자열의 해시와 같다. 이때 문자열의 문자들을 비교해 같으면 success를 다르면 LoadFileExist를 반환한다

3. 정렬 알고리즘
- Quick sort

퀵 정렬은 재귀함수를 이용하기 때문에 함수로 구현을 했다. 퀵 정렬은 리스트안의 한 요소를 선택해 그 요소를 pivot으로 둔다. pivot을 기준으로 pivot보다 작다면 pivot의 왼쪽으로, pivot보다 크다면 pivot의 오른쪽으로 옮겨진다. 옮겨지고 난 뒤 pivot을 제외하고 왼쪽과 오른쪽을 다시 정렬하는데 pivot을 기준으로 나눠진 두개의 배열에 새로운 pivot을 정해서 계속해서 반복한다(재귀함수). 계속해서 나눠지다가 배열의 크기가 0이거나 1이 된다면 종료한다.
ex) 3 7 2 0 6 1 을 quick정렬을 하자.
pivot을 3으로 한다면 3와 7을 비교한다. 7이 크기 때문에 3과 1을 비교한다. 1이 작기 때문에 1과 7의 위치를 바꾼다. -> 3 1 2 0 6 7	
left와 right의 위치를 업데이트한 뒤 2와 6으로 바뀌고 위와 같은 동작을 한다. 하지만 위 상황과 반대기 때문에 위치를 변경시키지 않는다. 
left와 right가 만난다(6)
3과 6을 비교해 3이 작기 때문에 6의 왼쪽으로 이동한다. ->1 2 0 3 6 7(3은 고정)
새로운 pivot 1설정(이전보다 작은 값), 2와 0을 pivot과 비교-> 1 0 2 3 6 7
left와 right가 만난다(2)
1과 2를 비교해 1이 작기 때문에 2의 왼쪽으로 이동한다. ->0 1 2 3 6 7

- Insert sort

삽입 정렬은 두번째 요소부터 시작해 그 앞의 요소들과 비교한 뒤 삽입할 위치를 지정한다. 그 뒤에 한 칸 뒤로 이동해 나머지 앞의 요소들과 비교한다. 위 동작을 반복해 총 삽입될 값의 수만큼 반복하면 끝난다.
5 3 8 1 2 7을 정렬한다고 하면 2번째인 3부터 시작한다
5>3이므로 3이 앞으로 이동 3 5 8 1 2 7
8>5이므로 그대로
1<8, 1<5, 1<3 이므로 맨 앞으로 간다. 1 3 5 8 2 7
2<8, 2<5, 2<3 이므로 2번째로 간다 1 2 3 5 8 7
7<8 이므로 한 칸 앞으로 간다 1 2 3 5 7 8 
정렬이 끝난다.

- Merge sort

병합 정렬은 큰 문제를 작은 문제로 나눠 본 뒤 다시 합치는 정렬방식이다.
배열에 정렬되지 않은 수가 있다면 나눌 수 있는 만큼 작게 분리해준다.
분리한 순서와 반대로(마지막에 분리한 것을 가장 먼저) 합친다.
합칠 때는 각 값들을 정렬해 합친다.
3 4 1 5 2를 정렬한다면 341, 52로 분리 34,1,5,2로 분리 3,4,1,5,2로 분리하다.
가장 마지막에 분리된 34를 합친다.
34와 1을 합치고 5 2를 합친다-> 134, 52
마지막으로 전부 합친다->12345

- Heap sort

힙 정렬은 원래 방식인 정형적인 방식으로 구현하지 않고 프로젝트를 진행할 때 구현해야 했던 min heap으로 구현했다. 즉 push를 이용해 heap에 값을 넣어준다. push를 할 때는 맨 끝에 삽입한 후 자신의 부모(자신 인데스/2)와 비교해 작으면 위로 부모와 위치를 바꾼다. 최대 root까지 올라갈 수 있다.
5 3 7 1 을 정렬한다면 
5는 root가 된다.
3이 자식으로 삽입되고 부모인 5와 비교해 3이 root가된다.
7이 자식으로 들어오고 부모인 3보다 크기 때문에 그대로 자식이 된다.
1은 5의 자식으로 들어간다. 부모인 5보다 작기 때문에 5와 바꾸고 그 위치의 부모인 3과 비교한다. 3보다 작기 때문에 1은 새로운 root가 된다.
이후 pop을 해 root를 빼준다. 1이 빠지고 가장 마지막 위치에 있던 5가 올라오고 자식과 비교를 한 뒤 3이 root가 된다. 이와 같은 방법으로 pop을 3번 더해주면 1 3 5 7으로 출력된다.
즉 삽입할 때 경우 마다 처리해줘야 하며 삽입한 후에 pop을 해 빼줘야하기 때문에 비효율적이다.

- Bubble sort

버블 정렬은 삽입 정렬과 거의 반대이다. 즉 앞에서부터 뒤로 이동하면서 비교한다. 첫번째 요소와 두번째 요소, 두번째 요소와 세번째 요소 이처럼 진행해 맨 뒤로 이동하고 총 1회전당 1개의 값의 위치가 고정되는 것이다 즉 n개의 값이 있다면 n-1회전을 해 정렬할 수 있다.
7 4 5 1 3을 정렬한다고 해보자
7>4, 7>5, 7>1, 7>3 이므로 4 5 1 3 7이 된다.
4<5, 5>1, 5>3 이므로 4 1 3 5 7이 된다.
4>1, 4>3이므로 1 3 4 5 7이 된다.
1<3이므로 그대로 유지된다.

- Selection sort

선택 정렬은 제자리에서 정렬하는 알고리즘으로 주어진 배열의 최솟값을 찾아 맨 앞의 값과 교체한다. 맨 앞의 값을 제외한 배열에서 최소값을 찾아 2번째 위치에 넣어준다. 위와 같은 동작을 원소가 1개 남을 때까지 진행한다.
9 6 7 3 5를 정렬한다고 해보자
최솟값 3 이므로 3 6 7 9 5
최솟값 5 이므로 3 5 7 9 6
최솟값 6 이므로 3 5 6 9 7
최솟값 7 이므로 3 5 6 7 9
