/* Arkansas State University
 * CS 4-5133 Compilers
 * Dr. Jeff Jenness
 * 2015-07-05
 *
 * token.c
 */
#include "token.h"

#define maxlen 256

const char* tokenTypeString[] = {
	"end-of-file",
	"identifier",
	"float literal",
	"int literal",
	"string literal",
  "keyword else",
	"keyword extern",
  "keyword float",
  "keyword if",
  "keyword int",
  "keyword return",
  "keyword void",
  "keyword while",
  "symbol \",\"",
  "symbol \";\"",
  "symbol \"(\"",
  "symbol \")\"",
  "symbol \"=\"",
  "symbol \"+\"",
  "symbol \"-\"",
  "symbol \"*\"",
	"symbol \"/\"",
	"symbol \"%\"",
  "symbol \"==\"",
  "symbol \"!=\"",
  "symbol \"<\"",
  "symbol \">\"",
  "symbol \"<=\"",
  "symbol \">=\"",
  "symbol \"&&\"",
  "symbol \"||\"",
  "symbol \"!\"",
  "symbol \"[\"",
  "symbol \"]\"",
  "symbol \"{\"",
  "symbol \"}\""
};

const char *tokenString(token t) {
    static char _token_buff[maxlen];

    const char format_s[] = "<%s(%d,%d):%s>";
    const char format_ss[] = "<%s(%d,%d):%s(%s)>";

    char temp[11];

    switch (t.token) {
			  case errBuffOverflow:
						strncpy(temp, t.attrib, 10);
						temp[10] = '\0';
						sprintf(_token_buff, "<ERROR(%d,%d): buffer overflowed on input beginning with: \"%s...\">", t.row, t.col, temp);
						break;
        case errBadInput:
            sprintf(_token_buff, "<ERROR(%d,%d): unrecognized character in input: found ENCODING(0x%x)>", t.row, t.col, t.attrib[0]);
            break;
        case errBadString:
            strncpy(temp, t.attrib, 10);
            temp[10] = '\0';
            sprintf(_token_buff, "<ERROR(%d,%d): unterminated string: %s%s%s%s: found end-of-line>", t.row, t.col, strlen(temp)>0?"beginning with \"":"", strlen(temp)>0?temp:"empty string", strlen(t.attrib)>10?"...":"", strlen(temp)>0?"\"":"");
            break;
        case errBadFloat:
            sprintf(_token_buff, "<ERROR(%d,%d): incorrect real format: missing exponent: found \"%s\">", t.row, t.col, t.attrib);
            break;
        case errBadComment:
            sprintf(_token_buff, format_s, "ERROR", t.row, t.col, " unterminated comment: found end-of-file");
            break;
        case tokEOF:
            sprintf(_token_buff, "<EOF>");
            break;
        case tokIDENT:
            sprintf(_token_buff, "<IDENT(%d,%d):\"%s\">", t.row, t.col, t.attrib);
            break;
        case litFLOAT:
            sprintf(_token_buff, format_ss, "LITERAL", t.row, t.col, "REAL", t.attrib);
            break;
        case litINT:
            sprintf(_token_buff, format_ss, "LITERAL", t.row, t.col, "INTEGER", t.attrib);
            break;
        case litSTRING:
            sprintf(_token_buff, "<%s(%d,%d):%s(\"%s\")>", "LITERAL", t.row, t.col, "STRING", t.attrib);
            break;
        case kwELSE:
            sprintf(_token_buff, format_s, "KEYWORD", t.row, t.col, "else");
            break;
        case kwEXTERN:
            sprintf(_token_buff, format_s, "KEYWORD", t.row, t.col, "extern");
            break;
        case kwFLOAT:
            sprintf(_token_buff, format_s, "KEYWORD", t.row, t.col, "float");
            break;
        case kwIF:
            sprintf(_token_buff, format_s, "KEYWORD", t.row, t.col, "if");
            break;
        case kwINT:
            sprintf(_token_buff, format_s, "KEYWORD", t.row, t.col, "int");
            break;
        case kwRETURN:
            sprintf(_token_buff, format_s, "KEYWORD", t.row, t.col, "return");
            break;
        case kwVOID:
            sprintf(_token_buff, format_s, "KEYWORD", t.row, t.col, "void");
            break;
        case kwWHILE:
            sprintf(_token_buff, format_s, "KEYWORD", t.row, t.col, "while");
            break;
        case symCOMMA:
            sprintf(_token_buff, format_s, "SYMBOL", t.row, t.col, "','");
            break;
        case symSEMI:
            sprintf(_token_buff, format_s, "SYMBOL", t.row, t.col, "';'");
            break;
        case symOPEN:
            sprintf(_token_buff, format_s, "SYMBOL", t.row, t.col, "'('");
            break;
        case symCLOSE:
            sprintf(_token_buff, format_s, "SYMBOL", t.row, t.col, "')'");
            break;
        case symASSIGN:
            sprintf(_token_buff, format_s, "SYMBOL", t.row, t.col, "'='");
            break;
        case symPLUS:
            sprintf(_token_buff, format_s, "SYMBOL", t.row, t.col, "'+'");
            break;
        case symMINUS:
            sprintf(_token_buff, format_s, "SYMBOL", t.row, t.col, "'-'");
            break;
        case symMUL:
            sprintf(_token_buff, format_s, "SYMBOL", t.row, t.col, "'*'");
            break;
				case symDIV:
            sprintf(_token_buff, format_s, "SYMBOL", t.row, t.col, "'/'");
            break;
				case symMOD:
            sprintf(_token_buff, format_s, "SYMBOL", t.row, t.col, "'%'");
            break;
        case symEQUAL:
            sprintf(_token_buff, format_s, "SYMBOL", t.row, t.col, "'=='");
            break;
        case symNOTEQ:
            sprintf(_token_buff, format_s, "SYMBOL", t.row, t.col, "'!='");
            break;
        case symLESS:
            sprintf(_token_buff, format_s, "SYMBOL", t.row, t.col, "'<'");
            break;
        case symGREATER:
            sprintf(_token_buff, format_s, "SYMBOL", t.row, t.col, "'>'");
            break;
        case symLESSEQ:
            sprintf(_token_buff, format_s, "SYMBOL", t.row, t.col, "'<='");
            break;
        case symGREATEREQ:
            sprintf(_token_buff, format_s, "SYMBOL", t.row, t.col, "'>='");
            break;
        case symAND:
            sprintf(_token_buff, format_s, "SYMBOL", t.row, t.col, "'&&'");
            break;
        case symOR:
            sprintf(_token_buff, format_s, "SYMBOL", t.row, t.col, "'||'");
            break;
        case symNOT:
            sprintf(_token_buff, format_s, "SYMBOL", t.row, t.col, "'!'");
            break;
        case symSQOPEN:
            sprintf(_token_buff, format_s, "SYMBOL", t.row, t.col, "'['");
            break;
        case symSQCLOSE:
            sprintf(_token_buff, format_s, "SYMBOL", t.row, t.col, "']'");
            break;
        case symBROPEN:
            sprintf(_token_buff, format_s, "SYMBOL", t.row, t.col, "'{'");
            break;
        case symBRCLOSE:
            sprintf(_token_buff, format_s, "SYMBOL", t.row, t.col, "'}'");
            break;
        default:
            sprintf(_token_buff, "<ERROR: unrecognized token value: %d>", t.token);
    }
    return _token_buff;
}

char *setAttrib(token *t, char *s) {
    strncpy(t->attrib, s, attriblen-1);
    t->attrib[attriblen-1] = '\0';
    return t->attrib;
}
