// header.h
#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "file_manager.h"

typedef struct {
	char* ime;
	char* prezime;
	int id;
} CLAN;

// Prototipovi funkcija
int validirajImePrezime(const char* unos);
int validirajID(const char* unos);
CLAN** ucitajClanoveIzDatoteke(FILE* file, int* brojClanova);
void spremiClanoveUDatoteku(FILE* file, CLAN* const* clanovi, int brojClanova);
void oslobodiClanove(CLAN** clanovi, int brojClanova);
void dodajClana(CLAN*** clanovi, int* brojClanova);
void izbrisiClana(CLAN*** clanovi, int* brojClanova, int id);
void urediClana(CLAN** clanovi, int brojClanova, int id);
void ispisClanova(CLAN* const* clanovi, int brojClanova);
void obrisiDatoteku(CLAN*** clanovi, int* brojClanova);
void preimenujDatoteku(void);

#endif
