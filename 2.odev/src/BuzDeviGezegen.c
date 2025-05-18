/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 05.05.2025
* <p> 
* Buz Devi Gezegenin Kaynak Dosyası  
* Yapı, Gezegen soyut sınıfından türetilmiştir. 
* Bu dosyada gezegen oluşturma, yaşlanma katsayısını(0.5) belirleme ve bellek
* temizleme işlemleri gerçekleştirilir.
* </p>
*/

#include "BuzDeviGezegen.h"

//BuzDeviGezegen turunde yeni bir nesne olusturma metodu
BuzDeviGezegen BuzDeviGezegenOlustur(const char* isim, int saat, const char* tarih, double yaslanma) {
    BuzDeviGezegen this;
    this = (BuzDeviGezegen)malloc(sizeof(struct BUZDEVIGEZEGEN)); // Bellek ayırma
    this-> super= GezegenOlustur(isim, saat, tarih);     // Temel gezegen yapısı oluşturulur
    this->yaslanmaKatsayisi = yaslanma; // Bu gezegene özel yaşlanma katsayısını atanır.

    // Ortak metodlar 
    this->super->yaslanma = &YaslanmaBuzDevi; 
    this->super->removeKisi = &removeKisiDefault;
    this->super->guncelleNufus = &guncelleNufus;
    this->super->self = this; 

    this->super->getNufus = &BuzDeviGezegenGetNufus;
    this->super->yoketGezegen = (void (*)(struct GEZEGEN*)) BuzDeviniYokEt;   
 return this;
}

// Bu gezegene özel  yaşlanma katsayısı döner
double YaslanmaBuzDevi(const Gezegen gezegen) {
    BuzDeviGezegen buzdevi = (BuzDeviGezegen)(gezegen->self);
   return buzdevi->yaslanmaKatsayisi;
}

void BuzDeviniYokEt(const BuzDeviGezegen this) {
   if (!this) return;
    free(this);
}
// Bu gezegenin nufusunu döner
int BuzDeviGezegenGetNufus(struct GEZEGEN* this) {
    if (this == NULL) return 0;
    return this->nufusSayisi;
}