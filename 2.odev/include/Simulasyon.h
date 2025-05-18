/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 05.05.2025
* <p> 
* Simulasyon Sınıfı Başlık Dosyası
* Simulasyon sınıfı, gezegenler, uzay araçları ve kişileri içeren bir simülasyonu temsil eder.
* Simülasyonun başlangıç, güncelleme ve bitiş durumlarını kontrol eden fonksiyonları içerir.
* Simülasyon, gezegenlerin ve uzay araçlarının durumunu güncelleyerek simülasyonu ilerletir.
* Simülasyon sınıfı, gezegenler ve uzay araçları arasındaki etkileşimleri yönetir.
* </p> 
*/

#ifndef SIMULASYON_H
#define SIMULASYON_H

#include "Gezegen.h"
#include "UzayAraci.h"
#include "Kisi.h"
#include "DosyaOkuma.h"
#include "Zaman.h"

/**
 * Simülasyon yapısı
 * Burası tüm gezegenleri, uzay araçlarını, kişileri ve simülasyon saatini içerir.
 * Zamanın ilerlemesi, uzay araçlarının hareketi, kişilerin yaşlanması ve gezegenlerin güncellenmesi
 * gibi işlemleri kontrol eden işlevleri barındırır.
 */
struct SIMULASYON {
    Gezegen* gezegenler; // Gezegen dizisi
    int gezegenSayisi;
    UzayAraci* uzayAraclari; // Uzay aracı dizisi
    int uzayAracSayisi;
    Kisi* kisiler;  // Kişiler dizisi
    int kisiSayisi;
    int simulasyonSaati;
    Zaman zaman;  // Zaman işlemlerini yöneten yapı

    // Metotlar
    void (*baslat)(struct SIMULASYON*);
    Gezegen (*getGezegenByName)(struct SIMULASYON*, const char*);
    int (*isKalkisZamaniGeldi)(struct SIMULASYON*, UzayAraci, Gezegen);
    void (*displayGezegenler)(struct SIMULASYON*); // Gezegenleri yazdırır
    void (*displayUzayAraclari)(struct SIMULASYON*); // Uzay araçlarını yazdırır
    void (*displayFinalDurum)(struct SIMULASYON*);
    int (*isSimulasyonBitti)(struct SIMULASYON*);
    void (*updateUzayAraclari)(struct SIMULASYON*); // Uzay araçlarını günceller
    void (*updateGezegenler)(struct SIMULASYON*); // Gezegenleri günceller
    void (*uzayAraciHareketi)(struct SIMULASYON*, UzayAraci); // Uzay aracının hareketini yönetir

};
//Benzetim 
typedef struct SIMULASYON* Simulasyon;
int isSimulasyonBitti(const Simulasyon);


// Yapıcı fonksiyon
/**
 * Yeni bir Simülasyon nesnesi oluşturur.
 * @param gezegenler Gezegen dizisi
 * @param gezegenSayisi Gezegen sayısı
 * @param uzayAraclari Uzay aracı dizisi
 * @param uzayAracSayisi Uzay aracı sayısı
 * @param zaman Zaman yönetim yapısı
 * @param kisiler Kişi dizisi
 * @param kisiSayisi Kişi sayısı
 * @return Simulasyon Yeni oluşturulan simülasyon nesnesi
 */
Simulasyon SimulasyonOlustur(Gezegen* gezegenler, int gezegenSayisi, UzayAraci* uzayAraclari, int uzayAracSayisi, Zaman zaman, Kisi* kisiler, int kisiSayisi);

#endif