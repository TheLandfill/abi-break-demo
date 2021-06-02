# abi-break-demo

This repo is the simplest possible version of an ABI break I could demonstrate in C++. The executable will compile with a different class layout for Simple_String than the shared library, which has noticeable side effects in both the size of the class and the fact that changing the variables within the class will lead to the class reporting a nonsense length.
