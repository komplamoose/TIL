# 알고리즘 : 분기한정

---

## 0-1 배낭 문제

> 0-1 배낭 문제를 이번엔 분기한정으로 풀어보자
> 
<br>

### 접근법

- 우선 아이템을 기존과 같이 단위 무게로 정렬한다.
    - `Bound` 보장하기 위해 필요
- 매 노드 방문시마다, 실제로 상태공간 트리의 노드를 만든다.
- 노드의 `Bound` 값을 기준으로 정렬되는 `우선순위 큐`를 만든다.
- `Promising` 조건
    - 이 노드의 `Bound` 값이 과연 현재 구한 `Maxprofit`보다 큰가?
- 조건 만족한다면, 이 노드의 자식노드에 대해서도 `유망`한지 체크해주고, `유망`하다면 `PQ`에 넣어준다.
- 다시 돌아와서 `PQ`에서 하나 `Pop`한다.
- `PQ`가 빌 때까지 반복
<br><br>

### 전체 코드

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef struct node* node_ptr;
typedef struct node{
    int level;
    int weight;
    int profit;
    float bound;
    node (){ // 생성자
        level=0;
        weight=0;
        profit=0;
        bound=0;
    }
}node_t;

int n, W;
int w[100001]; // 총 물건 무게
int v[100001]; // 물건 가치
int maxprofit=0;

vector<pair<int,pair<int,int>>> temp;

struct compare { // Bound가 큰 값 기준으로 정렬하는 비교 구조체
    bool operator()(node_ptr a, node_ptr b){
        return a->bound < b->bound;
    }
};

float bound(node_ptr u) { // Bound 값을 계산해주는 함수
    int j, k, totweight;
    float result;
    if (u->weight >= W) { // 만약 이 노드의 무게가 최대 용량을 초과한다면, Bound=0, 그냥 이 노드는 취급해주면 안됨
        return 0;
    }else {
        result = u->profit; //  result => Bound임. 현재까지 구한 Profit 담아줌
        j = u->level + 1; // 아직 선택 안한 아이템들 다 체크하자
        totweight = u->weight; // 무게 그대로 상속
        while ( j <= n && totweight + w[j] <= W) { // 최대 아이템까지 탐색하면서, 이 아이템을 넣었을 때 무게가 최대 용량보다는 작거나 같아야 함
            totweight += w[j];
            result += v[j];
            j++;
        }
        // j번째 아이템은 넣으면 가방 터져서 못넣었음 ㅠㅠ
        k=j;
        if (k <= n) // 만약 k가 n보다 크다면, 모든 물건 다 넣었다는 뜻임
            result += (W-totweight) * ((float)v[k]/w[k]); // 아까 커서 못넣은 j번째 아이템 남은 공간만큼 잘라서 넣자.
        
        return result;
    }
}

node_ptr create_node() { // 노드 생성 함수
    node_ptr temp = new struct node;
    return temp;
}

void print(node_ptr temp) // 문제조건 출력을 위한 노드 출력함수
{
    cout << temp->level << " " << temp->weight << " " << temp->profit << " " << temp->bound << endl;
}

void knapsack6(){
    priority_queue<node_ptr, vector<node_ptr>, compare> PQ; // 분기한정을 위한 우선순위 큐, Bound 값 기준으로 내림차순 정렬됨
    node_ptr u, k;
    k=create_node();
    k->level=0; k->weight=0; k->profit=0; k->bound=bound(k); // 제일 첫번째 Root 노드 방문 경우.
    PQ.push(k);
    print(k);
    while (!PQ.empty()) {
        k=PQ.top(); PQ.pop(); // 하나 뽑는다.
        if (k->bound > maxprofit) { // 뽑은 노드가 유망하다면
            u = create_node(); // 자식 노드 생성 (Case 1 : 다음 레벨의 아이템 넣는 경우)
            u->level=k->level+1; // 부모 다음 레벨
            u->weight=k->weight + w[k->level +1]; // 다음 레벨의 아이템 넣는 경우니까, 부모 노드에 다음 레벨 아이템 무게 추가
            u->profit=k->profit+v[k->level+1]; // 넣는 경우니까 Profit 추가
            u->bound=bound(u); // Bound도 계산해줌
            print(u);
            if (u->weight <= W && u->profit > maxprofit){ // 다음 아이템 넣었던 노드 U의 총 무게가 가방 최대 무게를 넘지 않고, 동시에 Maxprofit보다 profit이 더 크다면, maxprofit을 갱신함.
                maxprofit=u->profit;
            }
            if (u->bound > maxprofit){ // 이 자식노드 u가 유망한지 체크한다. (뿌리 내렸을 때, 현재의 maxprofit보다 더 커질 수 있는 가능성이 존재하는지 체크)
                PQ.push(u);
            }
            u = create_node(); // 다음 레벨의 아이템을 안넣는 경우로 자식 노드 생성
            u->level=k->level+1; u->weight=k->weight; u->profit=k->profit; u->bound=bound(u); // 레벨만 늘어나고, 나머진 상속받음
            print(u);
            if (u->bound > maxprofit){ // 유망한지 체크
                PQ.push(u);
            }
        }
    }
}

int main()
{
    cin >> n >> W; // 물건 갯수와 가방 용량 입력받기
    
    for (int i=1; i<=n; i++) {
        cin >> w[i];
    }
    for (int i=1; i<=n; i++) {
        cin >> v[i];
    }

    // 단위무게로 정렬 START
    vector<pair<int,pair<int,int>>> temp; 
    for (int i=1; i<=n; i++) {
        temp.push_back(make_pair(v[i]/w[i],make_pair(w[i],v[i])));
    }
    sort(temp.begin(), temp.end(), greater<>());

    for (int i=0; i<n; i++) {
        w[i+1]=temp[i].second.first;
        v[i+1]=temp[i].second.second;
    }
    // 단위무게로 정렬 END

    knapsack6();

    cout << maxprofit << endl;
}
```
