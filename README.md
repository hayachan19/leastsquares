# Least-squares function approximator
This is a rewrite of a task I had assigned in order to qualify for retaking Numerical Methods final exam. With the freshman knowledge of C++ and the intimidating stigma of it back then, the original was basically one long list of commands. No functions, no memory management, and variables such as `jtjijtrlinia`. After starting the re-learning of C++, I thought why not to improve this 4 year old abomination of the program.

The task was "Using the least-squares function approximation, determine if points providen belong to a linear or quadriatic function". Program first tries to find the coefficients of the linear function by using LU decomposition to solve the system of linear equations. Then the Gauss-Newton method is used to minimize the geometric fit error, which determines if it lies within specified margin. If so, it's a linear function. If not, the same process is repeated for quadriatic function.

## Usage
The program looks for `file.txt` file, consisting of pairs of numbers representing points in two-dimensional space. Each point is denoted as X (space) Y, one per line. 

```
-2 4.0
-1.009 1
0 0
1 1.999
2.0003 4
```

The order of points doesn't matter.

## So what's "new"?
* Vector/Matrix classes

  Original was operating on STL vectors and nested vectors for matrices. All math was performed directly on indices, leading to loops being everywhere. Loops for adding, loops for multiplying, loops for transposing, even loops for initializing since I didn't know you could fill vectors with value on declaration. Both vector and matrix classes are just wrappers for STL vectors with basic arithmetic and other miscellaneous operations, and while being catered to this project and not being fully featured, it gets the job done.
  
* "Proper" LU decomposition implementation

  Previous one was shamelessly adopted from the Internet, my attempts at rewritting it ended up with basically the same result. LU class offers methods for decomposing, solving and inverting matrices using LU decomposition (without pivot support).

* Generics

  While not so useful for scientific purpose of this project, I've implemented it for all the classes used for completeness.

* Organised code

  Instead of `main()` hosting the entire program, linear and geometric fitting became separate functions, variables have a bit more sensible names, and code *tries* to conform to RAII principle.

## To-Do
* Document the code properly
* Iron out possible inconsistencies
* Implement command line arguments for iteration count, error threshold and input file
* Add LU decomposition variant with pivot matrix
* Add initialization lists for vector and matrix classes

## References
* [Computer Aided Assessment of Linear and Quadratic Function Graphs Using Least-squares Fitting](https://annals-csis.org/proceedings/2014/pliks/365.pdf) (Co-written by assigning professor)
* [A piece of code I borrowed back then](http://ganeshtiwaridotcomdotnp.blogspot.com/2009/12/c-c-code-lu-decomposition-for-solving.html)
