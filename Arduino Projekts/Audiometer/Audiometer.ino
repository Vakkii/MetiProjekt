#define ROW_1 2
#define ROW_2 3
#define ROW_3 4
#define ROW_4 5
#define ROW_5 6
#define ROW_6 7
#define ROW_7 8
#define ROW_8 9

#define COL_1 10
#define COL_2 11
#define COL_3 12
#define COL_4 13
#define COL_5 A0
#define COL_6 A1
#define COL_7 A2
#define COL_8 A3
const byte rows[] = {
    ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8
};
const byte col[] = {
  COL_1,COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8
};
int count= 0;
void setup() {
  for(int i =0; i<8; i++){
        pinMode(rows[i], OUTPUT);
        digitalWrite(rows[i], LOW);
        pinMode(col[i], OUTPUT);
        digitalWrite(col[i], LOW);
   }


}
void resetMatrix(){
  for(int i =0; i<8; i++){
     digitalWrite(rows[i], LOW);
     digitalWrite(col[i], LOW);
  }
}
void loop() {
        for(int i =0; i<8; i++){
          for(int k =0; k<8; i++){
              digitalWrite(rows[k], HIGH);
              digitalWrite(col[i], HIGH);
              delay(2000);
              resetMatrix();
              while(1){
              delay(500);
              }
          }
        }
}


