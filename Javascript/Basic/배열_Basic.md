# 자바스크립트 : 배열 기본

---

## 배열

- 사용법

```jsx
let student = ['철수', '영희', ... , '영수'];
```

배열은 대괄호로 묶어주고, 쉼표로 구분한다.

배열 요소들은 인덱스 넘버를 통해 호출할 수 있는데, 기본적으로 다른 언어와 비슷하다.

<br>

### 배열의 특징

**자바스크립트의 배열은 문자 뿐만 아니라 숫자, 객체, 함수 또한 포함할 수 있다.**

예를 들어

```jsx
let arr = [
	'민수',
  3,
  false,
  {
    name : Mike,
    age : 30,
  },
  function() {
    console.log("Hello!");
  }
];
```

이런 식으로 넣어도 된다.

<br>

### 유용한 기능

- `length` : 배열의 길이 반환

`student.length` // 30

- `push()` : 배열 끝에 추가

```jsx
let days = ['월', '화', '수'];

days.push('목');

console.log(days) // ['월', '화', '수', '목']
```

- `pop()` : 배열 끝 요소 제거
    - 예제 코드 생략

- `shift`, `unshift` : 배열 앞에 추가 / 제거
    - `unshift()` : `push_front()`
    - `shift()` : `pop_front()`

> **Tips** 💡

`push()`, `unshift()` 는 여러 개의 인수를 한번에 추가할 수도 있다.
// `days.push(’월’,’화’,’수’);`


<br>

### 배열의 반복문 1:  ( for )

```jsx
let days = ['월', '화', '수'];

for (let index = 0; index < days.length; index++) {
	console.log(days[index]);
}
```

배열의 요소들을 `for`문으로 출력할 수 있다. 아주 기본적.

<br>

### 배열의 반복문 2:  ( for … of )

```jsx
let days = ['월', '화', '수'];

for (let day of days){
	console.log(day);
}
```

C++ 의 `for… :` 랑 같다.

이 때, 객체 요소 순환시 사용하는 `for…in` 과 `for...of`는 반드시 구분해주자.

배열도 객체기 때문에 `in`을 사용해도 되지만, `of`를 쓰는 것이 훨씬 좋다.  

⚡ **배열은 `for...of` 써야된다!** ⚡
