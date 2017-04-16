using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CardLib;
using static System.Console;
namespace Player
{
    class Program
    {
        static void Main(string[] args)
        {
            WriteLine("BenjaminCards : a new and exciting card game.");
            WriteLine("To win ypu must have 7 cards of the some suit in" +
                "your hand");
            WriteLine();
            bool isPutOK = false;
            int choice = -1;
            do
            {
                WriteLine("How many players(2 -7)");
                string input = ReadLine();
                try
                {
                    choice = Convert.ToInt32(input);
                    if ((choice >= 2) && (choice <= 7))
                        isPutOK = true;
                }
                catch 
                {
                    //Ignore failed conversions,just contiune prompting
                }
            } while (isPutOK==false);
            Player[] players = new Player[choice];
            for (int p = 0; p < players.Length; p++)
            {
                WriteLine($"player{p + 1},enter your name");
                string playerName = ReadLine();
                players[p] = new Player(playerName);
            }
            Game newGame = new Game();
            newGame.SetPlayers(players);
            int whoWon = newGame.playGame();
            WriteLine($"{players[whoWon].Name} has won the game");
            ReadKey();
        }
    }
}
