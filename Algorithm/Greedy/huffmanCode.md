# 알고리즘 : Greedy Approach

---

## 허프만 코드

---

> 데이터 압축 문제
> 
<br>

### 문제 설명

- 문자로 이뤄진 데이터 파일을, 이진파일로 Encode하자.
- 이 때, 각 문자들은 구분할 수 있도록 고유한 이진 형태로 변환되어야 할 것이다.
    - (ex. A ⇒ 01, B⇒ 101)
- 근데 각 문자를 정확히 구분하기 위해 Fully하게 비트 수를 사용한다면, 변환된 이진 파일의 크기가 지나치게 커지게 된다.
- 어짜피 변환만 가능하면 되니까, 이렇게 문자-이진 형태로 변환되는 경우에 이진 파일의 용량을 최소화하는 방법은 무엇일까?
- 가장 많이 나오는 문자를 작은 비트로 할당해주면, 적은 비트수를 사용할 수 있을 것이다.
<br>

### 최적 이진 코드

- 루트 노드로 부터 시작되어, 왼쪽은 0, 오른쪽은 1을 의미하는 트리를 생성한다.
- 문자의 비트를 하나하나 읽어가면서 트리를 탐색하면, 쉽게 구분할 수 있게 된다.
    - Leaf 노드에 도착하기 전까지 비트 자릿수 따라서 계속 탐색하면 된다.
- 이때, 한 문자의 코드 워드(비트로 변환된 값)은, 다른 문자의 코드워드의 prefix(전치)가 될 수 없다.
    - 만약 A가 001이라면, 001로 시작하는 다른 비트 변환결과는 존재할 수 없다.
- 이 때, 문자 변환하였을 때 소요된 총 비트 수는
    - 그 문자의 빈도수 * 그 문자가 존재하는 트리의 Depth이다.
    - 그래서 최종적으로 이 비트 수를 최소화하도록 트리를 생성하는 방법이 바로 허프만 알고리즘이다.
<br>

### 허프만 알고리즘

> Greedy하게 접근하여, 이런 최적 이진 코드 트리를 생성해주는 방법
> 
<br>

### 구현

1. Frequency 기준, 오름차순으로 정렬하는 우선순위 큐를 생성한다.
2. 주어진 단어들을 모두 빈도-단어로 이뤄진 노드로 생성해서 큐에 넣는다.
3. 큐에서 2개의 노드를 뽑는다. (가장 낮은 빈도 2개)
4. 가상의 노드를 하나 생성하고, 2개의 뽑은 노드들을 이 노드의 Left Child, Right Child로 집어 넣어준다.
5. 이때 가상의 노드의 빈도수는 left+right의 빈도수 합이고, 단어는 임의의 단어다.
6. 이걸 큐 사이즈가 1이 될 때까지 (큐에 하나만 남아있을 때까지) 반복한다.
7. 큐에 하나 남은 것을 뽑으면, 이게 허프만 알고리즘을 통해 생성된 최적 이진 코드 트리의 루트 노드다.
<br>

### 시간 복잡도

- min heap으로 구현된 우선순위 큐의 삽입은 logN의 시간 복잡도를 가진다.
- 이걸 모든 단어 n에 대해 반복하므로 시간 복잡도는 O(nlogn)이 된다.
<br>

### 만들어진 허프만 코드를 통해 인코딩 (문자⇒이진)

- 각 문자에 맞는 이진 변환 Map을 생성해서, 문자를 입력받으면 Map의 key를 통해 이에 맞는 이진 값으로 변환해주면 된다.
    - Key-Value : 문자-이진 값
<br>

### 만들어진 허프만 코드를 통해 디코딩 (이진⇒문자)

- Prefix 형태를 유지했기 때문에, 한 문자의 끝에 도달했다면 그 뒤는 확인하지 않아도 된다.
    - a=11일 때, 비트 체크를 통해 11까지 도달했다면 그 이상은 볼 필요 없다. 11로 시작되는 문자는 a 하나밖에 없기 때문이다.
- 숫자를 읽어가면서, 0이면 트리의 왼쪽, 1이면 트리의 오른쪽으로 이동해간다.
- 만약 트리의 Leaf 노드에 도착했다면, 그 노드에 있는 문자를 반환하고, 다시 Root로 돌아가서 다음 비트숫자부터 또 탐색한다.
<br>

### 전체 코드

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

typedef struct node *node_ptr;
typedef struct node {
    char symbol;
    int frequency;
    node_ptr left;
    node_ptr right;
}node_t; // 트리 생성을 위한 노드

struct compare {
    bool operator()(node_ptr p, node_ptr q) {
        return p->frequency > q->frequency;
    }
}; // Frequency가 낮은 기준으로 정렬하기 위한 우선순위 큐의 비교함수

typedef priority_queue<node_ptr, vector<node_ptr>, compare> PriorityQueue;

node_ptr rt;
PriorityQueue PQ;

node_ptr create_node(char c, int fq) // 노드 생성 함수
{
    node_ptr temp = (node_ptr)malloc(sizeof(node_t));
    temp->symbol=c;
    temp->frequency=fq;
    temp->left=NULL;
    temp->right=NULL;

    return temp;
}

void huffman(int n) // 허프만 트리 생성 함수
{
    while(PQ.size()!=1) { // 마지막에 2개 남았을 때 합치면 무조건 size=1이 되므로 이때 탈출해야 한다.
        node_ptr p = PQ.top(); PQ.pop();
        node_ptr q = PQ.top(); PQ.pop();
        node_ptr r = create_node('+', p->frequency+q->frequency);
        r->left = p;
        r->right = q;

        PQ.push(r);
    }
}

void encode(node_ptr root, vector<int>& code, map<char, vector<int>>& encoder)
{
    if (root->symbol != '+'){ // '+' 가 아니라면 => 노드가 현재 Leaf 노드에 도달했다면
        vector<int> ret; // 리프노드까지 도달했을 때의 code => 그 문자의 이진 변환 결과
        ret.resize(code.size());
        copy(code.begin(), code.end(), ret.begin()); // ret에 옮겨담아서 symbol - code 형태로 맵에 넣어줌
        encoder.insert(make_pair(root->symbol, ret));
    }
    else if (root != NULL) { // Null이 아니라면 => 노드가 존재한다면.
        code.push_back(0); // 노드의 왼쪽으로 탐색
        encode(root->left, code, encoder);
        code.pop_back();
        code.push_back(1); // 노드의 오른쪽으로 탐색
        encode(root->right,code, encoder);
        code.pop_back();
    }
}

string decode(node_ptr root, string s)
{
    node_ptr cur = root; // 루트로 다시 돌아가야 하기 때문에, 루트 값은 건드리지 않고 가상의 Temp cur 생성

    string result = "";
    for (auto c : s)
    {
        if (c=='0') {
            cur = cur->left; // 이진값이 0이면 트리의 왼쪽
        }else {
            cur = cur->right; // 이진값이 1이면 트리의 오른쪽
        }

        if (cur->left==NULL && cur->right==NULL) { // 만약 왼쪽 오른쪽 둘 다 NULL => 리프노드 도착
            result += cur->symbol; // 도달한 리프노드의 문자로 변환
            cur = root; // 다시 루트로 돌아가줌
        }
    }

    return result;
}

void preorder(node_ptr root)
{
    if (root!=NULL){
        cout << root->symbol<<":"<<root->frequency<<" ";
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(node_ptr root)
{
    if (root!=NULL){
        inorder(root->left);
        cout << root->symbol<<":"<<root->frequency<<" ";
        inorder(root->right);
    }
}

void solve(int n)
{
    huffman(n); // 총 입력받은 문자 수 n을 파라미터로 넣어서 허프만 트리를 생성한다. 
    rt = PQ.top(); // 허프만 트리의 루트노드를 받아준다.
    preorder(rt); cout << "\n"; // 루트노드를 전위순회한다.
    inorder(rt); cout << "\n"; // 루트노드를 중위순회한다. 
    vector<int> code; // 문자=>이진 형태로 변환된 결과값(문자 하나의 변환결과에 해당)을 담을 배열
    map<char,vector<int>> encoder; // 문자 : 이에 맞는 이진값을 담는 벡터 구조로 되어있는 맵을 만든다.
    encode(rt, code, encoder);

    int c1;
    cin >> c1; // 테스트케이스
    for (int i=0; i<c1; i++) // encoding
    {
        string s;
        cin >> s; // 변환할 문자열 입력받기
        for (int j=0; j<s.length(); j++) { // 그냥 문자열의 각 문자를 Key로 넣어서 해당하는 Value 리턴해주면 됨
            vector<int> temp = encoder[s[j]];
            for (auto loop : temp) {
                cout << loop;
            }
        }
        cout << "\n";
    }

    // 이진 => 문자로 decode 하는 부분
    int c2;
    cin >> c2;
    for (int i=0; i<c2; i++) // decoding
    {
        string s;
        cin >> s;
        
        string d = decode(rt, s); // 루트노드와 이진코드를 입력으로 받음
        
        cout << d << "\n";
    }
}

int main()
{
    int n;
    cin >> n;

    vector<char> cV;
    vector<int> fqV;
    for (int i=0; i<n; i++){ // 문자 입력받기
        char c;
        cin >> c;
        cV.push_back(c);
    }
    for (int i=0; i<n; i++){ // 빈도수 입력받기
        int input;
        cin >> input;
        fqV.push_back(input);
    }
    for (int i=0; i<n; i++){ // 문자-빈도수를 노드에 담아서, 이 노드를 우선순위 큐에 집어넣는다. 
        node_ptr temp = create_node(cV[i],fqV[i]);
        PQ.push(temp);
    }

    solve(n);
}
```

 

---
