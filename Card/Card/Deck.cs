using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CardLib
{
    public class Deck:ICloneable
    {
        public event EventHandler LastCardDrawn;
        public Card GetCard(int cardNum)
        {
            if (cardNum >= 0 && cardNum <= 51)
            {
                if ((cardNum == 51) && (LastCardDrawn != null))
                {
                    LastCardDrawn(this, EventArgs.Empty);
                }
                return cards[cardNum];
            }
            else throw new CardOutOfRangeException((Cards)cards.Clone());
        }

        private Deck(Cards newCards)
        {
            cards = newCards;
        }

        public object Clone()
        {
            Deck newDeck = new Deck(cards.Clone() as Cards);
            return newDeck;
        }
        public Deck(bool isAceHigh) : this()
        {
            Card.isAceHigh = isAceHigh;
        }

        public Deck(bool useTrump,Suit trump):this()
        {
            Card.useTrumps = useTrump;
            Card.trump = trump;
        }

        public Deck(bool isAceHigh,bool useTrump,Suit trump):this()
        {
            Card.isAceHigh = isAceHigh;
            Card.useTrumps = useTrump;
            Card.trump = trump;
        }

        private Cards cards = new Cards();
        public Deck()
        {
            for (int suitVal = 0; suitVal < 4; suitVal++)
            {
                for (int rankVal = 1; rankVal < 14; rankVal++)
                {
                    cards.Add(new Card((Suit)suitVal, (Rank)rankVal));
                }
            }
        }
       
        public void Shuffle()
        {
            Cards newDecks = new Cards();
            bool[] assigned = new bool[52];
            Random sourceGen = new Random();
            for (int i = 0; i < 52; i++)
            {
                int sourceCard = 0;
                bool foundCard = false;
                while (foundCard==false)
                {
                    sourceCard = sourceGen.Next(52);
                    if (assigned[sourceCard]==false)
                    {
                        foundCard = true;
                    }
                }
                assigned[sourceCard] = true;
                newDecks.Add(cards[sourceCard]);
            }
            newDecks.CopyTo(cards);
        }
    }
}
