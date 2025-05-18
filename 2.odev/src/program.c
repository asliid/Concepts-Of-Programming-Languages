/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 05.05.2025
* <p> 
* Main Program Sınıfı
* Simülasyonun başlatıldığı ve tüm bileşenlerin oluşturulduğu ana program.
* Bu program, kişileri, uzay araçlarını ve gezegenleri dosyadan okur.
* Simülasyon nesnesini oluşturur ve simülasyonu başlatır.
* Simülasyon sırasında bellek temizliği ve hata kontrolü sağlar.
* </p> 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Kisi.h"
#include "Gezegen.h"
#include "UzayAraci.h"
#include "DosyaOkuma.h"
#include "Simulasyon.h"
#include "Zaman.h"
#include "Exception.h"  

int main() {
    // Dosya okuma nesnesini olusturulur
    DosyaOkuma oku = DosyaOkumaOlustur();

    // Kişiler Kisiler.txt dosyasından okunur
    int kisiSayisi = 0;
    Kisi* kisiler = oku->kisileriOku("Kisiler.txt", &kisiSayisi);
    if (!kisiler || kisiSayisi == 0) {
        Exception e = ExceptionOlustur("Kisiler okunamadi veya bulunamadi!");
        printf("HATA: %s\n", e->getMessage(e));
        e->yoket(e);
        return 1;
    }

    // Uzay araclari Araclar.txt dosyasindan okunur
    int uzayAracSayisi = 0;
    UzayAraci* uzayAraclari = oku->uzayAraclariniOku("Araclar.txt", kisiler, kisiSayisi, &uzayAracSayisi);
    if (!uzayAraclari || uzayAracSayisi == 0) {
        Exception e = ExceptionOlustur("Uzay Araclari okunamadi veya bulunamadi!");
        printf("HATA: %s\n", e->getMessage(e));
        e->yoket(e);
        return 1;
    }

    // Gezegenleri Gezegenler.txt dosyasından okur

    int gezegenSayisi = 0;
    Gezegen* gezegenler = NULL;
    gezegenSayisi = oku->gezegenleriGetir("Gezegenler.txt", &gezegenler);
    if (!gezegenler || gezegenSayisi == 0) {
        Exception e = ExceptionOlustur("Gezegenler okunamadi veya bulunamadi!");
        printf("HATA: %s\n", e->getMessage(e));
        e->yoket(e);
        return 1;
    }

    // Zaman nesnesi oluşturulur
    Zaman zaman = ZamanOlustur();
    if (!zaman) {
        Exception e = ExceptionOlustur("Zaman nesnesi oluşturulamadı!");
        printf("HATA: %s\n", e->getMessage(e));
        e->yoket(e);
        return 1;
    }

    //Simulasyon nesnesini oluştur
    Simulasyon simulasyon = SimulasyonOlustur(gezegenler, gezegenSayisi, uzayAraclari, uzayAracSayisi, zaman, kisiler, kisiSayisi);
    if (!simulasyon) {
        Exception e = ExceptionOlustur("Simulasyon nesnesi NULL! Bellek ayrilamamis olabilir veya baska bir hata var.");
        printf("HATA: %s\n", e->getMessage(e));
        e->yoket(e);
        zaman->ZamanYokEt(zaman);
        return 1;
    }

    //Simulasyonu baslatilir.
    simulasyon->baslat(simulasyon);

    // Bellek temizliği yapilir
    for (int i = 0; i < uzayAracSayisi; i++) {
        if (uzayAraclari[i]->yolcular) {
            free(uzayAraclari[i]->yolcular);
            uzayAraclari[i]->yolcular = NULL;
        }
        if (uzayAraclari[i]) {
            uzayAraclari[i]->yoketUzayAraci(uzayAraclari[i]);
        }
    }
    free(uzayAraclari);

    for (int i = 0; i < gezegenSayisi; i++) {
        if (gezegenler[i]) {
            gezegenler[i]->yoketGezegen(gezegenler[i]);
        }
    }
    free(gezegenler);

    for (int i = 0; i < kisiSayisi; i++) {
        if (kisiler[i]) {
            kisiler[i]->kisiYokEt(kisiler[i]);
        }
    }
    free(kisiler);

    // Zaman nesnesini yok edilir
    zaman->ZamanYokEt(zaman);
    
    // Simulasyon nesnesini yok edilir
    free(simulasyon);

    return 0;
}