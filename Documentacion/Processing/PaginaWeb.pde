import processing.serial.*;
import java.util.*;

// =======================
// VARIABLES DE SENSORES
// =======================
float tempA = 0;
float humA  = 0;
float hTi   = 0;
float pH    = 0;
float o2    = 0;
float gas   = 0;
float vBat  = 0;
int vBatPct = 0;

// =======================
// HISTORIAL PARA GRAFICOS
// =======================
int historialMax = 100;
float[] histTempA = new float[historialMax];
float[] histHumA  = new float[historialMax];
float[] histHTi   = new float[historialMax];
float[] histPH    = new float[historialMax];
float[] histO2    = new float[historialMax];
float[] histGas   = new float[historialMax];
float[] histVBat  = new float[historialMax];
float[] histVBatPct = new float[historialMax];

String graficoActivo = "";

// =======================
// SERIAL
// =======================
Serial puerto;

// =======================
// FUENTES
// =======================
PFont fontTitulo;
PFont fontTexto;

// =======================
// VARIABLES DE GUARDADO
// =======================
int intervaloHora = 3600 * 1000; // 1 hora en milisegundos
int ultimoGuardado = 0;
PrintWriter archivoDatos;

// =======================
// ESPACIADO TARJETAS (GLOBAL)
// =======================
float spacingX;       // Espaciado uniforme entre etiquetas
float yFila1;
float yFila2;

void setup() {
  fullScreen();
  smooth();

  fontTitulo = createFont("Arial-Bold", 50);
  fontTexto  = createFont("Arial", 20);
  textAlign(CENTER, CENTER);

  println("Puertos disponibles:");
  printArray(Serial.list());

  puerto = new Serial(this, Serial.list()[0], 9600);
  puerto.bufferUntil('\n');

  // Crear/abrir archivo CSV
  archivoDatos = createWriter("datos_sensores.csv");
  archivoDatos.println("Hora,TempA,Gas,HumA,HTi,pH,O2,VBat,VBatPct");
  archivoDatos.flush();

  // =======================
  // CONFIGURACIÓN ESPACIADO TARJETAS
  // =======================
  spacingX = width / 6.0;  // Espaciado horizontal
  yFila1 = height * 0.3;
  yFila2 = height * 0.62;  // Las etiquetas de abajo un poco más abajo
}

void draw() {

  // Actualizar historiales
  actualizarHistorial(histTempA, tempA);
  actualizarHistorial(histHumA, humA);
  actualizarHistorial(histHTi, hTi);
  actualizarHistorial(histPH, pH);
  actualizarHistorial(histO2, o2);
  actualizarHistorial(histGas, gas);
  actualizarHistorial(histVBat, vBat);
  actualizarHistorial(histVBatPct, vBatPct);

  // Guardado automático cada hora
  if (millis() - ultimoGuardado >= intervaloHora) {
    guardarDatos();
    ultimoGuardado = millis();
  }

  // Si hay gráfico activo, dibujarlo
  if (!graficoActivo.equals("")) {
    dibujarGrafico(graficoActivo);
    return;
  }

  // Dashboard
  fondoGradiente();
  dibujarHeader();

  // =======================
  // FILA SUPERIOR (4 TARJETAS)
  // =======================
  tarjetaTemperatura((int)(width/2 - spacingX*1.5), (int)yFila1, tempA);
  tarjetaHumedadAire((int)(width/2 - spacingX*0.5), (int)yFila1, humA);
  tarjetaHumedadTierra((int)(width/2 + spacingX*0.5), (int)yFila1, hTi);
  tarjetaPH((int)(width/2 + spacingX*1.5), (int)yFila1, pH);

  // FILA INFERIOR (4 TARJETAS)
  tarjetaO2((int)(width/2 - spacingX*1.5), (int)yFila2, o2);
  tarjetaGas((int)(width/2 - spacingX*0.5), (int)yFila2, gas);
  tarjetaVBat((int)(width/2 + spacingX*0.5), (int)yFila2, vBat);
  tarjetaVBatPct((int)(width/2 + spacingX*1.5), (int)yFila2, vBatPct);

  // Fecha y hora arriba a la derecha
  fill(255);
  textFont(fontTexto);
  textAlign(RIGHT, TOP);
  String hora = nf(hour(),2)+":"+nf(minute(),2)+":"+nf(second(),2);
  String fecha = nf(day(),2)+"/"+nf(month(),2)+"/"+year();
  text(fecha+" "+hora, width-20, 20);
  textAlign(CENTER, CENTER);
}

// =======================
// HEADER
// =======================
void dibujarHeader() {
  fill(255);
  textFont(fontTitulo);
  text("EcoFlow Systems", width/2, height*0.06);

  textFont(fontTexto);
  fill(200);
  text("Environmental Monitoring Dashboard", width/2, height*0.12);
}

// =======================
// BASE TARJETA
// =======================
void baseTarjeta(int x, int y) {
  int w = 200, h = 220;
  noStroke();
  fill(0, 60);
  rect(x-w/2+5, y+5, w, h, 20);
  fill(40, 60, 80);
  rect(x-w/2, y, w, h, 20);
}

// =======================
// TARJETAS
// =======================
void tarjetaTemperatura(int x, int y, float v) {
  baseTarjeta(x,y);
  drawThermometer(x, y+50, v);
  fill(255);
  text("TEMPERATURA AIRE", x, y+95);
  textSize(26);
  text(nf(v,1,1)+" °C", x, y+145);
}

void tarjetaHumedadAire(int x, int y, float v) {
  baseTarjeta(x,y);
  drawWaterDrop(x,y+50);
  fill(255);
  text("HUMEDAD AIRE", x, y+95);
  textSize(26);
  text(nf(v,1,1)+" %", x, y+145);
}

void tarjetaHumedadTierra(int x, int y, float v) {
  baseTarjeta(x,y);
  drawPlant(x,y+50);
  fill(255);
  text("HUMEDAD TIERRA", x, y+95);
  textSize(26);
  text(nf(v,1,1)+" %", x, y+145);
}

void tarjetaPH(int x, int y, float v) {
  baseTarjeta(x,y);
  drawFlask(x,y+50);
  fill(255);
  text("PH", x, y+95);
  textSize(26);
  text(nf(v,1,2), x, y+145);
}

void tarjetaO2(int x, int y, float v) {
  baseTarjeta(x,y);
  drawLungs(x,y+50);
  fill(255);
  text("O2", x, y+105);
  textSize(26);
  text(nf(v,1,1)+" %", x, y+145);
}

void tarjetaGas(int x, int y, float v) {
  baseTarjeta(x,y);
  drawCloud(x,y+50);
  fill(255);
  text("GAS", x, y+105);
  textSize(26);
  text(nf(v,0,0)+" %", x, y+145);
}

void tarjetaVBat(int x, int y, float v) {
  baseTarjeta(x,y);
  fill(255,255,100);
  rect(x-25, y, 50, 50, 8);
  fill(255);
  text("VOLTAJE", x, y+95);
  textSize(26);
  text(nf(v,1,2)+" V", x, y+125);
}

void tarjetaVBatPct(int x, int y, int pct) {
  baseTarjeta(x,y);
  fill(255,255,100);
  rect(x-25, y, 50, 50, 8);
  fill(255);
  text("ESTADO", x, y+95);
  textSize(26);
  text(pct+" %", x, y+125);
}

// =======================
// ICONOS
// =======================
void drawThermometer(float x,float y,float v){
  fill(255,80,80);
  rect(x-6,y-30,12,60,6);
  ellipse(x,y+30,26,26);
}
void drawWaterDrop(float x,float y){
  fill(80,160,255);
  beginShape();
  vertex(x,y-30);
  bezierVertex(x-14,y-8,x-10,y+18,x,y+30);
  bezierVertex(x+10,y+18,x+14,y-8,x,y-30);
  endShape(CLOSE);
}
void drawPlant(float x,float y){
  fill(100,200,100);
  triangle(x,y-25,x-15,y+15,x+15,y+15);
}
void drawFlask(float x,float y){
  fill(255,255,150);
  triangle(x-12,y+15,x+12,y+15,x,y-25);
}
void drawLungs(float x,float y){
  fill(150,255,255);
  ellipse(x-10,y,22,36);
  ellipse(x+10,y,22,36);
}
void drawCloud(float x,float y){
  fill(255,255,255,180);
  ellipse(x-25,y,35,25);
  ellipse(x,y-10,45,35);
  ellipse(x+25,y,35,25);
}

// =======================
// HISTORIAL
// =======================
void actualizarHistorial(float[] h,float v){
  for(int i=0;i<h.length-1;i++) h[i]=h[i+1];
  h[h.length-1]=v;
}

// =======================
// GRAFICO CON VALOR EN VIVO
// =======================
void dibujarGrafico(String s){
  background(20,40,60);

  float[] h=histTempA;
  float actual=tempA;
  String titulo="Temperatura Aire";

  if(s.equals("humA")){h=histHumA;actual=humA;titulo="Humedad Aire";}
  if(s.equals("hTi")){h=histHTi;actual=hTi;titulo="Humedad Tierra";}
  if(s.equals("pH")){h=histPH;actual=pH;titulo="pH";}
  if(s.equals("o2")){h=histO2;actual=o2;titulo="O₂";}
  if(s.equals("gas")){h=histGas;actual=gas;titulo="Gas";}
  if(s.equals("vbat")){h=histVBat;actual=vBat;titulo="Voltaje Batería";}
  if(s.equals("vbatPct")){h=histVBatPct;actual=vBatPct;titulo="Estado Batería (%)";}

  stroke(255);
  line(80,height-80,width-80,height-80);
  line(80,height-80,80,80);

  for(int i=0;i<=5;i++){
    float y=map(i*20,0,100,height-80,80);
    text(i*20,50,y);
    line(75,y,80,y);
  }

  noFill();
  stroke(255,200,50);
  beginShape();
  for(int i=0;i<h.length;i++){
    float x=map(i,0,h.length-1,80,width-80);
    float y=map(h[i],0,100,height-80,80);
    vertex(x,y);
  }
  endShape();

  textFont(fontTitulo);
  text(titulo,width/2,50);

  textAlign(RIGHT,TOP);
  textSize(24);
  fill(255,200,50);
  text(nf(actual,1,2), width-50, 50);
  textAlign(CENTER,CENTER);
}

// =======================
// CLICK DERECHO
// =======================
void mousePressed(){
  if(mouseButton==RIGHT){
    if(graficoActivo.equals("")){
      if(mouseDentro(width/2 - spacingX*1.5,yFila1)) graficoActivo="tempA";
      else if(mouseDentro(width/2 - spacingX*0.5,yFila1)) graficoActivo="humA";
      else if(mouseDentro(width/2 + spacingX*0.5,yFila1)) graficoActivo="hTi";
      else if(mouseDentro(width/2 + spacingX*1.5,yFila1)) graficoActivo="pH";
      else if(mouseDentro(width/2 - spacingX*1.5,yFila2)) graficoActivo="o2";
      else if(mouseDentro(width/2 - spacingX*0.5,yFila2)) graficoActivo="gas";
      else if(mouseDentro(width/2 + spacingX*0.5,yFila2)) graficoActivo="vbat";
      else if(mouseDentro(width/2 + spacingX*1.5,yFila2)) graficoActivo="vbatPct";
    } else graficoActivo="";
  }
}

boolean mouseDentro(float x,float y){
  return mouseX>x-100 && mouseX<x+100 && mouseY>y && mouseY<y+220;
}

// =======================
// FONDO
// =======================
void fondoGradiente(){
  for(int i=0;i<height;i++){
    float t=map(i,0,height,0,1);
    stroke(20+20*t,40+40*t,60+60*t);
    line(0,i,width,i);
  }
}

// =======================
// GUARDAR DATOS CADA HORA
// =======================
void guardarDatos() {
  String horaActual = nf(hour(),2)+":"+nf(minute(),2)+":"+nf(second(),2);
  String linea = horaActual + "," + tempA + "," + gas + "," + humA + "," + hTi + "," + pH + "," + o2 + "," + vBat + "," + vBatPct;
  archivoDatos.println(linea);
  archivoDatos.flush();
  println("Datos guardados: "+linea);
}

// =======================
// AL SALIR
// =======================
void exit() {
  archivoDatos.flush();
  archivoDatos.close();
  super.exit();
}

// =======================
// SERIAL (NO TOCAR)
// =======================
void serialEvent(Serial p){
  String l=p.readStringUntil('\n');
  if(l==null) return;
  String[] v=split(trim(l),',');
  if(v.length<8) return;
  tempA = float(v[0]);
  gas   = float(v[1]);
  humA  = float(v[2]);
  hTi   = float(v[3]);
  pH    = float(v[4]);
  o2    = float(v[5]);
  vBat  = float(v[6]);
  vBatPct = int(v[7]);
}
