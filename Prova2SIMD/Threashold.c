//
//  Threashold.c
//  Prova2SIMD
//
//  Created by leonardo albuquerque on 22/06/16.
//  Copyright © 2016 leonardo albuquerque. All rights reserved.
//

#include "Threashold.h"


PPMImage *aplicaThresold(PPMImage *img, unsigned char valor)
{
    int i;
    PPMImage *imgThresold;
    
    if (!img->dataBW){
        fprintf(stderr, "A imagem passada precisa ser convertida para escala de cinza\n");
        fprintf(stderr, "faça uma chamada a função converteBW(PPMImage *img) antes\n");
        return NULL;
        
    }
    //Aloca a estrutura
    imgThresold = (PPMImage *)malloc(sizeof(PPMImage));
    
    //Aloca o espaço para os pixeis
    imgThresold->dataBW = (byte*)malloc(img->width * img->height * sizeof(byte));
    
    if (!imgThresold | !imgThresold->dataBW) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }
    
    imgThresold->width = img->width;
    imgThresold->height = img->height;
    
    // SEÇÃO PASSÍVEL DE OTIMIZAÇÃO
    
    __m128i pixel128;
    //0 é o centro assim como o 127 era no algoritmo original, aparentemente(funciona!)
    //passando só valor a imagem fica quase toda branca
    __m128i medium = _mm_set1_epi8(valor-127);
    
    fprintf(stderr, "Aplicando o thresold...");
    for ( i = 0; i < (img->width * img->height); i+=5 ) {
        
        pixel128 = _mm_loadu_si128((__m128i *) &img->dataBW[i]);
        //thereshold
        pixel128 = _mm_cmplt_epi8 (pixel128, medium);
        
        _mm_storeu_si128((__m128i *) &imgThresold->dataBW[i], pixel128);
        
    }
    
    fprintf(stderr, "pronto\n");
    return imgThresold;
}