# Basic Concepts

If you've already had experience with programming languages, you can skip this whole article.

What do I mean? If the following sounds familiar:

- variables and data types
- control flow
- functions

Then feel free to go on to the next topic. If anything there feels odd or unfamiliar, read on.

## What is a ...

### Program

I was tempted to make a very esoteric 'Tron' joke here, but I suspect you, Dear Reader, may only have a passing acquaintance with that bit of film history. Oh, tis the sad state of the world today /irony

Anyways ...

A program, according to Wikipedia is:

> a collection of instructions that performs a specific task when executed by a computer. A computer requires programs to function.

That's a great definition, if I've ever heard one. This begs us to question, what do we mean by 'instructions'. At it's lowest level, that's assembly. Here's an example (this is from the GCC 7.3 x86-64 bit compiler):

``` asm
  push rbp
  mov rbp, rsp
  movss xmm0, DWORD PTR .LC0[rip]
  pop rbp
  ret
.LC0:
  .long 1078523331
```

Back in the day, that's how you wrote a computer program. And there's something to be said for being able to read that (especially in games programming). But that is well outside the scope of these articles.

That example is incredibly hard to read. And it's also incredibly hard to write. Considering all that program does is calculate Pi. And by 'calculate', I mean it simply gives us the value `3.14`.

Here's what that code actually looks like, in C:

``` C++
float calcPi() 
{
    return 3.14f;
}
```

Even if you've never written a line of code before, five bucks says you have have a pretty good idea what the intent of that code is.

However, this is a great place to start - so let's break that bit of code down, line by line.

First off, what we are doing is declaring a function, called `calcPi`. What's a function? Think of it like a command that you can get your program to do.  We've all given a dog a command to 'sit' at some point in time, right? Well, this is the same kind of thing. We're asking the program to perform a specific command (or function ... or even instruction, but that would be pushing it).

The function `calcPi` then has a body - that's the stuff between the curly braces (the `{` and `}` symbols). This defines the 'scope' of the function; the start and end of `calcPi`.  We're going to use the word _scope_ again later. But at this point, thinking of it as the start and end of a block of code is a great way to think about it.

So, we have a function called `calcPi`. We also have `float`, `return` and `3.14f`.  What do each of those mean in this context?

Well, `float` and `return` are C _keywords_. The language specification defines a number of keywords. I'll list them later, but for now, understand the C reserves a number of words for specific usage.

`float` is what's called a 'data type' (also referred to as just a 'type'). It defines the type of data that can be associate with it. In this case, it represents a single precision floating point value (in math, a 'real' number). Thus a float can be 1.0, 1.5, 1.25, -7.0, 0.0 ... any single precision number. Please be aware that this number isn't infintely precise; it has some fairly stringent limitations as to it's precision.

There are a fair number of data types and I'll introduce them as we go. Once we have a few under our belt, I'll go ahead an list out all the data types.

The `return` part of the body of the function is directly related to that float in the 'function signature'. That function signature states that for the function `calcPi` it returns a floating point value and takes no parameters. Thus the `return` keyword will return back to whatever called this function a value, in this case `3.14 ... f`.

Why the `f` at the end of that number? It represents that the constant value of `3.14` is a floating point number. If we didn't have the `f` on the end, the compiler assumes that the number is a `double` data type (look, our second `type`!). A `double` indicates to the compiler that the amount of memory used to hold that real number is much larger than a `float` - it's twice as big.  But it's a separate type - you could either say `double calcPi()` or `float calcPi()` when you declared the 'return type' of the function.

The `calcPi` function has a return value. But what if I wanted to have the function work on something. For example, I wanted to double a given floating point value? Then I would need to pass in some arguements into the function:

``` C++
float multBy2(float value)
{
    return value * 2.0f;
}
```

The _syntax_ of this function should look similar to the previous example, but with one exception - in between the round brackets (parenthesis) we have `float value`. We've seen the `float` keyword already - it defines a data type, but now we have this additional word, `value`. This is what's called a variable. Much like in math, thinking to your linear algebra classes, a variable does not have a fixed, or constant value.

So, in the case of the `multBy2` function, it returns a `float` but also takes in a single `float` as it's arguement.

It then takes that variable, and multiplies it by 2 (2.0f in this case). And then returns it to whatever invoked this function.

A lot to unpack in just that one line of code. Let's start:

1. C++ defines core mathematical operations as such: +, -, *, /, %, (, ). These are called 'operators'. In order, that's Addition, Subtraction, Multiplication, Division and Parenthesis.
2. Mathematical order of operations is grouped first by parenthesis, then multiplication and division, and finally addition/subtraction. There *is no inherent order of operations* defined in C++; it's not like prefix or postfix math. Any order of operations is inherently defined by the operator iteself. For example, the `+` operator processes from left to right. Source: [cppreference](http://en.cppreference.com/w/cpp/language/eval_order)
3. The `return` keyword will evaluate everything to it's right before returning. Thus we can assume that everything to the right will get computed. However, if you want to resolve any ambiguity, you can place parenthesis around the operations: `return (value * 2.0f);`. This is purely for asthetics as it does nothing to the compiled code. (There is one exception, but I'm not going to cover it here as it's a fairly advanced issue).

How do we invoke a function? Glad you asked. Invoking `multBy2` would look like this:

``` C++
float result = multBy2(7.0f);
```

After that line is executed, we would have a new variable, `result` that would contain a floating point value of `14.0f`.

How would we use that for real? I mean, the entire point of this article is to see a program in action!  We're going to use a web app called [C++ shell](http://cpp.sh/) to muck around with coding.

I've created a simple stub of a program [here](cpp.sh/42me).

``` C++
// Example program
#include <stdio.h>

float calcPi()
{
    return 3.14f;
}

float multBy2(float value)
{
    return value * 2.0f;
}

int main()
{
    float doubled7 = multBy2(7.0f);
    float pi = calcPi();
    
    printf("variable: doubled7: %f\n", doubled7);
    printf("variable: pi: %f\n", pi);
}
```

What's new about this, compared to what we had before? It's an actual program - it compiles and runs. It's just compiled and run 'in the cloud'.

We see in this code the two functions that we talked about earler: `calcPi` and `multBy2`. But now we have this new function called `main`.  What's that?

The C++ compiler will always look for a `main` function defined _somewhere_ in the codebase. It must find one as that is the entry point into our program from the Operating System. At least for a console application. If you're writing a Microsoft windows native app, it's a different beast. I'll talk more about main functions later, but for now, what we have here is 'good enough'.

Let's break down the `main` function line by line:

``` C++
    float doubled7 = multBy2(7.0f);
```

On this line we create a new variable `doubled7` and initialize it with the output of the function `multBy2`. From this point onward, in the main function, we will be able to access the variable `doubled7`.

``` C++
    float pi = calcPi();
```

This is the fundamentally the same as the previous line. We create a new variable `pi` that is generated by the funtion `calcPi`.

``` C++
    printf("variable: doubled7: %f\n", doubled7);
```

Now, `printf` is a function that we haven't defined ourself. It's part of a library. We reference that library with an `#include` directive, which is done on the first line:

``` C++
#include <stdio.h>
```

This is what's called a header file. We'll talk more about them later, but it does allow us to introduce one concept. C++ have very few builtin functions. VERY few. There's a couple of additional steps required to get most external functions linked into a program you create, but that's well and outside of the scope of this article.

As you can see, the `printf` function takes more than one arguement. What you're seeing is a 'string' as well as the float variable.

A string (or in this case, what's called a 'string literal') simply represents a buffer of characters.

What does `printf` do? It prints a formatted string to the console. What does that mean? Well, simply put, there are a set of formatting specifiers that you can encode into the string that will allow you to do in-place substitution of the value of a variable into the string.

For example, in the example program, we have the output string (what's printed to the console) looking like this:
`variable: doubled7: 14.000000`

The `\n` in that formatting string represents a newline; it functionally adds a carriage return into the console.

``` C++
    printf("variable: pi: %f\n", pi);
```

I think you can see what this is doing.


## Output

When you actually execute the code, you end up with the following output:

``` bash
variable: doubled7: 14.000000
variable: pi: 3.140000
```
