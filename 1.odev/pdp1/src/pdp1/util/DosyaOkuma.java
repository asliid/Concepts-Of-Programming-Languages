/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 26.03.2025
* <p> 
* Dosya Okuma Sınıfı
* </p> 
*/



package pdp1.util;

import java.io.*;
import java.util.*;
import pdp1.model.*;


public class DosyaOkuma {
	
	//	Kisiler.txt dosyasını okuyarak her satiri bir Kisi nesnesine dönüştürür.
    public static List<Kisi> kisilerGetir() {
        List<Kisi> kisiler = new ArrayList<>();
        try (BufferedReader reader = new BufferedReader(new FileReader("Kisiler.txt"))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split("#");
                String isim = parts[0];
                int yas = Integer.parseInt(parts[1]);
                int kalanOmur = Integer.parseInt(parts[2]);
                String uzayAraciAdi = parts[3];
                Kisi kisi = new Kisi(isim, yas, kalanOmur, uzayAraciAdi);
                kisiler.add(kisi);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return kisiler;
    }
    /* Araclar.txt dosyasından uzay aracı bilgilerini okur.
     * Her uzay aracinin ismine göre o araca ait yolcuları kisiler listesinden bulur.
     * Her aracı ve yolcularını içeren UzayAraci nesnelerini oluşturur ve uzayAraci listesine ekler
     */
    public static List<UzayAraci> uzayAraclariniGetir(List<Kisi> kisiler) {
        List<UzayAraci> uzayAraclari = new ArrayList<>();
        try (BufferedReader reader = new BufferedReader(new FileReader("Araclar.txt"))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split("#");
                String isim = parts[0];
                String cikisGezegeni = parts[1];
                String varisGezegeni = parts[2];
                String cikisTarihi = parts[3];
                int mesafeSaat = Integer.parseInt(parts[4]);
                List<Kisi> yolcular = new ArrayList<>();
                // Araca ait kişileri bulur ve araca ekler
                for (Kisi kisi : kisiler) {
                    if (kisi.getBulunduguUzayAraciAdi().equals(isim)) {
                        yolcular.add(kisi);
                    }
                }
                UzayAraci uzayAraci = new UzayAraci(isim, cikisGezegeni, varisGezegeni, cikisTarihi, mesafeSaat, yolcular, false);
                uzayAraclari.add(uzayAraci);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return uzayAraclari;
    }
    //Gezegenler.txt dosyasındaki her satırı bir Gezegen nesnesine dönüştürür.
    public static List<Gezegen> gezegenleriGetir() {
        List<Gezegen> gezegenler = new ArrayList<>();
        try (BufferedReader reader = new BufferedReader(new FileReader("Gezegenler.txt"))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split("#");
                String isim = parts[0];
                int gununKacSaatOldugu = Integer.parseInt(parts[1]);
                String tarih = parts[2];
                Gezegen gezegen = new Gezegen(isim, gununKacSaatOldugu, tarih);
                gezegenler.add(gezegen);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return gezegenler;
    }
}