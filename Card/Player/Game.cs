using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CardLib;
using static System.Console;
namespace Player
{
    public class Game
    {
        private int currentCard;
        private Deck playDeck;
        private Player[] players;
        private Cards discardedCards;
        public Game()
        {
            currentCard = 0;
            playDeck = new Deck(true);
            playDeck.LastCardDrawn += Reshuffle;
            playDeck.Shuffle();
            discardedCards = new Cards();
        }
        private void Reshuffle(object source,EventArgs args)
        {
            WriteLine("Discarded cards reshuffled into deck");
            ((Deck)source).Shuffle();
            discardedCards.Clear();
            currentCard = 0;
        }
        public void SetPlayers(Player[] newPlayers)
        {
            if (newPlayers.Length>7)
               throw new ArgumentException("A maximum of 7 players may play this game");
            if (newPlayers.Length < 2)
               throw new ArgumentException("A minimum of 2 players may play this game");
            players = newPlayers;            
        }
        private void DealHands()
        {
            for (int p = 0; p < players.Length; p++)
            {
                for (int c = 0; c < 7; c++)
                {
                    players[p].PlayHand.Add(playDeck.GetCard(currentCard++));
                }
            }
        }
        public int playGame()
        {
            //Only play if players exit
            if (players==null)
            {
                return -1;
            }
            //Deal initial hands
            DealHands();
            //Initialize game vars,includeing an initial card to place on
            //the table :playCard
            bool gameWon = false;
            int currentPlayer;
            Card playCard = playDeck.GetCard(currentCard++);
            discardedCards.Add(playCard);
            //Main game loop, cintinues until GameWon == true;
            do
            {
                //Loop through players in each game round
                for (currentPlayer = 0; currentPlayer < players.Length; currentPlayer++)
                {
                    WriteLine($"{players[currentPlayer].Name}'s turn");
                    WriteLine("Current hand: ");
                    foreach (Card card in players[currentPlayer].PlayHand)
                    {
                        WriteLine(card);
                    }
                    WriteLine($"Card in play: {playCard}");

                    bool inputOk = false;
                    do
                    {
                        WriteLine("Please T to take in play or D to draw:");
                        string input = ReadLine();
                        if (input.ToLower() == "t")
                        {
                            WriteLine($"Drawn :{playCard}");
                            if (discardedCards.Contains(playCard))
                            {
                                discardedCards.Remove(playCard);
                            }
                            players[currentPlayer].PlayHand.Add(playCard);
                            inputOk = true;
                        }
                        if (input.ToLower() == "d")
                        {
                            Card newCard;
                            bool cardIsAvailable;
                            do
                            {
                                newCard = playDeck.GetCard(currentCard++);
                                cardIsAvailable = !discardedCards.Contains(newCard);
                                if (cardIsAvailable)
                                {
                                    foreach (Player textplayer in players)
                                    {
                                        if (textplayer.PlayHand.Contains(newCard))
                                        {
                                            //如果这张牌已经在手牌中就退出
                                            cardIsAvailable = false;
                                            break;
                                        }
                                    }
                                }
                            } while (!cardIsAvailable);
                            //Add the card found to player hand
                            WriteLine($"Drawn: {newCard}");
                            players[currentPlayer].PlayHand.Add(newCard);
                            inputOk = true;
                        }
                    } while (inputOk == false);
                    //Display new hand with cards number
                    WriteLine("New hand");
                    for (int i = 0; i < players[currentPlayer].PlayHand.Count; i++)
                    {
                        WriteLine($"{i + 1}" +
                            $"{players[currentPlayer].PlayHand[i]}");
                    }
                    inputOk = false;
                    int choice = -1;
                    do
                    {
                        WriteLine("Choose card to discard");
                        string input = ReadLine();
                        try
                        {
                            choice = Convert.ToInt32(input);
                            if (choice > 0 && choice <= 8)
                                inputOk = true;
                        }
                        catch
                        {
                            //Ignore failed conversions ,just continue prompting
                        }
                    } while (inputOk == false);
                    playCard = players[currentPlayer].PlayHand[choice - 1];
                    players[currentPlayer].PlayHand.RemoveAt(choice - 1);
                    discardedCards.Add(playCard);
                    WriteLine($"Discarding : {playCard}");
                    WriteLine();
                    gameWon = players[currentPlayer].HasWon();
                    if (gameWon == true)
                    {
                        break;
                    }
                }
            } while (gameWon == false);
            return currentPlayer;
        }
    }
}
