# CLAY

_A `C23` Linear Algebra librarY_

## Table of Contents

- [Table of Contents](#table-of-contents)
- [Overview](#overview)
    - [Key Components](#key-components)
    - [Key Features](#key-features)
- [Setup](#setup)
    - [Cloning the Repository](#cloning-the-repository)

## Overview

### Key Components

- `include/`: Holds declarations for the structures and methods utilized in the library.
    - [`include/Vector/`](./include/Vector/): Structures and methods for vectors.
    - [`include/Matrix/`](./include/Matrix/): Structures and methods for matrices.
- `src/`: Holds definitions for the structures and methods utilized in the library.

### Key Features

- **Matrix Decompositions**
    - _LU Decomposition with Partial Pivoting_
    - _In-place LU Decomposition with Partial Pivoting_
    - _Cholesky Decomposition_
    - _In-place Cholesky Decomposition_
    - _QR Decomposition_
    - _QR Decomposition for Hessenberg Matrices_
- **Direct Linear Solvers**
    - _Gaussian Elimination with Partial Pivoting_
    - _LU Solver_
    - _Cholesky Solver_
    - _QR Solver_
- **Eigenvalue Computation**
    - _QR Algorithm_

## Setup

### Cloning the Repository

Clone the repository from [here](https://github.com/diantonioandrea/CLAY):

```bash
git clone git@github.com:diantonioandrea/CLAY.git
```
