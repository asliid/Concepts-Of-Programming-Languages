/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 26.03.2025
* <p> 
* Main Sınıf
* </p> 
*/


package pdp1;

import pdp1.model.*;
import pdp1.simulasyon.*;
import pdp1.util.*;
import java.util.List;

public class Main {
    public static void main(String[] args) throws InterruptedException {
    	
        List<Kisi> kisiler = DosyaOkuma.kisilerGetir();     // Kişi verilerini dosyadan okunur.
        List<UzayAraci> uzayAraclari = DosyaOkuma.uzayAraclariniGetir(kisiler);     // Uzay araçları kişilere göre dosyadan okunur.
        List<Gezegen> gezegenler = DosyaOkuma.gezegenleriGetir();     //  Gezegenler dosyadan okunur.


        Simulasyon simulasyon = new Simulasyon(gezegenler, uzayAraclari);
       
        
        // Simulasyon öncesi ekrani temizler.
        Console.clear();
        
        // Simulasyonu baslatir.
        simulasyon.baslat();
        
        System.out.println("Simülasyon başarıyla tamamlandı!");
      
    }
}