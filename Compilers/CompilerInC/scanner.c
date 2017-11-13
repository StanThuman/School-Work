/* Arkansas State University
 * CS 4-5133 Compilers
 * Dr. Jeff Jenness
 * 2015-07-05
 *
 * scanner.c
 */
#include "scanner.h"

FILE *input;
int row, col;
token t;
char buff[bufflen];
int tabwidth;

int KWidx[] = { 2, 7, 4, 5, 0, 3, 6, 1, 8 };

char *KWstr[] = { "", "else", "extern", "float", "if",
                  "int", "return", "void", "while" };

tokenType KWtok[] = { tokIDENT, kwELSE, kwEXTERN, kwFLOAT, kwIF,
                      kwINT, kwRETURN, kwVOID, kwWHILE };

static int KWhash(char *s) {
    int len = strlen(s);
    int c1 = (int)s[0], c2 = (int)(len>1?s[1]:s[0]), c3 = (int)s[len-1];
    return (len + 6*c1 + 9*c2 + 18*c3) % 9;
}

static tokenType KWsearch(char *s) {
    message(DEBUG, "KWsearch: keyword search for: '%s'", s);

    int h = KWhash(s);
    message(DEBUG, "hash: keyword hash value = %i", h);
    message(DEBUG, "hash: keyword index value = %i", KWidx[h]);
    message(DEBUG, "hash: matching to keyword \"%s\"", KWstr[KWidx[h]]);
    if (strcmp(KWstr[KWidx[h]], s) == 0)
        return KWtok[KWidx[h]];
    else
        return KWtok[0];
}

//TODO: buffer overflow error detection
static void strnapp(char *s, char c, int n) {
    int len = strlen(s);
    if (len < n-1) {
        s[len] = c;
        s[len+1] = '\0';
    } else {
      t.token = errBuffOverflow;
    }
}

static int peekCh() {
	int c;
	if (feof(input))
		c = -1;
	else {
		c = getc(input);//gets current char from input fstream
		ungetc(c, input); //put back char into the stream
	}
	return c;
}

static int nextCh() {
    int c;
    if (feof(input))
        c = -1;
    else {
        c = getc(input);
        strnapp(buff, (char)c, bufflen);
        if (c == '\r' || c == '\n') { // Mac or Unix EOL
            if (c == '\r' && peekCh() == '\n') // DOS style EOL
                c = getc(input);
            ++row;
            col = 0;
        } else if (c == '\t')
            col = col/tabwidth * tabwidth + tabwidth;  // calculate the tab column
        else
            ++col;
    }
    return c;
}

void scannerInit(FILE *fin) {
    input = fin;
    row = 1; col = 0;  // index of current character
    buff[0] = '\0';
    tabwidth = DEFtabwidth;

    message(DEBUG, "scanner: initialized");
}

int setTabWidth(int t) {
    message(DEBUG, "scanner: setting TabWidth to %i", t);
    return tabwidth = t<1?DEFtabwidth:t;
}

int getTabWidth() {
    return tabwidth;
}

int getLinesRead() {
	return row - 1;
}

token scannerRead() {
    int c;

    c = nextCh();

    //checks for comments
    while (isspace((char)c) || ((char)c == '/' && (peekCh() == '*' || peekCh() == '/'))) {
        if (c == '/' && peekCh() == '*') { // found multi-line comment
            t.row = row; t.col = col;  // helps to find unterminated comments
            c = nextCh();
            while ((c = nextCh()) >= 0) { // short-circuit nextCh()
                if (c == '*' && peekCh() == '/') {
                    c = nextCh();
                    break;
                }
            }
            if (c < 0) { // should not be EOF
                t.token = errBadComment;
                setAttrib(&t, buff);
                return t;
            }
        } else if (c == '/' && peekCh() == '/') { // found single-line comment
            c = nextCh();
            while ((c = nextCh()) >= 0) { // exit on end-of-file
                if (c == '\n' || c == '\r') { // exit on end-of-line
                    break;
                }
            }
        }
        c = nextCh();
    } //end while loop

    t.row = row; t.col = col;     // record location of lexeme
    message(DEBUG, "scanner: next character '%c'", c);

    if (c < 0)
        t.token = tokEOF;
    else {
        buff[0] = '\0';            // initialize the buffer
        strnapp(buff, (char)c, bufflen);
        if (isalpha((char)c) || (char)c == '_') {
            message(DEBUG, "scanner: processing identifier");
            while ((c = peekCh()) == '_' || isalnum((char)c))
                c = nextCh();
            if (t.token != errBuffOverflow)
              t.token = KWsearch(buff);
        } else if (isdigit((char)c) || (char)c == '.') {
            message(DEBUG, "scanner: processing number");
            if ((char)c == '.') {
              if (!isdigit((char)peekCh())) {
                  t.token = errBadInput;
                  setAttrib(&t, buff);
                  return t;
              }
              while (isdigit((char)peekCh()))
                  c = nextCh();
              if (tolower((char)peekCh()) == 'e') {
                  c = nextCh();
                  if ((char)peekCh() == '+' || (char)peekCh() == '-')
                      c = nextCh();
                  if (!isdigit((char)peekCh())) {
                      t.token = errBadFloat;
                      setAttrib(&t, buff);
                      return t;
                  }
                  while (isdigit((char)peekCh()))
                      c = nextCh();
              }
              if (t.token != errBadInput && t.token != errBuffOverflow)
                t.token = litFLOAT;
            } else {
              while (isdigit((char)peekCh()))
                c = nextCh();
              if (peekCh() == '.') {
                  c = nextCh();
                  while (isdigit((char)peekCh()))
                      c = nextCh();
                  if (tolower((char)peekCh()) == 'e') {
                      c = nextCh();
                      if ((char)peekCh() == '+' || (char)peekCh() == '-')
                          c = nextCh();
                      if (!isdigit((char)peekCh())) {
                          t.token = errBadFloat;
                          setAttrib(&t, buff);
                          return t;
                      }
                      while (isdigit((char)peekCh()))
                          c = nextCh();
                  }
                  if (t.token != errBuffOverflow)
                    t.token = litFLOAT;
              } else {
                if (t.token != errBuffOverflow)
                  t.token = litINT;
              }
            }
        } else if (c == '"') {
            message(DEBUG, "scanner: processing string");
            buff[0] = '\0';  // remove the beginning quote from buffer
            while ((c = nextCh()) != '"') {
                if (c < 0 || c == '\n' || c == '\r') {
                    t.token = errBadString;
                    buff[strlen(buff)-1] = '\0';
                    setAttrib(&t, buff);
                    return t;
                }
            }
            buff[strlen(buff)-1] = '\0';  // remove the ending quote from buffer
            if (t.token != errBuffOverflow)
              t.token = litSTRING;
        } else if (c == ',') {
            t.token = symCOMMA;
        } else if (c == '=') {
            if (peekCh() == '=') {
                c = nextCh();
                t.token = symEQUAL;
            } else
                t.token = symASSIGN;
        } else if (c == ';') {
            t.token = symSEMI;
        } else if (c == '(') {
            t.token = symOPEN;
        } else if (c == ')') {
            t.token = symCLOSE;
        } else if (c == '+') {
            t.token = symPLUS;
        } else if (c == '-') {
            t.token = symMINUS;
        } else if (c == '*') {
            t.token = symMUL;
        } else if (c == '/') {
            t.token = symDIV;
        } else if (c == '%') {
            t.token = symMOD;
        } else if (c == '!') {
            if (peekCh() == '=') {
                c = nextCh();
                t.token = symNOTEQ;
            } else
                t.token = symNOT;
        } else if (c == '<') {
            if (peekCh() == '=') {
                c = nextCh();
                t.token = symLESSEQ;
            } else
                t.token = symLESS;
        } else if (c == '>') {
            if (peekCh() == '=') {
                c = nextCh();
                t.token = symGREATEREQ;
            } else
                t.token = symGREATER;
        } else if (c == '&') {
            if (peekCh() == '&') {
                c = nextCh();
                t.token = symAND;
            } else
                t.token = errBadInput;
        } else if (c == '|') {
            if (peekCh() == '|') {
                c = nextCh();
                t.token = symOR;
            } else
                t.token = errBadInput;
        } else if (c == '[') {
            t.token = symSQOPEN;
        } else if (c == ']') {
            t.token = symSQCLOSE;
        } else if (c == '{') {
            t.token = symBROPEN;
        } else if (c == '}') {
            t.token = symBRCLOSE;
        } else {
            t.token = errBadInput;
        }
        setAttrib(&t, buff);
    }

    message(DEBUG, "scanner: found %s", t.token>=0?tokenTypeString[t.token]:"an error!");
    return t;
}

const char *scannerError(token t) {
	static char *msg;

	switch (t.token) {
    case errBuffOverflow:
        msg = "buffer overflow";
        break;
		case errBadInput:
				msg = "unrecognized input character";
				break;
		case errBadString:
				msg = "unterminated string literal";
				break;
		case errBadFloat:
				msg = "unrecognized float literal";
				break;
		case errBadComment:
				msg = "unterminated comment";
				break;
		default:
				msg = "unknown error code";
	}

	return msg;
}
