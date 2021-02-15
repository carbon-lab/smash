/**
 * main.c
 * @author Ulyan Sobin
 */

#include <stdio.h>
#include <string.h>

#include "help.h"
#include "global.h"
#include "progress.h"

FILE *files[100];
char *filenames[100];

char *clean_path = NULL;

int main(int argc, char *argv[]) {
	int i, j = 0;

	if (argc < 2) {
		puts(HELP_DOCUMENT);
		return 1;
	}

	for (i = 1; i < argc; i++) {
		char *arg = argv[i];
		if (arg[0] == '-') {
			if (!strcmp(arg, "-h") ||
				!strcmp(arg, "--help") ||
				!strcmp(arg, "-?"))
			{
				puts(HELP_DOCUMENT);
				return 0;
			}
			else if (
				!strcmp(arg, "-c") ||
				!strcmp(arg, "--clean"))
			{
				app_mode = MODE_CLEAN;
			}
		}
		else {
			if (app_mode == MODE_CLEAN) {
				if (clean_path == NULL) {
					clean_path = arg;
				}
			}
			else if (app_mode == MODE_DEFAULT) {
				FILE *fp = fopen(arg, "rb+");
				if (fp != NULL) {
					files[j] = fp;
					filenames[j] = arg;
					j++;
				}
				else {
					printf("ERROR: File \'%s\' cannot be opened. Skip.\n", arg);
				}
			}
		}
	}

	switch (app_mode) {
		case MODE_DEFAULT:
			for (i = 0; i < j; i++) {
				rewrite_file(files[i]);
				fclose(files[i]);
				remove(filenames[i]);
			}
			break;
		case MODE_CLEAN:
			i = clean_drive(clean_path);
			if (i != 0) {
				puts("ERROR: occur when clean the drive");
				return -1;
			}
			break;
		default:
			return -3;
	}

	return 0;
}