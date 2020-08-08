using GalaSoft.MvvmLight;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Frontend.Models;
using System;
using GalaSoft.MvvmLight.Command;
using Frontend.View;

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
        /// 
        public RelayCommand LoadCharacter { get; set; }


        private BitmapSource image;
        public BitmapSource Image
        {
            get { return image; }
            set { image = value;
                RaisePropertyChanged(() => Image);
            }
        }
        private CharacterImagesModel characterImages;
        public CharacterImagesModel CharacterImages
        {
            get { return characterImages; }
            set
            {
                characterImages = value;
                RaisePropertyChanged(() => CharacterImages);
            }
        }
        private CharacterModel characterModel;
        public CharacterModel CharacterModel
        {
            get { return characterModel; }
            set { characterModel = value; RaisePropertyChanged(() => CharacterModel); }
        }
        private BitmapSource img;
        public BitmapSource Img
        {
            get { return img; }
            set { img = value; RaisePropertyChanged(() => Img); }
        }
        private string hh;
        public string HH
        {
            get { return hh; }
            set { hh = value; 
                RaisePropertyChanged(() => HH); }
        }
        public MainViewModel()
        {
            //var path = new Uri("pack://application:,,,/Resources/Galadriela/background.jpg");

            //Image = new BitmapImage(path);
            CharacterImages = new CharacterImagesModel("Galadriela");
            CharacterModel = new CharacterModel
            {
                Live = 200,
                Concentration = 100,
                LiveMax = 200,
                ConcentrationMax = 200,
                Name = "Galadriela"
            };
            var path = new Uri("C:/Users/Krzysztof/source/repos/Gra/Frontend/Resources/" + "Galadriela");
            var chracterPath = new Uri(path + "/character.jpg");
            Img = new BitmapImage(chracterPath);
            HH = "asdasd";
            LoadCharacter = new RelayCommand( () =>
            {
                CharacterImages = new CharacterImagesModel("Galadriela");
                CharacterModel = new CharacterModel
                {
                    Live = 200,
                    Concentration = 100,
                    LiveMax = 200,
                    ConcentrationMax = 200,
                    Name = "Galadriela"
                };
            });
        }
    }
}