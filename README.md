# 🐍 Snake Game in C++ with ncurses

Un'implementazione moderna e completa del classico gioco Snake realizzata in C++ utilizzando la libreria ncurses per l'interfaccia testuale.

![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![ncurses](https://img.shields.io/badge/ncurses-6.0%2B-green.svg)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)

## 📋 Indice

- [🎮 Caratteristiche](#-caratteristiche)
- [🛠 Prerequisiti](#-prerequisiti)
- [🚀 Installazione](#-installazione)
- [🎯 Come Giocare](#-come-giocare)
- [📁 Struttura del Progetto](#-struttura-del-progetto)
- [⚙️ Configurazione](#-configurazione)
- [👥 Autori](#-autori)

## 🎮 Caratteristiche

### ✨ Funzionalità Principali
- **Menu interattivo** con navigazione a frecce
- **Sistema di livelli** con difficoltà progressiva (1-10)
- **Classifica persistente** con salvataggio automatico dei punteggi
- **Attraversamento bordi** - il serpente può passare attraverso i muri
- **Sistema di pausa** durante il gioco

### 🎨 Interfaccia Utente
- Menu principale con 4 opzioni:
  - **Gioca** - Avvia il gioco con il livello selezionato
  - **Classifica** - Visualizza i migliori 10 punteggi
  - **Livelli** - Selezione della difficoltà (1-10)
  - **Esci** - Termina il programma

### 🏅 Sistema di Punteggio Avanzato
- Punti base per ogni mela mangiata
- **Bonus temporali** basati sul livello
- **Moltiplicatori di difficoltà** per livelli superiori
- **Classifica colorata** con podio (oro, argento, bronzo)

## 🛠 Prerequisiti

### Librerie Richieste
- **ncurses** (versione 6.0 o superiore)
- **Compilatore C++** con supporto C++11 o superiore
- **MinGW** (per utenti Windows)

### Installazione ncurses

#### 🐧 Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install libncurses5-dev libncursesw5-dev
```

#### 🍎 macOS
```bash
brew install ncurses
```

#### 🪟 Windows (MinGW)
1. Installa [MinGW-w64](https://www.mingw-w64.org/)
2. Scarica ncurses per MinGW
3. Aggiungi le directory `bin` e `include` alle variabili d'ambiente

## 🚀 Installazione

### 1. Clona il Repository
```bash
git clone https://github.com/your-username/SnakeProgetto.git
cd SnakeProgetto
```

### 2. Compila il Progetto

#### Metodo 1: Usando VS Code (Consigliato)
1. Apri il progetto in Visual Studio Code
2. Usa il task predefinito `Ctrl+Shift+P` → "Tasks: Run Task" → "Compila automaticamente"

#### Metodo 2: Compilazione Manuale
```bash
# Linux/macOS
g++ -std=c++11 -o snake main.cpp -lncurses

# Windows (MinGW)
g++ -I/mingw64/include/ncurses -o main.exe main.cpp -lncurses -L/mingw64/bin -static
```

### 3. Esegui il Gioco
```bash
# Linux/macOS
./snake

# Windows
main.exe
```

## 🎯 Come Giocare

### 🎮 Controlli di Base
| Tasto | Azione |
|-------|--------|
| `↑` `↓` `←` `→` | Movimento del serpente |
| `ESC` | Menu pausa |
| `Enter` | Conferma selezione menu |

### 🎯 Obiettivo
- Mangia le **mele rosse** (🍎) per crescere e guadagnare punti
- Evita di collidere con il tuo stesso corpo
- Sopravvivi il più a lungo possibile per massimizzare il punteggio
- Completa i livelli per bonus aggiuntivi

### 📊 Sistema di Livelli
- **Livello 1-3**: Velocità base, ideale per principianti
- **Livello 4-6**: Velocità media, sfida moderata  
- **Livello 7-10**: Velocità alta, per giocatori esperti

## 📁 Struttura del Progetto

```
SnakeProgetto/
├── 📂 gioco/                    # Core game logic
│   ├── 🐍 Serpente.cpp/hpp      # Implementazione serpente
│   ├── 🍎 Mela.cpp/hpp          # Gestione mele/cibo
│   ├── 📶 Livelli.cpp/hpp       # Sistema livelli
│   └── 🎮 game.cpp              # Game loop principale
├── 📂 menu_handler/             # Gestione interfaccia
│   └── 📋 main_menu.cpp/h       # Menu principale
├── 📂 file_handler/             # Persistenza dati
│   └── 💾 file_manager.cpp/h    # Gestione file punteggi
├── 📂 utils/                    # Funzioni utility
│   └── 🛠 utils.cpp/h           # Utilità comuni
├── 📂 includes/                 # Headers globali
│   └── 📚 include.h/cpp         # Include centralizzati
├── 📊 classifica.cpp/h          # Sistema classifica
├── 🏁 main.cpp                  # Entry point
└── 📝 SaveFile.txt              # File punteggi (auto-generato)
```

### 🏗 Architettura Modulare
- **Separazione delle responsabilità** tra moduli
- **Classi specializzate** per ogni componente
- **Design pattern** implementati (Singleton, State)
- **Gestione memoria** con RAII

## ⚙️ Configurazione

### 🎛 Parametri Personalizzabili
Modifica i valori in `includes/include.h`:

```cpp
// Dimensioni finestra di gioco
#define GAME_WIDTH 80
#define GAME_HEIGHT 24

// Velocità base del serpente
#define BASE_SPEED 7

// Punti per mela
#define APPLE_POINTS 10

// Durata livello (secondi)
#define LEVEL_DURATION 45
```

### 🎨 Personalizzazione Colori
I colori possono essere modificati in `utils/utils.cpp`:

```cpp
init_pair(1, COLOR_GREEN, COLOR_BLACK);  // Serpente
init_pair(2, COLOR_RED, COLOR_BLACK);    // Bordi
init_pair(3, COLOR_YELLOW, COLOR_BLACK); // Mele
```

### 🥇 Classifica
- **🥇 1° posto**: Visualizzato in **oro**
- **🥈 2° posto**: Visualizzato in **argento**  
- **🥉 3° posto**: Visualizzato in **bronzo**
- Salvataggio automatico in `SaveFile.txt`
- Formato: `NomeGiocatore:Punteggio`

## 🔧 Risoluzione Problemi

### ❗ Errori Comuni

#### "ncurses.h not found"
```bash
# Verifica installazione ncurses
pkg-config --cflags ncurses

# Se mancante, reinstalla
sudo apt-get install libncurses5-dev
```

#### "Terminale troppo piccolo"
- Ridimensiona la finestra del terminale
- Minimo richiesto: 80x24 caratteri

#### Problemi di compilazione Windows
- Verifica che MinGW sia nel PATH
- Controlla che ncurses sia installato correttamente
- Usa il comando di compilazione specifico per Windows

### 🐛 Debug
Per abilitare output di debug, aggiungi `-DDEBUG` durante la compilazione:
```bash
g++ -DDEBUG -std=c++11 -o snake main.cpp -lncurses
```

## 👥 Autori

### 👨‍💻 Team di Sviluppo
- **Matteo Terzi**  [matteo.terzi8@studio.unibo.it](mailto:matteo.terzi8@studio.unibo.it)
- **Francesco Pignanelli**  [francesco.pignanelli@studio.unibo.it](mailto:francesco.pignanelli@studio.unibo.it)  
- **Leonardo Rocco Monaco**  [leonardorocco.monaco@studio.unibo.it](mailto:leonardorocco.monaco@studio.unibo.it)

### 🎓 Contesto Accademico
Progetto sviluppato per il corso di **Programmazione** presso l'**Università di Bologna** - Corso di Laurea in Informatica.

---

<div align="center">

**⭐ Se ti piace questo progetto, lascia una stella! ⭐**

Realizzato con ❤️ da studenti di Informatica UNIBO

[🔝 Torna all'inizio](#-snake-game-in-c-with-ncurses)

</div>
