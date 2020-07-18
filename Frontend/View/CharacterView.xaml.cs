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
        public static readonly DependencyProperty BackgroundImageProperty = DependencyProperty.Register("BackgroundImage", typeof(BitmapSource), typeof(CharacterView), new FrameworkPropertyMetadata(null));
        public BitmapSource BackgroundImage
        {
            get { return GetValue(BackgroundImageProperty) as BitmapSource; }
            set { SetValue(BackgroundImageProperty, value); }
        }
        public static readonly DependencyProperty CharacterProperty = DependencyProperty.Register("Character", typeof(CharacterModel), typeof(CharacterView), new PropertyMetadata(null));
        public CharacterModel Character
        {
            get { return (CharacterModel)GetValue(CharacterProperty); }
            set { 
                SetValue(CharacterProperty, value);
            }
        }
    }
}
