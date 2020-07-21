# Miscellaneous Keys for better understanding in C++

### [Classes](https://github.com/ritiksingla/Competitive-Programming-Notebook/blob/master/Miscellaneous/classes.cpp)
- Operator Overloading
- Increment and Decrement operators overloading
- Functors

### [Template](https://github.com/ritiksingla/Competitive-Programming-Notebook/blob/master/Miscellaneous/template.cpp)
- Useful debugging
- Time saving templates
- Rich PBDS library

### Builtin functions of GCC compiler
```cpp
Indices goes from small to large in one based index
NOTE: Dont use for number zero anything (clz,ffs,ctz,popcount,etc.)
index  ... 5 4 3 2 1
binary ....1 0 0 0 0
// Count leading zeros
__builtin_clz(int)->32-(1 based most significant bit)
__builtin_clzll(int)->64-(1 based most significant bit)
// Find first setbit
__builtin_ffs(x) gives 1 based index of lsb from right
// Count trailing zeros
__builtin_ctz(x) returns number of trailing 0-bits of x
// Total number of setbits
__builtin_popcount(x) returns number of 1-bits of x
__builtin_popcountll(x) returns number of 1-bits of x
```

 ### Bitset
```cpp
int x = 32;
string b = "11001";
bitset<32>binary1(x);
bitset<32>binary2(b);
debug(binary2, binary2[0], binary2.size(), binary2.any(), binary2.none());
binary2.set();
binary2.flip(10);
binary2=(~binary2);
debug(binary2,binary2.to_ullong());
debug(binary1.count());
debug((binary1 | binary2));
/* Output
[binary2, binary2[0], binary2.size(), binary2.any(), binary2.none()] : 00000000000000000000000000011001 1 32 1 0 
[binary2,binary2.to_ullong()] : 00000000000000000000010000000000 1024 
[binary1.count()] : 1 
[(binary1 | binary2)] : 00000000000000000000010000100000
*/
```

### Polishing Basics
- Swap operation: tie(b,a)=make_tuple(a,b);
- Cut and paste in v and empty w:vector<int>v=move(w);
- For set use s.lower_bound(x),s.upper_bound(x)...
- map.count(x),set.count(x) returns 0 or 1 
- multiset.count(x) returns total instance of x.