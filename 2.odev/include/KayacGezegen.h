/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 05.05.2025
* <p> 
* Kayaç Gezegeni Sınıfı Başlık Dosyası
* Gezegen soyut yapısından türetilmiştir.
* Yaşlanma katsayısı ve yok etme işlemlerini içerir. 
* Kalıtım benzetimi struct ile yapılmıştır.
* </p> 
*/

#ifndef KAYAC_GEZEGEN_H
#define KAYAC_GEZEGEN_H

#include "Gezegen.h"
/// Kayaç Gezegenini temsil eden yapı.
/// Gezegen türünden kalıtım alır (super).
struct KAYACGEZEGEN
{
    Gezegen super;  // Temel Gezegen yapısı (kalıtım benzeri kullanım)
    double yaslanmaKatsayisi;  // Kayac gezegeninin yaslanma katsayısı
    
    // Fonksiyon pointer'ları
    void (*yoket)(struct KAYACGEZEGEN*);  // Bellek temizleme fonksiyonu
    void (*guncelleNufus)(struct GEZEGEN*);   // Gezegen üzerindeki nüfusu güncelleyen fonksiyon

};

typedef struct KAYACGEZEGEN* KayacGezegen;
// Fonksiyon prototipleri

/// Yeni bir Kayaç Gezegen oluşturur.
/// @param isim Gezegen adı
/// @param saat Bir günün kaç saatten oluştuğu
/// @param tarih Tarih bilgisi 
/// @param yaslanma Yaşlanma katsayısı (0.0-normal süre)
KayacGezegen KayacGezegenOlustur(const char* isim, int saat, const char* tarih, double yaslanma);

// Kayaç gezegeninin yaşlanma katsayısını döner
double YaslanmaKayac(const Gezegen );

// Kayaç gezegenini yok eder.
void KayaciYokEt(const KayacGezegen );

// Kayaç gezegeninin nüfusunu döner
int KayacGezegenGetNufus(struct GEZEGEN* this);

// Kayaç gezegeninin nüfusunu döner
void guncelleNufus(Gezegen gezegen);

#endif