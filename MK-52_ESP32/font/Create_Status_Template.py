import numpy as np
from codecs import encode as enc
import cv2

outEncoded = lambda f, s: f.write(enc( s, "utf8")) 

grayImage = cv2.cvtColor(cv2.imread( "./font/Status_Template.png").astype(np.uint8), \
                                    cv2.COLOR_BGR2GRAY)

print( grayImage.shape)

f1 = open("./hardware/Status_Template.h", "wb")
outEncoded( f1, "const uint8_t StatusTemplate_320x20px[] PROGMEM = {\n")

count = 0
for i in range(20):
    for j in range(0,320,8):
        r = 0
        for k in range(8):
            r *= 2
            if( grayImage[i,j+k] > 100): r += 1
        outEncoded( f1, "0x{:02x},".format(r))
        count += 1
        if count % 20 == 0:
            outEncoded( f1, "\n")
if count % 20 == 0: f1.seek(-2,2) 
else: f1.seek(-1,2) 
outEncoded( f1, "};\n")
f1.close()
