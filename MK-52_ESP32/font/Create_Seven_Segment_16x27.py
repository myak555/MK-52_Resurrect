from codecs import encode as enc

def convertHex( s):
    r = 0
    for c in s:
        r *= 2
        if c == "o": r += 1
    return r//256, r%256

outEncoded = lambda f, s: f.write(enc( s, "utf8")) 

f1 = open("./font/Seven_segment_16x27.src", "rt", encoding="utf8")
f2 = open("./hardware/Seven_Segment.h", "wb")
outEncoded( f2, "const uint8_t Seven_segment_16x27px[] PROGMEM = {\n")

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
