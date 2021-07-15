## ConvertBRP

ConvertBRP is a simple disassembler for BRP binaries.

If you have Python installed, simply run:

```
python ConvertBRP.py <input BIN> <address code> [output MK52]
```

If Python is not installed, download the dist folder content and run 

```
ConvertBRP.exe <input BIN> <address code> [output MK52]
```


ConvertBRP - простой дизассемблер для дампов памяти БРП.

Если установлен Python, запуск:

```
python ConvertBRP.py <input BIN> <address code> [output MK52]
```

Если не установлен Python, надо загрузить содержимое директории dist. Запуск:

```
ConvertBRP.exe <input BIN> <address code> [output MK52]
```

## ConvertBRP_Ru

ConvertBRP - дизассемблер для дампов памяти БРП с выдачей в "классическом формате".

Должен быть установлен Python, запуск:

```
python ConvertBRP_Ru.py <Входной BIN> <адрес в ROM> [Выходной файл txt]
```

Например, задача 2.4а из БРП-2 для вычисления расстояния и курса вдоль Большого круга: "положение переключателя 2", значит, нужен будет файл BRP2-2.BIN. Адрес программы для загрузки - там же в руководстве: 4252098.

* Из коммандной строки, набираем:

```
python ConvertBRP_Ru.py BRP2-2.BIN 4252098
```

* Читаем программу на экране

* Если хочется записать программу в файл, то команда, например:

```
python ConvertBRP_Ru.py BRP2-2.BIN 4252098 БРП2_Программа_2_4а
```

Вместо экрана, программа запишется в файл, например, БРП2_Программа_2_4а.txt

* Далее читаем программу в любимом редакторе текстов.

## BRP Dumps

BRP ROM Dumps are courtesy Sergey Frolov. See readme.md for details. Translation from Russian is available in [Wiki] (https://github.com/myak555/MK-52_Resurrect/wiki/12.-BRP-ROM-Instructions)

* BRP2-1.BIN - БРП2 "Астро", положение переключателя "1"
* BRP2-2.BIN - БРП2 "Астро", положение переключателя "2"
* BRP3-1.BIN - БРП3 (математика), положение переключателя "1"
* BRP3-2.BIN - БРП3 (математика), положение переключателя "2"
* BRP4-0006-P1-1.BIN - неизвестный БРП, предположительно "Гео", положение переключателя "1"
* BRP4-0006-P1-2.BIN - неизвестный БРП, предположительно "Гео", положение переключателя "2"
* BRP4-1.BIN - БРП4 (бытовые программы и игрушки), положение переключателя "1"
* BRP4-2.BIN - БРП4 (бытовые программы и игрушки), положение переключателя "2"
