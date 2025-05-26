
from dataclasses import dataclass
from dataclasses import field
from typing import Any

@dataclass
class streamer:
    iterator : list[Any] = field(default_factory = lambda: [])


    def add(self, token):
        self.iterator.append(token)
    
    def peek(self):
        return self.iterator[0]

    def pop(self):
        return self.iterator.pop(0)

    def __len__(self):
        return len(self.iterator)

    def __iter__(self):
        return iter(self.iterator)

    def __str__(self):
        return "\n".join(map(str, self.iterator))

