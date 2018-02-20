# Your first real program

## Summary

In this article, we move from web-based C++ tools, to something you can run on your own machine, using Visual Studio 2017.

In order to help speed up your ability to work with the codebase, I've created a Visual Studio 2017 project template you can work with. It's located in the `templates` folder in this repo. It's called `SpacedInvadersTemplate.zip`.

In order to use it, you'll need to copy it into your `Documents\Visual Studio 2017\Templates\ProjectTemplates` folder. If you have Visual Studio already running, you'll need to restart the IDE (not your computer).

From that point on, if you want to create a new project to work from, all you have to do is select the template and it will automatically create a starter project for you:

![What the new project dialog should now look like](images/newprojecttemplate.png)

This is just a simpler way to create new projects that are going to follow a standard format. That format includes having the appropriate libraries ready to go, paths set up and a fair bit of boilerplate code inserted for you already.

The template is based off the `initialtemplate` project in the included solution `spacedinvaders`. Go ahead and open that solution in Visual Studio 2017.

Here's what we end up with, when we run the program:

![The template executable in action](images/initialtemplate.gif)

So, how do we get there from here? There's actually a fair bit of ground to cover, and we'll introduce a few more C/C++ concpets along the way.

## The Executable

We're going to continue with our previous examples by creating a windows console application. It's going to have the standard `main` entry point; there won't be any OS specific code in our example.

However, in order to do that, we need to use a 3rd party library called [Allegro](http://liballeg.org/). Our project already has a number of features enabled, but eventually we'll talk about that (way down the line in our article series). Those features will be enabled through a series of functions. And, much like our previous example of using `printf`, we are going to need to include some headers in order for our program to know how to access them.

We therefore need to include some header files:

``` C++
// spacedinvaders.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
```

Our first include, `stdafx.h` is part of what Microsoft calls a 'precompiled header' - it's nothing more than a caching system to increase build times. For now it's kind of irrelevant, so we can ignore it. NB: I may remove this as part of the template to increase the clarity of the article.

Next up, we include `stdio.h`. We don't currently need it for our executable, it probably should be removed as it will increase build times, but I _may_ need it eventually. So I like to have it on hand.

The next four includes actually are used for Allegro features. In order, they are: the core Allegro system, any image manipulation functions, rendering primitives and text rendering. Like `stdio.h`, not all are used, but I find it useful to have they preset as part of the template.

One thing you'll probably notice is that the first include uses quotation marks around `stdafx.h` and the later ones all use angled brackets (`<` and `>`). This is purely for defining where the compiler looks for the header files. Quotation marks indicates that you should look relative to the current file. Angled braces indicates that you should use the 'project defined include paths' that you can set up in the project options (or part of the default compiler/solution setup).

Later we'll be creating our own header files, so we'll end up using quotation marks. (or will we ...)

Next up we have something called 'Forward Declarations`. Here's something about C/C++ - you can use something until you declare it. You have to define variable before you use them, right? Well, you have to do the same thing with functions. Thus:

``` C++
// Forward Declarations
void Setup();
void Teardown();
```

Is just telling the compiler that 'Hey, you know, I'm going to tell you that I have these functions. I'm not going to define the body of these functions just yet, but they're coming up ... eventually".

See, what happens is that when you actually build your program, you run through a couple of steps. First up, the 'compiler' will go through your code and compile all the files with the `cpp` extension (or `cc`, or `c` depeding on ... things). Compiling creates a set of `.obj` files; object files which are files that have been converted into ... almost ... something you can run. We then go through another step, a 'link' step, which then takes all the object files (the `.obj` files) and any libraries that we are looking to use, like Allegro, and inserts functions into the final exectuable.

Go back to the last example. When the compiler creates an exe that can use the `printf` function, the code that _is_ the printf instructions is actually inserted into the executable. That's done through the link step.

And all those 'Forward Declarations'? They can be put into a header file.  We'll revisit that in the not too distant future.

However, if you scroll to the bottom of the `main.cpp` file, youll see that we have the `Setup` and `Teardown` functions actually implemented.

## Global variables and variable scope

We then have a section that defines some 'Global Variables'. That's a bit of a misnomer as they aren't actually truly 'global' - they're what's called 'file global'. More on that shortly. However, what we have looks like this:

``` C++
// Global definitions
ALLEGRO_DISPLAY* gDisplay = nullptr;
ALLEGRO_FONT* gFont = nullptr;
ALLEGRO_EVENT_QUEUE* gEventQueue = nullptr;
```

Those ... kinda look like variables. But `ALLEGRO_DISPLAY`, `ALLEGRO_FONT` and `ALLEGRO_EVENT_QUEUE` don't look like the types we've seen already, like `float` or `int`.  What gives?

Well, they actually are types. Just not native types like `float` and `int`.  You don't need to include any special headers to use those types. However it is a _custom type_, that's defined as part of the allegro library, in `#include <allegro5/allegro.h>`. We'll talk about creating our own type very soon, but it's just a hint outside of the scope of this article. We will, however, gladly use them for our own purposes.

But, they're not just a type - they have an asterix at the end: `ALLEGRO_DISPLAY*` ... isn't that a mathematical operator for multiplication?

It sure is. But in C/C++, you'll find that symbols often have different meanings depending on the context.  In this context, it represents a pointer.

OK, so what's a pointer? Wikipedia defines it as:

> In computer science, a pointer is a programming language object, whose value refers to (or "points to") another value stored elsewhere in the computer memory using its memory address. A pointer references a location in memory, and obtaining the value stored at that location is known as dereferencing the pointer. As an analogy, a page number in a book's index could be considered a pointer to the corresponding page; dereferencing such a pointer would be done by flipping to the page with the given page number and reading the text found on the indexed page.

So, what's stored in a pointer variable is a memory address. A pointer, depending on the operating system, can be of different sizes. You know how you can get a 32 or 64 bit version of windows? Yep, that is how big a pointer is (32 bits for a 32 bit OS, 64 in a 64 bit os).

That's an incredibly naive way to describe the difference between 32 and 64 bit operating systems. But at it's core, it's not wrong. It's just that there's a lot more going on than just that. In a later article, I'll talk more about 32 and 64 bit pointers and address spaces.

So what, then, does a pointer actually mean? Well, it points to a bit of memory.

Let's just over to the C++ shell to illustrate how pointers work (in a rudimentary fashion).

``` C++
// Example program
#include <stdio.h>

// File Global variables
int gA;             // a file global integer variable
int gB;             // a file global integer variable
int* gPointer;      // a file global integer pointer


int main()
{
  gA = 5;
  gB = 10;

  gPointer = &gA;

  printf("gA: %d\n", gA);
  printf("gB: %d\n", gB);
  printf("gPointer: %p\n", gPointer);
  printf("Value gPointer points to: %d\n", *gPointer);

  gPointer = &gB;
  printf("gPointer: %p\n", gPointer);
  printf("Value gPointer points to: %d\n", *gPointer);

  *gPointer = 15;

  printf("gA: %d\n", gA);
  printf("gB: %d\n", gB);
  printf("gPointer: %p\n", gPointer);
  printf("Value gPointer points to: %d\n", *gPointer);
}
```

Results in:
``` bash
gA: 5
gB: 10
gPointer: 0x600b4c
Value gPointer points to: 5
gPointer: 0x600b48
Value gPointer points to: 10
gA: 5
gB: 15
gPointer: 0x600b48
Value gPointer points to: 15
```

[Link to example](http://cpp.sh/86otz)

That is going to need a little bit of unpacking. First off, we have three variables defined:

``` C++
// File Global variables
int gA;             // a file global integer variable
int gB;             // a file global integer variable
int* gPointer;      // a file global integer pointer
```

`gA` and `gB` are just integer variables.

`gPointer` is an integer variable _pointer_. This simply states that this variable will hold the address of a memory location that is an integer. That's it.

Doing something like this:

``` C++
float someVariable;
float* someVariablePointer;
```

Means that `someVariablePointer` will point to a `float` type in memory.

Confused yet? That's OK, because it can be. And it'll get more complex when we talk about 'dynamic memory allocation'. But we aren't going there just yet.

Let's go back to how we declare variables. Looking at how we declared `gA` and `gB`:

``` C++
int gA;             // a file global integer variable
int gB;             // a file global integer variable
```

Each of those two lines creates a variable, in memory. That 'in memory' is kind of a broad term, as computer programs tend to have two types of memory: the stack and the heap.

In the above example, `gA` and `gB` are created on the stack. You don't have to do anyting special to create, or allocate, the space in memory for those variables. The compiler does that for you automatically. But they are created *on the stack*.

This means that the compiler will alocate enough room in memory to hold an integer varialbe ... *on the stack* ... automatically for you. And you can get and put data into it like we've seen already, by using the `=` operator, or just 'using' the variable, like we did with the `printf` function.

However, there are times when you want to store a pointer to a variable. Trust me, you're going to do this a _lot_ in C/C++. So if you want to create a pointer variable, you'll need to know the type, add a `*` after the type name and before the variable, like we did with `int* gPointer`.

As a side note, some coding conventions like to put the `*` symbol next to the type, some conventions like to put it next to the variable. It's totally a personal preference and if you look at some of my code samples in github, you'll see that I'm ... fluid ... in where I put the `*`.

OK, back to the code and the output.

## The Main body of work

Our main is actually quite simple, with a few caveats:

``` C++
int main()
{
    Setup();

    while (true)
    {
        ALLEGRO_EVENT event;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.06);
        bool get_event = al_wait_for_event_until(gEventQueue, &event, &timeout);    
        if (get_event && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        for (int index = 0; index < 25; index++)
        {
            al_put_pixel(rand() % 800, rand() % 600, al_map_rgb(rand() % 255, rand() % 255, rand() % 255));
        }
        al_flip_display();
    }

    Teardown();

    return 0;
}
```

This `main` function contains a call to the `Setup` and `Teardown` functions. We're going to ignore those for the purpose of this article, but we will go into depth on them in the near future.

We then have a while loop that iterates ... forever?

Yep! This is the case. So how does our program ever stop? You can actually exit from any loop by using the `break` instruction, as we see here:

``` C++
ALLEGRO_EVENT event;
ALLEGRO_TIMEOUT timeout;
al_init_timeout(&timeout, 0.06);
bool get_event = al_wait_for_event_until(gEventQueue, &event, &timeout);    
if (get_event && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
{
    break;
}
```

Let's break that down one line at a time.

``` C++
ALLEGRO_EVENT event;
```

What is an `ALLEGRO_EVENT`? It's a way to hook into Allegro's event system. So what's an event? The Operating System can have 'things' happen. Like creating a window, clicking on somewhere in the window, or pressing the `X` on the window to close it. When that happens, Allegro creates an 'event' that we can watch for. I'm really glossing over this for now, but again, we'll dig deeper into it shortly.

``` C++
ALLEGRO_TIMEOUT timeout;
```

``` C++
al_init_timeout(&timeout, 0.06);
```

``` C++
bool get_event = al_wait_for_event_until(gEventQueue, &event, &timeout);    
```

``` C++
if (get_event && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
{
    break;
}
```