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
        public BitmapSource CharacterImage { get; set; }
        public BitmapSource BackgroundImage { get; set; }
        public List<BitmapSource> SkilsImages { get; set; }
    }
}
