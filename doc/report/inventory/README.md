# Inventory for the H14 documentation checks

`check_coverage.py` compares HARM's current sources with these lists, taken once from the `v3` tag, so that the checks also run in a checkout without tags (e.g. the Docker image).

| File | What | Taken from `v3` with |
|---|---|---|
| `v3_options.txt` | command-line option names | `git show v3:src/commandLineParser/src/commandLineParser.cc`, every `( "name"` that opens a line |
| `v3_xml_names.txt` | XML element and attribute names the configuration reader asks for | `git show v3:…/manualDefinition/ManualDefinition.cc`, the names passed to `getAttributeValue` and `getNodesFromName` |
| `v3_metric_variables.txt` | metric variables | `git show v3:src/miner/utils/src/Metric.cc`, every `make_tuple("name"` |
| `default_output_decisions.txt` | decisions that change HARM's output with a v3 configuration and no new option | written by hand from `doc/plan/DECISIONS.md` |
