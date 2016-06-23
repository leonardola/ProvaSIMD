//
//  processos.c
//  Imagem04
//
//  Created by Marcelo Cendron on 30/04/16.
//  Copyright © 2016 Marcelo Cendron. All rights reserved.
//

#include "main.h"

int MIN(int X, int Y){
    return (X < Y) ? X : Y;
}
int MAX(int X, int Y){
    return (X > Y) ? X : Y;
}


void *histograma (PPMImage *histImage)
{
    int i, *hist;
    
    //Aloca o espaço para os pixeis
    hist = (int *)malloc(256 * sizeof(int));
    
    if (!histImage->dataBW) {
        fprintf(stderr, "A imagem passada deve ser preta e branca\n");
        exit(1);
    }
    
    if (!hist) {
        fprintf(stderr, "Nao foi possivel alocar memoria\n");
        exit(1);
    }
    fprintf(stderr, "Gerando o histograma...");
    
    /* Zera todos os elementos do histograma. */
    for (i=0; i<256; i++)
        hist[i] = 0;
    
    for (i=0; i < (histImage->width * histImage->height); i++)
        hist[histImage->dataBW[i]]++;
    
    fprintf(stderr, "pronto\n");
    fprintf(stderr, "Imprimindo histograma...\n");
    
    for(i=0; i <= 255; i++)
    {
        printf("%3d%10d", i, hist[i]);
        printf("\n");
    }
    
    /*
     int *hist2 = (int *)malloc(256 * sizeof(int));
     for (i=0; i<256; i++)
     hist2[i] = 0;
     
     for (i=0; i < (histImage->width * histImage->height); i++)
     hist2[histImage->dataBW[i]]++;
     
     
     fprintf(stderr, "pronto\n");
     fprintf(stderr, "!!!!Comparando os histogramas...\n");
     
     for(i=0; i <= 255; i++)
     {
     if (hist[i] != hist2[i]){
     printf("Diferente: %3d%10d\n", i, hist[i]);
     }
     }
     
     fprintf(stderr, "pronto\n");
     */
    
    return hist;
    
}

PPMImage *aplicaSepia(PPMImage *img)
{
    int i;
    byte r, g, b;
    PPMImage *imgsepia;
    //Aloca a estrutura
    imgsepia = (PPMImage *)malloc(sizeof(PPMImage));
    
    //Aloca o espaço para os pixeis
    imgsepia->data = (PPMPixel*)malloc(img->width * img->height * sizeof(PPMPixel));
    
    if (!imgsepia | !imgsepia->data) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }
    
    imgsepia->width = img->width;
    imgsepia->height = img->height;
    
    
    // SEÇÃO PASSÍVEL DE OTIMIZAÇÃO
    fprintf(stderr, "Aplicando o filtro sepia...");
    for ( i = 0; i < (img->width * img->height); i++ ) {
        r = 0.393 * img->data[i].red + 0.769 * img->data[i].green + 0.189 * img->data[i].blue;
        imgsepia->data[i].red = r > 255 ? 255 : r;
        
        g = 0.349 * img->data[i].red + 0.686 * img->data[i].green + 0.168 * img->data[i].blue;
        imgsepia->data[i].green = g > 255 ? 255 : g;
        
        b = 0.272 * img->data[i].red + 0.534 * img->data[i].green + 0.131 * img->data[i].blue;
        imgsepia->data[i].blue = b > 255 ? 255 : b;
        
    }
    fprintf(stderr, "pronto\n");
    return imgsepia;
}