/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 05.05.2025
* <p> 
* Kayac Gezegenin Kaynak Dosyası  
* Yapı, Gezegen soyut sınıfından türetilmiştir. 
* Bu dosyada gezegen oluşturma, yaşlanma katsayısını(0.5) belirleme ve bellek
* temizleme işlemleri gerçekleştirilir.
* </p>
*/
#include "KayacGezegen.h"

//KayacGezegen turunde yeni bir nesne olusturma metodu
KayacGezegen KayacGezegenOlustur(const char* isim, int saat, const char* tarih, double yaslanma) {
    KayacGezegen this;
    this = (KayacGezegen)malloc(sizeof(struct KAYACGEZEGEN)); // Bellek ayırma
    if (!this) return NULL;

    this->super = GezegenOlustur(isim, saat, tarih); // Temel gezegen yapısı oluşturulur
    this->yaslanmaKatsayisi = yaslanma; // Bu gezegene özel yaşlanma katsayısını atanır.

    // Ortak metodlar
    this->super->yaslanma = &YaslanmaKayac;
    this->super->getNufus = &KayacGezegenGetNufus;
    this->super->guncelleNufus = &guncelleNufus;
    this->super->removeKisi = &removeKisiDefault;
    this->super->self = this; // ✅ En önemli satır
    this->super->yoketGezegen = (void (*)(struct GEZEGEN*)) KayaciYokEt;
    return this;
}
// Bu gezegene özel  yaşlanma katsayısı döner
double YaslanmaKayac(const Gezegen gezegen) {
    KayacGezegen kayac = (KayacGezegen)(gezegen->self); // ✅ Doğru cast
    return kayac->yaslanmaKatsayisi;
}

int KayacGezegenGetNufus(struct GEZEGEN* this) {
    if (this == NULL) return 0;
    return this->nufusSayisi;
}


void KayaciYokEt(const KayacGezegen this) {
     if (!this) return;
   // this->super->yoketGezegen(this->super);
    free(this);
}