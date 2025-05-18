/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 05.05.2025
* <p> 
* Gezegen Sınıfı </p> 
* Bu dosya, temel gezegen yapısını ve gezegene ait davranışları (tarih güncelleme, nüfus işlemleri) tanımlar.
* Farklı gezegen türleri bu sınıftan türetilerek oluşturulmuştur.
* Ayrıca gezegenlerin bellek yönetimi ve yok etme işlemlerini de içerir.
*/

#include "Gezegen.h"
#include "Kisi.h"
#include "KayacGezegen.h"
#include "GazDeviGezegen.h"
#include "BuzDeviGezegen.h"
#include "UzayAraci.h"
#include "DosyaOkuma.h"
#include <stdio.h>
#include <stdlib.h>

// Gezegen oluşturucu fonksiyon
Gezegen GezegenOlustur(const char* isim, int saat, const char* tarih) {
    Gezegen gezegen = (Gezegen)malloc(sizeof(struct GEZEGEN));
    if (!gezegen) {
        printf("Bellek ayrilamadi!\n");
        return NULL;
    }

    gezegen->isim = strdup(isim);
    gezegen->gununKacSaatOldugu = saat;

    gezegen->tarih = malloc(50); // 50 karakterlik alan açıyoruz
    if (!gezegen->tarih) {
        printf("Tarih için bellek ayrilamadi!\n");
        free(gezegen);
        return NULL;
    }
    strcpy(gezegen->tarih, tarih); // Tarihi kopyalar

    // Fonksiyon atamaları
    gezegen->guncelleTarih = &guncelleTarih;
    gezegen->nufusHesapla = &nufusHesapla;
    gezegen->guncelleNufus = &guncelleNufus;
    gezegen->yoketGezegen = &yoketGezegen;
    gezegen->yaslanma = NULL; // Türe gore atanaır

    gezegen->getNufus = &getNufusDefault;
    gezegen->resetNufus = &resetNufusDefault;
    gezegen->addKisi = &addKisiDefault;
    gezegen->removeKisi = &removeKisiDefault;

    gezegen->nufus = malloc(sizeof(Kisi*) * 100); // Başlangıçta 100 kişilik alan açıyoruz
    gezegen->nufusSayisi = 0;
    gezegen->nufusKapasite = 100;

    return gezegen;
}

// Gezegen yok et fonksiyonu
// Bellek temizligi yapar
// Bu fonksiyon, gezegenin tüm dinamik bellek alanlarını serbest bırakır.
void yoketGezegen(const Gezegen this) {
    if (!this) return;
    free(this->isim);
    free(this->tarih);
    if (this->nufus) free(this->nufus);
    free(this);
}

// Ayin kac gün surdugunu hesaplar (artık yıl kontrolü dahil)
static int ayGunSayisi(int ay, int yil) {
    static int gunler[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (ay == 2 && ((yil % 4 == 0 && yil % 100 != 0) || (yil % 400 == 0)))
        return 29;
    return gunler[ay];
}

// Gezegenin tarihini simülasyon saatine göre günceller
void guncelleTarih(Gezegen gezegen, int simulasyonSaati) {
    int basGun, basAy, basYil;
    int saatPerGun = gezegen->gununKacSaatOldugu;

    // Gezegenin txtteki tarihini okur
    sscanf(gezegen->orijinalTarih, "%d.%d.%d", &basGun, &basAy, &basYil);

    // Toplam saat → gün ve saat olarak ayrilir
    int toplamSaat = simulasyonSaati;
    int ekGun = toplamSaat / saatPerGun;
    int ekSaat = toplamSaat % saatPerGun;

    // Baslangic tarihine ekle
    int gun = basGun + ekGun;
    int ay = basAy;
    int yil = basYil;

    while (gun > ayGunSayisi(ay, yil)) {
        gun -= ayGunSayisi(ay, yil);
        ay++;
        if (ay > 12) {
            ay = 1;
            yil++;
        }
    }

    // Yeni tarih hesaplandı → string olarak yaz
    snprintf(gezegen->tarih, 50, "%02d.%02d.%04d.%02d", gun, ay, yil, ekSaat);

}
// Nufus hesaplama 
void nufusHesapla(struct GEZEGEN* gezegen, struct UZAYARACI** uzayAraclari, int uzayAraciSayisi) {
    gezegen->nufusSayisi = 0;

    for (int i = 0; i < uzayAraciSayisi; i++) {
        UzayAraci arac = uzayAraclari[i];

        // Cikis gezegeninde ve yola cikmadiysa
        if (strcmp(arac->cikisGezegeni, gezegen->isim) == 0 && !arac->isYolaCiktiMi(arac)) {
            for (int j = 0; j < arac->yolcuSayisi; j++) {
                Kisi kisi = (arac->yolcular[j]);   // Kisi zaten Kisi* tipinde
                if (kisi && kisi->hayatta) {
                    gezegen->addKisi(gezegen, kisi);
                }
            }
        }

        // Varis gezegenine ulastiysa
        if (strcmp(arac->varisGezegeni, gezegen->isim) == 0 && arac->hedefeKalanSaat == 0) {
            for (int j = 0; j < arac->yolcuSayisi; j++) {
                Kisi kisi = (arac->yolcular[j]); 
                if (kisi && kisi->hayatta) {
                    gezegen->addKisi(gezegen, kisi);
                }
            }
        }
        
    }
}
//Her kisiyi yaslandirir, ölenleri nufustan cikarir
// Her bir kisinin yasını ve kalan omrunu gunceller.
// Bu islem, gezegenin yaslanma katsayısına baglı olarak yapilir.
void guncelleNufus(const Gezegen gezegen) {
    double katsayi = gezegen->yaslanma ? gezegen->yaslanma(gezegen) : 1.0;
    if (katsayi <= 0) katsayi = 1.0;

    int i = 0;
    while (i < gezegen->nufusSayisi) {
        Kisi kisiPtr = gezegen->nufus[i];

        if (!kisiPtr) {
            i++;
            continue;
        }

        kisiPtr->yas += katsayi;
        kisiPtr->kalanOmur -= katsayi;

   
        if (kisiPtr->kalanOmur <= 0) {
            kisiPtr->hayatta = 0;

            for (int k = i; k < gezegen->nufusSayisi - 1; k++) {
                gezegen->nufus[k] = gezegen->nufus[k + 1];
            }
            gezegen->nufus[gezegen->nufusSayisi - 1] = NULL;
            gezegen->nufusSayisi--;
            continue;
        }

        i++;
    }
}

// Default fonksiyonlar
int getNufusDefault(Gezegen this) {
    return this->nufusSayisi;
}

//  Nufusu sifirlar
void resetNufusDefault(Gezegen this) {
    this->nufusSayisi = 0;
}

//  Eger mevcut kapasite dolmussa, nufus kapasitesini iki katına cikarir
void addKisiDefault(Gezegen this, Kisi kisi) {
    // Kapasite yetersizse arttır
    if (this->nufusSayisi >= this->nufusKapasite) {
        int yeniKapasite = this->nufusKapasite * 2;
        Kisi* yeniNufus = realloc(this->nufus, sizeof(Kisi) * yeniKapasite);
        if (!yeniNufus) {
            fprintf(stderr, " Bellek genişletilemedi! Hata %s\n", kisi->isim);
            return;
        }
        this->nufus = yeniNufus;
        this->nufusKapasite = yeniKapasite;
    }

    this->nufus[this->nufusSayisi++] = kisi;
}

//  Bu fonksiyon, kisiyi nufus dizisinden cikarir ve diziyi gunceller.
void removeKisiDefault(Gezegen this, Kisi kisi) {
    for (int i = 0; i < this->nufusSayisi; i++) {
        if (this->nufus[i] == kisi) {
            for (int j = i; j < this->nufusSayisi - 1; j++) {
                this->nufus[j] = this->nufus[j + 1];
            }
            this->nufusSayisi--;
            break;
        }
    }
}