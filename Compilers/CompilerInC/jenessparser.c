/* Arkansas State University
 * CS 4-5133 Compilers
 * Dr. Jeff Jenness
 * 2015-07-05
 *
 * parser.c
 */
#include "parser.h"

static void resynchronize(tokenType* syncSet);

static token lookAhead;
static symtab* symbols;

void parserInit(FILE *fin) {
	scannerInit(fin);
    message(DEBUG, "parser: initialized");
}

static token getToken() {
	token t = scannerRead();
	while (t.token < 0) {
		message(ERROR, "line %i: col %i: scanner: %s", t.row, t.col, scannerError(t));
		t = scannerRead();
	}
	return t;
}

static void match(tokenType expected) {
    message(DEBUG, "parser: match: expecting %s", tokenTypeString[expected]);
    if (lookAhead.token == expected)
        lookAhead = getToken();
    else {
        message(ERROR, "line %i: col %i: parser: expecting %s: found %s",
            lookAhead.row, lookAhead.col, tokenTypeString[expected], tokenTypeString[lookAhead.token]);
		// lookAhead = getToken();
	}
}

static bool memberOf(tokenType element, tokenType* set) {
	bool found = false;
	int i = 0;
	while (!found && set[i] > 0)
		found = (element == set[i++]);
    return found;
}

static bool synchronized(tokenType* firstSet, tokenType* followSet, char* errMsg) {
	message(DEBUG, "parser: synchronize: %s", errMsg);
	bool synced = true;
  if (!memberOf(lookAhead.token, firstSet)) {
	message(DEBUG, "parser: synchronize: could not find %s", tokenTypeString[lookAhead.token]);
      message(ERROR, "line %i: col %i: parser: %s: found %s",
      	lookAhead.row, lookAhead.col, errMsg, tokenTypeString[lookAhead.token]);
  	while (lookAhead.token != tokEOF && !memberOf(lookAhead.token, firstSet) && !memberOf(lookAhead.token, followSet))
      	lookAhead = scannerRead();
		if (!memberOf(lookAhead.token, firstSet))
				synced = false;
  }
	return synced;
}

static void resynchronize(tokenType* syncSet) {
	while (lookAhead.token != tokEOF && !memberOf(lookAhead.token, syncSet))
        lookAhead = scannerRead();
}

/* prototypes for all grammar non-terminals functions (local) */
static void TranslationUnit();
static char* TypeSpecifier();
static void Parameter();
static void CompoundStatement(char *f);
static void Declaration();
static void Statement(char *f);
static void ExpressionStatement();
static void SelectionStatement(char *f);
static void RepetitionStatement(char *f);
static void ReturnStatement(char *f);
static char* Expression();
static char* AndExpression();
static char* RelationExpression();
static char* SimpleExpression();
static char* Term();
static char* Factor();
static char* Value();

bool parserRead() {  // Augmented Rule for grammar
	symbols = symtabInit();

	lookAhead = getToken();
    TranslationUnit();
    match(tokEOF);

	symtabFree(symbols);
    return (errorCount == 0);
}

static void TranslationUnit() {
	message(DEBUG, "parser: in TranslationUnit()");

	bool externDef;
	char type1[DEFLEN];
	char func[SYMLEN];
	if (synchronized(firstSet[nTranslationUnit], followSet[nTranslationUnit], "expecting type specifier")) {
 	  while (memberOf(lookAhead.token, firstSet[nTranslationUnit])) {
		externDef = false;
		if (lookAhead.token == kwEXTERN) {
			match(kwEXTERN);
			externDef = true;
		}
		strcpy(TypeSpecifier(), type1);
		if (lookAhead.token == tokIDENT) {
			if (!Define(symbols, lookAhead.attrib, type1))
				message(ERROR, "line %i: col %i: identifier \"%s\" already found in scope",
					lookAhead.row, lookAhead.col, lookAhead.attrib);
			strcpy(func, lookAhead.attrib);
		}
		match(tokIDENT);
		symtabDump(symbols);
        if (lookAhead.token == symSQOPEN || lookAhead.token == symCOMMA || lookAhead.token == symSEMI) {
            if (lookAhead.token == symSQOPEN) {
                match(symSQOPEN);
                match(litINT);
                match(symSQCLOSE);
            }
            while (lookAhead.token == symCOMMA) {
                match(symCOMMA);
				match(tokIDENT);
                if (lookAhead.token == symSQOPEN) {
                    match(symSQOPEN);
                    match(litINT);
                    match(symSQCLOSE);
                }
            }
            match(symSEMI);
        } else if (lookAhead.token == symOPEN) {
			openScope(symbols);
            match(symOPEN);
            if (memberOf(lookAhead.token, firstSet[nParameter])) {
                Parameter();
                while (lookAhead.token == symCOMMA) {
                    match(symCOMMA);
                    Parameter();
                }
            }
            match(symCLOSE);
			if (lookAhead.token == symBROPEN) {
				CompoundStatement(func);
			} else if (lookAhead.token == symSEMI)
				match(symSEMI);
			else
				message(ERROR, "expecting semicolon or function body");
			closeScope(symbols);
		}
	  }
	}
}

static char* TypeSpecifier() {
    message(DEBUG, "parser: in TypeSpecifier()");

	static char type[DEFLEN] = "\0\0";
	if (synchronized(firstSet[nTypeSpecifier], followSet[nTypeSpecifier], "expecting type specifier")) {
		if (lookAhead.token == kwINT) {
			match(kwINT);
			type[0] = 'i';
		} else if (lookAhead.token == kwFLOAT) {
			match(kwFLOAT);
			type[0] = 'f';
		} else if (lookAhead.token == kwVOID) {
			match(kwVOID);
			type[0] = 'v';
		}
	}
	return type;
}

static void Parameter() {
    message(DEBUG, "parser: in Parameter()");

    if (synchronized(firstSet[nParameter], followSet[nParameter], "expecting formal parameter")) {
        TypeSpecifier();
		match(tokIDENT);
        if (lookAhead.token == symSQOPEN) {
            match(symSQOPEN);
            match(symSQCLOSE);
        }
    }
}

static void CompoundStatement(char *f) {
    message(DEBUG, "parser: in CompoundStatement()");

		if (synchronized(firstSet[nCompoundStatement], followSet[nCompoundStatement], "expecting compound statement")) {
			match(symBROPEN);
			while (memberOf(lookAhead.token, firstSet[nDeclaration]) || memberOf(lookAhead.token, firstSet[nStatement])) {
				if (memberOf(lookAhead.token, firstSet[nDeclaration])) {
					Declaration();
				} else if (memberOf(lookAhead.token, firstSet[nStatement])) {
					Statement(f);
				}
			}
			match(symBRCLOSE);
	    }
}

static void Declaration() {
    message(DEBUG, "parser: in Declaration()");

    if (synchronized(firstSet[nDeclaration], followSet[nDeclaration], "expecting variable declaration")) {
        TypeSpecifier();
		match(tokIDENT);
        if (lookAhead.token == symSQOPEN) {
            match(symSQOPEN);
            match(litINT);
            match(symSQCLOSE);
        }
        while (lookAhead.token == symCOMMA) {
            match(symCOMMA);
			match(tokIDENT);
            if (lookAhead.token == symSQOPEN) {
                match(symSQOPEN);
                match(litINT);
                match(symSQCLOSE);
            }
        }
				match(symSEMI);
    }
}

static void Statement(char *f) {
    message(DEBUG, "parser: in Statement()");

		if (synchronized(firstSet[nStatement], followSet[nStatement], "expecting statement")) {
			if (memberOf(lookAhead.token, firstSet[nExpressionStatement])) {
				ExpressionStatement();
			} else if (lookAhead.token == symBROPEN) {
				openScope(symbols);
				CompoundStatement(f);
				closeScope(symbols);
			} else if (lookAhead.token == kwIF) {
				SelectionStatement(f);
			} else if (lookAhead.token == kwWHILE) {
				RepetitionStatement(f);
			} else if (lookAhead.token == kwRETURN) {
				ReturnStatement(f);
			}
		}
}

static void ExpressionStatement() {
    message(DEBUG, "parser: in ExpressionStatement()");

    if (synchronized(firstSet[nExpressionStatement], followSet[nExpressionStatement], "expecting an expression statement")) {
        if (memberOf(lookAhead.token, firstSet[nExpression])) {
            Expression();
            if (lookAhead.token == symASSIGN) {
                match(symASSIGN);
                Expression();
            }
        }
        match(symSEMI);
    }
}

static void SelectionStatement(char *f) {
    message(DEBUG, "parser: in SelectionStatement()");

	if (synchronized(firstSet[nSelectionStatement], followSet[nSelectionStatement], "expecting a conditional statement")) {
		match(kwIF);
		match(symOPEN);
		Expression();
		match(symCLOSE);
		Statement(f);
		if (lookAhead.token == kwELSE) {
			match(kwELSE);
			Statement(f);
		}
	}
}

static void RepetitionStatement(char *f) {
    message(DEBUG, "parser: in RepetitionStatement()");

    if (synchronized(firstSet[nRepetitionStatement], followSet[nRepetitionStatement], "expecting a repetition statement")) {
        match(kwWHILE);
        match(symOPEN);
        Expression();
        match(symCLOSE);
        Statement(f);
    }
}

static void ReturnStatement(char *f) {
    message(DEBUG, "parser: in ReturnStatement()");

	if (synchronized(firstSet[nReturnStatement], followSet[nReturnStatement], "expecting a return statement")) {
        match(kwRETURN);
        if (memberOf(lookAhead.token, firstSet[nExpression])) {
            Expression();
        }
        match(symSEMI);
    }
}

static char* Expression() {
	message(DEBUG, "parser: in Expression()");

	static char type[DEFLEN];
	if (synchronized(firstSet[nExpression], followSet[nExpression], "expecting an expression")) {
		AndExpression();
		while (lookAhead.token == symOR) {
				match(symOR);
				AndExpression();
		}
	}
	return type;
}

static char* AndExpression() {
	message(DEBUG, "parser: in AndExpression()");

	static char type[DEFLEN];
	if (synchronized(firstSet[nAndExpression], followSet[nAndExpression], "expecting an conjuctive expression")) {
			RelationExpression();
			while (lookAhead.token == symAND) {
					match(symAND);
					RelationExpression();
			}
	}
	return type;
}

static char* RelationExpression() {
    message(DEBUG, "parser: in RelationExpression()");

	static char type[DEFLEN];
	static tokenType relationOps[] = { symEQUAL, symNOTEQ, symLESS, symLESSEQ, symGREATER, symGREATEREQ, (tokenType)-1 };
	if (synchronized(firstSet[nRelationExpression], followSet[nRelationExpression], "expecting an relational expression")) {
        SimpleExpression();
        if (memberOf(lookAhead.token, relationOps)) {
            match(lookAhead.token);
            SimpleExpression();
        }
    }
	return type;
}

static char* SimpleExpression() {
    message(DEBUG, "parser: in SimpleExpression()");

	static char type[DEFLEN];
	if (synchronized(firstSet[nSimpleExpression], followSet[nSimpleExpression], "expecting an additive expression")) {
        Term();
        while (lookAhead.token == symPLUS || lookAhead.token == symMINUS) {
            match(lookAhead.token);
            Term();
        }
    }
	return type;
}

static char* Term() {
    message(DEBUG, "parser: in Term()");

	static char type[DEFLEN];
	if (synchronized(firstSet[nTerm], followSet[nTerm], "expecting an multiplicative expression")) {
        Factor();
        while (lookAhead.token == symMUL || lookAhead.token == symDIV || lookAhead.token == symMOD) {
            match(lookAhead.token);
            Factor();
        }
    }
	return type;
}

static char* Factor() {
	message(DEBUG, "parser: in Factor()");

	static char type[DEFLEN];
	if (synchronized(firstSet[nFactor], followSet[nFactor], "expecting an value expression")) {
		while (lookAhead.token == symPLUS || lookAhead.token == symMINUS)
			match(lookAhead.token);
		Value();
	}
	return type;
}

static char* Value() {
    message(DEBUG, "parser: in Value()");

	static char type[DEFLEN];
	if (synchronized(firstSet[nValue], followSet[nValue], "expecting an value")) {
        if (lookAhead.token == symOPEN) {
            match(symOPEN);
            Expression();
            match(symCLOSE);
        } else if (lookAhead.token == tokIDENT) {
			match(tokIDENT);
            if (lookAhead.token == symSQOPEN) {
                match(symSQOPEN);
                Expression();
                match(symSQCLOSE);
            } else if (lookAhead.token == symOPEN) {
                match(symOPEN);
				if (memberOf(lookAhead.token, firstSet[nExpression])) {
	                Expression();
	                while (lookAhead.token == symCOMMA) {
	                    match(symCOMMA);
	                    Expression();
	                }
				}
                match(symCLOSE);
            }
        } else if (lookAhead.token == litINT) {
            match(litINT);
        } else if (lookAhead.token == litFLOAT) {
            match(litFLOAT);
        } else if (lookAhead.token == litSTRING) {
            match(litSTRING);
        }
    }
	return type;
}
