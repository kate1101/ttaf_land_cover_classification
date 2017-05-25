Specifikáció

A feladat a félév során LiDAR alapú felszín-osztályozó algoritmus implementálása 
A.S. Antonarakis , K.S. Richards , J. Brasington : Object-based land cover classification using airborne LiDAR cikke alapján.
Az algoritmus LiDAR-os magassági- és intenzitási értékek,
valamint a visszaverődés sorszáma alapján 8 felületi modellt határoz meg,
majd 9 felülettípust különböztet a számított értékek küszöbölésésvel. 

Felületi modellek (5 m2-es cellákba eső ponthalmazokra)
•	lombkorona felületi modell(CSM): Maximum magassági érték
•	terepmodell(TM): Minimum magassági érték
•	növényzeti magasság modell(VHM): CSM-TM
•	intenzitás(IM): LiDAR-os adatokból kinyert intenzitásértékek átlaga 
•	intenzitáskülönbség(IDM): Az először visszaverődő pontok maximális intenzitásának és az utolsó visszaverődő pontok minimális intenzitásának különbsége
•	ferdeségi modell(SkM): Statisztikai mérőszám a magassági értékek eloszlásának ferdeségéről
•	íveltségi modell(KrM):  Statisztikai mérőszám a magassági értékek eloszlásának csúcsosságáról
•	százalékos lombkorona modell(PCM): a lombkoronáról visszaverődő pontok aránya

Felszíntípusok
•	víz
•	kavics
•	földfelszín
•	alacsony növényzet
•	fiatal (1-3 éves) ültetett erdő
•	átlagos korú(3-8 éves) ültetett erdő
•	öreg (8-12 éves) ültetett erdő
•	fiatal természetes erdő
•	öreg természetes erdő

Tesztadatok
•	Az eredeti munkában 3 manuálisan osztályozott adathalmazra végeztek összehasonlítást
•	Holland területekről pontfelhős és raszteres adatok nyilvánosan elérhetőek, melyeken tesztelni lehet az algoritmust  (https://www.pdok.nl/nl/ahn3-downloads)

Osztályozás
•	2 algoritmus alapján, a második finomítása az eredeti módszernek
•	Először magasság alapján csoportosítja a területeket(víz, sík/alacsony növényzetű, erdős), majd a további altípusok szerint
•	Lehetnek azonosítatlan területek is
•	Ezt követően színkódolt megjelenítés

Implementáció
•	Algoritmusok implementálása (Felületi jellemzők és osztályozás): C++-ban
•	LidDAR pontfelhők beolvasása: LibLAS-sal
•	Osztályozás eredményéből számított színkódolt térképek megjelenítése: OpenCV-vel

Megvalósítás ütemezése
•	03.14. Cikk feldolgozása
•	03.21. Specifikáció elkészítése
•	03.28. LiDAR .LAS/.LAZ formátumú adattípus megismerése, beolvasása, megjelenítése
•	04.04. Felületi jellemzők számítása
•	04.11. Osztályozás
•	04.18. -
•	04.25. Eredmények színkódolt megjelenítése
•	05.02. Eredmények összevetése raszteres adatokkal, algoritmusok finomítása
•	05.09. Tesztelés, hibajavítása, dokumentálás
•	05.16. Bemutató

