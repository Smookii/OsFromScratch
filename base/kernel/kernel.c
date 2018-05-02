#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include <stdint.h>
#include "../libc/kfs.h"

uint32_t pages[8];
int current_page_index = 0;

char* vga = (char*)0xb8000;

void kernel_main() {
    isr_install();
    irq_install();

    init_kfs();

    asm("int $2");
    asm("int $3");

    kprint("Type something, it will go through the kernel\n"
        "Type KTHXBAI to halt the CPU or KEBAB-MALLOC to request a kmalloc()\n> "
        "C = [Args] to create a file, L to list files\n");
}

void user_input(char *input) {
  contains_arg(input);
    if (strcmp(input, "KTHXBAI") == 0) {
        kprint("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }
    else if (strcmp(input, "KEBAB-MALLOC") == 0 || strcmp(input, "Q") == 0) {
        uint32_t phys_addr;
        uint32_t page = kmalloc(1000, 1, &phys_addr);

        pages[current_page_index++] = page;
        kprint("Block allocated");
        char temp_id[16] = "";
        int_to_ascii(current_page_index, temp_id);
        kprint(temp_id);

        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        kprint("Page: ");
        kprint(page_str);
        kprint(", physical address: ");
        kprint(phys_str);
        kprint("\n");
    }
    else if (strcmp(input, "SNOW NOW PLS") == 0){
      *vga = 0xb8000;
      vga += 0xb1;
      kprint(vga);
    }
    else if (strcmp(input, "L") == 0){
      list_files();
    }
    else{
      int index = contains_arg(input);
      if (index != 0){
        if (input[0] == 'C'){
          char buffer[128];
          get_args(index, input, buffer);
          c_file(buffer);
          str_clear(buffer, 128);
        }
        else if (input[0] == 'R'){
          //todo
        }
        else if (input[0] == 'S'){
          //findbyid
        }
      }
    }
    kprint("You said: ");
    kprint(input);
    kprint("\n");
}
