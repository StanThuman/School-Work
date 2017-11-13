/* Arkansas State University
 * CS 4-5133 Compilers
 * Dr. Jeff Jenness
 * 2015-07-05
 *
 * shell.c
 */
#include "shell.h"

#define maxlen 	50
#define namelen 50

#define EXT ".cmm"
char srcfilename[namelen];
char errfilename[namelen];
char dbgfilename[namelen];
bool stdinput = false;
int tabwidth = 8; // default tab width

static char *version();
static void banner();
static bool IsInteger(char *s);
static int getSwitch(char *s);
static void processArgs(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    FILE *fin;

	messagesInit();

    srcfilename[0] = '\0';
    errfilename[0] = '\0';
    dbgfilename[0] = '\0';

    processArgs(argc,argv);
    banner();

    if (srcfilename[0] == '\0' && !stdinput)
        message(WARNING, "compiler: no input specified");
    else {
        if (srcfilename[0] == '\0') {
            fin = stdin;
            message(VERBOSE, "compiler: reading from standard input");
        } else {
            if (stdinput)
                message(WARNING, "compiler: ignoring option --stdin: using source file \"%s\"", srcfilename);
            fin = fopen(srcfilename, "r");
            if (!fin)
                message(PANIC, "compiler: file \"%s\" not found", srcfilename);
            message(VERBOSE, "compiler: reading from source file \"%s\"", srcfilename);
        }

        setTabWidth(tabwidth);
		
		parserInit(fin);

		if (parserRead())
			message(NORMAL, "%i lines processed: compile successful", getLinesRead());
		else
		    message(NORMAL, "%i errors: %i warnings: compile failed", errorCount, warningCount);
    }

    return 0;
}

static char *version() {
    static char v[maxlen];
    sprintf(v,"V%s.%s.%s-%s",major,minor,sub,date);
    return v;
}

static void banner() {
    message(NORMAL, "%s %s (%s)", name, version(), author);
}

static bool IsInteger(char *s) {
    bool isInt = true;
    int i = 0;
    if (s[i] == '+' || s[i] == '-')
        ++i;
    while (i < strlen(s) && isInt)
        isInt = isInt && isdigit(s[i++]);
    return isInt;
}

static int getSwitch(char *s) {
	int i;
    for (i=0; i < strlen(s); ++i)
        s[i] = tolower(s[i]);
    if (strcmp(s, "+") == 0 || strcmp(s, "1") == 0 || strcmp(s, "on") == 0 || strcmp(s, "true") == 0)
        return 1;
    else if (strcmp(s, "-") == 0 || strcmp(s, "0") == 0 || strcmp(s, "off") == 0 || strcmp(s, "false") == 0)
        return 0;
    else
        return -1;
}

static void processArgs(int argc, char *argv[]) {
    int i;
    char opt[maxlen], *arg;
    for (i=1; i<argc; i++) {
        strncpy(opt, argv[i], maxlen-1);
        opt[maxlen-1] = '\0';
        if (opt[0] == '-') {
            if ((arg = strchr(opt,':')) || (arg = strchr(opt,'=')))
                *(arg++) = '\0';
            if (strcmp(opt, "--help") == 0 || strcmp(opt, "-h") == 0 || strcmp(opt, "-?") == 0) {
                banner();
                printf("usage: cmc [options] filename [options]\n");
                printf("options:\n");
                printf("    --help        print this help (or -h -?)\n");
                printf("    --version     print out current version (or -V)\n");
                printf("    --silent      run silently: implies -W:off (or -s)\n");
                printf("    --verbose     turn on verbose messages (or -v)\n");
                printf("    --debug       turn on debugging messages (or -d)\n");
                printf("    --debugfile:F print debug messages to file F: implies -d (or -D:F)\n");
                printf("    --warnings:S  switch on/off warning messages: default 'on' (or -W:S)\n");
                printf("    --errorfile:F print error messages to file F (or -E:F)\n");
                printf("    --messages:N  set message print level: N = 0-4: default 2 (or -M:N)\n");
                printf("    --stdin       read source from standard input (or --)\n");
                printf("    --tabs:N      set tab width of input: N > 0: default 8 (or -T:N)\n");
                printf("switches (S) turn 'on' using 1/+/on/true or 'off' using 0/-/off/false\n\n");
                exit(0);
            } else if (strcmp(opt, "--version") == 0   || strcmp(opt, "-V") == 0) {
                printf("%s\n", version());
                exit(0);
            } else if (strcmp(opt, "--silent") == 0    || strcmp(opt, "-s") == 0) {
                plvl = SILENT;
            } else if (strcmp(opt, "--verbose") == 0     || strcmp(opt, "-v") == 0) {
                plvl = VERBOSE;
            } else if (strcmp(opt, "--debug") == 0     || strcmp(opt, "-d") == 0) {
                plvl = DEBUG;
            } else if (strcmp(opt, "--debugfile") == 0 || strcmp(opt, "-D") == 0) {
                if (arg == NULL || arg[0] == '\0')
                    message(WARNING, "command-line: filename missing: not redirecting debug messages");
                else {
                    strncpy(dbgfilename, arg, namelen);
                    message(DEBUG, "command-line: redirecting debug messages to \"%s\"", dbgfilename);
                    plvl = DEBUG;
                    fdbg = fopen(dbgfilename, "w");
                }
            } else if (strcmp(opt, "--warnings") == 0  || strcmp(opt, "-W") == 0) {
                if (arg == NULL || arg[0] == '\0')
                    message(WARNING, "command-line: warning switch missing: setting to '%s'",warnings?"on":"off");
                else {
                    int s = getSwitch(arg);
                    if (s > 0)
                        warnings = true;
                    else if (s == 0)
                        warnings = false;
                    else
                        message(WARNING, "command-line: warning switch '%s' invalid: setting to '%s'", arg, warnings?"on":"off");
                }
            } else if (strcmp(opt, "--errorfile") == 0 || strcmp(opt, "-E") == 0) {
                if (arg == NULL || arg[0] == '\0')
                    message(WARNING, "command-line: filename missing: not redirecting error messages");
                else {
                    strncpy(errfilename, arg, namelen);
                    message(DEBUG, "command-line: redirecting error messages to \"%s\"", errfilename);
                    ferr = fopen(errfilename, "w");
                }
            } else if (strcmp(opt, "--messages") == 0  || strcmp(opt, "-M") == 0) {
                if (arg == NULL || arg[0] == '\0')
                    message(WARNING, "command-line: message level missing: setting to %d", plvl);
                else if (!IsInteger(arg))
                    message(WARNING, "command-line: message level '%s' invalid: setting to %d", arg, plvl);
                else {
                    level l = (level)atoi(arg);
                    if (l < SILENT || l > DEBUG)
                        message(WARNING, "command-line: message level %d out of range: setting to %d", l, plvl);
                    else
                        plvl = (level)l;
                }
            } else if (strcmp(opt, "--stdin") == 0     || strcmp(opt, "--") == 0) {
                stdinput = true;
            } else if (strcmp(opt, "--tabs") == 0      || strcmp(opt, "-T") == 0) {
                if (arg == NULL || arg[0] == '\0')
                    message(WARNING, "command-line: tab width missing: setting to %d", tabwidth);
                else if (!IsInteger(arg))
                    message(WARNING, "command-line: tab width '%s' invalid: setting to %d", arg, tabwidth);
                else {
                    int t = atoi(arg);
                    if (t <= 0)
                        message(WARNING, "command-line: tab width %d out of range: setting to %d", t, tabwidth);
                    else
                        tabwidth = t;
                }
            } else {
                banner();
                message(PANIC, "command-line: unknown option: '%s'", argv[i]);
            }
            message(DEBUG, "command-line: processed option '%s'", argv[i]);
        } else if (srcfilename[0] == '\0') {
            strncpy(srcfilename, argv[i], namelen-1);
            srcfilename[namelen-1] = '\0';
            if (strncmp(srcfilename+strlen(srcfilename)-strlen(EXT), EXT, strlen(EXT)) != 0)
                strncat(srcfilename, EXT, strlen(EXT));
            message(DEBUG, "command-line: processed filename \"%s\"", srcfilename);
        } else {
            banner();
            message(PANIC, "command-line: too many filenames");
        }
    }
}
