using System;
using System.Windows.Forms;

namespace WpfWithDirectX
{
    public partial class RenderControl : UserControl
    {
        public RenderControl()
        {
            InitializeComponent();
        }

        protected override void CreateHandle()
        {
            base.CreateHandle();
            NativeMethods.InitializeDirect3D9(Handle, (uint)Size.Width, (uint)Size.Height);
        }

        protected override void OnResize(EventArgs e)
        {
            NativeMethods.ResizeDirect3D9Viewport((uint)Size.Width, (uint)Size.Height);
            base.OnResize(e);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            NativeMethods.RenderDirect3D9();
            //base.OnPaint(e);
        }

        protected override void OnPaintBackground(PaintEventArgs e)
        {
            //base.OnPaintBackground(e);
        }

        protected override void DestroyHandle()
        {
            NativeMethods.CleanDirect3D9();
            base.DestroyHandle();
        }
    }
}
