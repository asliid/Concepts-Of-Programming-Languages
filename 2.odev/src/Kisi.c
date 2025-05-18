/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 05.05.2025
* <p> 
* Kişi Sınıfı
* Simülasyondaki bireyleri temsil eden sınıf.
* Her kişi ismi, yaşı, kalan ömrü ve içinde bulunduğu uzay aracı ile tanımlanır.
* Ayrıca yaşlanma katsayısı, biriken saat ve yaşam durumunu takip eder.
* Fonksiyon pointerları sayesinde nesne yönelimli benzetim yapılmıştır.
* </p>
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Kisi.h"


// "Constructor" fonksiyonu (Kisi oluşturuyoruz)
// Kişi ismi, yaşı, kalan ömrü ve bulunduğu aracın adı parametre olarak alınır.
Kisi kisiOlustur(const char* isim, int yas, double kalanOmur, const char* uzayAraciAdi) {
    Kisi newKisi = (Kisi)malloc(sizeof(struct KISI)); // Bellek ayırma
    if (newKisi == NULL) {
        printf("Bellek ayrilamadi!\n");
        return NULL;
    }
    
    newKisi->isim = strdup(isim); // isim için bellek ayırma
    newKisi->yas = yas;
    newKisi->kalanOmur = kalanOmur;
    newKisi->bulunduguArac = strdup(uzayAraciAdi);  // Uzay aracı adi için bellek ayırma
    newKisi->birikenSaat = 0.0;  // Yaslanma icin saat birikimi baslatilir

    // Fonksiyon göstericilerini islevlere atıyoruz
    newKisi->guncelleKalanOmur = &guncelleKalanOmur;
    newKisi->isAlive = &isAlive;
    newKisi->getKalanOmur = &getKalanOmur;
    newKisi->setKalanOmur = &setKalanOmur;
    newKisi->getYas = &getYas;
    newKisi->setYas = &setYas;
    newKisi->getIsim = &getIsim;
    newKisi->getBulunduguArac = &getBulunduguArac;
    
    newKisi->yaslanmaKatsayisi = 1.0;  // Varsayılan yaşlanma katsayısı
    newKisi->hayatta = 1; // Kişi başlangıçta hayattadır
    newKisi->kisiYokEt = &kisiYokEt;
    return newKisi;
}
// Kisi nesnesine ait belleği serbest bırakır.
void kisiYokEt(Kisi kisi) {
    if (kisi != NULL) {
        free(kisi->isim);
        free(kisi);
    }
}
// Simulasyon saatine göre kişinin yasini ve kalan omrunu gunceller.
// Yaslanma katsayisina göre biriken saat mantigi kullanilir.
void guncelleKalanOmur(Kisi kisi) {
    if (!kisi || !kisi->hayatta) return;

    double katsayi = kisi->yaslanmaKatsayisi;
    if (katsayi <= 0 || katsayi > 10) katsayi = 1.0;

    // Katsayılara göre biriken saat hesaplanıyor
    kisi->birikenSaat += katsayi;

    // Biriken saatler tam saat olunca yaş/ömür güncellenir
    int tamSaat = (int)(kisi->birikenSaat);
    kisi->birikenSaat -= tamSaat;

    kisi->yas += tamSaat;
    kisi->kalanOmur -= tamSaat;

    // Kalan omur sifir veya altına duserse kisi ölür
    if (kisi->kalanOmur <= 0) {
        kisi->hayatta = 0;
    }
}
int isAlive(const Kisi kisi) {return kisi->kalanOmur > 0;}

int getKalanOmur(const Kisi kisi) {return kisi->kalanOmur;}

void setKalanOmur(Kisi kisi, int omur) { kisi->kalanOmur = omur;}

int getYas(const Kisi kisi) {return kisi->yas;}

void setYas(Kisi kisi, int yas) {kisi->yas = yas;}

const char* getIsim(const Kisi kisi) {return kisi->isim;}

const char* getBulunduguArac(const Kisi kisi) {
    return kisi->bulunduguArac;
}