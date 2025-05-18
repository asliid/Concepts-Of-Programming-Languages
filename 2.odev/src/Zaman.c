/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 05.05.2025
* <p> 
* Zaman Sınıfı
* Simülasyondaki zaman hesaplamalarını yöneten sınıf.
* Zaman sınıfı, uzay aracının hedef gezegene ulaşma tarihini hesaplar.
* Ayrıca gezegenlerin sabit tarihleri ile uzay aracının çıkış tarihleri arasındaki farkı hesaplar.
* </p> 
*/

#include "Zaman.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Simülasyondaki mevcut zamanı (saat cinsinden) döner.
static int getSaat(Zaman this) {
    return this->saat;
}

// Simülasyonda zamanı bir saat ileri alır.
static void gec(Zaman this) {
    this->saat++;
}
// Gercek takvime göre bir ayin kaç gün surdugunu verir.
// Şubat ayı için artık yıl kontrolü  de yapilir.
static int ayGunSayisi(int ay, int yil) {
    static int gunler[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (ay == 2 && ((yil % 4 == 0 && yil % 100 != 0) || (yil % 400 == 0)))
        return 29;
    return gunler[ay];
}

// İki tarih arasındaki gün farkını verir.
// Tarihler gün/ay/yıl formatında alınır ve fark mutlak değer olarak hesaplanır.
int dateDifferenceInDays(int g1, int a1, int y1, int g2, int a2, int y2) {
    struct tm t1 = { .tm_mday = g1, .tm_mon = a1 - 1, .tm_year = y1 - 1900 };
    struct tm t2 = { .tm_mday = g2, .tm_mon = a2 - 1, .tm_year = y2 - 1900 };

    time_t time1 = mktime(&t1);
    time_t time2 = mktime(&t2);

    double diffInSeconds = difftime(time2, time1);
    return (int)(fabs(diffInSeconds / (60 * 60 * 24)));  // 🛡️ Mutlak değer
}

/* Uzay aracının varış gezegenine ne zaman ulaşacağını hesaplar.
* Hesaplama sabit çıkış ve varış tarihleri ile yapılır.
* Çıkış gezegeninin sabit tarihinden çıkışa kadar olan bekleme süresi hesaplanır.
* Çıkış gezegeninin sabit tarihine kadar olan gün farkı hesaplanır.
* Çıkış gezegeninin sabit tarihine kadar olan gün farkı, çıkış gezegeninin günün kaç saat olduğu ile çarpılır.
* Çıkış gezegeninin sabit tarihine kadar olan gün farkı, uzay aracının mesafe saatine eklenir.
* Varış gezegeninin sabit tarihine bu kadar saat eklenir.
* Varış gezegeninin sabit tarihine eklenen saat, varış gezegeninin günün kaç saat olduğu ile bölünür.
* Kalan saat, varış gezegeninin sabit tarihine eklenir.
*/
char* hedefTarihiHesapla(Zaman this,
                         UzayAraci uzayAraci,
                         Gezegen cikisGezegeni,
                         Gezegen varisGezegeni) {
    if (!uzayAraci || uzayAraci->imhaDurumu || !cikisGezegeni || !varisGezegeni)
        return strdup("--");

    // Cikis tarihine kadar olan bekleme süresini bul
    int sabitG, sabitA, sabitY;
    sscanf(cikisGezegeni->orijinalTarih, "%d.%d.%d", &sabitG, &sabitA, &sabitY);

    int cikisGun, cikisAy, cikisYil;
    sscanf(uzayAraci->cikisTarihi, "%d.%d.%d", &cikisGun, &cikisAy, &cikisYil);

    // Çıkış gezegeninin txt tarihine kadar olan gün farkı
    int gunFarki = dateDifferenceInDays(sabitG, sabitA, sabitY, cikisGun, cikisAy, cikisYil);
    int beklemeSaat = gunFarki * cikisGezegeni->gununKacSaatOldugu;

    // Toplam saat: bekleme süresi + yolculuk süresi
    int toplamSaat = beklemeSaat + uzayAraci->mesafeSaat;

    // Varış gezegeninin sabit tarihine bu kadar saat eklenir
    int vG, vA, vY, vS = 0;
    sscanf(varisGezegeni->orijinalTarih, "%d.%d.%d", &vG, &vA, &vY);

    int perGun = varisGezegeni->gununKacSaatOldugu;

    vG += toplamSaat / perGun;
    vS  = toplamSaat % perGun;

    // Gün taşması varsa ay/yıl güncellemesi yapılır
    while (vG > ayGunSayisi(vA, vY)) {
        vG -= ayGunSayisi(vA, vY);
        vA++;
        if (vA > 12) {
            vA = 1;
            vY++;
        }
    }
     // Tarihi string formatına çevrilir.
    char* tarihStr = malloc(24);
    snprintf(tarihStr, 16, "%02d.%02d.%04d", vG, vA, vY);
    return tarihStr;
}

// Zaman nesnesi için ayrılmış belleği serbest bırakır.
static void ZamanYokEt(Zaman z) {
    free(z);
}

// Yeni bir Zaman nesnesi oluşturur ve varsayılan fonksiyonları atar.
Zaman ZamanOlustur(void) {
    Zaman z = malloc(sizeof(struct ZAMAN));
    z->saat               = 0;
    z->getSaat            = getSaat;   
    z->gec                = gec;
    z->hedefTarihiHesapla = hedefTarihiHesapla;
    z->ZamanYokEt         = ZamanYokEt;
    return z;
}