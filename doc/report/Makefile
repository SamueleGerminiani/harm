# Build the HARM v4 report: make (harm_v4.pdf), make clean.
harm_v4.pdf: harm_v4.tex refs.bib $(wildcard sections/*.tex)
	latexmk -pdf -interaction=nonstopmode -halt-on-error harm_v4.tex

clean:
	latexmk -C harm_v4.tex

.PHONY: clean
