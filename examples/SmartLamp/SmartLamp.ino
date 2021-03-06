#include <SoftwareSerial.h>
#include "Obloq.h"

SoftwareSerial softSerial(10,11);
//生成OBLOQ对象，参数：串口指针，wifiSsid,WifiPwd,iotId,iotPwd
Obloq olq(&softSerial,"DFRobot-guest","dfrobot@2017","SJG02MoBSf","Sk7AnMsBrG");
const String devTopic = "HkfVZ9BBz";
 //led小灯引脚
int ledPin = 2;

//已监听设备的消息回调函数，可以在这个函数里面对接收的消息做判断和相应处理，需要用setMsgHandle()来设置这个回调函数
void msgHandle(const String& topic,const String& message)
{
    if(devTopic == topic)
    {
        if(message == "0")
          digitalWrite(ledPin,LOW);
        else if(message == "1")
          digitalWrite(ledPin,HIGH);
    }
}

void setup()
{
    pinMode(ledPin,OUTPUT);
    softSerial.begin(9600);
    olq.setMsgHandle(msgHandle);//注册消息回掉函数
    olq.subscribe(devTopic); //监听设备

}
void loop()
{
    olq.update();
}