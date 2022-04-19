# Ski-Jumping-Simulator

Symulator skoków narciarskich w C++.

## Tryby
- **Seria skoków:** Wybierasz skocznię, po czym wszyscy skoczkowie wpisani do pliku "jumpers.csv" oddają swoje skoki (tylko konkursy jednoseryjne).
- **Pojedynczy skok**: Wybierasz jednego skoczka (i skocznię) z listy. Wybierasz też ile razy skoczyć ma zawodnik i wyświetla się lista z jego wynikami.

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
- **Umiejętność lądowania** (od 1 do 60)
- **Forma** (od 1 do 120)
### Zapisywanie w pliku
Wszystkie atrybuty powinny być w takiej kolejności jak powyżej, **oddzielone przecinkami!!!**

Przykład:
```
Karl,Geiger,Niemcy,96,95,87,1,54,89
Piotr,Zyla,Polska,86,86,95,3,53,88
Kamil,Stoch,Polska,89,93,91,2,58,86
Domen,Prevc,Slowenia,79,81,96,2,53,75
```

*W przypadku atrybutów od 1 do 120 (czyli bez atrybutów lądowania) wartości powinny być max do 100. Wtedy wyniki będą bardziej realne.*

## Plik "hills.csv"
- **Nazwa**
- **Kraj**
- **Punkt K**
- **Punkt HS**
- **Punkty za belkę**
- **Punkty za wiatr przedni**
- **Maksymalna odległość mniej/więcej**
- **Startowa odległość**
- **Optymalna siła wybicia**
- **Metry za siłe wybicia**
- **Metry za technike wybicia**
- **Metry za technike lotu**

*Punkty za wiatr tylni będą obliczane automatycznie*

Przykład:
```
Wisla,Polska, 120, 134, 7.24, 10.8, 145.5, -117, 88.5, 1.4, 0.48, 0.48
Planica,Slowenia, 200, 240, 8.64, 14.4, 252.5, -157, 82, 1, 0.54, 0.83
```

### Obliczanie odległości
```
Startowa odległosc + (Technika wybicia * Metry za technike wybicia) + (Technika lotu * Metry za technike lotu) + (|Optymalna siła wybicia - siła wybicia| * Metry za siłę wybicia) + (Wiatr, belka i inne czynniki)
```
Siła wybicia, technika wybicia i technika lotu to ```Umiejętność + forma + losowość```

## Plik "config.csv"
- **Wiatr startowy**
- **Zmiana wiatru** (Jak wiatr może się zmienić. Wiatr jest obliczany: `Wiatr startowy + (losowanie między -zmiana wiatru a zmiana wiatru` np. `0.45 + (losowanie między -0.20 a 0.20)`);
- **Fałszywość wiatru** (Jest aby dodać realizmu. Wiatr przy skoku jest bez zmian, ale przy podawaniu wyników i podliczaniu punktów będzie inny. Np. jeżeli fałszywośc wiatru = 0.10. `Wiatr w wynikach = Wiatr + (losowanie między -0.10 a 0.10`. Można wyłączyć wpisując 0);
- **Rekompensata za belkę** (0 = nie, 1 = tak)
- **Rekompensata za wiatr** (0 = nie, 1 = tak)
- **Noty sędziowskie** (0 = nie, 1 = tak)
- **Pokazywanie wyników** (0 = nie, 1 = tak. Np. jeśli chcesz szybko przesymulować konkurs bez oglądania wyników na bieżąco to możesz wyłączyć tą opcje)

Przykład
```
0.80, 0.25, 0.10, 1, 1, 1, 1
```
