/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 05.05.2025
* <p> 
* Dosya Okuma Sınıfı Başlık Dosyası
* Kişi, Uzay Aracı ve Gezegen bilgilerini dosyadan okur.
* Kalıtım benzetimi struct ile yapılmıştır. 
* </p> 
*/

#ifndef DOSYAOKUMA_H
#define DOSYAOKUMA_H

#include "Kisi.h"
#include "KayacGezegen.h"
#include "GazDeviGezegen.h"
#include "BuzDeviGezegen.h"
#include "CuceGezegen.h"
#include "UzayAraci.h"

struct DOSYAOKUMA {
    // Fonksiyon pointerları
    Kisi* (*kisileriOku)(const char* dosyaAdi, int* kisiSayisi); // Kişileri okur
    UzayAraci* (*uzayAraclariniOku)(const char* dosyaAdi, Kisi* kisiler, int kisiSayisi, int* uzayAracSayisi); // Uzay araçlarını okur
    int (*gezegenleriGetir)(const char* dosyaAdi, Gezegen** gezegenler);//  Gezegenleri okur
};
typedef struct DOSYAOKUMA* DosyaOkuma;
// Constructor
DosyaOkuma DosyaOkumaOlustur();

#endif // DOSYAOKUMA_H