### Decyzje projektowe 
## entry
- entry zawiera typ int, a nie typ unsigned int (tak było w instrukcji)
- count w klasie entry musi mieć wartość conajmniej 1, gdy jest 0, to nie ma poco tego trzymać
- musimy mieć domyślny konstruktor, inaczej nie moglibyśmy trzymać jej w wektorze
## word_counter
- potrzebujemy domyślengo konstruktora, bo mozemy chcieć zadeklarować licznik przed jego uzyciem
- po utworzeniu licznika przy uzyciu domyślnego kontruktora jego stan to pusty vector ??? 
    - do sprawdzania stanu słuzy funkcja isEmpty
- nie zwracamy nigdy nie const-referencji na entry, dlatego zeby uzytkownik nie podmienił nam tego na inny obiekt - wtedy moglibyśmy stracić porządek w liście

- entryList nie jest posortowana bo
    - język polski ma 150 - 200 tys róznych słów, z czego zwykle uzywanych słów jest duzo duzo mniej. Przeciętna ksiąka ma koło 50tys słów, z czgo oczywiście duzo sie powtarza. Wynika z tego ze samych róznych kluczy nie ma tak duzo, a wiekszosc czasu bedziemy wstawiac elementy, dlatego implementacja roznych struktór/algorytów jak wyszukiwanie binarne czy drzewo raczej nie ma sensu, ale to tez moze zalezeć od konkretnego zastosowania
### Funkcjonalność licznika:
- dodanie słowa 
- dodanie słów ze strumienia
- wyczyszczenie licznika
- zapis zawartości licznika do pliku
- odczyt zawartoścli licznika z pliku
- iterator przechodzący przez słowa alfabetycznie - lex_iterator
    - lex_begin()
    - lex_end()
- iterator przechodzący przez słowa wg częstotliwości - freq_iterator
    - freq_begin()
    - freq_end()
- operatory indeksowania []
- += operator dodający stan innego licznka

### TODO / Pytania
- czy porównywanie stringów przy uzyciu > lub < jest ok ?? Niby wycofane w cpp 20
    - zastapione przez std::lexicographical_compare()

- czy addWord nie wykrzaczy tak jak BST ??
    - dlatego tworzymy i usuwamy obiekty entry tylko w obrębie word_countera
        - obiekt dynamiczny 

- dokończyć operatory >> i << dla word_counter
- dodać odczyc/zapis do pliku