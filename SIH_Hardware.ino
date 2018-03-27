#include <IRremote.h>


#include "remote.h"
//#define RELAY_ON 0
//#define RELAY_OFF 1
#include <QueueList.h>
unsigned long lastButtonTime = millis();
const int timeDelay = 500;

const int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
IRsend irsend;
decode_results results;
QueueList <unsigned long> queue;
QueueList < unsigned long> chan;
class Receiver{
  public:
    //long RecvArray[10];
   // bool datarecv =0;
    int i,count=0;
    int timeflag=0;
    int recvflag=0,sendFlag=0;
    void compute()  {
      
       if (irrecv.decode(&results)){
        //Serial.println("Helo");

           //0 to 9
          for(i=0;i<10;i++){
            if(results.value==arr[i])
              {
                //Serial.println(arr[i]);
                lastButtonTime=millis();
                timeflag=1;
                count++;
                queue.push(i);
                chan.push(i);
               // Serial.println(i);
                //Serial.println("Nooo");
                sendFlag=2;
                break;
              }                         
          }
          if(sendFlag==0)
            {
              sendFlag=1;
              chan.push(results.value);
            }
       irrecv.resume();
       }
        if(timeflag==1){
          if(millis()-lastButtonTime>=2000 || count==3 ){
            //Change Channel
            timeflag=0;
            count=0;
            recvflag=1;
            //while(!queue.isEmpty())
              //Serial.println(queue.pop());
          }
          
        }
    }

    void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);

  
}

 };
Receiver recv;

 class Controller{
  public:
    bool channel[250];
    int i,temp=0,controlFlag=0;
    int timeflag=0;

    
   void changeValue(){
    for(i=0;i<75;i++)
      channel[i]=false;
    for(i=75;i<250;i++)
      channel[i]=true;
   }
    
      
    void compute()  {
      changeValue();
      if(recv.recvflag==1)
        {
            while(!queue.isEmpty())
              { temp*=10;               
                temp+=queue.pop();
                
              }
              recv.recvflag=0;
              //Serial.println(temp);
              recv.sendFlag=0;
              //Check if the channel is blocked or unblocked
              if(channel[temp]==true){
                Serial.println("Channel present");
                controlFlag=1;
              }
              
              else{
              Serial.println("Not Present");
              //Emptying contents kachra
              while(!chan.isEmpty())
               chan.pop();
                           
              }
              temp=0;
        }
    }

 };
Controller control;

class Sender{
  public:
    void compute(){
      if(control.controlFlag==1){
        control.controlFlag=0;
        while(!chan.isEmpty()){
         
             Serial.println(arr[chan.pop()]);
             irsend.sendNEC(16738455,32);
             //Serial.println("heeloo");
             irrecv.enableIRIn();
              delay(100);
        }
      }
      if(recv.sendFlag==1){
        recv.sendFlag=0;
        while(!chan.isEmpty()){
              //IR SEH BHEJO 
              Serial.println(chan.pop());
             irsend.sendNEC(16738455,32);
            // Serial.println("Hello");
             irrecv.enableIRIn();
             delay(500);
        }
      }
    }
};
Sender transmit;
void setup(){
  recv.setup();  
}
//
void loop(){
//  if (irrecv.decode(&results)){
//        Serial.println(results.value);
//        getRemoteValues(results.value)
//        irrecv.resume();
//       }
  recv.compute();
  control.compute();
  transmit.compute();
  //Serial.println(recv.timeflag);
  //Serial.println(recv.sendFlag);
  //Serial.println(recv.recvflag);
  delay(300);
  //Serial.println("Kitoo");
  //irrecv.enableIRIn();
  
}
/*
 Arduino: 1.8.5 (Windows 10), Board: "Arduino/Genuino Uno"

Archiving built core (caching) in: C:\Users\ASHLEY~1\AppData\Local\Temp\arduino_cache_597842\core\core_arduino_avr_uno_0c812875ac70eb4a9b385d8fb077f54c.a
c:/program files (x86)/arduino/hardware/tools/avr/bin/../lib/gcc/avr/4.9.2/../../../../avr/lib/avr5/crtatmega328p.o:(.init9+0x0): undefined reference to `main'

C:\Users\ASHLEY~1\AppData\Local\Temp\ccXX0in0.ltrans0.ltrans.o: In function `__base_dtor ':

C:\Users\Ashley Lobo\Documents\Arduino\libraries\QueueList/QueueList.h:117: undefined reference to `operator delete(void*)'

C:\Users\Ashley Lobo\Documents\Arduino\libraries\QueueList/QueueList.h:117: undefined reference to `operator delete(void*)'

collect2.exe: error: ld returned 1 exit status

exit status 1
Error compiling for board Arduino/Genuino Uno.

This report would have more information with
"Show verbose output during compilation"
option enabled in File -> Preferences.

 */

