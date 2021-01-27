using System;
using System.Runtime.InteropServices;

namespace WpfWithDirectX
{
    static class NativeMethods
    {
        [DllImport("WpfWithDirectX.Rendering.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void InitializeDirect3D9(IntPtr windowHandle, uint width, uint height);

        [DllImport("WpfWithDirectX.Rendering.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RenderDirect3D9();

        [DllImport("WpfWithDirectX.Rendering.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetClearColor(byte r, byte g, byte b);

        [DllImport("WpfWithDirectX.Rendering.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetCirclePosition(float value);

        [DllImport("WpfWithDirectX.Rendering.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetCircleScale(float value);

        [DllImport("WpfWithDirectX.Rendering.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetCircleRotation(float value);

        [DllImport("WpfWithDirectX.Rendering.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ResizeDirect3D9Viewport(uint width, uint height);

        [DllImport("WpfWithDirectX.Rendering.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void CleanDirect3D9();
    }
}
