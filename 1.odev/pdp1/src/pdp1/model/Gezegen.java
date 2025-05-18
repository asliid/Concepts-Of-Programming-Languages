/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 26.03.2025
* <p> 
* Gezegen Sınıfı
* </p> 
*/

package pdp1.model;

import java.util.ArrayList;
import java.util.List;


public class Gezegen {
    private String isim;
    private int gununKacSaatOldugu;
    private String tarih;
    private int saat; 

    private List<Kisi> nufus;

    public Gezegen(String isim, int gununKacSaatOldugu, String tarih) {
        this.isim = isim;
        this.gununKacSaatOldugu = gununKacSaatOldugu;
        this.tarih = tarih;
        this.nufus = new ArrayList<>();
        this.saat = 0; // Program baslangicinda gezegenlerdeki zamani koordine edebilmek icin hepsinin saatini saat 00:00'dan başlatır.

    }
    
    /*Gezegenin tarihini simulasyon ilerledikce saat bazında ilerletir. 
     * Gezegenin kendi saat uzunluğuna (gununKacSaatOldugu) göre gün değişimini kontrol eder.
    */
    public void guncelleTarih(int simülasyonSaati) {    
        // Gezegenin mevcut tarih bilgisini parcalar: gun.ay.yil.saat formatinda
        String[] tarihParcalari = this.tarih.split("\\.");
        int gun = Integer.parseInt(tarihParcalari[0]);
        int ay = Integer.parseInt(tarihParcalari[1]);
        int yil = Integer.parseInt(tarihParcalari[2]);
        int saat = tarihParcalari.length > 3 ? Integer.parseInt(tarihParcalari[3]) : 0;

        // Simulasyon her cagirildiginda saat 1 arttirilir
        saat++;
        
        // Eğer gezegenin bir günlük zaman dilimi oluştuysa gün arttirilir ve bir sonraki gune gecilir. 
        if (saat >= this.gununKacSaatOldugu) {
            saat = 0;
            gun++;
            
            // Eger gun sayisi 30'a ulasirsa yeni aya geçilir.
            if (gun > 30) { // Her ay 30 gün varsayilir.
                gun = 1;
                ay++;
                
             // Eğer ay sayisi 12'yi geçtiyse yeni yıla geçilir.
                if (ay > 12) {
                    ay = 1;
                    yil++;
                }
            }
        }
        // Guncellenmis tarih bilgisi tekrar string olarak yazilir.
        this.tarih = gun + "." + ay + "." + yil + "." + String.format("%02d", saat);
    }

    //Gezegenlerin güncel nüfusunu hesaplamak için kullanilir.Yolculuk halindeki uzay araclari ya da ölmüş kisiler nufusa eklenmez.
    public void nufusHesapla(List<UzayAraci> uzayAraclari) {
        // Nüfusu her seferinde sıfırlar.
        this.nufus.clear();

        // Uzay araclarindaki yolcuları gezegene ekler.
        for (UzayAraci uzayAraci : uzayAraclari) {
        	
            // Eğer uzay aracı bu gezegende ise ve yolda degilse
            if (uzayAraci.getCikisGezegeni().equals(this.isim) && !uzayAraci.isYolaCiktiMi()) {
                for (Kisi kisi : uzayAraci.getYolcular()) {
                	// Eğer kişi hayattaysa, bulundugu gezegenin nufusuna eklenir
                    if (kisi.isAlive()) {
                        this.nufus.add(kisi);
                    }
                }
            }
            // Eğer uzay aracı varış gezegenine ulaştıysa
            if (uzayAraci.getVarisGezegeni().equals(this.isim) && uzayAraci.getHedefeKalanSaat() == 0) {
                for (Kisi kisi : uzayAraci.getYolcular()) {
                	// Sadece yaşayan kisiler nüfusa eklenir.
                    if (kisi.isAlive()) {
                        this.nufus.add(kisi);
                    }
                }
            }
        }
    }
    //Getter Setters
    public int getGununKacSaatOldugu() { return gununKacSaatOldugu; }

    public void addKisi(Kisi kisi) { this.nufus.add(kisi); }

    public void guncelleNufus() {nufus.removeIf(kisi -> !kisi.isAlive());}

    public String getIsim() {return isim;  }

    public String getTarih() {return tarih;  }
    
    public void setTarih(String yeniTarih) {this.tarih = yeniTarih;} 
    
    public int getSaat() { return saat;}
    
    public int setSaat() { return saat;}

    public int getNufus() { return nufus.size(); }
    
    public void resetNufus() { this.nufus.clear(); }
    
    public void removeKisi(Kisi kisi) { this.nufus.remove(kisi);}
    
    public List<Kisi> getNufusListesi() {return nufus;}
    
}