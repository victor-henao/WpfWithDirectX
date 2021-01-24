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

        void Slider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            NativeMethods.SetTriangleRotation((float)e.NewValue);
            host.Child.Invalidate();
        }
    }
}
