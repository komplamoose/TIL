# 자바스크립트 : setTimeout / setInterval

---

- `setTimeout` : 일정 시간이 지난 후 함수 실행
- `setInterval` : 일정시간 간격으로 함수를 반복

이 함수들은 비동기적으로 동작한다. 

### setTimeout()

```jsx
function fn(){
	console.log(3);
}

setTimeout(fn, 3000);

setTimeout(function(){
	console.log(3);
},3000);
```

`setTimeout()`은 2개의 인자를 받는다.

첫 번째 인자는 일정 시간 뒤 실행할 함수 그 자체이고,

두 번째 인자는 일정 시간이다. 1000은 1초를 의미한다.

<br>

```jsx
function showName(name){
	console.log(name);
}

setTimeout(showName, 3000, 'Mike')
```

함수에 파라미터가 필요하다면, 시간 뒤에 추가해준다.

<br>

### clearTimeout()

`setTimeout()`은 실행시 time id를 반환한다.

`clearTimeout()`은 time id를 받아. 실행되기로 한 예약을 취소한다.

<br>

### setInterval()

```jsx
function showName(name){
	console.log(name);
}

const tId = setInterval(showName, 3000, 'Mike');
```

`setTimeout`과 달리, 3초마다 함수를 실행한다.

중단하려면 `clearInterval()`을 실행하면 된다.

<br>

### delay === 3?

```jsx
setTimeout(function() {
	console.log(2)
},0);

console.log(1); // 얘가 먼저 찍힘.
```

주의 사항이 있다. delay time을 0으로 두더라도, 바로 실행되지 않는다.

이는 현재 실행중인 스크립트가 종료된 이후 스케줄링 함수가 실행되기 때문이다.

또한 기본적으로 브라우저는 4ms의 대기시간이 있다.

0이라고 delay를 적어도, 사실상 4ms를 적은 것과 마찬가지.

또한 여기엔 자바스크립트의 비동기적인 작동 구조가 함께 존재한다. 이후 비동기 파트에서 다룬다.

<br>

### 예제

```jsx
let num = 0;

function showTime() {
	console.log(`접속한지 ${num++}초가 지났습니다.`);
	if (num > 5) clearInterval(tId); // 5초 이후 반복 중단
}

const tId = setInterval(showTime, 1000);

```
