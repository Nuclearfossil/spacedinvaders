# Basic Concepts

If you've already had experience with programming languages, you can skip this whole article.

What do I mean? If the following sounds familiar:

- variables and data types
- functions
- control flow

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
// Return a constant representing the value of Pi
float calcPi() 
{
    return 3.14f;
}
```

Even if you've never written a line of code before, five bucks says you have have a pretty good idea what the intent of that code is.

However, this is a great place to start - so let's break that bit of code down, line by line.

We see the first line in the example illustrates the concept of a 'comment'. This is a bit of code that will NEVER get compiled - it is actually removed from the executable. But it's there for documentation purposes (Future Ash may not be as smart, or in the same headspace as Present Ash, and might need some reminders as to what he's thinking about). Comments are tremendously usefull and you'll see them littered through the upcoming articles.

Next up, what we are doing is declaring a function, called `calcPi`. What's a function? Think of it like a command that you can get your program to do.  We've all given a dog a command to 'sit' at some point in time, right? Well, this is the same kind of thing. We're asking the program to perform a specific command (or function ... or even instruction, but that would be pushing it).

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

What else can we do with formatting specifiers? Well, we can shorten the length of that float (to 2 decimal places), enforce numbers to have a +/- sign, numerical padding (adding 0's to the left of the whole number part of a float) as well as a bunc of other things.

The `\n` in that formatting string represents a newline; it functionally adds a carriage return into the console.

``` C++
    printf("variable: pi: %f\n", pi);
```

I think you can see what this is doing.

### Output

When you actually execute the code, you end up with the following output:

``` bash
variable: doubled7: 14.000000
variable: pi: 3.140000
```

## Program Flow Control

The previous was a pretty simple example, but I think it was enough to cover the absolute basics. Now let's try something a bit more complex. Following in line with some math-oriented functions, let's build a function that calculates a number to a specified power.

Just to re-iterate:
> 5<sup>3</sup> = 5 x 5 x 5

How can we generalize that? Using loops!

### Loops - while

A while loop can execute a bit of code over and over again until a certain condition is met. Here's a bit of an example:

``` C++
int i = 0;
int max = 7;

while (i < max)
{
    // do something
    i = i + 2;
}
```

Breaking down the `while` statment, we see that it only has a conditional bit; we loop _while_ the variable `i` is less than `max`. Inside the body of the while loop, we do something, and then modify the value of `i`.

Note that we don't just have to modify the left hand side of the equation. We could just have easily modified the right hand side. However, common convention is that we usually don't.

#### Sidebar - Conditionals?

Wait ... what's this about _conditionals_? What's happening there with that `i < max` bit of code in the `while` line?

Conditionals are essentially tests. Does something evaluate to 'true' or 'false'?

Computers tend to represent 'true' and 'false' as a bit - a 1 or a 0, an on or off. So what the conditional here is testing is: is the current value of `i` less than (the `<` operator) the current value of `max`. While that conditional is true, we continue to loop. Once that conditional evaluates to false, we stop looping an proceed to the code after the body of the loop (the next line after the loops `}`).

Also, a 'true' or a 'false' is also represented as a data type called a boolean (`bool` keyword in C/C++).

Get used to writing conditional statements. Programming is all about writing conditional statements. This will become evident shortly.

### Loops - do-while

There's also a variation on a `while` loop, called a `do-while`.  It looks like this:

``` C++
int i = 0;
int max = 7;

do
{
    // do something
    i = i + 2;
} while (i < max);
```

There is really only one difference between a `while` and `do-while` loop: a `do-while` loop is guaranteed to execute the body of the loop once. You aren't guaranteed that with a regular `while` loop.

Consider the following:

``` C++
int i = 10;
int max = 7;

do
{
    printf("I'm in the do-while loop\n");
    i = i + 2;
} while (i < max);

while (i < max)
{
    printf("I'm in the while loop\n");
    i = i + 2;
}
```

This generates the following result:

``` bash
I'm in the do-while loop
```

[example here](http://cpp.sh/3vkks)

### Loops - for

Another type of loop is called a for loop, defined in C/C++ like this:

``` C++
for (int i = 0; i < 5; i++)
{
    // do stuff
}
```

`for` is another C/C++ keyword that indicates that we are going to loop over a block of code (what's contained in the curly braces `{` `}`) until a certain condition is met.

The formal syntax for a for loop looks like this:

`for ( <initialization part>; <conditional part>; <post loop part> )`

The `initialization part` is just exactly that - it allows us to create some temporary variable to use as a counter. In this example, we create an integer variable (`int` is yet another data type - it holds a whole number) that we initialize with a value of 0.

The `conditional part` is evaluated at the start and subsequent iteration of the loop. We only iterate through the loop if it evaluates to true. So we only enter the loop while the value of `i` is less than 5.

The `post loop part` happens at the end of the loop. In this case, we use the `++` operator to increment the variable `i` by 1. The `++` operator is built in to C/C++. So is `--` which subtracts 1 from a variable.

A for loop can be thought of exactly like a `while` loop with the following syntax:

``` C++
<initialization part>
while (<conditional part>)
{
    // do stuff
    <post loop part>
}
```

## Using Loop flow control

We now come to the point where we figure out how to use those loops to generate a 'raise to the power of' function. Remember this?
> 5<sup>3</sup> = 5 x 5 x 5

Can you see how we're looping there? Kinda awesome, right? Well, we can code that up fairly easily:

``` C++
// Calculating an exponent
#include <stdio.h>

float calcPow(float base, float exponent)
{
    float result = base;
    for (int index = 0; index < (exponent - 1); index++)
    {
        result *= base;
    }

    return result;
}

int main()
{
    printf("5 to the power of 3 is: %f\n", calcPow(5, 3));
}
```

[calcPow example here](http://cpp.sh/9tl6x)

I think everything there is fairly obvious at this point. Except for that for loop. Take a look:

`for (int index = 0; index < (exponent - 1); index++)`

Why is our conditional set to `index < (exponent -1)`?

That has to do with how the body of the loop is set up. Look again:

``` C++
float result = base;
for (int index = 0; index < (exponent - 1); index++)
{
    result *= base;
}
```

We've already set `result` to `base` - so we don't have to loop `exponent` times. However, let's imagine what the program is actually doing. Consider the following table:

| iteration | index value |  test  | exponent | result value |
|:---------:|:-----------:|:------:|:--------:|:-----------:|
|1|0|0<3 (True)|3|35.0|
|2|1|1<3 (True)|3|325.0|
|3|2|2<3 (True)|3|3125.0|
|4|3|3<3 (False)|3|-|

These kinds of tables can be invaluable when debugging what's going on in a bit of code. We're essentially walking through, step by step, what the code is doing and writing down what we expect to see.

Executing this program results in the following:

``` bash
5 to the power of 3 is: 125.000000
```

That's great! Done!

Well, not quite. The exponent can be a positive or negative number. Our `calcPow` function doesn't actually do the right thing:

``` C++
// Calculating an exponent
#include <stdio.h>

float calcPow(float base, float exponent)
{
    float result = base;
    for (int index = 0; index < (exponent - 1); index++)
    {
        result *= base;
    }
    
    return result;
}

int main()
{
    printf("5 to the power of 3 is: %f\n", calcPow(5, 3));
    printf("5 to the power of -3 is: %f\n", calcPow(5, -3));
}
```

``` bash
5 to the power of 3 is: 125.000000
5 to the power of -3 is: 5.000000
```

Can you see what the problem is? Let's bring up that handy table again:

| iteration | index value |  test  | exponent | result value |
|:---------:|:-----------:|:------:|:--------:|:-----------:|
|1|0|0<-3 (False)|-3|-|

Also, the logic behind calculating a negative exponent is wrong. A negative exponent is calculated like so:

> 5<sup>-3</sup> = 1 / (5 x 5 x 5)

We're almost there. We just need to get our code to do the right thing. We need some way to have our code do one thing if we have a positive exponent, and something else if the exponent is negative.

For that, we need a branching statement. `if/else` to our rescue!

## if else Selection Statements

What an `if` statment does is perform some calculations 'if' a conditional statement is true. You can also add an `else` to deal with the false part.  Here's what it looks like:

``` C++
if (<conditional part>)
{
    // Do something here
}
else // This is optional!
{
    // Do this part if <conditional part> evaluates to false
}
```

Let's put that to use in our power calcuation code

``` C++
// Calculating an exponent
#include <stdio.h>

float calcPow(float base, float exponent)
{
    int iterations = exponent;
    if (exponent < 0)
    {
        iterations *= -1.0f;
    }

    float result = base;
    for (int index = 0; index < (iterations - 1); index++)
    {
        result *= base;
    }

    if (exponent < 0)
    {
        result = 1.0f / result;
    }
    return result;
}

int main()
{
    printf("5 to the power of 3 is: %f\n", calcPow(5, 3));
    printf("5 to the power of -3 is: %f\n", calcPow(5, -3));
}

```

``` bash
5 to the power of 3 is: 125.000000
5 to the power of -3 is: 0.008000 
```

[proper negative exponent handling](http://cpp.sh/5u56h)

A bit more to unpack here.

``` C++
    int iterations = exponent;  // iterations is a temp variable for how many times we should loop
    if (exponent < 0)           // if exponent is less than 0
    {
        iterations *= -1.0f;    // we negate it, making it a positive number.
    }
```

``` C++
    // This bit stays the same.
    float result = base;
    for (int index = 0; index < (iterations - 1); index++)
    {
        result *= base;
    }
```

``` C++
    if (exponent < 0)           // if the exponent is less than 0
    {
        result = 1.0f / result; // the actual value is 1 / (5 x 5 x 5)
    }
```

``` C++
    // This also stays the same
    return result;
}
```

### Exercise for you, dear reader

I've purposely left a bug in this bit of code. It's actually a really big bug. I'd like to see if you can find it.
In my next article, I'll post the bug and the solution for it.

As well, can you think of any ways to simplify this program? Without using any additional libraries?

Can you also write a version of this program that works with integer numbers?

# Wrap up

And that is a crazy short introduction to the C/C++ language. This gives us a running start. In my next example, we're going to start implemeting Spaced Invaders for real, using Visual Studio 2017 community.

But I'll also come back to C++ shell for quick little snippets like these. I find this to be an incredibly usefull tool for slamming out test code, without having to spin up a new Visual Studio project.

So, until next time, play around with the C++ shell, take a look at the Visual Studio solution that exists in this Github repo and experiment!

# Reference Material
- Technical reference for the language online: [C++ Reference](http://en.cppreference.com/w/)
- What a float actually looks like: [Single-precision floating point format](https://en.wikipedia.org/wiki/Single-precision_floating-point_format)
- Interactive C++ shell: [C++ shell](http://cpp.sh/)
- An alternative (code. compile. run. debug): [OnlineGDB](https://www.onlinegdb.com/online_c++_compiler)

