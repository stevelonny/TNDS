# Laboratorio di TNDS di steve
Raccolta di codici scritti durante il corso di [Laboratorio di Trattamento Numerico dei Dati Sperimentali](http://labmaster.mi.infn.it/Laboratorio2/labTNDS/) (A.A. 2021-2022) di Fisica @UNIMI. Il turno di laboratorio è quello tenuto dal [prof. Tomasi](https://ziotom78.github.io/tnds-tomasi-notebooks/).
#### Dipendenze
Nelle ultime lezioni e nei temi svolti è stato fatto uso della libreria [```fmtlib```](https://fmt.dev), che è quindi inclusa in questa repo per comodità spesso anche nelle sottocartelle. Molti codici usano [```root```](https://root.cern) per disegnare i grafici.

## Lezioni

### [Lezione 1](/Lezione01/)
Lettura da file e uso di array dinamici.
Implentazioni basiche di funzioni di manipolazione dati e statistica.
Funzioni in librerie.

### [Lezione 2](/Lezione02/)
Sviluppo di un classe vettore per l'allocazione di memoria dinamica.
Riadattate le funzioni nella libreria dell'esercizio precedente.
Uso di librerie multiple.

### [Lezione 3](/Lezione03/)
Implentazione dei template type nella libreria di vettori dell'esercizio precedente. Introduzione alla libreria STL ```<vector>```.
Uso anche di TH1F e di root.

### [Lezione 4-5](/Lezione04-5/)
Uso delle classi per il calcolo del campo vettoriale.
Uso di root per il grafico del dipolo.

### [Lezione 6](/Lezione06/) & [Lezione 6.1](/Lezione06.1/)
Ricerca degli zeri con il metodo della bisezione e della secante.
La corretta implementazione della secante è contenuta in [`/Lezione06.1`](/Lezione06.1/)

### [Lezione 7](/Lezione07/)
Integrazione numerica.

### [Lezione 8-9](/Lezione08-9/)
Equazioni differenziali con metodi di Eulero e Runge-Kutta.
Oscillatore armonico semplice (pure disegnato con ricerca della frequenza di risonanza contenuta in [`riproviamo.cpp`](/Lezione08-9/riproviamo.cpp)).
Pendolo (graficato con ricerca del periodo).

### [Lezione 10](/Lezione10/)
Random generator e metodi montecarlo.
L'esercizio 10.2 è diviso in due file: [`carlosampling.cpp`](/Lezione10/carlosampling.cpp) e [`graphcarlo.cpp`](/Lezione10/graphcarlo.cpp).

### [Lezione 11](/Lezione10/)
Esperimento del prisma simulato con metodi montecarlo.

---

## Temi d'esame
Non tutti sono completi e nemmeno corretti
Data | Argomento | Tema
| :--- | :--- | ---: |
[2008 09 16](/Temi/Prova20080916/)          | Eq. diff.         | [Compito_lab2_sep08.pdf](http://labmaster.mi.infn.it/Laboratorio2/labTNDS/TemiEsame/Compito_lab2_sep08.pdf)
[2009 01 15 (1)](/Temi/Prova20090115_1)     | Integrazione      | [Compito_lab2_pre09_1.pdf](http://labmaster.mi.infn.it/Laboratorio2/labTNDS/TemiEsame/Compito_lab2_pre09_1.pdf)
[2009 01 15 (6)](/Temi/Prova20090115_6)     | Esperimento       | [Compito_lab2_pre09_6.pdf](http://labmaster.mi.infn.it/Laboratorio2/labTNDS/TemiEsame/Compito_lab2_pre09_6.pdf)
[2009 06 25 (1)](/Temi/Prova20090625_1/)    | Esperimento       | [Compito_lab2_giu09.pdf](http://labmaster.mi.infn.it/Laboratorio2/labTNDS/TemiEsame/Compito_lab2_giu09.pdf)
[2009 07 22 (1)](/Temi/Prova20090722_1/)    | Eq. diff.         | [Compito_lab2_lug09.pdf](http://labmaster.mi.infn.it/Laboratorio2/labTNDS/TemiEsame/Compito_lab2_lug09.pdf)
[2010 02 25 (1)](/Temi/Prova20100225_1)     | Eq. diff.         | [Compito_lab2_feb10.pdf](http://labmaster.mi.infn.it/Laboratorio2/labTNDS/TemiEsame/Compito_lab2_feb10.pdf)
[2010 02 25 (2)](/Temi/Prova20100225_2/)    | Esperimento       | [Compito_lab2_feb10.pdf](http://labmaster.mi.infn.it/Laboratorio2/labTNDS/TemiEsame/Compito_lab2_feb10.pdf)
[2010 06 10](/Temi/Prova20100610/)          | Esperimento       | [Compito_lab2_giu10.pdf](http://labmaster.mi.infn.it/Laboratorio2/labTNDS/TemiEsame/Compito_lab2_giu10.pdf)
[2020 06 15](/Temi/Prova20200615/)          | Integrazione      | [AppelloTNDS_20200615.pdf](http://labmaster.mi.infn.it/Laboratorio2/labTNDS/TemiEsame/AppelloTNDS_20200615.pdf)
[2022 01 25](/Temi/Esame20220125)           | Ricerca zeri e Int.   | [20220115.pdf](/Temi/Esame20220125/20220115.pdf)
[2023 06 28](/Temi/Prova20230628)           | Eq. diff.             | [AppelloTNDS_20230628.pdf](/Temi/Prova20230628/AppelloTNDS_20230628.pdf)

----
----

## ToDo
Cose da mettere a posto

- [x] cambiare makefile e mettere solo una fmtlib invece di mille
- [ ] porre un readme dentro ogni lezione
- [ ] commentare funzioni/fare libreria
- [ ] pulire e correggere temi d'esame (con commenti magari)
- [ ] aggiungere versioni con gnuplot++
