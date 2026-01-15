# C++ Dice Simulator

## Un simplu program in terminal care consta in rostogolirea zarurilor  
#### (facut in C++)

Acest program a fost facut ca un proiect universitar pentru materia __Metode Avansate de Programare__. 
__El contine atat analize simple de probabilitate si statistici, cat si 2 joculete single-player, respectiv *CRAPS* si *YAHTZEE* (+sistem de balanta pentru joculete)__

___

## __Cum se obtine imaginea Docker:__
```
docker pull alexlct/dice-sim:latest
```

## __Cum se creaza si ruleaza containerul Docker (continuati sa cititi inainte de a rula comanda):__
```
docker run alexlct/dice-sim:latest
```

## **IMPORTANT!!!**
#### Pentru a va asigura ca puteti interactiona cu joculetele:
```
docker run -it alexlct/dice-sim:latest
```

#### Sau pentru a interactiona si salva balanta pentru joculete (RECOMANDAT):
```
docker run -it -v "$(pwd)/write_dir:/write_dir" alexlct/dice-sim:latest
```

## Exemple de rulari (cu Docker):
```
docker run alexlct/dice-sim:latest --.
docker run alexlct/dice-sim:latest --dice 3 --rolls 10 --game prob 15
docker run -it -v "$(pwd)/write_dir:/write_dir" alexlct/dice-sim:latest --game craps
docker run alexlct/dice-sim:latest --game stats --faces 20
docker run -it -v "$(pwd)/write_dir:/write_dir" alexlct/dice-sim:latest --game yahtzee
```

***

- ***Comenzi disponibile:***
    - --faces < val >
    - --dice < val >
    - --rolls < val >
    - --game < mod > [ moduri: ]
        1. stats
        1. prob < val > [ va da probabilitatea ca '--dice' zaruri sa dea suma < val > in '--rolls' rulari ]
        1. sum
        1. craps
        1. yahtzee
    - --seed < val >

    - --help / --h [ afiseaza informatii ]
    - --. [ ruleaza programul cu valorile default ]

### BONUS INFO:
#### La alegerea joculetelor (CRAPS sau YAHTZEE), nu are rost sa adaugati alta comanda, deoarece ele vin cu setari prestabilite