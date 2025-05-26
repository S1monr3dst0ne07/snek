
from dataclasses import dataclass
from dataclasses import field

@dataclass
class token:
    content : str = ''
    kind : str = ''

@dataclass
class streamer:
    iterator : list[token] = field(default_factory = lambda: [])

    def add(self, token):
        print(token)
        self.iterator.append(token)


def get_kind(c):
    match c:
        case x if x.isdigit(): return 'num'
        case x if x.isalpha(): return 'iden'
        case '"':              return 'quote'
        case '\n':             return 'newline'
        case ' ':              return 'space'
        case _:                return 'sym'

#the kinds of tokens that are forced to emit always
def force_emit(kind):
    return kind in ('sym', 'newline')


def tokenize(path):
    with open(path, "r") as f:
        src = f.read()
        
    stream = streamer() 
    buffer = []
    state = None
    string = False
    for char in src:
        kind = get_kind(char)

        if state == 'quote':
            string = not string

        if not string and state: #ensure coherent state
            if (kind != state or force_emit(state)): #find state transition
                stream.add(token(
                    content = "".join(buffer), 
                    kind = state,
                ))
                buffer = []

        buffer.append(char)
        state = kind

    return streamer
