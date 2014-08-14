.globl bar
bar:
  mov $0, %eax
  ret

.globl foo
foo:
  push %ebp
  mov %esp, %ebp

  movzb 8(%ebp), %eax
  push %eax

  push 8(%eax)
  push $0x10203040
  mov $0x10203040, %eax
  fldl (%eax)
  fstpl 8(%ebp)
  push 12(%ebp)
  push 8(%ebp)
  call bar
  add $8, %esp

  mov %ebp, %esp
  pop %ebp
  ret
