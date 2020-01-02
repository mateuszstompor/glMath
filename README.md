<p align="center">
  <img src="https://github.com/mateuszstompor/glMath/blob/master/artwork/icon.png?raw=true" width="40%">
</p>

<h1 align="center">glMath</h1>
<p align="center">    
    <a href="https://www.travis-ci.org/mateuszstompor/glMath">
        <img src="https://www.travis-ci.org/mateuszstompor/glMath.svg?branch=master" height="18pt" alt="Build status"/>
    </a>
</p>

The repository contains math tools required to develop a graphics engine.
It has been used for both online and offline rendering projects.
Examples of algebraic tools are `matrices`, `vectors`, `plane` and geometric primitives like `spheres` or `triangles`.
Has a definition of `ray` and implements most commonly used intersection methods.
Is capable of detecting in-sight bounding boxes in regard to a defined camera. 
It is distributed in form of a header-only library, optimized for storing matrices in column-wise order.
All classes which belong to the project are implemented as templates, there is no need of compilation.
The only thing required to use resources of the library is to include the main header file `glMath.h`.

## Compatibility
Project has been tested with the most popular compilers, such as clang, gcc and vsc. Uses C++17 standard.
It was tested on:
* clang(ver. 5.0)
* gcc(ver. 5.0)
* vs compiler from year 2015

## Requirements
* cmake (ver. 3.9+)

## Installation
To install the library locally execute the snipped below:
```bash
$ git clone https://github.com/mateuszstompor/glMath.git
$ cd glMath
$ mkdir build && cd build
$ cmake ..
$ make install
```

## Data structures
Each data structure is implemented as a template class. 
The user can decide which type shall be used for calculations.

Most important algebraic structures:
* `Vector` (n-dimensional) with optimization for 2, 3 and 4 dimensions
* `Matrix` (n-dimensional) with optimization for 2, 3 and 4 dimensions
* `Ray` (n-dimensional)
* `Spherical Coordinates` defined with three primary angles
* `Plane` (3 or 4 dimensional)

Most important structures for defining geometry of an object:
* `Sphere`
* `Triangle` both with a normal vector defined for the face as a whole or for each vertex
* `Vertex`

Structures used for defining viewport and objects in camera's sight:
* `BoundingBox`
* `OrthographicViewport`
* `FrustumViewport`

## Testing
The recommended way of executing tests is by running a container with all required dependencies. 
Firstly, build the image:
```bash
$ docker build -f ./tests/environment/Dockerfile  -t glmath_tests .
```

Instantiate the container and run the tests' executable:
```bash
$ docker run -ti glmath_tests
```

## General thoughts
I treat the project as a playground where I learn about maths backing 3D project. 
There are many other project which may have similar capabilities.
The purpose is to reinvent the wheel and let myself and anyone else get deep understanding of what's going on under the hood of an engine.
 