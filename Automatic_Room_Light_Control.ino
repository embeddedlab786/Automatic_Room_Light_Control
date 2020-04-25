#include <LiquidCrystal.h>// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define e_s1 A0 //echo pin
#define t_s1 A1 //Trigger pin

#define e_s2 A2 //echo pin
#define t_s2 A3 //Trigger pin

int relay = 8; // Out for light 

long dis_a=0,dis_b=0;
int flag1=0, flag2=0;
int person = 0; 

//**********************ultra_read****************************
void ultra_read(int pin_t,int pin_e,long &ultra_time){
long time;
pinMode(pin_t,OUTPUT);
pinMode(pin_e,INPUT);
digitalWrite(pin_t,LOW);
delayMicroseconds(2);
digitalWrite(pin_t,HIGH);
delayMicroseconds(10);
time=pulseIn (pin_e,HIGH);
ultra_time =  time / 29 / 2; 
}


void setup(){
Serial.begin(9600);// initialize serial communication at 9600 bits per second:

pinMode(relay, OUTPUT);

lcd.begin(16, 2);
lcd.setCursor(0, 0);
lcd.print("     Welcome    ");
delay(1000); // Waiting for a while
lcd.clear(); 
}

void loop(){ 
//*************************
ultra_read(t_s1,e_s1,dis_a);delay(30);
ultra_read(t_s2,e_s2,dis_b);delay(30);
//*************************

Serial.print("da:");Serial.println(dis_a);
Serial.print("db:");Serial.println(dis_b);   

if(dis_a<90 && flag1==0){flag1=1;
if(flag2==0){person = person+1;}
}

if(dis_b<90 && flag2==0){flag2=1;
if(flag1==0){person = person-1;}
}

if(dis_a>90 && dis_b>90 && flag1==1 && flag2==1){
flag1=0, flag2=0;
delay(1000); 
}

lcd.setCursor(0, 0);
lcd.print("Have Person: ");
lcd.print(person);
lcd.print("  ");
lcd.setCursor(0,1); 
lcd.print("Light is ");

if(person>0){digitalWrite(relay,HIGH); lcd.print("On ");}
else{digitalWrite(relay,LOW); lcd.print("Off");}
}
