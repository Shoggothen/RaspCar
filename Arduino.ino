int forward = 12;
int back = 11;
int left = 10;
int right = 9;
int delayint = 0;

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

int countChars( char* s, char c )
{
    return *s == '\0'
              ? 0
              : countChars( s + 1, c ) + (*s == c);
}

void process_data( String process_fullstr )
{
          if (process_fullstr.indexOf(";") >=0){
            String splitted = getValue(process_fullstr,';',1);
            delayint = splitted.toInt();
          } else {
            delayint = 0;
          }

          if (process_fullstr.indexOf("forward") >=0){
            digitalWrite(forward, LOW);
          }else if(process_fullstr.indexOf("back") >=0){
            digitalWrite(back, LOW);
          }else if(process_fullstr.indexOf("right") >=0){
            digitalWrite(right, LOW);
            digitalWrite(left, HIGH);
          }else if(process_fullstr.indexOf("left") >=0){
            digitalWrite(left, LOW);
            digitalWrite(right, HIGH);
          }else if(process_fullstr.indexOf("straight") >=0){
            digitalWrite(left, HIGH);
            digitalWrite(right, HIGH);
          }else if(process_fullstr.indexOf("stop") >=0){
            digitalWrite(forward, HIGH);
            digitalWrite(back, HIGH);
            digitalWrite(left, HIGH);
            digitalWrite(right, HIGH);
          }

          if(delayint != 0){
            delay(delayint);
            digitalWrite(forward, HIGH);
            digitalWrite(back, HIGH);
          }
          
          Serial.println(process_fullstr + " - done");
}

void setup() {
  Serial.begin(9600); //Serielle Verbindung öffnen
  pinMode(forward, OUTPUT);
  pinMode(back, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(left, OUTPUT);
  
  // Pins direkt HIGH schalten, damit kreislauf ned direkt geschlossen wird
  digitalWrite(forward, HIGH);
  digitalWrite(back, HIGH);
  digitalWrite(right, HIGH);
  digitalWrite(left, HIGH);
}

void loop() {
  String fullstr = ""; //"buffer" deklarieren, wo der string zwischengespeichert wird
  if (Serial.available() > 0) { //Wurden daten gesendet?
    delay(100); //100ms warten damit der computer genug zeit hat um den String zu übertragen
    while(Serial.available() > 0){ //Solange etwas vorhanden ist
      fullstr = fullstr + char(Serial.read()); //auslesen und dem buffer hinzufügen
    }
  
      if (fullstr.indexOf("|") >=0){
       char chared[fullstr.length() + 1];
       fullstr.toCharArray(chared,fullstr.length() + 1);
       int chars = countChars(chared, '|') +1;

       for(int i = 0; i < chars; i++){
          String fullstr_x = getValue(fullstr,'|', i);
       
          process_data(fullstr_x);
          delay(200);
       }
       
      } else {
          process_data(fullstr);
      }
    }
  
    fullstr = ""; //buffer leeren
  }