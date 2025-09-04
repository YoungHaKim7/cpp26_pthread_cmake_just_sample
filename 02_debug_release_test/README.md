# Result

```bash
$ just ro

rm -rf target
mkdir -p target
/opt/gcc-15/bin/g++ -std=c++26 -O2 -pedantic -pthread -pedantic-errors -lm -Wall -Wextra -ggdb ./src/main.cpp
mv a.out target
target/./a.out
Multiplication Time : 0.682643 seconds
```

- 최적화 안하면 12초짜리

```bash
$ just r

rm -rf target
mkdir -p target
/opt/gcc-15/bin/g++ -std=c++26 -pedantic -pthread -pedantic-errors -lm -Wall -Wextra -ggdb ./src/main.cpp
mv a.out target
target/./a.out
Multiplication Time : 12.8356 seconds
```
