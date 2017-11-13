/* Arkansas State University
 * CS 4-5133 Compilers
 * Dr. Jeff Jenness
 * 2015-07-05
 *
 * parser.h
 */
#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "messages.h"
#include "token.h"
#include "scanner.h"

void parserInit(FILE *fin);
bool parserRead();




#endif
