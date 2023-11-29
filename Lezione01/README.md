# Lezione 1 (5 Ottobre 2021)

Gli esercizi da svolgere per oggi sono i seguenti:

-   Esercizio 1.0
-   Esercizio 1.1
-   Esercizio 1.2
-   Esercizio 1.3

La descrizione è fornita sul [sito del laboratorio](http://labmaster.mi.infn.it/Laboratorio2/labTNDS/lectures_1819/lezione1_1819.html).

Per questo turno rendo sempre disponibili slide aggiuntive, con consigli specifici per svolgere gli esercizi ed approfondimenti. Le potete trovare a questo link: [ziotom78.github.io/tnds-tomasi-notebooks](https://ziotom78.github.io/tnds-tomasi-notebooks).

## Come usare Repl.it

-   Usate il pannello di sinistra per muovervi tra le cartelle
-   Il pannello di destra ha due funzionalità: *Console* e *Shell*. L'anno scorso abbiamo visto che *Console* vorrebbe essere una shell «furba», ma che spesso si blocca e richiede di chiudere la pagina e il browser e ripartire: vi consiglio di usare sempre *Shell*, che non ha mai dato questo tipo di problemi.
-   Evitate di copiare il file `data.dat` nelle sottocartelle; quando eseguite i vostri programmi, indicate esplicitamente `../data.dat`:

    ```
    $ ./esercizio1.0 10 ../data.dat
    ```

    Il motivo è che `data.dat` è un file abbastanza grande (~750 KB), e più dati sono salvati in una sessione Repl.it, più lenta è poi questa ad avviarsi.