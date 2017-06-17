#!/usr/bin/env python
# coding: utf-8

import sys
import subprocess
import time
import os
import os.path


print("...Midiendo tiempos...")

size = 10000
max =  20500

while size <= max:
    print("\n\nTamaño:" +str(size))
    os.system("./pmvREDUCTION %d" % (size))
    size += 500
