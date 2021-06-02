# abi-break-demo

This repo shows a relatively straightforward version of an ABI break in C++
caused by me reordering the members of the class around. The executable will
compile with a different class layout for Simple_String than the shared library,
which will cause a ton of problems. This repo consists of an intentionally
pathological example with several data members when one or two would have
sufficed. Furthermore, this code is littered with gross macros, nested if-else
chains, etc. because I was throwing this together without too much regard for
the cleanliness of the code.

## Example

Here's an example of it running on my machine.

![The Output of the Program](resources/output.png)

Every byte is encoded by two hex digits. For ease of reading, I separated each
the class into two bite chunks. Pink means that it just changed, green means
matches with the original, red means doesn't match with the original, and grey
is before anything changed. The text on the left is what I modified to get the
result.

## Endianness

This only works on little endian CPUs because I don't have a big endian one to
test the code on.
