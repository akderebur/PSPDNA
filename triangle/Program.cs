using Psp;

namespace triangle
{
    class Program
    {
        static void Main()
        {
            SceGraphics.Init();

            // Pixel size divided by 2 and 100
            float extentX = Display.Width * 0.005f; 
            float extentY = Display.Height * 0.005f;

            SceGraphics.ProjectionOrtho(extentX * -1f, extentX, extentY * -1f, extentY, -10f, 10f);

            PspVertex[] triangle = new PspVertex[3]
            {
                new PspVertex(0xFF00FF00, 0.5f, -0.5f, 0.0f),
                new PspVertex(0xFF0000FF, -0.5f, -0.5f, 0.0f),
                new PspVertex(0xFFFF0000, 0.0f, 0.5f, 0.0f)
            };

            while (State.IsRunning())
            {
                SceGraphics.StartFrame();
                SceGraphics.Clear(Color.Black);
                SceGraphics.DrawVertices(triangle, 3);
                SceGraphics.EndFrame();
            }

            SceGraphics.Terminate();
        }
    }
}
