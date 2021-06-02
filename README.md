# abi-break-demo

This repo shows a relatively straightforward version of an ABI break in C++. In
this case, I reordered the members of the class around and added one new one.
The executable will compile with a different class layout for Simple_String
than the shared library, which will cause a ton of problems. This repo consists
of an intentionally pathological example with several data members when one or
two would have sufficed. Furthermore, this code is littered with gross macros,
nested if-else chains, intentionally bad getters and setter, etc. because I was
throwing this together without too much regard for the cleanliness of the code.

## Example

Here's an example of it running on my machine.

![The Output of the Program](https://github.com/TheLandfill/abi-break-demo/blob/main/resources/abi-demo.png)

Every byte is encoded by two hex digits. For ease of reading, I separated each
the class into two bite chunks. Pink means that it just changed, green means
matches with the original, red means doesn't match with the original, and grey
is before anything changed. The text on the left is what I modified to get the
result. Note that everything can change in this class, including pointers and
const data like `added_data`.

## Explanation

An ABI break happens when two objects that execute code (e.g. executables and
shared libraries) expects different things from another. In this repo, the
shared library expects a class with one layout and the executable expects a
class with another layout. As another example, name mangling can cause problems
between compilers by leading to the same name in the API being two different
names for two different objects.

## Compiling and Running

Linux and MacOS:

```bash
$ git clone https://github.com/TheLandfill/abi-break-demo/
$ cd abi-break-demo
$ bin/gen-toolchains.py gcc-linux
$ cd Release
$ make
$ ./abi-break
```

Windows:

```batch
> git clone https://github.com/TheLandfill/abi-break-demo/
> cd abi-break-demo
> mkdir build
> cd build
> cmake ..
```

## Endianness

This probably only works on little endian CPUs because I don't have a big endian
one to test the code on.
