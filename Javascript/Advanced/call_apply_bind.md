# 자바스크립트 : call, apply, bind

---

함수 호출 방식과 관계 없이 this가 무엇인지 지정할 수 있다.

### call

```jsx
const mike = {
	name : "Mike",
};

const tom = {
	name : "Tom",
};

function showThisName() {
	console.log(this.name);
};

function update(birthYear, occupation){
	this.birthYear = birthYear;
	this.occupation = occupation;
}

showThisName(); // this : window
// window의 name은 빈 문자열
showThisName.call(mike); // this : mike
showThisName.call(tom); // this : tom

---

update.call(mike, 1999, 'singer') // update 함수의 인자로 1999, 'singer'를 전달
update.call(mike, 2002, 'teacher')
```

모든 함수에서 사용할 수 있으며, 객체를 넘겨 this를 특정 값으로 지정할 수 있다.

해당 함수가 주어진 객체의 메소드인 것처럼 사용할 수 있다.

call의 첫 번째 파라미터는 this로 사용할 값이고, 그 이후로 들어가는 파라미터는 이 호출하는 함수의 파라미터로 들어간다.

<br>

### apply

```jsx
const mike = {
	name : "Mike",
};

const tom = {
	name : "Tom",
};

function update(birthYear, occupation){
	this.birthYear = birthYear;
	this.occupation = occupation;
}

update.apply(mike, [1999, 'singer']) // update 함수의 인자로 [1999, 'singer']를 전달
update.apply(mike, [2002, 'teacher']) // 함수의 파라미터 인자로 배열을 넘겨줘야 한다.
```

함수 매개변수를 처리하는 방법을 제외하면 call과 완전히 같다.

call은 일반적인 함수와 마찬가지의 방식으로 매개변수를 받는데 반해

apply는 매개변수를 배열 형태로 받는다.

<br>

### apply 응용

```jsx
const num = [3, 10, 1, 4, 6]

const minNum = Math.min(num) // 동작 안함. 배열 말고 풀어서 받아야함.
const minNum = Math.min(...num) // 방법 1. Spread syntax

// apply 사용
const minNum = Math.min.apply(null, num); // num 배열의 값들을 차례대로 인수로 사용함.
// this가 필요 없으면 아무 값이나 넣어도 된다.
```

<br>

### bind : this 값을 영구히 바꿔준다.

```jsx
const mike = {
	name : "Mike",
};

function update(birthYear, occupation) {
	this.birthYear = birthYear;
	this.occupation = occupation;
}

const updateMike = update.bind(mike);
```

함수의 this 값을 영구히 바꿔줄 수 있다.

update함수의 this 값이 항상 어떤 경우에서든 mike 객체를 의미하도록 바꿔줄 수 있다.

bind시 함수와 객체를 묶어 새로운 함수를 반환한다.

반환되는 함수는 항상 bind되는 객체를 this로 받는다.

<br>

### call, apply, bind : 실사용 예제

```jsx
const user = {
	name : "Mike",
	showName : function () {
	  console.log(`hello, ${this.name}`);
  },
};

user.showName(); // result : hello, mike

let fn = user.showName;

fn(); // result : "", this를 잃어버림.
fn().call(user) // result : hello, mike
fn().apply(user) // same

let boundFn = fn.bind(user);

boundFn(); // result : hello, mike

```

객체 안에 있던 this를 사용하는 함수를 따로 불러서 쓰려고 할 때 유용하게 사용할 수 있다. 

bind시 잃어버렸던 this의 행방을 강제로 지정하여 사용할 수 있다.
