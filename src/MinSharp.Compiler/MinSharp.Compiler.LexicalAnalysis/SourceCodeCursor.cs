using MinSharp.Compiler.LexicalAnalysis.Model;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MinSharp.Compiler.LexicalAnalysis
{
    internal class SourceCodeCursor
    {
        private int currentCharacterIndex = 0;
        private int currentLineIndex = 0;
        private int currentColumnIndex = 0;


        /// <summary>
        /// Source Text.
        /// </summary>
        public SourceText SourceText { get; init; } = SourceText.Empty;

        /// <summary>
        /// Current Character.
        /// </summary>
        public char CurrentChar { get =>  SourceText.Text[currentCharacterIndex]; }

        /// <summary>
        /// Has More Characters To Process.
        /// </summary>
        public bool HasMoreCharatersToProcess { get => (currentCharacterIndex + 1) < SourceText.Text.Length; }

        /// <summary>
        /// Has More Charcaters To Process.
        /// </summary>
        public bool HasCurrentCharacter { get => currentCharacterIndex < SourceText.Text.Length; }

        /// <summary>
        /// Current Character Index.
        /// </summary>
        public int CurrentCharacterIndex { get => currentCharacterIndex; }

        /// <summary>
        /// Current Line Index
        /// </summary>
        public int CurrentLineIndex { get => currentLineIndex; set => currentLineIndex = value; }
        
        /// <summary>
        /// Current Column Index
        /// </summary>
        public int CurrentColumnIndex { get => currentColumnIndex; set => currentColumnIndex = value; }

        /// <summary>
        /// Next Character.
        /// </summary>
        public char NextCharacter 
        { 
            get 
            {
                if (currentCharacterIndex + 1 < SourceText.Text.Length) 
                {
                    return SourceText.Text[currentCharacterIndex + 1 ];
                }
                return '\0';
            } 
        }


        /// <summary>
        /// Moves to the next character
        /// </summary>
        /// <returns>True if the are more chacacters to process.</returns>
        public bool MoveNext(int numberOfCharactersToSkip =1)
        {
            while (numberOfCharactersToSkip > 0 && HasCurrentCharacter)
            {
                if (CurrentChar == '\n')
                {
                    currentLineIndex++;
                    currentColumnIndex = 0;
                }
                else
                {
                    currentColumnIndex++;
                }
                currentCharacterIndex++;
                numberOfCharactersToSkip--;
            }
            return HasCurrentCharacter;
        }


        public bool IsMatchAtCurrentCharacter(string stringToMatch)
        {
            for (int i =0;  i< stringToMatch.Length; i++)
            {
                if (currentCharacterIndex + i >= SourceText.Text.Length
                    || SourceText.Text[currentCharacterIndex + i ] != stringToMatch[i])
                {
                    return false;
                }
            }
            return true;
        }
    }
}
