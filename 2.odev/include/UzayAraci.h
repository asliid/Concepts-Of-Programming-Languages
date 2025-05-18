/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 05.05.2025
* <p> 
* Uzay Aracı Sınıfı Başlık Dosyası
*</p> 
* Uzay aracı sınıfı, uzay aracının özelliklerini ve metodlarını tanımlar. 
*/
#ifndef UZAY_ARACI_H
#define UZAY_ARACI_H

#include <stdio.h>

// KISI, GEZEGEN ve SIMULASYON yapıları sadece tip olarak tanımlanır,
// içeriği diğer dosyalarda yer alır.
struct KISI;
typedef struct KISI* Kisi;
struct GEZEGEN;
typedef struct GEZEGEN* Gezegen;
struct SIMULASYON;
typedef struct SIMULASYON* Simulasyon;
struct ZAMAN;
typedef struct ZAMAN* Zaman;


struct UZAYARACI {
    char* isim;
    char* cikisGezegeni;
    char* varisGezegeni;
    char* cikisTarihi;
    int mesafeSaat;

    Kisi* yolcular;  // Yolcu dizisi (kişiler)
    int yolcuSayisi; // Mevcut yolcu sayısı
    int yolcuKapasite; // Maksimum yolcu kapasitesi

    int imhaDurumu; // 1 ise araç imha edilmiştir
    int hedefeKalanSaat; // Araç yola çıktı mı? (1: evet, 0: hayır)
    int yolaCiktiMi;

    char* varisTarihi;
    int varisTarihiHesaplandi;

    void (*yolaCik)(struct UZAYARACI*);
    void (*guncelleHedefeKalanSaat)(struct UZAYARACI*); // Varışa kalan saati azaltır
    void (*kontrolEt)(struct UZAYARACI*, struct SIMULASYON*); // Aracın durumuu kontrol eder
    void (*imhaEt)(struct UZAYARACI*);
    int  (*isYolaCiktiMi)(struct UZAYARACI*);
    int  (*isCikisZamaniGeldi)(struct UZAYARACI*, struct GEZEGEN*); // Kalkış zamanı kontrolü
    void (*yoketUzayAraci)(struct UZAYARACI*);
    void (*setVarisTarihi)(struct UZAYARACI*, const char* tarih);
    void (*setHedefeKalanSaat)(struct UZAYARACI*, int saat);
};

//Benzetim 
typedef struct UZAYARACI* UzayAraci;
// Fonksiyonlar
void setHedefeKalanSaat(UzayAraci arac, int yeniSaat); // Uzay aracının hedefe kalan saatini ayarlar.
void yolaCik(const UzayAraci this); // Uzay aracını yola çıkarır 
void guncelleHedefeKalanSaat(const UzayAraci this); // Her simulasyon saati geçtikçe hedefe kalan saati 1 azaltır.
void kontrolEt(const UzayAraci this, Simulasyon simulasyon); // Yolcuların hayatta olup olmadığını kontrol eder, gerekiyorsa aracı imha eder.
void imhaEt(const UzayAraci this);
int  isYolaCiktiMi(const UzayAraci this);
int  isCikisZamaniGeldi(const UzayAraci this, const Gezegen);
char* hedefTarihiHesapla(Zaman this, UzayAraci uzayAraci, Gezegen cikisGezegen, Gezegen varisGezegen);

/**
 * Yeni bir uzay aracı oluşturur.
 * @param isim              Uzay aracının ismi
 * @param cikisGezegeni     Kalkış gezegeni adı
 * @param varisGezegeni     Varış gezegeni adı
 * @param cikisTarihi       Kalkış tarihi
 * @param mesafeSaat        Hedefe varmak için gereken saat
 * @param yolcular          Kişi dizisi (yolcular)
 * @param yolcuSayisi       Yolcu sayısı
 * @return UzayAraci        Yeni oluşturulan uzay aracı nesnesi
 */
UzayAraci UzayAraciOlustur(const char* isim, const char* cikisGezegeni,
                           const char* varisGezegeni, const char* cikisTarihi,
                           int mesafeSaat, Kisi* yolcular, int yolcuSayisi);
void yoketUzayAraci(const UzayAraci);                           

#endif