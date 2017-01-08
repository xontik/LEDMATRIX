//shapes[FORM][ORIENTATION][y][x]<--- shape

byte gridT[21][13];
void showGrid(Shape s, Shape n){
  int x, y, col;
  
  Serial.println("--actual shape --");
  Serial.print("xpos = ");
  Serial.print(s.posx);
  Serial.print(" ypos = ");
  Serial.print(s.posy);
  Serial.print(" form = ");
  Serial.print(s.form);
  Serial.println("------------");
  for(int i = 0; i<4;i++){
    for(int k = 0; k<4;k++){
      Serial.print(s.body[i][k]);
      Serial.print(" ");
    }
    Serial.println("");
  }
  Serial.println("------------");
  for(int i = 21; i>=0;i--){
    if(i<10){
      Serial.print("0");
    }
    Serial.print(i);
    Serial.print("|");
    for(int k = 0; k<13;k++){
      if(k>=s.posx && k<s.posx+4 && i>=s.posy && i<s.posy+4){ 
        if(s.body[i-s.posy][k-s.posx] != 0){
          Serial.print(s.body[i-s.posy][k-s.posx]);
        }else{
          Serial.print(gridT[i][k]);
        }
      }else{
        Serial.print(gridT[i][k]);
      }
      Serial.print(" ");
    }
    Serial.println("");
  }//*/
  
  for(int i = 2; i<22;i++){ 
    for(int k = 2;k<12;k++){
      x = k-2;
      y = i-2;
      col = gridT[i][k];
      L(x,y,col);
      
    }
  }
  for(int i = 0; i<4;i++){ 
    for(int k = 0;k<4;k++){
      x=s.posx+k-2;
      y=s.posy+i-2;
      col = s.body[i][k];
      if(col != 0 ){
        L(x,y,col);
      }
    }
  }
  rect(13,13,18,18,7);
  rect(14,14,17,17,0);
  for(int i = 0; i<4;i++){ 
    for(int k = 0;k<4;k++){
      x=14+k;
      y=14+i;
      col = n.body[i][k];
      if(col != 0){
        L(x,y,col);
      }
      
    }
  }
  SHOW;
   
}

void initTetris(){
  fillColor(0);
  rect(10,0,11,19,3);
  
  for(int i = 0; i<=21;i++){
    for(int k = 0; k<14;k++){
      gridT[i][k] = 0;
      if(i<=1 || k>=12 || k<=1){
        gridT[i][k] = 1;
      }
    }
  }
  

}
void tetris(int interval){
  
  bool loose = false;
  initTetris();
  unsigned long time = millis();
  Shape actualShape = Shape(0,0);
  Shape nextShape = spawnShape();
  
  while(!loose && cmd!="end"){
    
    if(millis()-time>=interval){
      
      time=millis();
      if(moveShapeY(-1, actualShape)){
        actualShape.posy--;
      }else{
        if(actualShape.posy == 19){
          loose = true;
        }
        fixShape(actualShape);
        actualShape.copy(nextShape);
        nextShape.copy(spawnShape());
      }
      //*/
      showGrid(actualShape, nextShape);
      
    }
    if(btreceive()){
      if(cmd == "r"){
        if(moveShapeX(1, actualShape)){
          actualShape.posx++;
        }
      }else if(cmd == "l"){
        if(moveShapeX(-1, actualShape)){
          actualShape.posx--;
        }
      }else if(cmd == "b"){
        while(moveShapeY(-1, actualShape)){
          actualShape.posy--;
        }
      }else if(cmd == "pause"){
        pause();
      }else if(cmd == "end"){
        pause();
      }else if(cmd == "t"){
        bool turn = false;
        if(rotate(actualShape)){
          turn = true;
        }else{
          if(moveShapeX(1, actualShape)){
            actualShape.posx++;
            if(rotate(actualShape)){
              turn=true;
            }else{
              if(moveShapeX(1, actualShape)){
                actualShape.posx++;
                if(rotate(actualShape)){
                  turn=true;
                }
              }
            }
              
          }
          if(moveShapeX(-1, actualShape) && !turn){
            actualShape.posx--;
            if(rotate(actualShape)){
              turn=true;
            }else{
              if(moveShapeX(-1, actualShape)){
                actualShape.posx--;
                if(rotate(actualShape)){
                  turn=true;
                }
              }
            }
              
          }
        }
        if(turn){
          actualShape.rotation(1);
        }
      }
      if(moveShapeY(-1, actualShape)){
        
      }else{
        fixShape(actualShape);
        actualShape.copy(nextShape);
        nextShape.copy(spawnShape());
      }
      showGrid(actualShape, nextShape);
    }
    
      
  }
  Serial.println("LOOOSE");
  bt.print("loose:");
}
bool moveShapeY(byte diry, Shape s){
  byte tmpx, tmpy;
  tmpx = s.posx;  
  tmpy = s.posy + diry; 
  for(int i = 0;i<4;i++){
    for(int j = 0;j<4;j++){
      if(s.body[j][i]!=0){
        if(gridT[j+tmpy][i+tmpx]!=0){
          return false;
        }
      }
    }
  }
  return true;
}
//todo
bool moveShapeX(int dirx, Shape s){
byte tmpx, tmpy;
  tmpx = s.posx + dirx;  
  tmpy = s.posy; 
  for(int i = 0;i<4;i++){
    for(int j = 0;j<4;j++){
      if(s.body[j][i]!=0){
        if(gridT[j+tmpy][i+tmpx]!= 0){
          return false;
        }
      }
    }
  }
  return true;
}  


//rotate 
bool rotate(Shape s){
  s.rotation(1);
  for(int i = 0;i<4;i++){
    for(int j = 0;j<4;j++){
      if(s.body[j][i]!=0){
        if(gridT[j+s.posy][i+s.posx]!= 0){
          return false;
        }
      }
    }
  }
  return true;
}
void downLines(byte ylastline, byte nbLine){
  for(int i = ylastline-nbLine+1; i<22-nbLine;i++){
    for(int j = 2;j<12;j++){
      gridT[i][j] = gridT[i+nbLine][j];
    }
  }
    
    
}
void checkline(){
  bool line = true;
  bool down = false;
  byte nbLines = 0;

  
  for(int i = 2; i< 22 && nbLines < 5;i++){
     line = true;  
    for(int j = 2;j<12;j++){
        if(gridT[i][j] == 0){
          line = false;
        }
      }
      if(line){
        
        nbLines++;
      }else{
        
        if(nbLines > 0){
          downLines(i-1,nbLines);
          nbLines = 0;
        }
      }
   }
   
  
}
void fixShape(Shape s){  
  for(int i = 0;i<4;i++){
    for(int j = 0;j<4;j++){
      if(s.body[j][i] != 0){
        gridT[j+s.posy][i+s.posx] = s.body[j][i];
      }
    }
  }
  checkline(); 
}
Shape spawnShape(){
  return Shape((int)random(0,6),(int)random(0,3));
}



