/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 05.05.2025
* <p> 
* Cüce Gezegeni Sınıfı Başlık Dosyası
* Gezegen soyut yapısından türetilmiştir.
* Yaşlanma katsayısı ve yok etme işlemlerini içerir. 
* Kalıtım benzetimi struct ile yapılmıştır.
* </p> 
*/
#ifndef CUCEGEZEGEN_H
#define CUCEGEZEGEN_H


#include "Gezegen.h"
/// Cüce Gezegenini temsil eden yapı.
/// Gezegen türünden kalıtım alır (super).
struct CUCEGEZEGEN
{
    Gezegen super; // Temel Gezegen yapısı (kalıtım benzeri kullanım)
    double yaslanmaKatsayisi;

    // Fonksiyon pointer'ları
    void (*yoket)(struct CUCEGEZEGEN*); // Bellek temizleme fonksiyonu
    void (*guncelleNufus)(struct GEZEGEN*);  // Gezegen üzerindeki nüfusu güncelleyen fonksiyon


};
typedef struct CUCEGEZEGEN* CuceGezegen; //Benzetim 
// Fonksiyon prototipleri

/// Yeni bir Cüce Gezegen oluşturur.
/// @param isim Gezegen adı
/// @param saat Bir günün kaç saatten oluştuğu
/// @param tarih Tarih bilgisi 
/// @param yaslanma Yaşlanma katsayısı (0.01)
CuceGezegen CuceGezegenOlustur(const char* isim, int saat, const char* tarih, double yaslanma);

// Cüce gezegeninin yaşlanma katsayısını döner
double YaslanmaCuce(const Gezegen );

//Cüce gezegenini yok eder.
void CuceYokEt(const CuceGezegen );

// Cüce gezegeninin nüfusunu döner
int CuceGezegenGetNufus(struct GEZEGEN* this);

// Cüce gezegen için nüfus güncelleme işlemi
void guncelleNufus(Gezegen gezegen);
#endif