/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 05.05.2025
* <p> 
* Cüce Gezegenin Kaynak Dosyası  
* Yapı, Gezegen soyut sınıfından türetilmiştir. 
* Bu dosyada gezegen oluşturma, yaşlanma katsayısını(0.01) belirleme ve bellek
* temizleme işlemleri gerçekleştirilir.
* </p>
*/

#include "CuceGezegen.h"

//CuceGezegen turunde yeni bir nesne olusturma metodu
CuceGezegen CuceGezegenOlustur(const char* isim, int saat, const char* tarih, double yaslanma) {
    CuceGezegen this;
    this = (CuceGezegen)malloc(sizeof(struct CUCEGEZEGEN)); // Bellek ayırma
    this->super = GezegenOlustur(isim, saat, tarih); // Temel gezegen yapısı oluşturulur
    this->yaslanmaKatsayisi = yaslanma; // Bu gezegene özel yaşlanma katsayısını atanır.

     // Ortak metodlar 
    this->super->yaslanma = &YaslanmaCuce;
    this->super->guncelleNufus = &guncelleNufus;
    this->super->getNufus = &CuceGezegenGetNufus;
    this->super->self = this; // ✅ En önemli satır

    this->super->removeKisi = &removeKisiDefault;
    this->super->yoketGezegen = (void (*)(struct GEZEGEN*)) CuceYokEt;    
    return this;
}
// Bu gezegene özel  yaşlanma katsayısı döner
double YaslanmaCuce(const Gezegen gezegen) {
    CuceGezegen cuce = (CuceGezegen)(gezegen->self);
    return cuce->yaslanmaKatsayisi;
}

void CuceYokEt(const CuceGezegen this) {
    if (!this) return;
    // Eğer super içindekileri temizleyeceksen aşağıyı açabilirsin:
    // this->super->yoketGezegen(this->super);
    free(this);
}

int CuceGezegenGetNufus(struct GEZEGEN* this) {
    if (this == NULL) return 0;
    return this->nufusSayisi;
}