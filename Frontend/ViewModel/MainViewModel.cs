using GalaSoft.MvvmLight;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System;

namespace Frontend.ViewModel
{
    /// <summary>
    /// This class contains properties that the main View can data bind to.
    /// <para>
    /// Use the <strong>mvvminpc</strong> snippet to add bindable properties to this ViewModel.
    /// </para>
    /// <para>
    /// You can also use Blend to data bind with the tool's support.
    /// </para>
    /// <para>
    /// See http://www.galasoft.ch/mvvm
    /// </para>
    /// </summary>
    public class MainViewModel : ViewModelBase
    {
        /// <summary>
        /// Initializes a new instance of the MainViewModel class.
        /// </summary>
        private BitmapSource image;
        public BitmapSource Image
        {
            get { return image; }
            set { image = value;
                RaisePropertyChanged(() => Image);
            }
        }
        public MainViewModel()
        {
            var path = new Uri("pack://application:,,,/Resources/Galadriela/background.jpg");
            Image = new BitmapImage(path);
        }
    }
}