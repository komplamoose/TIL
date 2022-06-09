# 알고리즘 : Backtracking

---

## 0-1 배낭문제 : 백트래킹

> 0-1 배낭 문제를 백트래킹을 이용하여 풀어보자. 
무게-가치로 이뤄진 아이템 N개가 존재할 때, 용량 W의 가방에 최대 가치를 담는 경우를 구하라.

단, 물건은 넣는지-안넣는지 (0-1) 두 가지 경우의 수 밖에 없다.
> 
<br>

### 문제 설명

- 백트래킹은 기본적으로 브루트포스에서 유래된다.
- 물건을 넣냐-안넣냐로 모든 경우의 수를 다 따져보자
- 부분 집합의 합 문제와 비슷하다고 생각할 수 있지만, 조금 다르다.
    1. 모든 솔루션을 다 구할 필요가 없다.
    2. 최적화 문제다. 반드시 Leaf node까지 도달할 필요가 없다. 중간 노드가 Optimal할 수 있다.
    3. 지속적으로 트리를 탐색해가면서, 탐색한 노드의 값이 최적값보다 크가면, 최적 값을 업데이트 한다.

<br>

### 상태공간트리 설정

- 이 Depth의 물건을 넣냐-안넣냐로 이진트리 생성
- 최적화 문제이므로, 뿌리 내릴때마다 이 Case가 최적의 값을 지니는지 체크헤야 함.
<br>

### 가지치기 전략

- 그냥 트리 전체를 그린다면?
    - `2^(n+1)-1`개의 노드를 가진 트리가 생성된다.
- 가지치기를 잘 해줘야 한다.
1. 만약 `현재까지 담은 아이템 ≥ 최대용량`이라면? 더 이상 가지를 뻗어나가지 않는다.
    1. `현재까지 담은 아이템 = 최대 용량`인 경우까지 체크하는 이유는, 어짜피 더이상 아이템을 추가할 수 없음 ⇒ `가지 내릴 필요 없음` 을 의미하기 때문이다.
2. `현재까지 고른 선택의 가치 합` + 아직 선택 안 한 아이템들의 가치들을 최대한 담는 방식으로 구한 한계치 `Bound`가 내가 여태까지 탐색하면서 구한 `Optimal한 값`보다 작다면, 가지 내릴 필요가 없다.
    1. *Bound의 값이 실제로 구현 가능한지 아닌지를 떠나서, Bound라 함은 진짜 쥐어짤만큼 쥐어짜봤자 최적값보다 모자람을 체크하는 용도다.*

<br> 

### 유망함수 설정 ☑️

- 우선 물건은 단위무게로 정렬하여, Greedy하게 고른다.
- 조건 1은 체크하기 쉬우니까 넘어가자.
- 조건 2 : Bound 구현
    - `totWeight` : `현재까지의 구한 가방의 Weight` + `남은 경우의 수인 K번째 전까지 아이템들의 Weight 합`
        - 이때 남은 경우의 수 한계치 `K`는, `K`번째 아이템을 넣었을 때 **최대용량 초과하는 경우**의 아이템 인덱스로 체크한다.
        - `k-1`번째까지 체크하며, `k`번째는 자리가 없어서 못 넣는다.
    - `Bound` : (`현재까지 구한 아이템의 Profit` + `남은 경우의 수인 K-1번째까지의 아이템들의 Profit 합`) + (`총 가방 용량` - `totWeight`) * (`Pk` / `Wk`)
        - `Bound` : 실제로 이 값이 존재하는지 여부는 중요하지 않고, 정말 우겨담을만큼 우겨담은 값임. 이 값이 최적값보다 적다면 진짜 무슨 짓을 해도 최적값보다 작다는 것
            - **가지치기 조건이 된다.**

<br>
<br>

### 시뮬레이션

- 제일 처음 Root node (하나도 안고른 상태를 의미)
    - `Maxprofit=0`
    - `profit=0`, `weight=0`, `bound`는 따로 불러서 계산
- 이때 Promising 검사
    - 이 노드를 봤을 때 `weight`가 `최대 Weight`보다 작고
    - `Bound`가 현재까지 구한 `Maxprofit`보다 크다면, 가지 내림
    - 매번 체크해서 Optimal 업데이트 할 때, 동시에 담아놨던 물건을 모아놓은 `BestSet` 또한 업데이트 해준다.
- 원래 같았으면 아이템 갯수만큼의 Depth로 완전 이진트리 `2^n-1개`의 노드를 탐색해야 하지만, 가지치기 잘 해주면 탐색하는 노드를 줄일 수 있다.
<br>
<br>

### 생각해볼 거리 🤔

- 만약 가지치기를 잘 해준다고 했을 때, `백트래킹`은 항상 `DP`보다 효율적일까?
    - 가지치기를 잘 해준다면 `DP`보다 방문하는 노드는 적어질 수 있다.
    - 그렇지만 `백트래킹`이 `DP`보다 효율적이리고 이야기할 수는 없다.
        - 가지치기의 결과는 매 케이스마다 예측 불가능하기때문에, 이론적으로 계산할 수 없다.
        - `DP`는 완전 탐색을 하지만, 부분 중복에 대한 계산을 안한다.
        - `백트래킹`은 가지치기를 통해 완전 탐색을 안하도록 유도한다.
        - 그러므로 완전 탐색을 안하도록 하는 `백트래킹`은 `DP`보다 효율적일 것이라 생각할 수 있다. 그러나 이걸 수학적으로 계산할 수 없다.
        - 다항시간 알고리즘을 찾을 수 없고, 다항시간 알고리즘이 없다고 증명도 못하는 경우, `NP-Complete`가 된다.
- 이 알고리즘의 시간복잡도
    - `몬테카를로 시뮬레이션` ⇒ 수많은 반복을 통해 평균 시간을 구하는 방법
- 공간복잡도
    - `O(2^n)`
        - 최악의 경우니까! 하나도 가지치기가 안될 수도 있으니까 `O(2^n)`이다.
- 이론적 비교
    - `DP` 시간복잡도 : `O(min(2^n, nW))`
    - `BT` 시간복잡도 : `세타(2^n)`
- 상태공간트리 ⇒ `세타(2^n)`
<br>
<br>

## 전체 코드 (백트래킹)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n,k;
int w[100001];
int v[100001];
vector<pair<int,pair<int,int>>> temp;

int maxProfit=0;
int bestChoice[100001];
float bound;

int include[100001]; // 0 => Not include, 1 => include. 0번째 칸 안 씀.

bool promising(int idx, int weight, int profit)
{
    if (weight>=k) return false; // 이 노드의 현재 무게가 한계치보다 크거나, 같다면 뿌리를 내릴 필요가 없다. 
    //만약에 크다면 이전 if 조건으로 인해 Optimal 체크에서 탈락할 것이고, 같으면 더이상 담을 수 없으니 뿌리내릴 필요가 없다.
    int j, h, totweight;
    j=idx+1;  // idx+1인 이유, idx번째 아이템까지 고려하였으니, 아직 고려 안한 아이템들에 대해 체크하기 위하여. 
    bound = profit; // 일단 현재까지 구한 프로핏 담아줌
    totweight = weight; // 일단 현재까지 구한 무게 담아줌
    while (j<=n && totweight + w[j] <= k) { // 최대 n번째 아이템까지 돌아감. w 배열은 1번부터 n번까지, 0번째칸 안쓰고 진행함.
        totweight += w[j];
        bound += v[j]; // 어짜피 최종 공식에서 시그마로 더 해줄 것 미리 함.
        j++;
    }
    h=j; // 잘라서 넣을 물건 인덱스 추출
    if (h <= n) // 만약 끝까지 다 넣었을 경우, h가 n보다 클 것이기 때문에 n보다 클 경우 더이상 넣을 아이템이 없음
        bound += (k-totweight) * ((float)v[h]/w[h]); // 남는 자리 잘라서 넣어줌
    return bound>maxProfit;
}

void solve(int idx, int weight, int profit) // 
{
    cout << idx << " " << weight << " " << profit << " "; // 무조건 노드 방문했으니까 출력해야 함. Promising은 가지를 뻗을까 말까를 의미함. 
    if (weight<=k && profit>maxProfit) { // 일단 노드 방문했으면 Optimal한 값인지 체크해준다. 최대용량보다 같거나, 작으면서 maxprofit보다 크면, 이 노드가 optimal하다고 체크해준다. 
        maxProfit=profit;
        copy(include, include+n+1, bestChoice);
    } 
    if (promising(idx, weight, profit)) { // 유망함수 체크
        cout << bound << " " << maxProfit << endl;
        include[idx+1]=1; // 가지를 뻗어도 되니까, 다음 번째 아이템을 넣는경우 - 안넣는 경우로 이진트리 생성
        solve(idx+1, weight+w[idx+1], profit+v[idx+1]);
        include[idx+1]=0; // idx+1번째 아이템 안넣는 경우로 출발
        solve(idx+1, weight, profit);
    }else{
        cout << bound << " " << maxProfit << endl; // 이 노드가 유망하지 않은 경우도, 일단 이 노드를 방문한 것이기 때문에 출력해야 한다.
    }
}

int main()
{
    cin >> n >> k;
    
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

    solve(0, 0, 0); // 인덱스(몇 번째 아이템 고를지), 현재까지의 무게, 현재까지의 이익을 파라미터로 넣는다. 
    cout << maxProfit << "\n";
    for (int i=1; i<=n; i++) {
        if (bestChoice[i]==1) cout << w[i] << " " << v[i] << "\n";
    }
}
```

---
