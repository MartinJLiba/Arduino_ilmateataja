//Bakalaureusetöö Arduino ilmateataja kood.
//Vajalikkude teekide kasutuselevõtt
#include <Adafruit_GFX.h> 
#include <TouchScreen.h>
#include <Adafruit_TFTLCD.h>
#include <ESP8266.h>
#include <dht.h>
 
//Vajalike viikude defineerimine ekraani isendi loomiseks.
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4
//Vajalike viikude defineerimine puutetundlikuse isendi loomiseks.
#define YP A3  
#define XM A2  
#define YM 9   
#define XP 8
//DHT anduri jaoks analoogviigu defineerimine.
#define dht_pin A5
//Ekraani isendi loomine
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
//Puutetundlikuse isendi loomine
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
//Wifi mooduli juhtimiseks isendi loomine. Serial tähistab rx ja tx viike.
ESP8266 esp(Serial); 
//DHT teegi isendi loomine.
dht DHT;

//Kalibreerimiseks vajalikud muutujad
#define TS_MINX 220
#define TS_MINY 215
#define TS_MAXX 910
#define TS_MAXY 875

//Värvi definitsioonid.
#define BLACK     0x0000
#define WHITE 0xFFFF
#define YELLOW  0xFFE0
#define GREY     0x7BEF
#define CYAN    0x07FF
#define GREEN   0x07E0
#define ORANGE  0xFD20
//Vajutustundlikuse määramine
#define MINPRESSURE 1
#define MAXPRESSURE 1000

const char *SSID     = "ludovisi"; //Pääsupunkti nime muutuja
const char *PASSWORD = "Singa68talu";//Pääsupunkti salasõna muutuja
//Ikoonide muutujad, mida kasutatakse ilmaandemte illustreerimiseks
extern uint8_t cloud_icon[];
extern uint8_t sun_icon[];
//extern uint8_t rain[];
extern uint8_t estonia_icon[];
extern uint8_t air_icon[];


//Muutujad, mis on vajalikud, et tuvastada millist ekraanivaadet kuvada pärast nupuvajutust
boolean current_condition=false; 
boolean future_condition=true;
boolean inClima=false;

//"Osaliselt pilves","4.5","87%","Idakirde","4.7","1002","15","3.0","Osaliselt pilves","24.5","Selge","4.4","Vihm"
String weatherdata[13]={}; //Muutuja, kus hoitakse päringust saadud ilmaandmeid 1:Ilmaolu, 2: temperatuur, 3:õhuniiskus, 4:tuulesuund, 5:tuule kiirus, 6:õhurõhk, 
//7:kellaaeg, 8-13 järgnevate tundide andmed. näide: {"Osaliselt pilves","4.5","87%","Idakirde","4.7","1002","15","3.0","Osaliselt pilves","24.5","Selge","4.4","Vihm"}
uint8_t next_hour; //Muutuja, kuhu salvestatakse arvuks teisendatud kellaeg. Vajalik, et tuvastada, kas ikoone kuvada öörežiimis
unsigned long next_request_time; //Muutuja, kuhu salvestatakse aeg järgmiseks päringuks
unsigned long  screenoff_time; //Muutuja, kuhu salvestatakse aeg, mil tuleb ekraan välja lülitada
bool screenon = true; //Muutja, tuvastamaks, kas ekraan on sisselülitatud
bool screenoff_perm =true; //Muutuja tuvastamaks, kas ekraani võib välja lülitada
int trig_pin = 12; //Trig viigu väärtus kaugusanduri jaoks
int echo_pin=11; //Echo viigu väärtus kaugusanduri jaoks
//Päring ilmaandmete saamiseks.
char* request= "GET http://api.wunderground.com/api/fad9d0fcd37d73e4/conditions/hourly/lang:ET/q/Estonia/Tartu.json HTTP/1.1\r\n\r\n";
//Päring aadressi saamiseks.
char* adress = "api.wunderground.com";


//Setup funktsioon, seda jooksutatakse ühel korral
void setup() {
  pinMode(10, OUTPUT); //Digitaalviik 10 seadistamine väljundiks
  digitalWrite(10, HIGH); //Digitaalviigu 10 5V tugevuseks määramine
  pinMode(trig_pin, OUTPUT); //Trig viigu seadistamine väljundiks
  pinMode(echo_pin, INPUT); //Echo viigu seadistamine väljundiks
  algseadistus(); //Funktsioon ekraani ja wifi mooduli algseadistamiseks.
  
 }


 
//loop funktsioon, see funktsioon jookseb tsükliliselt.
void loop() {
  if(!getData()){//Ilmaanmdete päringu tegemine
    delay(10000);
    
    if(!getData()){//Kui mingil põhjusel peaks päring esimene kord ebaõnnestuma, proovitakse uuesti
      //Veateate kuvamine
      digitalWrite(10, HIGH);
      tft.begin(37697);
      clearScreen(); 
      tft.setCursor(100,30);
      tft.print("Viga");
      screenoff_perm=true;
    }
    else{//Ilmaandmete päring on õnnestunud
    req_success(); //Funktsioon, et vältida koodu duplikeerimist.
  }
 }
  else{
    req_success();
  }

  
  next_request_time = millis() + 60000; //Hetkeajale lisatakse 10 minutit, pärast mida toimub andmete päring.
  screenoff_time = millis() + 30000; //Hetkeajale lisatakse minut, pärast mida lülitatakse ekraan välja.
  
  //Tsükkel, kuni järgmise päringuni.
  while (millis() < next_request_time ) {
    
    if(getTouch()){//Kontrollitakse, kas on toimunud nupuvajutus ekraanil, funktsiooniga getTouch().
      screenoff_time=millis() + 30000; //Kui toimub puudutus uuendatakse ekraani väljalülitamiseni jäänud aega.
      screenoff_perm=true; //Uuendatakse muutujat, mis lubab ekraani väljalülitamist.
     }
    
    else if(!screenon && getSign()){ //Kui ekraan on väljalülitatud kontrollitakse, kas toimub käeviibe kaugusanduri ees funktsiooniga getSign().
      //Ekraani sisselülitamine.
      digitalWrite(10, HIGH);
      tft.begin(37697);
      drawData();//Andmete joonistamine ekraanile.
      //Uuendatakse aega ja vajalikke tõeväärtusi
      screenoff_time=millis() + 30000;
      screenoff_perm=true;
      screenon=true;
      }
      
    else if(millis() > screenoff_time && screenoff_perm ){ //Kui ekraaniga pole interaktsiooni olnud 30 sekundi jooksul, lülitatakse ekraan välja.
      dimm(); //Funktsioon dimm() lülitab ekraani välja.
      //Edasi uuendatakse vastavaid tõeväärtusi
      screenon=false;
      screenoff_perm=false;
      current_condition=false;
      future_condition=true;
      }
   }
}

//Funktsioon ekraani ja wifi mooduli algseadistamiseks
void algseadistus(){
  tft.reset(); //Ekraani lähtestamine
  uint16_t identifier = 37697; //Ekraani id muutuja väärtustamine.
  //uint16_t identifier = tft.readID() //Ekraani id lugemine. Kasutada vaid ühel korra printides ekraanile või jadapordimonitori.
  tft.begin(identifier); //Ekraaniga ühenduse loomine
  //Järgnevalt seatakse paika sobilik asukoht ja kuvamisvalikud ning prinditakse infot algseadistamise õnnestumise kohta.
  clearScreen();
  tft.setCursor(55,50);
  tft.setTextSize(2);
  tft.print("Seadistamine");
  
  if (!esp.init(SSID, PASSWORD))//Pääsupunktiga ühenduse loomine
  {
    tft.print("Viga");
    while (true) ; 
  }
  tft.setCursor(75,80);
  tft.print("Valmis");
  delay(1000);
}


//Funktsiooni tegemisel sadud mõjutusi jsvesteri õpetusest aadressil: http://www.instructables.com/id/Simple-Arduino-and-HC-SR04-Example/.
bool getSign(){
  delay(500);//Viivituse pikkus iga mõõtmise vahel.
  //Muutujad pikkuse ja ajakestvuse jaoks.
  long duration;
  long distance;
  
  digitalWrite(trig_pin, LOW);//trig_pin lülitatakse hetkeks välja signaali puhastamiseks.
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);//trig_pin kaudu saadetakse signaal välja.
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);//trig_pin lülitatakse välja
  
  duration = pulseIn(echo_pin, HIGH);//Mõõdetakse aeg, mis kulus signaali tagasijõudmiseks.
  distance = (duration/2) / 29.1; //Arvutatakse välja vahemaa
  
  if (distance < 30) {//Kui vahemaa on alla 8 cm, tagastatakse true, mille peale ekraan lülitub sisse.
    return true;
  }
  return false;
}

//Funktsioon, mis tuvastab nupuvajutuse ekraanil.
bool getTouch(){
  TSPoint t = ts.getPoint(); //Puutepunkti pikkuse, laiuse ja kõrguse koordinaadid salvestatakse punkti p.
  
  //Vajutustundlikuks vajalik viikude seadistamine väljundiks.
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (t.z > ts.pressureThreshhold) { //Kui puudutuse tugevus on piisavalt suur, hakatakse puudutuse koordinaate edasi võrdlema.

   //Koordinaatide teisendamine, ekraani mõõtmetele vastavale kujule, map funktsiooni abil.
   t.x = 240 - map(t.x, TS_MAXX, TS_MINX, 0, 240);
   t.y = map(t.y, TS_MAXY, TS_MINY, 0, 320);

   if(t.x>195 && t.x<240 && t.y>306 && t.y<326) //Kontroll, kas puudutus on toimunud nupu sees.
   {
    
   pinMode(XM, OUTPUT);
   pinMode(YP, OUTPUT);
   
    if(current_condition){//Kui hetkel oli ees järgnevate tundide ilmaandmete ekraanivaade, kuvatakse pärast nupuvajutust hetkeilmaandmed. 
      drawData();
      current_condition=false;
      future_condition=true;
      }
    else if(future_condition){//Kui hetkel oli ees hetkeilmaandmete ekraanivaade, kuvatakse pärast nupuvajutust järgnevate tundide ilmaandmed. 
      secondScreen();
      current_condition=true;
      future_condition=false;
      }
      return true;
   } 
   else if (t.x > 10 && t.x < 240 && t.y > 10 && t.y < 150) { //Kui puudutus toimus ekraani ülemise kasti sees, kuvatakse toatemperatuuri ja õhuniiskust.
      if(future_condition){ //Toatemperatuuri ja õhuniiskuse vaate kuvamine.
        DHT.read11(dht_pin);
        clearScreen();
        tft.setCursor(50, 50);
        tft.setTextSize(4);
        tft.print(DHT.temperature);
        tft.print(String(char(247))+"C");
        tft.setCursor(50, 150);
        tft.print(DHT.humidity);
        tft.print("%");
        inClima=true;
        current_condition = false;
        future_condition = false;
      }
      else if(inClima){ //Hetke ilmaolude kuvamine.
        drawData();
        inClima=false;
        current_condition = false;
        future_condition = true;
      }
    } return true;
  } return false;
}

//Funktsioon ilmaandmete kuvamiseks järgnevatel tundidel.
void secondScreen(){
    clearScreen(); //Puhastatakse ekraan
    //Järgnevalt prinditakse tähised, mis aja kohta ilmainfo käib
    tft.setCursor(5,5);
    tft.print("+1h");
    tft.setCursor(5,125);
    tft.print("+3h");
    tft.setCursor(5,225);
    tft.print("+5h");
    //Ilmainfo joonistamine, kindlaksmääratud koordinaatidele
    drawMainInfo(weatherdata[8],weatherdata[7],110,25,1);
    drawMainInfo(weatherdata[10],weatherdata[9],110,135,2);
    drawMainInfo(weatherdata[12],weatherdata[11],110,233,3);
    
    drawButton("<-");//Ekraanivaadete vahel vahetamise nupu joonistamine
}



//Funktsioon, mis joonistab ekraanile ilmaseisundit kirjeldava ikooni ja kirjutab ekraanile ilmaseiseisundi ja temperatuuri.
void drawMainInfo(String condition, String temp, int x, int y, uint8_t pos){
  tft.setCursor(x,y); 
  
  drawIcon(condition,pos);//Ikooni joonistamise funktsioon.

  //Järgnevalt vaadatakse läbi erijuhte, kui tekst ei mahu ekraanile ilma lisapositsioneerimiseta ära, siis määratakse asukoht ise.
  if(condition == "Osaliselt pilves"){
    tft.setCursor(x,y);
    tft.print("Osaliselt");
    tft.setCursor(x,y+20);
    tft.print("pilves");
  }
  else if(condition=="Lauspilvisus" || condition == "Peamiselt pilves"){
    tft.print("Pilves");
  }
  else if(condition=="Vihma võimalus"){
    tft.setCursor(x,y);
    tft.print("Vihma");
    tft.setCursor(x,y+20);
    tft.print("v" + String(char(147))+"imalus");//Täpitähe "õ", printimiseks tuleb see määrata sümbolikoodi abil.
  }
  
  //Kui tegemist pole erijuhtudega...
  else if(condition.length()>6){//Kui ilmaseisundi sõna pikkus on suurem kuuest, muudetakse tekstisuurust väiksemaks.
    tft.setTextSize(2);
    tft.print(condition);}
  else{///Kui ilmaseisundi sõna pikkus on väiksem võrdne kuuest, on teksti suurus 3.
    if(pos==1) tft.setTextSize(3);
    tft.print(condition);
    }
  
  
  //Temperatuuri printimine ekraanile.
  if(pos==3) tft.setCursor(x,y+45); //Kui temperatuuri prinditakse ekraani allaossa, siis tuleb täpsustada koordinaate, et nupp mahuks ära.
  else tft.setCursor(x,y+50); //Kui temperatuuri prinditakse ekraani ülaossa või keskele.
  tft.setTextSize(3);
  tft.print(temp);
  tft.setTextSize(2);
  tft.print(String(char(247))+"C");
}


//Hetke ilmaandmete ekraanile kuvamise funktsioon
void drawData(){
  tft.setTextSize(2);
  clearScreen(); //Puhastatakse ekraan
  
  tft.setTextColor(WHITE); //Tekstivärv valgeks
  drawMainInfo(weatherdata[0],weatherdata[1],110,30,1); //Ilmaseisundi ikooni joonistamine ning ilmaseisundi ja temperatuuri kirjutamine ekraanile.
  
  drawBitmap(150,135,estonia_icon,80,52,GREEN);//Eesti ikooni joonistamine
  drawWindDir();//Tuulesuuna kirjutamine ekraanile ja tuule suuna noole joonistamine Eesti ikoonile.

  //Alljärngev on tuule kiiruse kuvamine ekraanile
  tft.setTextSize(3);
  tft.setCursor(10,180);
  tft.print(weatherdata[4]);
  tft.setTextSize(2);
  tft.print("m/s");
  
  //Alljärgnev on õhuniiskuse kuvamine ekraanile
  tft.setTextSize(3);
  tft.setCursor(10,240);
  tft.print(weatherdata[2]);
  
  //Alljärgnev on õhurõhu kuvamine ekraanile
  tft.setCursor(10,290);
  tft.print(weatherdata[5]);
  tft.setTextSize(2);
  tft.print("hPa");
  tft.setCursor(10,290);
  
  drawBitmap(200,220,air_icon,40,40,CYAN);//Õhu ikooni joonistamine
  
  drawButton("->"); //Ekraanivaadete vahel vahetamise nupu joonistamine
}



//Funktsioont Tuule suuna tekstiliseks kuvamiseks ekraanile ja noole joonistamiseks Eesti ikoonile.
void drawWindDir(){
  uint16_t suund;
  tft.setCursor(10,140);
  suund = weatherdata[3].toInt();
  
  //Alljärgnevalt kontrollitakse, millisesse ilmakaarde tuule suund jääb ja vastavalt sellele prinditakse ekraanile tuulsesuund ja joonistatakse nool Eesti ikoonile
  //Täpitähtede kuvamiseks kasutatakse sümbolikoodi.
  if(suund>338 || suund <=23){
    tft.print("P"+String(char(147)) +"hjatuul");
    tft.drawTriangle(190, 158, 202, 158, 196, 164, GREY);
    }
  else if(suund>23 && suund <=68){
    tft.print("Kirdetuul");
    tft.drawTriangle(206, 164, 197, 155, 197, 164, GREY);
   }
  else if(suund>68 && suund <=113){
    tft.print("Idatuul");
    tft.drawTriangle(200, 162, 200, 150, 191, 156, GREY);
  }
  else if(suund>113 && suund <=158){
    tft.print("Kagutuul");
    tft.drawTriangle(198, 171, 207, 162, 198, 162, GREY);
  }
  else if(suund>158 && suund <=203){
    tft.print("L"+String(char(147))+"unatuul");
    tft.drawTriangle(190, 158, 202, 158, 196, 152, GREY);
  }
  else if(suund>203 && suund <=248){
    tft.print("Edelatuul");
    tft.drawTriangle(206, 164, 197, 155, 206, 155, GREY);

  }
  else if(suund>248 && suund <=293){
    tft.print("L"+String(char(132))+String(char(132))+"netuul");
    tft.drawTriangle(200, 162, 200, 150, 209, 156, GREY);

  }
  else if(suund>293 && suund <=338){
    tft.print("Loodetuul");
    tft.drawTriangle(194, 167, 203, 158, 203, 167, GREY);
  }
}

//Funktsioon ikoonide joonistamiseks
void drawIcon(String icon, uint8_t pos){//Funktsiooni argumenditeks on icon, mis on ikooni nimi ja pos, mis näitab millisesse ekraaniosasse tuleb ikoon joonistada
                                        //pos 1 tähistab ekraani ülaosa, 2 keskosa ja 3 alumist osa.
                                        //Lisaks vaadatakse, kas tuleb kuvada öörežiimi ikoone või päevarežiimi ikoone.
  if(icon=="Osaliselt pilves"){
     uint8_t y;
     if(next_hour>=6 && next_hour <=23 ){//Kontrollitakse, kas hetkel on  päev.
      //Erinevate potitsioonide korral on ikooni alguspunktid erinevates koordinaatides.
      //Postisiooni tuvastamiseks kasutatakse switch/case lauset.
      switch(pos){//pos on väärtus, mida case lausete abil hakatakse otsima.
        case 1:drawSunCloud(40,10);//Kui pos == 1 joonistatakse ikoon ekraani ülemisse poolde.
        break;
        case 2:drawSunCloud(40,130);//Kui pos == 2 joonistatakse ikoon ekraani keskele.
        break;
        case 3:drawSunCloud(40,230);//Kui pos == 3 joonistatakse ikoon ekraani alumisse poolde.
        break;
      }
     }
     else{//Polnud päev järelikult on öö.
     switch(pos){
        case 1:drawSunCloud(90,40);
        break;
        case 2:drawSunCloud(40,130);
        break;
        case 3:drawSunCloud(40,230);
        break;
      }
     }  
   }
  
  else if(icon=="Selge"){
    if(next_hour>=6 && next_hour <=23 ){
      switch(pos){
        case 1:drawSun(20,25);
        break;
        case 2:drawSun(20,140);
        break;
        case 3:drawSun(20,240);
        break;
      }
    }
    else{
      switch(pos){
        case 1:drawMoon(50,50);
        break;
        case 2:drawMoon(50,170);
        break;
        case 3:drawMoon(50,260);
        break;
      }
    }
  }
 else if(icon.indexOf("ihm")>=0){//Vihma kirjeldavaid sõnu on mitu, aga ikoone üks siin kontrollitakse, kas sõna sisaldab "ihm" tähekombinatsiooni. 
                                 //Kui jah, tuleb joonistada vihma ikoon.
  switch(pos){
        case 1:drawRain(20,15);
        break;
        case 2:drawRain(20,130);
        break;
        case 3:drawRain(20,230);
        break;
      }
      }
 
 else if(icon.indexOf("ilv")>0){
  switch(pos){
        case 1:drawCloud(20,15);
        break;
        case 2:drawCloud(20,130);
        break;
        case 3:drawCloud(20,230);
        break;
      }
 }
  else if(icon.indexOf("umi")>0 ||icon.indexOf("kuul")>0 || icon.indexOf("ume")>0){
    switch(pos){
        case 1:drawSnow(20,15);
        break;
        case 2:drawSnow(20,130);
        break;
        case 3:drawSnow(20,230);
        break;
      }
  }
}


//Funktsioon ekraani puhastamiseks ja piirjoonte joonistamisks.
void clearScreen(){
  tft.fillScreen(BLACK);//Taustavärvi seadmine mustaks.
  tft.drawLine(0,120,240,120,WHITE);//Infoeraldusjoone joonistamine
  tft.drawLine(0,220,240,220,WHITE);//Infoeraldusjoone joonistamine
  tft.drawRect(0,0,240,320,WHITE);//Raami joonistamine ümber ekraani
  tft.setTextColor(WHITE);
  

}

//Funktsioon nupu joonistamiseks.
void drawButton(String str){//Argumendiks nupu suund, kas "<-" või "->"
  tft.fillRect(190,290, 45, 20,ORANGE);//Nupuks vajaliku ristküliku joonistamine
  //Järgnevalt valitakse vastavalt suunale sobilik koordinaat ja joonistatakse nupp ristküliku sisse.
  if(str == "->"){
    tft.setCursor(205,293);
  }else if(str =="<-"){
    tft.setCursor(200,293);
  }
    tft.setTextSize(2);
    tft.setTextColor(BLACK);
    tft.print(str);
}


//Funktsioon lume ikooni joonistamisks
void drawSnow(int x, int y){//Argumentideks ikooni x ja y alguspunktid
  drawCloud(x,y);//Joonistatakse pilv.
  //Järgnevalt joonistatakse kuulikesed pilve alla.
  tft.fillCircle(x+15,y+70,5,WHITE);
  tft.fillCircle(x+35,y+70,5,WHITE);
  tft.fillCircle(x+55,y+70,5,WHITE);
}

//Funktsioon päikese ikooni joonistamisks
void drawSun(int x, int y){//Argumentideks ikooni x ja y alguspunktid
  drawBitmap(x,y,sun_icon,65,65,YELLOW);//Päikese ikooni joonistamine.
  }

//Funktsioon, mis joonistab osaliselt pilves ikooni.
void drawSunCloud(int x, int y){//Argumentideks ikooni x ja y alguspunktid
   if(next_hour>=6 && next_hour <=23 ){//Kui hetkel on päev joonistatakse päike.
      drawSun(x,y);
      drawBitmap(x-15,y+10,cloud_icon,60,60,WHITE);
    }
   else{//Kui hetkel on öö joonistatakse kuu
      drawMoon(x,y);//Kuu joonistamise funktsioon.
      drawBitmap(x-70,y-20,cloud_icon,60,60,WHITE);//Pilve joonistamine.
    }
   }

//Funktsioon vihma ikooni joonistamisks
void drawRain(int x, int y){//Argumentideks ikooni x ja y alguspunktid
  drawCloud(x,y);
  //Järgnevalt joonistatakse vihmapiisad pilve alla.
  tft.fillRect(x+15,y+60,3,15,WHITE);
  tft.fillRect(x+35,y+60,3,15,WHITE);
  tft.fillRect(x+55,y+60,3,15,WHITE);
}

//Funktsioon kuu ikooni joonistamisks
void drawMoon(int x, int y){//Argumentideks ikooni x ja y alguspunktid
  tft.fillCircle(x,y,25, GREY);//Halli ringi joonistamine
  tft.fillCircle(x+20,y,25, BLACK);//Musta ringi joonistamine, mis katab pool hallist ringist. Seeläbi moodustub poolkuu ikoon.
}

//Funktsioon pilve ikooni joonistamisks
void drawCloud(int x, int y){//Argumentideks ikooni x ja y alguspunktid
  drawBitmap(x,y,cloud_icon,60,60,WHITE);//Pilve ikooni joonistamine
}

//Funktsioon, mis pärast päringu õnnestumist, algatab andete kuvamise ekraanile.
void req_success(){
    next_hour = weatherdata[6].toInt();//Tunni teisendamine arvuks.
    //Kui ekraan on välja lülitatud, lülitatakse ekraan sisse ja kuvatakse uued andmed ekraanile.
    if(!screenon){
    digitalWrite(10, HIGH);
    tft.begin(37697);
    drawData();
    delay(1000);
    screenon=true;
    screenoff_perm=true;
  }
    else if(screenon) drawData(); //Ekraan oli sisse lülitatud, kuvatakse uued anmed ekraanile.
    //Muudetakse ekraanivaate tõeväärtusi, et nupule vajutades, kuvatakse teist ekraani.
    current_condition=false;
    future_condition=true;
  
}


//Funktsioon ekraani väljalülitamiseks.
void dimm(){
  //Ekraani väljalülitamiseks, muudetakse kõik viigud, millega ekraan ühendatud on, LOW peale, ehk neis on pärast seda 0V.
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(10, LOW);
}

bool getData(){ //Selles funktsioonis ühendatakse Weather Underground rakendusliidesega ja saadetakse päring.
  if(esp.createTCP(adress, 80)){//Ühendatakse Weather Underground rakendusliidesega.
      if(esp.sendSingle(request)){ //Saadetakse päring.
        if(processData()){ //Kutsutakse välja andmete töötlemise funktsioon.
          return true;
        }
       }
     else{
          return false;}
  }
  else{
    return false;
   }
return true;
}

//Selles funktsioonis eraldatakse JSON kujul vastusest ilmateataja jaoks vajalik info.
bool processData(){

  //Muutujad, mis on vajalikud päringu töötluseks
  bool starts=false; //Muutja, mis tuvastab, kas alustada võtmesõna koostamist.
  bool start_answer_capt = false; //Muutuja, mis tuvastab, kas alustada vastuse koostamist.
  String answer="";//Siia salvestatakse läbivaadatavaid võtmeid.
  String result="";//Siia salvestatakse vastus.
  char* keys[] = {"weather","temp_c","relative_humidity","wind_degrees","wind_kph","pressure_mb"};//List, kus on otsitavad võtmesõnad.
  uint16_t nr_captured=0; //Mitu vastust on kätte saadud
  uint8_t nr_c=0; //Muutuja, mis on vajalik järgnevate tundide info jaoks
  uint8_t second_hour=0; 
  uint8_t hours=1;
  char jutu_m='"';
  bool space=false;
  bool gettemp=false;
  
  while (nr_captured<13 ) {//Tsükkel kuni leitakse kõik vajalikud vastused.
    while (Serial.available() > 0 )//Tsükkel, kuni jadaliidesest saab lugeda sümboleid.
    {
      char c = Serial.read();//Loetakse sisse sümbol jadaliidesest.
      //tft.print(c);
    if(c!='\n' && c!='\t' ){ //Kontrollitakse, et sümbol polek tühi rida ega taandrida.
    if(start_answer_capt){//Alustatakse vastuse kogumist.
        if(c==','){ //Kontrollitakse, kas vastus on lõppenud.
        start_answer_capt=false;
        if(result!=""){ //Kontrollitakse, et vastus pole tühisõna.
          weatherdata[nr_captured]=result;//vastus lisatakse vastuste listi.
          nr_captured++;//Suurendatakse saadud vastuste arvu.
          result="";}
        }
        else if(c!=jutu_m && c!='}' && c!=':'){//Kui vastuse kogumumine veel käib, kontrollitakse, et sümbol pole ",} või :.
        if(space){
          space=false;
        }
        else{
        result+=c;//Täiendatakse vastust sümboliga.
        }
      }
    }
    else{
    if(starts){//Alanud on võtmesõna koostamine.
      if(c==jutu_m){//Kui on jõutud võtmesõna lõppu tähistava jutumärgini, lõpetatakse vastuse kogumine.
        starts=false;
        if(answer==keys[nr_c] && nr_c<6){
        nr_c++;
        start_answer_capt=true;
        }
        else if(nr_c>5){//Kui võtmesõnad järjendist on kõik vasted leitud, kogutakse kolm korda järgnevate tundide infot.
      if(answer=="temp"){
        if(nr_c==6 || nr_c==8 || nr_c==10){
        gettemp=true;
        answer="";}
      }
      else if(answer=="metric" && gettemp){
        start_answer_capt=true;
        gettemp=false;
        space=true;
      }
      else if(answer=="condition"){
        if(nr_c==6 || nr_c==8 || nr_c==10){
        start_answer_capt=true;
        space=true;
        }
        nr_c++;
      }
      else if(answer=="hour"){
        if(second_hour==0){
        start_answer_capt=true;
        second_hour++;
        space=true;}
        else{
        second_hour++;
        }
        }
      }
        answer="";
      }
      else{
      answer+=c;
    }
    }
    if(c == jutu_m){
      starts=true;
      }
    }
  }
 }
}
return true;
}

//Funktsioon ikoonide joonistamiseks, listide põhjal, mis on graphics.c failis. 
//Funktsioon pärineb Adafruit_gfx libraryst, kuid ilma koodis uuesti defineerimata, ei tööta see funktsioon projektis kasutatava ekraaniga.
void drawBitmap(int16_t x, int16_t y,
 const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {

  int16_t i, j, byteWidth = (w + 7) / 8;
  uint8_t byte;

  for(j=0; j<h; j++) {
    for(i=0; i<w; i++) {
      if(i & 7) byte <<= 1;
      else      byte   = pgm_read_byte(bitmap + j * byteWidth + i / 8);
      if(byte & 0x80) tft.drawPixel(x+i, y+j, color);
    }
  }
}

