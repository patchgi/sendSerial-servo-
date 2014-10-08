import processing.serial.*;

Serial serial;
ArrayList <String> idata;
int inputData, start, count, i;

void setup() {
  serial=new Serial(this, Serial.list()[0], 19200);
  idata=new ArrayList<String>();
}

void draw() {
}

void sendServoSequence(){
  String []readData=loadStrings("servodata.txt");
  int dataLength = readData.length;
  int []writeData=new int[dataLength];
  for (int j = 0; j < dataLength; j++) {
    writeData[j]=int(readData[j]);
  }
   for (int j = 0; j < dataLength; j++) {
    serial.write(byte(writeData[j]));
    print(writeData[j]+"=>");
    delay(100);
  }
  
}

void serialEvent(Serial port) {
  inputData=port.read();
  print(inputData+"=>");
  idata.add(str(inputData));
}

void keyPressed() {
  if (key=='s') {
    String []saveData=new String[idata.size()];
    for (int i=0;i<saveData.length;i++) {
      saveData[i]="";
    }
    for (int  j=0;j<saveData.length;j++) {
      saveData[j]=idata.get(j);
    }
    print(saveData);
    saveStrings("servodata.txt", saveData);
    delay(100);
    println("Done saving");
  }

  if (key=='p') {
     sendServoSequence();
  }
}

