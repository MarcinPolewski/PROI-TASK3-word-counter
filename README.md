# Decyzje projektowe 
### entry
- entry zawiera typ int, a nie typ unsigned int (tak było w instrukcji)
- count w klasie entry musi mieć wartość co najmniej 1, gdy jest 0, to nie ma po co tego trzymać
- musimy mieć domyślny konstruktor, inaczej nie moglibyśmy trzymać jej w wektorze
### word_counter
- potrzebujemy domyślnego konstruktora, bo możemy chcieć zadeklarować licznik przed jego użyciem
- po utworzeniu licznika, przy użyciu domyślnego konstruktora, jego stan to pusty vector ??? 
    - do sprawdzania stanu służy funkcja isEmpty()
- zwracamy tylko const-referencję na entry, dlatego żeby użytkownik nie podmienił nam tego na inny obiekt - wtedy moglibyśmy stracić porządek w liście
    - wyjątkiem jest operator [] używany jako lvalue. Zaimplementowałem go dlatego, że tak było w poleceniu, ale jego użycie stwarza ryzyko, że użytkownik zrobi nam psikusa, choćby wstawiając inne słowo, co zepsuje nam porządek listy, a my nawet tego nie odnotujemy. Naturalnie zaburzy to działanie wstawiania, szukania kolejnych elementów
- funkcje highest/lowestCount działają wewnątrz na indeksach, a nie referencjach, gdyż pojawiał się problem z modyfikatorami const
- entryList jest posortowany alfabetycznie
    - wstawianie do listy, szukanie elementu są w miarę proste (wyszukiwanie binarne)
    - łatwe działanie iteratora alfanumerycznego
- Funkcje wyszukiwania działają na iteratorach, nie na referencjach, bo wtedy łatwiej sygnalizować nieznalezienie elementu (zwracamy wtedy .end())
- getEntry nie wykorzystuje getEntryNonConst dlatego, że występowały problemy z konwersją z iteratora na const iterator (teoretycznie powinno to działać, ale funkcja ma modyfikator const, przez to użycie funkcji nie const nie działa)
- przeciążenie operatora ( entry &operator[](std::string const &word) ) gdy zostanie wyszukany element, którego nie ma, wyrzuci błąd, ponieważ nie jesteśmy mu w stanie podać liczności słowa, na które nie natrafiliśmy w ogóle. Inną opcją byłoby zwrócenie referencji na obiekt tego słowa o liczności zero, ale klasa entry na to nie pozwala i nie wpłynęłoby to jakoś drastycznie na działanie klasy.
- freq_iterator idzie po elementach patrząc najpierw na kolejność, potem na porządek alfabetyczny

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
- odczyt zawartości licznika z pliku
- zwrócenie najbardziej/najmniej popularnej wartości
- policzenie całkowitej ilości słów
- sprawdzenie czy licznik jest pusty
- iterator przechodzący przez słowa alfabetycznie - lex_iterator
    - lex_begin()
    - lex_end()
- iterator przechodzący przez słowa wg częstotliwości - freq_iterator
    - freq_begin()
    - freq_end()
- operatory indeksowania []
- += operator dodający stan innego licznika

# Time
- build moby dick 133ms
- iterated over moby dick by frequency in: 13 ms.
- iterated over moby dick alphabetically in: 0 ms.



# TODO / Pytania
- czy porównywanie stringów przy użyciu > lub < jest ok ?? Niby wycofane w cpp 20
    - zastąpione przez std::lexicographical_compare()
- czy można pozbyć się zmiennej temporary, przy korzystaniu z binary_search i lower_bound, np. czy można napisać specjalną funkcję porównującą
