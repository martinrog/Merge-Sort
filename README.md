# Merge-Sort

## Werking van het algoritme

Het algoritme is een iteratieve versie van merge sort.

In de eerste iteratie wordt de array beschouwd als blokken van grootte 1 ( altijd gesorteerd dus). Vervolgens worden telkens twee aangrenzende blokken samengevoegd tot een groter gesorteerd blok.

Hiervoor worden drie indexen gebruikt:
- left: begin van het linkerblok
- mid: begin van het rechterblok
- right: einde van het rechterblok

De blokken worden geïnterpreteerd als:
- linkerblok: left, mid
- rechterblok: mid, right

Tijdens het mergen worden de elementen uit beide blokken vergeleken en in een tijdelijke array geplaatst. Zodra één van de blokken leeg is, wordt de rest van het andere blok direct toegevoegd.

Na elke iteratie wordt de blokgrootte 'unit' verdubbeld (1 → 2 → 4 → 8 → ...), totdat de volledige array gesorteerd is.


## Complexiteit

- **Tijdscomplexiteit:** O(n log n)  
  De array wordt in log(n) iteraties verwerkt en in elke iteratie worden alle elementen doorlopen.

- **Ruimtecomplexiteit:** O(n)  
  Tijdens het mergen wordt tijdelijke opslag gebruikt voor de tussenresultaten.