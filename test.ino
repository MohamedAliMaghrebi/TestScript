#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h> 

const char* ssid = "Orange-E75A"; 
const char* password = "9ALL5DFARRB"; 

WebServer server(80);

// Fonction de gestion de la requête de la page d'accueil
void handleRoot() {
  // Charge le contenu du fichier index.html
  File file = SPIFFS.open("/index.html", "r");
  if (!file) {
    Serial.println("Failed to open index.html file");
    return server.send(404, "text/plain", "File not found");
  }

  // Lit le contenu du fichier et l'envoie au client
  server.streamFile(file, "text/html");
  file.close();
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Affiche l'adresse IP dans le moniteur série

  // Initialise le système de fichiers SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("An error occurred while mounting SPIFFS");
    return;
  }

  // Définit le gestionnaire de la page d'accueil
  server.on("/", HTTP_GET, handleRoot);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
