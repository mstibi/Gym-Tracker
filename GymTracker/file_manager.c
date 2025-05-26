#define _CRT_SECURE_NO_WARNINGS
#include "file_manager.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static char* trenutnaDatoteka = NULL;

void inicijalizirajDatoteku(void) {
	FILE* config = fopen("gym_config.cfg", "r");
	if (config) {
		char buffer[256];
		if (fgets(buffer, sizeof(buffer), config)) {
			buffer[strcspn(buffer, "\n")] = 0;
			trenutnaDatoteka = _strdup(buffer);
		}
		fclose(config);
	}
	if (!trenutnaDatoteka) {
		trenutnaDatoteka = _strdup("gym.txt");
	}
}

const char* dohvatiTrenutnuDatoteku(void) {
	return trenutnaDatoteka;
}

void postaviTrenutnuDatoteku(const char* novoIme) {
	free(trenutnaDatoteka);
	trenutnaDatoteka = _strdup(novoIme);
	spremiKonfiguraciju();
}

void spremiKonfiguraciju(void) {
	FILE* config = fopen("gym_config.cfg", "w");
	if (config) {
		fprintf(config, "%s", trenutnaDatoteka);
		fclose(config);
	}
}

void obrisiTrenutnuDatoteku(void) {
	free(trenutnaDatoteka);
	trenutnaDatoteka = NULL;
}
