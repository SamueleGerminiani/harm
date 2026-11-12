import json, sys, collections, re
r = json.load(open(sys.argv[1] + "/results.json"))
bad = [x for x in r if x["harm"] != x["sv"]]
def kind(x):
    if x["harm"] is None:
        return "HARM error"
    if "br_harm" in x and x["br_harm"] == x["sv"]:
        return "precedence"
    return "value"
by = collections.Counter((x["cat"].split()[0], kind(x)) for x in bad)
for k, v in sorted(by.items()): print(k, v)
print("\n-- precedence (bracketed SV reading agrees, bare does not): operator pairs")
pairs = collections.defaultdict(list)
for x in bad:
    if x["cat"] in ("prec", "prefix") and kind(x) == "precedence":
        print(f"  {x['exp']:<16} HARM prints {x['harm_text']}")
print("\n-- HARM errors (messages)")
errs = collections.Counter(re.sub(r"got:.*|'.*'", "", x["harm_text"])[:90] for x in bad if x["harm"] is None)
for k, v in errs.most_common(): print(f"  {v:3}  {k}")
