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

            redSlider.ValueChanged += RedSlider_ValueChanged;
            greenSlider.ValueChanged += GreenSlider_ValueChanged;
            blueSlider.ValueChanged += BlueSlider_ValueChanged;

            NativeMethods.SetClearColor((byte)redSlider.Value, (byte)greenSlider.Value, (byte)blueSlider.Value);
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

        private void RedSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            NativeMethods.SetClearColor((byte)e.NewValue, (byte)greenSlider.Value, (byte)blueSlider.Value);
            host.Child.Invalidate();
        }

        private void GreenSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            NativeMethods.SetClearColor((byte)redSlider.Value, (byte)e.NewValue, (byte)blueSlider.Value);
            host.Child.Invalidate();
        }

        private void BlueSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            NativeMethods.SetClearColor((byte)redSlider.Value, (byte)greenSlider.Value, (byte)e.NewValue);
            host.Child.Invalidate();
        }
    }
}
