
from dataclasses import dataclass
from dataclasses import field

import lex
import river


@dataclass
class line:
    content : river.streamer = field(default_factory = lambda: river.streamer())
    scope_depth : int = 0


def structurize(token_stream):
    line_stream = river.streamer()
    line_buffer = line()

    for token in token_stream:
        match token.kind:
            case 'newline': #end of line
                if len(line_buffer.content):
                    line_stream.add(line_buffer)
                line_buffer = line()
            case 'space':
                line_buffer.scope_depth = token.size // 4
            case _:
                line_buffer.content.add(token)

    return line_stream






