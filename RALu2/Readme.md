##RAL zadanie

##### Úloha 2: Aritmetika  modulo 2n, t.j. určenie polynómu rozšírenia poľa, potom súčet, súčin, inverzia

###### Podporované operácie:

zátvorky ()
Dva operandy
	klasické aritmeticke **+ - * /**
	exponent **^ e**

Jeden operand
inverzia 	**i** **'**
trace	**t**
square   	**s**

Pozn. pri umocnovaní (^) sa zadáva obyčajné číslo v decimálnom tvare

###### Zadávanie polynómu

Kalkulačka pracuje nad knižnicou NTL a preto všetky "čísla" tedy polynómy sa zadávajú ako
ax^0 bx^1 cx^2 dx^3... [a b c d],
takže napríklad sčítanie polynómov (v F2):

`x^2 + x `  sa zapíše ako `[0 0 1] + [0 1]`

###### Načítatelný príkaz kalkulačky

Kalkulačka by mala byť schopná načítať hocijakú kombináciu viacerých operácií z jedného riadku.

Ukážme si to na príklade:

`[0 0 1]e2 + [0 0 1]^2+ [1 1 1]*[3]s*([1 0]-[0 1 1])i^4`
Môžeme si všimnúť že:
	pre umocňovanie môžeme používať znak ktorý nám príde vhodnejší.
	pre operácie s jedným operandom sa vyhodnocujú okamžite a teda už keď  robíme `[1 1 1]*[3]s` tak sa v skutočnosti robí `[1 1 1]*[1]`
	okolo zátvoriek je potrebné vždy písať operátor (roznásobenie nie je automatické)


##### Inštalácia
Je potrebné stiahnuť, skompilovať a nalinkovať C++ knižnicu NTL. (podľa návodu v 'instalacia ntl.pdf' v korenovom adresari)
