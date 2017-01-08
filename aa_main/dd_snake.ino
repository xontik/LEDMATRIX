byte bodyX[400];
byte bodyY[400];
byte snakeSize;
byte appleX,appleY;
int dirX,dirY;
bool loose = false;
bool onBody(byte x,byte y){
   for(int i = 0;i<snakeSize;i++){
       if(bodyX[i]==x&&bodyY[i]==y){
           return true;

       }
   }
   return false;
}
void drawBody(){
   L(bodyX[snakeSize],bodyY[snakeSize],0);
  L(appleX,appleY,7);
   for(int i = 0; i < snakeSize;i++){
    L(bodyX[i],bodyY[i],6);
    //Ll(bodyX[i],bodyY[i]) = blend(CRGB::Green,CRGB::Red,1*(i/snakeSize));	
   } 
   SHOW;
}
void avance(){
  
            bodyX[snakeSize] = bodyX[snakeSize-1];
            bodyY[snakeSize] = bodyY[snakeSize-1];
            for(int i=snakeSize;i>0;i--){
              bodyX[i] = bodyX[i-1];
              bodyY[i] = bodyY[i-1];
             
              /*Serial.print("(");
              Serial.print(bodyX[i]);
              Serial.print(",");
              Serial.print(bodyY[i]);
              Serial.println(")");*/
            }
            bodyX[0]+=dirX;
            bodyY[0]+=dirY;
            /*Serial.print("(");
              Serial.print(bodyX[0]);
              Serial.print(",");
              Serial.print(bodyY[0]);
              Serial.println(")");
              Serial.println("-----HEAD ^^---");*/
            if(bodyX[0]==appleX&&bodyY[0]==appleY){
                snakeSize++;
                spawnApple();
            }
            if(beat(bodyX[0],bodyY[0])){
                loose=true;
                
            }
            else{ drawBody(); SHOW;}
            
}
bool beat(byte x,byte y){
   for(int i = 1;i<snakeSize;i++){
       if(bodyX[i]==x&&bodyY[i]==y){
           return true;
       }
   }
   if(x<0||x>19||y<0||y>19){
     return true;
   }
   return false;
}
void snake(int timming){
    fillColor(0);
    loose = false;
    unsigned long time = millis();
    dirX = random(1,3)-2;
    if(dirX==0){
        dirY = random(2);
        if(dirY==0){
          dirY=-1;
        }
    }
    snakeSize = 5;
    bodyX[0] = 10;
    bodyY[0] = 10;
    for(byte i = 1;i<=4;i++){
        bodyX[i] = bodyX[0]-i*dirX;
        bodyY[i] = bodyY[0]-i*dirY;
    }
    spawnApple();
    while(!loose){
        if(millis()-time>=timming){
          time = millis();
            avance();
            
            
        }
        
        if(btreceive()){
            if(cmd=="pause"){
                pause();
            }else if(cmd=="up"){
                if(dirY==0){
                    dirY++;
                    dirX=0;
                    avance();
                    time = millis();
                  
                }
            }else if(cmd=="down"){
                if(dirY==0){
                    dirY--;
                    dirX=0;
                    avance();
                    time = millis();
                    
                }
            }else if(cmd=="left"){
                if(dirX==0){
                    dirX--;
                    dirY=0;
                    avance();
                    time = millis();
                    
                }
            }else if(cmd=="right"){
                if(dirX==0){
                    dirX++;
                    dirY=0;
                    avance();
                    time = millis();
                    
                }
            }
            if(cmd=="end"){
                loose=true;
            }         
            
            
              
            
        }
        
    }
    if(cmd!="end"){
          bt.print("loose:");
    }
    
    
}
void spawnApple(){
    byte X,Y;
    bool  isBody = true;
    while(isBody){
        X = random(2,17);
        Y = random(2,17);
        isBody = onBody(X,Y);   
    }
    appleX=X;
    appleY=Y;
    
    L(X,Y,7);
}

