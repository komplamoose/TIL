# 알고리즘 : Backtracking

---

## M-Coloring

> 그래프가 주어졌을 때, 인접한 노드끼리 같은 색을 사용하지 않는 조건으로, 몇 개의 색이 있으면 그래프를 다 칠할 수 있는지 구하는 문제
> 
<br>

### 문제 설명

- 이론적으로 4개의 색이 있으면 모든 평면 그래프를 다 칠할 수 있음이 증명되었다. ⇒ `4색정리`
- 그러므로 중요한 것은 3색 이하에서도 이 그래프를 칠할 수 있는가 없는가를 체크하는 것이 중요하다.
<br>

### 상태공간트리 설정

- 그래프에서, 처음에 출발할 노드를 선택한다.
- 그 노드에서 색칠할 수 있는 경우의 수로 가지를 내린다.
    - M개의 경우로 내리면 된다.
- 노드를 칠했는데, 부모 노드와 같은 색으로 칠해지는 경우
⇒ 가지치기
<br>

### 가지치기 전략

- K번째로 칠한 노드 이전에 선택했던 노드들의 색을 탐색한다.
- 칠했던 노드가 만약
    - K번째로 칠한 노드와 `인접` 하고
    - 동시에 k번째로 칠한 노드와 `색상이 같다면`
    
    ⇒ 가지치기 해준다. 
<br>    

### 전체 코드

```cpp
#include <iostream>

using namespace std;

int graph[151][151]; // 그래프 담을 인접행렬
int gColor[151]; // 151개의 버텍스 색을 저장하는 배열

int v, e; //버텍스-엣지
int m; // 컬러의 숫자

int cnt=0;

bool promising(int k)
{
    int j = 1;
    while (j < k) // k번째로 칠한 버텍스 이전에 선택했던 버텍스 모두 탐색
    {
        if (graph[k][j]&&gColor[k]==gColor[j]) // 이 버텍스가 인접하면서, k번째 버텍스와 색이 같으면 안된다.
            return false;
        j++;
    }

    return true; // 이전에 칠했던 노드 다 탐색했는데도 못 찾음 => 이 버텍스에 이 색을 칠해도 된다 !
}

void solve(int k)
{
    int color;

    if (promising(k)) { // 유망함수 체크
        if (k == v){ // k==v : 버텍스 전부 다 칠하는데 성공했다면
            cnt++;
            return;
        } else{
            for (color = 1 ; color <= m ; color++) { // 일단 m개의 색 모두 다 칠해봄. 뿌리내리기
                gColor[k+1] = color; // k+1번째 버텍스의 색 칠함, 시작의 경우 첫번째 버텍스 칠하는 경우가 m개인 경우로 뿌리내림
                solve(k+1);
            }
        }
    }
}

int main()
{
    cin >> v >> e; // 총 버텍스와 엣지 숫자를 입력받는다. 

    for (int i=0; i < e; i++) {
        int a, b;
        cin >> a >> b;
        graph[a][b]=1;
        graph[b][a]=1;
    } // 그래프 관계 생성, 1일 경우 인접, 0이면 인접 안함
    for (int i=1; i<=4; i++) { // 색을 1개 사용했을 경우부터 4개 사용했을 경우까지 계산
        m=i;
        cnt=0;
        solve(0); // 0번째 버텍스 칠하는 경우부터 시작
        if (cnt!=0) break; // 카운트가 0이 아니다 => i번째 색을 사용했을 때 그래프를 다 칠할수 있는 경우가 존재한다 !
    }

    cout << m << "\n" << cnt << "\n";
}
```

---