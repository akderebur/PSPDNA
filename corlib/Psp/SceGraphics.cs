using System.Runtime.CompilerServices;

namespace Psp
{
    public static class SceGraphics
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        extern public static void Init();

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern public static void StartFrame();

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern static void SceClear(uint color);

        public static void Clear(Color color)
        {
            SceClear(color.ToNative());
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern public static void EndFrame();

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern public static void Terminate();

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern public static void ProjectionOrtho(float left, float right, float bottom, float top, float near, float far);

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern public static void DrawVertices(PspVertex[] vertices, int vertexCount);
    }
}
