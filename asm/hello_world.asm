[bits 16] ; tells the assembler we work in 16-bit mode
[org 0x7c00] ; memory location where BIOS will load

start: ;entry point label

	; https://wiki.cdot.senecacollege.ca/wiki/X86_64_Register_and_Instruction_Quick_Start
	; ax, bx, cx and dx  are general purpose registers.
	; si and di are general purpose registers as well, but stands for source register and destination register when using operations like movsb (source index, destination index)
	; sp : stack pointer 
	; bp : base pointer : points to the top of the stack when a function is called

	xor ax, ax ; used to set the a extended register to 0, since ax will always be equals to itself 
	mov ds, ax ; set the ds register to ax value (0) 
	mov es, ax ; same as above
	mov bx, 0x8000 ; set the b register to 0x8000

	mov si, hello_world
	call print_string

	hello_world db 'HelloWolrd', 13,0

print_string:
	mov ah, 0x0E ; ah is the first half of the ax register

.repeat_next_char:
	lodsb
	cmp al, 0
	je .done_print
	int 0x10
	jmp .repeat_next_char

.done_print
	ret

	times(510-($-$$)) db 0x00
	dw 0xAA55
