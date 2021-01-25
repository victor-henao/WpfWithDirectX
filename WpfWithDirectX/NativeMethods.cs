using System;
using System.Runtime.InteropServices;

namespace WpfWithDirectX
{
    static class NativeMethods
    {
        [DllImport("WpfWithDirectX.Rendering.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void InitializeDirect3D9(IntPtr windowHandle);

        [DllImport("WpfWithDirectX.Rendering.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RenderDirect3D9();

        [DllImport("WpfWithDirectX.Rendering.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetTrianglePosition(float value);

        [DllImport("WpfWithDirectX.Rendering.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetTriangleRotation(float value);

        [DllImport("WpfWithDirectX.Rendering.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetTriangleScale(float value);

        [DllImport("WpfWithDirectX.Rendering.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ResizeDirect3D9Viewport(uint width, uint height);

        [DllImport("WpfWithDirectX.Rendering.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void CleanDirect3D9();
    }
}
