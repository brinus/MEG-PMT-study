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


