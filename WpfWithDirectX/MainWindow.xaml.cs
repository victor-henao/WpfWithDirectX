using System;
using System.Runtime.InteropServices;
using System.Windows;

namespace WpfWithDirectX
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Control_HandleCreated(object sender, EventArgs e)
        {
            InitializeDirect3D9(((System.Windows.Forms.Control)sender).Handle);
        }

        private void Control_Paint(object sender, System.Windows.Forms.PaintEventArgs e)
        {
            RenderDirect3D9();
        }

        protected override void OnClosed(EventArgs e)
        {
            CleanDirect3D9();
            base.OnClosed(e);
        }

        [DllImport("WpfWithDirectX.Rendering.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void InitializeDirect3D9(IntPtr windowHandle);

        [DllImport("WpfWithDirectX.Rendering.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void RenderDirect3D9();

        [DllImport("WpfWithDirectX.Rendering.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void ResizeDirect3D9Viewport(uint width, uint height);

        [DllImport("WpfWithDirectX.Rendering.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void CleanDirect3D9();

        private void Control_SizeChanged(object sender, EventArgs e)
        {
            var control = (System.Windows.Forms.Control)sender;
            uint width = (uint)control.Size.Width;
            uint height = (uint)control.Size.Height;
            ResizeDirect3D9Viewport(width, height);
        }
    }
}
