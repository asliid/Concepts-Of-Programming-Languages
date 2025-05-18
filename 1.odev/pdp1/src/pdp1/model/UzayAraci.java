/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 26.03.2025
* <p> 
* Uzay Aracı Sınıfı
* </p> 
*/




package pdp1.model;

import java.util.List;

public class UzayAraci {
    private String isim;
    private String cikisGezegeni;
    private String varisGezegeni;
    private String cikisTarihi;
    private int mesafeSaat;
    private List<Kisi> yolcular;
    private boolean imhaDurumu;
    private int hedefeKalanSaat;
    private boolean yolaCiktiMi = false;
    private String varisTarihi; 
    private boolean varisTarihiHesaplandi = false;  

    public UzayAraci(String isim, String cikisGezegeni, String varisGezegeni, String cikisTarihi, int mesafeSaat, List<Kisi> yolcular, boolean imhaDurumu) {
        this.isim = isim;
        this.cikisGezegeni = cikisGezegeni;
        this.varisGezegeni = varisGezegeni;
        this.cikisTarihi = cikisTarihi;
        this.mesafeSaat = mesafeSaat;
        this.yolcular = yolcular;
        this.imhaDurumu = imhaDurumu;
        this.hedefeKalanSaat = mesafeSaat;
        this.yolaCiktiMi = false;
    }

    public void yolaCik() {
        this.yolaCiktiMi = true;
    }

    // Uzay aracının yola çıkıp çıkmadığını döner
    public boolean isYolaCiktiMi() {
        return yolaCiktiMi;
    }
    
    // Hedefe kalan saati 1 azaltır (eğer imha edilmemişse ve saat > 0 ise)
    public void guncelleHedefeKalanSaat() {
        if (!isImhaDurumu() && hedefeKalanSaat > 0) {
            hedefeKalanSaat--;
        }
    } 
    /* Uzay aracının çıkış zamanının gelip gelmediğini kontrol eder
     * Gezegenin tarihi uzay aracının çıkış tarihiyle aynıysa ve saat 00:00 ise çıkış zamanı gelmiştir
     */
    public boolean isCikisZamaniGeldi(Gezegen gezegen) {
        return !yolaCiktiMi && 
                gezegen.getTarih().equals(this.cikisTarihi) && 
                gezegen.getSaat() == 0; // 00:00'da çıkış yapar
     }
    // Uzay aracındaki tüm yolcular ölmüşse aracı imha eder
    public void kontrolEt() {
        boolean allDead = true;
        for (Kisi kisi : yolcular) {
            if (kisi.isAlive()) {
                allDead = false;
                break;
            }
        }

        if (allDead) {
            imhaEt();
        }
    }

    public void imhaEt() {
        this.imhaDurumu = true;
    }

    public boolean isImhaDurumu() {
        return imhaDurumu;
    }

    public String getCikisGezegeni() {
        return cikisGezegeni;
    }

    public String getVarisGezegeni() {
        return varisGezegeni;
    }

    public List<Kisi> getYolcular() {
        return yolcular;
    }

    public int getHedefeKalanSaat() {
        return hedefeKalanSaat;
    }

    public String getIsim() {
        return isim;
    }

    public String getCikisTarihi() {
        return cikisTarihi;
    }
    public int getMesafeSaat() {
        return this.mesafeSaat;
    }
    
    public void setHedefeKalanSaat(int hedefeKalanSaat) {
        this.hedefeKalanSaat = hedefeKalanSaat;
    }

    public String getVarisTarihi() {
        return varisTarihi;
    }

    public void setVarisTarihi(String varisTarihi) {
        this.varisTarihi = varisTarihi;
    }

    public boolean isVarisTarihiHesaplandi() {
        return varisTarihiHesaplandi;
    }

    public void setVarisTarihiHesaplandi(boolean varisTarihiHesaplandi) {
        this.varisTarihiHesaplandi = varisTarihiHesaplandi;
    }

    public void setImhaDurumu(boolean imhaDurumu) {
        this.imhaDurumu = imhaDurumu;
    }
}


