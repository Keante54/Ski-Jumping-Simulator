# Ski-Jumping-Simulator
Program do symulowania wyników skoków narciarskich.

## Zawartość folderu programu
***ski-jumping-simulator.exe*** - plik z programem.<br>
***folder resources*** - są tam pliki z zawodnikami, skoczniami, konfiguracjami konkursu itd.<br>
***folder results*** - ma dwa podfoldery: "csv" i "text" dla różnych formatów zapisu. Są tam wyniki konkursów.<br>
***folder src*** - kod źrodłowy programu.<br>

## Plik "jumpers.csv"
Plik znajduje się w folderze "resources" (i musi tam być). Są w nim wpisani skoczkowie do symulacji.

### Atrybuty skoczka
- Imię
- Nazwisko
- Narodowość
- Umiejętność siły wybicia (od 1 do 120)
- Umiejętność techniki wybicia (od 1 do 120)
- Umiejętność techniki lotu (od 1 do 120)
- Styl lotu (od 0 do 4: styl klasyczny, styl V, nowoczesne V, szerokie V, styl H)
- Umiejętność lądowania (od 1 do 60)
- Forma (od 1 do 120)
- Zapisywanie w pliku
- Wszystkie atrybuty powinny być w takiej kolejności jak powyżej, oddzielone przecinkami!!!

Przykład:

```
Karl,Geiger,Niemcy,96,95,87,1,54,89
Piotr,Zyla,Polska,86,86,95,3,53,88
Kamil,Stoch,Polska,89,93,91,2,58,86
Domen,Prevc,Slowenia,79,81,96,2,53,75
```
W przypadku atrybutów od 1 do 120 (czyli bez atrybutów lądowania) wartości powinny być max do 100. Wtedy wyniki będą bardziej realne.

## Plik "hills.csv"
- Nazwa
- Kraj
- Punkt K
- Punkt HS
- Punkty za belkę
- Punkty za wiatr przedni
- Maksymalna odległość mniej/więcej
- Startowa odległość
- Optymalna siła wybicia
- Metry za siłe wybicia
- Metry za technike wybicia
- Metry za technike lotu
- Punkty za wiatr tylni będą obliczane automatycznie

Przykład:

```
Wisla,Polska, 120, 134, 7.24, 10.8, 145.5, -117, 88.5, 1.4, 0.48, 0.48
Planica,Slowenia, 200, 240, 8.64, 14.4, 252.5, -157, 82, 1, 0.54, 0.83
```
**Obliczanie odległości**
```Startowa odległosc + (Technika wybicia * Metry za technike wybicia) + (Technika lotu * Metry za technike lotu) + (|Optymalna siła wybicia - siła wybicia| * Metry za siłę wybicia) + (Wiatr, belka i inne czynniki)
Siła wybicia, technika wybicia i technika lotu to Umiejętność + forma + losowość
```

## Plik "competitionRules.csv"
- Wiatr startowy
- Zmiana wiatru (Jak wiatr może się zmienić. Wiatr jest obliczany: Wiatr startowy + (losowanie między -zmiana wiatru a zmiana wiatru np. 0.45 + (losowanie między -0.20 a 0.20));
- Fałszywość wiatru (Jest aby dodać realizmu. Wiatr przy skoku jest bez zmian, ale przy podawaniu wyników i podliczaniu punktów będzie inny. Np. jeżeli fałszywośc wiatru = 0.10. Wiatr w wynikach = Wiatr + (losowanie między -0.10 a 0.10. Można wyłączyć wpisując 0);
- Rekompensata za belkę (0 = nie, 1 = tak)
- Rekompensata za wiatr (0 = nie, 1 = tak)
- Noty sędziowskie (0 = nie, 1 = tak)

Przykład:
```
0.80, 0.25, 0.10, 1, 1, 1
```

## Plik "competitionConfig.csv"
Plik zawiera tzw. konfiguracje konkursu (czyli ile skoczków skacze w jakiej serii.) Zapisujemy tam dwie rzeczy:
- Nazwa konfiguracji
- Informacje o rundach oddzielone przecinkiem (50, 30 aby w drugiej serii skakało 30 skoczków)

Przykład:
```
World cup, 50, 30
Flying Championship, 40, 30, 30, 30
Mini konkurs, 15, 10, 5, 3
```
(Liczba rund zależy od liczb wpisanych po przecinku po nazwie. Na końcu nie stawiamy przecinka.)


## Zapisywanie wyników do pliku
Wyniki zawod�w są zapisywane w folderze results/competitions. W folderze csv są wyniki oddzielane przecinkami, a w folderze text wszystko jest "ładniej".
Przy konkursie na skoczni o takiej samej nazwie, punkcie K i HS plik z wynikami jest nadpisywany.

Dla pojedynczych skok�w wyniki s� zapisywane w folderze results/single-jumps (format r�wnie� csv i txt)


## System konkurs�w
- Aby pokaza�/schowa� list� startow�, w�i�nij 's' podczas konkursu.
- Aby zmieni� belk� w czasie konkursu, w�i�nij 'b'.