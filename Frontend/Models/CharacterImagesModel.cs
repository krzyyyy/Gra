using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace Frontend.Models
{
    public class CharacterImagesModel
    {
        public CharacterImagesModel()
        {

        }
        public CharacterImagesModel(string characterFolder)
        {
            var path = new Uri("C:/Users/Krzysztof/source/repos/Gra/Frontend/Resources/" + characterFolder);
            var chracterPath = new Uri(path + "/character.jpg");
            var backgroundPath = new Uri(path + "/background.jpg");
            CharacterImage = new BitmapImage(chracterPath);
            BackgroundImage = new BitmapImage(backgroundPath);
        }
        public BitmapImage CharacterImage { get; set; }
        public BitmapImage BackgroundImage { get; set; }
        public List<BitmapSource> SkilsImages { get; set; }
    }
}
