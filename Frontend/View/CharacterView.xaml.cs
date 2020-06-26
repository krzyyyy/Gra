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
        public CharacterView()
        {
            InitializeComponent();
        }
        public static readonly DependencyProperty ImageProperty = DependencyProperty.Register("Image", typeof(BitmapImage), typeof(CharacterView), new PropertyMetadata(new BitmapImage()));
        public BitmapImage Image
        {
            get { return (BitmapImage)GetValue(ImageProperty); }
            set { SetValue(ImageProperty, value); }
        }
        public static readonly DependencyProperty CharacterProperty = DependencyProperty.Register("Character", typeof(CharacterModel), typeof(CharacterView), new PropertyMetadata(null));
        public CharacterModel Character
        {
            get { return (CharacterModel)GetValue(CharacterProperty); }
            set { SetValue(CharacterProperty, value); }
        }
    }
}
