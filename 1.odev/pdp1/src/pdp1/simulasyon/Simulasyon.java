/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 26.03.2025
* <p> 
* Simulasyon Sınıfı
* </p> 
*/


package pdp1.simulasyon;

import pdp1.model.*;

import java.util.List;


public class Simulasyon {
	
	// Gezegen ve uzay aracı listeleri
    private List<Gezegen> gezegenler;
    private List<UzayAraci> uzayAraclari;
    
    // Simülasyonun calistigi süreyi saat cinsinden tutar
    private int simülasyonSaati = 0;
    
    //Simulasyon sınıfının constructorı. Gezegen ve uzay aracı listesini alır.
    public Simulasyon(List<Gezegen> gezegenler, List<UzayAraci> uzayAraclari) {
        this.gezegenler = gezegenler;
        this.uzayAraclari = uzayAraclari;
    }
    
    /**
     * Simülasyon baslatilir. 
     * Gezegen tarihlerini başlatır, uzay araclarinin varıs tarihlerini
     * hesaplar ve her saniyede bir simulasyonu guncelleyerek ekrana yansitir.
     */
    public void baslat() throws InterruptedException{
    	
        // Gezegenlerin tarihlerini saatleri dahil olacak şekilde baslatir.
        gezegenTarihleri();

        // Uzay araçlarının varis tarihlerini hesaplar.
        for (UzayAraci uzayAraci : uzayAraclari) {
            if (!uzayAraci.isImhaDurumu() && uzayAraci.getVarisTarihi() == null) {
            	Gezegen cikis = getGezegenByName(uzayAraci.getCikisGezegeni());
            	Gezegen varis = getGezegenByName(uzayAraci.getVarisGezegeni());
            	String tarih = Zaman.hedefTarihiHesapla(uzayAraci, cikis, varis);
                uzayAraci.setVarisTarihi(tarih);
            }
        }
        try {
        	// Simülasyon bitene kadar calisir.
            while (!isSimulasyonBitti()) {
            	// Ekrani temizler
                pdp1.Console.clear();
                
                displayGezegenler();  // Gezegenleri gosterir.
                displayUzayAraclari();  // Uzay araclarini gosterir.
                
                simülasyonSaati++;   // Simulasyon saatini artirir.
                updateGezegenler();  // Gezegenlerin tarihini gunceller
                updateUzayAraclari();  // Uzay araclarini gunceller.
                
                Thread.sleep(1000);  // 1 saniye bekler.
            }
         // Simulasyon bittiginde ekrani temizler ve final durumunu gösterir.
            pdp1.Console.clear();
            displayFinalDurum();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
    /**
     * Gezegenlerin tarih bilgilerini "gg.aa.yyyy.00" formatına çevirerek başlatır.
     * Boylelikle programdaki gezegenlerin tarih yonetimi için
     * saat kisminin sıfırdan baslanmasi saglanir.
     */
    private void gezegenTarihleri() {
        for (Gezegen gezegen : gezegenler) {
            String[] tarihParts = gezegen.getTarih().split("\\.");
            gezegen.setTarih(tarihParts[0] + "." + tarihParts[1] + "." + tarihParts[2] + ".00");
        }
    }
    /**
     * Verilen isimle eşleşen gezegeni gezegenler listesinde arar.
     * İsmi verilen gezegen bulunursa o Gezegen nesnesi, bulunamazsa null döner
     */
    private Gezegen getGezegenByName(String name) {
        for (Gezegen gezegen : gezegenler) {
            if (gezegen.getIsim().equals(name)) {
                return gezegen;
            }
        }
        return null;
    }

    /**
     * Simülasyondaki tüm gezegenlerin isimlerini, tarihlerini ve nüfuslarını konsola yazdirir.
     * Her gezegen sabit genişlikte bir sütun içinde hizalanarak tablo görünümü sağlanır.
     */
    private void displayGezegenler() {

    	// Gezegen sütunu genişliği
    	int planetFieldWidth = 16;  // İsimler için sabit genişlik
    	int dateFieldWidth = 15;    // Tarihler için sabit genişlik
    	// Her satırda yazdırılacak gezegen sayısı
    	int planetsPerRow = 7;

    	// Gezegenler başlığı yazdırılıyor
    	System.out.print("Gezegenler   ");
    	for (int i = 0; i < gezegenler.size(); i++) {
    	    // Gezegen ismini hizalayıp yazdırıyoruz
    	    String formattedPlanet = "--- " + gezegenler.get(i).getIsim() + " ---";
    	    System.out.printf("%-" + planetFieldWidth + "s", formattedPlanet);

    	    // Eğer 7 gezegen yazılmışsa, yeni satıra geçiyoruz
    	    if ((i + 1) % planetsPerRow == 0) {
    	        System.out.println();  // Yeni satıra geç
    	        System.out.print("             ");  // Yeni satır için hizalama ekliyoruz
    	    }
    	}
    	System.out.println();  // Yeni satıra geç (son gezegenler tamamlandıktan sonra)

    	// Tarih başlığı yazdırılıyor
    	System.out.print("Tarih        ");
    	for (int i = 0; i < gezegenler.size(); i++) {
    	    // Tarihi hizalı şekilde yazdırıyoruz
    	    String[] tarihParts = gezegenler.get(i).getTarih().split("\\.");
    	    String temizTarih = tarihParts[0] + "." + tarihParts[1] + "." + tarihParts[2];
    	    System.out.printf("%-" + dateFieldWidth + "s", temizTarih);

    	    // Eğer 7 gezegen yazılmışsa, yeni satıra geçiyoruz
    	    if ((i + 1) % planetsPerRow == 0) {
    	        System.out.println();  // Yeni satıra geç
    	        System.out.print("             ");  // Yeni satır için hizalama ekliyoruz
    	    }
    	}
    	System.out.println();  // Yeni satıra geç (son tarih yazıldıktan sonra)

    	// Nüfus başlığı yazdırılıyor
    	System.out.print("Nüfus        ");
    	for (int i = 0; i < gezegenler.size(); i++) {
    	    // Nüfus bilgisini hizalı şekilde yazdırıyoruz
    	    System.out.printf("%-" + planetFieldWidth + "d", gezegenler.get(i).getNufus());

    	    // Eğer 7 gezegen yazılmışsa, yeni satıra geçiyoruz
    	    if ((i + 1) % planetsPerRow == 0) {
    	        System.out.println();  // Yeni satıra geç
    	        System.out.print("             ");  // Yeni satır için hizalama ekliyoruz
    	    }
    	}
    	System.out.println();  // Son olarak yeni satıra geç
    }
    /**
     * Tüm uzay araçlarının ad, durum, çıkış/varış gezegeni, kalan süre ve varış tarihini konsola yazdırır.
     * Veriler hizalanmış şekilde yazilir, her araç için bir satır gösterilir.
     */
    private void displayUzayAraclari() {
        System.out.println("Uzay Araçları:");
        System.out.printf("%-10s %-10s %-7s %-7s %-20s %15s%n",
                "Araç Adı", "Durum", "Çıkış", "Varış", "Hedefe Kalan Saat", "Varacağı Tarih");

        for (UzayAraci uzayAraci : uzayAraclari) {
            System.out.println(getUzayAraciDurumu(uzayAraci));
        }
    }
    
    /**
     * Verilen uzay aracının adını, durumunu, çıkış ve varış gezegenini, 
     * hedefe kalan saatini ve tahmini varış tarihini formatlı bir şekilde döner.
     *
     * Durumlar: "IMHA", "Vardı", "Yolda", "Bekliyor"
     * @param uzayAraci Bilgisi alınacak uzay aracı
     * @return Formatlanmış bilgi  
     */
    private String getUzayAraciDurumu(UzayAraci uzayAraci) {

        // Aracin mevcut durumu belirlenir.
    	  String durum;
    	    if (uzayAraci.isImhaDurumu()) {
    	        durum = "IMHA";
    	    } else if (uzayAraci.getHedefeKalanSaat() == 0 && uzayAraci.isYolaCiktiMi()) {
    	        durum = "Vardı";
    	    } else if (uzayAraci.isYolaCiktiMi()) {
    	        durum = "Yolda";
    	    } else {
    	        durum = "Bekliyor";
    	    }
    	 // Varis tarihi belirlenir
        String varisTarihi = "--";
        if (durum.equals("Vardı")) {
            Gezegen varisGezegeni = getGezegenByName(uzayAraci.getVarisGezegeni());
            if (varisGezegeni != null) {
            	 varisTarihi = uzayAraci.getVarisTarihi(); 
            }
        } else if (!durum.equals("IMHA")) {
            varisTarihi = uzayAraci.getVarisTarihi();
        }
        
        return String.format("%-10s %-10s %-8s %-8s %-20d %s",
                uzayAraci.getIsim(),
                durum,
                uzayAraci.getCikisGezegeni(),
                uzayAraci.getVarisGezegeni(),
                uzayAraci.getHedefeKalanSaat(),
                varisTarihi);
    }

    /**
     * Simülasyondaki her uzay aracinin durumunu ve yolcularını günceller.
     * Uzay aracinin  kontrolü yapılır
     * Hedefe kalan saat ve yolcuların ömrü güncellenir
     * Tum yolcular öldüyse araç imha edilir
     */
    private void updateUzayAraclari() {
        for (UzayAraci uzayAraci : uzayAraclari) {
            // Hareket durumunu kontrol et (yola çıkma zamanı gelmişse yola çıkar vb.)
            uzayAraciHareketi(uzayAraci);
            
            // Araç yoldaysa ve imha edilmemişse saati ve ulaşma durmunu günceller.
            if (uzayAraci.isYolaCiktiMi() && !uzayAraci.isImhaDurumu()) {
                uzayAraci.guncelleHedefeKalanSaat();  // Varışa kalan süreyi azaltir.
                uzayAraci.kontrolEt();				// Hedefe ulaştı mı kontrollerini yapar.
            }
            // Aractaki her yolcunun kalan ömrünü günceller.
            for (Kisi yolcu : uzayAraci.getYolcular()) {
                yolcu.guncelleKalanOmur(); 
            }
            // Eğer tüm yolcular ölmüşse, araci imha eder.
            boolean herkesOlmus = uzayAraci.getYolcular().stream().noneMatch(Kisi::isAlive);
            if (herkesOlmus) {
                uzayAraci.setImhaDurumu(true);
            }
        }
    }
    /**
     * Her gezegenin tarihini ve nüfusunu simülasyon saatine göre günceller.
     * Ayrıca, yolculuğu biten ya da henüz başlamamış olan uzay araçlarının yolcularını ilgili gezegene ekler.
     */
    private void updateGezegenler() {
    	// Her gezegenin nüfusunu sıfırlar ve tarihini günceller
        for (Gezegen gezegen : gezegenler) {
            gezegen.resetNufus(); // Mevcut nüfusu temizler.
            gezegen.guncelleTarih(simülasyonSaati);  // Simülasyon saatine göre tarihi günceller.
        }

        // Uzay araçlarındaki yolcuları doğru gezegene yerleştirir.
        for (UzayAraci uzayAraci : uzayAraclari) {
            if (uzayAraci.isImhaDurumu()) continue; // İmha edilmiş araçları atlar.
            
            // Araç hala yolda mı diye kontrol eder
            String currentLocation;
            if (uzayAraci.isYolaCiktiMi() && uzayAraci.getHedefeKalanSaat() > 0) {
                continue;  // Hala yoldaysa, varış yapilmamıstir.
            } 
            // Eğer varışa ulaştıysa, bulunduğu gezegen varış gezegenidir
            // Eğer hala yola çıkmadıysa bulunduğu gezegen çıkış gezegenidir
            else if (uzayAraci.isYolaCiktiMi()) {
                currentLocation = uzayAraci.getVarisGezegeni(); 
            } else {
                currentLocation = uzayAraci.getCikisGezegeni(); 
            }
            
            
            Gezegen gezegen = getGezegenByName(currentLocation);
            if (gezegen != null) {
                for (Kisi yolcu : uzayAraci.getYolcular()) {
                	// Hayatta kalan yolcuları gezegen nüfusuna ekler.
                    if (yolcu.isAlive()) {
                        gezegen.addKisi(yolcu);
                    }
                }
            }
        }
    }
    /**
     * Eğer uzay aracı henüz yola çıkmadıysa ve imha edilmediyse,
     * çıkış gezegeninin tarihine göre kalkış zamanı gelmişse:
     * yolcular çıkış gezegeninden silinir, araç yola çıkar
     * hedefe kalan saat hesaplanır.
     */
    private void uzayAraciHareketi(UzayAraci uzayAraci) {
        if (!uzayAraci.isYolaCiktiMi() && !uzayAraci.isImhaDurumu()) {
            Gezegen cikisGezegeni = getGezegenByName(uzayAraci.getCikisGezegeni());
         // Eğer çıkış gezegeni tanımlıysa ve kalkış zamanı geldiyse
            if (cikisGezegeni != null && isKalkisZamaniGeldi(uzayAraci, cikisGezegeni)) {
                // Yolcuları cikis gezegeninden cikarir.
                for (Kisi yolcu : uzayAraci.getYolcular()) {
                    cikisGezegeni.removeKisi(yolcu);
                }

                // Aracı yola cikarir.
                uzayAraci.yolaCik();

                // Gezegendeki saati alir ve kalan yol süresini günceller.
                String[] tarihParts = cikisGezegeni.getTarih().split("\\.");
                int currentHour = Integer.parseInt(tarihParts[3]);
                uzayAraci.setHedefeKalanSaat(uzayAraci.getMesafeSaat() - currentHour);
            }
        }
    }
    /**
     * Uzay aracının kalkış zamanı gelip gelmedigini kontrol eder.
     * Kalkış tarihi ve gezegenin güncel tarihine göre karşılaştırma yapılır.
     */
    private boolean isKalkisZamaniGeldi(UzayAraci uzayAraci, Gezegen cikisGezegeni) {
    	// Güncel tarih ve planlanan kalkış tarihi parçalanır (gün.ay.yıl)
        String[] currentDateParts = cikisGezegeni.getTarih().split("\\.");
        String[] departureDateParts = uzayAraci.getCikisTarihi().split("\\.");
        
        int currentDay = Integer.parseInt(currentDateParts[0]);
        int currentMonth = Integer.parseInt(currentDateParts[1]);
        int currentYear = Integer.parseInt(currentDateParts[2]);
        
        int departureDay = Integer.parseInt(departureDateParts[0]);
        int departureMonth = Integer.parseInt(departureDateParts[1]);
        int departureYear = Integer.parseInt(departureDateParts[2]);
        
        // Tarihleri karsilastirir.
        if (currentYear > departureYear) {
            return true;
        } else if (currentYear == departureYear) {
            if (currentMonth > departureMonth) {
                return true;
            } else if (currentMonth == departureMonth) {
                return currentDay >= departureDay;
            }
        }
        return false;
    }
    /**
     * Simülasyonun bitip bitmediğini kontrol eder.
     * Eğer tüm araçlar ya imha olmuşsa ya da hedeflerine ulaşmışlarsa biter.
     */
    private boolean isSimulasyonBitti() {
        for (UzayAraci uzayAraci : uzayAraclari) {
        	 // Eğer hâlâ yolda olan ya da yola çıkmamış bir araç varsa simülasyon devam eder
            if (!uzayAraci.isImhaDurumu() && 
                (uzayAraci.getHedefeKalanSaat() > 0 || !uzayAraci.isYolaCiktiMi())) {
                return false; //Simulasyon devam eder.
            }
        }
        return true; // Tüm araçlar ya varmış ya da imha edilmiş
    }
    /**
     * Simülasyon tamamlandıktan sonra gezegenlerin ve uzay araçlarının
     * son durumlarını ve toplam simulasyon saatini ekrana yazdırır.
     */
    private void displayFinalDurum() {
    	pdp1.Console.clear();
        System.out.println("=== Final Durum ===");
        System.out.println("Toplam Simülasyon Saati: " + simülasyonSaati + "\n");
        displayGezegenler();
        displayUzayAraclari();
    }

}