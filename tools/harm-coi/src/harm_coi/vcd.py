"""The signal names HARM sees in a VCD: relative to the scope, '::' between sub-scopes (D-013)."""
from pathlib import Path


def visible_names(path, scope, recursion):
    """Names of the variables under `scope` (a '::' path) at most `recursion` sub-scopes deep."""
    want = scope.split("::") if scope else []
    stack, names, found = [], set(), False
    with Path(path).open() as f:
        for line in f:
            tok = line.split()
            if not tok:
                continue
            if tok[0] == "$scope":
                stack.append(tok[2])
                found = found or stack == want
            elif tok[0] == "$upscope":
                stack.pop()
            elif tok[0] == "$var" and stack[:len(want)] == want:
                rel = stack[len(want):]
                if len(rel) <= recursion:
                    names.add("::".join(rel + [tok[4]]))
            elif tok[0] == "$enddefinitions":
                break
    if not found:
        raise ValueError(f"scope '{scope}' not found in {path}")
    return names
