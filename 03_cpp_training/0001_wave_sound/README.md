# 외국사람이 만든거
- C++
  - https://github.com/RobertDurfee/Wave

- C
  - wav2c makes arrays out of sounds - useful for Arduino SMAPLER v2 (and for GameBoy Advance) etc
    -  https://github.com/olleolleolle/wav2c

# 좋습니다 🎵 그러면 10초 동안 음이 바뀌는 WAV 파일을 만들어보겠습니다.

- 예를 들어 10초를 5등분해서, 각 2초마다
  - 도 (C4, 261.63Hz)
  - 레 (D4, 293.66Hz)
  - 미 (E4, 329.63Hz)
  - 파 (F4, 349.23Hz)
  - 솔 (G4, 392.00Hz)
- 이 순서대로 재생되도록 하겠습니다.# 

# Result

- cmake 로 최적화

```bash
$ just cro

rm -rf build
mkdir -p build
cmake -D CMAKE_BUILD_TYPE=RelWithDebInfo -D CMAKE_CXX_COMPILER=/opt/gcc-15/bin/g++ -D CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT="-O2 -g" -G Ninja .
-- The CXX compiler identification is GNU 15.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /opt/gcc-15/bin/g++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (0.1s)
-- Generating done (0.0s)
-- Build files have been written to: /home/g/my_project/Rust_Lang/9999/2222/cpp26_pthread_cmake_just_sample/02_debug_release_test
ninja
[4/4] Linking CXX executable target/02_debug_release_test
mv build.ninja CMakeCache.txt CMakeFiles cmake_install.cmake target .ninja_deps .ninja_log build
./build/target/02_debug_release_test
Multiplication Time : 0.640681 seconds
```

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
