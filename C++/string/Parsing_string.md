# ☑️ C++ 문자열 파싱 : std::sstream

---

: 이정도만 써도 파이썬 부럽지 않다. (사실 부럽다)
<br>


## istringstream : 공백 기준으로 자르기

> `string`을 입력받아, `공백` 기준으로 잘라준다.
> 

<br>

### 활용법

```cpp
#include <sstream>
#include <string>

using namespace std;

int main()
{
	istringstream iss("Test String 123");
	string str1, str2;
	int i1;

	iss >> str1 >> str2 >> i1;
}
```

- `istringstream` 사용시, 자동으로 공백 기준으로 문자열을 파싱할 수 있다.
- 분리된 결과물의 타입은 변수 타입에 맞춰 저장할 수 있다.

<br>

## stringstream , getline() : 토큰으로 자르기

> `공백` 말고 `토큰` 기준으로 자르고 싶을 땐 이렇게 잘라보자.
> 

### 활용법

```cpp
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	string test = "Test,String,123", token;
	stringstream ss(test);

	while (getline(ss,token,',') {
		cout << token << endl;
	}
}
```

---

# I Will be back. 👍
