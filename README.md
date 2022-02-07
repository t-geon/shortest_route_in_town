# shortest_route_in_town

A graph is formed using the distane and name information of the stores.    
Shortest path algorithm BFS, DIJKSTRA using set, DIJKSTRA using min heap, BELLMANFORD, FLOYD are used.    
After finding the shortest path, the path is sorted using a sorting algorithm.    
Use quick sort, insert sort, merge sort, heap sort, bubble sort, and selection sort.    
Finally, by connecting the signage of each store you hear from each route, the string is compressed according to the official compression rule of the Principality of Rabin-Karp.    
 -> When comparing strings, the Ravincalf algorithm must be used.    
 -> The Rabin-Karp algorithm is used for compression and update.    

# shortest path algorithm

1. BFS    
BFS is a graph search method with breadth-first search.    
A queue is used as a traversal method that visits the closest vertices in order from the starting vertex.    
- At the starting vertex, adjacent vertices are put into the queue.     
- Moves to the front element of the queue and pops it from the queue.    
- All vertices adjacent to the moved vertex are put into the queue.
- Repeat the above operation until the queue is empty    
Originally, it had to repeat moving from the value in the queue to the smallest value.    
However, since we implemented it without considering the cost, we store the starting vertex and the destination vertex when moving.    
When you arrive at the destination vertex, you can find the route by searching backwards based on the stored information.    

![image](https://user-images.githubusercontent.com/88877637/149550057-abe72134-3bc4-47d8-a8fd-78fc37763afb.png)

example) Given the graph above, let's find the shortest path from 1 to 5   
- After putting 1 into the queue and subtracting it, the reference vertex is set to 1, and the adjacent 2, 3, 4 vertices of 1 are put into the queue in order.    
- The reference vertex becomes 2, which is the front of the queue. Subtract 2 from the queue.    
- Since there are no adjacent vertices of 2, we don't put them in the queue.
- The reference vertex becomes 3. 3 is subtracted from the queue.    
- Since the adjacent vertex in 3 is 5, the search ends with the destination.    
At this time, the total movement path is found by approaching in the opposite direction.    
Since 3->5 is the last, we need to find the edge that reaches 3 while going backwards.    
1->3 is the corresponding edge, and the destination is the same as the starting point, so the path is 1 3 5.    

---------------------------------------------------------------------

2. DIJKSTRA (set)

Dijkstra algorithm is one of the most used algorithms for the shortest path search using dynamic programming.    
In Dijkstra algorithm, one shortest distance can consist of several shortest distances.    
Therefore, it has the characteristic of using the shortest distance information obtained before as it is.    
 
   ![image](https://user-images.githubusercontent.com/88877637/149550039-1fea5af6-562b-4a61-8347-4959468fc2e1.png)
   
example) Let's find the shortest distance from 1 to 2 in the graph above.    
- Initialize the length-storing array to IN_FINITY    
- Start by putting a pair with first = cost and second = destination into the set.     
-> When you put in 1, which is the source, cost = 0 and destination = 1.    
- It repeats until set is empty, and the iteration ends when a destination is reached in the middle.      
- Calculate the cost of going to the vertex adjacent to 1 by subtracting the first element from the set.      
- Compare with stored costs.    
-> If the cost is small when passing through the path, the cost and vertex are paired and put into the set.      
-> It stores where it was moved in prev_vertex. That is, 1 is stored.
- The set is sorted according to the key value.    
-> It moves to 4, which is the smallest of the costs going to 2, 3, and 4.    
- The pair moving to 4 is removed from the set, and the pair moving from 4 to 6 is put into the set.    
- The path from 1 to 2 is minimal.       
- Subtract the pair moving by 2 from the set. It ends because the output value is the same as the destination point.
- When one loop ends, a loop that checks prev_vertex starts.    
-> The shortest path for each vertex and the shortest path to the destination are traced back and the path is output. That is, 1 -> 2 is output.     

---------------------------------------------------------------------

3. DIJKSTRAMIN (minheap)

DIJKSTRAMIN performs the same function as DIJKSTRA.    
DIJKSTRA sorts through set, and DIJKSTRAMIN sorts through min heap.    

![image](https://user-images.githubusercontent.com/88877637/149550039-1fea5af6-562b-4a61-8347-4959468fc2e1.png)

example) I will explain with the same example as in DIJKSTRA. (1->2 shortest distance)    
- 길이를 저장하는 배열에 IN_FINITY를 모두 초기화한다    
- 비용을 첫번째 인자, 도착지를 두번째 인자로 push를 이용해 min heap에 넣고 시작한다.(출발지인 1을 넣을 때는 비용은 0이고 도착지는 1이다.)     
- 총 min heap이 빌 때까지 반복하며 중간에 도착지가 나오면 반복을 종료한다.     
- 첫번째 요소가 min heap에서 나오면서 1에 인접한 vertex로의 원래 비용과 경유하는 비용을 계산해 더 작은 값을 vertex와 함께 min heap에 넣어준다    
-> 즉 2,3,4가 들어간다. 이때 prev_vertex에 어디에서 이동한 것인지 저장한다. (1이 저장된다.)    
- min heap은 push할 때 key값에 따라 정렬되기 때문에 2,3,4로 가는 비용 중 가장 작은 4로 이동하면서 min heap에서 지워지고 4에서 6으로 이동하는 경로가 min heap에 들어간다.    
- 이때 1에서 2로 이동하는 경로가 최소가 된다. min heap에서 2로 이동하는 경로를 뺀다.    
- 나온 값이 도착지점과 같기 때문에 끝난다.    
- 하나의 반복문이 끝나고 나면 prev_vertex를 확인하는 반복문을 동해 각 정점 별 최단 경로와 도착지의 최단경로를 역추적해 경로를 출력했다. 즉 1 2로 출력된다.    

---------------------------------------------------------------------

4. BELLMANFORD

모든 경로를 여러 번 계산하기 때문에 다익스트라 알고리즘에 비해서 시간이 오래 걸린다.    
하지만 간선의 비용이 음수일 때에도 음수 사이클이 발생하지 않는다면 문제없이 사용할 수 있다는 장점이 있다.    
벨만 포드 알고리즘은 각 정점의 값을 무한대로, 이전 위치는 -1으로 초기화한다.    
d의 시작 정점에 0을 넣고 시작한다.    

![image](https://user-images.githubusercontent.com/88877637/149550100-0bc5a23c-0438-47e8-9a46-4c1475df9ea4.png)

example) 위와 같은 그래프에서 1에서 3으로 가는 최단경로    
- d의 1자리를 0을 넣고 d[2]=2 d[3]=8, d[4]=1이 된다.    
- 2에서 1으로 가는 값을 본다, d[1]에 2를 넣으려고 하지만 d[1]=0이기 때문에 넣지 못한다.    
- 3에서는 d[6]=9, d[5]=16이 된다.     
- 4에서는 d[6]=9에서 4로 바뀐다.     
- 5에서는 d[6]=4이기 때문에 25로 바뀌지 않는다.     
- 6에서는 d[3]=8에서 5로 바뀌고, d[5]=16에서 13으로 바뀐다.    
-> 위와 같이 동작하면 1바퀴가 돈 것으로 볼 수 있다.    
- 이와 같은 반복을 총 n-1번하면서 해당 정점을 경유를 했을 때 값이 작아지면 값을 갱신하고 p에 이전 위치를 저장한다.    
- n-1번 했을 때 값이 최단경로의 비용으로 볼 수 있고 p를 통해 경로를 알 수 있다.    
- 벨만 포드에서 예외처리 해야 할 음수 사이클은 n-1번의 반복을 한 뒤에 1번 더 위 동작을 실행해보면 알 수 있다.    
-> 1번 더 반복했을 때 정점의 값이 달라지는 경우가 있다면 음수 사이클이 존재하는 것이다.    

---------------------------------------------------------------------

5. FLOYD

다른 알고리즘들과는 달리 모든 정점 쌍에 대해 최단 거리를 구하며, 음의 비용을 갖는 간선이 있어도 사용할 수 있다.    
FLOYD 알고리즘은 s에서 e까지 이동할 때 최단거리를 중간 경유지인 w를 이용해 구한다.    
즉 s에서 w까지의 최단거리와 w에서 e까지의 최단거리를 이용한다.    
- FLOYD 알고리즘을 구현하기 위해서는 일단 2차원 배열을 선언한다.    
-> 형식은 a[출발 정점][도착 정점]으로 보면된다.    
- 그래프를 통해 직접 연결된 값들을 각 위치에 알맞게 초기화한다. 만약 연결되어 있지 않다면 무한대를 저장하고, a[1][1]와 같이 출발정점과 도착정점이 같으면 0을 저장한다.    
- for문 3개를 통해 현재 저장되어 있는 값과 중간 지점을 경유해서 갔을 때를 비교한다.    
- 경유해서 간 경우가 더 비용이 적다면 a[i][j]위치에 a[i][k]+a[k][j]를 저장한다.    
- 음수 사이클을 확인하는 방법은 a[i][i]가 0보다 작으면 음수 사이클이 있는 것이다.

![image](https://user-images.githubusercontent.com/88877637/149550247-b5676320-d7ed-41af-829c-62df8115e8f4.png)

example) 위와 같은 그래프가 있다면

0	4	-1	8   
INF	0	-2	-10    
INF	INF	0	3    
INF	INF	INF	0       -> 초기화를 한번 돌 때

0	4	-1	-6    
INF	0	-2	-10    
INF	INF	0	3    
INF	INF	INF	0      -> 가장 큰 반복문을 2번 돌았을 때

0	4	-1	-6    
INF	0	-2	-10    
INF	INF	0	3    
INF	INF	INF	0       -> 가장 큰 반복문을 3번 돌았을 때

---------------------------------------------------------------------

# Rabin-Karp

라빈-카프 알고리즘은 해시를 긴 데이터를 짧은 데이터로 바꾼다.    
각 짧은 데이터끼리 비교해 같은 문자인지 확인한다.    
다르게 보여도 같은 문자일수 있기 때문에 한 번 더 문자를 하나 하나 비교해 같은지 확인해 같은 문자열을 찾아내는 알고리즘이다.    

문자의 아스키코드 값에 2의 제곱 수를 차례대로 곱하여 더해준 해시방법을 사용했다.    
문자가 다르더라도 간혹 해시 값이 같게 나올 수 있다.
- 첫번째로 큰 문자열의 크기- 작은 문자열의 크기만큼 반복하는 반복문을 선언
- 첫번째 반복문 안에 작은 문자열의 길이만큼 반복하는 반복문을 만든다.
- 뒤에서부터 앞으로 2의 제곱수와 문자의 아스키코드를 곱하고 더해 해시를 구해준다.
- 처음에는 추가만 해주면 되고 처음이 아니라면 앞의 문자1개의 해시 값을 빼고 뒤의 해시 값을 더해줘야 한다. 
- 해시 값이 같다면 각각의 문자를 비교해준 뒤 같으면 success를 반환한다
- 해시 값이 같지 않으면 LoadFileExist(임의로 설정한 오류)가 반환된다.
abacabacaaba와 abacaaba를 예로 들자면 작은 문자열의 해시는 24833으로 고정되어 있고 큰 문자열을 이동하면서 해시를 계산한다.
첫번째 큰 문자열의 해시는 24837이므로 작은 문자열의 해시와 다르다.
두번째 큰 문자열의 해시는 24939이므로 작은 문자열의 해시와 다르다
세번째 큰 문자열의 해시는 24833으로 작은 문자열의 해시와 같다. 이때 문자열의 문자들을 비교해 같으면 success를 다르면 LoadFileExist를 반환한다

---------------------------------------------------------------------

# 정렬 알고리즘

1. Quick sort

퀵 정렬은 재귀함수를 이용하기 때문에 함수로 구현을 했다.    
퀵 정렬은 리스트안의 한 요소를 선택해 그 요소를 pivot으로 둔다.    
pivot을 기준으로 pivot보다 작다면 pivot의 왼쪽으로, pivot보다 크다면 pivot의 오른쪽으로 옮겨진다.
옮겨지고 난 뒤 pivot을 제외하고 왼쪽과 오른쪽을 다시 정렬하는데 pivot을 기준으로 나눠진 두개의 배열에 새로운 pivot을 정해서 계속해서 반복한다(재귀함수).    
계속해서 나눠지다가 배열의 크기가 0이거나 1이 된다면 종료한다.    

example) 3 7 2 0 6 1 을 quick정렬을 하자.    
- pivot을 3으로 한다면 3와 7을 비교한다.    
- 7이 크기 때문에 3과 1을 비교한다.     
- 1이 작기 때문에 1과 7의 위치를 바꾼다. -> 3 1 2 0 6 7	    
- left와 right의 위치를 업데이트한 뒤 2와 6으로 바뀌고 위와 같은 동작을 한다.    
->하지만 위 상황과 반대기 때문에 위치를 변경시키지 않는다.     
- left와 right가 만난다(6)    
- 3과 6을 비교해 3이 작기 때문에 6의 왼쪽으로 이동한다. ->1 2 0 3 6 7(3은 고정)    
- 새로운 pivot 1설정(이전보다 작은 값), 2와 0을 pivot과 비교-> 1 0 2 3 6 7    
- left와 right가 만난다(2)    
- 1과 2를 비교해 1이 작기 때문에 2의 왼쪽으로 이동한다. ->0 1 2 3 6 7    

--------------------------------------------------------------------- 

2. Insert sort

삽입 정렬은 두번째 요소부터 시작해 그 앞의 요소들과 비교한 뒤 삽입할 위치를 지정한다.    
그 다음 한 칸 뒤로 이동해 나머지 앞의 요소들과 비교한다.    
위 동작을 반복해 총 삽입될 값의 수만큼 반복하면 끝난다.    

example) 5 3 8 1 2 7을 정렬한다.    
- 2번째인 3부터 시작한다    
- 5>3이므로 3이 앞으로 이동한다 -> 3 5 8 1 2 7    
- 8>5이므로 그대로 -> 3 5 8 1 2 7    
- 1<8, 1<5, 1<3 이므로 맨 앞으로 간다. -> 1 3 5 8 2 7    
- 2<8, 2<5, 2<3 이므로 2번째로 간다. -> 1 2 3 5 8 7    
- 7<8 이므로 한 칸 앞으로 간다. -> 1 2 3 5 7 8     
- 정렬이 끝난다.

--------------------------------------------------------------------- 

3. Merge sort

큰 문제를 작은 문제로 나눠 해결한 뒤 다시 합치는 정렬방식이다.    
배열에 정렬되지 않은 수가 있다면 나눌 수 있는 만큼 작게 분리해준다.    
분리한 순서와 반대로(마지막에 분리한 것을 가장 먼저) 합친다.    
합칠 때는 각 값들을 정렬해 합친다.   
example) 3 4 1 5 2를 정렬한다
- 341, 52로 분리 34,1,5,2로 분리 3,4,1,5,2로 분리하다.
- 가장 마지막에 분리된 34를 합친다.
- 34와 1을 합치고 5 2를 합친다-> 134, 52
- 마지막으로 전부 합친다->12345

--------------------------------------------------------------------- 

4. Heap sort

Heap sort는 min heap으로 구현했다.    
push를 이용해 heap에 값을 넣는다.    
push를 할 때는 맨 끝에 삽입한 후 자신의 부모(자신 index/2)와 비교해 작으면 부모와 위치를 바꾼다.    
root까지 올라갈 수 있다.    

example) 5 3 7 1 을 정렬한다     
- 5는 root가 된다.
- 3이 자식으로 삽입되고 부모인 5와 비교해 3이 root가된다.
- 7이 자식으로 들어오고 부모인 3보다 크기 때문에 그대로 자식이 된다.
- 1은 5의 자식으로 들어간다. 부모인 5보다 작기 때문에 5와 바꾸고 그 위치의 부모인 3과 비교한다.
- 3보다 작기 때문에 1은 새로운 root가 된다.
- 이후 pop을 해 root를 빼준다. 
- 1이 빠지고 가장 마지막 위치에 있던 5가 올라오고 자식과 비교를 한 뒤 3이 root가 된다.
- 이와 같은 방법으로 pop을 3번 더해주면 1 3 5 7으로 출력된다.
즉 삽입할 때 경우 마다 처리해줘야 하며 삽입한 후에 pop을 해 빼줘야하기 때문에 비효율적이다.

--------------------------------------------------------------------- 

5. Bubble sort

Bubble sort은 Insert sort과 거의 반대이다.    
앞에서부터 뒤로 이동하면서 비교한다.    
첫번째 요소와 두번째 요소, 두번째 요소와 세번째 요소, 이처럼 진행한다.    
총 1회전 당 1개의 값의 위치가 고정되는 것이다.    
즉 n개의 값이 있다면 n-1회전을 해 정렬할 수 있다.    

example) 7 4 5 1 3을 정렬한다
- 7>4, 7>5, 7>1, 7>3 이므로 4 5 1 3 7이 된다.
- 4<5, 5>1, 5>3 이므로 4 1 3 5 7이 된다.
- 4>1, 4>3이므로 1 3 4 5 7이 된다.
- 1<3이므로 그대로 유지된다.

--------------------------------------------------------------------- 

6. Selection sort

제자리에서 정렬하는 알고리즘으로 주어진 배열의 최솟값을 찾아 맨 앞의 값과 교체한다.    
맨 앞의 값을 제외한 배열에서 최소값을 찾아 2번째 위치에 넣어준다.    
위와 같은 동작을 원소가 1개 남을 때까지 진행한다.    

example) 9 6 7 3 5를 정렬한다
- 최솟값 3 이므로 3 6 7 9 5
- 최솟값 5 이므로 3 5 7 9 6
- 최솟값 6 이므로 3 5 6 9 7
- 최솟값 7 이므로 3 5 6 7 9
