TEXCC=pdflatex
TEXFLAGS=-shell-escape -synctex=1 -interaction=nonstopmode


all:
	for texfiles in `ls -1 *.tex`;do $(TEXCC) $(TEXFLAGS) $$texfiles;done

clean:
	rm -f *.log *.toc *.synctex.gz *.aux
	rm -f *.out *.bbl *.blg *.lof
	rm -f *.pdf
	rm -rf ./_minted*
