// Deklaration und Initialisierung der Eingang-Pins
int Analog_Eingang = A0; // X-Achse-Signal
  
void setup ()
{
  pinMode (Analog_Eingang, INPUT);
       
  Serial.begin (9600); // Serielle Ausgabe mit 9600 bps
}
  
// Das Programm liest die aktuellen Werte der Eingang-Pins
// und gibt diese auf der seriellen Ausgabe aus
void loop ()
{
  float Analog;
    
  //Aktuelle Werte werden ausgelesen, auf den Spannungswert konvertiert...
  Analog = analogRead (Analog_Eingang) * (5.0 / 1023.0); 

    
  //... und an dieser Stelle ausgegeben
  Serial.print("Analoger Spannungswert:"); Serial.print (Analog, 4);  Serial.print ("V, ");
  Serial.println("");

  delay (200);
}
