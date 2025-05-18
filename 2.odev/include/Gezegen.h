/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 05.05.2025
* <p> 
* Gezegen Sınıfı Başlık Dosyası
* Temel gezegen sınıfıdır.
* Gezegen türleri (Kayaç, Gaz Devi, Buz Devi, Çüce) bu sınıftan türetilmiştir.
* Bu yapı her gezegenin ismini, tarihini, saat bilgilerini ve nufus bilgilerini içerir.
* Ayrıca nufus yönetimi, tarih güncelleme, yaşlanma oranı gibi işlemler için fonksiyonlar barındırır.
* Kalıtım benzetimi struct ile yapılmıştır.
* </p> 
*/
#ifndef GEZEGEN_H
#define GEZEGEN_H

#include "Kisi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct UZAYARACI;  // UzayAraci ön tanımı
typedef struct UZAYARACI* UzayAraci;

struct GEZEGEN {
    char* isim;                      // Gezegenin ismi
    int gununKacSaatOldugu;         // Bu gezegende 1 günün kaç saat sürüdüğü
    char* tarih;                    // Mevcut tarih bilgisi 
    
    Kisi* nufus;                    // Bu gezegende yaşayan kişi dizisi
    int nufusSayisi;                // Toplam kişi sayısı
    int nufusKapasite;              // Nüfus dizisinin kapasitesi
    
    void* self;                     // Kalıtım için gezegenin kendi türünü tutar
    char orijinalTarih[50];        // Başlangıç tarih bilgisi

    // Fonksiyon Pointerları
    void (*guncelleTarih)(struct GEZEGEN*, int simulasyonSaati); // Simülasyon saatine göre tarihi günceller
    void (*nufusHesapla)(struct GEZEGEN*, struct UZAYARACI**, int); // Nüfusu uzay aracı verilerine göre hesaplar
    void (*guncelleNufus)(struct GEZEGEN*); // Kişilerin yaşlanması vb. işlemleri gerçekleştirir
    void (*yoketGezegen)(struct GEZEGEN*); // Bellek temizliği yapar
    double (*yaslanma)(struct GEZEGEN*); // gezegendeki yaşlanma katsayısını döner
    int (*getNufus)(struct GEZEGEN*); // mevcut nufus sayısını verir
    void (*resetNufus)(struct GEZEGEN*); // Nüfus dizisini sıfırlar (temizler)
    void (*addKisi)(struct GEZEGEN*, Kisi kisi); // Gezegen nüfusuna kişi ekler
    void (*removeKisi)(struct GEZEGEN*, Kisi kisi); // Gezegen nüfusundan kişi çıkarır
};

typedef struct GEZEGEN* Gezegen;

// Fonksiyon prototipleri
/// Yeni bir gezegen oluşturan yapıcı fonksiyon.
/// @param isim Gezegen adı
/// @param saat Bir günün kaç saatten oluştuğu
/// @param tarih Tarih bilgisi
/// @return Yeni oluşturulan gezegen
/// @note Bu fonksiyon, gezegen türüne göre (Kayaç, Gaz Devi, Buz Devi, Çüce) uygun yapıcıyı çağırır.
Gezegen GezegenOlustur(const char* isim, int saat, const char* tarih);

//Yok etme işlemi
void yoketGezegen(const Gezegen);

// Gezegenin kişi sayısını döner (varsayılan getNufus fonksiyonu)
int getNufusDefault(Gezegen this);
// Gezegenin nüfus dizisini sıfırlar 
void resetNufusDefault(Gezegen this);
//Bir kişiyi gezegenin nüfusuna ekler
void addKisiDefault(Gezegen this, Kisi kisi);
//Bir kişiyi gezegenin nüfusundan çıkarır
void removeKisiDefault(Gezegen this, Kisi kisi);

void guncelleTarih(Gezegen gezegen, int simulasyonSaati); // Tarihi günceller
void nufusHesapla(struct GEZEGEN* gezegen, struct UZAYARACI** uzayAraclari, int uzayAraciSayisi);// Nüfusu hesaplar
void guncelleNufus(Gezegen);// Kişilerin yaşlanmasını günceller
#endif