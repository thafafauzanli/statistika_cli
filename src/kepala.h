/*
 * 	STATISTIKA CLI (C) 2022
 *	Penulis : Thafa Fauzanli
 * 	Youtube : youtube.com/c/takuniinfinity 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#ifndef _KEPALA_H
#define _KEPALA_H
#endif

// Global Variable
char j;
// Fungsi tambahan
void clear() { printf("\e[1;1H\e[2J"); }
int acakjarak(int da, int sa) {
	return (rand() % (sa-da))+da;
};
float float3(float n) {
	char str[40];
	sprintf(str, "%.3f", n);
	sscanf(str, "%f", &n);
	return n;
};
int dalam_jarak(int n, int da, int sa) {
	for (int ii=da; ii<=sa; ii++) {
		if (n==ii) {return 1; break;}
	}
	return 0;
}

// State
void kepala(), tentang(), menu(), dataacak();
void dataacak() {
	int jumda=0, nilti=0, nilre=0; // Jumlah data, nilai tertinggi, nilai terendah
	int r, k, p;
	j='0';
	while (1) {
		clear();
		kepala();
		printf("=== DISTRIBUSI FREKUENSI (data acak otomatis) ===\n\n");
		if (jumda!=0) {
			printf("Jumlah data : %i\n", jumda);
			printf("Nilai tertinggi : %i\n", nilti);
			printf("Nilai terendah : %i\n", nilre);
		} else {
			printf("Jumlah data : ");
			scanf("%i", &jumda);
			printf("Nilai tertinggi : ");
			scanf("%i", &nilti);
			printf("Nilai terendah : ");
			scanf("%i", &nilre);
		}
		printf("\n=> Data acak :\n");
		int dacak[jumda]; // Membuat var array data acak
		for (int i=0; i<jumda; i++) { // Membuat data acak
			dacak[i] = acakjarak(nilre, nilti);
		}
		for (int i=0; i<jumda; i++) { // Menampilkan data acak
			printf("%i", dacak[i]);
			if (i!=jumda-1) { printf(", "); }
			if ((i+1)%10==0) {printf("\n");}
		}
		printf("\n\n=> Data urut :\n");
		int daur[jumda]; int pmb; // Membuat var array data urut + variabel pembantu
		for (int i=0; i<jumda; i++) { daur[i] = dacak[i]; } //  Memasukkan data acak ke urut
		for (int i=0; i<jumda; i++) { // Mengurutkan data dari kecil - besar
			for (int l=i+1; l<jumda; l++) {
				if (daur[i] > daur[l]) {
					pmb = daur[i];
					daur[i] = daur[l];
					daur[l] = pmb;
				}
			}
		}
		for (int i=0; i<jumda; i++) { // Menampilkan data urut
			printf("%i", daur[i]);
			if (i!=jumda-1) {printf(", ");}
			if ((i+1)%10==0) {printf("\n");}
		}
		printf("\n(1. Pas, 2. Acak lagi, 0. Kembali) : ");
		scanf(" %c", &j);
		if (j=='0') {
			menu();
			break;
		} else if (j=='1') {
			// pas
		} else if (j=='2') {
			continue;
		} else {
			jumda = 0; nilti = 0; nilre = 0;
			continue;
		}
		
		printf("\n\n=> Jarak / Rentangan (R) :\n");
		r = nilti - nilre; // Membuat variabel dan nilai jarak (R)
		printf("R = data tertinggi - data terendah\n"); // rumus jarak
		printf("R = %i - %i\n", nilti, nilre);
		printf("R = %i\n", r);
		
		printf("\n=> Jumlah kelas (K) :\n");
		k = 1+3.3*float3(log10(jumda)); float pm;
		printf("K = 1 + 3.3 log jumlah data(n)\n"); // rumus kelas
		printf("K = 1 + 3.3 log %i\n", jumda);
		pm = float3(log10(jumda));
		printf("K = 1 + 3.3 %0.3f\n", pm);
		pm = 3.3*pm;
		printf("K = 1 + %0.4f = %0.4f = %i\n", pm, pm+1, k);
		
		printf("\n=> Panjang interval kelas (P) :\n");
		p = round((float)r/(float)k); // Membuat variabel dan nilai interval (P)
		printf("P = rentang(R) / kelas(K)\n"); // rumus interval
		pm = float3((float)r/(float)k);
		printf("P = %i / %i = %0.3f = %i\n", r, k, pm, p);
		
		// Pembuatan tabel Distribusi Frekuensi
		int nilter[k][2]; // Pembuatan nilai interval
		pmb = daur[0];
		for (int i=0; i<k; i++) {
			for (int l=0; l<2; l++) {
				if (i>0 && l==0) { pmb += 1; }
				if (l!=0) { pmb += p-1; }
				nilter[i][l] = pmb;
			}
		}
		int fre[k]; // Pembuatan frekuensi (F)
		for (int i=0; i<k; i++) {
			pmb = 0;
			for (int l=0; l<jumda; l++) {
				if (dalam_jarak(daur[l], nilter[i][0], nilter[i][1])==1) {
					pmb += 1;
				}
			}
			fre[i] = pmb;
		}
		printf("\n=== TABEL DISTRIBUSI FREKUENSI ===\n");
		printf("+------------------+--------------+\n");
		printf("|  Nilai Interval  | Frekuensi(F) |\n");
		printf("+------------------+--------------+\n");
		for (int i=0; i<k; i++) {
			char lng[8];
			if (fre[i] > 9) {lng[6] = '\0'; strcpy(lng, "     ");}
			else { lng[5] = '\0'; strcpy(lng, "      "); }
			printf("|     %i - %i      |       %i%s|\n", nilter[i][0], nilter[i][1], fre[i], lng );
		}
		printf("+------------------+--------------+\n");
		printf("|      Total      |      %i       |\n", jumda);
		printf("+------------------+--------------+\n");
		break;
	}
}

void menu() {
	clear();
	kepala();
	printf("\n0. Keluar            t. tentang\n");
	printf("-- Distribusi Frekuensi --\n");
	printf("1. Buat tabel dengan data acak otomatis\n");
	printf("2. Buat tabel dengan data diisi manual\n");
	
	printf("Masukkan opsi : ");
	scanf("%c", &j); printf("\n");
	
	if (j=='t') {
		tentang();
	} else if (j=='0') {
		printf("Sampai jumpa lagi...\n");
	} else if (j=='1') {
		dataacak();
	} else {
		menu();
	}
}

void kepala() {
	printf("====== STATISTIKA CLI ======\n");
	printf("----------------------------\n");
	printf("- Penulis : Thafa Fauzanli\n");
	printf("----------------------------\n");
}

void tentang() {
	clear();
	kepala();
	printf("\nAplikasi ini dibuat untuk memudahkan pengerjaan tugas statistika\n");
	printf("\n=> Special thanks to:\n");
	printf("- Allah SWT\n");
	printf("- Pak Hadri Hasan (Dosen Statistika)\n");
	printf("0. Kembali\n");
	
	printf("\nMasukkan opsi : ");
	scanf("%c", &j); printf("\n");
	
	if (j=='0') { menu(); }
	else { tentang(); }
}
