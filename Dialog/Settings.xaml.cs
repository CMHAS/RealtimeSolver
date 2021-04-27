using System;
using System.Windows;
using ClrClassLib;
using WpfApp1.UserControls;

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for Settings.xaml
    /// </summary>
    public partial class Settings : Window
    {
        private readonly Class1 class1 = new();
        public delegate void PointsChangedHandler(double[][] arr);
        public event PointsChangedHandler PointsChanged;

        public Settings()
        {
            InitializeComponent();
        }

        ~Settings()
        {
            class1.Dispose();
        }

        private void BoxSlider1_BoxSliderChanged(object sender, EventArgs e)
        {
            PointsChanged(class1.setStart(BoxSlider1.SlideValue));
        }

        private void BoxSlider2_BoxSliderChanged(object sender, EventArgs e)
        {
            PointsChanged(class1.setCruise(BoxSlider2.SlideValue));
        }

        private void BoxSlider3_BoxSliderChanged(object sender, EventArgs e)
        {
            PointsChanged(class1.setEnd(BoxSlider3.SlideValue));
        }

        private void BoxSlider4_BoxSliderChanged(object sender, EventArgs e)
        {
            PointsChanged(class1.setDist(BoxSlider4.SlideValue));
        }

        private void BoxSlider5_BoxSliderChanged(object sender, EventArgs e)
        {
            PointsChanged(class1.setAcc(BoxSlider5.SlideValue));
        }

        private void BoxSlider6_BoxSliderChanged(object sender, EventArgs e)
        {
            PointsChanged(class1.setRet(BoxSlider6.SlideValue));
        }

        private void BoxSlider2_Loaded(object sender, RoutedEventArgs e)
        {
            BoxSlider2.Slider1.Minimum = 1.0;
            BoxSlider2.SlideValue = 25.0;
        }

        private void BoxSlider4_Loaded(object sender, RoutedEventArgs e)
        {
            BoxSlider4.Slider1.Minimum = 1.0;
            BoxSlider4.Slider1.Maximum = 1000.0;
            BoxSlider4.SlideValue = 500.0;
        }

        private void BoxSlider5and6_Loaded(object sender, RoutedEventArgs e)
        {
            BoxSliderControl boxSliderControl = sender as BoxSliderControl;
            boxSliderControl.Slider1.Minimum = 1.0;
            boxSliderControl.Slider1.Maximum = 20.0;
            boxSliderControl.SlideValue = 5.0;
        }

        private void Closing_Settings(object sender, System.ComponentModel.CancelEventArgs e)
        {
            Settings settings = sender as Settings;
            settings.Hide();
            e.Cancel = true;
        }
    }
}
