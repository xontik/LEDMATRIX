 
void simpleEffect(){
  byte x,y;
  for(y = 0; y < 20; y++){
    for(x = y%2; x<20 ; x+=2){
      L(x,y,0);
    }
  }
  SHOW;
}
