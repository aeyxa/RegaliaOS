section .text

extern irq_handler

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
  push eax
  mov eax, irq_handler
  call eax
  pop eax
  pop gs
  pop fs
  pop es
  pop ds
  popa
  add esp, 8
  iret
