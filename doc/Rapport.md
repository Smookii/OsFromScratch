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
Nous employons tous un système d'éxploitation (ou au moins avons employé une fois) surtout dans notre travaille d'ingénieur en informatique. En effet, nous avons créé déjà des programmes qui sont exécuté sur des OS (Windows, Linux).
Dans le cours de conception OS nous avons choisi un projet qui consiste
à créer notre propre OS tournant sur une machine virtuel QEMU (émulateur d'architecture processeur). Avec ce projet nous voulons donc mieux comprendre comment fonctionne du côté hardware qu'au côté software notre OS, notamment les points suivant :
* Comment boot un ordinateur
* Comment écrire des programes bas niveau alors qu'il n'y a pas encore d'OS
* Comment relier le CPU avec tous les composants
* Comment passer du code assembleur à un langage haut niveau.
* Comment créer des caractéristique d'un OS comme un filesystem, un shell, des drivers, des tâches etc... .




## 2. Prérequis
### 2.1. Machine virtuelle
Les différens collaborateurs du projets ont décidé de travailler sur une machine virtuel linux.

### 2.2. Qemu
Qemu est un logiciel qui permet de créer une machine virtuel permetant de simuler une architecture sur laquelle nous pouvons instancier notre os.
Nous émulons un processeur i386 comme architécture.

### 2.3. Nasm
Nasm est un compilateur qui permet notamment de transformer nos fichiers assembleurs  en fichiers binaire.

### 2.4 Environnement
Le projet a été réaliser sur une système UNIX plus précisement une distribution Ubuntu. Mais le projet peut se faire également sur un système MSDOS.


## 3 Etape du projet
* Crée un boot loader.
* Entrer dans un mode 32-bit.
* Pouvoir passer du langage bas niveau (assembleur) au haut niveau (exemple langaege c).
* Gestion des I/O comme l'écran et le clavier.
* Associer un libc pour avoir des commandes de bases (par exemple utiliser BusyBox).
* Le MM (Memory Management).
* Créer un système de fichier (filesystem)
* Créer un shell de commande.



## 4. Bootloader (DONE)
Le bootloader est le programme qui sera lancé une fois que le BIOS à finit de s'initialiser.

Le Bios ne sait pas comment lancer l'OS, c'est le boot sector qui s'en occupe. Il est placé dans le 1er secteur du disque dr (cylindre 0, head 0, secteur 0). Il prend 512 bytes.
Ce boot sector est en 16-bit.
Dans un cas ou nous n'utiliserions pas une architecture virtuelle mais directement initialiser l'os sur un disque physique, il faudrait enregistrer le bootloader dans la MBR (Master Boot Record).

Avant l'initialisation



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

## Mode d'emploie
### Nasm
Pour passer du code assembleur à du code brute :
````bash
$nasm boot_sect.asm -f -o boot_sect.bin
````

### QEmu
Pour émuler notre os.
````bash
$qemu your-os-boot-disk-image-file.bin
````


## 7. Conclusion

## Référence
* [Writing a Simple Operation System - from Scratch](http://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf) Document by Nick Blunde
* [os-tutorial](https://github.com/cfenollosa/os-tutorial) Github by Carlos Fenollosa
* [wiki.osdev.org](https://wiki.osdev.org/) - Wiki for creation of operation system
