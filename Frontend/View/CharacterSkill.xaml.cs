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
    /// Interaction logic for CharacterSkill.xaml
    /// </summary>
    public partial class CharacterSkill : UserControl
    {
        public CharacterSkill()
        {
            InitializeComponent();
        }

        public static readonly DependencyProperty ImageProperty = DependencyProperty.Register("Image", typeof(BitmapImage), typeof(CharacterSkill), new PropertyMetadata(new BitmapImage()));
        public BitmapImage Image
        {
            get { return (BitmapImage)GetValue(ImageProperty); }
            set { SetValue(ImageProperty, value); }
        }

        //public static readonly DependencyProperty HeaderProperty = DependencyProperty.Register("Header", typeof(string), typeof(FFStatisticsGrid), new PropertyMetadata(""));
        //public string Header
        //{
        //    get { return (string)GetValue(HeaderProperty); }
        //    set { SetValue(HeaderProperty, value); }
        //}
    }

}
