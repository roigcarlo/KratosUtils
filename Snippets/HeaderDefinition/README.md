# Description

This snippet forces a ODR violation by adding the definition of a funcion in separated header and marking such definition as `inline`

C++ Standard allows multiple definitions across a single compilation unit as long as they identical, but leaves the programmer the responsability to ensure this condition. 
Breaking this rule results in undefined behaviour.

# Usage

To compile

```bash
cmake .
make
```

It will generate different binaries `_XYZ` where each letter is the order of linkage of the object containing a different definition or `_` if it has not been included

Note that different binaries have different outputs while the compiler does not issue any warning.
