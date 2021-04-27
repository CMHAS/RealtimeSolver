using System;
using System.Windows;
using System.Windows.Shapes;

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        // Instantiate the dialog box
        private readonly Settings dlg = new() { };
        public MainWindow()
        {
            InitializeComponent();
        }

        private void About_Click(object sender, RoutedEventArgs e)
        {
            _ = MessageBox.Show(new String("Copyright Magnus Hermansson AS"), new String("About"));
        }

        private void Inputs_Click(object sender, RoutedEventArgs e)
        {
            dlg.Show();
        }

        private void Dlg_PointsChanged(double[][] arr)
        {
            this.MakeLines(arr);
        }

        private void Canvas_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            static double reCalcLine(double x, bool isChanged, double pre, double post)
            {
                return isChanged ? x * post / pre : x;
            }
            if (IsLoaded)
            {
                System.Collections.IEnumerator enumerator = myCanvas.Children.GetEnumerator();
                while (enumerator.MoveNext())
                { 
                    Line line = (Line)enumerator.Current;
                    line.X1 = reCalcLine(line.X1, e.WidthChanged, e.PreviousSize.Width, e.NewSize.Width);
                    line.Y1 = reCalcLine(line.Y1, e.HeightChanged, e.PreviousSize.Height, e.NewSize.Height);
                    line.X2 = reCalcLine(line.X2, e.WidthChanged, e.PreviousSize.Width, e.NewSize.Width);
                    line.Y2 = reCalcLine(line.Y2, e.HeightChanged, e.PreviousSize.Height, e.NewSize.Height);
                }
            }
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            // Configure the dialog box
            dlg.Owner = this;
            dlg.PointsChanged += new Settings.PointsChangedHandler(Dlg_PointsChanged);
        }
    }
}
