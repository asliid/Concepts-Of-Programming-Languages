/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 05.05.2025
* <p> 
* Buz Devi Gezegeni Sınıfı Başlık Dosyası
* Gezegen soyut yapısından türetilmiştir.
* Yaşlanma katsayısı ve yok etme işlemlerini içerir. 
* Kalıtım benzetimi struct ile yapılmıştır.
* </p> 
*/

#ifndef BUZDEVIGEZEGEN_H
#define BUZDEVIGEZEGEN_H


#include "Gezegen.h"

/// Buz Devi Gezegenini temsil eden yapı.
/// Gezegen türünden kalıtım alır (super).
struct BUZDEVIGEZEGEN
{
    Gezegen super; // Temel Gezegen yapısı (kalıtım benzeri kullanım)
    double yaslanmaKatsayisi;

    // Fonksiyon pointer'ları
    void (*yoket)(struct BUZDEVIGEZEGEN*);  // Bellek temizleme fonksiyonu
    void (*guncelleNufus)(struct GEZEGEN*);   // Gezegen üzerindeki nüfusu güncelleyen fonksiyon

};
typedef struct BUZDEVIGEZEGEN* BuzDeviGezegen; //Benzetim 
// Fonksiyon prototipleri

/// Yeni bir Buz Devi gezegeni oluşturur.
/// @param isim Gezegen adı
/// @param saat Bir günün kaç saatten oluştuğu
/// @param tarih Tarih bilgisi 
/// @param yaslanma Yaşlanma katsayısı (0.5)
BuzDeviGezegen BuzDeviGezegenOlustur(const char* isim, int saat, const char* tarih, double yaslanma);

// Buz Devi gezegeninin yaşlanma katsayısını döner
double YaslanmaBuzDevi(const Gezegen );

//Buz Devi gezegenini yok eder.
void BuzDeviniYokEt(const BuzDeviGezegen);

// Buz Devi gezegeninin nüfusunu döner
int BuzDeviGezegenGetNufus(struct GEZEGEN* this);

// Buz devi gezegen için nüfus güncelleme işlemi
void guncelleNufus(Gezegen gezegen);

#endif