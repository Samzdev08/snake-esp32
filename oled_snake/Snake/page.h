#pragma once
#include <Arduino.h>

const char PAGE_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Snake ESP32</title>

  <style>
    * {
      box-sizing: border-box;
    }

    body {
      margin: 0;
      min-height: 100vh;
      padding: 24px;
      display: flex;
      align-items: center;
      justify-content: center;
      background: #0b121a;
      color: #eef6ff;
      font-family: Arial, sans-serif;
    }

    main {
      width: min(100%, 960px);
    }

    header, .scores, footer {
      display: flex;
      align-items: center;
      justify-content: space-between;
      gap: 16px;
      flex-wrap: wrap;
    }

    header {
      margin-bottom: 24px;
    }

    h1 {
      margin: 0;
      font-size: clamp(24px, 5vw, 40px);
    }

    #connexion {
      color: #ffca75;
      font-size: 14px;
    }

    .scores {
      margin-bottom: 16px;
      padding: 16px 20px;
      background: #17232f;
      border-radius: 12px;
      font-size: clamp(16px, 3vw, 24px);
    }

    strong {
      color: #a9ff83;
    }

    .terrain {
      position: relative;
      overflow: hidden;
      border: 2px solid #304555;
      border-radius: 14px;
      background: #111e29;
    }

    canvas {
      display: block;
      width: 100%;
      height: auto;
      image-rendering: pixelated;
    }

    .ecran {
      position: absolute;
      inset: 0;
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: center;
      gap: 14px;
      padding: 12px;
      background: rgba(11, 18, 26, 0.95);
      text-align: center;
    }

    [hidden] {
      display: none !important;
    }

    h2 {
      margin: 0;
      color: #a9ff83;
      font-size: clamp(26px, 6vw, 64px);
    }

    p {
      margin: 0;
      color: #b2c4d2;
      font-size: clamp(12px, 2.2vw, 20px);
    }

    #gameOver h2 {
      color: #ff7589;
    }

    .choix {
      display: flex;
      gap: 16px;
    }

    .option {
      padding: 10px 24px;
      border: 2px solid #425768;
      border-radius: 10px;
      color: #b2c4d2;
      font-size: clamp(14px, 2.5vw, 22px);
    }

    .option.selection {
      color: #0b121a;
      background: #a9ff83;
      border-color: #a9ff83;
      font-weight: bold;
    }

    footer {
      margin-top: 18px;
      color: #91a8ba;
      font-size: 14px;
    }

    button {
      padding: 10px 16px;
      border: 1px solid #425768;
      border-radius: 8px;
      background: #17232f;
      color: #eef6ff;
      cursor: pointer;
    }

    @media (max-width: 550px) {
      body {
        padding: 12px;
      }

      .ecran {
        gap: 6px;
      }

      .option {
        padding: 6px 16px;
      }
    }
  </style>
</head>

<body>
  <main>
    <header>
      <h1>Snake ESP32</h1>
      <span id="connexion" role="status">Connexion...</span>
    </header>

    <div class="scores">
      <span>Score : <strong id="score">0</strong></span>
      <span>Record : <strong id="record">0</strong></span>
    </div>

    <div class="terrain">
      <canvas id="terrain" width="128" height="48"></canvas>

      <section id="attente" class="ecran">
        <h2>Connexion...</h2>
        <p>En attente du jeu sur l'ESP32</p>
      </section>

      <section id="menu" class="ecran" hidden>
        <h2>SNAKE</h2>
        <p>Record : <strong id="recordMenu">0</strong></p>
        <p>Appuie sur le joystick pour jouer</p>
      </section>

      <section id="gameOver" class="ecran" hidden>
        <h2>GAME OVER</h2>

        <p>
          Score : <strong id="scoreFinal">0</strong>
          | Record : <strong id="recordFinal">0</strong>
        </p>

        <div class="choix">
          <span id="rejouer" class="option">Rejouer</span>
          <span id="retourMenu" class="option">Menu</span>
        </div>

        <p>Gauche / droite pour choisir · Clic pour valider</p>
      </section>
    </div>

    <footer>
      <span>Commandes sur le joystick de l'ESP32</span>
      <button id="pleinEcran" type="button">Plein écran</button>
    </footer>
  </main>

  <script>
    const MENU = 0;
    const JEU = 1;
    const GAME_OVER = 2;

    const GRILLE = 8;
    const HAUT_ZONE_JEU = 16;

    const elements = {};

    [
      "terrain", "connexion", "attente", "menu", "gameOver",
      "score", "record", "recordMenu", "scoreFinal", "recordFinal",
      "rejouer", "retourMenu", "pleinEcran"
    ].forEach(id => {
      elements[id] = document.getElementById(id);
    });

    const canvas = elements.terrain;
    const ctx = canvas.getContext("2d");

    let socket = null;
    let reconnexion = null;

    function dessinerCase(x, y, couleur) {
      ctx.fillStyle = couleur;
      ctx.fillRect(
        x,
        y - HAUT_ZONE_JEU,
        GRILLE - 1,
        GRILLE - 1
      );
    }

    function dessinerTerrain(jeu) {
      ctx.fillStyle = "#111e29";
      ctx.fillRect(0, 0, canvas.width, canvas.height);

      ctx.fillStyle = "#2b3d4c";

      for (let y = 0; y < canvas.height; y += GRILLE) {
        for (let x = 0; x < canvas.width; x += GRILLE) {
          ctx.fillRect(x, y, 1, 1);
        }
      }

      for (const obstacle of jeu.obstacles) {
        dessinerCase(obstacle.x, obstacle.y, "#8295a3");

        ctx.fillStyle = "#354958";
        ctx.fillRect(
          obstacle.x + 2,
          obstacle.y - HAUT_ZONE_JEU + 2,
          3,
          3
        );
      }

      dessinerCase(jeu.foodX, jeu.foodY, "#ff6577");

      jeu.serpent.forEach((segment, index) => {
        dessinerCase(
          segment.x,
          segment.y,
          index === 0 ? "#b4ff75" : "#54ce87"
        );
      });
    }

    function afficherEtat(jeu) {
      if (
        ![MENU, JEU, GAME_OVER].includes(jeu.etat) ||
        !Array.isArray(jeu.serpent) ||
        !Array.isArray(jeu.obstacles)
      ) {
        throw new Error("Etat du jeu incomplet");
      }

      elements.score.textContent = jeu.score;
      elements.record.textContent = jeu.record;
      elements.recordMenu.textContent = jeu.record;
      elements.scoreFinal.textContent = jeu.score;
      elements.recordFinal.textContent = jeu.record;

      dessinerTerrain(jeu);

      elements.attente.hidden = true;
      elements.menu.hidden = jeu.etat !== MENU;
      elements.gameOver.hidden = jeu.etat !== GAME_OVER;

      elements.rejouer.classList.toggle(
        "selection",
        jeu.choixGameOver === 0
      );

      elements.retourMenu.classList.toggle(
        "selection",
        jeu.choixGameOver === 1
      );

      const noms = ["Menu", "Partie en cours", "Game Over"];

      elements.connexion.textContent = "Connecté · " + noms[jeu.etat];
      elements.connexion.style.color = "#a9ff83";
    }

    function connecterWebSocket() {
      if (
        socket &&
        (socket.readyState === WebSocket.OPEN ||
         socket.readyState === WebSocket.CONNECTING)
      ) {
        return;
      }

      clearTimeout(reconnexion);

      elements.connexion.textContent = "Connexion...";
      elements.connexion.style.color = "#ffca75";

      socket = new WebSocket(
        "ws://" + window.location.hostname + ":81/"
      );

      const connexionActuelle = socket;

      connexionActuelle.onopen = () => {
        elements.connexion.textContent = "Connecté · En attente du jeu";
        elements.connexion.style.color = "#a9ff83";
      };

      connexionActuelle.onmessage = (message) => {
        try {
          afficherEtat(JSON.parse(message.data));
        } catch (erreur) {
          elements.connexion.textContent = "Données du jeu invalides";
          elements.connexion.style.color = "#ffca75";
          console.error(erreur);
        }
      };

      connexionActuelle.onclose = () => {
        if (socket !== connexionActuelle) {
          return;
        }

        socket = null;
        elements.connexion.textContent =
          "Déconnecté · Nouvelle tentative...";
        elements.connexion.style.color = "#ffca75";

        reconnexion = setTimeout(connecterWebSocket, 1000);
      };

      connexionActuelle.onerror = () => {
        connexionActuelle.close();
      };
    }

    if (!document.fullscreenEnabled) {
      elements.pleinEcran.hidden = true;
    }

    elements.pleinEcran.addEventListener("click", async () => {
      try {
        if (document.fullscreenElement) {
          await document.exitFullscreen();
        } else {
          await document.documentElement.requestFullscreen();
        }
      } catch (erreur) {
        console.error(erreur);
      }
    });

    document.addEventListener("fullscreenchange", () => {
      elements.pleinEcran.textContent = document.fullscreenElement
        ? "Quitter le plein écran"
        : "Plein écran";
    });

    connecterWebSocket();
  </script>
</body>
</html>
)rawliteral";