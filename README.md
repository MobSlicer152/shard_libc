## shard_libc

### What this project is and why the hell I'm doing it
This project is a 13-year-old's attempt at implementing the ISO C2x standard, purely for the sake of learning as much as possible about how C works internally and maybe (hopefully) creating a usable implementation somewhere down the road.

Currently, there's the beginnings of the code necessary to (almost) call main and have argc, argv, and envp/environ available on Windows (currently need quite a bit of stuff like malloc) and Linux (currently segfaults somewhere around main for reasons only the gods K&R know) running under x86-64.

### How to (theoretically) compile the library
Obviously, this project uses CMake for portability. It compiles just fine last time I checked under Linux, but on Windows there are some switches and stuff I have to figure out. If I or someone else gets the necessary stuff done, then running the standard `cmake -S. -B<somewhere> && cmake --build <somewhere>` will do the trick, providing you with `<somewhere>/src/[lib]c_shard.{a,lib}` and `<somewhere>/tests/test_main[.exe]` (which is a program that has a main function and nothing else that is intended to be called by the `__libc_call_main` function)

