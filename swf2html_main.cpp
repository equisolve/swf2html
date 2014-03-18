/****************************************************************************
CONFIDENTIAL AND PROPRIETARY INFORMATION.  The entire contents of this file
is Copyright © Macromedia, Inc. 2002, All Rights Reserved.  This
document is an unpublished trade secret of Macromedia, Inc. and may not be
viewed, copied or distributed by anyone, without the specific, written
permission of Macromedia, Inc. 
****************************************************************************/

/*

	swf2html_main.cpp

	SWF-to-HTML converter, command line tool

*/

#include <stdio.h>
#include <string.h>

#include "zlib.h"
#include "stags.h"
#include "swf2html_stdio.h"

#define BUILD_NUMBER 11

void usage( void )
{
	fprintf(stderr, "swf2html: Convert SWF to HTML [build %d]\n", BUILD_NUMBER);
	fprintf(stderr, "Copyright (c) 2002 Macromedia, Inc.  All rights reserved.\n\n");
    fprintf(stderr, "usage: swf2html [-l][-t][-o outputFile][-p prefixes][-s suffixes] inputFile\n\n");
    fprintf(stderr, "       -l dumps links only\n" );
    fprintf(stderr, "       -t dumps text only\n" );
    fprintf(stderr, "       -o to specify a filename for the output\n");
    fprintf(stderr, "       -p to specify a prefixes filter string in the form \"pre1|pre2\"\n");
    fprintf(stderr, "       -s to specify a suffixes filter string in the form \"suf1|suf2\"\n");
    fprintf(stderr, "       use - for inputFile if using stdin for the swf buffer\n");
	exit(-1);
}

int main (int argc, char **argv)
// Main program.
{
    char *inputFile = NULL;
	char *outputFileName = NULL;

    // Check the argument count.
    if (argc < 2)
    {
        // Bad arguments.
        usage();
        return -1;
    }

	Swf2HtmlConverterStdio converter;

	while (--argc > 0) {
		char *option = *++argv;
		if (*option == '-') {
			switch (option[1]) {
			case 0:
				/* It's '-' by itself, meaning scan standard input */
				if (inputFile != NULL) {
					fprintf(stderr, "swf2html: error: inputFile specified more than once!\n");
					usage();
				}
				inputFile = option;
				break;
			case 'l':
				converter.SetDumpLinks(true);
				converter.SetDumpText(false);
				break;
			case 't':
				converter.SetDumpText(true);
				converter.SetDumpLinks(false);
				break;
			case 'o':
				if (--argc > 0) {
					outputFileName = *++argv;
				}
				break;
			case 'p':
				if (--argc > 0) {
					converter.SetPrefixFilters(*++argv);
				}
				break;
			case 's':
				if (--argc > 0) {
					converter.SetSuffixFilters(*++argv);
				}
				break;
			default:
				fprintf(stderr, "swf2html: error: unknown command line switch!\n");
				usage();
			}
		} else {
			if (inputFile != NULL) {
				fprintf(stderr, "swf2html: error: inputFile specified more than once!\n");
				usage();
			}
			inputFile = option;
		}
	}

	if (!inputFile) {
		fprintf(stderr, "swf2html: error: inputFile is a required parameter!\n");
		usage();
	}

    // Parse the file passed in.
    converter.ConvertSwf2Html(inputFile, outputFileName);

    return 0;
}
