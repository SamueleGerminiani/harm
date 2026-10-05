#!/usr/bin/env python3
"""Deterministic 2-valued trace for the Verilator replay of HARM's SVA output (H1 validation).
A mod-10 counter enabled by 'en', a 3-state FSM advanced by 'en', and 'data' = {cnt, ~cnt}."""
import random
from pathlib import Path

r = random.Random(7)
cnt, st, rows = 0, 0, []
for _ in range(300):
    en = 1 if r.random() < 0.7 else 0
    rows.append(f"{en},{cnt:04b},{st:02b},{cnt:04b}{(~cnt) & 0xF:04b}")
    if en:
        cnt = 0 if cnt == 9 else cnt + 1
        st = (st + 1) % 3
out = Path(__file__).with_name("temporal2v.csv")
out.write_text("logic en, logic [3:0] cnt, logic [1:0] st, logic [7:0] data\n" + "\n".join(rows) + "\n")
