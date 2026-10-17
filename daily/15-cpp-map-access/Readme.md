# Worst of C++: std::map access operator

To run example, use: 
```bash
./uglymap 1
./uglymap 2
...
```
Content: 

1 - misleading access operator that creates new element

2 - inserting with {} result with extra move constructors & assignments

3 - emplace with object result with extra move 

4 - correct way to use emplace

5 - emplace for existing key will move out a original value

6 - try_emplace will not move out, it's signature is different (two args: key & value instead of pair)

7 - usefull insert_or_assign

8 - contains

9 - erase_if that works on containers


