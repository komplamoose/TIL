# 자바스크립트 : 배열 메소드 (sort, reduce)

---

### arr.sort()

```jsx
let arr = [1, 3, 2, 5, 4]

arr.sort() // 주의 ! 문자열로 처리해서 정렬한다.

console.log(arr); // [1, 2, 3, 4, 5]

let arr2 = [27, 8, 5, 13];
arr2.sort()

console.log(arr) // [13, 27, 5, 8]
// 숫자가 문자열로 처리되어 앞자리가 1인 13이 제일 먼저 오게 되었다.
```

배열을 재정렬한다. 

배열 자체를 변경해버린다. 


🔥 **새로운 배열이 생성되는 것이 아님** 🔥

문자열도 알파벳 순서대로 정렬해준다.

인수로 정렬 로직을 담은 함수를 넣어주어야 제대로 사용 가능하다.

그냥 돌리면 숫자도 문자열로 변환해서 제대로 정렬되지 않는다.

<br>

### arr.sort(fn)

```jsx
let arr = [27, 8, 5, 13];

arr.sort((a, b) => { // 숫자를 오름차순으로 정렬
	return a-b; 
});
// 두 요소를 가져와서, 크기를 비교한다.
// a가 b보다 크면 양수 리턴
// 같으면 0 리턴
// b가 a보다 크면 음수 리턴
// a와 b를 비교해서, a가 더 작으면 a를 앞으로 보내고, b가 더 작으면 b를 앞으로 보낸다.
// 같으면 가만히 놔둔다. 

arr.sort((a, b) => { // 숫자를 내림차순으로 정렬
	return b-a; 
});

-------------------------------------------------------------------------

let arr2 = ["banana", "n", "apple"];

arr2.sort() // 문자열을 사전순 (오름차순)으로 정렬 
// 대문자가 더 앞에 온다.

arr2.sort((a,b) => { // 문자열을 사전 역순 (내림차순)으로 정렬 
	if (a < b) return 1;
	if (a===b) return 0;
	if (a > b) return -1;
}); // 대문자가 더 앞에 온다.

arr2.sort((prev_a, prev_b) => { // 문자열을 대소문자 구분 없이 사전순(오름차순)으로 정렬 
	const a = prev_a.toUpperCase();
	const b = prev_b.toUpperCase();

	if (a > b) return 1;
	if (a===b) return 0;
	if (a < b) return -1;
});

arr2.sort((prev_a, prev_b) => { // 문자열을 대소문자 구분 없이 사전 역순(내림차순)으로 정렬 
	const a = prev_a.toUpperCase();
	const b = prev_b.toUpperCase();

	if (a < b) return 1;
	if (a===b) return 0;
	if (a > b) return -1;
});
```

보통 `Lodash`같은 라이브러리를 사용하면 편하게 사용할 수 있다. 

문자열은 유니코드순으로 정렬되는데, 이 경우 대문자가 소문자보다 앞에 오도록 정렬된다.

`toUpperCase()`를 사용해 모두 대문자로 변환해준 뒤 사용하면 대소문자 구분없이 가능하다.

(`toLowerCase()`도 가능)

<br>

### arr.reduce(fn) : 배열의 모든 수 합치기

```jsx
let arr = [1, 2, 3, 4, 5];

// for, for of, forEach를 사용해 더하기
let result=0;
arr.forEach(num => {
	result+=num;
});

// reduce 사용

const result = arr.reduce((prev, cur) => {
	return prev + cur;
}, 0)

// 누산값 : 0 + 현재값 1
// 누산값 : 1 + 현재값 2
// ...
// 누산값 : 10 + 현재값 5
```

인수로 함수를 받는다. 

배열의 모든 수를 합쳐서 리턴할 수 있다.

`(누적 계산값, 현재 값) ⇒ { return 계산값 };`

`reduce`는 함수를 받는데, 함수엔 이전 값(누산 값)과 현재 값이 인자로 들어간다.

누산값은 현재까지 누적된 계산값이다.

초기 값을 두 번째 인자로 넣어줄 수 있으며, 이는 `Optinal`하기 때문에

안 넣어주면 자동으로 초기 누산값에는 배열의 첫 번째 요소가 들어가게 된다.

<br>

### arr.reduce() 활용

```jsx
let userList = [
	{ name : "mike", age : 30 },
	{ name : "Tom", age : 10 },
	{ name : "Jane", age : 27},
	{ name : "Sue", age : 26},
	{ name : "Harry", age : 42},
	{ name : "Steve", age : 60},
];

let result = userList.reduce((prev, cur) => {
	if (cur.age > 19) {
		prev.push(cur.name);
  }
	return prev // 꼭 리턴 해줘야된다. 그래야 이게 다음 prev로 또 이어진다.
}, []) // 초기 값으로 빈 배열을 넣어준다.

```

`map()`이나 `filter()` 대신에, `reduce()`를 사용해서 배열을 반환할 수 있다.

`userList` 배열에서 성인 객체의 이름만 뽑아서 담은 배열로 반환해줄 수 있다.

<br>

↩️ ***Recap***

- `arr.map()`
    - 배열을 하나하나 순회하면서, 인자로 넣은 함수 기능을 수행할 수 있게 해주는 메소드
    - 요소 하나에 대한 함수 기능을 수행하고, 그 요소를 다시 반환해서 새로운 배열에 추가한다.
    - 요소 값을 하나하나 변경해서 처리한 뒤 새로운 배열을 생성하고자 할 때 편리하다.
- `arr.filter()`
    - 배열을 하나하나 순회하면서, 조건에 맞는 요소들을 모아놓은 배열을 반환하는 메소드
    - 조건에 맞는 요소들을 모두 찾고 싶을 때 사용하면 유용하다.

<br>

+) `reduceRight()` 

: `reduce()`와 기능적으로 동일하지만, `reduce()`가 배열 왼쪽에서부터 탐색하는 반면, `reduceRight()`는 배열 오른쪽부터 탐색한다.
