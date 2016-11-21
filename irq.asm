section .text

extern Handler

%macro irq 1

  global irq%1
  irq%1:
    cli
    push 0
    push %1
    jmp common_irq_handler;

%endmacro

common_irq_handler:
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
  mov ebx, Handler
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

irq 0
irq 1
irq 2
irq 3
irq 4
irq 5
irq 6
irq 7
irq 8
irq 9
irq 10
irq 11
irq 12
irq 13
irq 14
irq 15
