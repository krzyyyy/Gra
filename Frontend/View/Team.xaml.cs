using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Frontend.View
{
    /// <summary>
    /// Interaction logic for Team.xaml
    /// </summary>
    public partial class Team : UserControl
    {
        public Team()
        {
            InitializeComponent();
            //Image = new BitmapImage(new Uri("pack://application:,,,/Resources/Galadriela/background.jpg"));

        }
        public static readonly DependencyProperty ImageProperty = DependencyProperty.Register("Image", typeof(ImageSource), typeof(Team), new UIPropertyMetadata());
        public ImageSource Image
        {
            get { return (ImageSource)GetValue(ImageProperty); }
            set {
                SetValue(ImageProperty , value);
                

            }
        }
    }
}
