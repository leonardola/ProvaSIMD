//
//  BlackAndWhite.c
//  Prova2SIMD
//
//  Created by leonardo albuquerque on 16/06/16.
//  Copyright © 2016 leonardo albuquerque. All rights reserved.
//

#include "BlackAndWhite.h"


PPMImage *converteBW(PPMImage *img)
{
    int i;
    PPMImage *imgBW;
    byte tmp;
    
    //Aloca a estrutura
    imgBW = (PPMImage *)malloc(sizeof(PPMImage));
    
    //Aloca o espaço para os pixeis
    imgBW->dataBW = (byte*)malloc(img->width * img->height * sizeof(byte));
    
    if (!imgBW | !imgBW->dataBW) {
        fprintf(stderr, "Nao foi possivel alocar memoria\n");
        exit(1);
    }
    
    imgBW->width = img->width;
    imgBW->height = img->height;
    
    // SEÇÃO PASSÍVEL DE OTIMIZAÇÃO
    fprintf(stderr, "Convertendo para escala de cinza...");
    for ( i = 0; i < (img->width * img->height); i++ ) {
        tmp = (byte) ( img->data[i].red * 0.299 +
                      img->data[i].green * 0.587 +
                      img->data[i].blue * 0.114);
        imgBW->dataBW[i] = tmp > 255? 255 : tmp;
        
    }
    fprintf(stderr, "pronto\n");
    return imgBW;
}