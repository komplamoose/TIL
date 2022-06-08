# 알고리즘 : Backtracking

---

## 부분집합의 합

> 집합 S가 주어지고, 숫자 W가 주어졌을 때, S의 부분집합의 합이 W가 되는 부분집합의 경우의 수를 탐색하라.
> 
<br>

### 문제 설명

- 모든 부분집합의 갯수는 2의 N승이므로, 브루트 포스하게 탐색하면 시간 복잡도가 O(2^n)이 나온다.
- 이것보다 더 빠른 확실한 방법이 없다.
- Lower-bound를 증명하는 방법도 없다.
    - NP-완전 문제다.
- 백트래킹을 통해 가지치기를 해야한다.
<br>

### 가지치기 전략

- 상태 공간 트리는 집합에서 어떤 숫자를 포함하거나-안포함하거나로 나뉘는 이진 트리 형식으로 구성된다.
    - 이 때 트리의 Depth는 집합의 원소가 된다.
- 양의 정수만 받는 경우, Sum의 값이 W보다 크거나, 같다면 더이상 노드 그 아래로 탐색할 필요가 없다.
- 현재까지의 합이 W를 넘어서면 ⇒ 더 이상 안가도 된다.
- 그 노드 기준으로 남아 있는 모든 숫자 다 더해도 W에 모자르면 ⇒  안가도 된다.
<br>

### 구현

1. 현재까지 담은 Weight + (다음에 담을 숫자)가 W보다 크다면
    
    ⇒ 가지치기한다.
    
    - 함수 파라미터로 Sum 값을 넘겨주어야 한다.
2. 현재 기준으로, 내가 지금까지 고른 부분집합의 합과 아직 선택 안한 남아있는 숫자를 모두 더 한 값이 W보다 모자르다면, 어짜피 다 선택해도 W에 다다를 수 없으니까, 갈 필요가 없어진다.
<br>

## 전체 코드

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, s;

int cnt=0;

int nums[30];
vector<int> v;
vector<vector<int>> answer;

bool promising(int sum, int cur) // 모든 입력받은 정수 양수일때만 적용 가능
{
    if (sum>s){ // 일단 그 노드에 진입한 뒤 체크하는 것이므로 n+1번째 숫자 넣었던 경우랑 똑같음
        return false; // 결과적으로 sum>s인 경우 절대 s에 도달 불가능 (양수 집합의 경우)
    }
    else{
        int remain=0;
        for (int i=cur; i<n; i++) {
            remain += nums[i]; //아직 선택 안했던 숫자들 모두 더하기
        }
        if (sum+remain < s) { // 지금까지 고른 숫자 + 남은 숫자 다 더해도 S에 모자라면 갈 필요도 없다.
            return false;
        }
    }

    return true;
}
/*
주의사항 : 이 프로그램에서 유망함수 체크는 일단 그 노드에 "진입한 뒤" 체크한다.
*/

void solve(int sum, int cur)
{
    if (cur==n){ // N번째 원소까지 탐색에 도달했다면  
        if (sum==s){ // 끝까지 체크했는데, Sum이 S와 같다면
            answer.push_back(v); // 조건만족한 부분집합 케이스 입력
            cnt++; // 경우의 수 추가
        }
        return;
    }else{
        if (promising(sum, cur)){ // 유망함수 조건 체크
            solve(sum, cur+1); // 그대로 숫자 넣지말고 유지하는 경우 (cur번째 원소 부분집합에 안넣는 경우)
            v.push_back(nums[cur]); // cur번째 원소를 부분 집합에 넣는 경우
            solve(sum+nums[cur], cur+1); // 다음 숫자 넣어보는 경우
            v.pop_back(); // 돌아왔으면 다시 빼줌
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> s; // 집합의 원소 갯수 N, 목표 S 입력

    for (int i=0; i<n; i++){
        cin >> nums[i];
    }

    solve(0, 0); // 현재까지의 Sum과 0번째 칸의 원소 선택 할 것임을 파라미터로 입력
    reverse(answer.begin(), answer.end()); // 백트래킹 순서대로 리버스

    if (s==0) cnt--; // 공집합인 경우가 잡히므로 S가 0이면 하나 빼줘야 함. 
    
    if (cnt==0){
        cout << cnt << "\n";
        cout << "\n";
    }else{
        cout << cnt << "\n";
        for (auto loop : answer) {
            for (int i=0; i<loop.size(); i++) {
                cout << loop[i];
                if (i < loop.size()-1) cout << " ";
            }
            cout << "\n";
        }
    }
}
```

---
