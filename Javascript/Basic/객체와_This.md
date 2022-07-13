# 자바스크립트 : 객체

---

## Part 1. 객체 (Object) Basic

객체를 하나 만들어보자. 

```jsx
const superman = {
  name : 'clark',
  age : 33,
};
```

+) 객체 요소 마지막엔, 그냥 ‘,’ 를 추가해주는 것이 이후 추가-수정 시 편하다.

객체는 중괄호로 작성하고, 내부 프로퍼티로 구성된다.

만든 객체에 접근해보자. 

<br>

### 객체 - 접근, 추가, 삭제

**접근**

```jsx
superman.name // 'clark'
superman['age'] // 33
```

**추가**

```jsx
superman.gender = 'male';
superman['hairColor'] = 'black';
```

**삭제**

```jsx
delete superman.hairColor;
```

삭제하고 싶은 프로퍼티 앞에 `delete` 키워드를 붙혀준다.

<br>

### 객체 - 단축 프로퍼티

만약에 현재

```jsx
const name = 'clark';
const age = 33;

const superman = {
  name : name,
  age : age,
  gender : 'male',
}
```

이런 상태로 객체가 존재한다고 가정하자. 이 때, 객체에 들어갈 값은 

name == ‘clark’

age == ‘33’

이 된다.

근데 이미 변수가 선언되었고, 객체에 그 변수를 프로퍼티로 넣고 싶은 경우

```jsx
const name = 'clark';
const age = 33;

const superman = {
  name,
  age,
  gender : 'male',
}
```

이렇게도 사용할 수 있다.

<br>

### 객체 - 프로퍼티 존재 여부 확인

객체에 존재하지 않는 프로퍼티를 호출하면 

**undefined**가 나온다. 

객체에 이 프로퍼티가 있는지 없는지 확실히 판단하려면 어떻게 해야할까?

```jsx
'birthDay' in superman;
// false

'age' in superman;
// true
```

이 `in`은 언제 쓰는게 좋을까?

어떤 값이 넘어올 지 모를 때 사용하면 된다. 

<br>

### for … in 반복문

```jsx
 for (let key in superman) {
  console.log(key);
  console.log(superman[key]);
}
```

for … in 반복문을 사용하면, 객체 내부의 프로퍼티를 순회할 수 있다.

<br>

### 객체 생성 함수

함수의 리턴 값으로 객체를 반환할 수도 있다.

```jsx
const makeObject = (name, age) => {
  return {
		name : name,
    age : age,
    hobby : "Soccer",
	};
};

const Mike = makeObject('Mike', 30);
```

변수 이름과 프로퍼티 이름이 동일할 경우 축약해서 사용할 수 있다.

<br>

### ‘in’ 키워드 활용

person 객체를 입력받아, 이 객체가 성인인지 아닌지 판별하는 함수를 하나 작성해보자.

```jsx
const isAdult = user => {
	if (user.age < 20) {
	  return false;
  }
	return true;
}
```

보기엔 잘 동작할 것처럼 보인다.

근데 만약 age라는 프로퍼티가 없는 객체가 입력된다면 어떻게 될까?

**이 경우에도 결과값은 True가 나온다**

없는 객체를 호출하면, 그 반환값은 `undefined`가 된다.

그 경우 if 문을 통한 결과값은 false가 되기 때문에, 위의 조건문을 스킵하는 것이다. 

제대로 동작하도록 고쳐보자.

```jsx
const isAdult = user => {
	if (!('age' in user) || user.age < 20) {
	  return false;
  }
	return true;
}
```

위의 조건식을 삽입하면, 나이가 없는 경우 성인이 아니라고 판단할 수 있다.

`age`가 없을 경우 `‘age’ in user` 에서 결과값이 `false`가 나올 것이고, 이걸 true로 변환해 조건식을 만족하도록 한다.

<br>

<br>

## Part 2. 객체 - this, method

이전에 만든 `superman` 객체에 함수를 추가해보자.

<br>

### Method

```jsx
const superman = {
  name : 'clark',
  age : 33,
  fly : fucntion(){
    console.log('I Can Fly!');
  },
}

superman.fly();
// I Can Fly!
```

이렇게 객체 프로퍼티로 할당된 함수를

`**method**`라고 한다.

이 때, 이 코드는

```jsx
const superman = {
  name : 'clark',
  age : 33,
  fly(){
    console.log('I Can Fly!');
  },
}

superman.fly();
// I Can Fly!
```

이렇게 축약해서 사용할 수 있다. `function` 키워드를 생략할 수 있다.

<br>

### This

메소드 호출시, 객체의 `name`을 출력하는 메소드를 작성해보자.

```jsx
const user = {
  name : 'Mike',
  sayHello() {
    console.log(`Hello, I'm ${user.name}`);
  },
}
```

뭔가 이렇게 하면 될 것 같다.

근데 문제가 발생할 수 있다. 위와 같은 기능을 작성하기 위해선

```jsx
const user = {
  name : 'Mike',
  sayHello() {
    console.log(`Hello, I'm ${this.name}`);
  },
}
```

`this` 키워드를 사용해야 한다. 

이 때

 `user.sayHello()`

를 호출하면, `this`는 자동으로 호출한 객체로 변환된다. 

`this`를 활용하는 것이 좋은 예시를 살펴보자

```jsx
let boy = {
	name : "John",
}

let girl = {
	name : "Jane",
}

sayHello : fucntion() {
	console.log(`Hello, I'm ${this.name}`);
}
```

위의 `boy`, `girl` 객체에 `sayHello()`를 넣어보자.

`this`는, `Runtime`시 결정된다.

결론적으로 

`boy.seyHello()`의 결과값은 // Jonh이 되고,

`girl.sayHello()`의 결과값은 // Jane이 되는 것이다.
와
또한 객체를 다른 변수에 할당해서 또 다른 객체를 만들때도, this 키워드를 사용하지 않고 객체 이름으로 호출시 문제가 발생할 수 있게 된다.

<br>

### 화살표 함수

근데 만약 위의 sayHello() 를 화살표 함수로 선언했다면 동작이 완전 달라진다.

```jsx
sayHello : () => {
	console.log(`Hello, I'm ${this.name}`);
}
```

🔥 **중요** 🔥

: 화살표 함수는 일반 함수와 달리, 자신만의 this를 가지지 않는다. 
화살표 함수에서 this를 사용하면, 그 this는 함수 외부에서 값을 가져오게 된다.

만약 이런 객체가 있다고 생각해보자,

```jsx
let boy = {
	name : "Mike",
  sayHello : () => {
    console.log(this);
  },
}

boy.sayHello();

// this != boy
```

메소드를 화살표 함수로 선언할 시, `this`는 `boy`가 아니다!

화살표 함수는 `this`를 갖지 않는다. 이 경우 화살표 함수는 전역객체인 `this`를 불러온다.

이 때 전역객체 `this` 는 

- 브라우저 환경 : `window`
- Node.js 환경 : `global`

이다.

 `this` 는 매우 복잡해 따로 나중에 따로 정리하겠다.

> 결론적으로, 객체에 메소드를 작성할 땐, 화살표 함수를 사용하지 않는 것이 좋다.
>
