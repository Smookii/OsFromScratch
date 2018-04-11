### Créer le cross-compiler

(Pour récupérer le path de la version actuelle de gcc :
```bash
which gcc
```

```bash
export CC=/usr/bin/gcc-4.9
export LD=/usr/bin/gcc-4.9

export PREFIX="/usr/local/i386elfgcc" #le compilo sera là
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

On peut enfin compiler notre function.c vers function.o :

```shell
narval@fuzzyOctopuss:~/dev/os-tutorial/12-kernel-c$ /usr/local/i386elfgcc/bin/i386-elf-gcc -ffreestanding -c function.c -o function.o
```

Résultat :

```shell
narval@fuzzyOctopuss:~/dev/os-tutorial/12-kernel-c$ cat function.c
int my_function() {
    return 0xbaba;
}
narval@fuzzyOctopuss:~/dev/os-tutorial/12-kernel-c$ /usr/local/i386elfgcc/bin/i386-elf-objdump -d function.o

function.o:     file format elf32-i386


Disassembly of section .text:

00000000 <my_function>:
   0:   55                      push   %ebp
   1:   89 e5                   mov    %esp,%ebp
   3:   b8 ba ba 00 00          mov    $0xbaba,%eax
   8:   5d                      pop    %ebp
   9:   c3                      ret    
```