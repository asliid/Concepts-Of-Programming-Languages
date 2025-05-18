package pdp1;

import java.io.IOException;
public class Console {
	
	//Konsolu temizler.
    public static void clear() {
        try {
            if (System.getProperty("os.name").contains("Windows")) 
                new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
            else 
                Runtime.getRuntime().exec("clear");
            System.out.print("\033c\033[3J");
            System.out.flush();
            
        } catch (IOException | InterruptedException ex) {           
        	
        }
    }
}  