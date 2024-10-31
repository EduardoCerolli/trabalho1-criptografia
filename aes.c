#include <stdlib.h>
#include <stdio.h>


unsigned char caixaS[256] = {
    // 0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,  // 0
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,  // 1
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,  // 2
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,  // 3
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,  // 4
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,  // 5
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,  // 6
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,  // 7
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,  // 8
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,  // 9
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,  // A
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,  // B
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,  // C
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,  // D
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,  // E
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}; // F

unsigned char rcon[10] = {1, 2, 4, 8, 16, 32, 64, 128, 27, 54};

unsigned char chave[16];
unsigned char chaveExpandida[160];


// XOR entre o bloco atual e chave de rodada
void adicionaChave (unsigned char bloco[16], unsigned char chave[160], int rodada) {
    for (int i = 0; i < 4; i++) {
        bloco[(i * 4) + 0] = bloco[(i * 4) + 0] ^ chave[(i * 4) + rodada + 0];
        bloco[(i * 4) + 1] = bloco[(i * 4) + 1] ^ chave[(i * 4) + rodada + 1];
        bloco[(i * 4) + 2] = bloco[(i * 4) + 2] ^ chave[(i * 4) + rodada + 2];
        bloco[(i * 4) + 3] = bloco[(i * 4) + 3] ^ chave[(i * 4) + rodada + 3];
    }

    return;
}

void substituiBytes(unsigned char bloco[16]) {
    for (int i = 0; i < 4; i++) {
        bloco[(i * 4) + 0] = caixaS[bloco[(i * 4) + 0]];
        bloco[(i * 4) + 1] = caixaS[bloco[(i * 4) + 1]];
        bloco[(i * 4) + 2] = caixaS[bloco[(i * 4) + 2]];
        bloco[(i * 4) + 3] = caixaS[bloco[(i * 4) + 3]];
    }
}

void rotacionaLinhas (unsigned char bloco[16]) {
    unsigned char aux1, aux2, aux3, aux4;
    
    for (int i = 1; i < 4; i++)
    {
        aux1 = bloco[(i * 4) + ((0 + i) % 4)];
        aux2 = bloco[(i * 4) + ((1 + i) % 4)];
        aux3 = bloco[(i * 4) + ((2 + i) % 4)];
        aux4 = bloco[(i * 4) + ((3 + i) % 4)];

        bloco[(i * 4) + 0] = aux1;
        bloco[(i * 4) + 1] = aux2;
        bloco[(i * 4) + 2] = aux3;
        bloco[(i * 4) + 3] = aux4;
    }
    
    return;
}

void multiplicaColunas(unsigned char bloco[16]) {
    unsigned char matriz_aux[16];
     
    for (int i = 0; i < 4; i++) {

        matriz_aux[i]  = (bloco[i] << 1) ^ (bloco[i] >> 7 ) * 0x1B;
        matriz_aux[i] ^= ((bloco[4 + i] << 1) ^ (bloco[4 + i] >> 7 ) * 0x1B) ^ (bloco[4 + i]);
        matriz_aux[i] ^= bloco[8 + i];
        matriz_aux[i] ^= bloco[12 + i];

        matriz_aux[4 + i]  = bloco[i];
        matriz_aux[4 + i] ^= (bloco[4 + i] << 1) ^ (bloco[4 + i] >> 7 ) * 0x1B;
        matriz_aux[4 + i] ^= ((bloco[8 + i] << 1) ^ (bloco[8 + i] >> 7 ) * 0x1B) ^ (bloco[8 + i]);
        matriz_aux[4 + i] ^= bloco[12 + i];

        matriz_aux[8 + i]  = bloco[i];
        matriz_aux[8 + i] ^= bloco[4 + i];
        matriz_aux[8 + i] ^= (bloco[8 + i] << 1) ^ (bloco[8 + i] >> 7 ) * 0x1B;
        matriz_aux[8 + i] ^= ((bloco[12 + i] << 1) ^ (bloco[12 + i] >> 7 ) * 0x1B) ^ (bloco[12 + i]);

        matriz_aux[12 + i]  = ((bloco[i] << 1) ^ (bloco[i] >> 7 ) * 0x1B) ^ (bloco[i]);
        matriz_aux[12 + i] ^= bloco[4 + i];
        matriz_aux[12 + i] ^= bloco[8 + i];
        matriz_aux[12 + i] ^= (bloco[12 + i] << 1) ^ (bloco[12 + i] >> 7 ) * 0x1B;
    }

    // Copia os resultados de volta para o bloco original
    for (int i = 0; i < 4; i++) {
        bloco[(i * 4) + 0] = matriz_aux[(i * 4) + 0];
        bloco[(i * 4) + 1] = matriz_aux[(i * 4) + 1];
        bloco[(i * 4) + 2] = matriz_aux[(i * 4) + 2];
        bloco[(i * 4) + 3] = matriz_aux[(i * 4) + 3];
    }

    return;
}


void funcaoG (unsigned char palavra[4], unsigned char p0, unsigned char p1, unsigned char p2, unsigned char p3, int rodada) {
    palavra[0] = p1;
    palavra[1] = p2;
    palavra[2] = p3;
    palavra[3] = p0;

    palavra[0] = caixaS[palavra[0]];
    palavra[1] = caixaS[palavra[1]];
    palavra[2] = caixaS[palavra[2]];
    palavra[3] = caixaS[palavra[3]];

    palavra[0] = palavra[0] ^ rcon[rodada];

    return;
}

void expandeChave () {
    unsigned char aux[4];
    int rodada = 0;
    
    funcaoG(aux, chave[3], chave[4 + 3], chave[8 + 3], chave[12 + 3], 0);
    chaveExpandida[0] = aux[0] ^ chave[0];
    chaveExpandida[4] = aux[1] ^ chave[4];
    chaveExpandida[8] = aux[2] ^ chave[8];
    chaveExpandida[12] = aux[3] ^ chave[12];

    chaveExpandida[1] = chaveExpandida[0] ^ chave[1];
    chaveExpandida[4 + 1] = chaveExpandida[4] ^ chave[4 + 1];
    chaveExpandida[8 + 1] = chaveExpandida[8] ^ chave[8 + 1];
    chaveExpandida[12 + 1] = chaveExpandida[12] ^ chave[12 + 1];

    chaveExpandida[2] = chaveExpandida[1] ^ chave[2];
    chaveExpandida[4 + 2] = chaveExpandida[4 + 1] ^ chave[4 + 2];
    chaveExpandida[8 + 2] = chaveExpandida[8 + 1] ^ chave[8 + 2];
    chaveExpandida[12 + 2] = chaveExpandida[12 + 1] ^ chave[12 + 2];

    chaveExpandida[3] = chaveExpandida[2] ^ chave[3];
    chaveExpandida[4 + 3] = chaveExpandida[4 + 2] ^ chave[4 + 3];
    chaveExpandida[8 + 3] = chaveExpandida[8 + 2] ^ chave[8 + 3];
    chaveExpandida[12 + 3] = chaveExpandida[12 + 2] ^ chave[12 + 3];
    
    for (int i = 4; i < 40; i+= 4)
    {
        rodada++;
        funcaoG(aux, chaveExpandida[i - 1], chaveExpandida[4 + i - 1], chaveExpandida[8 +  i - 1], chaveExpandida[12 + i - 1], rodada);
        chaveExpandida[i] = aux[0] ^ chaveExpandida[i - 4];
        chaveExpandida[4 + i] = aux[1] ^ chaveExpandida[4 + i - 4];
        chaveExpandida[8 +  i] = aux[2] ^ chaveExpandida[8 +  i - 4];
        chaveExpandida[12 + i] = aux[3] ^ chaveExpandida[12 + i - 4];

        chaveExpandida[i + 1] = chaveExpandida[i + 1 - 1] ^ chaveExpandida[i + 1 - 4];
        chaveExpandida[4 + i + 1] = chaveExpandida[4 + i + 1 - 1] ^ chaveExpandida[4 + i + 1 - 4];
        chaveExpandida[8 +  i + 1] = chaveExpandida[8 +  i + 1 - 1] ^ chaveExpandida[8 +  i + 1 - 4];
        chaveExpandida[12 + i + 1] = chaveExpandida[12 + i + 1 - 1] ^ chaveExpandida[12 + i + 1 - 4];

        chaveExpandida[i + 2] = chaveExpandida[i + 2 - 1] ^ chaveExpandida[i + 2 - 4];
        chaveExpandida[4 + i + 2] = chaveExpandida[4 + i + 2 - 1] ^ chaveExpandida[4 + i + 2 - 4];
        chaveExpandida[8 +  i + 2] = chaveExpandida[8 +  i + 2 - 1] ^ chaveExpandida[8 +  i + 2 - 4];
        chaveExpandida[12 + i + 2] = chaveExpandida[12 + i + 2 - 1] ^ chaveExpandida[12 + i + 2 - 4];

        chaveExpandida[i + 3] = chaveExpandida[i + 3 - 1] ^ chaveExpandida[i + 3 - 4];
        chaveExpandida[4 + i + 3] = chaveExpandida[4 + i + 3 - 1] ^ chaveExpandida[4 + i + 3 - 4];
        chaveExpandida[8 +  i + 3] = chaveExpandida[8 +  i + 3 - 1] ^ chaveExpandida[8 +  i + 3 - 4];
        chaveExpandida[12 + i + 3] = chaveExpandida[12 + i + 3 - 1] ^ chaveExpandida[12 + i + 3 - 4];
    }
    

    return;
}

void cifraBloco (unsigned char bloco [16]) {

    for (int i = 0; i < 4; i++) {
        bloco[(i * 4) + 0] = bloco[(i * 4) + 0] ^ chave[(i * 4) + 0];
        bloco[(i * 4) + 1] = bloco[(i * 4) + 1] ^ chave[(i * 4) + 1];
        bloco[(i * 4) + 2] = bloco[(i * 4) + 2] ^ chave[(i * 4) + 2];
        bloco[(i * 4) + 3] = bloco[(i * 4) + 3] ^ chave[(i * 4) + 3];
    }

    for (int i = 0; i < 9; i++) {
        substituiBytes(bloco);
        rotacionaLinhas(bloco);
        multiplicaColunas(bloco);
        adicionaChave(bloco, chaveExpandida, i * 4);
    }
    substituiBytes(bloco);
    rotacionaLinhas(bloco);
    adicionaChave(bloco, chaveExpandida, 9 * 4);
    
    return;
}

void preencheChave(char *senha) {
    unsigned char aux[17];

    if (senha == NULL) {
        printf("Digite a senha.\n");
        int res = scanf ("%16s", aux);
        if (res == 0) {
            perror ("Erro ao ler chave") ;
            exit (1) ;
        }
    }
    else {
        FILE *arq;
        arq = fopen(senha, "r");
        if (!arq) {
            perror ("Erro ao abrir arquivo") ;
            exit (1) ;
        }
        int tam = fread(aux, 1, 16, arq);
        if (tam != 16) {
            perror ("Erro ao ler chave") ;
            exit (1) ;
        }

        fclose (arq);
    }

    int k = 0;
    for (int i = 0; i < 4; i++) {
        chave[i] = aux[k++];
        chave[4 + i] = aux[k++];
        chave[8 + i] = aux[k++];
        chave[12 + i] = aux[k++];
    }

    expandeChave();
}

int leBloco (unsigned char bloco [16], FILE *arq) {
    unsigned char aux[17];
    
    int tam = fread (aux, 1, 16, arq) ;    
    if (tam < 1)
        return 0;
    
    for (int i = tam; i < 16; i++)
        aux[i] = 'X';

    int k = 0;
    for (int i = 0; i < 4; i++) {
        bloco[i] = aux[k++];
        bloco[4 + i] = aux[k++];
        bloco[8 + i] = aux[k++];
        bloco[12 + i] = aux[k++];
    }

    return 1;
}

int main (int argc, char *argv[]) {
    char *dados, *senha = NULL;

    if (argc < 2) {
        printf("Informe o arquivo de dados.\n");
        return 1;
    }
    else if (argc > 2) {
        senha = argv[2];
    }
    
    dados = argv[1];

    preencheChave(senha);

    FILE *arq;
    arq = fopen(dados, "r");
    if (!arq) {
        perror ("Erro ao abrir arquivo") ;
        exit (1) ;
    }

    // unsigned char bloco [16];
    // while (!feof (arq)) {
    //     if (leBloco(bloco, arq)) {
    //         cifraBloco(bloco);
            
    //         for (int i = 0; i < 4; i++)
    //         {
    //             for (int j = 0; j < 4; j++)
    //                 printf("%c", bloco[(j * 4) + i]);        
    //         }
    //     }
    // }

    for (int i = 0; i < 40; i++)
    {
        for (int j = 0; j < 4; j++)
            printf("%02x", chaveExpandida[(j * 4) + i]);        
    }
    printf("\n");


    fclose (arq);
    return 0;
}