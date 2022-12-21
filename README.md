# Install LaTeX

## Contents
- [ArchLinux](#archlinux)
	+ [TeXLive](#texlive)
	+ [TeXStudio](#texstudio)

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