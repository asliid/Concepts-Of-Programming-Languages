/**
* @author Aslı Döngez
* @since 05.05.2025
*
* Kişi Sınıfı 
* <p> 
* Her kişi; isim, yaş, kalan ömür, bulunduğu araç gibi özellikler taşır.
* Ayrıca yaşlanma oranı, yaşam durumu ve çeşitli erişim metotları içerir.
* Bu yapı simülasyonda gezegen ve araç durumlarına göre bireylerin yaşlanmasını ve ölümünü kontrol eder.
*<p> 
*/

#ifndef KISI_H
#define KISI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UzayAraci.h"  // Uzay aracı yapısını önden bildir
#include "Gezegen.h"     // Zaman yapısını önden bildir   

struct KISI {
    char* isim;
    double yas;
    double kalanOmur; // Ölmeden önceki kalan süresi (saat)
    char* bulunduguArac;
    int hayatta; // 1: Yaşıyor, 0: Ölü
    double yaslanmaKatsayisi;   // Gezegen türüne göre yaşlanma katsayısı
    double birikenSaat;   // Saat bazlı yaş biriktirmek için kullanılır

    // Fonksiyon göstericileri (method benzeri)
    void (*guncelleKalanOmur)(struct KISI*); // Kalan ömrü günceller
    int  (*isAlive)(struct KISI*); // Kişinin yaşayıp yaşamadığını kontrol eder
    int  (*getKalanOmur)(struct KISI*); 
    void (*setKalanOmur)(struct KISI*, int); 
    int  (*getYas)(struct KISI*); 
    void (*setYas)(struct KISI*, int); 
    const char* (*getIsim)(struct KISI*); 
    const char* (*getBulunduguArac)(struct KISI*); 
    
    void (*kisiYokEt)(struct KISI*);  // bellek temizleme
};

typedef struct KISI* Kisi; // Kisi yapısını pointer olarak tanımlar

/// @brief Yeni bir kişi oluşturur
/// @param isim Kişinin adı
/// @param yas Başlangıç yaşı
/// @param kalanOmur Kalan ömür (saat cinsinden)
/// @param uzayAraciAdi Bulunduğu uzay aracı
Kisi kisiOlustur(const char* isim, int yas, double kalanOmur, const char* uzayAraciAdi);

//--Yardımcı Fonksiyonlar--//
void guncelleKalanOmur(Kisi kisi);
int isAlive(Kisi kisi);
int getKalanOmur(Kisi kisi);
void setKalanOmur(Kisi kisi, int omur);
int getYas(Kisi kisi);
void setYas(Kisi kisi, int yas);
const char* getIsim(Kisi kisi);
const char* getBulunduguArac(Kisi kisi);
void kisiYokEt(Kisi kisi);

#endif