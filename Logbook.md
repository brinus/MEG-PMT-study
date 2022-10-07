# Logbook

## 23 settembre 2022

Il setup consiste in:
- Alimentatore mod. *Array 3646A* *HV* = 59 V
- Alimentatore mod. *Array 3646A* *LV* = 12 V
- Oscilloscopio mod. *Tektronik TDS2024C*
- Board custom mod. *LEM PAPA 2013-3*
- SiPM dim: 10x10x5 mm^3^
- Collimatore
- *DRS4 Evaluation Board V5* 4 canali
- PC Windows locale
- Sorgente di 90Sr

Vogliamo studiare lo spettro in funzione dell'alimentazione *HV* (*high voltage*)

Inseriamo prima della DRS4 un attenuatore da 10dB passivo, perchè ci accorgiamo che altrimenti il segnale (misura *peak-peak*) satura al valore (assoluto) di ~500 mV. Montiamo la sorgente di 90Sr in posizione. Frequenza di trigger ~5÷6 kHz. Trigger level: -56 mV.

### Spettro della WF: Span in *HV*

Abbiamo impostato ad occhio i cursori in modo da comprendere totalmente il segnale, abbiamo fatto misurare (con tanto di istogramma) l'integrale della WF. Abbiamo impostato l'alimentazione *HV* a 59 V, otteniamo 59.2 V (sembra che l'alimentatore aggiunga di conto suo 0.2 V). Abbiamo salvato il file come `test0923.001.dat` nella cartella `SummerStudent2022`.

Analizziamo il file con `readWD` e osserviamo il file `.root` in output. Esplorando il `TTree T` contenuto nel file di output, troviamo corrispondenza tra il branch `amplitude` e la misura effettuata dal PC locale *Peak-Peak Amplitude*. Non riusciamo invece a capire cosa siano i branch `area` e `area2`, in quanto non corrispondono con la misura del PC locale *Gated charge*.

Scopriamo che PC-loc misura l'integrale in pC. Scopriamo che nel codice `readWD.cpp` 
```
area += ped - aWF[bin]
```
Quindi è normale che il grafico risulti ribaltato rispetto all'asse verticale. Scopriamo come vengono determinate `iw.start` e `iw.stop`
```
iw.start = peakBin - gCONFIG.intRise * stdv;
iw.stop  = peakBin + gCONFIG.intDecay * tau;
```
Abbiamo inoltre capito che le scale orizzontali delle *WF* sono in ns.

Notare che `peakBin` prende il bin con il picco (**NEGATIVO**), per questo motivo utilizza il metodo `GetBinMinimum()` quando definisce `peakBin`. 

Rimane da capire quale sia la scala sull'asse orizzontale nel branch `area` e `area2`, e da capire come mai ci sia un fattore moltiplicativo di ~1/20 dalla scala di *Gated charge* a quella di `area`.


## 27 settembre 2022

Vogliamo fare lo scan in *HV* a step di 0.2 V. Controlliamo prima il rate, posizionata la sorgente di 90Sr: il rate vale ~3.5 kHz. Il nome di questi file sarà `scanHV.xx.dat` dove `xx` è il valore del voltaggio in V. Variamo il valore di *HV* lo facciamo variare tra 58 e 60 V. Ogni file ha 10000 entries.

Quando andiamo ad impostare il voltaggio, benchè andiamo di 0.2 in 0.2 (partendo da 58.0), l'*HV* assume un valore leggermente superiore (ordine di 0.1-0.2 V). Il valore della resistenza *POT* è di 0.491 kOhm.

1. 58.2 V
2. 58.3 V
3. 58.5 V
4. 58.7 V
5. 58.9 V
6. 59.1 V
7. 59.3 V
8. 59.5 V
9. 59.7 V
10. 59.9 V
11. 60.1 V

Facciamo uno scan in *POT*, da 0.7 a 0.3 kOhm a passi di 50 Ohm. Fissiamo la *HV* a 59.0 V (-> 59.1 V). I file si chiameranno `scanPOT.xx.dat`, dove xx è il valore della resistenza sul potenziometro in Ohm.

1. 717
2. 648
3. 606
4. 546
5. 497
6. 444
7. 406
8. 352
9. 302


## 7 ottobre 2022

### Misure di campo magnetico
Consideriamo il cilindro più grande e posizionimao la sonda in modo che sia allla stessa altezza del metro sui è poggiato il magnete.
Misuriamo il campo magnetico all'interno del cilindro (tramite la sonda) per diverse posizioni del magnete. Consideriamo la posizione della prima faccia del magnete, quella più vicina al cilindro.
L'errore sulle misure di posizione è determinato dal sapere dove si trova esattamente il centro del cilindro, 
dall'incertezza sulla posizione della sonda nel cilindro, ossia nel determinare si si trova esattamente nel centro oppure no

Misuriamo la circonferenza del cilindro in cui vereseremo l'azoto liquido. Vale (41.00 +- 0.2) cm. Il raggio è quindi (6.52 +- 0.03 ) [cm]. 
L'incertezza con cui misuriamo la distanza dal centro è di 0.2 cm perchè: fino alla fine del ciclindro argentato abbiamo una precisione di 0.03 cm, ma dalla fine del cilindro abbiamo realizzato noi le tacchette con il pennarello e il metro e quindi aggiungiamo un'incertezza che non è quella del metro (0.1 cm), ma è più grande perchè subentra lo spessore del pennarello e perciò consideriamo 0.2 cm. Alla fine sommando le due incertezze, 0.03 e 0.2 risulta un errore complessivo di 0.2 cm. Questa incertezza va sommata in quadratura con quella con cui determiniamo se la sonda è esattamente al centro del cilindro rivestito con il tape.
Tale errore è dato dalla differenza tra il raggio interno del cilindro stesso e metà spessore della sonda.

Il diametro interno vale (2.50 +- 0.01) [cm]. Come errore abbimao assunto quello del metro (0.05 [cm])/sqrt(12). 

Di conseguenza il raggio interno vale (1.250 +- 0.005) [cm].

Metà spessore della sonda è 0.3 cm. Dunque l'errore sistematico nel posizionare la sonda nel centro è (1.3 - 0.3) [cm] (abbiamo approssimato 1.25 con 1.3), cioè 1 [cm].

Alla fine l'errore complessivo è dato dalla somma in quadratura di errore statistico (misura della distanza dal centro esatto) e sistematico (misura della posizone della sonda), rispettivamente di 0.2 [cm] e 1 [cm]. 

L'errore sulle misure di campo magnetico è 0.002 [mT], poichè l'errore di "costruzione", visto sul manuale è trascurabile rispetto al digit che "balla".



distanza [cm] | B [mT] | 
:-------------| :------|
 8 | 5.831 |
 9 | 4.472 |
 10| 3.415 |
 11| 2.530 |
 12| 1.979 |
 13| 1.550 |
 14| 1.221 |
 15| 0.963 |
 16| 0.783 |
 17| 0.625 |
 18| 0.500 |
 19| 0.391 |
 20| 0.313 |

### Riproducibilità delle misure fatte
Posizioniamo il cilindro argentato e l'asta. Inseriamo il fermo per il ciclindro con il tape, inseriamo il cilindro stesso al centro di quello argentato 
 e poi al suo interno la sonda. Posizioniamo il magnete nel primo punto in cui vogliamo misurare il campo e facciamo scendere la sonda nel cilindro, fermandola all'altezza in cui il campo magnetico è maggiore e che quindi ci aspettiamo sia il punto allineato (più vicino) al magnete.

Decidiamo di togliere il cilindro argentato, che adesso non serve. Prima abbiamo inserito la sonda in modo che fosse alla stessa altezza del magnete e subito dopo abbiamo inserito il cilindro che la contiene, posizionandolo sul tavolo in verticale.

Posizioniamo il magnete accanto alla scala con i centimetri e poi la sonda in orizzontale, in modo che sia davanti al magnete. Misuriamo la distanza tra sonda e magnete (1.60  + - 0.05[cm]). A questo punto inseriamo il cilindro con tape. Come incertezza sul campo prendiamo 0.01 [mT] pe rle prime due misure e 0.001 [mT] per le altre.

distanza [cm] | B [mT] | 
:-------------| :------|
1 | -53.14 |
2 | -28.93 |
3 | -18. 524 |
4 | - 12.445 |
5 | -7.797 |
6 | -5.404 |
7 | -3.951 |
8 | -2.971 |
9 | -2.120 |
10 | -1.521|

Togliamo il cilindro più grande, controlliamo di nuovo la distanza tra sonda e magnete (sempre 1.6 [cm]) ed inseriamo il cilindro più piccolo. Le incertezze di msiura sono le stesse.

distanza [cm] | B [mT] | 
:-------------| :------|
1 | -68.68 |
2 | -39.90|
3 | -24.27 |
4 | -15.370 |
5 | -10.327 |
6 | -7.236 |
7 | -5.240 |
8 | -3.748 |
9 | -2.775 |
10 | -2.038|





