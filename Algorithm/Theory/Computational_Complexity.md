# 알고리즘 : Computational Complexity

---

## 챕터 1. 계산 복잡도

> 알고리즘 문제 해결보다, 문제의 계산 복잡도에 대해 생각해보자.
> 

### 문제 해결을 위한 2가지 접근법

1. 문제를 해결하는 방법
2. 문제를 해결할 수 없음을 증명하는 방법

### 문제를 구분하는 여러가지 접근법

1. 문제가 주어지면
2. 이 문제를 계산을 통해 풀 수 있는가?
    1. 풀 수 있는 경우
        1. 이 문제가 풀기 쉬운가? (다항시간 내에 풀리는가?)
            1. 풀기 쉬운 문제
                1. P 집합
            2. 풀기 어려운 문제
                1. 다항시간 이외에 풀리는데, 무조건 다항시간 내에 못 푼다고 증명가능한 문제
                2. 다항시간 이외에 풀리는데, 다항시간 내에 못 푼다고 증명 못하는 문제
                    1. NP 집합
    2. 풀 수 없는 경우
        1. Halting Problem (정지 문제)
        2. 반례만 찾으면 된다.

### Computational Complexity의 목표

- 알고리즘의 시간 Lower-bound가 아니라, 문제 그 자체의 Lower-bound를 정하자.

### Case 1. Sorting Problem

- 정렬 문제의 Lower-Bound
    - 무슨 짓을 하더라도, 이 List가 정렬되어 있는지 확인하려면 O(n)이 소요된다.
- 원소를 비교하는 정렬 알고리즘
    - Merge sort, Quick sort, Heap sort
    - O(nlogn)의 한계점을 가짐이 증명되어 있음.
- 원소를 비교를 하지 않고 정렬하는 알고리즘
    - Radix sort, Bucket Sort
    - O(dn)의 시간 복잡도를 가진다. 일반화하면 O(n)이라 생각할 수 있다.
- 비교를 사용하지 않고 정렬하는 알고리즘이 실사용에서 적용하기 어려운 부분이 있는 것이나, Quick sort가 일반적으론 가장 빠르다는 그런 추가적 사실은 제외하자.
    - 결국 궁극적으로 “정렬 문제”의 Lower-bound는 Omega(N)이 된다.
        - 라딕스 소트 때문에.

### Case 2. Searching Problem

- 탐색 문제
- 리스트가 정렬된 상태인 경우
    - 이진 탐색 : O(logN)
- Hash Table 사용 방법
    - O(1)
- Binary Search Tree
    - 최악의 경우 탐색시간 O(n)
    - 트리가 한 쪽 방향으로 쏠려 있는 경우 (balanced하지 않은 경우)
- BST의 문제 해결을 위한 새로운 트리들
    - AVL Tree
        - 왼쪽과 오른쪽의 레벨 차이가 +-1로 유지
    - Red-Black Tree
        - 왼쪽과 오른쪽의 차이가 logN을 넘지 않도록 유지
    - 위와 같은 트리들의 탐색 시간 복잡도
        - O(logN)이 보장된다.
- B-Tree, B+-Tree
    - 데이터베이스 시스템에서 사용하는 트리, binary, trinary가 아닌 N-ary 트리.
- Hash Table의 탐색 시간 복잡도는 O(1)이므로, 이게 가장 좋은 방법일까?
    - Range를 대응해낼 수 없기 때문에, 항상 좋은 방법은 아니다.

## 챕터 2. 선택 문제와 적대적 논증법

> 가정 : 1층에서 100층까지 있는 건물에서, 계란을 가장 높은 층에서 떨어트렸을 때, 계란이 안 깨진 사람이 우승을 하는 대회가 있다고 가정하자.
> 
- 우리의 목표
    - 계란이 몇 층에서부터 안 깨지는 지 증명하는 횟수를 최소화하자.

- Q1. 계란이 **한 개** 주어진다면, 증명 방법 최소화하는 방법은 무엇일까?
    - A1. 순차 탐색 방법
        - 1층에서부터 올라가면서, 계란이 깨지는 층을 확인한다.
        - Worst Case : O(n)
        - Average Case : O(n)

- Q2. 계란이 무한 대로 주어진다면?
    - A2. 이진 탐색 방법
        - 50층에서 깨지면 25층, 안깨지면 75층
        - Worst Case : O(logN)
        - Average Case O(logN)

- Q3. 계란이 단 2개만 주어진다면?
    - 1개가 있다면 반드시 순차 탐색을 해야 한다. 나머지 1개로는 순차 탐색의 범위를 최소화하자.
    - 10층 단위로 상승하여, 1개를 깨트려보자. 만약 깨진다면 그 지점을 목표로 설정하여 순차탐색 범위를 지정하면 된다.
    - Lower Bound한 해결책은 아니다. 그냥 접근법 중 하나임.
    - 2개의 계란 문제로 일반화되어 있다.

### 2개의 계란 문제

- 이 문제는 시도 횟수 몇번 안에 몇 층까지 커버할 수 있는지 수학적으로 정의되어 있다.

$$
(x(x+1))/2
$$

- x가 시도횟수라면, 검사할 수 있는 최대 층수를 구하는 식이다.
- x가 13라면
    - 13번의 검사 방법 안에 총 (13*14)/2 ⇒ 91층까지 확인 가능
- x가 14라면
    - 14번의 검사 방법 안에 총 (14*15)/2 ⇒ 105층까지 확인 가능하다.
- 결과적으로, 100층까지 존재할 경우 계란 2개로 확인하는 검사 방법의 최소 값은 최악의 경우
    - 14가 되겠다.

### 선택 문제

> 정렬되지 않은 고유한 N개의 Key들이 주어졌을 때, 이 Key들 중 K번째로 큰 수 ( 혹은 작은 수 ) 를 찾는 문제
> 
- 뇌 비우고 푸는 방법
    - 정렬한 후 찾기
        - O(nLogN) ⇒ O(n)
        - O(nLogN)

### Case 1. 만약 K가 1이라면? (가장 큰 수, 혹은 가장 작은 수)

- 최악의 경우, 최선의 경우 모두
    - 반드시 N-1번의 비교를 해야 한다.
    - $T(n) = n-1$
- 키들끼리 비교하여 최대 값을 찾는 문제는 결정적(Deterministic)한 알고리즘인 경우 반드시 N-1번의 비교를 수행해야 한다.
    - 최대(혹은 최소) 값을 찾아내는 문제의 Lower Bound는 N-1임이 증명되어 있다.

### Case 2. 최대 값과 최소 값을 동시에 찾아내고 싶다면?

- Naive한 접근법
    - 일단 최대 값을 찾고, 최대 값이 아닌 나머지에서 최소 값을 찾아보자
    - $T(n) = 2n-3$
    - 좋은 방법은 아님
- 좋은 방법 (토너먼트)
    - 숫자 2개씩 비교하면서, 그 결과에 따라 Winner, Loser로 나눠보자.
    - 최대 값은 반드시 Winner 집합에 있을 것이고, 최소 값은 반드시 Loser 집합에 있을 것이다.
        - N이 짝수일 경우 : $T(n) = (3n)/2 - 2$
        - N이 홀수일 경우 : $T(n) = (3n)/2 - 3/2$
- 토너먼트 방법이 과연 이 문제의 Lower-Bound한 해결방법인지 증명해보자
    - 증명법 : Adversary Argument (적대적 논증법)
    - 토너먼트 게임
        - 토너먼트 트리의 형태
            - Leaf Node의 갯수 ⇒ N개
            - Internal Node의 갯수 ⇒ N-1개

```cpp
void find_both(int n, vector<int> S, int& small, int& large)
{
	small = S[1];
	large = S[1];

	for (int i=2; i <= n; i++) {
		if (S[i] < small)
			small = S[i];
		else if (S[i] > large)
			large = S[i];
}
```

### +) Adversary Argument : 적대적 논증법

- 가상의 적(Adversary)이 있다고 가정하자.
    - 이 적은 이 알고리즘의 해결책을 구하기 위한 방법을 알고 있다.
- 우리는 이 적에게 질문하여, 최소한의 질문만을 통해 답을 얻어내야 한다.
    - 우리는 반드시 Yes-No로 답변할 수 있는 질문만 할 수 있다.
    - 적은 거짓말하지 않는다.
- 이 적은 알고리즘을 가능한 최대한 어렵게 만드는 것이 목표다. 최대한 쉬운 방법을 찾으려는 우리의 적이다.
- 우리가 구해낸 최소 질문 `f(n)`은, 결국 최악의 경우에서의 Lower-bound가 된다.

### 질문 전략 세우기

- 멍청한 질문(당연한 질문)을 해서는 안된다.
- 토너먼트 게임에서 나올 수 있는 모든 상태를 구분해보자.
    - 여기서 질문은 Comparison을 의미한다. (숫자 간의 비교)
    
    | State | 설명 | 상태로부터 얻은 정보 |
    | --- | --- | --- |
    | X | 이 숫자에 대해 질문 하지 않은 상태. | 0 |
    | L | 질문 했는데, Loser인 상태 | 1 |
    | W | 질문 했는데, Winner인 상태 | 1 |
    | WL | 질문 했는데, 어떤 숫자 상대로는 Winner인데 어떤 숫자 상대로는 Loser임 | 2 |
    - 토너먼트 게임을 한다면, 숫자들은 결국 이 4가지 상태로 구분될 것이다.

![image](https://user-images.githubusercontent.com/78531103/173244056-dbad9765-2cde-490d-bc8e-bfbc8ec030b8.png)

> 질문(비교) Case 정리
> 
1. X-X끼리 비교
    1. 두 숫자는 W-L로 나뉘게 된다.
    2. 총 2개의 새로운 정보 획득
2. X-L, 혹은 X-W
    1. W-L 혹은 L-W로 변화
    2. 총 1개의 새로운 정보 획득 (X⇒W or L)
3. L-W 비교
    1. 패배자와 승리자를 비교해봤자 승리자가 무조건 이김
    2. 의미 없는 연산
4. L-WL
    1. L-WL로 나뉨.
    2. 의미 없는 연산
5. L-L or W-W
    1. 둘 중 하나는 WL로 바뀜 (새로운 정보)

- 비교 하였을 때 가장 새로운 정보 획득이 많은 질문
    - X-X
- 그러므로 만약 비교에 X가 있다면 반드시 질문한다.
- W-W, L-L도 반드시 정보획득하므로, 진행한다.
- 해봤자 정보 획득 안하는 바보같은 질문만 안하면 된다.

- 결론적으로, 최대 최소를 찾는 Deterministic한 알고리즘은 “비교”(질문)을 사용하는 경우, Worst-Case에서
    - N이 짝수일 경우 : $T(n) = (3n)/2 - 2$
    - N이 홀수일 경우 : $T(n) = (3n)/2 - 3/2$
    - 보장된다.

### Case 3. 리스트에서 2번째로 큰 값 찾기 (차대값)

- Naive한 접근법
    - n개의 키에서, 최대 키를 찾고 (N-1)
    - 최대 키 제외한 리스트에서 최대 키를 또 찾는다. (N-2)
    - $T(n)=2n-3$
- 좋은 방법 (토너먼트)
    - Key들 간의 토너먼트 트리를 생성한다.
    - 차대값은, 가장 큰 최대값을 제외하고는 다 이기는 숫자다.
    - 그러므로, 차대값은 최대값과 대결하여 Loser가 된 집합 내부에 있을 것이다.
        - 최대값이 Leaf에서 Root로 올라온 그 경로에 차대값이 존재할 것이다.
    - Key들은 토너먼트를 하면서, 승리시마다 나에게 진 Key를 저장하면서 올라간다.
    - 최종 Winner가 정해졌을 때, 이 Winner가 저장한 Key들 중에 최대 값을 찾으면 이게 차대값이 될 것이다.
    - $T(n) = n+ logn   -2$
    - 실제로는 숫자를 저장하는 저장 과정이 또 추가되는 것이기 때문에, 실제 경우 그냥 정렬해서 찾는게 가장 빠르다.
    

### 토너먼트 함수 ( 차대값 찾기 )

```cpp
struct item {
	int index;
	int value;
};

int n, second_largest;
item largest;
vector<item> S(n);
vector<item> L(S.size());

void tournament(int n, vector<item> S, vector<item> L, item &largest)
{
	if (n==1)
		largest = S[0];
	else {
		vector<item> winner;
		for (int i=0; i<n-1; i+=2) {
			if (S[i].value > S[i+1].value) {
				winner.push_back(S[i]);
				L[i]=S[i+1];
			}else {
				winner.push_back(S[i+1]);
				L[i+1] = S[i];
			}
		}
		return tournament(n/2, winner, L, largest);
	}
}

int main()
{
	tournament(n, S, L, largest);
	find_largest(n, L[largest.index], second_largest);
}
```

### Case 4. K번째로 큰 수 찾기 (Selection Problem)

- 비슷한 예
    - 중간 값 찾기
- 위의 Case들을 일반화하여, K번째로 큰 수를 찾는 방법을 찾아보자.

### Pivot Selection

- 퀵 정렬의 Pivot에 대해 기억하자.
- Pivot을 설정해서 파티션을 나누면
    - 피벗보다 작은 값들은 왼쪽에
    - 피벗보다 큰 값은 오른쪽에 있게 된다.
- 우린 이걸 응용해서 Selection Problem을 해결할 수 있다.
- Pivot 아이템이 K번째 슬롯에 있기 전까지 파티셔닝을 하자!
    - 분할정복적인 방법이다.

### 기본적인 파티션 나누기를 위한 함수 (Algorithm 8.5)

```cpp
int selection(int low, int high, int k)
{
	int pivotpoint;
	
	if (low == high)
		return S[low];
	else {
		partion(low, high, pivotpoint);
		print_list(S);
		if (k==pivotpoint)
			return S[pivotpoint];
		else if (k < pivotpoint)
			return selection(low, pivotpoint-1, k);
		else
			return selection(pivotpoint+1, high, k);
	}
}

void partiotion(int low, int high, int& pivotpoint)
{
	int i, j, pivotitem;
	
	pivotitem = S[low];
	
	j=low;
	for (int i= low+1; i<= high; i++)
		if (S[i] < pivotitem) {
			j++;
			swap(S[i], S[j]);
		}
	
	pivotpoint=j;
	swap(S[low], S[pivotpoint]);
}
```

- 8.5 알고리즘을 사용시, 항상 피벗값을 파티션의 첫 번째 원소로 선택하여 나눈다.
- 기존 퀵소트와 방식이 동일하기 때문에, 이미 값이 거의 다 정렬된 최악의 경우 시간 복잡도도 동일하다.
- Worst case : O(n^2)
- Average case : O(n)

### 파티션 알고리즘 개선 (랜덤 선택)

- 피벗을 랜덤으로 선택하자.
- Average case : O(logN);
- Worst Case : O(n^2) (랜덤 돌렸는데 다 첫 번째만 뽑힌 경우)

### 파티션 알고리즘 개선 (Median 사용)

- 기존 퀵 셀렉션의 문제는 Worst case가 자꾸 n이 나온다는 문제다.
- 피봇팅을 했을 때, 리스트가 거의 절반으로 분할되면 아주 좋을 것이다.
- 피봇을 뭘 선택해야 리스트를 절반으로 나눌 수 있을까?
- 해결책 1. 중앙값을 찾자!
    - 리스트의 중앙 값을 찾는 것 자체가 K번째 키 찾기 문제와 동일함.
    - 매우 시간 복잡도가 드는 방식
- 해결책 2. 중앙값들의 중앙값 찾기
    - 수학적으로, 5개의 키에서 미디안 값을 찾는 것은 6번만의 비교로 가능하다는 결론이 나왔다.
    - 그러므로 Key들을 5개씩 나눠서 이들의 미디안을 구하고, 이렇게 구한 미디안에서 미디안을 구하는 방식으로 미디안을 근사해보자.
        - 완벽한 중앙값은 아니겠지만, 적어도 랜덤보단 안정성이 보장될 것이다.
- 중앙값의 중앙값 알고리즘
    - $T(n) = 7n/10 -3/2$
    - Worst case
        - $W(n) <= 22n$
    - Worst case에서도 Linear함이 보장되는 정렬이 되었다.

### 실제로 구현한 Median 사용 알고리즘 (Algorithm 8.6)

```cpp
int select(int n, int S[], int k) {
	return selection2(S, 1, n, k);
}

int selection2(int S[], int low, int high, int k)
{
	int pivotpoint;
	if (low==high)
		return S[low];
	else {
		partition2(S,low, high, pivotpoint);
		if (k==pivotpoint)
			return S[pivotpoint];
		else if (k<pivotpoint)
			return selection2(S,low, pivotpoint-1, k);
		else
			return selection2(S, pivotpoint+1, high, k);
	}
}

void partition2(int S[], int low, int high, int& pivotpoint) {
	int arraysize = high-low-1;
	
	int r = (int)ceil((double)arraysize/5);
	int i, j, mark, first, last, pivotitem, T[r+1];

	for (i=1; i<=r; i++) {
		first = low + 5*i -1;
		last = min(low+5*i-1, low+arraysize-1);
		T[i]=median(S, first, last);
	}

	pivotitem = select(r, T, (r+1)/2);
	
	j=low;

	for (i=low; i<=high; i++) {
		if (S[i] == pivotitem){
			swap(S[i], S[j]);
			mark = j++;
		}		
		else if (S[i] < pivotitem)
			swap(S[i], S[j++]; 
	}

	pivotpoint = j - 1;
	swap(S[mark], S[pivotpoint]);
}
```

### 중앙값 찾아주는 C++ std::nth_element

```cpp
int median(vector<int> &v)
{
    size_t n = v.size() / 2;
    nth_element(v.begin(), v.begin()+n, v.end());
    return v[n];
}
```

## Randomized Algorithm의 3가지 타입

### Type 1. 몬테 카를로 알고리즘

- 굉장히 많은 시뮬레이션을 돌려서 벤치마크를 체크함.
    - 원주율 알고리즘
    - 몬티홀 문제
- 반드시 Correct한 답을 주진 않지만, Estimate한 근사 값을 줌.

### Type 2. 라스베가스 알고리즘

- 항상 Correct한 답을 줌
    - 근데 때때로는 아예 답을 못 주는 경우도 생김

### Type 3. 셔우드 알고리즘

- 항상 Correct한 답을 줌
- 근데 몇 번만에 Correct한 답을 줄 지 결정 불가능.

## 정리

- 선택 문제
    - 정렬되지 않은 고유값 리스트에서 K번째로 큰 키를 찾아라.
- 최대 값 찾기 문제
    - 무조건 N-1
- 차대값 찾기 문제
    - 토너먼트 방식 이용시 n + logN -2
- 최대값, 최소값 동시 찾기 문제
    - 홀수일시 3N/2 -3/2
    - 짝수일시 3N/2 -2
- K번째 수 찾기 문제
    - 퀵 셀렉션 응용
        - 피봇 선택 방식 (최악의 경우)
            1. 첫 번째 원소 선택 : O(N^2)
            2. 랜덤 선택 : O(N^2)
            3. 중앙값의 중앙값 : O(n)
    

---
