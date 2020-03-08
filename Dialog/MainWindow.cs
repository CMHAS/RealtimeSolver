using System;
using System.Windows.Shapes;
using System.Windows;
using System.Windows.Media;
using System.Linq;

namespace WpfApp1
{
    public partial class MainWindow : Window
    {
        // Make lines and update times
        private void MakeLines(double[][] arr)
        {
            if (!(arr.Last()[0] > 0.0)) return;

            double scaleW = myCanvas.ActualWidth / arr.Last()[0];
            double scaleH = myCanvas.ActualHeight / 100.0;          // Scaled using max velocity 100m/s
            myTbTime.Text = TimeSpan.FromSeconds(arr.Last()[0]).ToString(@"hh\:mm\:ss\.ff");

            myCanvas.Children.Clear();
            for (int i = 0; i < (arr.Length - 1); ++i)
            {
                Line line = new Line
                {
                    X1 = arr[i][0] * scaleW,
                    Y1 = myCanvas.ActualHeight - arr[i][1] * scaleH,
                    X2 = arr[i + 1][0] * scaleW,
                    Y2 = myCanvas.ActualHeight - arr[i + 1][1] * scaleH,
                    ToolTip = "Vecocity",
                    Stroke = Brushes.Orange,
                    StrokeThickness = 4
                };
                if (line.Y1 > line.Y2)
                    line.Stroke = Brushes.Green;
                else if (line.Y1 < line.Y2)
                    line.Stroke = Brushes.Red;
                myCanvas.Children.Add(line);
            }
        }

    }
}
