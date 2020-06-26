using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ModelWrapper;
using Frontend.Models;

namespace Frontend.ViewModel
{
    public class MainViewModel
    {
        private CharacterModel character;
        public CharacterModel Character { get; set; }
        public MainViewModel()
        {
            Character = new CharacterModel();
            Character.Name = "adasdad";
        }
        //private WCharacter character;
        //public WCharacter Character
        //{
        //    get { return character; }
        //    set { character = value; }
        //}
    }
}
