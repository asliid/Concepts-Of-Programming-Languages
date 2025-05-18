/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 05.05.2025
* <p> 
* Gaz Devi Gezegenin Kaynak Dosyası  
* Yapı, Gezegen soyut sınıfından türetilmiştir. 
* Bu dosyada gezegen oluşturma, yaşlanma katsayısını(0.5) belirleme ve bellek
* temizleme işlemleri gerçekleştirilir.
* </p>
*/

#include "GazDeviGezegen.h"

//GazDeviGezegen turunde yeni bir nesne olusturma metodu
GazDeviGezegen GazDeviGezegenOlustur(const char* isim, int saat, const char* tarih, double yaslanma) {
    GazDeviGezegen this;
    this = (GazDeviGezegen)malloc(sizeof(struct GAZDEVIGEZEGEN)); // Bellek ayırma
    this-> super= GezegenOlustur(isim, saat, tarih); // Temel gezegen yapısı oluşturulur
    this->yaslanmaKatsayisi = yaslanma; // Bu gezegene özel yaşlanma katsayısını atanır.

    // Ortak metodlar 
    this->super->yaslanma = &YaslanmaGazDevi;
    this->super->getNufus = &getNufusDefault;
    this->super->resetNufus = &resetNufusDefault;
    this->super->addKisi = &addKisiDefault;
    this->super->removeKisi = &removeKisiDefault;
    this->super->guncelleNufus = &guncelleNufus;
    this->super->self = this; // ✅ En önemli satır

    this->super->getNufus = &GazDeviGezegenGetNufus;   // veya ilgili fonksiyon
    this->super->yoketGezegen = (void (*)(struct GEZEGEN*)) GazDeviniYokEt;   
     return this;
}
// Bu gezegene özel  yaşlanma katsayısı döner
double YaslanmaGazDevi(const Gezegen gezegen) {
   GazDeviGezegen gazDevi = (GazDeviGezegen)(gezegen->self);
    return gazDevi->yaslanmaKatsayisi;
}
void GazDeviniYokEt(const GazDeviGezegen this) {
    if (!this) return;
   // this->super->yoketGezegen(this->super);
    free(this);
}
int GazDeviGezegenGetNufus(struct GEZEGEN* this) {
    if (this == NULL) return 0;
    return this->nufusSayisi;
}