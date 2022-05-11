TEXCC=pdflatex
BIBCC=bibtex
TEXFLAGS=-shell-escape -synctex=1 -interaction=nonstopmode
TEXFILE=$(shell basename --suffix=.tex $$(ls -1 *.tex))

all:
	$(TEXCC) $(TEXFLAGS) $(TEXFILE).tex
	$(BIBCC) $(TEXFILE).aux
	$(TEXCC) $(TEXFLAGS) $(TEXFILE).tex
	$(TEXCC) $(TEXFLAGS) $(TEXFILE).tex # run twice to update ToC/BibTeX

clean:
	rm -f *.log *.toc *.synctex.gz *.aux *.pyg
	rm -f *.out *.bbl *.blg *.lof *.lot
	rm -f *.pdf *Notes.bib
	rm -rf ./_minted*
