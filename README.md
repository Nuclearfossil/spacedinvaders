# Spaced Invaders - A C/C++ Programming Tutorial Series

## Rationale

For years I've wanted to put together a tutorial in programming languages that would be appropriate for all ages and disciplines. It's bothered me that there haven't been any 'accessible' tutorials out there; tutorials that go from zero to competency in a way that _everyone_ can understand. That is a difficult problem to try and get right.

So, I thought I'd throw my hat into the ring on this one.

What we're going to build over the course of this series is a functional (not necessarily complete) Space Invaders clone. I chose this because:

<ol type="a">
 <li>I'm a game developer by day. Write what you know.</li>
 <li>There's a butt load of source material that people can reference.</li>
 <li>Gameplay logic is trivial.</li>
 <li>It allows, at an incredibly low fidelity, us to cover a great deal of ground.</li>
</ol>

## The Method

I'm going to be using a mix of technologies for this.

- Visual Studio Community 2017
  - This is what's caused an IDE - an Integrated Development Environment.
  - This is where we can edit the 'code' that creates a program.
  - We also use it to 'build' the program.
  - And, we also use it to debug the program when things go sideways.
- C++ Shell
  - This is a web-based C/C++ compiler.
  - It's very simple to use and allows us to quickly try out ideas (and try code snippets).
- Allegro
  - A library that covers the majority of our media needs (drawing lines, images, text).
  - Also is a nice utility wrapper for operating system functionality.
- GitHub
  - You're here.
  - Github is a place to store code (and share it).
  - Also can be used to document code.
- Markdown
  - You won't need this, but I use Markdown as my article formatting language.
- Krita and The Gimp
  - Image editing

I'm also going to be writing in a very informal manner. I write like I talk. I'll be doing a lot of edits as I build out this documentation, so you may want to re-read sections (I'll call them out as I edit them).

## So why not just grab a book/take a class?

Well ... arguably you should. One web article can't replace a university education. Or a degree from a college. These articles aren't meant to replace formal classes and other reference material. I personally encourage researching and experimenting as much as possible any programming language that you can find. The intent of these articles is to act as a supplement to other materials. I will try not to gloss over topics, but if there are better resources for explaining the material, I will be (gladly) referring to them.

That said, I do find that there are some ideas, concepts and techniques that are either glossed over, skipped entirely, or wrong, in a great deal of materials out there (and in many universities, in my experience). My goal in these articles is to cover the fundamentals, as I see them and try to convey them in a fashion that is consumable to the reader, given only a mildly passing curiosity in programming. Hopefully this instills a sense of curiosity about programming and the C/C++ language that you may not have had in the past.

The other aspect of this is that I want anyone who's reading this to feel engaged. If there are any questions, or suggestions, I'd like to be able to accommodate them as much as possible. For now, I'm going to try and answer all questions through twitter - just reply to this tweet (until I find something better): https://twitter.com/nuclearfossil/status/967220497569083392

## Syllabus

I'll be building this out as I go:

- Introduction (You're currently here)
- [Basic Concepts](00.basicconcepts.md)
- [Function Primer](01.functionprimer.md)
- [More on Functions](01.morewithfunctions.md)
- [Program Flow Control](01.programflowcontrol.md)
- [Pointers](01.pointers.md)
- [Something you can compile on your own machine](02.firststeps.md)
- [Arrays](02.arrays.md)
- [Graphics Introduction](03.graphics.md)
- [Simple Animation](03.simpleanimation.md)

## Related Materials

- [Introduction to Programming for Games by Andrew Simpson](github.com/asimpson2004/ASCII_Invaders)
