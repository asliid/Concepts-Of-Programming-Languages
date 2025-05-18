/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 26.03.2025
* <p> 
* Kişi Sınıfı
* </p> 
*/


package pdp1.model;

public class Kisi {
    private String isim;
    private int yas;
    private int kalanOmur;
    private String bulunduguUzayAraciAdi;

    public Kisi(String isim, int yas, int kalanOmur, String bulunduguUzayAraciAdi) {
        this.isim = isim;
        this.setYas(yas);
        this.kalanOmur = kalanOmur;
        this.bulunduguUzayAraciAdi = bulunduguUzayAraciAdi;
    }
    //Kişinin kaç saat daha yaşayacağını, kalan omrunu belirtir.
    public void guncelleKalanOmur() {
        if (kalanOmur > 0) {
            kalanOmur--;
        }
    }

    public int getKalanOmur() {
        return kalanOmur;
    }

    public void setKalanOmur(int kalanOmur) {
        this.kalanOmur = kalanOmur;
    }

    public boolean isAlive() {
        return kalanOmur > 0;
    }

    public String getIsim() {
        return isim;
    }

    public String getBulunduguUzayAraciAdi() {
        return bulunduguUzayAraciAdi;
    }

	public int getYas() {
		return yas;
	}

	public void setYas(int yas) {
		this.yas = yas;
	}

	
}