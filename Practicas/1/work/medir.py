#!/usr/bin/env python
# coding: utf-8

import sys
import subprocess
import time
import os
import os.path

if len(sys.argv) != 3:
    print("[ERROR] formato:\n <nombre_del_ejecutable><salida>")
    sys.exit(0)

file = sys.argv[1]
out = "out/"+sys.argv[2]


print("...Midiendo tiempos...")

size = 16384
max = 67108864

while size <= max:
   os.system("./"+file+" %d >> %s" % (size,out))
   print("procesado: "+str(size)+" of "+str(max)+"\n")
   size *= 2
