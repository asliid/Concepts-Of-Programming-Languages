/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 05.05.2025
* <p> 
* Zaman Sınıfı Başlık Dosyası
* Uzay aracının varış zamanını ve tarihini yönetir.
* Zamanın ilerlemesi, hedef tarihin hesaplanması ve zamanın güncellenmesi gibi işlemleri içerir.
* </p> 
*/
#ifndef ZAMAN_H
#define ZAMAN_H

#include "UzayAraci.h"

#include "Gezegen.h"
#include <stdio.h>

struct UZAYARACI; 
struct GEZEGEN;

struct ZAMAN {
    int saat; // Simülasyon saati
    
    // Fonksiyon pointerları (nesne yönelimli benzetim için)
    int (*getSaat)(struct ZAMAN*); 
    void (*gec)(struct ZAMAN*); // Zamanı ilerletir (simulasyon zamanına göre 1 saat artırır)
    char* (*hedefTarihiHesapla)(struct ZAMAN*, struct UZAYARACI*, struct GEZEGEN*, struct GEZEGEN*); // Hedef gezegene varış tarihini hesaplar
    void (*ZamanYokEt)(struct ZAMAN*);
};
//Benzetim 
typedef struct ZAMAN* Zaman;

// Yapıcı
Zaman ZamanOlustur();  // Yeni bir ZAMAN nesnesi oluşturulur.

#endif