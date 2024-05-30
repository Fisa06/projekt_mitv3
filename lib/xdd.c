uint8_t lol[64] = {0};
for (uint8_t i = 1; i < 64; i= i+3) {

    lol[i] = 1;
}
uint32_t color = 0x400040;
uint32_t out[64] = {0};
for(uint8_t i = 0; i < 64; i++){
    if(lol[i]){
        out[i] = color;
    }
}

uint8_t lol2[64] = {0};
for (uint8_t i = 0; i < 64; i= i+3) {
    lol2[i] = 1;
}
uint32_t color2 = 0x004000;
uint32_t out2[64] = {0};
for(uint8_t i = 0; i < 64; i++){
    if(lol2[i]){
        out2[i] = color2;
    }
}
uint8_t lol3[64] = {0};
for (uint8_t i = 2; i < 64; i= i+3) {
    lol3[i] = 1;
}
uint32_t color3 = 0x0040f;
uint32_t out3[64] = {0};
for(uint8_t i = 0; i < 64; i++){
    if(lol3[i]){
        out3[i] = color3;
    }
}