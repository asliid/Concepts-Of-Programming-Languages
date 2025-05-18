/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 05.05.2025
* <p> 
* Dosya Okuma Sınıfı
* Dosya okuma işlemlerini gerçekleştiren fonksiyonları içerir.
* Kişi, uzay aracı ve gezegen bilgilerini dosyalardan okur.
* Txtlerden okuma yapılır ve gerekli nesneler oluşturulur.
* </p> 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Kisi.h" // Kisi struct'ı ve kisiOlustur() buradan gelir
#include "UzayAraci.h" // UzayAraci struct'ı ve UzayAraciOlustur() buradan gelir
#include "DosyaOkuma.h" // Dosya okuma fonksiyonları
#include "Gezegen.h" // Gezegen struct'ı ve fonksiyonları buradan gelir
#define MAX_LINE_LENGTH 256

//Verilen dosya yolundan kişi bilgilerini okur ve Kisi* dizisi döner. Kişi sayısı, kisiSayisi değişkenine yazılır.
Kisi* kisileriOku(const char* dosyaAdi, int* kisiSayisi) { 
    FILE* dosya = fopen(dosyaAdi, "r");
    if (!dosya) {
        perror("Dosya açilamadi");
        *kisiSayisi = 0;
        return NULL;
    }

    Kisi* kisiler = NULL;
    *kisiSayisi = 0;

    char satir[256];
    while (fgets(satir, sizeof(satir), dosya)) {
        satir[strcspn(satir, "\n")] = '\0';

        // Satırları # karakterine göre ayırır
        char* isim = strtok(satir, "#");
        char* yasStr = strtok(NULL, "#");
        char* omurStr = strtok(NULL, "#");
        char* aracAdi = strtok(NULL, "#");

        if (!isim || !yasStr || !omurStr || !aracAdi) continue;

        Kisi yeniKisi = kisiOlustur(isim, atoi(yasStr), atoi(omurStr), aracAdi);

        if (!yeniKisi) continue;

         // Dinamik diziye eklemek için belleği genişletir
        Kisi* temp = realloc(kisiler, (*kisiSayisi + 1) * sizeof(Kisi*));  
        if (!temp) {
            perror("Bellek tahsisi basarisiz");
            yeniKisi->kisiYokEt(yeniKisi);
            break;
        }

        kisiler = temp;
        kisiler[*kisiSayisi] = yeniKisi;
        (*kisiSayisi)++;
    }

    fclose(dosya);
    return kisiler;
    
}
// Verilen dosyadan uzay aracı bilgilerini okur ve UzayAraci* dizisi döner. Uzay aracı sayısı, uzayAracSayisi değişkenine yazılır.
// Her araca karşılık gelen yolcular kisiler dizisinden bulur.
UzayAraci* uzayAraclariniOku(const char* dosyaAdi, Kisi* kisiler, int kisiSayisi, int* uzayAracSayisi) {
    FILE* file = fopen(dosyaAdi, "r");
    if (!file) {
        printf("Dosya bulunamadi: %s\n", dosyaAdi);
        *uzayAracSayisi = 0;
        return NULL;
    }

    int kapasite = 10;
    UzayAraci* araclar = malloc(sizeof(UzayAraci) * kapasite);
    *uzayAracSayisi = 0;

    char satir[MAX_LINE_LENGTH];
    while (fgets(satir, sizeof(satir), file)) {
        satir[strcspn(satir, "\n")] = 0;

        char isim[50], cikis[50], varis[50], tarih[50];
        int mesafe;

        // Satırı parse edilir.
        sscanf(satir, "%[^#]#%[^#]#%[^#]#%[^#]#%d", isim, cikis, varis, tarih, &mesafe);

        // Bu araca ait yolcuları bulur.
        Kisi* yolcular = NULL;
        int yolcuSayisi = 0;

        for (int i = 0; i < kisiSayisi; i++) {
            if (strcmp(kisiler[i]->bulunduguArac, isim) == 0) {
                Kisi* yeniYolcular = realloc(yolcular, sizeof(Kisi*) * (yolcuSayisi + 1));
                if (!yeniYolcular) {
                    free(yolcular);
                    fclose(file);
                    return NULL;
                }
                yolcular = yeniYolcular;
                yolcular[yolcuSayisi++] = kisiler[i];
            }
        }

        UzayAraci yeniArac = UzayAraciOlustur(isim, cikis, varis, tarih, mesafe, yolcular, yolcuSayisi);

        // Bellek dolarsa artırır
        if (*uzayAracSayisi >= kapasite) {
            kapasite *= 2;
            UzayAraci* yeniAraclar = realloc(araclar, sizeof(UzayAraci) * kapasite);
            if (!yeniAraclar) {
                fclose(file);
                return NULL;
            }
            araclar = yeniAraclar;
        }

        araclar[(*uzayAracSayisi)++] = yeniArac;
    }

    fclose(file);
    return araclar;
}
// Gezegen bilgilerini okur ve uygun gezegen türüne göre nesne oluşturur.
int gezegenleriGetir(const char* dosyaAdi, Gezegen** gezegenler) {
    FILE* file = fopen(dosyaAdi, "r");
    if (!file) {
        printf("Dosya açılamadı: %s\n", dosyaAdi);
        return 0;
    }

    char satir[256];
    int kapasite = 10;
    int gezegenSayisi = 0;

    *gezegenler = (Gezegen*)malloc(sizeof(Gezegen) * kapasite);
    if (!*gezegenler) {
        printf("Gezegenler için bellek ayrılamadı!\n");
        fclose(file);
        return 0;
    }

    while (fgets(satir, sizeof(satir), file)) {
        satir[strcspn(satir, "\n")] = 0;

        char* isim = strtok(satir, "#");
        char* turStr = strtok(NULL, "#");
        char* saatStr = strtok(NULL, "#");
        char* tarih = strtok(NULL, "#");

        if (!isim || !turStr || !saatStr || !tarih) {
            printf("Satır format hatalı. Atlanıyor.\n");
            continue;
        }

        int gezegenTuru = atoi(turStr);
        int gununKacSaatOldugu = atoi(saatStr);

        // Bellek dolarsa kapasiteyi artır
        if (gezegenSayisi >= kapasite) {
            kapasite *= 2;
            Gezegen* tmp = realloc(*gezegenler, sizeof(Gezegen) * kapasite);
            if (!tmp) {
                printf("Realloc başarısız! Bellek yetersiz.\n");
                fclose(file);
                return gezegenSayisi;
            }
            *gezegenler = tmp;
        }

        // Txtten okunan gezegen türüne göre farlı türde gezegen nesneleri oluşturur.
        switch (gezegenTuru) {
            case 0: {
                KayacGezegen yeniKayac = KayacGezegenOlustur(isim, gununKacSaatOldugu, tarih, 1.0);
                if (yeniKayac){ (*gezegenler)[gezegenSayisi++] = yeniKayac->super;
                        strcpy((*gezegenler)[gezegenSayisi - 1]->orijinalTarih, tarih);}

                break;
            }
            case 1: {
                GazDeviGezegen yeniGaz = GazDeviGezegenOlustur(isim, gununKacSaatOldugu, tarih, 0.1);
                if (yeniGaz) {(*gezegenler)[gezegenSayisi++] = yeniGaz->super;
                        strcpy((*gezegenler)[gezegenSayisi - 1]->orijinalTarih, tarih);}

                break;
            }
            case 2: {
                BuzDeviGezegen yeniBuz = BuzDeviGezegenOlustur(isim, gununKacSaatOldugu, tarih, 0.5);
                if (yeniBuz){ (*gezegenler)[gezegenSayisi++] = yeniBuz->super;
                        strcpy((*gezegenler)[gezegenSayisi - 1]->orijinalTarih, tarih);}

                break;
            }
            case 3: {
                CuceGezegen yeniCuce = CuceGezegenOlustur(isim, gununKacSaatOldugu, tarih, 0.01);
                if (yeniCuce) {(*gezegenler)[gezegenSayisi++] = yeniCuce->super;
                        strcpy((*gezegenler)[gezegenSayisi - 1]->orijinalTarih, tarih);}

                break;
            }
            default:
                printf("Bilinmeyen gezegen türü: %d. Satır atlandı.\n", gezegenTuru);
        }
    }

    fclose(file);
    return gezegenSayisi;
}
// Yapıcı
DosyaOkuma DosyaOkumaOlustur() {
    DosyaOkuma oku = malloc(sizeof(struct DOSYAOKUMA));
    oku->kisileriOku = &kisileriOku;
    oku->uzayAraclariniOku = &uzayAraclariniOku;
    oku->gezegenleriGetir = &gezegenleriGetir;
    return oku;
}
