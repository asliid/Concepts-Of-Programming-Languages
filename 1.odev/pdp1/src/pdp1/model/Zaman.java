/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 26.03.2025
* <p> 
* Zaman Sınıfı
* </p> 
*/



package pdp1.model;

public class Zaman {
    private int saat;

    public Zaman() {
        this.saat = 0;
    }

    public int getSaat() {
        return saat;
    }

    public void gec() {
        this.saat++;
    }
    
    /**
     * Uzay aracının çıkış ve varış gezegenlerine göre hedefe varacağı tarihi hesaplar.
     * Gezegenlerin tarihleri ve gün uzunlukları göz önünde bulundurularak, toplam geçen süre
     * saat cinsinden hesaplanır ve varış gezegenine göre tarih formatına dönüştürülür.
     *
     * @param uzayAraci       Uzay aracının çıkış tarihi ve seyahat süresini içerir
     * @param cikisGezegeni   Uzay aracının kalktığı gezegen
     * @param varisGezegeni   Uzay aracının varacağı gezegen
     * @return                Hedef gezegende varış tarihi (gg.aa.yyyy formatında) veya "--" (geçersiz durumlarda)
     */
    public static String hedefTarihiHesapla(UzayAraci uzayAraci, Gezegen cikisGezegeni, Gezegen varisGezegeni) {
    	// Arac imha mı diye kontrol edilir. 
        if (uzayAraci.isImhaDurumu() || cikisGezegeni == null || varisGezegeni == null) {
            return "--";
        }

        String[] cikisTarihParts = uzayAraci.getCikisTarihi().split("\\.");
        String[] cikisGezegenTarihParts = cikisGezegeni.getTarih().split("\\.");
        String[] varisGezegenTarihParts = varisGezegeni.getTarih().split("\\.");

        // Textteki tarihler parçalanır.

        int planlananGun = Integer.parseInt(cikisTarihParts[0]);
        int planlananAy = Integer.parseInt(cikisTarihParts[1]);
        int planlananYil = Integer.parseInt(cikisTarihParts[2]);

        int cikisGezegenGun = Integer.parseInt(cikisGezegenTarihParts[0]);
        int cikisGezegenAy = Integer.parseInt(cikisGezegenTarihParts[1]);
        int cikisGezegenYil = Integer.parseInt(cikisGezegenTarihParts[2]);

        int varisGezegenGun = Integer.parseInt(varisGezegenTarihParts[0]);
        int varisGezegenAy = Integer.parseInt(varisGezegenTarihParts[1]);
        int varisGezegenYil = Integer.parseInt(varisGezegenTarihParts[2]);
        
        //Cikis tarihlerinin farkı gun olarak hesaplanir 
        int gunFarki = dateDifferenceInDays(
                cikisGezegenGun, cikisGezegenAy, cikisGezegenYil,
                planlananGun, planlananAy, planlananYil
        );
        
        //Bekleme suresi saat olarak hesaplanir. 
        int beklemeSaati = gunFarki > 0 ? gunFarki * cikisGezegeni.getGununKacSaatOldugu() : 0;
        
        // Toplam geçen saat = bekleme süresi + yolculuk süresi hesaplanir.
        int toplamGecenSaat = beklemeSaati + uzayAraci.getMesafeSaat();

        // Varis gezegeninin mevcut tarihi hesaplanir.
        int saatPerGun = varisGezegeni.getGununKacSaatOldugu();
        int varisGezegenToplamSaat =
                ((varisGezegenYil * 12 + varisGezegenAy - 1) * 30 + (varisGezegenGun - 1)) * saatPerGun;

        // Hedefe varis anındaki toplam saat bulunur.
        int yeniToplamSaat = varisGezegenToplamSaat + toplamGecenSaat;
        
        // Yeni tarih hesaplanir. 

        int toplamGun = yeniToplamSaat / saatPerGun;
        int hedefGun = (toplamGun % 30) + 1;
        int toplamAy = toplamGun / 30;
        int hedefAy = (toplamAy % 12) + 1;
        int hedefYil = toplamAy / 12;

        // Varıs tarihi olusturulur.
        String hedefTarihi = hedefGun + "." + hedefAy + "." + hedefYil;

        // Uzay aracina varis vakti set edilir.
        uzayAraci.setVarisTarihi(hedefTarihi);

        return hedefTarihi;
    }
    //Iki tarih arasındaki gün farkını hesaplar.
    private static int dateDifferenceInDays(int gun1, int ay1, int yil1,
                                            int gun2, int ay2, int yil2) {
        int totalDays1 = yil1 * 360 + ay1 * 30 + gun1;
        int totalDays2 = yil2 * 360 + ay2 * 30 + gun2;
        return totalDays2 - totalDays1;
    }
}