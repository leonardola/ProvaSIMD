//
//  Negative.c
//  Prova2SIMD
//
//  Created by leonardo albuquerque on 22/06/16.
//  Copyright © 2016 leonardo albuquerque. All rights reserved.
//

#include "Negative.h"


//PPMImage *negativo (PPMImage *img)
//{
//    int i;
//    byte r, g, b;
//    PPMImage *imgNegativo;
//    imgNegativo = (PPMImage *)malloc(sizeof(PPMImage));
//    
//    //Aloca o espaço para os pixeis
//    imgNegativo->data = (PPMPixel*)malloc(img->width * img->height * sizeof(PPMPixel));
//    
//    if (!imgNegativo | !imgNegativo->data) {
//        fprintf(stderr, "Nao foi possivel alocar memoria\n");
//        exit(1);
//    }
//    
//    imgNegativo->width = img->width;
//    imgNegativo->height = img->height;
//    
//    
//    fprintf(stderr, "Aplicando o negativo...");
//    
//    for ( i = 0; i < (img->width * img->height); i++ ) {
//        r = 255 - img->data[i].red;
//        imgNegativo->data[i].red = r < 0? 0 : r;
//        
//        g = 255 - img->data[i].green;
//        imgNegativo->data[i].green = g < 0 ? 0 : g;
//        
//        b = 255 - img->data[i].blue;
//        imgNegativo->data[i].blue = b < 0 ? 0 : b;
//        
//    }
//    fprintf(stderr, "pronto\n");
//    
//    return imgNegativo;
//    
//}


PPMImage *negativo (PPMImage *img)
{
    
    int i;
    PPMImage *imgNegativo;
    imgNegativo = (PPMImage *)malloc(sizeof(PPMImage));
    
    //Aloca o espaço para os pixeis
    imgNegativo->data = (PPMPixel*)malloc(img->width * img->height * sizeof(PPMPixel));
    
    if (!imgNegativo | !imgNegativo->data) {
        fprintf(stderr, "Nao foi possivel alocar memoria\n");
        exit(1);
    }
    
    imgNegativo->width = img->width;
    imgNegativo->height = img->height;
    
    __m128i m255 = _mm_set1_epi8(255);
    
    fprintf(stderr, "Aplicando o negativo...");
    
    //r = 8 bits
    //g = 8 bits
    //b = 8 bits
    //total 24bits
    //128/24 = quase 5 pixels
    
    __m128i pixel128;
    for ( i = 0; i < (img->width * img->height); i+= 5 ) {
        //carrega 5 pixels por vez sobrando um subpixel no final
        pixel128 = _mm_loadu_si128((__m128i *) &img->data[i]);
        //subtrai o valor do subpixel de 255 invertendo a imagem
        pixel128 = _mm_sub_epi8(m255, pixel128);
        
        //guarda 5 pixels o ultimo subpixel será sobrescrito no próximo loop
        _mm_storeu_si128((__m128i *)&imgNegativo->data[i], pixel128);
        
    }
    
    fprintf(stderr, "pronto\n");
    
    return imgNegativo;
    
}