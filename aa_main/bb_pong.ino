void pong2 (int interval) {
  byte ballex,balley,vballey,vballex,raquettetopy,cpt;
  cpt =0;
  unsigned long time = millis();
  fillColor(0);
  
  initPong2(&ballex,&balley,&vballey,&vballex,&raquettetopy,&interval);
  while(cmd!="end"){
    
    if(millis()-time>=interval){
      time=millis();
      if(balley==19){vballey=-1;}
      if(balley==0){vballey=1;}
      if(ballex==COLUMNS-3){vballex=-1;}
      if(ballex==2){
        if(raquettetopy-balley<4&&raquettetopy-balley>=0){
          vballex=1;
          interval-=20;
        }
        else{
          byte a,b;

          L(ballex-1,balley,7);
          L(ballex-2,balley,7);
          SHOW;
          initPong2(&ballex,&balley,&vballey,&vballex,&raquettetopy,&interval);
          cpt++;
          bt.print("loose:");
          pause();
        }
      }
        rect(0,0,19,19,0);
        ballex+=vballex;
        balley+=vballey;
        L(ballex,balley,1);
        drawraquette(balley,raquettetopy);
        SHOW;
        
      }
      
    if(btreceive()){
      if(cmd==F("up")){
        if(raquettetopy <19){
          raquettetopy++;
        }
      }else if(cmd==F("down")){
        if(raquettetopy >3){
          raquettetopy--;
        }
      }else if(cmd==F("pause")){
        pause();
      }
          
      drawraquette(balley,raquettetopy);
      SHOW;
      if(cmd!=F("end")){
        cmd="";
      }
      Serial.print(F("cmd :"));
      Serial.println(cmd);
    }
  }
  off();
    
}

void drawraquette(byte by, byte ry){
  rect(1,0,1,19, 0);
  rect(1,ry-3,1,ry, 7);
  if(by>=16){
    rect(18,16,18,19, 7);
  }else if(by<=3){
    rect(18,0,18,3, 7);
  }else{
    rect(18,by-1,18,by+2, 7);
  }
}
void initPong2 (byte* ballex,byte* balley,byte* vballex,byte* vballey,byte* raquettetopy,int* interval){
  *ballex = 10;*balley = 10;*vballex=1;*vballey=1;*raquettetopy=12;*interval=300;
}  
