# ApryxScript
Apryx Scripting Language

Welcome to a short description of ApryxScript. A ~~typesafe~~ Javascript inspired language that has been in development for quite a while now!

ApryxScript looks a lot like Javascript, the hello world program looks like this:
```
console.log("Hello World!")
```

As you can see, its very straight forward C like. You can declare variables like this:
```
var variableOne = 1
```

Note, there are not semi colons. You can still add them if you want, but they are not needed.
For example
```
main() main()

main();main();
```
The two statements do exactly the same.

Some other examples that hopefully speak for themself (the readme file will become better later :) )

```
function main(){
  console.log("This is the main function")
}
main()
```


Currently classes are also implemented
```
class Vector{
	var x = 0
	var y = 0
	var z = 0
	
	function toString(){...}
}

var v = Vector()
console.log(v.toString())

```


~~Currently I'm gonna try to make this typesafe, because i know i can.~~
Dropped the plan to make it typesafe, i guess.

^Basically it's typescript
