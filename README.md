## shard_libc

### What this project is and why the hell I'm doing it
This project is an attempt at implementing the ISO C2x standard, purely for the sake of learning as much as possible about how C works internally and maybe (hopefully) creating a usable implementation somewhere down the road. The Windows C runtime is also pretty (unnecessarily) bloated most of the time for smaller apps, so this could eventually be a viable alternative. Another awesome thing is that this implementation breaks the standard by __not renaming implemented POSIX/BSD/more obscure printf-related functions__ <sub>_\*cough\*_ _\*cough\*_ damn you Microsoft _\*cough\*_ _\*cough\*_</sub>, which makes it possible to port your existing somewhat POSIX-dependant code to it with less effort.

Currently, there's the beginnings of the code necessary to (almost) call `main` and have `argc`, `argv`, and `envp`/`environ` available on Windows (currently need quite a bit of stuff like `malloc`) and Linux (currently segfaults somewhere around `main` for reasons only K&R know) running under x86-64.

### How to (theoretically) compile the library
Obviously, this project uses CMake for portability. Currently, nothing compiles the way it should. If I or someone else gets the necessary stuff done, then running the standard `cmake -S. -B<somewhere> && cmake --build <somewhere>` will do the trick, providing you with `<somewhere>/src/[lib]c_shard.{a,lib}` and `<somewhere>/tests/test_main[.exe]` (which is a program that has a main function and nothing else that is intended to be called by the `__libc_call_main` function)

<sub>Note: anything disparaging Microsoft in this project is not to be taken too seriously, I'm just frustrated with ~~some~~ __a lot__ of their design choices that make it less fun to develop for their platforms.</sub>
