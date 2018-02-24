# Basic Concepts

If you've already had experience with programming languages, you can skip this whole article.

What do I mean? If the following sounds familiar:

- variables and data types
- functions
- control flow

Then feel free to go on to the next topic. If anything there feels odd or unfamiliar, read on.

## What is a ...

### Program

![This is a program, right?](images/thisisaprogramright.png)

This is a program, right?

Right?

Sorry, couldn't help myself.

...

Anyways ...

A program, according to Wikipedia is:

> a collection of instructions that performs a specific task when executed by a computer. A computer requires programs to function.

That's a great definition. However 'instructions' can be a be of an abstract term? We're used to seeing instructions when we put together IKEA furniture, when following a recipie, or following GPS directions. But for a computer, it's a _little_ different. Whenever you run a program, it's performing a series of steps:

- send an email to a recepient.
- view a web page
- play a game

However, each one of the previous examples can be further refined. For example, sending an email consists of:

- Convert the 'email' you created into something that formatted for transmission to a destination.
- if there are any attachments, those have to be converted into something that can be sent via email.
- If the email address is improperly formatted, don't send it
- The email bounced for some reason, we have to deal with that.

And each one of those steps can be even further broken down:

- Convert the 'email' you created into something that formatted for transmission to a destination.
  - Create an email header that has the correct routing information.
  - Take the subject line of the email and add that to the email header.
  - Take the body of the text and add it to a buffer that is attached to the email header.

And even those steps can be broken down. At it's lowest level, the lowest level would be assembly. Here's an example (this is from the GCC 7.3 x86-64 bit compiler, for those wondering):

``` asm
  push rbp
  mov rbp, rsp
  movss xmm0, DWORD PTR .LC0[rip]
  pop rbp
  ret
.LC0:
  .long 1078523331
```

It actually gets more atomic than that, as that get converted into a series of 0's and 1's. Let's not follow that trope, as nobody actually reads that in real life. However, it really wasn't that long ago when programs were written using that syntax. As early as 2003, that was a common programming language for writing GPU shaders; programs that are actually run on your video card to render graphics. As a programmer, there's something to be said for being able to read assembly, especially in games programming. Rest easy, we won't be covering assembly as that is well outside the scope of these articles.

## The most minimal C++ program ever

``` C++
// This is the simplest program you will ever see in C++.
int main()
{
    return 0;
}
```

[Try it online](https://repl.it/@Nuclearfossil/MinimalCProgram)

When I was a child, I was taught in Sunday School that the shortest sentence in the English language was "Jesus Wept". While that may not be technically true, there is a bit of an analogy there. By definition, a complete sentence has to have at least a subject and a main verb to state a complete thought. So, we could also argue that "I do" could also be considered the shortest sentence.

How does that relate to a program? Simply put, a complete _program_ has to have an 'entry point', a 'body' and a result. What I've illustrated above does just exactly that. I think that this is a great place to start, so let's break that bit of code down, line by line.

The first line in the example illustrates the concept of a 'comment'. This is a bit of code that is never put into the executable. It's there for documentation purposes: Future me may not be as 'clever', or in the same headspace as Present-day me and might need some reminders as to what he's thinking about. Comments are tremendously useful and you'll see them littered through the upcoming articles. If you're inspecting other people's code, hopefully they've added comments as well to guide you in understanding their thought process when they wrote their code.

The second line is our entry point into our program. In C++, all programs start with a _function_ called main. Think of a function like a command that you can get your program to do.  We've all given a dog a command to 'sit' at some point in time, right? Well, this is the same kind of thing. We're asking the program to perform a specific command (or function ... or even instruction, but that would be pushing it).

The function `main` then has a body - that's the stuff between the curly braces (the `{` and `}` symbols). This defines the 'scope' of the function; the start and end of `calcPi`.  We're going to use the word _scope_ again later. At this point, think of it as the start and end of a block of code.

Inside that body of code, we only have a `return 0;` _statement_. This tells the function that we're finished doing stuff in that block of code and that the result of the function is the number `0`. Each statement in C/C++ must end with that `;`.

That's kind of a boring bit of code. It doesn't actually do anything. And as much as it pains me to do this, I'm going to follow the tried and true, "everyone does it so why don't I do it too" example.

``` C++
// The old tried and true example
#include <stdio.h>
int main()
{
    printf("Greetings, Program ...");
    return 0;
}
```

[You can try this out online here](https://repl.it/@Nuclearfossil/GreetingsProgram)

In this example, I'm introducting a 'library function', `printf`. You see, C/C++ doesn't actually have a lot of inherent functionality; it's actually fairly bare-bones. To get additional functionality, developers expose new functions through libraries. We include those libraries using the `#include` directive. In this case, we've modified the code to include the `stdio.h` library. What that directive is actually doing is going to the file system (the hard disk/network drive) and looking for a file called `stdio.h` and 'including' it into this file.

This is the standard mechanism in C++ to expose functions to your program. We'll dig into libraries and how to organize your code later.

The `printf` function takes one 'argument'. In this case it's a _string_; anything wrapped in a double quote `"` symbol is considered by C++ to be a string.

If you run that bit of code, you get the following output:

```
gcc version 4.6.3
   
Greetings, Program ...   
```

And that, in a nutshell, is your very first program. Neat, hunh?

And for this article, I think I'm going to stop it there. We're going to cover a great deal of ground over the next few articles, so I want to try and keep it bite-sized, rather than overwhelm.

You can head back to the main article page [here]{README.md) and continue on with the next article.

# Reference Material
- For the keener: Technical reference for the language online: [C++ Reference](http://en.cppreference.com/w/)
- Another Interactive C++ shell: [C++ shell](http://cpp.sh/)
- Yet another interactive shell (code. compile. run. debug): [OnlineGDB](https://www.onlinegdb.com/online_c++_compiler)
