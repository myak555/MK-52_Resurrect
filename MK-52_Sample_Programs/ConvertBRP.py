import sys

class BRP:
    def __init__(self, filename):
        self.codelines0 = ["0", "1", "2", "3", "4", "5", "6", "7",
                    "8", "9", ".", "/-/", "EE", "Cx", "Enter", "Bx"]
        self.codelines1 = ["+", "-", "*", "/", "X<->Y", "10^x", "EXP", "LG",
                    "LN", "ArcSIN", "ArcCOS", "ArcTG", "SIN", "COS", "TG", "Undefined"]
        self.codelines2 = ["pi", "SQRT", "X^2", "1/X", "X^Y", "Rotate", "<-DM", "Undefined",
                    "Undefined", "Undefined", "->DMS", "Undefined", "Undefined", "Undefined", "Undefined", "Undefined"]
        self.codelines3 = ["<-DMS", "|X|", "SIGN", "->DM", "[X]", "\{X\}", "MAX", "AND",
                    "OR", "XOR", "NOT", "RAND", "Undefined", "Undefined", "Undefined", "Undefined"]
        self.codelines5 = ["STOP", "GOTO", "RETURN", "GOSUB",
                    "NOP", "Undefined", "Undefined", "IFNOT X!=0 GOTO",
                    "WHILE L2>0 GOTO", "IFNOT X>=0 GOTO", "WHILE L3>0 GOTO", "WHILE L1>0 GOTO",
                    "IFNOT X<0 GOTO", "WHILE L0>0 GOTO", "IFNOT X=0 GOTO", "Undefined"]
        self.codelinesK = ["K X!=0 GOTO ","GOTO ", "K X>0 GOTO ", "K GOSUB ",
                    "K X->M ", "K X<0 GOTO ", "K M->X ", "K X=0 GOTO "]                
        self.codelinesR = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"]
        with open(filename, mode='rb') as file:
            self.Bytes = file.read()
        return

    def extractProgram( self, address):
        nread = (address % 100) - 1
        start = ((address // 100) % 10000) >> 1
        print( "Program at: {:d}, {:d} steps".format(start, nread))
        self.addressExpected = False
        self.lines = []
        for i in range(nread):
            addr = self.convertAddress( start+i)
            s = "P{:04d}: {:s}".format(i, self.convertCodeMK52(self.Bytes[addr]))
            self.lines += [s]
        return self.lines  

    def convertCodeMK52( self, code):
        upper = (code>>4) & 0x0F
        lower = code & 0x0F
        if self.addressExpected:
            self.addressExpected = False
            addr = self.codelinesR[upper] + self.codelinesR[lower]
            self.lines[-1] += " 00" + addr
            return "#" + addr
        self.addressExpected = code in [0x51, 0x53, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E]
        if upper == 0xF: return "Undefined"
        if upper == 0x0: return self.codelines0[lower]
        if upper == 0x1: return self.codelines1[lower]
        if upper == 0x2: return self.codelines2[lower]
        if upper == 0x3: return self.codelines3[lower]
        if upper == 0x4: return "X->M " + self.codelinesR[lower]
        if upper == 0x5: return self.codelines5[lower]
        if upper == 0x6: return "M->X " + self.codelinesR[lower]
        return self.codelinesK[upper-7] + self.codelinesRself[lower]

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
        print( "BRP Disassembler v. 1.0")
        print( "Usage:")
        print( "   python ConvertBRP.py <input BIN> <address code> [output MK52]")
        print( )
        return
    filename = args[1]
    if filename[-4:].upper() != ".BIN": filename += ".BIN"
    print( )
    print( "Extracting from:")
    print( "   {:s}".format( filename))
    try:
        brp = BRP( filename)
    except:
        print( "   File not found!")
        print( )
        return
    try:
        address = int( args[2])
    except:
        print( "   Address {:s} not recognized".format(args[2]))
        print( )
        return
    pLines = brp.extractProgram( address)
    if len( args) == 3:
        for l in pLines: print( l)
        print( )
        return
    filename = args[3]
    if filename[-5:].upper() != ".MK52": filename += ".MK52"
    print( "Writing to:")
    print( "   {:s}".format( filename))
    try:
        f1 = open( filename, "wt")
        f1.write( "#\n")
        f1.write( "# MK-52 program\n")
        f1.write( "#\n")
        f1.write( "PC=0000\n")
        for l in pLines: f1.write( l + "\n")
        f1.close()
    except:
        print( "   Unable to write")
    print( )
    return

Main( sys.argv)
