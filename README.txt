Very simple example using the 65816 LLVM backend with Clang to compile to
an SFC (SNES/Super Nintendo) cartridge ROM.

The backend outputs to the WLAK format, compatible with WLA DX. Since
the backend does not have its own linker, we have to download and use
wlalink for this purpose. We also use wla-65816 since it has some
very handy macros for defining SFC headers.

http://www.villehelin.com/wla.html


LIMITATIONS

Global variables have to be defined in boot.asm for now.

The compile script is a Bash script, and might have to be modified
for use on nonconforming operating systems.


BUILDING AND RUNNING

1. Check out the source code

git clone https://github.com/Peppar/llvm-C65-sfc-example.git sfc-example

2. Modify the paths in sfc-example/compile.sh to point to wla-65816,
   wlalink, clang and llvm-mc (from the 65816 compatible Clang
   builds).

3. Compile

cd sfc-example
./compile.sh

4. Emulate using your favorite SFC emulator, for example with higan:

higan sfc-example/sfc-example.sfc

5. Push A/B/X/Y to change the background color.
