shard_libc                                                 {#mainpage}
==========

### What this project is and why the hell I'm doing it
This project is an attempt at implementing the ISO C2x standard, purely for the sake of learning as much as possible about how C works internally and maybe (hopefully) creating a usable implementation somewhere down the road. The Windows C runtime is also pretty (unnecessarily) bloated most of the time for smaller apps, so this could eventually be a viable alternative. Another awesome thing is that this implementation breaks the standard by __not renaming implemented POSIX/BSD/more obscure printf-related functions__, which makes it possible to port your existing somewhat POSIX-dependant code to it with less effort.

Currently, there's the code necessary to call `main` and have `argc`, `argv`, and `envp`/`environ` available on Windows and Linux running under x86-64. There's also some other stuff like some of the more common (read "they were necessary to implement half this stuff sanely") `string.h` functions, a (working) syscall wrapper for both platforms (yes, Windows too), dynamic loading of all DLL's and functions (including NTDLL's functions, see `src/win32/dll_loader.c`), basic poorly implemented I/O (shitty fprintf/vfprintf, [stb_sprintf](https://github.com/nothings/stb/blob/master/stb_sprintf.h)), `write` for both platforms (the Windows one can even use kernel handles (I think)), and no security (stack protector and such) whatsoever. On Windows, `bin/main.exe` compiles (as of this writing) to ~6 pages (25600 bytes), while the same executable compiled with MSVCRT is ~30 pages (123392 bytes).

### How to compile the library
This project should work fine on Windows and Linux. On Windows, building in Visual Studio will give you `bin/libc_shard.lib` and `bin/main.exe`. On Linux, running `ninja` will get you `bin/libc_shard.a` and `bin/tests/main`. `bin/main` should print the program's arguments when you run it.

<sub>Note: anything disparaging Microsoft in this project is not to be taken too seriously, I'm just frustrated with some^H^H^H^H __a lot__ of their design choices that make it less fun to develop things (this especially) for their platforms. I don't really hate them. In fact, their many products (particularly Windows and MSDOS) are quite impressive.</sub>
