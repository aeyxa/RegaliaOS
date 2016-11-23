; Here we are defining the init and fini functions which are used by g++ to
; do some initial linking before jumping into kernel_main. This is usually done
; for you by the C library but because we are compiling with the flag -nostdlib
; in our linker, we have to do it ourselves.

; The code here comes from http://wiki.osdev.org/Calling_Global_Constructors
; and at this time is specifically used for the purpose of loading the terminal
; as a global object before jumping into kernel_main.

; NOTE: There was a .type in the example above, not sure that's required with
; NASM as it compiles and works as intended.

section .init
global init

init:
  push ebp
  mov ebp, esp

section .fini
global fini

fini:
  push ebp,
  mov ebp, esp
