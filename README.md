# C++ Dice Simulator

## Un simplu program in terminal care consta in rostogolirea zarurilor  
#### (facut in C++)

Acest program a fost facut ca un proiect universitar pentru materia __Metode Avansate de Programare__. 
__El contine atat analize simple de probabilitate si statistici, cat si 2 joculete single-player, respectiv *CRAPS* si *YAHTZEE* (+sistem de balanta pentru joculete)__

___

## __Cum se obtine imaginea Docker:__
```
docker pull ...
```

***

* ***Comenzi disponibile:***
    1. --faces < val >
    1. --dice < val >
    1. --rolls < val >
    1. --game < mod > [ moduri: ]
        1. stats
        1. prob < val > [ va da probabilitatea ca (rolls x dice) sa dea suma < val >]
        1. sum
        1. craps
        1. yahtzee
    1. --seed < val >

    1. --help / --h [ afiseaza informatii ]
    1. --. [ ruleaza programul cu valoriile default ]

## Exemple de rulari (cu Docker):
```
docker run dice-sim --.
docker run dice-sim --dice 1 --rolls 3 --game prob 15
docker run -it dice-sim --game craps
docker run dice-sim --game stats --faces 20
docker run -it dice-sim --game yahtzee
```
## **IMPORTANT!!!**
#### Pentru a va asigura ca puteti interactiona cu joculetele:
```
docker run -it dice-sim --game yahtzee [craps sau yahtzee]

```
#### Pentru a salva si a tine cont de balanta pentru joculete:
```
mkdir -p write_dir

docker run -it -v "$(pwd)/write_dir:/write_dir" dice-sim --game craps
[craps sau yahtzee]
```
### BONUS INFO:
#### La alegerea joculetelor, nu are rost sa adaugati alta comanda, deoarece ele vin cu setari prestabilite