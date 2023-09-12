namespace Psp
{
    public struct PspVertex
    {
        public uint Color;
        public float X;
        public float Y;
        public float Z;

        public PspVertex(uint color, float x, float y, float z)
        {
            Color = color;
            X = x;
            Y = y;
            Z = z;
        }
    }
}
