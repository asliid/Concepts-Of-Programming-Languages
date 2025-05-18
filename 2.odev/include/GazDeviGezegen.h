/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 05.05.2025
* <p> 
* Gaz Devi Gezegeni Sınıfı Başlık Dosyası
* Gezegen soyut yapısından türetilmiştir.
* Yaşlanma katsayısı ve yok etme işlemlerini içerir. 
* Kalıtım benzetimi struct ile yapılmıştır.
* </p> 
*/

#ifndef GAZ_DEVI_GEZEGEN_H
#define GAZ_DEVI_GEZEGEN_H


#include "Gezegen.h"
/// Gaz Devi Gezegenini temsil eden yapı.
/// Gezegen türünden kalıtım alır (super).
struct GAZDEVIGEZEGEN {

    Gezegen super;   // Temel Gezegen yapısı (kalıtım benzeri kullanım)
    double yaslanmaKatsayisi;

    // Fonksiyon pointer'ları
    void (*yoket)(struct GAZDEVIGEZEGEN*);  // Bellek temizleme fonksiyonu
    void (*guncelleNufus)(struct GEZEGEN*);  // Gezegen üzerindeki nüfusu güncelleyen fonksiyon

};

typedef struct GAZDEVIGEZEGEN* GazDeviGezegen;
// Fonksiyon prototipleri

/// Yeni bir Gaz Devi Gezegeni oluşturur.
/// @param isim Gezegen adı
/// @param saat Bir günün kaç saatten oluştuğu
/// @param tarih Tarih bilgisi 
/// @param yaslanma Yaşlanma katsayısı (0.1)
GazDeviGezegen GazDeviGezegenOlustur(const char* isim, int saat, const char* tarih, double yaslanma);

// Gaz Devi gezegeninin yaşlanma katsayısını döner
double YaslanmaGazDevi(const Gezegen);

//Gaz Devi gezegenini yok eder.
void GazDeviniYokEt(const GazDeviGezegen);

// Gaz Devi gezegeninin yaşlanma katsayısını döner
int GazDeviGezegenGetNufus(struct GEZEGEN* this);

// Gaz Devi gezegeninin nüfusunu döner
void guncelleNufus(Gezegen gezegen);

#endif