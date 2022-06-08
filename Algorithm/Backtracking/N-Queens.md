# 알고리즘 : Backtracking

---

## N-Queens 문제

> N by N 체스 보드판에, 서로 잡아먹히지 않도록 N개의 퀸을 놓도록 하는 경우의 수를 구하는 문제
> 

<br>

### 문제 설명

1. 퀸은 자신 기준 상하좌우, 대각선 모든 칸에 갈 수 있다.
2. 퀸은 서로 마주보면 안된다.
3. 모든 경우의 수를 브루트포스하게 탐색하여 구하면 O((n^2)!)의 시간 복잡도를 가진다.
    1. 다항 시간 내에 해결하는 방법이 아직 없다.
    2. 동시에 해결할 수 없다고 증명하는 방법도 없다.
    3. 이런 문제를 NP-Complete(NP-완전) 문제라 하고, 동시에 NP-Hard하다 한다.
<br>
<br>

### 접근법

1. 퀸은 한 행에 하나만 있을 수 있다.
2. 일단 퀸을 한 칸에 놓는다
3. 다음 Row로 건너가서 기존 퀸 위치 기준으로 봤을 때 위배되지 않는 칸에 퀸을 놔둔다.
    1. 같은 열, 혹은 대각선에 퀸이 존재한다면 못 놓는다.
    2. 행 조건은 이미 매 놓을때마다 행을 기준으로 놓기로 하였으므로 체크 안해도 된다.
4. 불가능하다면 다시 돌아온다.
5. n번째 행에 퀸을 놓았다면, N-Queen 문제의 조건을 만족한 것이므로 체크해주고, 다시 돌아간다.
<br>
<br>

## 전체 코드

```cpp
#include <iostream>
#include <vector>

using namespace std;

int n;
int cnt=0;
bool isused1[16]; // 열에 대응, (x,y)칸에 퀸을 놨으면 isused1[y]에 true;
bool isused2[32]; // 우상향하는 대각선에 대응 (x,y)칸에 퀸을 놨으면 isused2[x+y]칸에 true;
bool isused3[32]; // 우하향하는 대각선에 대응, (x,y)칸에 퀸을 놨다면 isused2[x-y+n-1]에 true, n-1 더해주는 이유는 음수 방지용

vector<int> v;

unsigned long long int m = 0;

void solve(int cur)
{
    if (cur==n) { // N번째 행에 도달했다면 (조건만족)
        string temp="";
        for (auto loop : v) { 
            temp += to_string(loop);
        }
        if (m<stoull(temp)){
            m=stoull(temp);
        } // 놓는 칸을 정리한 벡터를 숫자로 치환했을 때 가장 큰 값 구하는 부분 
        cnt++; // 경우의 수 +1 해주기
        return;
    }else {
        for (int i=0; i<n; i++) { // 보드의 0번째 열부터 n-1번째 열까지 모두 탐색. 행은 어짜피 재귀함수 단계로 하는거니까 열만 탐색
            if (isused1[i]==false&&isused2[cur+i]==false&&isused3[cur-i+n-1]==false) { // 그 열에 아무도 없고, 그 열 기준의 우하향, 우상향 대각선에 아무것도 없다면
                isused1[i]=true; isused2[cur+i]=true; isused3[cur-i+n-1]=true;
                v.push_back(i+1);
                solve(cur+1); // 다음 단계로 진입
                isused1[i]=false; isused2[cur+i]=false; isused3[cur-i+n-1]=false; // 다시 돌아왔으면 같은 행의 다음 열에 놔서 확인해야 하니까 다시 안가본걸로 체크
                v.pop_back();
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n; // N 입력받기
    solve(0); // 0-> 상태공간트리의 루트부터 시작

    cout << cnt << "\n";
    cout << m << "\n";
}
```

### 추가 설명 : isused 배열

1. isused1
    1. 그 퀸의 **열**에 대해 체크함.
    2. (x, y) 칸에 퀸을 놓았다면, isused1[y] = true
2. isused2
    1. 퀸 기준 우상향하는 방식으로 그려지는 대각선에 대응함.
    2. 수학적으로 (x,y)칸에 퀸을 놓았다면, x+y를 통해 우상향 대각선 구할 수 있음. 모르겠음 그려서 확인해볼 것.
    3. isused2[x+y]=true
3. isused3
    1. 퀸 기준 우하향하는 방식으로 그려지는 대각선에 대응함.
    2. 수학적으로 (x,y)에 놓았다면은 x-y+n-1에 그 대각선 모두 표현 가능
    3. 원래 x-y로만 해도 계산 가능하지만, 그러면 음수가 나오니까 그냥 n-1 더 해줌
    4. isused3[x-y+n-1]=true

---
