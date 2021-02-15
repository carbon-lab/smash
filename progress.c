/**
 * progress.c
 * @author Ulyan Sobin
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

#define BUFFER_SIZE 1024
static uint8_t buffer[BUFFER_SIZE];

int cover_byte(FILE *file, uint8_t byte, size_t fsize);
int cover_random(FILE *file, size_t fsize);

int rewrite_file(FILE *file) {

	fseek(file, 0, SEEK_END);
	size_t fsize = ftell(file);

	cover_byte(file, 0x00, fsize);
	cover_byte(file, 0xFF, fsize);
	cover_random(file, fsize);

	return 0;
}

int cover_byte(FILE *file, uint8_t byte, size_t fsize) {
	memset(buffer, byte, BUFFER_SIZE);
	fseek(file, 0, SEEK_SET);
	int64_t i, limit = (int64_t)fsize - BUFFER_SIZE;
	for (i = 0; i  < limit; i += BUFFER_SIZE)
		fwrite(buffer, BUFFER_SIZE, 1, file);
	if (i == 0) i = BUFFER_SIZE;
	fwrite(buffer, BUFFER_SIZE - (i - (int64_t)fsize), 1, file);
	return 0;
}

int cover_random(FILE *file, size_t fsize) {
	int64_t i;
	int32_t seed = (int32_t)time(NULL);
	for (i = 0; i < BUFFER_SIZE; i += 4) {
		srand(seed);
		seed = (uint32_t)(sin(seed) * 65535.0);
		*((int32_t*)&buffer[i]) = rand();
	}
	fseek(file, 0, SEEK_SET);
	int64_t limit = (int64_t)fsize - BUFFER_SIZE;
	for (i = 0; i  < limit; i += BUFFER_SIZE)
		fwrite(buffer, BUFFER_SIZE, 1, file);
	if (i == 0) i = BUFFER_SIZE;
	fwrite(buffer, BUFFER_SIZE - (i - (int64_t)fsize), 1, file);
	return 0;
}

int clean_drive(char *path) {
	int count = 0;
	char path_buf[128];

	do {
		sprintf(path_buf, "%s/PLACEHOLDER_%X", path, count++);

		FILE *ph = fopen(path_buf, "wb");
		if (ph == NULL) goto L_OUT;

		size_t i, c = 0;
		memset(buffer, 0, BUFFER_SIZE);
		do {
			i = fwrite(buffer, BUFFER_SIZE, 1, ph);
			c += 1;
			if (c % 1024 == 0) {
				printf("%6d MB space covered\n", c / 1024);
				if (c / 1024 >= 2048) {
					goto L_CONTINUE;
				}
			}
		} while (i > 0);
		goto L_OUT;
		L_CONTINUE:
		fclose(ph);
	} while (1);
	L_OUT:;

	int i;
	for (i = 0; i < count; i++) {
		sprintf(path_buf, "%s/PLACEHOLDER_%X", path, i);
		remove(path_buf);
	}

	return 0;
}
