# 자바스크립트 : Class

---

### Class

```jsx
const User = function (name, age) {
	this.name = name;
	this.age = age;
	showName(){
		console.log(this.name);
	}
};

const mike = new User("Mike", 30);

// 생성자 함수를 이용한 객체 생성 

class User2 {
	constructor(name, age) {
		this.name = name;
		this.age = age;	
	}
	showName(){
		console.log(this.name);
	}
}

const tom = new User2("tom", 19);

// class를 통한 생성.
```

우리는 지금까지 비슷한 형태의 객체를 생성하기 위해, `생성자 함수`를 이용했다.

이 과정을 `Class`를 사용해 구현할 수 있다.

`Class`는 `ES6`에 추가된 기능으로 기본적으로 `new`를 통해 객체를 생성하는 것은 동일하다.

`class`는 `생성자 함수`와 뭐가 다른걸까?

`class`는 `constructor`를 가지는데, 이 `constructor`는 객체를 만들어주는 생성자 메소드 기능을 한다.

`new`를 통해 실행하면, 이 `constructor`가 실행된다.

`showName()` 메소드는, `User2`의 프로토타입에 저장된다. 

생성자 함수를 통해 만들면, 생성자 함수 내의 함수가 객체 내부로 진입하지만, `class`를 통해 만들면

위 함수가 그 객체의 `prototype`에 위치하게 된다. 사용법은 동일하다.

물론 생성자 함수 prototype 내부에 직접 함수를 넣으면 class와 동일하게 구현할 수 있다.

그럼 class는 단순히 생성자 함수의 문법적 편의성을 위해 나타난 기능인걸까?

<br>

```jsx
const User = function (name, age) {
	this.name = name;
	this.age = age;
	showName(){
		console.log(this.name);
	}
};

const mike = User("Mike", 30);
// new 없이 실행
// result : undefined (NO ERROR)
// 개발자가 실수 했지만, 런타임 에러가 일어날 수 있음.

class User2 {
	constructor(name, age) {
		this.name = name;
		this.age = age;	
	}
	showName(){
		console.log(this.name);
	}
}

const tom = User2("tom", 19);
// new 없이 실행
// result : TypeError 발생
```

위처럼, `Class`를 통해 객체를 생성하면. `new` 키워드가 없이 사용하는 실수를 저질러도

자바스크립트에서 `TypeError`를 발생시켜 **런타임 에러**를 막아준다.

`클래스`를 통해 생성된 객체의 `__proto__`를 보면 그냥 `function`이 들어가있는 `mike` 객체와 다르게

`User2`를 통해 생성한 객체인 `tom` 프로토타입엔 `constructor`가 `class User2`로 정확히 명시되어 있다.

이걸 통해 `new` 없이 실행하면 에러가 발생하도록 한다.

<br>

```jsx
for (const p in mike) {
	console.log(p);
}
// 생성자 함수를 통해 생성한 객체 순회
// result : name, age, showName
// showName은 생성자함수의 프로토타입에 넣어주었음에도, for...in을 통해 접근된다.

for (const p in tom) {
	console.log(p);
}
// class를 통해 생성한 객체 순회
// result : name, age
// for...in을 통해 showName이 접근되지 않는다.
// 진짜 요소들만 접근할 수 있다.
```

또한 class의 메소드는, for…in 문에서 제외된다. 

hasOwnProperty()를 통해 프로토타입 프로퍼티인지 구분해주지 않아도 된다.

<br>

### class : 상속

```jsx
// extends

class Car {
	constructor(color){
		this.color = color;
		this.wheels = 4;
	}
	drive(){
		console.log("drive...");
	}
	stop(){
		console.log("stop!");
	}
}

class Bmw extends Car {
	park() {
		console.log("PARK");
	}
}

const z4 = new Bmw("blue");
```

생성자함수에선 prototype를 이용해서 상속을 구현하였다면

class에서는 더 편하게 상속을 사용할 수 있다. (Like Java)

기본적으로 자바랑 비슷하다.

이 때, z4를 살펴보면, `park()`는 `z4`의 프로토타입에 위치하고, 이 프로토타입은 `Car Class`다.

또한 `drive()`, `stop()`은 `Car`의 프로토타입에 위치한다.

만약 내가 `z4.drive()`를 사용한다면

1. 일단 `z4` 객체 내부에서 찾는다.
2. 없으면 프로토타입인 `Car` 객체 내부에서 찾는다.
3. 여기에도 없으면 `Car` 객체의 프로토타입 내부에서 찾는다.

<br>

### class : 메소드 오버라이딩 (Overriding)

```jsx
// extends

class Car {
	constructor(color){
		this.color = color;
		this.wheels = 4;
	}
	drive(){
		console.log("drive...");
	}
	stop(){
		console.log("stop!");
	}
}

class Bmw extends Car {
	park() {
		console.log("PARK");
	}
	stop() {
		super.stop() // 부모 클래스인 Car의 stop() 메소드를 호출한다.
		console.log("OFF");
	}
}

*const z4 = new Bmw("blue");*
```

만약 자식 클래스가 부모 클래스가 가진 메소드와 동일한 이름을 가진 메소드를 갖는다면 어떻게 될까?

아까 배웠던 것처럼, 호출시 무조건 자기 자신부터 탐색해서 점점 부모로 탐색하므로

같은 이름을 가졌더라도 자식의 함수를 부르고 끝난다.

만약 부모의 메소드를 그대로 사용하면서, 그 기능을 확장하고 싶다면 어떻게 할까?

그럴땐 `super` 키워드를 사용하면 된다.

이 키워드를 붙이면 같은 이름을 가졌더라도 부모 클래스의 기능을 불러 사용할 수 있다.

이런 방식을 바로 `오버라이딩`이라고 한다.

<br>

### class : 생성자 오버라이딩

```jsx
class Car {
	constructor(color){ // 실행시 빈 객체 {} 생성 후 추가
		this.color = color;
		this.wheels = 4;
	}
	drive(){
		console.log("drive...");
	}
	stop(){
		console.log("stop!");
	}
}

class Bmw extends Car {
	constructor() {
		this.navi = 1;
	}
	park() {
		console.log("PARK");
	}
}

const z4 = new Bmw("blue");
// 오류 발생.
// 자식 생성자 호출 전에 super constructor을 통해 부모 생성자를 먼저 호출해줘야 한다.

--------------------------------------------------------------
class Bmw extends Car {
	constructor() {
		this.navi = 1;
	}
	park() { // extends를 통해 상속받은 클래스는 생성자가 객체를 생성하지 않음
		super();
		console.log("PARK");
	}
}

const z4 = new Bmw("blue");
// result : { color : undefined, wheels : 4, nave : 1 }
// 자식 클래스에서 인수를 받지 않아, undefined가 들어갔다.

----------------------------------------------------------------------
class Bmw extends Car {
	constructor() {
		this.navi = 1;
	}
	park(color) { // extends를 통해 상속받은 클래스는 생성자가 객체를 생성하지 않음
		super(color);
		console.log("PARK");
	}
}

const z4 = new Bmw("blue");
```

메소드처럼 생성자로 오버라이딩 될 수 있다.

이 때 자식 클래스의 생성자가 따로 있다면, 부모 생성자를 먼저 호출해주어야 한다.

클래스의 생성자는, 일단 빈 객체를 만들어주고 

`this`로 이 객체를 가리키게 된다.

근데 `extends`를 통해 상속을 받은 클래스의 생성자는, **빈 객체를 만드는 작업을 건너 뛴다.**

이미 객체가 있다고 가정한다. 그걸 방지하기 위해 부모 생성자를 반드시 호출해주어야 한다.

또한 부모 생성자를 호출하기 위해, 자식 생성자도 부모 생성자의 파라미터를 입력받아야 제대로 동작한다.

자바스크립트의 내부 동작과정에 대해 알아보자.

만약 자식 클래스에서 생성자를 정의하지 않았다면, 자식 클래스는

<br>

```jsx
class Bmw extends Car {
	constructor(...args) { // 나머지 인수. 파라미터 몇 개든 그냥 다 받아버림
		super(..args);
	} // 생성자가 없으면 자바스크립트는 이 클래스의 생성자는 이렇게 존재한다고 가정한다.
}
```

이렇게 가정하고 동작한다.

무조건 super가 호출되므로, 자식 클래스에 constructor가 따로 있으면 super를 해주어야 하는 이유다.

<br>
