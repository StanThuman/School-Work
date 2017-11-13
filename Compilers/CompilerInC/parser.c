/* Arkansas State University
* CS 4-5133 Compilers
* Dr. Jeff Jenness
* 2015-07-05
*
* parser.c
*/
#include "parser.h"

static token lookAhead;

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
	}
}

static bool memberOf(tokenType element, tokenType* set) {
	bool found = false;
	int i = 0;
	while (!found && set[i] > 0)
		found = (element == set[i++]);

	return found;
}

//static void synchronize(tokenType* firstSet, tokenType* followSet, char* errMsg) {
//	message(DEBUG, "parser: synchronize: %s", errMsg);
//	if (!memberOf(lookAhead.token, firstSet)) {
//		message(DEBUG, "parser: synchronize: could not find %s", tokenTypeString[lookAhead.token]);
//		message(ERROR, "line %i: col %i: parser: %s: found %s",
//				lookAhead.row, lookAhead.col, errMsg, tokenTypeString[lookAhead.token]);
//		while (lookAhead.token != tokEOF && !memberOf(lookAhead.token, firstSet) && !memberOf(lookAhead.token, followSet))
//			lookAhead = scannerRead();
//	}
//}
static bool synchronize(tokenType* firstSet, tokenType* followSet, char* errMsg) {
	message(DEBUG, "parser: synchronize: %s", errMsg);
	bool synced = true;
	if (!memberOf(lookAhead.token, firstSet)) {
		message(DEBUG, "parser: synchronize: could not find %s",
				tokenTypeString[lookAhead.token]);
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
static void TypeSpecifier();
static void Parameter();
static void CompoundStatement();
static void Declaration();
static void Statement();
static void ExpressionStatement();
static void SelectionStatement();
static void RepetitionStatement();
static void ReturnStatement();
static void Expression();
static void AndExpression();
static void RelationExpression();
static void SimpleExpression();
static void Term();
static void Factor();
static void Value();

static void isArray();

// add the rest here

bool parserRead() {  // Augmented Rule for grammar
	lookAhead = getToken();
	TranslationUnit();

	//printf("Tokens are : %s",tokenString(lookAhead));
	// add augmented rule here
	/*do {
		t = scannerRead();
		if (t.token < 0) ++errorCount;
		printf("%s\n", tokenString(t));
	} while (t.token != tokEOF);*/


	return (errorCount == 0);
}

// sample parse function with firstSet
static void TranslationUnit() {

	message(DEBUG, "parser: in TranslationUnit()\n");

	// fill in with tokens, -1 must be the last one!
	static tokenType firstSet[] = { kwEXTERN, kwINT, kwFLOAT, kwVOID, (tokenType)-1 };
	static tokenType followSet[] = { tokIDENT, tokEOF, (tokenType)-1 };

	// fill in the rule here
	//while(lookAhead.token == kwEXTERN || lookAhead.token == kwINT || lookAhead.token == kwFLOAT || lookAhead.token == kwVOID){
	
	while (synchronize(firstSet, followSet, "End of File")){		
		if (lookAhead.token == kwEXTERN){
			match(kwEXTERN);			
		}

		TypeSpecifier();

		if (lookAhead.token == tokIDENT){
			match(tokIDENT);			
		} else{
			message(PANIC, "NO identifier detected...\n");
		}


		if (lookAhead.token == symSQOPEN || lookAhead.token == symCOMMA || lookAhead.token == symOPEN){
			//array check
			isArray();

			//continuous loop if multiple declarations following a comma
			while (lookAhead.token == symCOMMA){
				if (lookAhead.token == symCOMMA){
					match(symCOMMA);
					if (lookAhead.token == tokIDENT){
						match(tokIDENT);
						isArray();
					}
				}
			}//end while

			if (lookAhead.token == symSEMI){
				match(symSEMI);
			}

			if (lookAhead.token == symOPEN){
				match(symOPEN);

				if (lookAhead.token == kwINT || lookAhead.token == kwFLOAT || lookAhead.token == kwVOID){
					Parameter();

					while (lookAhead.token == symCOMMA){
						match(symCOMMA);
						Parameter();
					}
				}

				if (lookAhead.token == symCLOSE)
					match(symCLOSE);
			}

			if (lookAhead.token == symBROPEN || lookAhead.token == symSEMI){

				if (lookAhead.token == symBROPEN){
					match(symBROPEN);
					CompoundStatement();
				}

				if (lookAhead.token == symSEMI)
					match(symSEMI);

			}

			/*if (lookAhead.token == symSEMI){
				match(symSEMI);
			}*/
		}
	}//end while	
	
}

static void TypeSpecifier(){
	bool checkForOnceType = false;
	static tokenType firstSet[] = { kwINT, kwFLOAT, kwVOID, (tokenType)-1 };
	static tokenType followSet[] ={tokIDENT, (tokenType)-1};

	if (synchronize(firstSet, followSet, "No Type Found\n")){

		if (lookAhead.token == kwINT && checkForOnceType == false){
			match(kwINT);
			checkForOnceType = true;			
		}

		if (lookAhead.token == kwFLOAT && checkForOnceType == false){
			match(kwFLOAT);
			checkForOnceType = true;			
		}

		if (lookAhead.token == kwVOID && checkForOnceType == false){
			match(kwVOID);
			checkForOnceType = true;			
		}
	}
}

static void Parameter(){

	static tokenType firstSet[] = { kwINT, kwFLOAT, kwVOID, (tokenType)-1 };
	static tokenType followSet[] = { tokIDENT, symCOMMA, symCLOSE, (tokenType)-1 };
	bool checkForOne = false;
	//while (lookAhead.token == kwINT || lookAhead.token == kwFLOAT || lookAhead.token == kwVOID){
	if(synchronize(firstSet, followSet, "No Type Specifier found\n")){
		if (lookAhead.token == kwINT){
			match(kwINT);
			checkForOne = true;
			if (lookAhead.token == symCOMMA){
				match(symCOMMA);
			}
		}
		if (lookAhead.token == kwFLOAT){
			match(kwFLOAT);
			checkForOne = true;
			if (lookAhead.token == symCOMMA){
				match(symCOMMA);
			}
		}
		
		if (lookAhead.token == kwVOID){
			match(kwVOID);
			checkForOne = true;
			if (lookAhead.token == symCOMMA){
				match(symCOMMA);
			}
		}

		if(lookAhead.token == symSQOPEN  && checkForOne == true){
			match(symSQOPEN);
			if(lookAhead.token == symSQCLOSE)
				match(symSQCLOSE);
			else
				message(DEBUG, "Expecting closing square bracket\n");
		}
	}
}

static void CompoundStatement(){

	static tokenType firstSet[] = { symBROPEN, (tokenType)-1 };
	static tokenType followSet[] = { kwINT, kwFLOAT, kwVOID, kwIF,  symBRCLOSE, symPLUS, symMINUS, symNOT,
		symOPEN, kwWHILE, kwRETURN, litFLOAT, litINT, litSTRING, (tokenType)-1 };
	if (synchronize(firstSet, followSet, "Expecting an open parantheses \(\n")){
		if (lookAhead.token == symBROPEN){
			match(symBROPEN);
			Declaration();
		} else
			Statement();

		if (lookAhead.token == symBRCLOSE){
			match(symBRCLOSE);
		} else{
			message(DEBUG, "Expecting closing curly brace\n");
		}
	}
}

static void Declaration(){
	static tokenType firstSet[] = { kwINT, kwFLOAT, kwVOID, (tokenType)-1 };
	static tokenType followSet[] = { kwINT, kwFLOAT, kwVOID, symBRCLOSE, (tokenType)-1 };
	if (synchronize(firstSet, followSet, "DeclarationStatement Error\n")){
		TypeSpecifier();

		if (lookAhead.token == tokIDENT){
			match(tokIDENT);
		}

		isArray();

		while (lookAhead.token == symCOMMA){
			match(symCOMMA);

			if (lookAhead.token == tokIDENT){
				match(tokIDENT);
			
				if(lookAhead.token == symSQOPEN){
					isArray();
				}
			}			
		}
	}
}
static void Statement(){	
	static tokenType firstSet[] = { symPLUS, symMINUS, symNOT, symOPEN, tokIDENT, litFLOAT, litINT, litSTRING, symBROPEN, kwIF, kwWHILE, kwRETURN, (tokenType)-1 };
	static tokenType followSet[] = { kwELSE, kwINT, kwFLOAT, kwVOID, symBRCLOSE, symPLUS, symMINUS, symNOT, symOPEN, tokIDENT, litFLOAT, litINT, litSTRING, 
		symBROPEN, kwIF, kwWHILE, kwRETURN, (tokenType)-1 };
	if (synchronize(firstSet, followSet, "DeclarationStatement Error\n")){		
		ExpressionStatement();
		CompoundStatement();
		SelectionStatement();
		RepetitionStatement();
		ReturnStatement();
	}
	
}

//not sure
static void ExpressionStatement(){
	static tokenType firstSet[] = { symPLUS, symMINUS, symNOT, symOPEN, tokIDENT, litFLOAT, litINT, litSTRING, (tokenType)-1 };
	static tokenType followSet[] = { symASSIGN, symBRCLOSE, kwINT, kwFLOAT, kwVOID, symPLUS, symMINUS, symNOT, symOPEN, tokIDENT, 
		litFLOAT, litINT, litSTRING, symBROPEN, kwIF, kwWHILE, kwRETURN, (tokenType)-1 };
	if (synchronize(firstSet, followSet, "ExpressionStatement Error \n")){
		Expression();

		if (lookAhead.token == symASSIGN){
			match(symASSIGN);

			if(memberOf(lookAhead.token, firstSet))
				Expression();			
		}

		if (lookAhead.token == symSEMI){
			match(symSEMI);
		}
	}
}

static void Expression(){
	static tokenType firstSet[] = { symPLUS, symMINUS,tokIDENT, symOPEN, litFLOAT, litINT, litFLOAT, (tokenType)-1 };
	static tokenType followSet[] = { symASSIGN, symSEMI, symCLOSE, symSQCLOSE, symCOMMA, symCLOSE, (tokenType)-1 };
	if (synchronize(firstSet, followSet, "Expression Error\n")){
		AndExpression();

		if (lookAhead.token == symOR){
			match(symOR);
			AndExpression();
		}
	}

}
static void SelectionStatement(){
	printf("inside selection statement");
	static tokenType firstSet[] = { kwIF, (tokenType)-1 };
	static tokenType followSet[] = { symOPEN, (tokenType)-1 };
	if (synchronize(firstSet, followSet, "SelectionStatement Error\n")){
		if (lookAhead.token == kwIF){
			match(kwIF);

			if (lookAhead.token == symOPEN){
				match(symOPEN);
				Expression();

				if (lookAhead.token == symCLOSE){
					match(symCLOSE);
					Statement();
				}
			} else{
				message(DEBUG, "No Open Parenthese\n");
			}
		}
	}
}

static void RepetitionStatement(){
	static tokenType firstSet[] = { kwWHILE, (tokenType)-1 };
	static tokenType followSet[] = { symOPEN, (tokenType)-1 };

	if (synchronize(firstSet, followSet, "RepititionStatement Error\n")){
		if (lookAhead.token == kwWHILE){
			match(kwWHILE);

			if (lookAhead.token == symOPEN){
				match(symOPEN);

				Expression();

				if (lookAhead.token == symCLOSE){
					match(symCLOSE);

					Statement();
				}
			}
		}
	}
}

static void ReturnStatement(){
	static tokenType firstSet[] = { kwRETURN, (tokenType)-1 };
	static tokenType followSet[] = { symSEMI, symPLUS, symMINUS, symNOT, tokIDENT, litFLOAT, litINT, litSTRING, (tokenType)-1 };

	if (synchronize(firstSet, followSet, "Return Statement error\n")){
		if (lookAhead.token == kwRETURN){
			match(kwRETURN);

			Expression();			

			if (lookAhead.token == symSEMI){
				match(symSEMI);
			}
		}
	}
}
static void AndExpression(){
	
	static tokenType firstSet[] = { symPLUS, symMINUS, symNOT, symOPEN, tokIDENT, litFLOAT, litINT, litSTRING, (tokenType)-1 };
	static tokenType followSet[] = { symOR, symPLUS, symMINUS, symNOT, symOPEN, tokIDENT, litFLOAT, litINT, litSTRING, (tokenType)-1 };
	
	if (synchronize(firstSet, followSet, "AndExpression Error")){
		RelationExpression();

		while (lookAhead.token == symAND){
			RelationExpression();
		}
	}

}

static void RelationExpression(){
	static tokenType firstSet[] = { symPLUS, symMINUS, symNOT, symOPEN, tokIDENT, litFLOAT, litINT, litSTRING, (tokenType)-1 };
	static tokenType followSet[] = { symAND, (tokenType)-1 };

	if (synchronize(firstSet, followSet, "AndExpression Error")){
		SimpleExpression();
		if (lookAhead.token == symLESSEQ || lookAhead.token == symLESS || lookAhead.token == symGREATEREQ
			|| lookAhead.token == symGREATER || lookAhead.token == symEQUAL || lookAhead.token == symNOTEQ){

			if (lookAhead.token == symLESSEQ){
				match(symLESSEQ); SimpleExpression();
			}
			if (lookAhead.token == symLESS){
				match(symLESS); SimpleExpression();
			}
			if (lookAhead.token == symGREATEREQ){
				match(symGREATEREQ); SimpleExpression();
			}
			if (lookAhead.token == symGREATER){
				match(symGREATER); SimpleExpression();
			}
			if (lookAhead.token == symEQUAL){
				match(symEQUAL); SimpleExpression();
			}
			if (lookAhead.token == symNOTEQ){
				match(symNOTEQ); SimpleExpression();
			}
		}
	}
}

static void SimpleExpression(){
	static tokenType firstSet[] = { symPLUS, symMINUS, symNOT, symOPEN, tokIDENT, litFLOAT, litINT, litSTRING, (tokenType)-1 };
	static tokenType followSet[] = { symLESS, symLESSEQ, symGREATER, symGREATEREQ, symEQUAL, symNOTEQ, (tokenType)-1 };
	
	if (synchronize(firstSet, followSet, "SimpleExpression Error")){
		Term();

		while (lookAhead.token == symPLUS || lookAhead.token == symMINUS){

			if (lookAhead.token == symPLUS){
				match(symPLUS);
			}
			Term();
		}
	}
}
static void Term(){

	static tokenType firstSet[] = { symPLUS, symMINUS, symNOT, symOPEN, tokIDENT, litFLOAT, litINT, litSTRING, (tokenType)-1 };
	static tokenType followSet[] = { symPLUS, symMINUS, symPLUS, symMINUS, symNOT, symOPEN, tokIDENT, litFLOAT, litINT, litSTRING, (tokenType)-1 };

	bool oneSymbol = false;
	
	if (synchronize(firstSet, followSet, "Term Error")){
		Factor();
		while (lookAhead.token == symMUL || lookAhead.token == symDIV || lookAhead.token == symMOD){

			oneSymbol = false;

			if (lookAhead.token == symMUL && oneSymbol == false){
				match(symMUL);
				oneSymbol = true;
			}

			if (lookAhead.token == symDIV && oneSymbol == false){
				match(symDIV);
				oneSymbol = true;
			}

			if (lookAhead.token == symMOD && oneSymbol == false){
				match(symMOD);
				oneSymbol = true;
			}

			Factor();

		}
	}
	

}
static void Factor(){

	static tokenType firstSet[] = { symPLUS, symMINUS, symNOT, symOPEN, tokIDENT, litFLOAT, litINT, litSTRING, (tokenType)-1 };
	static tokenType followSet[] = { symMUL, symMOD, symDIV, (tokenType)-1 };

	if (synchronize(firstSet, followSet, "Factor Error")){
		if (lookAhead.token == symPLUS || lookAhead.token == symMINUS){

			if (lookAhead.token == symPLUS){
				match(symPLUS);
			}
			if (lookAhead.token == symMINUS){
				match(symMINUS);
			}
		}
		Value();
	}

}
static void Value(){

	static tokenType firstSet[] = { symOPEN, tokIDENT, litFLOAT, litINT, litSTRING, (tokenType)-1 };
	static tokenType followSet[] = { symAND, symPLUS, symMINUS, symMOD, symDIV, (tokenType)-1 };
	if (synchronize(firstSet, followSet, "Value Expression")){
		if (lookAhead.token == symOPEN || lookAhead.token == tokIDENT || lookAhead.token == litFLOAT
			|| lookAhead.token == litINT || lookAhead.token == litSTRING){

			if (lookAhead.token == symOPEN){
				match(symOPEN);

				Expression();

				if (lookAhead.token == symCLOSE){
					match(symCLOSE);
				}
			}

			if (lookAhead.token == tokIDENT){
				match(tokIDENT);

				if (lookAhead.token == symSQOPEN || lookAhead.token == symOPEN){

					if (lookAhead.token == symSQOPEN){
						match(symSQOPEN);
						Expression();

						if (lookAhead.token == symSQCLOSE){
							match(symSQCLOSE);
						}
					}

					if (lookAhead.token == symOPEN){
						match(symOPEN);

						Expression();

						if (lookAhead.token == symCOMMA){

							while (lookAhead.token == symCOMMA){
								match(symCOMMA);
								Expression();
							}
						}
					}

					if (lookAhead.token == symCLOSE){
						match(symCLOSE);
					}
				}
			}
			if (lookAhead.token == litFLOAT
				|| lookAhead.token == litINT || lookAhead.token == litSTRING){


				if (lookAhead.token == litFLOAT){
					match(litFLOAT);
				}

				if (lookAhead.token == litINT){
					match(litINT);
				}

				if (lookAhead.token == litSTRING){
					match(litSTRING);
				}
			}

			if (lookAhead.token == symSEMI){
				match(symSEMI);
			}

			if(lookAhead.token == tokEOF){
				match(tokEOF);
				return;
			}
		}
	}
}

static void isArray(){
	if (lookAhead.token == symSQOPEN){
		match(symSQOPEN);
		if (lookAhead.token == litINT){
			match(litINT);
			if (lookAhead.token == symSQCLOSE){
				match(symSQCLOSE);
			}
		}
	}
}
