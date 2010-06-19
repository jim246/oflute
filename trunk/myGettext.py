#!/usr/bin/python
# -*- coding: utf-8 -*-

import re
import sys
import json

argumentos = sys.argv[1:]

if len(argumentos) == 0:
    print "Se necesita algún argumento."
    sys.exit()


valores = []
for rutaFichero in argumentos:
    print "Parseando '" + rutaFichero +  "'..."
    try:
        fichero = open(rutaFichero, 'r')
        for linea in fichero.readlines():
            linea.rstrip()
            cadenas = re.findall("_\(\"(.*?)\"\)",linea)
            if len(cadenas) != 0:
                for c in cadenas:
                    valores.append("\"%s\": \"%s\"" % (c, c) )
                    print c

        fichero.close()
        
    except IOError:
        print "Error al leer el fichero '" + rutaFichero + "'"

salida = open("trans.es", 'w')
salida.write("{\n")
salida.write(",\n".join(valores))
salida.write("\n}")
salida.close()
