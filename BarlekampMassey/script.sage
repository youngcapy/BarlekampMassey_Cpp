#!/usr/bin/env sage

import sys



p = conway_polynomial(sys.argv[1], sys.argv[2]) # Например, для GF(3) и n = 1

with open("conway_poly.txt", "w") as file:
    file.write(str(p))
