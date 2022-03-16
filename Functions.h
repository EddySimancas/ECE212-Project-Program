#ifndef _Functions_H
#define _Functions_H

void Graph(Adafruit_HX8357 &d, double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, String title, String xlabel, String ylabel, unsigned int gcolor, unsigned int acolor, unsigned int pcolor, unsigned int tcolor, unsigned int bcolor, boolean &redraw) {
  //This function neatly graphs functions or a set of data


  double ydiv, xdiv;
  // initialize old x and old y in order to draw the first point of the graph
  // but save the transformed value
  // note my transform funcition is the same as the map function, except the map uses long and we need doubles
  //static double ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
  //static double oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  double i;
  double temp;
  int rot, newrot;

  if (redraw == true) {

    redraw = false;
    ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
    oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
    // draw y scale
    for ( i = ylo; i <= yhi; i += yinc) {
      // compute the transform
      temp =  (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

      if (i == 0) {
        d.drawLine(gx, temp, gx + w, temp, acolor);
      }
      else {
        d.drawLine(gx, temp, gx + w, temp, gcolor);
      }

      d.setTextSize(1);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(gx - 40, temp);
      // precision is default Arduino--this could really use some format control
      d.println(i);
    }
    // draw x scale
    for (i = xlo; i <= xhi; i += xinc) {

      // compute the transform

      temp =  (i - xlo) * ( w) / (xhi - xlo) + gx;
      if (i == 0) {
        d.drawLine(temp, gy, temp, gy - h, acolor);
      }
      else {
        d.drawLine(temp, gy, temp, gy - h, gcolor);
      }

      d.setTextSize(1);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(temp, gy + 10);
      // precision is default Arduino--this could really use some format control
      d.println(i);
    }

    //now draw the labels
    d.setTextSize(2);
    d.setTextColor(tcolor, bcolor);
    d.setCursor(gx , gy - h - 30);
    d.println(title);

    d.setTextSize(1);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx , gy + 20);
    d.println(xlabel);

    d.setTextSize(1);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx - 30, gy - h - 10);
    d.println(ylabel);


  }

  //graph drawn now plot the data
  // the entire plotting code are these few lines...
  // recall that ox and oy are initialized as static above
  x =  (x - xlo) * ( w) / (xhi - xlo) + gx;
  y =  (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  d.drawLine(ox, oy, x, y, pcolor);
  d.drawLine(ox, oy + 1, x, y + 1, pcolor);
  d.drawLine(ox, oy - 1, x, y - 1, pcolor);
  ox = x;
  oy = y;
  
}

void drawHomeButton(void){
  // This function draws a "home button" and
  // always places it at the bottom right corner
  // of the screen when the function is called.
  // This function also returns four variables
  // called "XMIN_HOME, XMAX_HOME, YMIN_HOME, YMAX_HOME."
  // These four points are the boundry condition the touch screen
  // will use to check if the inside of the rounded rectanlge
  // has been pressed by the user
  
  int radius = 40;
  int centerX = tft.width() - radius - 1; //
  int centerY = tft.height() - radius - 1; //

  int rectCornerX = centerX - 25;
  int rectCornerY = centerY - 19;
  int rectWidth = radius + 10;
  int rectHeight = radius + 10;
  
  int triLeftX = centerX - 35;
  int triLeftY = centerY - 19;

  int triMidX = centerX;
  int triMidY = centerY - 40;
  
  int triRightX = centerX + 35;
  int triRightY = centerY - 19;

  int rectOutlineX = centerX - 10;
  int rectOutlineY = centerY + 11;
  int rectOutlineW = (rectWidth / 2) - 5;
  int rectOutlineH = (rectHeight) / 2;

  int minBorderX = centerX - radius;
  int minBorderY = centerY - radius;
  int maxBorderX = minBorderX + rectWidth;
  int maxBorderY = minBorderY + rectHeight;

  XMIN_HOME = minBorderX;
  XMAX_HOME = maxBorderX;
  YMIN_HOME = minBorderY;
  YMAX_HOME = maxBorderY;

  tft.drawCircle(centerX, centerY, radius, WHITE); // x pos, y pos, radius, color
  tft.fillRect(rectCornerX, rectCornerY, rectWidth, rectHeight, WHITE); // (top left) x pos, y pos, width, height, color
  tft.fillTriangle(triLeftX, triLeftY, triMidX, triMidY, triRightX, triRightY, WHITE); // (x, y) bottom left, (x, y) top, (x,y) bottom right, color
  tft.fillRect(rectOutlineX, rectOutlineY, rectOutlineW, rectOutlineH, BLACK); // door
  tft.drawRect(rectCornerX, rectCornerY, rectWidth, rectHeight, WHITE); // outline
}

void drawSettingsButton(int rotation){
  // This function draws a "settings button" and
  // places it at the bottom left corner
  // of the screen, when the screen is in its vertical
  // settings, (its placed at top right when the screen is
  // in its horizontal settings) whenever the function is called.
  // This function also returns four variables
  // called "XMIN_HOME, XMAX_HOME, YMIN_HOME, YMAX_HOME."
  // These four points are the boundry condition the touch screen
  // will use to check if the inside of the rounded rectanlge
  // has been pressed by the user
  
  int radius = 10;
  int rectCornerX;
  int rectCornerY;
  int rectWidth = 105;
  int rectHeight = 65;

  if(rotation % 2 == 0){ // if even (aka vertical)
    rectCornerX = 10;
    rectCornerY = tft.height() - 70;
  }
  else{
    rectCornerX = tft.width() - rectWidth - 1;
    rectCornerY = 10;
  }

  int cursorLocX = rectCornerX + 5;
  int cursorLocY = rectCornerY + 25;

  XMIN_SET = rectCornerX;
  XMAX_SET = rectCornerX + rectWidth;
  YMIN_SET = rectCornerY;
  YMAX_SET = rectCornerY + rectHeight;
  
  tft.drawRoundRect(rectCornerX, rectCornerY, rectWidth, rectHeight, radius, WHITE); // 0, 410, 105, 65
  tft.setCursor(cursorLocX, cursorLocY); tft.setTextSize(2); tft.setTextColor(WHITE, BLACK); // 5, 435
  tft.print("SETTINGS");
}

void drawSquicle(int locX, int locY, String textName, int &xmin, int &xmax, int &ymin, int &ymax){
  // This functions draws a rounded rectangle at any
  // location, starting at the top left corner denoted
  // by the point "(locX, locY)" and returns four
  // points. The four points "xmin, xmax, ymin, ymax" are
  // the boundry condition the touch screen will use to
  // check if the inside of the rounded rectanlge
  // has been pressed by the user
  
  int width = (textName.length()) *3*6;
  int height = 60;
  int radius = 10;

  int cursorLocX = locX + (textName.length())*3;
  int cursorLocY = locY + 24;

  xmin = locX;
  xmax = locX + width;
  ymin = locY;
  ymax = locY + height;
  
  tft.drawRoundRect(locX, locY, width, height, radius, WHITE); // x, y, w, h, r, color
  tft.setCursor(cursorLocX, cursorLocY); tft.setTextSize(2); tft.setTextColor(WHITE, BLACK);
  tft.print(textName);
  
}

void setTouchPoints(int rotation){
  // This function sets the touch screen setting
  // to recieve proper input from presses.
  
  // Retrieve a point  
  TS_Point p = ts.getPoint();
  
  // Scale from ~0->4000 to tft.width using the calibration #'s
  // the scale depended on the rotation varibale, which decided the landscape of the screen
  if(rotation == 0){
    p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0); // tft.width(), 0);
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
    y = p.y;
    x = p.x;
  }
  else if (rotation == 1){
    p.x = map(p.x, TS_MINY, TS_MAXY, tft.height(), 0);
    p.y = map(p.y, TS_MINX, TS_MAXX, tft.width(), 0);
    y = p.x;
    x = p.y;
  }
  else if (rotation == 2){
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
    y = p.y;
    x = p.x;
  }
  else if (rotation == 3){
    p.x = map(p.x, TS_MINY, TS_MAXY, 0, tft.height());
    p.y = map(p.y, TS_MINX, TS_MAXX, 0, tft.width());
    y = p.x;
    x = p.y;
  }

  if(y < 0){
    y = 0;
  }
  if(x < 0){
    x = 0;
  }

  // uncomment lines below to aid in debugging the touch screen
  //Serial.print("X = "); Serial.print(x); Serial.print("\tY = "); Serial.print(y);  Serial.print("\tPressure = "); Serial.println(p.z); 
  //delay(500);
}

void clearBuffer(void){
  // this function clears the recent stored data
  // from the touchscreen buffer
  
  TS_Point p = ts.getPoint();
  p = ts.getPoint();
}

void beginSetUp(void){
  // This function calls all the function
  // needed to set up the serial monitor,
  // the touchscreen, Wi-Fi, spg30 snensor, DHT11 sensor, and tft display.
  
  Serial.begin(115200);

  // touchscreen set up
  Serial.println("HX8357D Test!");
  if (!ts.begin()) {
    Serial.println("Couldn't start touchscreen controller");
    while (1);
  }
  Serial.println("Touchscreen started");
  tft.begin();
  tft.fillScreen(BLACK);

  // graph set up
  tft.setRotation(2);
  a1 = 3.354016E-03 ;
  b1 = 2.569850E-04 ;
  c1 = 2.620131E-06 ;
  d1 = 6.383091E-08 ;
  tft.setRotation(rotation); 

  // sgp30 set up -------------------------------
  Serial.println("SGP30 test");     //  Print message in the Serial Monitor
  if (! sgp.begin())                //  Check if the connection to the sensor was NOT successful.
  {
    Serial.println("Sensor not found :(");
  }

  // DHT11 set up -------------------------------
  Serial.println("DHT11 sensor!");
  //call begin to start sensor
  dht.begin();

  // LED pins set up ------------------------
  ledcAttachPin(ledR, 1); // assign RGB led pins to channels
  ledcAttachPin(ledG, 2);
  ledcAttachPin(ledB, 3);

  ledcSetup(1, 1000, 8); // 1 kHz PWM, 8-bit resolution
  ledcSetup(2, 1000, 8);
  ledcSetup(3, 1000, 8);

  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, 0);

  // Buzzer pin set up ------------------------
  pinMode(buzzerPin, OUTPUT);

  // Wi-Fi set up
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  //get string data on the server
  server.on("/fanSpeed", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", fanSpeed().c_str());
  });
  // Start server
  server.begin();

}

void graphData(int rotation, int dataArray[], String titleName, String xName, String yName){
  // This function uses the original graphing function but
  // it is used to graph the data gathered from the sensors
  
  int maxDataValue = dataArray[0];
  int originX = 50;
  int originY;
  int width;
  int height;
  int lowerDomain;
  int upperDomain;
  int deltaX;
  int lowerRange;
  int upperRange;
  int deltaY;
  
  for(int i = 0; i < 24; i++){
    if(maxDataValue < dataArray[i]){
      maxDataValue = dataArray[i];
    }
  }
  
  if(rotation % 2 == 0){
    originX = 50;
    originY = 440;
    width = 240;
    height = 400;
    lowerDomain = 0;
    upperDomain = 23;
    deltaX = 4;
    lowerRange = 0;
    upperRange = ceil(maxDataValue*1.25);
    deltaY = ceil(upperRange/4);
  }
  else{
    originX = 50;
    originY = 280;
    width = 410;
    height = 240;
    lowerDomain = 0;
    upperDomain = 23;
    deltaX = 4;
    lowerRange = 0;
    upperRange = ceil(maxDataValue*1.25);
    deltaY = ceil(upperRange/4);
  }
  
  tft.fillScreen(BLACK); 
  for (nx = 0; nx < 24; nx += 1) {
    
    ny = dataArray[(int) nx];
    
    Graph(tft, nx, ny, originX, originY, width, height, lowerDomain, upperDomain, deltaX, lowerRange, upperRange, deltaY, titleName, xName, yName, DKCYAN, DKCYAN, MAGENTA, WHITE, BLACK, display1);
    delay(50);
  }
  nx = 0;
  ny = 0;
  display1 = true;
  while(1){
    if(ts.touched()){
      break;
    }
  }
  
}

int buttonIsPressed(int xmin, int xmax, int ymin, int ymax){
  // this function checks to see if the
  // the user pressed the touchscreen
  // within the boundaries of any given button
  
  if(ymin < y && y < ymax){
    if(xmin < x && x < xmax){
      // wait until user lets go off of screen
      while(1){
        if(!ts.touched()){
          break;
        }
      }
      return 1;
    }
  }

  return 0;
}

void homeScreen(int rotation){
  // This function draws the homescreen of the touchscreen.
  // The homescreen consist of 6 buttons (CO2, TVOC, TEMP, HUMID, Settings, Home)
  // and displays the current values of the four sensors

  tft.fillScreen(BLACK);
  int locX = 10;
  int locY = 10;
  int downShift = 0;
  if(rotation % 2 == 0){ // if even (aka vertical)
    downShift = 80;
  }
  else{
    downShift = 65;
  }
  
  drawHomeButton();
  drawSettingsButton(rotation);
  drawSquicle(locX, locY, "eCO2", XMIN_eCO2, XMAX_eCO2, YMIN_eCO2, YMAX_eCO2);
  drawSquicle(locX, (locY + downShift), "TVOC", XMIN_TVOC, XMAX_TVOC, YMIN_TVOC, YMAX_TVOC);
  drawSquicle(locX, (locY + downShift*2), "TEMP", XMIN_TEMP, XMAX_TEMP, YMIN_TEMP, YMAX_TEMP);
  drawSquicle(locX, (locY + downShift*3), "HUMID", XMIN_HUMID, XMAX_HUMID, YMIN_HUMID, YMAX_HUMID);

  tft.setCursor((XMAX_eCO2 + 20), (YMIN_eCO2 + 24) ); tft.setTextSize(2); tft.setTextColor(WHITE, BLACK);
  tft.print("eCO2:         ppm");
  tft.setCursor((XMAX_TVOC + 20), (YMIN_TVOC + 24) );
  tft.print("TVOC:         ppb");
  tft.setCursor((XMAX_TEMP + 20), (YMIN_TEMP + 24) );
  tft.print("Temperature:    F");
  tft.setCursor((XMAX_HUMID + 20), (YMIN_HUMID + 24) );
  tft.print("Humidity:    %rh");

}

void settingsScreen(){
  // this function displays the settings screen
  
  tft.fillScreen(BLACK);
  tft.setCursor(0, 0); tft.setTextSize(2); tft.setTextColor(WHITE);
  tft.print("Settings menu");
  int locX = 10;
  int locY = 65;
  int downShift = 0;
  if(rotation % 2 == 0){ // if even (aka vertical)
    downShift = 80;
  }
  else{
    downShift = 65;
  }
  drawSquicle(locX, locY, "CO2 range", XMIN_B1, XMAX_B1, YMIN_B1, YMAX_B1);
  drawSquicle(locX, locY + downShift, "VOC range", XMIN_B2, XMAX_B2, YMIN_B2, YMAX_B2);
  drawHomeButton();
}

void eCO2Settings(void){
  // this function displays the CO2 settings screen
  
  int locX = 10;
  int locY = 20;
  int downShift = 0;
  if(rotation % 2 == 0){
    downShift = 80;
  }
  else{
    downShift = 65;
  }

  while(1){
    tft.fillScreen(BLACK);
    drawHomeButton();
    drawSquicle(locX, (tft.height() - 65), "Back", XMIN_B1, XMAX_B1, YMIN_B1, YMAX_B1);
    tft.setCursor(0, 0); tft.setTextSize(2); tft.setTextColor(WHITE);
    tft.print("Here you can change the\n"); tft.print("eCO2");
    tft.print(" range at which this\ndevice will notify you\n");
    tft.print("\nChoose which range you\nwould like to edit");
    drawSquicle(locX, (locY + downShift), "Healthy", XMIN_B2, XMAX_B2, YMIN_B2, YMAX_B2);
    drawSquicle(locX, (locY + downShift*2), "Warning", XMIN_B3, XMAX_B3, YMIN_B3, YMAX_B3);
    drawSquicle(locX, (locY + downShift*3), "Hazard", XMIN_B4, XMAX_B4, YMIN_B4, YMAX_B4);
    while(1){
      setTouchPoints(rotation);
      if(buttonIsPressed(XMIN_HOME, XMAX_HOME, YMIN_HOME, YMAX_HOME)){
        break;
      }
      if(buttonIsPressed(XMIN_B1, XMAX_B1, YMIN_B1, YMAX_B1)){
        break;
      }
      if(buttonIsPressed(XMIN_B2, XMAX_B2, YMIN_B2, YMAX_B2)){
        clearBuffer();
        tft.fillScreen(BLACK);
        tft.setCursor(0, 0); tft.setTextSize(2); tft.setTextColor(WHITE, BLACK);
        tft.print("Lower Value: 0\n");
        tft.print("Upper Value: ");
        drawHomeButton();
        drawSquicle(locX, (tft.height() - 65), "Back", XMIN_B1, XMAX_B1, YMIN_B1, YMAX_B1);
        drawSquicle(locX, (locY + downShift), "Decrease", XMIN_B2, XMAX_B2, YMIN_B2, YMAX_B2);
        drawSquicle(locX, (locY + downShift*2), "Increase", XMIN_B3, XMAX_B3, YMIN_B3, YMAX_B3);
        while(1){
          tft.setCursor(150, 15); tft.setTextSize(2); tft.setTextColor(WHITE, BLACK);
          tft.print(CO2minUpper); tft.print("     ");
          setTouchPoints(rotation);
          if(buttonIsPressed(XMIN_HOME, XMAX_HOME, YMIN_HOME, YMAX_HOME)){
            break;
          }
          if(buttonIsPressed(XMIN_B1, XMAX_B1, YMIN_B1, YMAX_B1)){
            break;
          }
          if(buttonIsPressed(XMIN_B2, XMAX_B2, YMIN_B2, YMAX_B2)){
            CO2minUpper = CO2minUpper - 100;
            if(CO2minUpper <= 400){
              CO2minUpper = 400;
            }
            CO2midLower = CO2minUpper;
          }
          if(buttonIsPressed(XMIN_B3, XMAX_B3, YMIN_B3, YMAX_B3)){
            CO2minUpper = CO2minUpper + 100;
            if(CO2minUpper > 2000){
              CO2minUpper = 2000;
            }
            CO2midLower = CO2minUpper;
          }
          
        }
        
      }
      if(buttonIsPressed(XMIN_B3, XMAX_B3, YMIN_B3, YMAX_B3)){
        clearBuffer();
        tft.fillScreen(BLACK);
        tft.setCursor(0, 0); tft.setTextSize(2); tft.setTextColor(WHITE, BLACK);
        tft.print("Lower Value: "); tft.print(CO2midLower);
        tft.print("\nUpper Value: ");
        drawHomeButton();
        drawSquicle(locX, (tft.height() - 65), "Back", XMIN_B1, XMAX_B1, YMIN_B1, YMAX_B1);
        drawSquicle(locX, (locY + downShift), "Decrease", XMIN_B2, XMAX_B2, YMIN_B2, YMAX_B2);
        drawSquicle(locX, (locY + downShift*2), "Increase", XMIN_B3, XMAX_B3, YMIN_B3, YMAX_B3);
        while(1){
          tft.setCursor(150, 15); tft.setTextSize(2); tft.setTextColor(WHITE, BLACK);
          tft.print(CO2midUpper); tft.print("     ");
          setTouchPoints(rotation);
          if(buttonIsPressed(XMIN_HOME, XMAX_HOME, YMIN_HOME, YMAX_HOME)){
            break;
          }
          if(buttonIsPressed(XMIN_B1, XMAX_B1, YMIN_B1, YMAX_B1)){
            break;
          }
          if(buttonIsPressed(XMIN_B2, XMAX_B2, YMIN_B2, YMAX_B2)){
            CO2midUpper = CO2midUpper - 1000;
            if(CO2midUpper <= (CO2midLower + 1000)){
              CO2midUpper = (CO2midLower + 1000);
            }
            CO2maxLower = CO2midUpper;
          }
          if(buttonIsPressed(XMIN_B3, XMAX_B3, YMIN_B3, YMAX_B3)){
            CO2midUpper = CO2midUpper + 1000;
            if(CO2midUpper > 10000){
              CO2midUpper = 10000;
            }
            CO2maxLower = CO2midUpper;
          }
        }
        
      }
      if(buttonIsPressed(XMIN_B4, XMAX_B4, YMIN_B4, YMAX_B4)){
        clearBuffer();
        tft.fillScreen(BLACK);
        tft.setCursor(0, 0); tft.setTextSize(2); tft.setTextColor(WHITE, BLACK);
        tft.print("Lower Value: "); tft.print(CO2maxLower);
        tft.print("\nUpper Value: ");
        drawHomeButton();
        drawSquicle(locX, (tft.height() - 65), "Back", XMIN_B1, XMAX_B1, YMIN_B1, YMAX_B1);
        drawSquicle(locX, (locY + downShift), "Decrease", XMIN_B2, XMAX_B2, YMIN_B2, YMAX_B2);
        drawSquicle(locX, (locY + downShift*2), "Increase", XMIN_B3, XMAX_B3, YMIN_B3, YMAX_B3);
        while(1){
          tft.setCursor(150, 15); tft.setTextSize(2); tft.setTextColor(WHITE, BLACK);
          tft.print(CO2maxUpper); tft.print("     ");
          setTouchPoints(rotation);
          if(buttonIsPressed(XMIN_HOME, XMAX_HOME, YMIN_HOME, YMAX_HOME)){
            break;
          }
          if(buttonIsPressed(XMIN_B1, XMAX_B1, YMIN_B1, YMAX_B1)){
            break;
          }
          if(buttonIsPressed(XMIN_B2, XMAX_B2, YMIN_B2, YMAX_B2)){
            CO2maxUpper = CO2maxUpper - 1000;
            if(CO2maxUpper <= (CO2maxLower + 1000)){
              CO2maxUpper = (CO2maxLower + 1000);
            }
          }
          if(buttonIsPressed(XMIN_B3, XMAX_B3, YMIN_B3, YMAX_B3)){
            CO2maxUpper = CO2maxUpper + 1000;
            if(CO2maxUpper > 50000){
              CO2maxUpper = 50000;
            }
          }
        }
        
      }

      // error checking
      if(CO2midUpper <= (CO2midLower + 1000)){
        CO2midUpper = (CO2midLower + 1000);
      }
      if(CO2maxUpper <= (CO2maxLower + 1000)){
        CO2maxUpper = (CO2maxLower + 1000);
      }
      
    }
    if(buttonIsPressed(XMIN_HOME, XMAX_HOME, YMIN_HOME, YMAX_HOME)){
      break;
    }
    setTouchPoints(rotation);
    if(buttonIsPressed(XMIN_B1, XMAX_B1, YMIN_B1, YMAX_B1)){
      break;
    }
    clearBuffer();
  }

}

void TVOCSettings(void){
  // this function displays the TVOC settings screen
  
  int locX = 10;
  int locY = 20;
  int downShift = 0;
  if(rotation % 2 == 0){
    downShift = 80;
  }
  else{
    downShift = 65;
  }

  while(1){
    tft.fillScreen(BLACK);
    drawHomeButton();
    drawSquicle(locX, (tft.height() - 65), "Back", XMIN_B1, XMAX_B1, YMIN_B1, YMAX_B1);
    tft.setCursor(0, 0); tft.setTextSize(2); tft.setTextColor(WHITE);
    tft.print("Here you can change the\n"); tft.print("TVOC");
    tft.print(" range at which this\ndevice will notify you\n");
    tft.print("\nChoose which range you\nwould like to edit");
    drawSquicle(locX, (locY + downShift), "Healthy", XMIN_B2, XMAX_B2, YMIN_B2, YMAX_B2);
    drawSquicle(locX, (locY + downShift*2), "Warning", XMIN_B3, XMAX_B3, YMIN_B3, YMAX_B3);
    drawSquicle(locX, (locY + downShift*3), "Hazard", XMIN_B4, XMAX_B4, YMIN_B4, YMAX_B4);
    while(1){
      setTouchPoints(rotation);
      if(buttonIsPressed(XMIN_HOME, XMAX_HOME, YMIN_HOME, YMAX_HOME)){
        break;
      }
      if(buttonIsPressed(XMIN_B1, XMAX_B1, YMIN_B1, YMAX_B1)){
        break;
      }
      if(buttonIsPressed(XMIN_B2, XMAX_B2, YMIN_B2, YMAX_B2)){
        clearBuffer();
        tft.fillScreen(BLACK);
        tft.setCursor(0, 0); tft.setTextSize(2); tft.setTextColor(WHITE, BLACK);
        tft.print("Lower Value: 0\n");
        tft.print("Upper Value: ");
        drawHomeButton();
        drawSquicle(locX, (tft.height() - 65), "Back", XMIN_B1, XMAX_B1, YMIN_B1, YMAX_B1);
        drawSquicle(locX, (locY + downShift), "Decrease", XMIN_B2, XMAX_B2, YMIN_B2, YMAX_B2);
        drawSquicle(locX, (locY + downShift*2), "Increase", XMIN_B3, XMAX_B3, YMIN_B3, YMAX_B3);
        while(1){
          tft.setCursor(150, 15); tft.setTextSize(2); tft.setTextColor(WHITE, BLACK);
          tft.print(TVOCminUpper); tft.print("     ");
          setTouchPoints(rotation);
          if(buttonIsPressed(XMIN_HOME, XMAX_HOME, YMIN_HOME, YMAX_HOME)){
            break;
          }
          if(buttonIsPressed(XMIN_B1, XMAX_B1, YMIN_B1, YMAX_B1)){
            break;
          }
          if(buttonIsPressed(XMIN_B2, XMAX_B2, YMIN_B2, YMAX_B2)){
            TVOCminUpper = TVOCminUpper - 10;
            if(TVOCminUpper <= 20){
              TVOCminUpper = 20;
            }
            TVOCmidLower = TVOCminUpper;
          }
          if(buttonIsPressed(XMIN_B3, XMAX_B3, YMIN_B3, YMAX_B3)){
            TVOCminUpper = TVOCminUpper + 10;
            if(TVOCminUpper > 110){
              TVOCminUpper = 110;
            }
            TVOCmidLower = TVOCminUpper;
          }
          
        }
        
      }
      if(buttonIsPressed(XMIN_B3, XMAX_B3, YMIN_B3, YMAX_B3)){
        clearBuffer();
        tft.fillScreen(BLACK);
        tft.setCursor(0, 0); tft.setTextSize(2); tft.setTextColor(WHITE, BLACK);
        tft.print("Lower Value: "); tft.print(TVOCmidLower);
        tft.print("\nUpper Value: ");
        drawHomeButton();
        drawSquicle(locX, (tft.height() - 65), "Back", XMIN_B1, XMAX_B1, YMIN_B1, YMAX_B1);
        drawSquicle(locX, (locY + downShift), "Decrease", XMIN_B2, XMAX_B2, YMIN_B2, YMAX_B2);
        drawSquicle(locX, (locY + downShift*2), "Increase", XMIN_B3, XMAX_B3, YMIN_B3, YMAX_B3);
        while(1){
          tft.setCursor(150, 15); tft.setTextSize(2); tft.setTextColor(WHITE, BLACK);
          tft.print(TVOCmidUpper); tft.print("     ");
          setTouchPoints(rotation);
          if(buttonIsPressed(XMIN_HOME, XMAX_HOME, YMIN_HOME, YMAX_HOME)){
            break;
          }
          if(buttonIsPressed(XMIN_B1, XMAX_B1, YMIN_B1, YMAX_B1)){
            break;
          }
          if(buttonIsPressed(XMIN_B2, XMAX_B2, YMIN_B2, YMAX_B2)){
            TVOCmidUpper = TVOCmidUpper - 10;
            if(TVOCmidUpper <= (TVOCmidLower + 10)){
              TVOCmidUpper = (TVOCmidLower + 10);
            }
            TVOCmaxLower = TVOCmidUpper;
          }
          if(buttonIsPressed(XMIN_B3, XMAX_B3, YMIN_B3, YMAX_B3)){
            TVOCmidUpper = TVOCmidUpper + 10;
            if(TVOCmidUpper > 500){
              TVOCmidUpper = 500;
            }
            TVOCmaxLower = TVOCmidUpper;
          }
        }
        
      }
      if(buttonIsPressed(XMIN_B4, XMAX_B4, YMIN_B4, YMAX_B4)){
        clearBuffer();
        tft.fillScreen(BLACK);
        tft.setCursor(0, 0); tft.setTextSize(2); tft.setTextColor(WHITE, BLACK);
        tft.print("Lower Value: "); tft.print(TVOCmaxLower);
        tft.print("\nUpper Value: ");
        drawHomeButton();
        drawSquicle(locX, (tft.height() - 65), "Back", XMIN_B1, XMAX_B1, YMIN_B1, YMAX_B1);
        drawSquicle(locX, (locY + downShift), "Decrease", XMIN_B2, XMAX_B2, YMIN_B2, YMAX_B2);
        drawSquicle(locX, (locY + downShift*2), "Increase", XMIN_B3, XMAX_B3, YMIN_B3, YMAX_B3);
        while(1){
          tft.setCursor(150, 15); tft.setTextSize(2); tft.setTextColor(WHITE, BLACK);
          tft.print(TVOCmaxUpper); tft.print("     ");
          setTouchPoints(rotation);
          if(buttonIsPressed(XMIN_HOME, XMAX_HOME, YMIN_HOME, YMAX_HOME)){
            break;
          }
          if(buttonIsPressed(XMIN_B1, XMAX_B1, YMIN_B1, YMAX_B1)){
            break;
          }
          if(buttonIsPressed(XMIN_B2, XMAX_B2, YMIN_B2, YMAX_B2)){
            TVOCmaxUpper = TVOCmaxUpper - 100;
            if(TVOCmaxUpper <= (TVOCmaxLower + 100)){
              TVOCmaxUpper = (TVOCmaxLower + 100);
            }
          }
          if(buttonIsPressed(XMIN_B3, XMAX_B3, YMIN_B3, YMAX_B3)){
            TVOCmaxUpper = TVOCmaxUpper + 100;
            if(TVOCmaxUpper > 3000){
              TVOCmaxUpper = 3000;
            }
          }
        }
        
      }

      // error checking
      if(TVOCmidUpper <= (TVOCmidLower + 10)){
        TVOCmidUpper = (TVOCmidLower + 10);
      }
      if(TVOCmaxUpper <= (TVOCmaxLower + 100)){
        TVOCmaxUpper = (TVOCmaxLower + 100);
      }
      
    }
    if(buttonIsPressed(XMIN_HOME, XMAX_HOME, YMIN_HOME, YMAX_HOME)){
      break;
    }
    setTouchPoints(rotation);
    if(buttonIsPressed(XMIN_B1, XMAX_B1, YMIN_B1, YMAX_B1)){
      break;
    }
    clearBuffer();
  }

}

void updateArray(int dataArray[]){
  // this function shifts any given array
  
  int oldValues[23] = {0};

  // make a copy of the array
  for(int i = 0; i < 24; i++){
    oldValues[i] = dataArray[i];
  }
  // upload the old values (ofset by one) back to the original array
  // this is effectivly shifting all the values of the array to the left by one
  for(int j = 1; j < 24; j++){
    dataArray[j-1] = oldValues[j];
  }
}

void displaySensorValues(float humid, float temp){
  // this function displays the sensor values on the screen
  
  // Check if taking the measurement failed
  if (! sgp.IAQmeasure()){
    Serial.println("Measurement failed");
  }

  // Check if any reads failed and exit early (to try again).
  if (isnan(humid) || isnan(temp)) {
  Serial.println("Failed to read from DHT sensor!");
  }
  
  tft.setCursor((XMAX_eCO2 + 90), (YMIN_eCO2 + 24) ); tft.setTextSize(2); tft.setTextColor(WHITE, BLACK);
  tft.print(sgp.eCO2); tft.print(" ");
  tft.setCursor((XMAX_TVOC + 90), (YMIN_TVOC + 24) );
  tft.print(sgp.TVOC); tft.print(" ");
  tft.setCursor((XMAX_TEMP + 170), (YMIN_TEMP + 24) );
  tft.print((int)temp); tft.print(" ");
  tft.setCursor((XMAX_HUMID + 140), (YMIN_HUMID + 24) );
  tft.print((int)humid); tft.print(" ");
  
  delay(150);
  
  if ( (CO2minLower < sgp.eCO2 && sgp.eCO2 < CO2minUpper) && (TVOCminLower < sgp.TVOC && sgp.TVOC < TVOCminUpper) ){
    ledcWrite(1, 0);
    ledcWrite(2, 255); // turn on green LED and turn others off
    ledcWrite(3, 0);
    digitalWrite(buzzerPin, LOW); // turn off buzzer

    fan_speed = 0; // turn off the filtration system
  }
  if ( (CO2midLower < sgp.eCO2 && sgp.eCO2 < CO2midUpper) || (TVOCmidLower < sgp.TVOC && sgp.TVOC < TVOCmidUpper) ){
    ledcWrite(1, 255);
    ledcWrite(2, 165); // turn on orange LED
    ledcWrite(3, 0);
    digitalWrite(buzzerPin, LOW); // turn off buzzer

    fan_speed = 1; // turn on filtration system on low
  }
  if ( (CO2maxLower < sgp.eCO2 && sgp.eCO2 < CO2maxUpper) || (TVOCmaxLower < sgp.TVOC && sgp.TVOC < TVOCmaxUpper) ){
    ledcWrite(1, 255);  // turn on red LED and turn others off
    ledcWrite(2, 0); 
    ledcWrite(3, 0);
    digitalWrite(buzzerPin, HIGH); // turn on buzzer

    fan_speed = 2; // turn on filtration system on high
  }
  
}

#endif
