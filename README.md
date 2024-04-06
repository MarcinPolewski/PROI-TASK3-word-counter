# Decyzje projektowe 
### entry
- entry zawiera typ int, a nie typ unsigned int (tak było w instrukcji)
- count w klasie entry musi mieć wartość conajmniej 1, gdy jest 0, to nie ma po co tego trzymać
- musimy mieć domyślny konstruktor, inaczej nie moglibyśmy trzymać jej w wektorze
### word_counter
- potrzebujemy domyślengo konstruktora, bo możemy chcieć zadeklarować licznik przed jego uzyciem
- po utworzeniu licznika, przy uzyciu domyślnego kontruktora, jego stan to pusty vector ??? 
    - do sprawdzania stanu słuzy funkcja isEmpty()
- zwracamy tylko const-referencji na entry, dlatego zeby uzytkownik nie podmienił nam tego na inny obiekt - wtedy moglibyśmy stracić porządek w liście
    - wyjątkiem jest operator [] uzywany jako lvalue. Zaimplementowałem go dlatego, ze tak było w poleceniu, ale jego uzycie stwarza ryzyko, ze uzytkownik zrobi nam psikusa, chociażby wstawiając inne słowo, co zepsuje nam porządek listy, a my nawet tego nie odnotujemy. Naturalnie zaburzy to dzialanie wstawiania,szukania kolejnych elementow
- funcje highest/lowestCount działają wewnątrz na indeksach,a nie referencjach, gdyz pojawiał się problem z modyfikatorami const
- entyrList jest posortowany alfabetycznie
    - wstawianie do listy, szukanie elementu są wmiare proste(wyszukiwanie binarne)
    - łatwe działanie iteratora alfanumerycznego
- Funckje wyszukiwania działają na iteratorach, nie na referencjach, bo wtedy łatwiej sygnalizować nieznalecienie elementu(zwracamy wtedy .end())
- getEntry nie wykorzystuje getEntryNonConst dlatego ze występowały problemy z konwersją z iteratora na const iterator(teoretycznie powinno to działać, ale funckja ma modyfikator const, przez to uycie funckji nie const nie działa)
- przeciązenie opertatora ( entry &operator[](std::string const &word) ) gdy zostanie wyszukany element, którego nie ma wyrzuci błąd, gdyż nie jesteśmy mu wstanie podać liczności słowa, na które nie natrafiliśmy wgl. Inną opcją byłoby wzrócenie referencji na obiekt tego słowa o liczności zero, ale klasa entry na to nie pozwala i nie wpłyneło by to jakoś drastycznie na działanie klasy.
- freq_iterator idzie po elementach patrząc najpier na kolejność, potem na porządek alfabetyczny

# Funkcjonalność licznika:
- dodanie słowa ze:
    - stringa
    - entry
- dodanie słów ze:
    - strumienia
    - vectora stringów
    - vectora entries
- wyczyszczenie licznika
- zapis zawartości licznika do pliku
- odczyt zawartoścli licznika z pliku
- zwrócenie najbardziej/najmniej popularnej wartości
- policzenie całkowitej ilości słów
- sprawdzenei czy licznik jest pusty
- iterator przechodzący przez słowa alfabetycznie - lex_iterator
    - lex_begin()
    - lex_end()
- iterator przechodzący przez słowa wg częstotliwości - freq_iterator
    - freq_begin()
    - freq_end()
- operatory indeksowania []
- += operator dodający stan innego licznka

# TODO / Pytania
- czy porównywanie stringów przy uzyciu > lub < jest ok ?? Niby wycofane w cpp 20
    - zastapione przez std::lexicographical_compare()
- czy można pozbyć się zmiennej temporary, przy korzsytaniu z binary_search i lower_bound, np. czy można napisać specjalną funkcje porównująca

