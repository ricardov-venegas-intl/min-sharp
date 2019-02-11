﻿using System;
using System.Collections.Generic;
using System.Text;

namespace min_sharp_compiler.Types
{
    /// <summary>
    /// Types of tokens generated by the lexical analizer
    /// </summary>
    public enum TokenType
    {
        /// <summary>
        /// End of LIne
        /// </summary>
        LineTerminator=10,

        /// <summary>
        /// White space
        /// </summary>
        WhileSpace=11,

        /// <summary>
        /// Coment
        /// </summary>
        Comment=20,

        /// <summary>
        /// Identifier
        /// </summary>
        Identifier=100,

        /// <summary>
        /// Keyword
        /// </summary>
        Keyword=200,

        /// <summary>
        /// Number literal
        /// </summary>
        NumberLiteral =300,

        /// <summary>
        /// String Literal
        /// </summary>
        StringLiteral = 310,

        /// <summary>
        /// Operator
        /// </summary>
        Operator=400,

        /// <summary>
        /// Colon
        /// </summary>
        Colon=410,

        /// <summary>
        /// Semicolon
        /// </summary>
        SemiColon=420,

        /// <summary>
        /// Lexical Error
        /// </summary>
        Error=3000
    }
}