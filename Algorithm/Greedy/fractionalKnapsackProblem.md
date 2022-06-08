# 알고리즘 : Greedy Approach

---

## 분할 가능한 배낭 문제

> 용량 W를 가진 배낭에, 빈 자리 없이 물건을 꽉 채워 담을 때의 최대 효용을 구하는 문제. (이 때, 물건은 잘라서 넣을 수도 있다.)
> 
<br>

### 접근법

1. 물건을 단위 가치를 계산한다.
    1. 단위 가치 = 가치/무게
2. 물건을 단위 가치 기준으로 정렬시킨다.
3. 가장 큰 단위 가치를 가진 물건을 배낭에 담는다.
4. 남은 배낭 용량보다 물건 용량이 더 크다면, 남은 배낭 용량만큼 잘라서 넣는다.

<br>

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool COMPARE(pair<float, pair<int, int>> a, pair<float, pair<int, int>> b){
    return a.first > b.first;
} // 단위가치 기준 정렬을 위한 비교함수 작성

typedef vector<pair<float, pair<int,int>>> Items;

void solve(int n, Items& v)
{
    int m;
    cin >> m; // 테스트케이스
    
    for (int i=0; i < m ; i++) { 
        int capacity;
        cin >> capacity; // 가방의 용량 입력

        int w=0; // 현재 가방에 담긴 용량

        vector<pair<int, int>> knap; // 저장될 가방

        int j=0;
        while(w<capacity&&j<v.size()) // 현재 담은 용량 w가 최대 용량보다 작고 (같다면 안돌아도 되니까)
        {                             // j (남은 물건을 가리키는 인덱스) 가 최대크기보다 작을때 (물건 끝까지 탐색)
            if (v[j].second.first<=capacity-w) { // item을 통채로 넣을 수 있을 때
                knap.push_back(make_pair(v[j].second.first,v[j].second.second));
                w+=v[j].second.first; // 그냥 집어넣음
            }else {
                int remain = capacity-w; // 만약 못넣는다면, 남은 용량 계산해서 넣어줌
                knap.push_back(make_pair(remain,v[j].first*remain));
                w+=remain;
            }
            j++;
        }

        int maxProfit = 0;
        for (auto loop : knap) {
            maxProfit += loop.second; // 가방에 담긴 Profit 모두 더하면 최대 이득 계산 가능
        }
        cout << maxProfit << "\n";

        for (auto loop : knap) {
            cout << loop.first << " " << loop.second << "\n";
        }
    }
}

int main()
{
    int n;
    vector<int> weight;
    vector<int> price;
    cin >> n;

    for (int i=0; i<n ; i++) { // 무게 입력받기 
        int input;
        cin >> input;
        weight.push_back(input);
    }

    for (int i=0; i<n ; i++) { // 가치 입력받기
        int input;
        cin >> input;
        price.push_back(input);
    }

    Items item;
    for (int i=0; i<n; i++) { // 단위 가치를 계산해서, [단위가치, (무게, 가치)] 형태로 묶어 넣어준다.
        float ppw = price[i]/weight[i];
        if (ppw!=0) item.push_back(make_pair(ppw,make_pair(weight[i],price[i])));
    }

    sort(item.begin(), item.end(), COMPARE); // 단위가치 기준으로 정렬한다.

    solve(n, item);
}
```

---
