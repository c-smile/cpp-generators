# cpp-generators
Generators/corroutines for C++

## Introduction

Iterators in C++ is a good but not a perfect abstraction. The concept of `foreach()` (D, Python, Ruby, etc.) appears as a more generic solution. At least, `foreach()` does not require an artificial `iterator::end()` to be defined for the collection.

The `foreach()` abstraction can be imagined as some function/object that returns the next value of collection/sequence each time it gets invoked. Such functions are known as generators.

Generators are functional objects that persist internal state between invocations thus they can be considered as corroutines too. 

## Background

This version of $generator's for C++ is based on the bright [idea of Simon Tatham - "coroutines in C"](http://www.chiark.greenend.org.uk/~sgtatham/coroutines.html). In particular, on the idea of using `switch`/`case` for the implementation. 

## Declaring a Generator

To declare a generator, you will use `$generator`, `$yield`, `$emit`, and `$stop` "keywords" that are macro definitions in fact.

Here is a typical implementation of a generator. In this particular example our generator will emit numbers from 10 to 1 in descending order:

```cpp
include "generator.hpp"

$generator(descent)
{
   // place for all variables used in the generator
   int i; // our counter

   // place the constructor of our generator, e.g. 
   // descent(int minv, int maxv) {...}
   
   // from $emit to $stop is a body of our generator:
    
   $emit(int) // will emit int values. Start of body of the generator.

      for (i = 10; i > 0; --i)
         $yield(i); // a.k.a. yield in Python,
                    // returns next number in [1..10], reversed.
   $stop; // stop, end of sequence. End of body of the generator.
};
```

Having such a descending generator declared, we will use it as:

```cpp
int main(int argc, char* argv[])
{
  descent gen;
  for(int n; gen(n);) // "get next" generator invocation
    printf("next number is %d\n", n);
  return 0;
}
```

The `gen(n)` there is in fact an invocation of the `bool operator()(int& v)` method defined "under the hood" of our generator object. It returns `true` if the parameter `v` was set, and `false` if our generator cannot provide more elements - was stopped.

## Limitations of the Approach

`$yield` cannot be placed inside a `switch` statement as `$emit()` declares a `switch` by itself.

## License

The generator.hpp is licensed under [The BSD License](https://opensource.org/licenses/bsd-license.php).