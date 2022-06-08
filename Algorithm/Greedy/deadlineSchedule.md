# 알고리즘 : Greedy Appoach

---

## Deadline Scheduling

> 마감 데드라인이 존재하는 Job들 여러 개가 있을 때, 최대 Profit을 얻는 경우를 구하라
> 

### 접근법

1. 우선 주어진 Job들을 가중치 기준으로 정렬한다.
2. 제일 가중치가 큰 놈을 스케줄링 시퀀스에 집어넣고 (얘는 무조건 들어가야 되니까), 두 번째로 가중치가 큰 놈부터 비교를 시작한다.
3. Job이 실행되는 시간은 1-2-3-4-5-6-7 형태로 증가하므로, 최소한 Sequence가 제대로 작동하려면 데드라인이 오름차순을 유지하여야 한다. 
4. 테스트 시퀀스 K를 생성한 뒤, S의 값을 옮겨 담는다.
5. 오름차순의 형태를 유지하면서 이 Sequence가 Feasible한 지 체크해야 하므로, 큰 가중치를 가진 값을 벡터 뒤에서부터 탐색하여 자신보다 낮은 값이 있다면 K의 그 곳에 넣는 방식으로 오름차순 형태를 유지한다.
    1. 이때, Feasible 조건은 시퀀스의 Job이 실행되는 시간(벡터의 인덱스+1)에 맞추어 그 Job의 데드라인 안에 실행할 수 있는 지이다. 
6. 오름차순으로 정렬된 벡터는 자신들의 데드라인이 인덱스 넘버 + 1 보다 같거나, 최소한 커야한다. (Feasible 조건)
7. 만족하지 못하면, 이 i번째 Job을 넣었을 때의 Sequence는 조건 만족하지 않는 시퀀스이므로 넘어간다.
8. 만족한다면, Optimal한 Sequence인 S에 이 Sequence를 덮어 씌운다. 

<br>
<br>

```cpp
#include <iostream>
#include <vector>

using namespace std;

int n;

vector<pair<int, int>> schedule;

bool possibleCheck(vector<pair<int, int>> temp)
{
    for (int i=0; i < temp.size(); i++) {
        if (temp[i].first < i+1) return 0;
    }
    // 만족하는 조건 : 이 시퀀스의 데드라인은 본인이 위치한 배열 인덱스 +1보다 무조건 크거나 같아야 함.
    // 실행되는 시간이 3인데 만약 데드라인이 2라면, 얘는 실행 못하는 Job이 되기 때문임.

    return 1;
} 

void solve()
{
    vector<pair<int, int>> S; // Optimal한 결과값을 저장하는 S
    vector<pair<int, int>> K; // 테스트용 K
    S.push_back(schedule[0]); // 제일 큰거 일단 집어넣음
    
    for (int i=1; i<n; i++) { // 모든 준비된 Job 하나하나 순회.
        K.resize(S.size()); // S 사이즈로 리사이즈 해줘야 함.
        copy(S.begin(), S.end(), K.begin()); // 현재 옵티멀한 시퀀스 그대로 옮겨담기
        int index=0;
        while(index < K.size() && K[index].first <= schedule[i].first)
            index++; // 데드라인의 오름차순 구조를 유지할 수 있는 최소한의 위치 찾음
            // 넣어서 테스트하려는 Job i의 데드라인보다 큰 놈을 찾으면, 멈춤.
        K.insert(K.begin()+index, schedule[i]); // 큰놈보다 바로 앞에 넣음

        if (possibleCheck(K)){ // 넣어보고 이게 제대로 동작하는 시퀀스가 맞는지 테스트
            S.resize(K.size());
            copy(K.begin(), K.end(), S.begin());
        }
    }

    int sum=0; // 옵티말한 시퀀스의 최대 얻을 수 있는 값 구하는 부분
    for (auto loop : S)
    {
        sum += loop.second;
    }
    cout << sum << "\n";

    for (int i=0; i<S.size(); i++) { // 시퀀스의 Profit 출력하는 부분
        cout << S[i].second;
        if (i < S.size()-1) cout << " ";
    }

    cout << "\n";
}

int main()
{
    cin >> n;
    vector<int> deadline;
    vector<int> profit;
    for (int i=0; i<n; i++) {
        int input;
        cin >> input;
        deadline.push_back(input);  // 데드라인 입력
    }
    for (int i=0; i<n; i++) {
        int input;
        cin >> input;
        profit.push_back(input); // 프로핏 입력
    }
    for (int i=0; i<n; i++) {
        schedule.push_back(make_pair(deadline[i], profit[i]));
    } // 이미 정렬되어 있다.
    // 데드라인 - 프로핏으로 묶어서 스케줄에 넣음
    // 정렬하면 sort로 하면 되고, deadline 기준으로 정렬됨.

    solve();
}
```
