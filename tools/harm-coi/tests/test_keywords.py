"""H23 (D-037): harm-coi writes signals named after HARM keywords escaped, with HARM's own list."""

import re
from pathlib import Path

from harm_coi.predicates import KEYWORDS, escaped

HEADER = Path(__file__).resolve().parents[3] / "src" / "utils" / "include" / "harmKeywords.hh"


def test_same_list_as_harm():
    body = HEADER.read_text().split("names = {", 1)[1].split("}", 1)[0]
    assert set(re.findall(r'"([^"]+)"', body)) == KEYWORDS


def test_escaped():
    assert escaped("W") == "\\W " and escaped("next") == "\\next " and escaped("data") == "data"
    assert escaped("u::W") == "u::W"
