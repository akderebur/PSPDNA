using System.Runtime.CompilerServices;

namespace Psp
{
    public static class Display
    {
        public const float Width = 480;
        public const float Height = 272;

        [MethodImpl(MethodImplOptions.InternalCall)]
        extern public static int WaitVblankStart();
    }
}
