# 알고리즘 : Backtracking

---

## 기사의 여행 ♟️

> `n by m` 체스 보드 판에서, 체스 Knight가 임의의 한 칸에서 출발하여, 모든 칸을 다 찍고 다시 출발점으로 돌아오는 경우의 수를 구하는 문제
> 
- 다시 돌아오는 경우 ⇒ `해밀턴 회로`
- 다시 안돌아와도 되는 경우 ⇒ `해밀턴 경로`
<br>

### 🔥 해밀턴 회로에서 출발 정점 선택이 의미가 없는 이유

: 어짜피 회로는 자기 자신으로 돌아오며, 모든 정점을 방문한다. 그래프가 존재할 때 회로를 만든다면, 시작점으로 어느 점을 고르든지 간에, 다른 점에서 시작하는 경우와 같다고 볼 수 있으므로 의미가 없다.

⇒ `싸이클`이 생기니깐
<br><br>

### 접근법 (회로 구하기)

1. `n`, `m`을 입력받는다.
2. `n by m`의 `2차원 배열`을 생성한 뒤, `-1`로 채워넣는다.
3. 만약 `board[x][y] == -1` 이라면, 이 칸엔 방문하지 않은 것이다.
4. 사전에 Knight가 이동할 수 있는 모든 경우의 수 8가지를 정리해놓는다.
    1. `x=2, y=1`
    2. `x=1, y=2`
    3. `x= -1, y=2`
    4. `x=-2, y=1`
    5. `x=-2, y=-1`
    6. `x=-1, y= -2`
    7. `x=1, y=-2`
    8. `x=2, y=-1`
5. 우선 기사의 회로를 구한다. 회로를 구하는 경우 출발정점 선택은 의미가 없으니 그냥 `0,0`으로 잡아놓는다.
    1. 첫 번째로 방문한 칸이라는 뜻으로 `board[0][0]`에 `1`을 대입한다.

 6. `knight_circular` 함수를 호출한다. 파라미터로는 기사의 현재 위치, 그리고 몇 번째 방문을 했는지를 고른다.

모든 버텍스를 순회해야 하므로, 방문 횟수 == n*m이 된다면 마지막 점에 도달했다는 뜻이다.

1. 현재 위치 `x`, `y`에서 갈 수 있는 모든 경우의 수 8가지에 대해서 다 뿌리를 내려본다.
2. 근데 만약 뿌리 내리기 전, `Promising` 함수에 의해 `False` 체크가 되면, 뿌리 내리지 않는다.
3. 쭉쭉 내려가면서 `idx`가 `n*m`까지 도달하는 경우에, 그 위치에서 기사의 이동 경우의 수 8가지를 돌렸는데, 출발 정점으로 갈 수 있는 경우, 회로로 체크한다.
<br>
 

### 접근법 (경로 구하기)

1. 경로의 경우 출발 정점이 어디냐에 따라 경우의 수가 달라질 수 있다. 
    1. `싸이클`이 형성되지 않기 때문이다.
2. 동일
3. 동일
4. 동일
5. `idx`가 `n*m`까지 뿌리 내리는데 성공했다면, 그 자체로 경로가 완성되었다는 뜻이다. 조건 만족
<br>

### 유망함수 설정

- 기사의 위치 `x`, `y`는 `체스 보드 칸`을 벗어나선 안된다.
- 기사가 방문하는 칸 `board[x][y]`는 반드시 `-1` 이어야 한다. (방문하지 않은 칸이어야 한다.)
<br>

### 전체 코드

```cpp
#include <iostream>
#include <vector>

using namespace std;

int n, m;
int cnt=0;
vector<vector<int>> board;

int xMove[8] = {2, 1, -1, -2, -2, -1, 1, 2}; // 기사가 이동할 수 있는 8가지 경우의 수
int yMove[8] = {1, 2, 2, 1, -1, -2, -2, -1};

int xpos=0;
int ypos=0;

bool promissing(int x, int y) // 유망함수
{
    if (x<0 || x>=n || y<0 || y>=m) return false; // 칸을 벗어 났는가?
    if (board[x][y]!=-1) return false; // 이미 방문한 칸은 아닌가?

    return true;
}

void knight_pass(int x, int y, int idx)
{
    if (idx==n*m){ // 다시 돌아올 필요 없음. 그 자체로 조건 만족
        cnt++;
        return;
    }
    for (int i=0; i<8; i++) { // 갈 수 있는 모든 방향 순회
        int nx = x+xMove[i]; int ny= y+yMove[i];

        if (promissing(nx, ny)) { // 만약 이동할 공간이 유망하지 않다면, 아예 뿌리 안내림
            board[nx][ny]=idx+1;
            knight_pass(nx,ny,idx+1);
            board[nx][ny]=-1; // 다음 경우의 수에선 이 칸 방문 안했던 걸로 체크해야 함
        }
    }
}

void knight_circular(int x, int y, int idx)
{
    if (idx==n*m){
        for (int i=0; i<8; i++) { // 마지막 칸에서 갈 수 있는 모든 방향 순회, 출발정점에 갈 수 있으면 회로조건 충족 
            int nx = x+xMove[i]; int ny= y+yMove[i];
            if (nx==0&&ny==0) {
                cnt++;
                break;
            }
        }
        return;
    }
    for (int i=0; i<8; i++) { // 갈 수 있는 모든 방향 순회
        int nx = x+xMove[i]; int ny= y+yMove[i];

        if (promissing(nx, ny)) {
            board[nx][ny]=idx+1;
            knight_circular(nx,ny,idx+1);
            board[nx][ny]=-1;
        }
    }
}

int main()
{
    cin >> n >> m;

    board.assign(n,vector<int>(m,-1));

    xpos=0; ypos=0;
    board[0][0]=1; // 시작점 체크 반드시 해줘야 함. 안 그럼 시작점도 나중에 갈 수 있는 칸으로 체크되어버림
    cnt=0;
    knight_circular(0,0,1);
    cout << cnt << "\n";

    int tc;
    cin >> tc;
    while(tc--) {
        for (int i=0; i<n; i++){
            for (int j=0; j<m; j++) {
                board[i][j]=-1;
            }
        }
        int startX, startY;
        cin >> startX >> startY;
        cnt=0;
        board[startX][startY]=1; // 시작점 체크 반드시 해줘야 함.
        knight_pass(startX, startY, 1);
        cout << cnt << "\n";
    }
}
```
