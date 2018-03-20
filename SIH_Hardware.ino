#include <IRremote.h>
#include "remote.h"
//#define RELAY_ON 0
//#define RELAY_OFF 1
#include <QueueList.h>
unsigned long lastButtonTime = millis();
const int timeDelay = 500;

const int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;
QueueList <long> queue;

class Receiver{
  public:
    long RecvArray[10];
    bool datarecv =0;
    int i,count=0;
    int timeflag=0;
    
    void compute()  {
      
       if (irrecv.decode(&results)){
//        Serial.println(results.value);

           //0 to 9
          for(i=0;i<10;i++){
            if(results.value==arr[i])
              {
                lastButtonTime=millis();
                timeflag=1;
                count++;
                queue.push(i);
                break;
              }                         
          }
          
        irrecv.resume();
       }
        if(timeflag==1){
          if(millis()-lastButtonTime>=2000 || count==3 ){
            //Change Channel
            timeflag=0;
            count=0;
            for(i=0;i<3;i++)
              Serial.println(queue.pop());
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

void setup(){
  recv.setup();  
}

void loop(){
//  if (irrecv.decode(&results)){
//        Serial.println(results.value);
//        getRemoteValues(results.value)
//        irrecv.resume();
//       }
  recv.compute();
  
}


