# glMath

<p>Repository contains math operations and data structures used by graphics engines and optimized for OpenGL.
Project is integrated with Travis. After each commit server runs tests and checks memory footprint using Valgrind.</p>

## Requirements
Project is compatible with the most popular compilers, such as clang, gcc and vsc.
It was tested on:
<ul>
  <li>clang(ver. >5.0)</li>
  <li>gcc(ver. >5.0)</li>
  <li>vs compiler from year 2015</li>
</ul>

## How to build
Because classes which belong to project are implemented as templates there is no need of compilation.
Only thing which has to be done in order to use library is to include main header file.

## How to use?
Clone repository, copy files from include directory to your project and import umbrella file named glMath.h.
Alternatively, it is possible to use CMake in order to install project.

## Installation
If you would like to install the library once and for all I suggest using CMake and run the snippet placed below.
```c
$ git clone https://github.com/mateuszstompor/glMath.git
$ cd glMath
$ mkdir build && cd build
$ cmake ..
$ make install
```

## Data structures
<p>Each data structure is implemented as template class, so user can decide which underlying type he/she wants to use.</p>
<ul>
<li>Vector</li>
<li>Spherical Coordinates</li>
<li>Matrix</li>
<li>Plane</li>
<li>Bounding Box</li>
<li>Structures used for representation of viewport, such as frustum and box viewport</li>
</ul>

## Build, Tests and MemCheck status
[![Build Status](https://www.travis-ci.org/mateuszstompor/glMath.svg?branch=master)](https://www.travis-ci.org/mateuszstompor/glMath)
