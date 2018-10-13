// File author is Ítalo Lima Marconato Matias
//
// Created on July 18 of 2018, at 21:12 BRT
// Last edited on October 13 of 2018, at 20:31 BRT

#define __CHICAGO_DISPLAY__

#include <chicago/debug.h>
#include <chicago/display.h>
#include <chicago/mm.h>
#include <chicago/string.h>

UIntPtr DispFrameBuffer = 0;
UIntPtr DispWidth = 0;
UIntPtr DispHeight = 0;
UIntPtr DispBytesPerPixel = 0;
UInt32 DispProgressBar = 0;

UInt8 DispFont[128][16] = {
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x7E, 0x81, 0xA5, 0x81, 0x81, 0xA5, 0x99, 0x81, 0x81, 0x7E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x7E, 0xFF, 0xDB, 0xFF, 0xFF, 0xDB, 0xE7, 0xFF, 0xFF, 0x7E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x36, 0x7F, 0x7F, 0x7F, 0x7F, 0x3E, 0x1C, 0x08, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x08, 0x1C, 0x3E, 0x7F, 0x3E, 0x1C, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x18, 0x3C, 0x3C, 0xE7, 0xE7, 0xE7, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x18, 0x3C, 0x7E, 0xFF, 0xFF, 0x7E, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x3C, 0x3C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0xC3, 0xC3, 0xE7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x66, 0x42, 0x42, 0x66, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3, 0x99, 0xBD, 0xBD, 0x99, 0xC3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
	{ 0x00, 0x00, 0x78, 0x60, 0x70, 0x58, 0x1E, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x3C, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x7E, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0xFC, 0xCC, 0xFC, 0x0C, 0x0C, 0x0C, 0x0C, 0x0E, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0xFE, 0xC6, 0xFE, 0xC6, 0xC6, 0xC6, 0xC6, 0xE6, 0xE7, 0x67, 0x03, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x18, 0x18, 0xDB, 0x3C, 0xE7, 0x3C, 0xDB, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x7F, 0x1F, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x40, 0x60, 0x70, 0x78, 0x7C, 0x7F, 0x7C, 0x78, 0x70, 0x60, 0x40, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x18, 0x3C, 0x7E, 0x18, 0x18, 0x18, 0x7E, 0x3C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x00, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0xFE, 0xDB, 0xDB, 0xDB, 0xDE, 0xD8, 0xD8, 0xD8, 0xD8, 0xD8, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x3E, 0x63, 0x06, 0x1C, 0x36, 0x63, 0x63, 0x36, 0x1C, 0x30, 0x63, 0x3E, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x18, 0x3C, 0x7E, 0x18, 0x18, 0x18, 0x7E, 0x3C, 0x18, 0x7E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x18, 0x3C, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x3C, 0x18, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x30, 0x7F, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x06, 0x7F, 0x06, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x36, 0x7F, 0x36, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x08, 0x1C, 0x1C, 0x3E, 0x3E, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x3E, 0x3E, 0x1C, 0x1C, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x18, 0x3C, 0x3C, 0x3C, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x66, 0x66, 0x66, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x36, 0x36, 0x7F, 0x36, 0x36, 0x36, 0x7F, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00 },
	{ 0x18, 0x18, 0x3E, 0x63, 0x43, 0x03, 0x3E, 0x60, 0x60, 0x61, 0x63, 0x3E, 0x18, 0x18, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x43, 0x63, 0x30, 0x18, 0x0C, 0x06, 0x63, 0x61, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x1C, 0x36, 0x36, 0x1C, 0x6E, 0x3B, 0x33, 0x33, 0x33, 0x6E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x0C, 0x0C, 0x0C, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x18, 0x30, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x0C, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0C, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x0C, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x40, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x1C, 0x36, 0x63, 0x63, 0x6B, 0x6B, 0x63, 0x63, 0x36, 0x1C, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x18, 0x1C, 0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x3E, 0x63, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x63, 0x7F, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x3E, 0x63, 0x60, 0x60, 0x3C, 0x60, 0x60, 0x60, 0x63, 0x3E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x30, 0x38, 0x3C, 0x36, 0x33, 0x7F, 0x30, 0x30, 0x30, 0x78, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x7F, 0x03, 0x03, 0x03, 0x3F, 0x60, 0x60, 0x60, 0x63, 0x3E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x1C, 0x06, 0x03, 0x03, 0x3F, 0x63, 0x63, 0x63, 0x63, 0x3E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x7F, 0x63, 0x60, 0x60, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x0C, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x3E, 0x63, 0x63, 0x63, 0x3E, 0x63, 0x63, 0x63, 0x63, 0x3E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x3E, 0x63, 0x63, 0x63, 0x7E, 0x60, 0x60, 0x60, 0x30, 0x1E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x18, 0x18, 0x0C, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x3E, 0x63, 0x63, 0x30, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x3E, 0x63, 0x63, 0x7B, 0x7B, 0x7B, 0x3B, 0x03, 0x3E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x08, 0x1C, 0x36, 0x63, 0x63, 0x7F, 0x63, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x3F, 0x66, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x66, 0x66, 0x3F, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x3C, 0x66, 0x43, 0x03, 0x03, 0x03, 0x03, 0x43, 0x66, 0x3C, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x1F, 0x36, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x7F, 0x66, 0x46, 0x16, 0x1E, 0x16, 0x06, 0x46, 0x66, 0x7F, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x7F, 0x66, 0x46, 0x16, 0x1E, 0x16, 0x06, 0x06, 0x06, 0x0F, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x3C, 0x66, 0x43, 0x03, 0x03, 0x7B, 0x63, 0x63, 0x66, 0x5C, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x63, 0x63, 0x63, 0x63, 0x7F, 0x63, 0x63, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x78, 0x30, 0x30, 0x30, 0x30, 0x30, 0x33, 0x33, 0x33, 0x1E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x67, 0x66, 0x66, 0x36, 0x1E, 0x1E, 0x36, 0x66, 0x66, 0x67, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x0F, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7F, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x63, 0x67, 0x6F, 0x7F, 0x7B, 0x73, 0x63, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x3E, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x3F, 0x66, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x06, 0x06, 0x0F, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x3E, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x6B, 0x7B, 0x3E, 0x30, 0x70, 0x00, 0x00 },
	{ 0x00, 0x00, 0x3F, 0x66, 0x66, 0x66, 0x3E, 0x36, 0x66, 0x66, 0x66, 0x67, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x3E, 0x63, 0x63, 0x06, 0x1C, 0x30, 0x60, 0x63, 0x63, 0x3E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x7E, 0x7E, 0x5A, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x08, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x63, 0x63, 0x63, 0x63, 0x6B, 0x6B, 0x6B, 0x7F, 0x77, 0x36, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x63, 0x63, 0x36, 0x3E, 0x1C, 0x1C, 0x3E, 0x36, 0x63, 0x63, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x7F, 0x63, 0x61, 0x30, 0x18, 0x0C, 0x06, 0x43, 0x63, 0x7F, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x3C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x3C, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0E, 0x1C, 0x38, 0x70, 0x60, 0x40, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x3C, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3C, 0x00, 0x00, 0x00, 0x00 },
	{ 0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00 },
	{ 0x0C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x30, 0x3E, 0x33, 0x33, 0x33, 0x6E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x07, 0x06, 0x06, 0x1E, 0x36, 0x66, 0x66, 0x66, 0x66, 0x3E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x63, 0x03, 0x03, 0x03, 0x63, 0x3E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x38, 0x30, 0x30, 0x3C, 0x36, 0x33, 0x33, 0x33, 0x33, 0x6E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x63, 0x7F, 0x03, 0x03, 0x63, 0x3E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x1C, 0x36, 0x26, 0x06, 0x0F, 0x06, 0x06, 0x06, 0x06, 0x0F, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x6E, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3E, 0x30, 0x33, 0x1E, 0x00 },
	{ 0x00, 0x00, 0x07, 0x06, 0x06, 0x36, 0x6E, 0x66, 0x66, 0x66, 0x66, 0x67, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x18, 0x18, 0x00, 0x1C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x60, 0x60, 0x00, 0x70, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x66, 0x66, 0x3C, 0x00 },
	{ 0x00, 0x00, 0x07, 0x06, 0x06, 0x66, 0x36, 0x1E, 0x1E, 0x36, 0x66, 0x67, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x1C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x37, 0x7F, 0x6B, 0x6B, 0x6B, 0x6B, 0x63, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x3B, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x3B, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x0F, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x6E, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3E, 0x30, 0x30, 0x78, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x3B, 0x6E, 0x66, 0x06, 0x06, 0x06, 0x0F, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x63, 0x06, 0x1C, 0x30, 0x63, 0x3E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x08, 0x0C, 0x0C, 0x3F, 0x0C, 0x0C, 0x0C, 0x0C, 0x6C, 0x38, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x6E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x63, 0x6B, 0x6B, 0x6B, 0x7F, 0x36, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x36, 0x1C, 0x1C, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x7E, 0x60, 0x30, 0x1F, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x33, 0x18, 0x0C, 0x06, 0x63, 0x7F, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x70, 0x18, 0x18, 0x18, 0x0E, 0x18, 0x18, 0x18, 0x18, 0x70, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x0E, 0x18, 0x18, 0x18, 0x70, 0x18, 0x18, 0x18, 0x18, 0x0E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x6E, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x08, 0x1C, 0x36, 0x63, 0x63, 0x63, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00 }
};

UIntPtr DispGetFrameBuffer(Void) {
	return DispFrameBuffer;
}

UIntPtr DispGetWidth(Void) {
	return DispWidth;
}

UIntPtr DispGetHeight(Void) {
	return DispHeight;
}

UIntPtr DispGetBytesPerPixel(Void) {
	return DispBytesPerPixel;
}

Void DispExtractRGB(UIntPtr c, PUInt8 r, PUInt8 g, PUInt8 b) {
	if (r != Null) {
		*r = (UInt8)((c >> 16) & 0xFF);
	}
	
	if (g != Null) {
		*g = (UInt8)((c >> 8) & 0xFF);
	}
	
	if (b != Null) {
		*b = (UInt8)(c & 0xFF);
	}
}

Void DispPutPixel(UIntPtr x, UIntPtr y, UIntPtr c) {
	if (x >= DispWidth) {																										// Fix the x and the y if they are bigger than the screen dimensions
		x = DispWidth - 1;
	}
	
	if (y >= DispHeight) {
		y = DispHeight - 1;
	}
	
	PUInt8 fb = (PUInt8)(DispFrameBuffer + (y * (DispWidth * DispBytesPerPixel)) + (x * DispBytesPerPixel));					// Get a pointer to the framebuffer STARTING AT X, Y POSITION
	
	if (DispBytesPerPixel == 3) {																								// 3 bytes per pixel (True Color)?
		UInt8 r;																												// Yes
		UInt8 g;
		UInt8 b;
		
		DispExtractRGB(c, &r, &g, &b);																							// Extract the RGB values
		
		*fb++ = b;																												// And write them!
		*fb++ = g;
		*fb++ = r;
	} else if (DispBytesPerPixel == 4) {																						// 4 bytes per pixel (True Color + Alpha Blending)?
		UInt8 r;																												// Yes
		UInt8 g;
		UInt8 b;
		
		DispExtractRGB(c, &r, &g, &b);																							// Extract the RGB values
		
		*fb++ = b;																												// And write them!
		*fb++ = g;
		*fb++ = r;
		*fb++ = 0xFF;																											// *HACKHACKHACK*
	}
}

Void DispDrawLine(UIntPtr x0, UIntPtr y0, UIntPtr x1, UIntPtr y1, UIntPtr c) {
	if (x0 >= DispWidth) {																										// Fix the x and the y if they are bigger than the screen dimensions
		x0 = DispWidth - 1;																										//     Sorry, this function will not have a lot of documentation (not that my other ones are commented in a good way...)
	}
	
	if (y0 >= DispHeight) {
		y0 = DispHeight - 1;
	}
	
	if (x1 >= DispWidth) {
		x1 = DispWidth - 1;
	}
	
	if (y1 >= DispHeight) {
		y1 = DispHeight - 1;
	}
	
	IntPtr dx = x1 - x0;																										// Let's get the line direction
	IntPtr dy = y1 - y0;
	IntPtr sdx = (dx < 0) ? -1 : 1;
	IntPtr sdy = (dy < 0) ? -1 : 1;
	IntPtr px = x0;
	IntPtr py = y0;
	IntPtr x = 0;
	IntPtr y = 0;
	
	dx = sdx * dx + 1;
	dy = sdy * dy + 1;
	
	if (DispBytesPerPixel == 3) {																								// 3 bytes per pixel (True Color)?
		UInt8 r;																												// Yes
		UInt8 g;
		UInt8 b;
		
		DispExtractRGB(c, &r, &g, &b);																							// Extract the RGB values
		
		if (dx >= dy) {																											// This line is more horizontal?
			for (x = 0; x < dx; x++) {																							// Yes
				*((PUInt8)(DispFrameBuffer + (py * (DispWidth * DispBytesPerPixel)) + (px * DispBytesPerPixel))) = b;
				*((PUInt8)(DispFrameBuffer + (py * (DispWidth * DispBytesPerPixel)) + (px * DispBytesPerPixel) + 1)) = g;
				*((PUInt8)(DispFrameBuffer + (py * (DispWidth * DispBytesPerPixel)) + (px * DispBytesPerPixel) + 2)) = r;
				
				y += dy;
				
				if (y >= dx) {
					y -= dx;
					py += sdy;
				}
				
				px += sdx;
			}
		} else {
			for (y = 0; y < dy; y++) {																							// No, so is more vertical
				*((PUInt8)(DispFrameBuffer + (py * (DispWidth * DispBytesPerPixel)) + (px * DispBytesPerPixel))) = b;
				*((PUInt8)(DispFrameBuffer + (py * (DispWidth * DispBytesPerPixel)) + (px * DispBytesPerPixel) + 1)) = g;
				*((PUInt8)(DispFrameBuffer + (py * (DispWidth * DispBytesPerPixel)) + (px * DispBytesPerPixel) + 2)) = r;
				
				x += dx;
				
				if (x >= dy) {
					x -= dy;
					px += sdx;
				}
				
				py += sdy;
			}
		}
	} else if (DispBytesPerPixel == 4) {																						// 4 bytes per pixel (True Color + Alpha Blending)?
		UInt8 r;																												// Yes
		UInt8 g;
		UInt8 b;
		
		DispExtractRGB(c, &r, &g, &b);																							// Extract the RGB values
		
		if (dx >= dy) {																											// This line is more horizontal?
			for (x = 0; x < dx; x++) {																							// Yes
				*((PUInt8)(DispFrameBuffer + (py * (DispWidth * DispBytesPerPixel)) + (px * DispBytesPerPixel))) = b;
				*((PUInt8)(DispFrameBuffer + (py * (DispWidth * DispBytesPerPixel)) + (px * DispBytesPerPixel) + 1)) = g;
				*((PUInt8)(DispFrameBuffer + (py * (DispWidth * DispBytesPerPixel)) + (px * DispBytesPerPixel) + 2)) = r;
				*((PUInt8)(DispFrameBuffer + (py * (DispWidth * DispBytesPerPixel)) + (px * DispBytesPerPixel) + 3)) = 0xFF;
				
				y += dy;
				
				if (y >= dx) {
					y -= dx;
					py += sdy;
				}
				
				px += sdx;
			}
		} else {
			for (y = 0; y < dy; y++) {																							// No, so is more vertical
				*((PUInt8)(DispFrameBuffer + (py * (DispWidth * DispBytesPerPixel)) + (px * DispBytesPerPixel))) = b;
				*((PUInt8)(DispFrameBuffer + (py * (DispWidth * DispBytesPerPixel)) + (px * DispBytesPerPixel) + 1)) = g;
				*((PUInt8)(DispFrameBuffer + (py * (DispWidth * DispBytesPerPixel)) + (px * DispBytesPerPixel) + 2)) = r;
				*((PUInt8)(DispFrameBuffer + (py * (DispWidth * DispBytesPerPixel)) + (px * DispBytesPerPixel) + 3)) = 0xFF;
				
				x += dx;
				
				if (x >= dy) {
					x -= dy;
					px += sdx;
				}
				
				py += sdy;
			}
		}
	}
}

Void DispDrawRectangle(UIntPtr x, UIntPtr y, UIntPtr w, UIntPtr h, UIntPtr c) {
	DispDrawLine(x, y, x, y + h - 1, c);																						// Let's use the DispDrawLine to draw the rectangle (we just need to draw 4 lines)
	DispDrawLine(x, y, x + w - 1, y, c);
	DispDrawLine(x, y + h - 1, x + w - 1, y + h - 1, c);
	DispDrawLine(x + w - 1, y, x + w - 1, y + h - 1, c);
}

Void DispFillRectangle(UIntPtr x, UIntPtr y, UIntPtr w, UIntPtr h, UIntPtr c) {
	if (x >= DispWidth) {																										// Fix the x and the y if they are bigger than the screen dimensions
		x = DispWidth - 1;
	}
	
	if (y >= DispHeight) {
		y = DispHeight - 1;
	}
	
	if ((x + w) > DispWidth) {																									// Fix the width and height of our rectangle if they are bigger than the screen dimensions
		w = DispWidth - x;
	}
	
	if ((y + h) > DispHeight) {
		h = DispHeight - y;
	}
	
	PUInt8 fb = (PUInt8)(DispFrameBuffer + (y * (DispWidth * DispBytesPerPixel)) + (x * DispBytesPerPixel));					// Get a pointer to the framebuffer STARTING AT X, Y POSITION
	
	if (DispBytesPerPixel == 3) {																								// 3 bytes per pixel (True Color)?
		UInt8 r;																												// Yes
		UInt8 g;
		UInt8 b;
		
		DispExtractRGB(c, &r, &g, &b);																							// Extract the RGB values
		
		for (UIntPtr i = 0; i < h; i++) {																						// And fill our rectangle
			for (UIntPtr j = 0; j < w; j++) {
				*fb++ = b;
				*fb++ = g;
				*fb++ = r;
			}
			
			fb += (DispWidth - w) * DispBytesPerPixel;
		}
	} else if (DispBytesPerPixel == 4) {																						// 4 bytes per pixel (True Color + Alpha Blending)?
		UInt8 r;																												// Yes
		UInt8 g;
		UInt8 b;
		
		DispExtractRGB(c, &r, &g, &b);																							// Extract the RGB values
		
		for (UIntPtr i = 0; i < h; i++) {																						// And fill our rectangle
			for (UIntPtr j = 0; j < w; j++) {
				*fb++ = b;
				*fb++ = g;
				*fb++ = r;
				*fb++ = 0xFF;
			}
			
			fb += (DispWidth - w) * DispBytesPerPixel;
		}
	}
}

Void DispDrawRoundedRectangle(UIntPtr x, UIntPtr y, UIntPtr w, UIntPtr h, UIntPtr r, UIntPtr c) {
	if (r == 0) {																												// Radius is 0?
		DispDrawRectangle(x, y, w, h, c);																						// Yes, so just draw an rectangle
		return;
	}
	
	IntPtr f = 1 - r;
	IntPtr dfx = 1;
	IntPtr dfy = -2 * r;
	UIntPtr xx = 0;
	UIntPtr yy = r;
	
	if (w > 0) {
		w--;
	}
	
	if (h > 0) {
		h--;
	}
	
	while (xx < yy) {
		if (f >= 0) {
			yy--;
			dfy += 2;
			f += dfy;
		}
		
		xx++;
		dfx += 2;
		f += dfx;
		
		DispPutPixel(x - xx + r, y + h + yy - r, c);																			// Bottom left
		DispPutPixel(x - yy + r, y + h + xx - r, c);
		DispPutPixel(x - xx + r, y - yy + r, c);																				// Top left
		DispPutPixel(x - yy + r, y - xx + r, c);
		DispPutPixel(x + w + xx - r, y + h + yy - r, c);																		// Bottom right
		DispPutPixel(x + w + yy - r, y + h + xx - r, c);
		DispPutPixel(x + w + xx - r, y - yy + r, c);																			// Top right
		DispPutPixel(x + w + yy - r, y - xx + r, c);
	}
	
	DispDrawLine(x + r, y, x + w - r, y, c);																					// Draw the top line
	DispDrawLine(x + r, y + h, x + w - r, y + h, c);																			// The bottom one
	DispDrawLine(x, y + r, x, y + h - r, c);																					// The left one
	DispDrawLine(x + w, y + r, x + w, y + h - r, c);																			// And, the right one!
}

Void DispFillRoundedRectangle(UIntPtr x, UIntPtr y, UIntPtr w, UIntPtr h, UIntPtr r, UIntPtr c) {
	if (r == 0) {																												// Radius is 0?
		DispFillRectangle(x, y, w, h, c);																						// Yes, so just fill an rectangle
		return;
	}
	
	IntPtr f = 1 - r;
	IntPtr dfx = 1;
	IntPtr dfy = -2 * r;
	UIntPtr xx = 0;
	UIntPtr yy = r;
	
	if (w > 0) {
		w--;
	}
	
	if (h > 0) {
		h--;
	}
	
	while (xx < yy) {
		if (f >= 0) {
			yy--;
			dfy += 2;
			f += dfy;
		}
		
		xx++;
		dfx += 2;
		f += dfx;
		
		DispDrawLine(x - xx + r, y + h + yy - r, x - xx + r, y - yy + r, c);													// Left
		DispDrawLine(x - yy + r, y + h + xx - r, x - yy + r, y - xx + r, c);
		DispDrawLine(x + w + xx - r, y + h + yy - r, x + w + xx - r, y - yy + r, c);											// Right
		DispDrawLine(x + w + yy - r, y + h + xx - r, x + w + yy - r, y - xx + r, c);
	}
	
	DispFillRectangle(x + r, y, w - r * 2 + 1, h + 1, c);																		// Fill the center rectangle
	DispDrawLine(x, y + r, x, y + h - r, c);																					// The left line
	DispDrawLine(x + w, y + r, x + w, y + h - r, c);																			// And the right one
}

Void DispDrawBitmap(PUInt8 bmp, UIntPtr x, UIntPtr y) {
	PBmpHeader hdr = (PBmpHeader)bmp;																							// BMP file header
	PBmpInfoHeader ihdr = (PBmpInfoHeader)(((UIntPtr)bmp) + sizeof(BmpHeader));													// BMP info header
	PUInt8 bytes = (PUInt8)(((UIntPtr)bmp) + hdr->off);																			// The image itself
	
	for (UIntPtr i = 0; i < ihdr->height; i++) {																				// Let's do it!
		PUInt8 row = bytes + i * ihdr->width * 3;																				// Get this row
		
		for (UIntPtr j = 0, k = 0; k < ihdr->width; k++) {																		// Let's draw all the pixels
			UInt8 b = row[j++] & 0xFF;
			UInt8 g = row[j++] & 0xFF;
			UInt8 r = row[j++] & 0xFF;
			
			DispPutPixel(x + k, y + (ihdr->height - (i + 1)), (((r << 16) | (g << 8) | b) & 0xFFFFFF) | 0xFF000000);			// Convert the R, B and G to the A8R8G8B8 format and ALWAYS REMEMBER THAT IN BMP THE 0, 0 IS AT THE BOTTOM LEFT, AND OUR 0, 0 IS AT TOP LEFT
		}
	}
}

static Void DispWriteFormatedCharacter(PUIntPtr x, PUIntPtr y, UIntPtr bg, UIntPtr fg, Char data) {
	switch (data) {
		case '\n': {																											// Line feed
			*y += 16;
			break;
		}
		case '\r': {																											// Carriage return
			*x = 0;
			break;
		}
		case '\t': {																											// Tab
			*x = (*x + 32) & ~31;
			break;
		}
		default: {																												// Normal character (probably)
			for (IntPtr i = 0; i < 16; i++) {
				for (IntPtr j = 15; j >= 0; j--) {
					if (DispFont[(UInt8)data][i] & (1 << j)) {																	// Foreground?
						DispPutPixel(*x + j, *y + i, fg);																		// Yes!
					} else {
						DispPutPixel(*x + j, *y + i, bg);																		// Nope
					}
				}
			}
			
			*x += 8;
			
			break;
		}
	}
}

static Void DispWriteFormatedString(PUIntPtr x, PUIntPtr y, UIntPtr bg, UIntPtr fg, PChar data) {
	for (UIntPtr i = 0; i < StrGetLength(data); i++) {
		DispWriteFormatedCharacter(x, y, bg, fg, data[i]);
	}
}

static Void DispWriteFormatedInteger(PUIntPtr x, PUIntPtr y, UIntPtr bg, UIntPtr fg, UIntPtr data, UInt8 base) {
	if (data == 0) {
		DispWriteFormatedCharacter(x, y, bg, fg, '0');
		return;
	}
	
	static Char buf[32] = { 0 };
	Int i = 30;
	
	for (; data && i; i--, data /= base) {
		buf[i] = "0123456789ABCDEF"[data % base];
	}
	
	DispWriteFormatedString(x, y, bg, fg, &buf[i + 1]);
}

Void DispWriteFormated(UIntPtr x, UIntPtr y, UIntPtr bg, UIntPtr fg, Const PChar data, ...) {
	VariadicList va;
	VariadicStart(va, data);																									// Let's start our va list with the arguments provided by the user (if any)
	
	UIntPtr cx = x;
	UIntPtr cy = y;
	
	for (UInt32 i = 0; data[i] != '\0'; i++) {
		if (data[i] != '%') {																									// It's an % (integer, string, character or other)?
			DispWriteFormatedCharacter(&cx, &cy, bg, fg, data[i]);																// Nope
		} else {
			switch (data[++i]) {																								// Yes! So let's parse it!
			case 's': {																											// String
				DispWriteFormatedString(&cx, &cy, bg, fg, (PChar)VariadicArg(va, PChar));
				break;
			}
			case 'c': {																											// Character
				DispWriteFormatedCharacter(&cx, &cy, bg, fg, (Char)VariadicArg(va, Int));
				break;
			}
			case 'd': {																											// Decimal Number
				DispWriteFormatedInteger(&cx, &cy, bg, fg, (UIntPtr)VariadicArg(va, UIntPtr), 10);
				break;
			}
			case 'x': {																											// Hexadecimal Number
				DispWriteFormatedInteger(&cx, &cy, bg, fg, (UIntPtr)VariadicArg(va, UIntPtr), 16);
				break;
			}
			default: {																											// None of the others...
				DispWriteFormatedCharacter(&cx, &cy, bg, fg, data[i]);
				break;
			}
			}
		}
	}
	
	VariadicEnd(va);
}

Void DispIncrementProgessBar(Void) {
	if (DispProgressBar == 0) {																									// This first one is different
		DispFillRectangle(DispWidth / 2 - 100 + (DispProgressBar * 2) + 3, DispHeight - 24, 1, 9, 0x0000A8);
		DispFillRectangle(DispWidth / 2 - 100 + (DispProgressBar * 2) + 4, DispHeight - 25, 1, 11, 0x0000A8);
		DispFillRectangle(DispWidth / 2 - 100 + (DispProgressBar * 2) + 5, DispHeight - 26, 1, 13, 0x0000A8);
		DispFillRectangle(DispWidth / 2 - 100 + (DispProgressBar * 2) + 6, DispHeight - 27, 11, 15, 0x0000A8);
		DispProgressBar += 10;
	} else if (DispProgressBar < 90) {
		DispFillRectangle(DispWidth / 2 - 100 + (DispProgressBar * 2), DispHeight - 27, 17, 15, 0x0000A8);						// The others are... normal
		DispProgressBar += 10;
	} else if (DispProgressBar < 100) {
		DispFillRectangle(DispWidth / 2 - 100 + (DispProgressBar * 2), DispHeight - 27, 15, 15, 0x0000A8);						// The last one is also different
		DispFillRectangle(DispWidth / 2 - 100 + (DispProgressBar * 2) + 15, DispHeight - 26, 1, 13, 0x0000A8);
		DispFillRectangle(DispWidth / 2 - 100 + (DispProgressBar * 2) + 16, DispHeight - 25, 1, 11, 0x0000A8);
		DispFillRectangle(DispWidth / 2 - 100 + (DispProgressBar * 2) + 17, DispHeight - 24, 1, 9, 0x0000A8);
		DispProgressBar += 10;
	}
}

Void DispFillProgressBar(Void) {
	while (DispProgressBar < 100) {																								// Just fill the progress bar until it's 100%
		DispIncrementProgessBar();
	}
}

Void DispDrawProgessBar(Void) {
	DispDrawRoundedRectangle(DispWidth / 2 - 100, DispHeight - 30, 201, 21, 7, 0xFFFFFF);										// Draw the progress bar border
	DispWriteFormated(DispWidth / 2 - 56, 7, 0x000000, 0xFFFFFF, "Starting up...");												// And the "Starting..." text
	DispDrawBitmap(DispBootSplashImage, DispWidth / 2 - 150, DispHeight / 2 - 50);												// Draw the logo
}

Void DispPreInit(UIntPtr w, UIntPtr h, UIntPtr bpp) {
	if ((bpp != 3) && (bpp != 4)) {																								// For now, we only support True Color (... a lot of colors, 3 bytes per pixel) and True Color + ALPHA BLENDING! (... same as the True Color, but with one extra byte)
		DbgWriteFormated("PANIC! Couldn't init the display\r\n");
		while (1) ;
	}

	DispFrameBuffer = MmBootAlloc(w * h * bpp, True);																			// Alloc some virt space for the frame buffer
	DispWidth = w;
	DispHeight = h;
	DispBytesPerPixel = bpp;
}

Void DispInit(UIntPtr fb) {
	for (UIntPtr i = 0; i < DispWidth * DispHeight * DispBytesPerPixel; i += MM_PAGE_SIZE) {									// Let's map the frame buffer to the virtual memory!
		if (!MmMap(DispFrameBuffer + i, fb + i, MM_MAP_KDEF)) {
			DbgWriteFormated("PANIC! Couldn't init the display\r\n");
			while (1) ;
		}
	}
	
	StrSetMemory((PVoid)DispFrameBuffer, 0, DispWidth * DispHeight * DispBytesPerPixel);										// Clear the screen
}
