#if !defined(__PSP_SCEGRAPHICS_H)
#define __PSP_SCEGRAPHICS_H

#include "Types.h"

tAsyncCall *Psp_SceGraphics_nativeInit(PTR pThis_, PTR pParams, PTR pReturnValue);
tAsyncCall *Psp_SceGraphics_nativeStartFrame(PTR pThis_, PTR pParams, PTR pReturnValue);
tAsyncCall *Psp_SceGraphics_nativeClear(PTR pThis_, PTR pParams, PTR pReturnValue);
tAsyncCall *Psp_SceGraphics_nativeEndFrame(PTR pThis_, PTR pParams, PTR pReturnValue);
tAsyncCall *Psp_SceGraphics_nativeTerminate(PTR pThis_, PTR pParams, PTR pReturnValue);

tAsyncCall *Psp_SceGraphics_nativeProjectionOrtho(PTR pThis_, PTR pParams, PTR pReturnValue);
tAsyncCall *Psp_SceGraphics_nativeDrawVertices(PTR pThis_, PTR pParams, PTR pReturnValue);

#endif