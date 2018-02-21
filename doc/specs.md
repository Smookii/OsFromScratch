# OS - Cahier des charges

## OS from scratch

### Luca Srdjenovic, Axel Bento da Silva, Guillaume Noguera

#### Introduction

Le but est de développer un petit os destiné à tourner sur Qemu (architecture ARM, reste à définir lequel)
Une grande partie du projet consistera évidemment à se documenter sur le fonctionnement concret d'un os.


#### Buts (~Etapes)

1. Etudier l'architecture choisie
2. Etudier le flux "standard" d'un OS
3. Définir routines de base en assembleur
4. Boot
5. Gestion d'un file system
6. Affichage d'un hello world
7. Gestion entrées (clavier)
8. Développement d'un petit compilateur
9. Invite de commande (directement assembleur ? Possible ? )
10. Invite de commande - Language "courant"


#### Prérequis
* Qemu qui permet de simuler une architecture sur laquelle nous lançons notre os.
* Nasm qui permet de compiler des fichiers assembleurs en fichier binaire.


#### BootLoader
La première chose à faire est de créer un bootloader c'est à dire le programme, qui va être lancé à l'initialisation de la machine (dans un cas réel le boot loader doit être placer dans le MBR).



#### Links

[Base utilisée](http://createyourownos.blogspot.ch)
[Github](https://github.com/cfenollosa/os-tutorial)
[Document utilse](http://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)
