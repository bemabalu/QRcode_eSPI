#include <Arduino.h>
#include "qrencode.h"
#include "qrcode_espi.h"


QRcode_eSPI::QRcode_eSPI(TFT_eSPI *display) {
    this->display = display;
}


void QRcode_eSPI::init(uint16_t size, uint16_t xoffset, uint16_t yoffset) {
    //display->init();
    this->screenwidth = display->width();
    this->screenheight = display->height();
    display->fillScreen(TFT_BLACK);
    if (!size){
        size = screenwidth;
        if (screenheight<screenwidth)
            size = screenheight;
    }
    multiply = size/WD;
    offsetsX = (screenwidth-(WD*multiply))/2+xoffset;
    offsetsY = (screenheight-(WD*multiply))/2+yoffset;
}

void QRcode_eSPI::create(String message) {
  display->startWrite();
  QRcodeDisplay::create(message);
  display->endWrite();
}

void QRcode_eSPI::screenwhite() {
    //display->fillScreen(TFT_WHITE );
    display->fillRect(offsetsX-multiply,offsetsY-multiply,(WD+2)*multiply,(WD+2)*multiply,TFT_WHITE);
}

void QRcode_eSPI::screenupdate() {
    // No hay que hacer nada
}

void QRcode_eSPI::drawPixel(int x, int y, int color) {
    if(color==1) {
        color = TFT_BLACK;
    } else {
        color = TFT_WHITE;
    }
    display->drawPixel(x,y,color);
    if (this->multiply>1) {
        display->fillRect(x,y,multiply,multiply,color);
    }
}