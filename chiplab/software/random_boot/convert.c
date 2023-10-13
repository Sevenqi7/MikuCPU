#include<stdio.h>
#include<stdlib.h>
void main(){
    FILE *in;
    FILE *out;
    unsigned char mem[4];
    in  = fopen("rand_boot.bin","rb");
    out = fopen("rom.vlog","w");
    fprintf(out,"@1c000000\n");
    while(!feof(in)) {
        if (fread(mem,1,1,in) != 1) {
            fprintf(out,"%02x\n", mem[0]);
            break;
        }
        fprintf(out,"%02x\n", mem[0]);
    }
    fclose(in);
    fclose(out);
}
