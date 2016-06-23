//
//  Brightness.c
//  Prova2SIMD
//
//  Created by leonardo albuquerque on 16/06/16.
//  Copyright © 2016 leonardo albuquerque. All rights reserved.
//

#include "Brightness.h"


PPMImage *aumentaBrilho(PPMImage *img, unsigned char valor){
    
    int i;
    PPMImage *imgBrilho;
    //Aloca a estrutura
    imgBrilho = (PPMImage *)malloc(sizeof(PPMImage));
    
    //Aloca o espaço para os pixeis
    imgBrilho->data = (PPMPixel*)malloc(img->width * img->height * sizeof(PPMPixel));
    
    if (!imgBrilho | !imgBrilho->data) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }
    
    imgBrilho->width = img->width;
    imgBrilho->height = img->height;
    
    char max = 255 - valor;
    __m128i max128i = _mm_set1_epi8(max);
    __m128i value128i = _mm_set1_epi8(valor);
    
    __m128i pixel128i;
    
    
    // SEÇÃO PASSÍVEL DE OTIMIZAÇÃO
    fprintf(stderr, "Aplicando brilho a mais...");
    for ( i = 0; i < (img->width * img->height); i+= 5 ) { 
        //carrega
        pixel128i = _mm_loadu_si128((__m128i*) &img->data[i]);
        //evita overflow
        pixel128i = _mm_min_epu8(max128i, pixel128i);
        //aumenta o brilho
        pixel128i = _mm_add_epi8(pixel128i, value128i);
        //salva
        _mm_storeu_si128((__m128i*) &imgBrilho->data[i], pixel128i);
        
    }
    
    fprintf(stderr, "pronto\n");
    return imgBrilho;
}