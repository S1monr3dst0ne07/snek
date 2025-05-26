
import sys
from dataclasses import dataclass
from dataclasses import field
import typing

import lex        
import tree
import manifold



def main():

    if len(sys.argv) < 2:
        print("no file provided\n")
        sys.exit(1)
    
    stream = lex.tokenize(sys.argv[1])
    structure = manifold.structurize(stream)
    print(structure)
    #tree.parse_scope(stream)



main()
