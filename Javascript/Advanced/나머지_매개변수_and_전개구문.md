# 자바스크립트 : 나머지 매개변수, 전개 구문

---

### 인수 전달

```jsx
fucntion showName(name) {
  console.log(name);
}

showName('Mike'); // result : 'Mike;

showName('Mike', 'Tom'); // result : 'Mike', NOT ERROR

showName(); // result : undefined, NOT ERROR
```

하나의 인수를 받는 함수에 2개의 인수를 전달하더라도

에러는 발생하지않고, 기존 ‘Mike’만 출력된다.

자바스크립트에서, 함수의 파라미터 갯수는 제한이 없다.

파라미터 갯수를 정해놓고 함수를 만들어도, 꼭 그걸 정확히 지키면서 호출하지 않아도 동작한다.

함수에서 인수를 얻는 방법은 2가지가 있다.

1. arguments로 접근
2. 나머지 매개 변수

과거엔 arguments만 사용했지만, 현재는 나머지 매개변수를 더 자주 사용한다.

화살표 함수에는 argument가 없다.

<br>

### arguments

```jsx
function showName(name) {
	console.log(arguments.length); // 받은 인수의 갯수
	console.log(arguments[0]); // 첫 번쨰로 받은 인수
	console.log(arguments[1]); // 두 번째로 받은 인수
}

showName('Mike', 'Tom');

// result :
// 2
// 'Mike'
// 'Tom'
```

- 함수로 넘어온 모든 인수에 접근
- 함수 내에서 이용가능한 지역 변수
- length, index 보유
- Array 형태의 객체
- 배열에서 사용할 수 있는 내장 메서드 없음 (ex. forEach, map…)
- 매개변수로 넘어온 인수들은 arguments 객체를 통해 접근 가능하다.
- ES6에선 사용 권장 안함

<br>

### 🔥 나머지 매개변수 (Rest Parameters)

```jsx
function showName(...names) { // ...배열이름
	console.log(names);
}

showName(); // [], 아무도 넣지 않으면 undefined가 아니라 빈 배열이 된다.
showName('Mike'); // ['Mike']
showName('Mike', 'Tom'); // ['Mike', 'Tom']
```

ES6 이후 버전의 자바스크립트에선, arguments 객체 사용 대신 

나머지 매개변수 방식을 사용하는 것이 권장된다. 

나머지 매개변수는 정해지지 않은 갯수의 인수를 배열로 나타낼 수 있게 한다.

인수로 점 ‘…’ 를 찍고, 배열 이름을 파라미터로 넣어준다.

그럼 이 인수들이 이 배열에 들어간다.

**배열이므로 forEach, map 등의 기존 배열 메소드를 사용할 수 있다. **

<br>

### 나머지 매개변수 활용

```jsx
function add(...numbers) {
	let result = numbers.reduce((prev, cur) => prev + cur);
	// 화살표 함수 내부가 1줄이고, 리턴문 밖에 없으면 다 생략 가능
}

add(1, 2, 3, 4, 5);
add(1, 2);
```

전달받은 모든 인수를 더하는 함수를 만들자.

매번 전달되는 인수의 숫자는 다르다.

<br>

### 나머지 매개변수 활용 (생성자 함수)

```jsx
function User(name, age, ...skills) { // skill을 나머지 매개변수로 입력받아
//1개 이상의 skill도 처리가능하게 한다.
	this.name = name;
	this.age = age;
	this.skills = skills;
}

const user = new User('Mike', 30, 'html', 'css');
const user = new User('Tom', 20, 'html');
```

user 객체를 만들어 주는 생성자 함수를 만든다고 가정하자.

이 때, skill의 갯수가 1개 이상인 경우도 처리해야 한다면

나머지 매개변수로 아예 배열로 받아 입력해주면 편리하다.

주의할 점은, 나머지 매개변수는 항상 매개변수 마지막 순서에 있어야 한다는 점이다.

<br>

### 전개 구문 (Spread syntax) : 배열

```jsx
let arr1 = [1, 2, 3];
let arr2 = [4, 5, 6];

let result = [...arr1, ...arr2];
// ...arr1 : 배열의 인자들을 풀어서 쓴 것
// 사실상 1, 2, 3, 4, 5, 6

let result2 = [0, ...arr1, ...arr2, 7, 8, 9, 10];
// 이렇게 중간에 쓰는 것도 가능하다.

console.log(result) // result : [1, 2, 3, 4, 5, 6]
```

배열 요소들을 풀어서 표현한다. 

`arr.push()`, `arr.splice()`, `arr.concat()` 등의 기능을 사용하지 않고도

편하게 배열을 만들 수 있다.

<br>

### 전개 구문 (Spread syntax) : 복제

```jsx
let arr = [1, 2, 3];
let arr2 = [...arr];

let user = {name : "mike", age : 30};
let user2 = {...user};

user2.name = "Tom" // user2 객체의 name 변경

console.log(user.name); // result : 'mike'
console.log(user2.name); // result : 'tom'
// 배열, 객체의 요소만을 정확히 복사함. 
// 기존에 그냥 대입하면 결국 user의 포인터를 가져가는 것과는 다름
```

`Object.assign()`을 쓰지 않고 쉽게 객체를 복제할 수 있다.
