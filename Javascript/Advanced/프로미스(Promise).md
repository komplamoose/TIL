# 자바스크립트 : Promise

---

### Promise

```jsx
const pr = new Promise((resolve, reject) => {
	// code..
});
```

프로미스는 비동기 처리를 도와준다.

인자로 함수를 전달 받는다.

- resolve : 작업이 성공한 경우 실행할 함수
- reject : 작업이 실패할 경우 실행할 함수

이렇게 어떤 일이 완료된 후 실행되는 함수를 `callback` 함수라고 한다.

<br>

### promise 객체

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/d1ce9b82-625f-4303-be42-670a8823e541/Untitled.png)

new Promise() 생성자가 반환하는 promise 객체는 state와 result를 프로퍼티로 가진다.

이 때 state는 초기에 `pending`이었다가. resolve(value) 함수가 호출되면 ( == 성공하면 ) 

`fulfilled` 상태로 변경된다.

이 때 result 프로퍼티의 값은, resolve 함수로 전달된 value 값이 들어간다.

만약 reject(error) 함수가 호출되면 ( == 실패하면 )

state는 rejected가 되고, result는 reject 함수로 전달된 error가 된다.

<br>

### 코드로 살펴보기

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/5c452e0f-564b-468d-ab1c-369d11f6fc0d/Untitled.png)

3초 뒤 setTimeout이 실행되면, resolve() 함수를 호출하고, 그 때 state가 fulfilled로 변경되고, result가 ‘OK’가 된다.

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/ee09550c-aaca-4b32-bd72-f72ecba57254/Untitled.png)

3초 뒤  setTimeout이 실행되면, reject() 함수를 실행하고, 프로퍼티가 바뀐다.

<br>

### then

```jsx
const pr = new Promise((resolve, reject) => {
	setTimeout(() => {
		resolve('OK');
	}, 3000);
}); // 3초 뒤 성공함수 실행

pr.then(
	function(result){
		console.log(result + " 가지러 가자!");
	}, // 성공시 실행, result엔 resolve()의 파라미터인 'OK' 입력
	function(err){
		console.log("다시 해주세요");
	} // 실패시 실행, err엔 error 값이 들어감.
);
```

then()을 이용하여 resolve와 reject를 실행할 수 있다.

then()의 첫 번째 인자는, 작업이 성공적으로 이행되었을 때 실행하는 함수다.

then()의 두 번째 인자는, 작업이 실패했을 때 실행하는 함수다. 

<br>

### catch, finally

```jsx
pr.then( // then만으로 구현
	function(result){
		console.log(result + " 가지러 가자!");
	}, // 성공시 실행, result엔 resolve()의 파라미터인 'OK' 입력
	function(err){
		console.log("다시 해주세요");
	} // 실패시 실행, err엔 error 값이 들어감.
);

---

pr.then( // catch로 구현
	function(result) {}
).catch)
	function(err){}
);

---

pr.then( // catch로 구현
	function(result) {}
).catch(
	function(err){}
).finally(
	function() {
		console.log("THE END");
	}
);
```

`then()` 이외에도 `catch()`, `finally()`를 사용할 수 있다.

`catch`는 에러가 발생할 경우에만 실행된다.

이렇게 사용하면, 가독성도 매우 좋아지고, 

성공시 실행할 함수로부터 발생하는 에러도 잡아줄 수 있기 떄문에, `catch`를 사용하는 것이 훨씬 좋다.

`finally()`는 `promiss`가 이행되던, 에러가 발생되던, 항상 실행되는 함수다.

로딩 화면 같은 것을 없앨 때 유용하다.

<br>

### 콜백지옥

```jsx
//f1 - f2 - f3 순서로 실행되는 프로그램을 작성해보자

const f1 = (callback) => {
	setTimeout(function () {
		console.log("1번 주문 완료");
		callback();
	},1000);
};

const f2 = (callback) => {
	setTimeout(function () {
		console.log("2번 주문 완료");
		callback();
	},2000);
};

const f3 = (callback) => {
	setTimeout(function () {
		console.log("3번 주문 완료");
		callback();
	},3000);
};

// promise 없이 작성, Callback Hell
f1(function() {
	f2(function() {
		f3(function(){
			console.log("Done.");
		});
	});
});
```

`promise` 없이 순서가 보장된 작업을 구현하기 위해선, `callback` 함수를 이용한 `callback hell`을 벗어날 수 없다.

위의 방법을 promise로 구현해보자.

<br>

### promise로 콜백지옥 탈출하기

```jsx
const f1 = () => {
	return new Promise((res, rej) => {
		setTimeout(() => {
			console.log("1번 주문 완료");
		},1000);
	});
}

const f2 = (message) => {
	console.log(message);
	return new Promise((res, rej) => {
		setTimeout(() => {
			console.log("2번 주문 완료");
		},3000);
	});
}

const f1 = (message) => {
	console.log(message);
	return new Promise((res, rej) => {
		setTimeout(() => {
			console.log("3번 주문 완료");
		},2000);
	});
}

f1()
.then((res) => f2(res)) // f1의 promise의 결과값 res를 f2로 넘겨주는 함수 작성
.then((res) => f3(res)) // f2의 반환값인 promise로부터 then 실행
.then((res) => console.log(res))
.catch(console.log("Error") // f1, 이나 f2에서 에러가 발생하더라도 바로 catch가 실행된다.
.finally(() => {
	console.log("The end")
});
```

이렇게 promise 사용시, 좀 더 가독성 있는 코드를 작성할 수 있다.

이런 연결 구조를 Promise Chaning이라 한다.

<br>

### Promise.all

```jsx
const f1 = () => {
	return new Promise((res, rej) => {
		setTimeout(() => {
			res("1번 주문 완료");
		},1000);
	});
}

const f2 = (message) => {
	console.log(message);
	return new Promise((res, rej) => {
		setTimeout(() => {
			res("2번 주문 완료");
		},3000);
	});
}

const f1 = (message) => {
	console.log(message);
	return new Promise((res, rej) => {
		setTimeout(() => {
			res("3번 주문 완료");
		},2000);
	});
}

// Promise.all 사용
Promise.all([f1(), f2(), f3()]) // 프로미스 객체의 result로 이뤄진 배열 인자로 받음
.then((res) => {
	console.log(res);
}); // 위의 f1, f2, f3 작업이 모두 완료되면 then 작업이 실행된다.
```

아까 위 작업을 실행하면, 모든 Promise가 끝날때까지 6초가 걸린다.

세 가지 작업이 동시에 진행되고 있다고 가정하면 어떨까? 이러면 가장 오래걸리는 작업이 3초이므로 3초에 모든 작업이 끝날 것이다.

그걸 처리하기 위해 Promise.all을 사용할 수 있다.

Promise.all은 인자로 프로미스 객체의 result로 이뤄진 배열을 받는다.

이때 Promise.all의 result는 이 result 배열이 된다.

이렇게 Promise.all은 한꺼번에 함수들을 실행시키고, 모든 작업이 끝나면 then 작업을 실행한다.

**대신 Promise.all 사용시 중간에 하나라도 에러가 나면 그대로 터져버린다.**

**위의 promise 구문에선 2번이 오류가 나더라도 1번은 보여준 것과 대조된다.**

모든 요소 중 하나라도 누락되면 보여주면 안되는 경우 사용하면 된다.

<br>

### Promise.race()

```jsx
const f1 = () => {
	return new Promise((res, rej) => {
		setTimeout(() => {
			res("1번 주문 완료");
		},1000);
	});
}

const f2 = (message) => {
	console.log(message);
	return new Promise((res, rej) => {
		setTimeout(() => {
			res("2번 주문 완료");
		},3000);
	});
}

const f1 = (message) => {
	console.log(message);
	return new Promise((res, rej) => {
		setTimeout(() => {
			res("3번 주문 완료");
		},2000);
	});
}

// Promise.race 사용
Promise.race([f1(), f2(), f3()]) // 프로미스 객체의 result로 이뤄진 배열 인자로 받음
.then((res) => {
	console.log(res);
}); // 위의 f1, f2, f3 작업 중 하나라도 완료되면 then 작업이 실행된다. 나머지 작업을 끝내버린다.
```

기본적으로 Promise.all과 사용법은 동일하다. 

차이점은 Promise.all은 모든 작업이 다 완료될 때까지 기다리지만,

Promise.race는 하나라도 완료되면 나머지 작업들을 끝내버리고 then을 실행한다.

용량이 큰 이미지를 로딩하는데, 그 중 하나라도 완료되면 그걸 보여줄 때 사용할 수 있다.
