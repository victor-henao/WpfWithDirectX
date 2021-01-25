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

        private void PositionSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            NativeMethods.SetTrianglePosition((float)e.NewValue);
            host.Child.Invalidate();
        }

        private void RotationSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            NativeMethods.SetTriangleRotation((float)e.NewValue);
            host.Child.Invalidate();
        }

        private void ScaleSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            NativeMethods.SetTriangleScale((float)e.NewValue);
            host.Child.Invalidate();
        }
    }
}
