section .text

global idt_load

extern idt

idt_load:
  lidt [idt]
  ret
