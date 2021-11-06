# Ski-Jumping-Simulator

Symulator skoków narciarskich w C++.

## Tryby
- **Seria skoków:** Wybierasz skocznię, po czym wszyscy skoczkowie wpisani do pliku "jumpers.csv" oddają swoje skoki (tylko konkursy jednoseryjne).
- **Pojedynczy skok** (niedostępne): Wybierasz jednego skoczka (i skocznię) i na własno ustawionym wietrze + belce skoczek oddaje 1 skok lub więcej.

## Plik jumpers.csv
Plik znajduje się w folderze "resources" (i musi tam być). Są w nim wpisani skoczkowie do serii skoków (lub pojedynczego skoku).
### Atrybuty skoczka
- **Imię**
- **Nazwisko**
- **Narodowość**
- **Umiejętność siły wybicia** (od 1 do 120)
- **Umiejętność techniki wybicia** (od 1 do 120)
- **Umiejętność techniki lotu** (od 1 do 120)
- **Styl lotu** (od 0 do 4: *styl klasyczny, styl V, nowoczesne V, szerokie V, styl H*)
- **Umiejętność lądowania** (od 1 do 60) (ma wpływ na to jak dobrze umie wylądować zawodnik, a nie jak ładnie. Np Ammann umie dobrze lądować ale niezbyt ładnie.)
- **Styl lądowania** (od 1 do 60)
- **Forma** (od 1 do 120)
### Zapisywanie w pliku
Wszystkie atrybuty powinny być w takiej kolejności jak powyżej, **oddzielone przecinkami!!!**

Przykład:
```
Karl,Geiger,Niemcy,96,95,87,1,54,53,89
Piotr,Zyla,Polska,86,86,95,3,53,52,88
Kamil,Stoch,Polska,89,93,91,2,56,58,86
Domen,Prevc,Slowenia,79,81,96,2,53,53,75
```

*W przypadku atrybutów od 1 do 120 (czyli bez atrybutów lądowania) wartości powinny być max do 100. Wtedy wyniki będą bardziej realne.*

## Plik "hills.csv"
- **Nazwa**
- **Narodowość**
- **Punkt K**
- **Punkt HS**
- **Punkty za belkę**
- **Metry za belkę** (-1 oznacza że będzie wynosić `Punkty za belke / Punkty za metr` (dla dużej skoczni 1.8, dla normalnej 2.0 itd)
- **Punkty za wiatr przedni**
- **Metry za wiatr przedni**
- **Punkty za wiatr tylni**
- **Metry za wiatr tylni**
- **Maksymalna odległość mniej/więcej**
- **Startowa odległość**
- **Trudność lądowania**
- **Bonus za styl lotu** (dla każdego stylu osobno)
- **Optymalna siła wybicia**
- **Metry za siłe wybicia**
- **Metry za technike wybicia**
- **Metry za technike lotu**

Przykład:
```
Wisla,Polska, 120, 134, 7.24, -1, 10.8, 7.9, 13.07, 9.15, 145.5, -117, 130, -14, 18, 19, 20, 20, 88.5, 1.4, 0.48, 0.48
Planica,Slowenia, 200, 240, 8.64, -1, 14.4, 11, 17.42, 15.5, 252.5, -157, 180, -27, 20, 24.5, 27, 30, 82, 1, 0.54, 0.83
```

### Obliczanie odległości
```
Startowa odległosc + (Technika wybicia * Metry za technike wybicia) + (Technika lotu * Metry za technike lotu) + (|Optymalna siła wybicia - siła wybicia| * Metry za siłę wybicia) + (Wiatr, belka i inne czynniki)
```
Siła wybicia, technika wybicia i technika lotu to ```Umiejętność + forma + losowość```

## Plik "config.csv"
- **Przedział wiatru** (Dwie oddzielne wartośći. Wiatr startowy będzie losowany między tymi wartościami)
- **Zmiana wiatru** (Jak wiatr może się zmienić. Wiatr jest obliczany: `Wiatr startowy + (losowanie między -zmiana wiatru a zmiana wiatru` np. `0.45 + (losowanie między -0.20 a 0.20)`);
- **Fałszywość wiatru** (Jest aby dodać realizmu. Wiatr przy skoku jest bez zmian, ale przy podawaniu wyników i podliczaniu punktów będzie inny. Np. jeżeli fałszywośc wiatru = 0.10. `Wiatr w wynikach = Wiatr + (losowanie między -0.10 a 0.10`. Można wyłączyć wpisując 0);
- **Rekompensata za belkę** (0 = nie, 1 = tak)
- **Rekompensata za wiatr** (0 = nie, 1 = tak)
- **Noty sędziowskie** (0 = nie, 1 = tak)
- **Pokazywanie wyników** (0 = nie, 1 = tak)
- **Oczekiwanie po skoku** (Jeśli 0, trzeba nacisnąć dowolny klawisz po skoku aby kontynuować, inaczej czeka X milisekund. Sekunda = 1000ms)
- **Pokazywanie wyników** (0 = nie, 1 = tak. Np. jeśli chcesz szybko przesymulować konkurs bez oglądania wyników na bieżąco to możesz wyłączyć tą opcje)

Przykład
```
0.80, 0.80, 0.25, 0.10, 1, 1, 1, 1, 0, 1
```