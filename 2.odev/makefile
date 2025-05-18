all: derle bagla calistir

derle:
	gcc -c -I ./include/ ./src/Gezegen.c -o ./lib/Gezegen.o
	gcc -c -I ./include/ ./src/KayacGezegen.c -o ./lib/KayacGezegen.o
	gcc -c -I ./include/ ./src/GazDeviGezegen.c -o ./lib/GazDeviGezegen.o
	gcc -c -I ./include/ ./src/BuzDeviGezegen.c -o ./lib/BuzDeviGezegen.o
	gcc -c -I ./include/ ./src/CuceGezegen.c -o ./lib/CuceGezegen.o
	gcc -c -I ./include/ ./src/UzayAraci.c -o ./lib/UzayAraci.o
	gcc -c -I ./include/ ./src/Simulasyon.c -o ./lib/Simulasyon.o
	gcc -c -I ./include/ ./src/Zaman.c -o ./lib/Zaman.o
	gcc -c -I ./include/ ./src/DosyaOkuma.c -o ./lib/DosyaOkuma.o
	gcc -c -I ./include/ ./src/Kisi.c -o ./lib/Kisi.o
	gcc -c -I ./include/ ./src/Console.c -o ./lib/Console.o
	gcc -c -I ./include/ ./src/Exception.c -o ./lib/Exception.o
	gcc -c -I ./include/ ./src/program.c -o ./lib/program.o

bagla:
	gcc ./lib/*.o -o ./bin/program

calistir:
	./bin/program