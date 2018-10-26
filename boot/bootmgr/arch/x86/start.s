// File author is Ítalo Lima Marconato Matias
//
// Created on October 22 of 2018, at 15:31 BRT
// Last edited on October 24 of 2018, at 17:44 BRT

.code16

.extern LoaderMain
.global LoaderEntry
LoaderEntry:
	cli
	
	xor %ax, %ax						// Setup segments
	mov %ax, %ds
	mov %ax, %es
	mov $0x9000, %ax
	mov %ax, %ss
	mov $0xFFFF, %sp
	
	movb %dl, (ArchBootDrive)			// Save the boot drive
	
	call LoaderEnableA20				// Enable the A20 gate
	
	call LoaderInstallGDT				// Install a basic GDT
	
	mov %cr0, %eax						// Set the pmode bit in CR0
	or $1, %eax
	mov %eax, %cr0
	
	ljmp $0x08, $1f						// Far jump to enter pmode
.code32
1:
	mov $0x10, %ax						// Setup segments
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %ss
	mov $0x90000, %esp
	
	call LoaderMain						// Call the loader main function
2:
	jmp 2b								// Infinite loop

IDTPointerLimit:
	.word 0								// IDT limit storage
IDTPointerBase:
	.int 0								// IDT base storage

.global IDTLoad
IDTLoad:
	mov 4(%esp), %eax					// Load base
	mov %eax, (IDTPointerBase)
	mov 8(%esp), %ax					// Load limit
	mov %ax, (IDTPointerLimit)
	lidt (IDTPointerLimit)				// Reload IDT
	ret

.macro ISR_NO_ERRCODE num
.global ISRHandler\num
ISRHandler\num:
	cli
	push $0
	push $\num
	jmp ISRCommonStub
.endm

.macro ISR_ERRCODE num
.global ISRHandler\num
ISRHandler\num:
	cli
	push $\num
	jmp ISRCommonStub
.endm

ISR_NO_ERRCODE 0
ISR_NO_ERRCODE 1
ISR_NO_ERRCODE 2
ISR_NO_ERRCODE 3
ISR_NO_ERRCODE 4
ISR_NO_ERRCODE 5
ISR_NO_ERRCODE 6
ISR_NO_ERRCODE 7
ISR_ERRCODE 8
ISR_NO_ERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NO_ERRCODE 15
ISR_NO_ERRCODE 16
ISR_NO_ERRCODE 17
ISR_NO_ERRCODE 18
ISR_NO_ERRCODE 19
ISR_NO_ERRCODE 20
ISR_NO_ERRCODE 21
ISR_NO_ERRCODE 22
ISR_NO_ERRCODE 23
ISR_NO_ERRCODE 24
ISR_NO_ERRCODE 25
ISR_NO_ERRCODE 26
ISR_NO_ERRCODE 27
ISR_NO_ERRCODE 28
ISR_NO_ERRCODE 29
ISR_NO_ERRCODE 30
ISR_NO_ERRCODE 31
ISR_NO_ERRCODE 32
ISR_NO_ERRCODE 33
ISR_NO_ERRCODE 34
ISR_NO_ERRCODE 35
ISR_NO_ERRCODE 36
ISR_NO_ERRCODE 37
ISR_NO_ERRCODE 38
ISR_NO_ERRCODE 39
ISR_NO_ERRCODE 40
ISR_NO_ERRCODE 41
ISR_NO_ERRCODE 42
ISR_NO_ERRCODE 43
ISR_NO_ERRCODE 44
ISR_NO_ERRCODE 45
ISR_NO_ERRCODE 46
ISR_NO_ERRCODE 47
ISR_NO_ERRCODE 48
ISR_NO_ERRCODE 49
ISR_NO_ERRCODE 50
ISR_NO_ERRCODE 51
ISR_NO_ERRCODE 52
ISR_NO_ERRCODE 53
ISR_NO_ERRCODE 54
ISR_NO_ERRCODE 55
ISR_NO_ERRCODE 56
ISR_NO_ERRCODE 57
ISR_NO_ERRCODE 58
ISR_NO_ERRCODE 59
ISR_NO_ERRCODE 60
ISR_NO_ERRCODE 61
ISR_NO_ERRCODE 62
ISR_NO_ERRCODE 63
ISR_NO_ERRCODE 64
ISR_NO_ERRCODE 65
ISR_NO_ERRCODE 66
ISR_NO_ERRCODE 67
ISR_NO_ERRCODE 68
ISR_NO_ERRCODE 69
ISR_NO_ERRCODE 70
ISR_NO_ERRCODE 71
ISR_NO_ERRCODE 72
ISR_NO_ERRCODE 73
ISR_NO_ERRCODE 74
ISR_NO_ERRCODE 75
ISR_NO_ERRCODE 76
ISR_NO_ERRCODE 77
ISR_NO_ERRCODE 78
ISR_NO_ERRCODE 79
ISR_NO_ERRCODE 80
ISR_NO_ERRCODE 81
ISR_NO_ERRCODE 82
ISR_NO_ERRCODE 83
ISR_NO_ERRCODE 84
ISR_NO_ERRCODE 85
ISR_NO_ERRCODE 86
ISR_NO_ERRCODE 87
ISR_NO_ERRCODE 88
ISR_NO_ERRCODE 89
ISR_NO_ERRCODE 90
ISR_NO_ERRCODE 91
ISR_NO_ERRCODE 92
ISR_NO_ERRCODE 93
ISR_NO_ERRCODE 94
ISR_NO_ERRCODE 95
ISR_NO_ERRCODE 96
ISR_NO_ERRCODE 97
ISR_NO_ERRCODE 98
ISR_NO_ERRCODE 99
ISR_NO_ERRCODE 100
ISR_NO_ERRCODE 101
ISR_NO_ERRCODE 102
ISR_NO_ERRCODE 103
ISR_NO_ERRCODE 104
ISR_NO_ERRCODE 105
ISR_NO_ERRCODE 106
ISR_NO_ERRCODE 107
ISR_NO_ERRCODE 108
ISR_NO_ERRCODE 109
ISR_NO_ERRCODE 110
ISR_NO_ERRCODE 111
ISR_NO_ERRCODE 112
ISR_NO_ERRCODE 113
ISR_NO_ERRCODE 114
ISR_NO_ERRCODE 115
ISR_NO_ERRCODE 116
ISR_NO_ERRCODE 117
ISR_NO_ERRCODE 118
ISR_NO_ERRCODE 119
ISR_NO_ERRCODE 120
ISR_NO_ERRCODE 121
ISR_NO_ERRCODE 122
ISR_NO_ERRCODE 123
ISR_NO_ERRCODE 124
ISR_NO_ERRCODE 125
ISR_NO_ERRCODE 126
ISR_NO_ERRCODE 127
ISR_NO_ERRCODE 128
ISR_NO_ERRCODE 129
ISR_NO_ERRCODE 130
ISR_NO_ERRCODE 131
ISR_NO_ERRCODE 132
ISR_NO_ERRCODE 133
ISR_NO_ERRCODE 134
ISR_NO_ERRCODE 135
ISR_NO_ERRCODE 136
ISR_NO_ERRCODE 137
ISR_NO_ERRCODE 138
ISR_NO_ERRCODE 139
ISR_NO_ERRCODE 140
ISR_NO_ERRCODE 141
ISR_NO_ERRCODE 142
ISR_NO_ERRCODE 143
ISR_NO_ERRCODE 144
ISR_NO_ERRCODE 145
ISR_NO_ERRCODE 146
ISR_NO_ERRCODE 147
ISR_NO_ERRCODE 148
ISR_NO_ERRCODE 149
ISR_NO_ERRCODE 150
ISR_NO_ERRCODE 151
ISR_NO_ERRCODE 152
ISR_NO_ERRCODE 153
ISR_NO_ERRCODE 154
ISR_NO_ERRCODE 155
ISR_NO_ERRCODE 156
ISR_NO_ERRCODE 157
ISR_NO_ERRCODE 158
ISR_NO_ERRCODE 159
ISR_NO_ERRCODE 160
ISR_NO_ERRCODE 161
ISR_NO_ERRCODE 162
ISR_NO_ERRCODE 163
ISR_NO_ERRCODE 164
ISR_NO_ERRCODE 165
ISR_NO_ERRCODE 166
ISR_NO_ERRCODE 167
ISR_NO_ERRCODE 168
ISR_NO_ERRCODE 169
ISR_NO_ERRCODE 170
ISR_NO_ERRCODE 171
ISR_NO_ERRCODE 172
ISR_NO_ERRCODE 173
ISR_NO_ERRCODE 174
ISR_NO_ERRCODE 175
ISR_NO_ERRCODE 176
ISR_NO_ERRCODE 177
ISR_NO_ERRCODE 178
ISR_NO_ERRCODE 179
ISR_NO_ERRCODE 180
ISR_NO_ERRCODE 181
ISR_NO_ERRCODE 182
ISR_NO_ERRCODE 183
ISR_NO_ERRCODE 184
ISR_NO_ERRCODE 185
ISR_NO_ERRCODE 186
ISR_NO_ERRCODE 187
ISR_NO_ERRCODE 188
ISR_NO_ERRCODE 189
ISR_NO_ERRCODE 190
ISR_NO_ERRCODE 191
ISR_NO_ERRCODE 192
ISR_NO_ERRCODE 193
ISR_NO_ERRCODE 194
ISR_NO_ERRCODE 195
ISR_NO_ERRCODE 196
ISR_NO_ERRCODE 197
ISR_NO_ERRCODE 198
ISR_NO_ERRCODE 199
ISR_NO_ERRCODE 200
ISR_NO_ERRCODE 201
ISR_NO_ERRCODE 202
ISR_NO_ERRCODE 203
ISR_NO_ERRCODE 204
ISR_NO_ERRCODE 205
ISR_NO_ERRCODE 206
ISR_NO_ERRCODE 207
ISR_NO_ERRCODE 208
ISR_NO_ERRCODE 209
ISR_NO_ERRCODE 210
ISR_NO_ERRCODE 211
ISR_NO_ERRCODE 212
ISR_NO_ERRCODE 213
ISR_NO_ERRCODE 214
ISR_NO_ERRCODE 215
ISR_NO_ERRCODE 216
ISR_NO_ERRCODE 217
ISR_NO_ERRCODE 218
ISR_NO_ERRCODE 219
ISR_NO_ERRCODE 220
ISR_NO_ERRCODE 221
ISR_NO_ERRCODE 222
ISR_NO_ERRCODE 223
ISR_NO_ERRCODE 224
ISR_NO_ERRCODE 225
ISR_NO_ERRCODE 226
ISR_NO_ERRCODE 227
ISR_NO_ERRCODE 228
ISR_NO_ERRCODE 229
ISR_NO_ERRCODE 230
ISR_NO_ERRCODE 231
ISR_NO_ERRCODE 232
ISR_NO_ERRCODE 233
ISR_NO_ERRCODE 234
ISR_NO_ERRCODE 235
ISR_NO_ERRCODE 236
ISR_NO_ERRCODE 237
ISR_NO_ERRCODE 238
ISR_NO_ERRCODE 239
ISR_NO_ERRCODE 240
ISR_NO_ERRCODE 241
ISR_NO_ERRCODE 242
ISR_NO_ERRCODE 243
ISR_NO_ERRCODE 244
ISR_NO_ERRCODE 245
ISR_NO_ERRCODE 246
ISR_NO_ERRCODE 247
ISR_NO_ERRCODE 248
ISR_NO_ERRCODE 249
ISR_NO_ERRCODE 250
ISR_NO_ERRCODE 251
ISR_NO_ERRCODE 252
ISR_NO_ERRCODE 253
ISR_NO_ERRCODE 254
ISR_NO_ERRCODE 255

.extern ISRDefaultHandler
ISRCommonStub:
	push %eax
	push %ecx
	push %edx
	push %ebx
	push %ebp
	push %esi
	push %edi
	
	push %ds
	push %es
	push %fs
	push %gs
	
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	
	push %esp
	call ISRDefaultHandler
	add $4, %esp
	
	pop %gs
	pop %fs
	pop %es
	pop %ds
	
	pop %edi
	pop %esi
	pop %ebp
	pop %ebx
	pop %edx
	pop %ecx
	pop %eax
	
	add $8, %esp
	iret

.code16

LoaderEnableA20:
	pusha								// Save all the registers
	
	call 1f								// Disable keyboard
	mov $0xAD, %al
	out %al, $0x64
	
	call 1f								// Tell the controller to read the output port
	mov $0xD0, %al
	out %al, $0x64
	
	call 2f								// Get the output port data and store it
	in $0x60, %al
	push %eax
	
	call 1f								// Tell controller to write to the output port
	mov $0xD1, %al
	out %al, $0x64
	
	call 1f								// Enable A20
	pop %eax
	or $2, %al
	out %al, $0x60
	
	call 1f								// Enable the keyboard
	mov $0xAE, %al
	out %al, $0x64
	
	call 1f
	
	popa								// Restore all the registers
	ret
1:
	in $0x64, %al
	test $2, %al
	jnz 1b
	ret
2:
	call 1b
	mov $0xD0, %al
	out %al, $0x64
3:
	in $0x64, %al
	test $1, %al
	jz 3b
	in $0x60, %al
	ret

LoaderInstallGDT:
	pusha
	lgdt (LoaderGDTPointer)
	popa
	ret

LoaderGDTStart:
	.int 0x00000000, 0x00000000
	.byte 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x9A, 0xCF, 0x00
	.byte 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x92, 0xCF, 0x00
LoaderGDTEnd:
LoaderGDTPointer:
	.word LoaderGDTEnd - LoaderGDTStart - 1
	.int LoaderGDTStart

.global ArchBootDrive
ArchBootDrive: .byte 0