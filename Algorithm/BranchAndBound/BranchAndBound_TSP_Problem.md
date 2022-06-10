# 알고리즘 : Branch and Bound

---

## 외판원 순회 문제

> 외판원 순회 문제를 분기한정법으로 풀어보자.
> 

<br>

### 상태공간트리 설정

- 도시에 연결된 모든 도시들을 자식으로 가진다.
- 총 `N`개의 도시가 존재할 때, `N-1`번째 도시에 방문하는 경우, 종료시킬 수 있다.
    - 어짜피 남아있는 도시는 하나 뿐이니까, `N-1`번째 도시와 아직 방문 안한 나머지 1개인 `N`번째 도시가 연결된 상태인지 체크하기만 하면 된다.
    - 또한 이 때, 선택된 `N`번째 도시는 `출발 도시`와 연결되어 있어야 한다.

<br>

### 평가함수 (Bound) 설정

- `Bound`
    - **아직 방문 안한 모든 도시들을 방문하였을 때의 최소 경로 길이 값.**
- 기존의 `Bound`가 최대로 다다를 수 있는 `Upper-Bound`를 구헤야 하는 문제였다면, 이번 문제에선 이 노드 기준으로 앞으로 진행하였을 때 최대 줄이면 이정도까지 줄일 수 있다는 `Lower-Bound`를 구해내야 한다.
- 각 선택된 도시마다 다른 도시로 뻗어나가는 엣지가 있다고 가정하자.
    - 이 때, `TSP`는 `DiGraph`를 가정하므로, 들어오는 엣지가 아닌, 밖으로 빠져나가는 `OutGoing` 엣지만 고려한다.
- 아직 안 고른 도시들의 `OutGoing` 엣지 중, 가중치가 가장 낮은 엣지들만 골라서 더 해준다면, 이것은 진짜 무슨 짓을 해도 이것 이하로는 낮아질 수 없는 `Lower-Bound`가 될 것이다.
    - 실제로 그 경로들이 `TSP` 조건을 만족하는지는 중요하지 않다. 진짜 무슨 짓을 하더라도 이것보다 작을 수 없다는 조건을 구하기 때문이다.
    - `0-1 Knapsack`에서도, 물건을 잘라서 넣을 수 없음에도 잘라서 넣었음을 기억하자.
- 어떻게 구해낼까?
    1. 일단 모든 도시들의 최소비용 엣지들의 합을 구해준다.
    2. 이렇게 고른 최소비용 엣지가 만약 내가 여태까지 왔던 경로인 `Path`에 포함된 엣지라면, 제외시켜준다.

<br>

### 구현

- 초기 최소길이는 `INF`로 설정해준다.
- `Promising` 조건
    - 이 노드의 `Bound`가 현재의 `minlength`보다 작으면 `유망`하다.
    - 이 노드가 `유망`하다면, `PQ`에 넣는다.
    - 이 노드의 자식들의 `Bound` 또한 구해서, `유망`한 경우 `PQ`에 삽입한다.
    - `PQ`는 `Bound` 값을 기준으로 하는 `Min-Heap`이다.
- `PQ`의 `Top`을 뽑아낸다.
- `minlength`는 결국 최종 레벨인 `N-1` `Depth`까지 도달해야만 업데이트 할 수 있다.
- 초반엔 유의미한 `Minlength`를 구해내기 위해, 초기엔 상태공간트리를 `DFS`처럼 깊이 우선 탐색을 한다.
- 만약 노드의 `Depth`가 `N-1`에 도달했다면,
    - 이 경로에서 `아직 안 방문한 도시` 하나를 찾아, `N-1`번째 방문 도시와 `연결`되었는지 체크해준다.
        - `연결`되었다면, `마지막으로 방문한 도시`와 `처음에 방문한 도시`가 `연결`되었는지 체크해준다.
            - 이 모든 조건을 만족한다면, 올바른 `TSP Pass`로 인정해주고, `minlength`를 이 `pass`의 경로합으로 업데이트 해준다.
- 이제 다음 `PQ`에서 값을 뽑아줄 때, 만약 뽑은 노드의 `Bound` 값이 내가 구한 `Minlength`보다 크다면, 여기서 진행해봤자 `Minlength`보다 무조건 큰 값이 나올 수 밖에 없다는 뜻이므로, 가지치기 해준다.
    - 만약 작다면, `PQ`에 넣어준다.
        - 같은 경우 넣을 필요 없다. 굳이 안탐색해도 이미 동일한 최소 길이를 구해낸 상태니까.
- 노드가 `N-1 Depth`에 도달했다면?
    - 도시의 번호들이 `1`부터 `N`까지 존재한다고 했을 때, 내가 방문한 도시들의 `번호 합`을 빼주면, 내가 방문 안한 도시의 번호가 나올 것이다.
        - `1~N의 합` - `(내가 여태까지 방문한 도시들의 번호 합)`

<br>

### 주의🤨

- 매 순간 완벽하게 `Optimal`한 값을 구할 수는 없다.
- 일종의 `Approximation` 알고리즘이다. (근사 알고리즘)
- `Optimal`한 결과라고 확정할 수는 없지만, 매우 비슷한 값을 구해낸다.
    - `Globally Optimal`하다고 확정할 순 없지만, `Local Optimal`한 솔루션을 구해낸다.

### 전체 코드

> 🖕 모든 의구심을 주석으로 풀어넀다.
> 

```cpp
#include <iostream>
#include <vector>
#include <queue>
#define INF 10000001

using namespace std;

int W[100][100];

int vert, edge;

typedef struct node* node_ptr;
typedef struct node {
    int level;
    vector<int> path;
    int bound;
    node() { // 생성자, new 호출시 자동으로 호출된다.
        level=0;
        path.clear();
        bound=INF;
    }
}nodetype;

struct compare{
    bool operator()(node_ptr a, node_ptr b) {
        return a->bound > b->bound; // 오름차순
    }
};

int length(vector<int> path) {
    int len=0;
    for (auto it=path.begin(); it!=path.end(); it++) {
        if (it!=path.end()-1) { // end의 경우 더이상 갈 곳이 없기 때문에, 여기서 앞으로 진행해갈 "경로"는 없음. length 함수는 이미 경로 마지막에 1을 추가한 경우에만 동작함
            len += W[*it][*(it+1)]; // 경로의 다음 도시로 가는 길이를 합함. end()의 경우 마지막 1인데, 여기의 다음 경로는 없음
        }
    }
    return len;
}

bool hasOutGoing(int v, vector<int> path) { // 1부터 end-1까지에 위치한 버텍스들은, 최소한 다음 버텍스에게 OUT 하는 엣지를 가지고 있다. 여기서 누군가를 밟으러 간다. 
                                            //엣지의 가능성을 체크하기 위해 고려할 필요가 없는 버텍스들이다.
                                            // 이미 이 버텍스들은 다른 도시를 향해 뻗은 엣지가 있으므로, 체크 안해주면 뻗어나가는 Edge가 2개가 되므로 제외
                                            // Path의 마지막 (path.end)의 도시의 경우, 경로엔 있지만, 아직 어떤 도시로 뻗어갈 지 모르기 때문에, 제외하지 않는다.
    for (auto it = path.begin(); it!=path.end()-1; it++) {
        if (*it==v) return true; 
    }
    return false;
}

bool hasInComing(int v, vector<int> path) { // 2부터 end까지에 위치한 버텍스들은, 누군가에 의해 밟혀진다. Bound 함수 계산시, 새롭게 아직 방문 안된 도시를 고려할 것이기 때문에, 
    for (auto it = path.begin()+1; it != path.end(); it++) { // 1번 도시는 밟혀질 수 있다. 마지막 도시에서 1번 도시로 가는 경우가 있기 때문에, 1번 도시도 이미 경로에 있다고 안밟힐 도시로 취급하면 안된다.
        if (*it==v) return true;
    }
    
    return false;
}

int bound(node_ptr temp) {
    int lower = length(temp->path); // 이 노드의 현재까지 걸어온 길의 가중치 합
    for (int i=1; i<=vert; i++) { // 모든 버텍스 검사 
        if (hasOutGoing(i, temp->path)) continue; // 만약 이 버텍스가 out-going에 속한다면? => 이미 이 버텍스는 다른 도시를 향해 뻗어 나가 있음. 
        //아직 다른 도시로 가지 않은, 도시만을 고려하여야 함. Path의 마지막에 위치한 도시의 경우도 아직 어떤 도시로 갈지 선택 안한 경우기 때문에, OutGoing 엣지가 없는 경우로 처리해아 함.
        int min = INF;
        for (int j=1; j<=vert; j++) { // 이 i버텍스에서 갈 수 있는 버텍스 검사
            if (i==j) continue; // 자기 자신 패스
            if (j==1 && i == temp->path[temp->path.size()-1]) continue; // 내가 밟으려고 고려하는 경로가 출발 정점인데, 만약 밟으려고 출발할라는 도시가 현재 마지막 경로인 경우
            // 자세히 설명해야 이해가 간다.
            // 일단 가려는 도시가 j인데, i가 path의 마지막 경로가 아니어야 되는 이유 => path의 마지막 경로가 아닌 아직 선택 안한 도시의 경우, 마지막 도시로 선택되어 1번 도시로 돌아갈 수 있는 가능성이 존재한다.
            // 만약 이 i가 중간과정의 path 마지막 도시인 경우, 이 i는 절대 TSP Path의 출발정점 재방문 직전 마지막 도시로 선택될 수 없다.
            // Bound 검사를 한다는 것은, 이 노드(경로)는 아직 도시들을 하나 빼고 다 밟아본 상태가 아니라는 것을 의미한다.
            // 근데 만약 i가 path의 마지막 경로인데, j가 1이라는 것은, path의 중간지점에서 첫 번째 출발 정점으로 가는 경우를 의미하는 것인데, 이런 경우는 모든 조건을 살펴봐도 존재하지 않는다.
            // 첫 번째 도시로 가는 경우는 무조건 마지막 도시에서 가야 한다. 근데 이 프로그램에선 마지막 도시의 경우는 Bound 함수를 체크하지 않는다.
            // 그러므로, 갈 수 있는 경우의 수에서 첫 번째 도시를 방문하는 경우는 아예 존재할 수 없는 경우이므로, Bound 값 계산에서 고려하지 않아도 된다.
            if (hasInComing(j, temp->path)) continue; // 내가 이제 밟으려고 하는 j가 이미 밟힌 도시인지 체크 (내가 선택한 경로에 이 도시가 존재함을 의미)
            // hasInComing 이라는 것은, 이 도시는 이미 다른 도시에 의해 밟힌 도시라는 뜻이다. (이미 내가 지나온 경로에 포함되었다는 뜻)
            if (min > W[i][j]) min = W[i][j]; // 
        }
        lower+=min;
    }

    return lower;
}

node_ptr create_node() {
    node_ptr temp = new struct node;
    return temp;
}

bool isIn(int i, vector<int> path) {
    for (auto loop : path) { // 끝까지 검사해서 찾으면, i번 버텍스가 내가 지나왔던 경로에 존재한다는 뜻이다.
        if (loop==i) return true;
    }

    return false;
}

int remaining_vertex(vector<int> path) {
    int sum=0;
    for (auto loop : path) {
        sum+=loop;
    }
    
    return ((vert*(vert+1))/2)-sum; // 어짜피 모든 버텍스 밟아야하니 인덱스는 1부터 n까지 존재, 
    //마지막 하나 안밟은 애는 1부터 n까지의 합에서 내가 여태까지 밟은 버텍스 인덱스합을 빼면 
    //안밟은 버텍스의 인덱스가 나온다.
}

void print(int level, int bound, vector<int> path) {
    if (bound>=INF) {
        cout << level << " " << "INF" << " ";
        for (int i=0; i<path.size(); i++) {
            cout << path[i];
            if (i<path.size()-1) cout << " ";
        }
        cout << "\n";
    }else{
        cout << level << " " << bound << " ";
        for (int i=0; i<path.size(); i++) {
            cout << path[i];
            if (i<path.size()-1) cout << " ";
        }
        cout << "\n";
    }
}

void travel2(vector<int>& opttour, int& minLength) {
    priority_queue<node_ptr, vector<node_ptr>, compare> PQ; // Bound 기준으로 정렬되는 Min-Heap
    node_ptr u, v; 
    opttour.resize(vert+1); // Copy할라면 capacity 늘어나야함. 
    v=create_node();
    minLength=INF; // 루트 노드 설정
    v->level=0; v->path.push_back(1); v->bound = bound(v); // 첫번쨰 출발점 (1번도시) 루트노드 설정
    print(v->level, v->bound, v->path); // 루트노드 방문한 것과 마찬가지니까 출력
    PQ.push(v);
    while(!PQ.empty()) {
        v=PQ.top(); PQ.pop(); // 일단 뽑는다.
        if (v->bound < minLength) { // 유망한지 검사. 유망 안하면 그냥 패스함
            for (int i=2; i <= vert; i++) { // 이 노드에서, 아직 방문 안한 도시들을 구해내기 위해, 일단 모든 도시를 수를 체크한다.
                if (isIn(i,v->path)) continue; // 만약 이 버텍스에서 내가 가려고 하는 다음 버텍스가, 이미 path에 존재한다면, 한번 밟은 애임. 
                u=create_node(); // i가 이미 v path에 존재한다면, 이미 밟았던 도시라는 뜻이므로, 이 노드의 자식노드로 고려하지 않는다. 자식노드는 이 도시에서 방문할 수 있으면서, 아직 안밟은 도시를 의미하기 때문이다.
                u->level=v->level+1; // 다음 레벨 자식 노드를 생성하기 위한 작업
                u->path=v->path; // 패스는 일단 그대로 상속받는다.
                u->path.push_back(i); // 상속받은 패스에 이제 밟으려고 하는 버텍스를 추가함. 이것은 자식 노드를 생성하는 과정이기 때문이다. 
                if (u->level == vert-2) { // 만약 n-2 단계까지 왔다면, 남은거 뭔지 찾아서 그냥 계산하면 됨. 레벨은 0단계에서 시작하였으므로, N-2에 도달하였을 때, 남아있는 도시 하나를 노드 생성 안하고 바로 구해낼 수 있다.
                    u->path.push_back(remaining_vertex(u->path)); // Path에서 안 발은 도시를 찾아내는 방법을 통해 아직 안밟은 도시를 경로에 추가한다.
                    u->path.push_back(1); // 아직 안밟은 1개의 도시는 반드시 1번 도시로 돌아가야 하므로, 경로에 추가한다.
                    print(u->level, length(u->path), u->path); // 노드에 방문하였으므로 출력
                    if (length(u->path) < minLength) { // 이 경로는 근데 MinLength보다 작아야만 의미 있다. 체크해주자.
                        minLength = length(u->path); // 임의로 추가한 마지막 도시가 출발 정점으로 갈 수 있는지 없는지 체크 안하는 이유 => 갈 수 없는 경우 이 경로 합은 기존 경로합 + INF가 되는데, 무조건 최대값 Minlength인 INF보다 큰 것이 자명하기 때문이다.
                        copy(u->path.begin(), u->path.end(), opttour.begin()); // 찾은 최적경로 저장
                    }
                }
                else { // 만약 노드가 아직 N-2 레벨에 도달하지 못했다면, (인터널 노드라면)
                    u->bound = bound(u); // 이 노드의 bound 구함
                    print(u->level, u->bound, u->path);
                    if (u->bound < minLength) { 
                        PQ.push(u); // 안유망하면 (바운드가 minlength보다 같거나 크면, 더이상 탐색 필요 없음) 안넣음
                    }
                }
            }
        }
    }
}

int main()
{
    cin >> vert >> edge; // 총 버텍스와, 엣지 입력받음

    for (int i=0; i<edge; i++) {
        int x, y, weight;
        cin >> x >> y >> weight;
        W[x][y]=weight;
    } // Digraph이므로 진행

    for (int i=1; i<=vert; i++){
        for (int j=1; j<=vert; j++) {
            if (i==j) continue;
            if (W[i][j]==0) W[i][j]=INF;
        }
    } // 자기 자신=0, 직통으로 갈 수 없는 경우 INF로 초기화

    vector<int> opttour; // 최적의 경로를 저장하는 배열
    int minLength; // 최적(최소) 값을 저장하는 변수

    travel2(opttour, minLength); // 최적값 구하러 가자

    cout << minLength << endl;
    
    for (int i=0; i<opttour.size(); i++) {
        cout << opttour[i];
        if (i<opttour.size()-1) cout << " ";
    }
    cout << endl;
}
```
