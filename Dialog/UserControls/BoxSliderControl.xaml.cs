using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WpfApp1.UserControls
{
    /// <summary>
    /// Interaction logic for BoxSliderControl.xaml
    /// </summary>
    public partial class BoxSliderControl : UserControl
    {
        public event EventHandler BoxSliderChanged;

        private void BoxSliderChangedFunc()
        {
            BoxSliderChanged?.Invoke(this, EventArgs.Empty);
        }

        public BoxSliderControl()
        {
            InitializeComponent();
        }

        public double SlideValue
        {
            get => Slider1.Value;
            set => Slider1.Value = value;
        }
        private void Slider1_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            NumBox1.Text = e.NewValue.ToString();
            BoxSliderChangedFunc();
        }

        private void Slider1_GotFocus(object sender, RoutedEventArgs e)
        {
            NumBox1.Text = Slider1.Value.ToString();
        }

        private void NumBox1_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (Double.TryParse(NumBox1.Text, out double myDouble))
            {
                Slider1.Value = myDouble;
                BoxSliderChangedFunc();
            }
            else if ((NumBox1.Text.Length != 0) /*|| !NumBox1.Text.EndsWith('.')*/)
            {
                _ = MessageBox.Show(new String("Use numbers only."), new String("Not a number"));
                NumBox1.Text = "";
            }
        }

        private void NumBox1_Initialized(object sender, EventArgs e)
        {
            NumBox1.Text = Slider1.Value.ToString();
        }

        private void NumBox1_LostFocus(object sender, RoutedEventArgs e)
        {
            NumBox1.Text = Slider1.Value.ToString();
        }
    }
}
