TEXCC=pdflatex
TEXFLAGS=-shell-escape -synctex=1 -interaction=nonstopmode


all:
	for texfiles in `ls -1 *.tex`;do $(TEXCC) $(TEXFLAGS) $$texfiles;done
	for texfiles in `ls -1 *.tex`;do $(TEXCC) $(TEXFLAGS) $$texfiles;done # run twice for TOC/Index

clean:
	rm -f *.log *.toc *.synctex.gz *.aux *.pyg
	rm -f *.out *.bbl *.blg *.lof *.lot
	rm -f *.pdf
	rm -rf ./_minted*
