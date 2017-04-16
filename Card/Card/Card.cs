using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CardLib
{
  
    public class Card:ICloneable
    {

        public static bool useTrumps = false;
        public static Suit trump = Suit.Club;
        public static bool isAceHigh = true;
 
        public readonly Suit suit;
        public readonly Rank rank;
        public Card(Suit newSuit,Rank newRank)
        {
            suit = newSuit;
            rank = newRank;
        }
        private Card()
        { }
        public override string ToString()
        {
            return "The " + rank + " of " + suit + "s";
        }

        public object Clone() => MemberwiseClone();

        //运算符重载
        public static bool operator ==(Card card1,Card card2)
        =>(card1?.suit==card2?.suit)&&(card1?.rank==card2?.rank);
        public static bool operator !=(Card card1,Card card2)
        =>(card1?.suit!=card2?.suit)||(card1?.rank!=card2?.rank);
        public override bool Equals(object card)
        {
            return this == (Card)card;
        }
        public override int GetHashCode()
        {
            return 13 * (int)suit + (int)rank;
        }

        public static bool operator >(Card card1,Card card2)
        {
            if (card1.suit == card2.suit)
            {
                if (isAceHigh)
                {
                    if (card1.rank == Rank.Ace)
                    {
                        if (card2.rank == Rank.Ace)
                        {
                            return false;
                        }
                        else return true;
                    }
                    else
                    {
                        if (card1.rank == Rank.Ace)
                        {
                            return false;
                        }
                        else return (card1.rank > card2.rank);
                    }
                }
                else return (card1.rank > card2.rank);
            }
            else
            {
                if (useTrumps && (card2.suit == Card.trump))
                {
                    return false;
                }
                else return true;
            }
        }

        public static bool operator <(Card card1,Card card2)=>!(card1>card2);
        public static bool operator >=(Card card1,Card card2)
        {
            if (card1.suit==card2.suit)
            {
                if (isAceHigh)
                {
                    if (card1.rank == Rank.Ace)
                    {
                        return true;
                    }
                    else
                    {
                        if (card2.rank == Rank.Ace)
                        {
                            return false;
                        }
                        else return (card1.rank > card2.rank);
                    }
                }
                else return (card1.rank >= card2.rank);
            }
            else
            {
                if (useTrumps && (card2.suit == Card.trump))
                {
                    return false;
                }
                else return true;
            }
        }
        public static bool operator <=(Card card1 ,Card card2)
        {
            return !(card1 > card2);
        }
    }
}
