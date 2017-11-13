/* Arkansas State University
 * CS 4-5133 Compilers
 * Dr. Jeff Jenness
 * 2015-07-05
 *
 * scanner.h
 */
#ifndef __SCANNER_H__
#define __SCANNER_H__

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "messages.h"
#include "token.h"

//TODO: add command-line option for bufflen
#define bufflen 256
#define DEFtabwidth 8

void scannerInit(FILE *);
token scannerRead();
const char *scannerError(token);
int getLinesRead();
int setTabWidth(int);
int getTabWidth();

#endif
