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

            positionSlider.ValueChanged += PositionSlider_ValueChanged;
            scaleSlider.ValueChanged += ScaleSlider_ValueChanged;
            rotationSlider.ValueChanged += RotationSlider_ValueChanged;
        }

        private void PositionSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            NativeMethods.SetCirclePosition((float)e.NewValue);
            host.Child.Invalidate();
        }

        private void ScaleSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            NativeMethods.SetCircleScale((float)e.NewValue);
            host.Child.Invalidate();
        }

        private void RotationSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            NativeMethods.SetCircleRotation((float)e.NewValue);
            host.Child.Invalidate();
        }
    }
}
