section .text

global common_handler
extern ISR_Handler

%macro interrupt 1

  global isr%1
  isr%1:
    cli
    push %1
    jmp common_handler

%endmacro

%macro no_error_interrupt 1

  global isr%1
  isr%1:
    cli
    push 0
    push %1
    jmp common_handler

%endmacro

common_handler:
  pusha
  push ds
  push es
  push fs
  push gs
  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov eax, esp
  mov ebx, esp
  push eax
  push ebx
  mov ebx, ISR_Handler
  call ebx
  pop ebx
  pop eax
  pop gs
  pop fs
  pop es
  pop ds
  popa
  add esp, 8
  iret

no_error_interrupt 0
no_error_interrupt 1
no_error_interrupt 2
no_error_interrupt 3
no_error_interrupt 4
no_error_interrupt 5
no_error_interrupt 6
no_error_interrupt 7
interrupt 8
no_error_interrupt 9
interrupt 10
interrupt 11
interrupt 12
interrupt 13
interrupt 14
no_error_interrupt 15
no_error_interrupt 16
no_error_interrupt 17
no_error_interrupt 18
no_error_interrupt 19
no_error_interrupt 20
no_error_interrupt 21
no_error_interrupt 22
no_error_interrupt 23
no_error_interrupt 24
no_error_interrupt 25
no_error_interrupt 26
no_error_interrupt 27
no_error_interrupt 28
no_error_interrupt 29
no_error_interrupt 30
no_error_interrupt 31
