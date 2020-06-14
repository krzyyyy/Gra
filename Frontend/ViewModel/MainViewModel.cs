using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ModelWrapper;

namespace Frontend.ViewModel
{
    public class MainViewModel
    {
        public MainViewModel()
        {
            Character = new WCharacter();
        }
        private WCharacter character;
        public WCharacter Character
        {
            get { return character; }
            set { character = value; }
        }
    }
}
