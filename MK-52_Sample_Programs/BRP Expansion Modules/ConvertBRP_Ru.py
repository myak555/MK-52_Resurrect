import sys

class BRP:
    def __init__(self, filename):
        self.codelines0 = ["0", "1", "2", "3", "4", "5", "6", "7",
                    "8", "9", ".", "/-/", "ВП", "Cx", "Ввод", "F Bx"]
        self.codelines1 = ["+", "-", "*", "/", "X<->Y", "F 10^x", "F Exp", "F Lg",
                    "F Ln", "F Sin-1", "F Cos-1", "F Tg-1", "F Sin", "F Cos", "F Tg", "Код не понят"]
        self.codelines2 = ["F pi", "F SQRT", "F X^2", "F 1/X", "F X^Y", "F Rotate", "K <-o'", "Код не понят",
                    "Код не понят", "Код не понят", "K ->o'\"", "Код не понят", "Код не понят", "Код не понят", "Код не понят", "Код не понят"]
        self.codelines3 = ["K <-o'\"", "K |X|", "K ЗН", "K ->o'", "K [X]", "K \{X\}", "K max", "K и",
                    "K или", "К иск.или", "К не", "К Сч", "Код не понят", "Код не понят", "Код не понят", "Код не понят"]
        self.codelines5 = ["С/П", "БП", "В/О", "ПП",
                    "НОП", "Код не понят", "Код не понят", "F X!=0",
                    "F L2", "F X>=0", "F L3", "F L1",
                    "F X<0", "F L0", "F X=0", "Код не понят"]
        self.codelinesK = ["K X!=0 ","K БП", "K X>0 ", "K ПП",
                    "K П", "K X<0 ", "K ИП", "K X=0 "]                
        self.codelinesR = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"]
        with open(filename, mode='rb') as file:
            self.Bytes = file.read()
        return

    def extractProgram( self, address):
        nread = (address % 100)
        start = ((address // 100) % 10000) >> 1
        print( "Программа по адресу: {:d},  шагов: {:d}".format(start, nread))
        self.addressExpected = False
        self.lines = []
        for i in range(nread):
            addr = self.convertAddress( start+i)
            s = "{:02d}: {:s}".format(i, self.convertCodeMK52(self.Bytes[addr]))
            self.lines += [s]
        return self.lines  

    def convertCodeMK52( self, code):
        upper = (code>>4) & 0x0F
        lower = code & 0x0F
        if self.addressExpected:
            self.addressExpected = False
            addr = self.codelinesR[upper] + self.codelinesR[lower]
            return addr
        self.addressExpected = code in [0x51, 0x53, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E]
        if upper == 0xF: return "Код не понят"
        if upper == 0x0: return self.codelines0[lower]
        if upper == 0x1: return self.codelines1[lower]
        if upper == 0x2: return self.codelines2[lower]
        if upper == 0x3: return self.codelines3[lower]
        if upper == 0x4: return "П" + self.codelinesR[lower]
        if upper == 0x5: return self.codelines5[lower]
        if upper == 0x6: return "ИП" + self.codelinesR[lower]
        return self.codelinesK[upper-7] + self.codelinesR[lower]

    def convertAddress( self, address):
        topSequence = address // 7
        bottomSequence = address % 7
        newAddress = topSequence * 7 + bottomSequence - 1
        if bottomSequence == 0: newAddress += 7
        return newAddress

def Main(args):
    if len( args) < 3:
        print( )
        print( "MK-52 Resurrect!")
        print( "Дизассемблер v. 1.0")
        print( "Использование:")
        print( "   python ConvertBRP_Ru.py <имя BIN> <адрес программы в БРП> [выходной файл txt]")
        print( )
        return
    binname = args[1]
    if binname[-4:].upper() != ".BIN": binname += ".BIN"
    print( )
    print( "Извлекаю:")
    print( "   {:s}".format( binname))
    try:
        brp = BRP( binname)
    except:
        print( "   Файл не найден!")
        print( )
        return
    try:
        address = int( args[2])
    except:
        print( "   Адрес {:s} неправильный".format(args[2]))
        print( )
        return
    pLines = brp.extractProgram( address)
    if len( args) == 3:
        for l in pLines: print( l)
        print( )
        return
    filename = args[3]
    if filename[-5:].upper() != ".TXT": filename += ".txt"
    print( "Пишу в файл:")
    print( "   {:s}".format( filename))
    try:
        f1 = open( filename, "w", encoding="utf-8")
        f1.write( u"#\n")
        f1.write( u"# {:s} из {:s} по адресу {:d}\n".format(filename, binname, address))
        f1.write( u"#\n")
        for l in pLines:
            f1.write( l)
            f1.write( u"\n")
        f1.close()
    except:
        print( "   Ошибка записи")
    print( )
    return

Main( sys.argv)
