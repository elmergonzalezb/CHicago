// File author is Ítalo Lima Marconato Matias
//
// Created on January 03 of 2020, at 22:49 BRT
// Last edited on January 03 of 2020, at 22:51 BRT

#include <stdio.h>

int fprintf_unlocked(FILE *restrict stream, const char *restrict format, ...) {
	va_list arg;															// Let's init our arg list
	va_start(arg, format);
	int ret = vfprintf_unlocked(stream, format, arg);						// Call vfprintf
	va_end(arg);															// End the arg list
	return ret;
}
