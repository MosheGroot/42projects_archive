# ft_containers project

  Rewrite some of STL containers: vector, stack, map and set. 

  Map and set are based on own implementation of Red-black tree.

  Languare: C++

## Result
* Work with template classes and functions
* SFINAE mechanism usage
* Own implementation of `RB_tree` with my own article about ["deletion in Red-black tree"](https://habr.com/ru/post/573502/)
* Unit-tests for every container
* Little benchmark

## Project structure

```
|- tests/           (unit tests and benchmark for containers)
|
|- data_structs/    (some data structures, includes RB_Tree)
|\
||- ft_pairs.hpp
||- ft_rb_tree.hpp
|
|- utils/           (SFINAE mechanisms, iterators' tags, lexicographical compare and other)
|
|- ft_vector.hpp    (containers implementation)
|- ft_stack.hpp
|- ft_map.hpp
|- ft_set.hpp

```

## Usage

```
make
```
Compiles unit-tests programm. Run `test` and use `<enter>` to go to the next test.

```
make benchmark
```
Compiles two benchmark programs: `banch_std` and `banch_ft` -- and executes them with `time` utility.

```
make [clean / fclean / re]
```
Standart rules for cleaning from \*.o files, removing binaries, and recompiling the program.
