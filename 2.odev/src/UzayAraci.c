/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 05.05.2025
* <p> 
* Uzay Aracı Sınıfı
* Bu kaynak dosyası, UzayAraci yapısının işlevlerini içerir.
* Uzay araçları, çıkış ve varış gezegenleri, kalkış ve hedef tarihleri,
* kalan yolculuk süresi ve mevcut durum bilgilerini tutar.
* Bu dosyada araç oluşturma, yola çıkma, hedefe kalan saat güncelleme, 
* imha etme, ekrana yazdırma ve bellek temizleme işlemleri tanımlanmıştır.
* </p> 
*/


#include "UzayAraci.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Kisi.h"
#include "Gezegen.h"
#include "KayacGezegen.h"
#include "GazDeviGezegen.h"
#include "BuzDeviGezegen.h"
#include "CuceGezegen.h"
#include "Simulasyon.h"
#include "Zaman.h"



//Yapici fonksiyon 
// Uzay aracı nesnesi oluşturur ve gerekli alanları başlatır.
UzayAraci UzayAraciOlustur(const char* isim, const char* cikisGezegeni,
                           const char* varisGezegeni, const char* cikisTarihi,
                           int mesafeSaat, Kisi* yolcular, int yolcuSayisi) {   
    UzayAraci uzayAraci = (UzayAraci)malloc(sizeof(struct UZAYARACI));
    if (!uzayAraci) {
        printf("[HATA] UzayAraci için bellek ayrılamadı!\n");
        return NULL;
    }

    uzayAraci->isim = strdup(isim);
    uzayAraci->cikisGezegeni = strdup(cikisGezegeni);
    uzayAraci->varisGezegeni = strdup(varisGezegeni);
    uzayAraci->cikisTarihi = strdup(cikisTarihi);
    uzayAraci->mesafeSaat = mesafeSaat;
    

    //Yolcular Kopyalanir.
    uzayAraci->yolcuSayisi = yolcuSayisi;
    uzayAraci->yolcuKapasite = yolcuSayisi;
    uzayAraci->setHedefeKalanSaat = &setHedefeKalanSaat;
    uzayAraci->yolcular = malloc(sizeof(Kisi*) * yolcuSayisi);
    if (!uzayAraci->yolcular) {
        printf("[HATA] Yolcu dizisi için bellek ayrılamadı!\n");
        free(uzayAraci); // Bellek sızıntısını önlemek için uzayAraci'nı da serbest bırakıyoruz.
        return NULL;
    }

    for (int i = 0; i < yolcuSayisi; i++) {
        uzayAraci->yolcular[i] = yolcular[i]; // Sadece pointeri kopyalıyoruz.
    }
    uzayAraci->imhaDurumu = 0;
    uzayAraci->hedefeKalanSaat = mesafeSaat;
    uzayAraci->yolaCiktiMi = 0;

    uzayAraci->varisTarihi = NULL;
    uzayAraci->varisTarihiHesaplandi = 0;

    // Metot atamaları
    uzayAraci->yolaCik = &yolaCik;
    uzayAraci->guncelleHedefeKalanSaat = &guncelleHedefeKalanSaat;
    uzayAraci->kontrolEt = &kontrolEt;
    uzayAraci->imhaEt = &imhaEt;
    uzayAraci->isYolaCiktiMi = &isYolaCiktiMi;
    uzayAraci->isCikisZamaniGeldi = &isCikisZamaniGeldi;
    uzayAraci->yoketUzayAraci = &yoketUzayAraci;

    return uzayAraci;
}

// Uzay aracini yola cikarir
void yolaCik(const UzayAraci this) {
    this->yolaCiktiMi = 1;
}

// Uzay aracinin hedefe kalan saatini gunceller
// Her simulasyon saati geçtikçe hedefe kalan saati 1 azaltır.
void guncelleHedefeKalanSaat(const UzayAraci this) {
    if (!this->imhaDurumu && this->hedefeKalanSaat > 0) {
        this->hedefeKalanSaat--;
    }
}

//Uzay aracinin icindeki yolcuların durumunu kontrol eder.
void kontrolEt( UzayAraci this, Simulasyon simulasyon) {

    int allDead = 1; // Başlangıçta tüm yolcuların öldüğü varsayılır.

    // Yolcularin icinde hâlâ hayatta olan var mi diye kontrol eder
    for (int i = 0; i < this->yolcuSayisi; i++) {
        if ((this->yolcular[i])->hayatta) {
            allDead = 0;
            break;
        }
    }
    // Eğer tüm yolcular ölmüşse, uzay aracı imha edilir
    if (allDead) {
        this->imhaEt(this);

    // Eğer araç imha edilmemişse ve varış tarihi henüz hesaplanmamışsa
    } else if (this->varisTarihi == NULL) {

        // Kalkış ve varış gezegenlerini simülasyon nesnesinden bulur.
        Gezegen cikisGezegen = simulasyon->getGezegenByName(simulasyon, this->cikisGezegeni);
        Gezegen varisGezegen = simulasyon->getGezegenByName(simulasyon, this->varisGezegeni);

        // Varis tarihini hesaplar.
        char* hesaplananTarih = hedefTarihiHesapla(simulasyon->zaman, this, cikisGezegen, varisGezegen);

        // Önceden atanmış varış tarihi varsa serbest birakilir.
        if (this->varisTarihi) free(this->varisTarihi); 

        // Yeni varis tarihi atanir.
        this->varisTarihi = hesaplananTarih;
    }
}
// Uzay aracinin imha edilmesini saglar
void imhaEt(const UzayAraci this) {
    this->imhaDurumu = 1;
}
// Uzay aracinin yola cikip cıkmadigini kontrol eder
int isYolaCiktiMi(const UzayAraci this) {
    return this->yolaCiktiMi;
}

// Uzay aracinin kalkis zamaninin gelip gelmedigini kontrol eder
int isCikisZamaniGeldi(const UzayAraci this, struct GEZEGEN* gezegen) {
    int gun, ay, yil, saat;
    sscanf(gezegen->tarih, "%d.%d.%d.%d", &gun, &ay, &yil, &saat);

    return !this->yolaCiktiMi &&
           strcmp(gezegen->tarih, this->cikisTarihi) == 0 &&
           saat == 0;
}

// Uzay aracinin hedefe kalan saatini ayarlar, günceller
void setHedefeKalanSaat(UzayAraci arac, int yeniSaat) {
    if (arac) {
        arac->hedefeKalanSaat = yeniSaat;
        //printf("[DEBUG] %s aracı için hedefe kalan saat %d olarak ayarlandı.\n", arac->isim, yeniSaat);
    }
}

// Uzay araci nesnesini yok eder
// Bellek sızıntısını önlemek için tüm bileşenleri serbest bırakır.
void yoketUzayAraci(const UzayAraci this) {
    if (!this) return;
    free(this->isim);
    free(this->cikisGezegeni);
    free(this->varisGezegeni);
    free(this->cikisTarihi);
    if (this->varisTarihi) free(this->varisTarihi);
   if (this->yolcular) free(this->yolcular); 
    free(this);
}
