from codecs import encode as enc

def convertHex( s):
    r = 0
    for c in s[:12]:
        r *= 2
        if c == "o": r += 1
    return r//16, (r%16)*16

outEncoded = lambda f, s: f.write(enc( s, "utf8")) 

f1 = open("./font/Nixedsys_12x20.src", "rt", encoding="utf8")
f2 = open("./hardware/Nixedsys_1251.h", "wb")
outEncoded( f2, "const uint8_t Nixedsys_12x20[] PROGMEM = {\n")

count = 0
while True:
    s = f1.readline().strip()
    if len(s) == 0: break
    if s.startswith("#"):
        print("Processing: [{:s}]".format(s[2:]))
        continue
    lb, rb, = convertHex( s)
    print("{:04d} {:s} # 0x{:02x}, 0x{:02x}".format( count, s, lb, rb))
    outEncoded( f2,  "0x{:02x},".format(lb))
    outEncoded( f2,  "0x{:02x},".format(rb))
    count += 2
    if count % 20 == 0: outEncoded( f2, "\n")
if count % 20 == 0: f2.seek(-2,2) 
else: f2.seek(-1,2) 
outEncoded( f2, "};\n")
f1.close()
f2.close()
