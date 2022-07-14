# 자바스크립트 : 메소드, 계산된 프로퍼티

---
<br>

## Computed property

```jsx
let a = 'age';

const user = {
	name : 'Mike',
	age : 30,
}
```
이런 변수, 객체가 존재한다고 가정하자.
<br>


```jsx
let a = 'age';

const user = {
	name : 'Mike',
	[a] : 30,
}
```
이렇게 사용해도 된다. 이때 `[a]` 에는, `변수 a`에 할당된 값이 들어간다.
<br>


```jsx
const user = {
	[1 + 4] : 5,
	["안녕" + "하세요"] : "Hello",
}

console.log(user)
// { 5 : 5, 안녕하세요 : "Hello" }
```
이런 식으로 안에 식 자체를 넣는 것도 가능하다.
<br>


- 사용법

```jsx
function makeObj(key, val) {
	return {
		[key] : val,
	};
}

const obj = makeObj("나이", 33);
```

이런 식으로 쓸 때 좋다. 어떤게 키가 될 지 모르는 객체를 생성해야 할 때 유용하다.
<br>
<br>

## 객체 Methods

객체에서 사용할 수 있는 다양한 메서드들을 알아보자.
<br>

### 1. Object.assign()

: 객체를 복사해준다.

```jsx
const user = {
	name : 'mike',
	age : 30,
}

const cloneUser = user;
```

이 user를 그냥 cloneUser에 할당한다고, 객체가 복사되는 걸까?

**아니다**

user가 담고 있는 것은, 객체가 위치한 메모리 주소다.

그냥 객체 참조 주소을 복사할 뿐이라는 것이다. 

`얕은 복사`가 일어난다.
<br>

- 사용법

```jsx
const newUser = Object.assign({}, user);
```

여기서 `빈 객체 {}`는 초기값이다. 

`빈 객체 {}`에, `user`의 값들이 복사되고, 이 `객체 {}`를 할당받는 것이다. 

`빈 객체 {}`에 `user` 객체를 병합한 뒤, 넘겨주는 것으로 이해하면 된다.

객체를 새로 만들어 넘겨주었으니 `깊은 복사`가 일어난다.

- 이 때 빈 객체 {} 대신 이미 값이 있는 객체
    - ex. `{ food : “kimchi” }` 등을 만들어 넣어주면, 그 객체에 `user`를 합친 뒤, 그 객체를 다시 돌려준다.

- `파라미터 1 객체의 프로퍼티`와 `user의 프로퍼티` 중 이름이 같은 것이 있다면 어떻게 될까?
    - user의 값을 덮어 씌운다.
<br>

- 응용

```jsx
const user = {
	name : "mike",
}

const info1 = {
	age : 30,
}

const info2 = {
	gender : "male"
}

Object.assign(user, info1, info2)
// user에 info1, info2를 병합!
```

이렇게 사용해도 된다. Object는 이미 어딘가에 존재한다고 생각해도 된다. 
<br>

### 2. Object.keys()

: Key 배열을 반환한다. 

```jsx
const user = {
	name : 'mike',
	age : 30,
	gender : "male"
}

Object.keys(user);
```

객체를 인수로 넘겨주면, 이 객체의 `key`로 이뤄진 배열을 반환한다.
<br>

### 3. Object.values()

: Value 배열을 반환한다. 

```jsx
const user = {
	name : 'mike',
	age : 30,
	gender : "male"
}

Object.values(user);
```

객체를 인수로 넘겨주면, 이 객체의 `value`로 이뤄진 배열을 반환한다.
<br>

### 4. Object.entries()

: Key/Value 배열을 반환한다. 

```jsx
const user = {
	name : 'mike',
	age : 30,
	gender : "male"
}

Object.entries(user);

// [ ["name", "Mike"], ["age", 30], ["gender", "male"] ]
```

객체를 인수로 넘겨주면, 이 객체의 `key-value 쌍`으로 이뤄진 배열을 반환한다.
<br>

### 5. Object.fromEntries()

: Key/Value 배열을 입력받아, 객체로 반환해준다.

```jsx
const arr = [
	["name", "Mike"],
	["age", 30],
	["gender", "male"]
];

Object.fromEntries(arr);
```

 `key-value 쌍`으로 이뤄진 배열을 입력받아, 객체로 만들어 반환한다.
 
<br>
<br>
