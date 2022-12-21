# Install LaTeX

## Contents
- [ArchLinux](#archlinux)
	+ [TeXLive](#texlive)
	+ [TeXStudio](#texstudio)
	+ [Visual Studio Code](#visual-studio-code)
	+ [Makefile](#makefile)

## ArchLinux

Example install command for ArchLinux, Manjaro, or any other Arch-based GNU/Linux distributions OS.

### TeXLive

To install TeXLive package, you can use command:

```sh
sudo pacman -S texlive-most texlive-bin latex2html latex2rtf dblatex minted biber pdftk
```

It will download approximately 800MB and installation size about 2.5GB.

This should be reproducible in other GNU/Linux distributions like Ubuntu or Fedora.

### TeXStudio

For editor, you can choose TeXStudio and can be installed using command:

```sh
sudo pacman -S texstudio
```

Installation size approximately 500MB (including Qt5 toolkit)

![images](Modul/LaTex/images/texstudio.png?raw=true)

**TIPS:** If you use **minted**, you should use **-shell-escape**.
 
 Go to menu *Options* -> *Configure TexStudio* -> *Commands* to add **-shell-escape** like this:.
 
![images](Modul/LaTex/images/texstudio_shellescape.png?raw=true)
 
### Visual Studio Code

You can also use general code editor like Visual Studio Code to write LaTeX document.

First install VSCodium from this AUR package: https://aur.archlinux.org/packages/vscodium-bin/

![images](Modul/LaTex/images/vscodium.png?raw=true)

Then install **LaTeX-Workshop** extension from *View* -> *Extension*.

### Makefile

You can also use this **Makefile** to build PDF from LaTeX documents

```make
TEXCC=pdflatex
BIBCC=bibtex
TEXFLAGS=-shell-escape -synctex=1 -interaction=nonstopmode
TEXFILE=$(shell basename --suffix=.tex $$(ls -1 *.tex))

# '-' sign mean keep going even if the command fail
all:
	-$(TEXCC) $(TEXFLAGS) $(TEXFILE).tex
	-$(BIBCC) $(TEXFILE).aux
	-$(TEXCC) $(TEXFLAGS) $(TEXFILE).tex
	-$(TEXCC) $(TEXFLAGS) $(TEXFILE).tex # run twice to update ToC/BibTeX

clean:
	rm -f *.out *.bbl *.blg *.lof *.lot *.nav *.vrb
	rm -f *.log *.toc *.synctex.gz  *.pyg *.snm
	rm -f *.aux *Notes.bib
	rm -f *.pdf
	rm -rf ./_minted*
```

Save as Makefile in same directory of any LaTeX documents, then run command:

```sh
make all
```

and to clean up you can run commmand:

```sh
make clean
```
