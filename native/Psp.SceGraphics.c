#include "Compat.h"
#include "Sys.h"
#include "System.Array.h"

#include "Psp.SceGraphics.h"

#if defined(__PSP__)
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>
#endif

// Adapted from https://github.com/IridescentRose/PSP-GPU-Tutorials/
// Changed depth test to LEQUAL

// Define PSP Width / Height
#define PSP_BUF_WIDTH (512)
#define PSP_SCR_WIDTH (480)
#define PSP_SCR_HEIGHT (272)

static unsigned int __attribute__((aligned(16))) list[262144];

// Get Memory Size
static unsigned int getMemorySize(unsigned int width, unsigned int height, unsigned int psm)
{
	switch (psm)
	{
		case GU_PSM_T4:
			return (width * height) >> 1;

		case GU_PSM_T8:
			return width * height;

		case GU_PSM_5650:
		case GU_PSM_5551:
		case GU_PSM_4444:
		case GU_PSM_T16:
			return 2 * width * height;

		case GU_PSM_8888:
		case GU_PSM_T32:
			return 4 * width * height;

		default:
			return 0;
	}
}

// Vram Buffer Request
void* getStaticVramBuffer(unsigned int width, unsigned int height, unsigned int psm)
{
	static unsigned int staticOffset = 0;
	unsigned int memSize = getMemorySize(width,height,psm);
	void* result = (void*)staticOffset;
	staticOffset += memSize;

	return result;
}

// Vram Texture Request
void* getStaticVramTexture(unsigned int width, unsigned int height, unsigned int psm)
{
	void* result = getStaticVramBuffer(width,height,psm);
	return (void*)(((unsigned int)result) + ((unsigned int)sceGeEdramGetAddr()));
}

tAsyncCall *Psp_SceGraphics_nativeInit(PTR pThis_, PTR pParams, PTR pReturnValue)
{
    void* fbp0 = getStaticVramBuffer(PSP_BUF_WIDTH,PSP_SCR_HEIGHT,GU_PSM_8888);
	void* fbp1 = getStaticVramBuffer(PSP_BUF_WIDTH,PSP_SCR_HEIGHT,GU_PSM_8888);
	void* zbp = getStaticVramBuffer(PSP_BUF_WIDTH,PSP_SCR_HEIGHT,GU_PSM_4444);

	sceGuInit();

	sceGuStart(GU_DIRECT,list);
	sceGuDrawBuffer(GU_PSM_8888,fbp0,PSP_BUF_WIDTH);
	sceGuDispBuffer(PSP_SCR_WIDTH,PSP_SCR_HEIGHT,fbp1,PSP_BUF_WIDTH);
	sceGuDepthBuffer(zbp,PSP_BUF_WIDTH);
	sceGuOffset(2048 - (PSP_SCR_WIDTH/2),2048 - (PSP_SCR_HEIGHT/2));
	sceGuViewport(2048,2048,PSP_SCR_WIDTH,PSP_SCR_HEIGHT);
	sceGuDepthRange(0,65535);
	sceGuClearDepth(65535);
	sceGuScissor(0,0,PSP_SCR_WIDTH,PSP_SCR_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuDepthFunc(GU_LEQUAL);
	sceGuEnable(GU_DEPTH_TEST);
	sceGuFrontFace(GU_CW);
	sceGuShadeModel(GU_SMOOTH);
	sceGuEnable(GU_CULL_FACE);
	sceGuEnable(GU_TEXTURE_2D);
	sceGuEnable(GU_CLIP_PLANES);
	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);

	sceGumMatrixMode(GU_PROJECTION);
    sceGumLoadIdentity();

    sceGumMatrixMode(GU_VIEW);
    sceGumLoadIdentity();

    sceGumMatrixMode(GU_MODEL);
    sceGumLoadIdentity();

    return NULL;
}

tAsyncCall *Psp_SceGraphics_nativeStartFrame(PTR pThis_, PTR pParams, PTR pReturnValue)
{
	sceGuStart(GU_DIRECT, list);

	// TODO: Texturing support
    sceGuDisable(GU_TEXTURE_2D);
	
	return NULL;
}

tAsyncCall *Psp_SceGraphics_nativeClear(PTR pThis_, PTR pParams, PTR pReturnValue)
{
    U32 color = INTERNALCALL_PARAM(0, U32);

	sceGuClearColor(color);
	sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT | GU_STENCIL_BUFFER_BIT);

    return NULL;
}

tAsyncCall *Psp_SceGraphics_nativeEndFrame(PTR pThis_, PTR pParams, PTR pReturnValue)
{
	sceGuFinish();
    sceGuSync(0, 0);
    sceDisplayWaitVblankStart();
	sceGuSwapBuffers();

	return NULL;
}

tAsyncCall *Psp_SceGraphics_nativeTerminate(PTR pThis_, PTR pParams, PTR pReturnValue)
{
	sceGuTerm();
    return NULL;
}

tAsyncCall *Psp_SceGraphics_nativeProjectionOrtho(PTR pThis_, PTR pParams, PTR pReturnValue)
{
 	float left = ((float *)pParams)[0];
    float right = ((float *)pParams)[1];
    float bottom = ((float *)pParams)[2];
    float top = ((float *)pParams)[3];
    float near = ((float *)pParams)[4];
    float far = ((float *)pParams)[5];

	sceGumMatrixMode(GU_PROJECTION);
    sceGumLoadIdentity();
    sceGumOrtho(left, right, bottom, top, near, far);

	return NULL;
}

tAsyncCall *Psp_SceGraphics_nativeDrawVertices(PTR pThis_, PTR pParams, PTR pReturnValue)
{
	HEAP_PTR vertexArray = ((HEAP_PTR*)pParams)[0];
	int vertexCount =  ((int*)pParams)[1];

    PTR pFirstElement = SystemArray_LoadElementAddress(vertexArray, 0);

	sceGumDrawArray(GU_TRIANGLES, GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_3D, vertexCount, NULL, pFirstElement);

	return NULL;
}


