#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>

#include "reseau.h"
#include "etat.h"
#include "page.h"

const char* ssid = "ESP32-MonReseau";
const char* password = "12345678";

WebServer server(80);
WebSocketsServer webSocket(81);

String dernierEtatEnvoye;

String construireEtatJeu() {
  String json;
  json.reserve(1500);

  json = "{\"score\":" + String(score);
  json += ",\"record\":" + String(record);
  json += ",\"etat\":" + String((int)etatJeux);
  json += ",\"choixGameOver\":" + String(choixGameOver);
  json += ",\"foodX\":" + String(foodX);
  json += ",\"foodY\":" + String(foodY);
  json += ",\"serpent\":[";

  for (int i = 0; i < snakeLength; i++) {
    if (i > 0) {
      json += ",";
    }

    json += "{\"x\":" + String(snakeX[i]);
    json += ",\"y\":" + String(snakeY[i]) + "}";
  }

  json += "],\"obstacles\":[";

  for (int i = 0; i < nbObs; i++) {
    if (i > 0) {
      json += ",";
    }

    json += "{\"x\":" + String(obsX[i]);
    json += ",\"y\":" + String(obsY[i]) + "}";
  }

  json += "]}";

  return json;
}

void handleRoot() {
  server.sendHeader("Cache-Control", "no-store");
  server.send_P(200, "text/html; charset=utf-8", PAGE_HTML);
}

void initWifi() {
  WiFi.mode(WIFI_AP);

  if (!WiFi.softAP(ssid, password)) {
    Serial.println("Erreur : creation du reseau Wi-Fi impossible");
    return;
  }

  Serial.print("Reseau Wi-Fi : ");
  Serial.println(ssid);

  Serial.print("Adresse IP : ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.begin();

  webSocket.begin();

  webSocket.onEvent(
    [](uint8_t client, WStype_t type, uint8_t* payload, size_t length) {
      if (type == WStype_CONNECTED) {
        String json = construireEtatJeu();
        webSocket.sendTXT(client, json);
      }
    }
  );

  Serial.println("Serveur web et WebSocket demarres");
}

void mettreAJourWifi() {
  server.handleClient();
  webSocket.loop();

  String json = construireEtatJeu();

  if (json != dernierEtatEnvoye) {
    webSocket.broadcastTXT(json);
    dernierEtatEnvoye = json;
  }
}