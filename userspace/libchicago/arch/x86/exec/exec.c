// File author is Ítalo Lima Marconato Matias
//
// Created on November 06 of 2019, at 18:44 BRT
// Last edited on January 05 of 2020, at 22:03 BRT

#include <chicago/types.h>

IntPtr ExecCreateProcess(PWChar path, UIntPtr argc, PWChar *argv) {
	IntPtr ret;
	Asm Volatile("int $0x3F" : "=a"(ret) : "0"(0x1F), "b"((UIntPtr)path), "c"(argc), "d"((UIntPtr)argv));
	return ret;
}
