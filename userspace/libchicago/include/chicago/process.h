// File author is Ítalo Lima Marconato Matias
//
// Created on October 29 of 2018, at 19:12 BRT
// Last edited on December 24 of 2019, at 13:47 BRT

#ifndef __CHICAGO_PROCESS_H__
#define __CHICAGO_PROCESS_H__

#include <chicago/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

IntPtr PsCreateThread(UIntPtr entry);
IntPtr PsGetCurrentThread(Void);
IntPtr PsGetCurrentProcess(Void);
Void PsSleep(UIntPtr ms);
UIntPtr PsWait(IntPtr handle);
IntPtr PsCreateLock(Void);
Void PsLock(IntPtr lock);
Void PsUnlock(IntPtr lock);
Void PsExitThread(UIntPtr ret);
Void PsExitProcess(UIntPtr ret);

#ifdef __cplusplus
}
#endif

#endif		// __CHICAGO_PROCESS_H__
