# Vidurkio skaičiuoklė

## Programos veikimas
  
  * Paleidus programą, vartotojo yra paklausiama ar jis nori pats irašyti duomenis ar visus veiksmus atlikti su failais

  * Pasirinkus rašyti rankiniu būdu, vartotojo yra prašoma įvesti studento vardą bei pavardę
  * Tada yra paklausiama ar yra žinomas pažymių skaičius, bei kokiu būdu norima įvesti tuos pažymius (įrašyti ranka arba generuoti atsitiktinai)
  * Įrašius visus pažymius (įskaitant ir egzamino vertinimą), vartotojui leidžiama pasirinkti ar jis nori pridėti dar vieną studenta
  * Įrašius norimą kiekį studentų, vartotojas turi galimybę pasirinkti rezultatus: vidurkį arba medianą

  --------------------------------------------------------------------------------------------------------

  * Pasirinkus atlikti veiksmus su failais, vartotojo yra paklausiama ar jis nori generuoti duomenų failus.
  * Pasirinkus generuoti, vartotojui leidžiama rinktis kuriuos failus nori generuoti
  * Po failų sukūrimo, vartotojas turi pasirinkti kurį failą jis nori nuskaityti
  * Galiausiai vartotojui duodamas pasirinkimas pagal ką rūšiuoti studentus : vidurkį ar medianą

  * Tuomet rezultatai yra išvedami į 2 atskirus failus: vargšiukai ir kietiakai (kietiakai, kurių vidurkis >= 5)
  
  ***Įvedus neegzsituojančio failo pavadinimą, programa parodys klaidos pranešimą ir baigs darbą***

## Programos diegimas bei naudojimas
* Parsisiųskite programos kodą iš [Releases](https://github.com/MantasLengvinas/OOP-2-uzt/releases)
* Jei naudojate Linux/Mac OS, tai naudokite šias komandas: 
```bash

    g++ -c functions.cpp
    g++ -o main main.cpp functions.o
    ./main

```

ARBA

```bash
  make makefile all
```

* Nuo v0.5, programą galima paleisti taip:

```bash
    g++ -c functions.cpp
    g++ -o main main.cpp functions.o
    ./main {norimas konteineris (v, d, l)}
```

* Jei naudojate Windows OS, tai naudokite šias komandas:
```bash

    g++ -c functions.cpp
    g++ -o main main.cpp functions.o
    main

```
ARBA
```bash
  cmake .
  cmake --build .
```
* Taip pat programos kodą galima įkelti į jūsų mėgiama IDE (pvz: CodeBlocks) ir tiesiog paleisti kodą

## Programos atminties naudojimo ir jos spartos įvertinimas

| **Vector**               | 1 000   | 10 000  | 100 000   | 1 000 000  | 10 000 000   |
| ------------------------ | ------- | ------- | --------- | ---------- | ------------ |
| **Atminties naudojimas** |         |         |           |            |              |
| Vieno konteinerio        | 0.171MB | 0.691MB |  7.813MB  | 77.445MB   |   774.184MB  |
| Dviejų konteinerių       | 0.241MB | 2.714MB | 23.742MB  | 263.688MB  |  2297.540MB  |
| Skirtumas                | 0.070MB | 2.023MB | 15.929MB  | 186.242MB  |  1523.350MB  |
|                          |         |         |           |            |              |
| **Laiko naudojimas**     |         |         |           |            |              |
| Vieno konteinerio        | 0.004s  | 0.036s  | 0.413s    | 5.188s     |  71.450s     |
| Dviejų konteinerių       | 0.002s  | 0.032s  | 0.302s    | 3.918s     |  41.976s     |
| Skirtumas                | 0.002s  | 0.004s  | 0.111s    | 1.270s     |  22.474s     |

| ***Deque***              | 1 000   | 10 000  | 100 000   | 1 000 000  | 10 000 000   |
| ------------------------ | ------- | ------- | --------- | ---------- | ------------ |
| **Atminties naudojimas** |         |         |           |            |              |
| Vieno konteinerio        | 0.113MB | 0.644MB |  8.437MB  | 81.683MB   |   805.992MB  |
| Dviejų konteinerių       | 0.125MB | 2.312MB | 22.363MB  | 215.238MB  |   2123.81MB  |
| Skirtumas                | 0.011MB | 1.667MB | 13.925MB  | 133.555MB  |  1317.820MB  |
|                          |         |         |           |            |              |
| **Laiko naudojimas**     |         |         |           |            |              |
| Vieno konteinerio        | 0.0023s | 0.057s  | 0.719s    | 6.222s     |  79.265s     |
| Dviejų konteinerių       | 0.0028s | 0.043s  | 0.653s    | 5.669s     |  72.471s     |
| Skirtumas                | 0.0005s | 0.014s  | 0.066s    | 0.553s     |   6.794s     |

| ***List***               | 1 000   | 10 000  | 100 000   | 1 000 000  | 10 000 000   |
| ------------------------ | ------- | ------- | --------- | ---------- | ------------ |
| **Atminties naudojimas** |         |         |           |            |              |
| Vieno konteinerio        | 0.121MB | 0.882MB |  9.476MB  |  91.765MB  |   902.312MB  |
| Dviejų konteinerių       | 0.183MB | 2.386MB | 27.488MB  | 241.383MB  |    2351.2MB  |
| Skirtumas                | 0.062MB | 1.503MB | 18.011MB  | 149.617MB  |   1448.89MB  |
|                          |         |         |           |            |              |
| **Laiko naudojimas**     |         |         |           |            |              |
| Vieno konteinerio        | 0.0015s | 0.022s  | 0.255s    | 3.598s     |  51.181s     |
| Dviejų konteinerių       | 0.0011s | 0.011s  | 0.139s    | 1.498s     |  30.419s     |
| Skirtumas                | 0.0004s | 0.011s  | 0.116s    | 2.100s     |  20.762s     |

* Procesorius: Intel Core I5-9300H, 2.4 GHz
* RAM: 8GB DDR4 2400MHz 
* SSD: NVMe M.2
	
## Versijos

  * [v0.1](https://github.com/MantasLengvinas/OOP-2-uzd/releases/tag/v0.1) Įvykdyti v0.1 reikalavimai
  * [v0.2](https://github.com/MantasLengvinas/OOP-2-uzd/releases/tag/v0.2) Įvykdyti v0.2 reikalavimai - galimybė skaityti iš failo
  * [v0.3](https://github.com/MantasLengvinas/OOP-2-uzd/releases/tag/v0.3) Įvykdyti v0.3 reikalavimai - įdėti try catch blokai, programa išskaidyta į atskirus failus
  * [v0.4](https://github.com/MantasLengvinas/OOP-2-uzd/releases/tag/v0.4) Įvykdyti v0.4 reikalavimai - failų generavimas, laiko analizė, studentų skirstymas pagal galutinį balą
  * [v0.5](https://github.com/MantasLengvinas/OOP-2-uzd/releases/tag/v0.5) Įvykdyti v0.5 reikalavimai - programa gali saugoi duomenys 3 skirtinguose konteineriuose: list, deque ir vector
  * [v1.0](https://github.com/MantasLengvinas/OOP-2-uzd/releases/tag/v1.0) Įvykdyti v1.0 reikalavimai - įdėtas partition optimizavimas, padaryti memory testai, bei sukurti makefile
