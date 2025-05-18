/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 05.05.2025
* <p> 
* Simulasyon Sınıfı
* Burada gezegenler, uzay araçları ve kişileri içeren bir simülasyon temsil edilir
* Simülasyonun başlangıç, güncelleme ve bitiş durumlarını kontrol eden fonksiyonları içerir.
* Gezegenlerin ve uzay araçlarının durumunu güncelleyerek simülasyonu ilerletilir.
* Simülasyon sınıfı, gezegenler ve uzay araçları arasındaki etkileşimleri yönetir.
* </p> 
*/

#include "Simulasyon.h"
#include "UzayAraci.h"
#include "Kisi.h"
#include "DosyaOkuma.h"
#include "Gezegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Console.h"
#include "Zaman.h"


/**
 * Simülasyon başlangıç fonksiyonu.
 * - Gezegenlere yolcu yerleştirme
 * - Simülasyon saatine göre araç ve gezegen güncellemeleri
 * - Görsel çıktılar
 * - Final durum hesaplamaları yapılır
 */
static void baslat(Simulasyon this) {

    // 1. Başlangıçta her gezegenin nufusu hesaplanır.
    // Bu sayede hangi aractaki yolcuların hangi gezegende olduğu belirlenmis olur.
    for (int i = 0; i < this->gezegenSayisi; i++) {
        this->gezegenler[i]->nufusHesapla(this->gezegenler[i], this->uzayAraclari, this->uzayAracSayisi);
    }

    // 2. Simülasyon ana döngüsü
    // Simülasyon, tüm uzay araçları ya hedefe ulaşana ya da imha edilene kadar sürer.
    while (!this->isSimulasyonBitti(this)) {
        Console_clear();
        this->displayGezegenler(this);
        this->displayUzayAraclari(this);

        this->simulasyonSaati++;
        this->updateGezegenler(this);
        this->updateUzayAraclari(this);
    }
    
    this->simulasyonSaati++;
    this->updateGezegenler(this);
    Console_clear();
    this->displayFinalDurum(this);
}

//Simülasyon nesnesi için gezegen adı ile gezegen bulma fonksiyonu.
static Gezegen getGezegenByName(Simulasyon this, const char* name) {
    for (int i = 0; i < this->gezegenSayisi; i++) {
        if (strcmp(this->gezegenler[i]->isim, name) == 0) {
            return this->gezegenler[i];
        }
    }
    return NULL;
}

/**
 * Uzay aracının kalkış zamanı gelip gelmediğini kontrol eder.
 *
 * @param this Simülasyon nesnesi (gerekmiyor gibi görünse de metod imzasında standart)
 * @param uzayAraci Kalkış zamanı kontrol edilecek uzay aracı
 * @param cikisGezegeni Uzay aracının kalkacağı gezegen
 * @return Kalkış zamanı geldiyse 1, gelmediyse 0 döner
 */
static int isKalkisZamaniGeldi(Simulasyon this, UzayAraci uzayAraci, Gezegen cikisGezegeni) {

    int gunSim, aySim, yilSim;
    int gunDep, ayDep, yilDep;
    // Çıkış gezegeninin mevcut tarihini alıyoruz (örneğin: "05.05.2025")
    sscanf(cikisGezegeni->tarih, "%d.%d.%d", &gunSim, &aySim, &yilSim);

    // Uzay aracının kalkması gereken tarihi alıyoruzs
    sscanf(uzayAraci->cikisTarihi, "%d.%d.%d", &gunDep, &ayDep, &yilDep);

    // Tarih karsilastirmasi yapilir.
    if (yilSim > yilDep) {
        return 1;
    } else if (yilSim == yilDep) {
        if (aySim > ayDep) {
            return 1;
        } else if (aySim == ayDep) {
            return gunSim >= gunDep;
        }
    }
    return 0; // Tarih henüz gelmemişse kalkamaz
}

//Gezegenleri bilgilerini ekrana yazdırır. 
// Her gezegen için isim, tarih ve nüfus bilgilerini gösterir.
// Her satırda 10 gezegen bilgisi gösterilir.
static void displayGezegenler(Simulasyon this) {
    const int colWidth = 17;
    const int perLine =10;

    for (int start = 0; start < this->gezegenSayisi; start += perLine) {
        int end = (start + perLine < this->gezegenSayisi) ? (start + perLine) : this->gezegenSayisi;

        //Gezegen ciktisi
        printf("Gezegenler:    ");
        printf("\n");
        printf("              ");
         for (int i = start; i < end; i++) {
            char isimOrtali[7];
            int len = strlen(this->gezegenler[i]->isim);
            int pad = (6 - len) / 2;
            snprintf(isimOrtali, sizeof(isimOrtali), "%*s%-*s", pad + len, this->gezegenler[i]->isim, 6, "");
            printf("---%s---    ", isimOrtali);
        }
        printf("\n");

        // Tarih ciktisi
        printf("Tarih          ");
        for (int i = start; i < end; i++) {
            int gun, ay, yil, saat;
            sscanf(this->gezegenler[i]->tarih, "%d.%d.%d.%d", &gun, &ay, &yil, &saat);
            char tarihStr[20];
            snprintf(tarihStr, sizeof(tarihStr), "%02d.%02d.%04d", gun, ay, yil);
            printf("%-16s", tarihStr);
        }
        printf("\n");
        // Nufus ciktisi
            printf("Nufus        ");
            for (int i = start; i < end; i++) {
                int nufus = this->gezegenler[i]->getNufus(this->gezegenler[i]);
                char buf[16];
                snprintf(buf, sizeof(buf), "%d", nufus);
                int len = strlen(buf);
                int totalWidth = colWidth - 1;  // Satırın sonunda biraz daha sıkı görünüm için -1
                int padLeft = (totalWidth - len) / 2;
                int padRight = totalWidth - padLeft - len;
                printf("%*s%s%*s", padLeft, "", buf, padRight, "");
            }
            printf("\n\n");
    }
}
// Uzay araçlarının bilgilerini ekrana yazdırır.
// Her araç için isim, durum, çıkış gezegeni, varış gezegeni, hedefe kalan saat ve varacağı tarih bilgilerini gösterir.
static void displayUzayAraclari(Simulasyon this) {

    // Araç adı 10 karakter, Durum 10 karakter, diğerleri sabit genişlikte
    printf("Uzay Araclari:\n");
    printf("%-17s %-8s %-8s %-8s %-20s %s\n",
        "Arac Adi", "Durum", "Cikis", "Varis", "Hedefe Kalan Saat", "Hedefe Varacagi Tarih");

    for (int i = 0; i < this->uzayAracSayisi; i++) {
        UzayAraci arac = this->uzayAraclari[i];

        char durum[11]; // Durum için 10 karakterlik bir alan(bekliyor,vardı,imha)

        // Aracin durumu belirlenir
        if (arac->imhaDurumu) {
            strcpy(durum, "IMHA     ");
        } else if (arac->hedefeKalanSaat == 0 && arac->yolaCiktiMi) {
            strcpy(durum, "Vardi    ");
        } else if (arac->yolaCiktiMi) {
            strcpy(durum, "Yolda    ");
        } else {
            strcpy(durum, "Bekliyor ");
        }

        // Eger araç imha edilmediyse ve tarihi varsa yazdirilir
        const char* varisTarihi = "--";
        if (strcmp(durum, "IMHA     ") != 0 && arac->varisTarihi != NULL) {
            varisTarihi = arac->varisTarihi;
        }

        //Kalan saat bilgisi yazdirilir
        const char* kalanSaatStr = "--";
        char saatBuffer[16];
        if (!arac->imhaDurumu) {
            snprintf(saatBuffer, sizeof(saatBuffer), "%d", arac->hedefeKalanSaat);
            kalanSaatStr = saatBuffer;
        }

        printf("%-16s %s %-8s %-8s %-20s %s\n",
            arac->isim, durum, arac->cikisGezegeni, arac->varisGezegeni,
            kalanSaatStr, varisTarihi);
        }
}
// Simulasyonun bitip bitmedigini kontrol eder.
// Eger tüm uzay araçları hedefe ulaşmışsa veya imha olmuşsa simülasyon bitmesi icin 1 döner.
// Simulasyon bitmediyse 0 döner.
int isSimulasyonBitti(const Simulasyon this) {
    for (int i = 0; i < this->uzayAracSayisi; i++) {
        UzayAraci arac = this->uzayAraclari[i];
        if (!arac->imhaDurumu &&
            (arac->hedefeKalanSaat > 0 || !arac->yolaCiktiMi)) {
            return 0;  // Simulasyon devam eder
        }
    }
    return 1; // Bitti
}
// Simulasyon saatine göre gezegenlerin ve uzay araçlarının güncellenmesini sağlar.
// Her gezegenin tarihini günceller, uzay araçlarının durumunu kontrol eder ve kişileri ekler.
// Uzay araçlarının varış gezegenine ulaşan kişileri ekler.
// Her gezegene özel yaşlanma uygulanir.
static void updateGezegenler(Simulasyon this) {
     // Her gezegenin nufusu sifirlanir ve tarihi guncellenir
    for (int i = 0; i < this->gezegenSayisi; i++) {
        this->gezegenler[i]->resetNufus(this->gezegenler[i]);
        this->gezegenler[i]->guncelleTarih(this->gezegenler[i], this->simulasyonSaati);
    }
    //Tüm uzay araclari uzerinden gezegenlere kisi ekleme islemleri yapilir.
    for (int i = 0; i < this->uzayAracSayisi; i++) {
        UzayAraci arac = this->uzayAraclari[i];
        if (arac->imhaDurumu) continue; // Araç imha olmussa atlanir

        // Bekleyen araçlar çıkış gezegeninin nufusuna eklenir
        if (!arac->yolaCiktiMi) {
            Gezegen cikis = this->getGezegenByName(this, arac->cikisGezegeni);
            if (cikis != NULL) {
                for (int j = 0; j < arac->yolcuSayisi; j++) {
                    Kisi kisi = arac->yolcular[j];
                    if (kisi && kisi->isAlive(kisi)) {
                        cikis->addKisi(cikis, kisi);
                    }
                }
            }
        }

        // Varis gezgenine ulasan araclar varis gezegeninin nufusuna eklenir.
        if (arac->yolaCiktiMi && arac->hedefeKalanSaat == 0) {
            Gezegen varis = this->getGezegenByName(this, arac->varisGezegeni);
            if (varis != NULL) {
                for (int j = 0; j < arac->yolcuSayisi; j++) {
                    Kisi kisi = arac->yolcular[j];
                    if (kisi && kisi->isAlive(kisi)) {
                        varis->addKisi(varis, kisi);
                    }
                }
            }
        }
    }

    // Her gezegene göre yaşlanma uygulanıir
    for (int i = 0; i < this->gezegenSayisi; i++) {
        Gezegen g = this->gezegenler[i];
        if (g->guncelleNufus) {
            g->guncelleNufus(g);
        } else {
            printf("[ERROR] %s için guncelleNufus fonksiyonu atanmadı!\n", g->isim);
        }
    }
}
// Uzay araçlarının durumunu günceller.
// Araçların yola çıkıp çıkmadığını kontrol eder, hedefe kalan saatleri günceller.
// Araçların varış tarihlerini hesaplar.
// Araçlardaki yolcuların durumunu kontrol eder ve gerekli işlemleri yapar.
// Eğer tüm yolcular ölmüşse aracı imha eder.
static void updateUzayAraclari(Simulasyon this) {
    for (int i = 0; i < this->uzayAracSayisi; i++) {
        UzayAraci arac = this->uzayAraclari[i];
        if (!arac) continue;

        // Aracin kalkis zamani geldiyse hareket ettirilir
        this->uzayAraciHareketi(this, arac);

        //Hedefe kalan saat guncellenir
        if (arac->yolaCiktiMi && !arac->imhaDurumu && arac->guncelleHedefeKalanSaat) {
            arac->guncelleHedefeKalanSaat(arac);
        }
        // Aractaki yolcuların yasları güncellenir (sadece yolculukta olanlarin)
        for (int j = 0; j < arac->yolcuSayisi; j++) {
            Kisi kisi = arac->yolcular[j];
            if (kisi && kisi->isAlive(kisi)) {
              if (arac->yolaCiktiMi && arac->hedefeKalanSaat > 0) {
                // Arac yoldaysa normal yaslanir yani yaslanma katsayısı 1.0'dir
                double katsayi = 1.0;
                kisi->yaslanmaKatsayisi = katsayi;
                kisi->guncelleKalanOmur(kisi);
              }
            }
        }
         // Eger tum yolcular ölmüşse araç imha edilir
        int herkesOlmus = 1;
        for (int j = 0; j < arac->yolcuSayisi; j++) {
            Kisi kisi = arac->yolcular[j];
            if (kisi && kisi->isAlive(kisi)) {
                herkesOlmus = 0;
                break;
            }
        }
        // Eğer tüm yolcular ölmüşse arac imha edilir
        if (herkesOlmus && !arac->imhaDurumu) {
            arac->imhaEt(arac); 
        }

        // Varış tarihi daha önce hesaplanmamışsa tarih hesabi yapilir
        if (!herkesOlmus && arac->varisTarihi == NULL) {
            Gezegen cikis = this->getGezegenByName(this, arac->cikisGezegeni);
            Gezegen varis = this->getGezegenByName(this, arac->varisGezegeni);
            char* hesaplananTarih = this->zaman->hedefTarihiHesapla(this->zaman, arac, cikis, varis);
            if (arac->varisTarihi) free(arac->varisTarihi);
            arac->varisTarihi = hesaplananTarih;
        }
    }
}
// Uzay aracının hareketini yönetir.
// Eger aracin kalkis zamanı geldiyse, onu hareket ettirir (yani yola çıkarır) ve hedefe kalan saat bilgisini hesaplar.
static void uzayAraciHareketi(Simulasyon this, UzayAraci arac) {


    // Eger aras henuz yola cikmamıs ve imha edilmemişse devam et
    if (!arac->yolaCiktiMi && !arac->imhaDurumu) {

        //Aracin çıkış gezegenini ismine göre bulur
        Gezegen cikisGezegen = this->getGezegenByName(this, arac->cikisGezegeni);

        // Eğer çıkış gezegeni bulunursa ve kalkış zamanı geldiyse
        // Araç yola çıkarılır ve hedefe kalan saat hesaplanır
        if (cikisGezegen != NULL && this->isKalkisZamaniGeldi(this, arac, cikisGezegen)) {

            for (int i = 0; i < arac->yolcuSayisi; i++) {
                cikisGezegen->removeKisi(cikisGezegen, arac->yolcular[i]);
            }

             //Araç yola çıkar 
            arac->yolaCik(arac);

            int currentHour = 0;
            if (cikisGezegen->tarih != NULL) {
                sscanf(cikisGezegen->tarih, "%*d.%*d.%*d.%d", &currentHour);
            }

            // Hedefe kalan saat hesaplanir
            if (arac->setHedefeKalanSaat != NULL) {
                arac->setHedefeKalanSaat(arac, arac->mesafeSaat - currentHour);
            }

        }

    }
}
// Simulasyonun final durumunu ekrana yazdırır.
static void displayFinalDurum(Simulasyon this) {
    printf("\n=== Final Durum ===\n");
    this->displayGezegenler(this);
    this->displayUzayAraclari(this);
}
//Yapici fonksiyon
// Simulasyon nesnesi oluşturur ve gerekli alanları başlatır.
// Simulasyon nesnesi için bellek ayırır ve metotları atar.
Simulasyon SimulasyonOlustur(Gezegen* gezegenler, int gezegenSayisi, UzayAraci* uzayAraclari, int uzayAracSayisi,Zaman zaman,Kisi* kisiler, int kisiSayisi)
 {

    Simulasyon sim = (Simulasyon)malloc(sizeof(struct SIMULASYON));
    if (sim == NULL) {
        printf("Simulasyon için bellek ayrılamadı!\n");
        return NULL;
    }

    sim->gezegenler = gezegenler;
    sim->gezegenSayisi = gezegenSayisi;
    sim->uzayAraclari = uzayAraclari;
    sim->uzayAracSayisi = uzayAracSayisi;
    sim->kisiler = kisiler;
    sim->kisiSayisi = kisiSayisi;
    sim->simulasyonSaati = 0;
    sim->zaman = zaman;
    // Metotlar
    sim->baslat = &baslat;
    sim->getGezegenByName = &getGezegenByName;
    sim->isKalkisZamaniGeldi = &isKalkisZamaniGeldi;
    sim->displayGezegenler = &displayGezegenler;
    sim->displayUzayAraclari = &displayUzayAraclari;
    sim->displayFinalDurum = &displayFinalDurum;
    sim->isSimulasyonBitti = &isSimulasyonBitti;
    sim->updateGezegenler = &updateGezegenler;
    sim->updateUzayAraclari = &updateUzayAraclari;
    sim->uzayAraciHareketi = &uzayAraciHareketi;

    return sim;
}