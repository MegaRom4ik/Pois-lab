# PPOIS

Laboratory assignments in C++17.

## Lab 1

Two programs: a 3D vector and tic-tac-toe.

- `lab1/vector` — vector length, addition, subtraction, cross product, and other operations.
- `lab1/tictactoe` — a two-player game with a configurable board size and save/load support.
- `lab1/tests` — unit tests.

## Running

Clang, Make, and curl are required.

```sh
make all
./build/vector_cli
./build/tictactoe_cli
```

Run the tests:

```sh
make test
```

Enter a vector as `x1 y1 z1 x2 y2 z2`. In tic-tac-toe, X moves first and row and column
numbers start at 1. Fill an entire row, column, or diagonal to win. Program menus are in Russian.

Lab 1 branch: `feature/lab1-vector-tictactoe`. Lab 2 branch: `feature/lab2-cooking`.

[Lab 1 assignment](https://github.com/alix-zzh/ppois-course/blob/master/ru/lab1.md)

## Lab 2

A cooking workshop with recipes, ingredient storage, purchasing, and cooking.
Use the `feature/lab2-cooking` branch for this assignment.

```sh
make lab2
./build/cooking_cli
```

Class and operation descriptions: [lab2/README.md](lab2/README.md).

## Documentation

Doxygen is needed to generate the documentation:

```sh
make docs
```

Open `build/docs/html/index.html` for Lab 1 or, on the Lab 2 branch, `build/cooking-docs/html/index.html`
in a browser. The generated HTML can be read without installing Doxygen.
