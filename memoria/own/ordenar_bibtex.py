#!/usr/bin/env python
# -*- coding: utf-8 -*-

import re

f = open("bibliografia.bib", "r")

bib_entries = {}

current_entry = ""
current_entry_body = ""

for l in f.readlines():
#    l = l.rstrip()
    
    r = re.search(r"@.*?{(.*?),", l)
    if r:
        bib_entries[current_entry] = current_entry_body
        current_entry = r.groups(1)[0]
        current_entry_body = "" 

    current_entry_body += l

f.close()

f = open ("bibliografia_sorted.bib", "w")
for k in sorted(bib_entries.keys()):
    f.write(bib_entries[k])

f.close()
