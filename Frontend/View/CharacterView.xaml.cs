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
using Frontend.Models;

namespace Frontend.View
{
    /// <summary>
    /// Interaction logic for CharacterView.xaml
    /// </summary>
    public partial class CharacterView : UserControl
    {
        //public CharacterView()
        //{
        //    InitializeComponent();
        //}

        //public static readonly DependencyProperty ImageSourceProperty =
        //    DependencyProperty.Register("ImageSource",
        //    typeof(ImageSource), typeof(CharacterView), new FrameworkPropertyMetadata(null));
        //public ImageSource Image
        //{
        //    get { return GetValue(ImageSourceProperty) as ImageSource; }
        //    set { SetValue(ImageSourceProperty, value); }
        //}

        //public static readonly DependencyProperty CommandProperty =
        //    DependencyProperty.Register("Command",
        //    typeof(ICommand), typeof(CharacterView),
        //    new FrameworkPropertyMetadata(null));
        //public ICommand Command
        //{
        //    get { return GetValue(CommandProperty) as ICommand; }
        //    set { SetValue(CommandProperty, value); }
        //}

        public static readonly DependencyProperty StatisticsProperty = DependencyProperty.Register("Statistics",
    typeof(String), typeof(CharacterView), new PropertyMetadata());


        public String Statistics
        {
            get { return (String)GetValue(StatisticsProperty); }
            set { SetValue(StatisticsProperty, value); }
        }
    }
}
