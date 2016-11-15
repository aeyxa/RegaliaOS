section .text

extern _ZN7Regalia16InterruptManager15HandleInterruptEhm
; The extern above is the object function name of the HandleInterrupt() in
; the idt.cpp file, found by running:
;
; make idt.o
; nm idt.o
;
; produced the following output:
;
; 00000000 T _ZN7Regalia16InterruptManager15HandleInterruptEhm

global _ZN7Regalia16InterruptManager22IgnoreInterruptRequestEv

%macro HandleException 1
global _ZN7Regalia16InterruptManager16HandleException\number\()Ev

_ZN16InterruptManager16HandleException\number\()Ev:
  mov (interruptNumber), %1   ; set variable
  jmp int_buttom              ; jump with it

%endmacro

%macro HandleInterruptRequest0x00 0
global _ZN7Regalia16InterruptManager26HandleInterruptRequest0x00Ev

_ZN7Regalia16InterruptManager26HandleInterruptRequest0x00Ev:
  mov byte [interruptNumber], 0x20  ; set variable
  jmp int_bottom                    ; jump with it

%endmacro

%macro HandleInterruptRequest0x01 0
global _ZN7Regalia16InterruptManager26HandleInterruptRequest0x01Ev

_ZN7Regalia16InterruptManager26HandleInterruptRequest0x01Ev:
  mov byte [interruptNumber], 0x21  ; set variable
  jmp int_bottom                    ; jump with it

%endmacro

HandleInterruptRequest0x00; idt.cpp/h 0x00 timer interrupt
HandleInterruptRequest0x01; idt.cpp/h 0x01 keyboard interrupt

; int_bottom is used to jump into the HandleInterrupt function described above.

int_bottom:
  ; first we push current registers
  pusha
  push ds
  push es
  push fs
  push gs

  ; jump to the c++ function with the interruptNumber
  push esp
  push interruptNumber
  call _ZN7Regalia16InterruptManager15HandleInterruptEhm
  mov esp, eax

  ; pop the registers back
  pop gs
  pop fs
  pop es
  pop ds
  popa

_ZN7Regalia16InterruptManager22IgnoreInterruptRequestEv:

  iret

data:
    interruptNumber: db 0 ; start at zero
    IRQ_BASE: db 0x20 ; 0x20 is the Master PIC's command port
