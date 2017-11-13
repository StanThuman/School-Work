/* Arkansas State University
 * CS 4-5133 Compilers
 * Dr. Jeff Jenness
 * 2015-07-05
 *
 * token.h
 */
#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <stdio.h>
#include <string.h>
#include "messages.h"

#define attriblen 256

typedef enum {
	// errors
    errBuffOverflow = -1, /* scanner buffer overflow */
    errBadInput     = -2, /* unknown character in input stream */
    errBadString    = -3,	/* bad form for string literal */
    errBadFloat     = -4,	/* bad form for float literal */
    errBadComment   = -5,	/* unterminated comment */
    // tokens
    tokEOF = 0,			/* End-Of-File marker */
    tokIDENT,				/* identifier */
    // literals
    litFLOAT,				/* float number literal */
    litINT,					/* int number literal */
    litSTRING,			/* string literal */
    // keywords
    kwELSE,
	  kwEXTERN,
    kwFLOAT,
    kwIF,
    kwINT,
    kwRETURN,
    kwVOID,
    kwWHILE,
    // special symbols
    symCOMMA,				/* , */
    symSEMI,				/* ; */
    symOPEN,				/* ( */
    symCLOSE,				/* ) */
    symASSIGN,			/* = */
    symPLUS,				/* + */
    symMINUS,				/* - */
    symMUL,					/* * */
    symDIV,					/* / */
    symMOD,					/* % */
    symEQUAL,				/* == */
    symNOTEQ,				/* != */
    symLESS,				/* < */
    symGREATER,			/* > */
    symLESSEQ,			/* <= */
    symGREATEREQ,		/* >= */
    symAND,					/* && */
    symOR,					/* || */
    symNOT,					/* ! */
    symSQOPEN,			/* [ */
    symSQCLOSE,			/* ] */
    symBROPEN,			/* { */
    symBRCLOSE			/* } */
} tokenType;

typedef struct {
    tokenType token;      // the actual token value
    char attrib[attriblen];  // the lexeme attribute
    int row, col;         // row and column of the lexeme
} token;

extern const char* tokenTypeString[];

const char *tokenString(token t);    // this is the object properties/methods for Lexeme
char *setAttrib(token *t, char *s);

#endif
