### ON COLLERA CA PLUS TARD LOL

Par défaut pas possible d'écrire dans la ROM (Read Only Memory patate), mais QEMU permet d'émuler un disque dur en utilisant un système FAT (Représenté ici par un dossier hd)

```shell
qemu -drive file=fat:rw:path
```

-> modifié dans le Makefile
