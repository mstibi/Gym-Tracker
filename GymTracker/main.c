#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include "file_manager.h"

typedef enum {
	DODAJ_CLANA = 1,
	IZBRISI_CLANA,
	UREDI_CLANA,
	ISPISI_CLANOVE,
	SORTIRAJ_PO_IMENU,
	SORTIRAJ_PO_PREZIMENU,
	PRETRAZI_PO_ID,
	NAJVECI_ID,
	OBRISI_DATOTEKU,
	PREIMENUJ_DATOTEKU,
	IZLAZ
} IzbornikOpcija;

int main(void) {
	inicijalizirajDatoteku();
	FILE* file = fopen(dohvatiTrenutnuDatoteku(), "a+");

	if (!file) {
		perror("Greska pri otvaranju datoteke");
		return 1;
	}

	int brojClanova = 0;
	CLAN** clanovi = ucitajClanoveIzDatoteke(file, &brojClanova);
	fclose(file);


	IzbornikOpcija odabir;
	do {
		printf("\n========================================\n");
		printf("| GYM MANAGEMENT SYSTEM               |\n");
		printf("========================================\n");
		printf("| 1 - Dodaj clana                     |\n");
		printf("| 2 - Izbrisi clana                   |\n");
		printf("| 3 - Uredi clana                     |\n");
		printf("| 4 - Ispisi sve clanove              |\n");
		printf("| 5 - Sortiraj po imenu               |\n");
		printf("| 6 - Sortiraj po prezimenu           |\n");
		printf("| 7 - Pretrazi po ID-u                |\n");
		printf("| 8 - Prikazi clana s najvecim ID-em  |\n");
		printf("| 9 - Obrisi datoteku                 |\n");
		printf("|10 - Preimenuj datoteku              |\n");
		printf("|11 - Izlaz                           |\n");
		printf("========================================\n");
		printf("Odabir: ");

		if (scanf("%d", (int*)&odabir) != 1) {
			printf("Neispravan unos!\n");
			while (fgetc(stdin) != '\n');
			continue;
		}
		while (getchar() != '\n' && !feof(stdin));

		switch (odabir) {
		case DODAJ_CLANA:
			dodajClana(&clanovi, &brojClanova);
			break;

		case IZBRISI_CLANA: {
			int id;
			printf("Unesi ID clana za brisanje: ");
			if (scanf("%d", &id) == 1) {
				while (getchar() != '\n' && !feof(stdin));
				izbrisiClana(&clanovi, &brojClanova, id);
			}
			else {
				printf("Neispravan unos!\n");
				while (getchar() != '\n' && !feof(stdin));
			}
			break;
		}

		case UREDI_CLANA: {
			int id;
			printf("Unesi ID clana za uređivanje: ");
			if (scanf("%d", &id) == 1) {
				while (getchar() != '\n' && !feof(stdin));
				urediClana(clanovi, brojClanova, id);
			}
			else {
				printf("Neispravan unos!\n");
				while (getchar() != '\n' && !feof(stdin));
			}
			break;
		}

		case ISPISI_CLANOVE:
			ispisClanova(clanovi, brojClanova);
			break;

		case SORTIRAJ_PO_IMENU:
			ispisSortiranihClanovaPoImenu(clanovi, brojClanova);
			break;

		case SORTIRAJ_PO_PREZIMENU:
			ispisSortiranihClanovaPoPrezimenu(clanovi, brojClanova);
			break;

		case PRETRAZI_PO_ID: {
			int id;
			printf("Unesi ID clana za pretragu: ");
			if (scanf("%d", &id) == 1) {
				while (getchar() != '\n' && !feof(stdin));
				pretrazivanje(clanovi, brojClanova, id);
			}
			else {
				printf("Neispravan unos!\n");
				while (getchar() != '\n' && !feof(stdin));
			}
			break;
		}

		case NAJVECI_ID:
			najveciID(clanovi, brojClanova);
			break;

		case OBRISI_DATOTEKU:
			obrisiDatoteku(&clanovi, &brojClanova);
			break;
		case PREIMENUJ_DATOTEKU:
			preimenujDatoteku();
			break;

		case IZLAZ:
			printf("Hvala na koristenju programa! Dovidjenja.\n");
			break;

		default:
			printf("Nepostojeca opcija!\n");
			break;
		}

		// Automatsko spremanje promjena
		file = fopen(dohvatiTrenutnuDatoteku(), "w");
		if (file) {
			spremiClanoveUDatoteku(file, clanovi, brojClanova);
			fclose(file);
		}

	} while (odabir != IZLAZ);

	oslobodiClanove(clanovi, brojClanova);
	obrisiTrenutnuDatoteku();

	return 0;
}
