using System;
using System.Windows;
using System.Windows.Threading;

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
            var timer = new DispatcherTimer
            {
                Interval = TimeSpan.FromSeconds(1 / 60)
            };
            timer.Tick += Timer_Tick;
            timer.Start();
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            //throw new NotImplementedException();
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
