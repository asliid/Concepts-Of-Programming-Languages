/** 
* 
* @author Aslı Döngez ve asli.dongez@ogr.sakarya.edu.tr 
* @since 05.05.2025
* <p> 
* Konsol Temizleme Sınıfı
* </p> 
*/
#include <stdio.h>
#include <stdlib.h>
#include "Console.h"

void Console_clear() {
    // Windows ise cls, Linux/Mac ise clear
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}