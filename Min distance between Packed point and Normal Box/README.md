# Min distance between Normal Box and Packed Point

## Task Description:

Task is  to implement code to find the Hausdorff distance from a normalized box to a horizontally packed point in C++ using AVX-512.

The normalized box represents a rectangle centered at the point (0,0), and the packed point is defined by two arrays of 8 doubles, which correspond to the X and Y coordinates, respectively. The interface for the PackedPoint and NormalBox classes can be found in the `structures_cpp.h` and `structures_avx.h` files.

Implemented in `SquaredDistance` and `SquaredDistanceMask` functions to find the Euclidean distance between two points, as well as the `Hausdorff_CPP` and `Hausdorff_AVX` functions to find the Hausdorff distance between the horizontally packed point and the normalized box. The interface can be found in the `hausdorff_avx.h` and `hausdorff_cpp.h` files.

**Note that if a point is inside the "box," we still calculate its Hausdorff distance to the "box" using the same rules as if it were outside.**

**A point lying on the boundary of the box is considered to be inside it.**

Link the files through the attached `BUILD` file.

Tests for the task can be found in the `test.cpp` file, and benchmarks are in the `bench.cpp` file.

## Useful Links:

[Hausdorff Distance](https://en.wikipedia.org/wiki/Hausdorff_distance)  
[AVX-512 Functions Registry](https://www.laruence.com/sse/#avx512techs=AVX512F&expand=42)

## Project Description:

**See the task description section :P**

In addition to the files mentioned above, the project includes a `functions.h` file, which contains the masks `IsUp`, `IsDiag`, `IsRight`, and `Within`, which determine the position of the **module of the packed point coordinates** relative to the normalized box in the **first quadrant** of the coordinate plane.

It is clear that if `IsUp`, `IsRight`, or `Within` are true, it is sufficient to consider only the "far corner" of the box "visible" from this point; in the case of `IsDiag`, two "far corners" are considered.

Explanations for the checked flags are provided in comments in the `functions.h` file.

Next, in the `Hausdorff_AVX` function, the aforementioned masks are checked, and the supremum of the obtained values is taken.

The code using AVX-512 is implemented similarly to the code in pure C++, with vector instructions speeding it up from ~13ns to ~6ns.

The project was completed by Dmitry Volkovets and Mikhail Naumovich, FPMI BSU, 1st course, 1st group, 2023/2024.