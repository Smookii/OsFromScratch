# Rapport OS From Scratch

<!-- TOC depthFrom:1 depthTo:6 withLinks:1 updateOnSave:1 orderedList:0 -->

- [Rapport OS From Scratch](#rapport-os-from-scratch)
	- [1. Introduction](#1-introduction)
	- [2. Prérequis](#2-prrequis)
		- [2.1. Machine virtuelle](#21-machine-virtuelle)
		- [2.2. Qemu](#22-qemu)
		- [2.3. Nasm](#23-nasm)
	- [3. Bootloader](#3-bootloader)
	- [4. Crosscompiler](#4-crosscompiler)
		- [4.1 Implémenter le cross-compiler](#41-implmenter-le-cross-compiler)
	- [5. Kernel](#5-kernel)
	- [6. Problèmes rencontrés](#6-problmes-rencontrs)
		- [6.1. Destruction d'une machine virtuelle](#61-destruction-dune-machine-virtuelle)
	- [7. Conclusion](#7-conclusion)

<!-- /TOC -->


## 1. Introduction
Le but du projet est de créer un petit Os tournant sur une machine virtuel QEMU.

Le projet est séparé en plusieurs parties :
* L'implémentation du bootloader
* Un crosscompiler pour pouvoir utilisé le language C
* Le kernel de notre Os


## 2. Prérequis
### 2.1. Machine virtuelle
Les différens collaborateurs du projets ont décidé de travailler sur une machine virtuel linux.

### 2.2. Qemu
Qemu est un logiciel qui permet de créer une machine virtuel permetant de simuler une architecture sur laquelle nous pouvons instancier notre os.

### 2.3. Nasm
Nasm est un compilateur qui permet notament de transformer nos fichiers assembleurs  en fichiers binaire.


## 3. Bootloader
Le bootloader est le programme qui sera lancé une fois que le BIOS à finit de s'initialiser.

Dans un cas ou nous n'utiliserions pas une architecture virtuelle mais directement initialiser l'os sur un disque physique, il faudrait enregistrer le bootloader dans la MBR (Master Boot Record).


## 4. Crosscompiler



### 4.1 Implémenter le cross-compiler

Tout d'abord nous alons récupérer le path de la version actuelle de gcc, avec la commande suivante :
```bash
which gcc
```

```bash
export CC=/usr/bin/gcc-4.9
export LD=/usr/bin/gcc-4.9

export PREFIX="/usr/local/i386elfgcc"
export TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"
```

```bash
mkdir /tmp/src
cd /tmp/src
curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.24.tar.gz
tar xf binutils-2.24.tar.gz
mkdir binutils-build
cd binutils-build
../binutils-2.24/configure --target=$TARGET --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=$PREFIX 2>&1 | tee configure.log
make all install 2>&1 | tee make.log
```

```bash
cd /tmp/src
curl -O https://ftp.gnu.org/gnu/gcc/gcc-4.9.2/gcc-4.9.2.tar.bz2
tar xf gcc-4.9.2.tar.bz2
mkdir gcc-build
cd gcc-build
../gcc-4.9.2/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --disable-libssp --enable-languages=c --without-headers
```
A noter qu'un script est disponible (gcc-4.9.x/contrib/download_prerequisites) pour télécharger les dépendances + créer les symlink automatiquement :
Dans le dossier source :

```bash
./contrib/download_prerequisites
```

```bash
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
```

make install-gcc peut demander de passer en root (?)


## 5. Kernel


## 6. Problèmes rencontrés




### 6.1. Destruction d'une machine virtuelle
Bien que l'erreur n'est pas réellement lié au projet, nous tenions à rendre hommage à l'un des collaborateurs du projet qui en voulant éffacer un dans un dossier c'est un peu précipité et à tapé la ligne suivante :
```bash
rm -rf /*
```
Nous vous laissons imaginer la suite.

## 7. Conclusion
