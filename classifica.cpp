#pragma once
#include "classifica.h"
#include "utils/utils.h"

#include <iostream> // Per std::cerr se necessario, ma cercheremo di evitarlo
#include <fstream>  // Per FileManager
#include <string>   // Per std::string, std::stoi
#include <vector>   // Per std::vector
#include <sstream>  // Per std::stringstream
#include <algorithm>// Per std::sort
#include <cstdlib>  // Per srand
#include <ctime>    // Per time
#include <cstring>  // Per strncpy, strlen, strtok_r (o strtok)

// Struttura per i dati del giocatore
struct ScoreEntry {
    std::string name;
    int score;
    std::string original_line_prefix; // Per mantenere "Nome:"
};

// Funzione di confronto per std::sort (ordina per punteggio decrescente)
bool compareScores(const ScoreEntry& a, const ScoreEntry& b) {
    return a.score > b.score;
}

void Classifica::start_classifica(){
    srand(time(NULL));
    initscr();
    curs_set(0);
    noecho();
    start_color(); // Necessario per usare COLOR_PAIR

    // Inizializza le coppie di colori che userai in InlinedTextWindow
    init_pair(1, COLOR_YELLOW, COLOR_BLACK); // Esempio per la prima riga (es. titolo)
    init_pair(2, COLOR_GREEN, COLOR_BLACK);  // Esempio per la seconda riga
    init_pair(3, COLOR_CYAN, COLOR_BLACK);   // Esempio per la terza riga
    // Puoi definire più coppie se necessario

    FileManager fileManager;

    const int bufferSize = 2048; // Aumentato per sicurezza con più righe
    char original_buffer[bufferSize];
    char sorted_display_buffer[bufferSize]; // Buffer per il testo ordinato da visualizzare

    // Leggi il file originale
    int chNumber = fileManager.readFile(original_buffer, bufferSize); // Usa il nome file corretto

    if (chNumber == 0 || (chNumber > 0 && strncmp(original_buffer, "Errore:", 7) == 0) ) {
        // Se il file è vuoto o c'è stato un errore di lettura, visualizza il messaggio e esci
        mvprintw(0, 0, original_buffer[0] == '\0' ? "File classifica vuoto o non trovato." : original_buffer);
        refresh();
        getch();
        endwin();
        return;
    }

    std::vector<ScoreEntry> scores;
    std::string fileContent(original_buffer);
    std::stringstream ss_parse(fileContent);
    std::string line;
    std::string header_line; // Per memorizzare la prima riga "Classifica"

    // 1. Leggi l'intestazione (se presente)
    if (std::getline(ss_parse, header_line)) {
        // Controlla se è una riga di dati o un'intestazione
        // Se non contiene ':', assumiamo sia un'intestazione
        if (header_line.find(':') == std::string::npos) {
            // È un'intestazione, la gestiremo separatamente
        } else {
            // Non c'era un'intestazione, la prima riga è già un dato
            // Rimetti la riga nello stream per il parsing successivo
            // Questo è un po' macchinoso; idealmente, la logica di parsing è più robusta
            // Ma per semplicità, se la prima riga ha ':', la consideriamo dato.
            // Per ora, assumiamo che la prima riga sia sempre un'intestazione se non ha ':'
            // Se la prima riga è un dato, `header_line` sarà vuota dopo il prossimo blocco
            // e la riga verrà processata nel ciclo while.
            // Per questo esempio, rendiamo esplicito che se non è un dato, è l'header.
            if (header_line.find(':') == std::string::npos) {
                 // header_line già contiene l'intestazione
            } else {
                // La prima riga era un dato, la processeremo nel loop.
                // Resetta lo stream e rileggi la prima riga come dato.
                // Questa parte è complessa con char buffer, più facile con stringhe.
                // Per ora, semplifichiamo: la prima riga è header se non ha ':'
                // altrimenti, la processiamo come dato e non avremo un header separato.
                // Se la prima riga è "Classifica", header_line la conterrà.
                // Se è "Fra:200", il blocco if qui sotto non la considererà header.
                // Quindi, dobbiamo rimettere `line` nello stream o processarla qui.
                // Soluzione più semplice: se la prima riga non ha ':', è l'header.
                // Altrimenti, non c'è header separato.
                // Modifichiamo:
                std::stringstream temp_ss_for_first_line(fileContent);
                std::string first_line_check;
                std::getline(temp_ss_for_first_line, first_line_check);
                if (first_line_check.find(':') == std::string::npos) {
                    // header_line è già corretta
                } else {
                    header_line.clear(); // Non c'è un header separato
                    // Resettiamo ss_parse per rileggere tutto
                    ss_parse.clear();
                    ss_parse.str(fileContent);
                }
            }
        }
    }

    // 2. Parsa le righe dei giocatori
    while (std::getline(ss_parse, line)) {
        if (line.empty() || line == header_line) continue; // Salta righe vuote o l'header già letto

        size_t colon_pos = line.find(':');
        if (colon_pos != std::string::npos && colon_pos + 1 < line.length()) {
            ScoreEntry entry;
            entry.original_line_prefix = line.substr(0, colon_pos + 1); // Include il ':'
            // Pulisci il nome nel prefisso
            entry.original_line_prefix.erase(0, entry.original_line_prefix.find_first_not_of(" \t"));
            entry.original_line_prefix.erase(entry.original_line_prefix.find_last_not_of(" \t") + 1);

            std::string score_str = line.substr(colon_pos + 1);
            // Pulisci la stringa del punteggio
            score_str.erase(0, score_str.find_first_not_of(" \t"));
            score_str.erase(score_str.find_last_not_of(" \t") + 1);

            try {
                entry.score = std::stoi(score_str);
                // Il nome vero e proprio è prima dei ':' nel prefisso
                entry.name = entry.original_line_prefix.substr(0, entry.original_line_prefix.length() -1); // Rimuovi ':'
                scores.push_back(entry);
            } catch (const std::exception& e) {
                // Ignora righe con punteggio non valido
            }
        }
    }

    // 3. Ordina i giocatori
    std::sort(scores.begin(), scores.end(), compareScores);

    // 4. Ricostruisci il buffer per la visualizzazione
    std::string sorted_content_str;
    if (!header_line.empty()) {
        sorted_content_str += header_line + "\n";
    }
    for (const auto& entry : scores) {
        sorted_content_str += entry.name + ":" + std::to_string(entry.score) + "\n";
    }

    // Copia nel buffer di visualizzazione
    strncpy(sorted_display_buffer, sorted_content_str.c_str(), bufferSize - 1);
    sorted_display_buffer[bufferSize - 1] = '\0';
    int display_chNumber = strlen(sorted_display_buffer);

    // 5. Crea la finestra e visualizza
    // Calcola dimensioni finestra in base al contenuto (semplificato)
    int num_display_lines = 1; // Per l'header
    for (const auto& entry : scores) num_display_lines++;
    if (num_display_lines == 0 && !header_line.empty()) num_display_lines = 1; // Solo header
    if (num_display_lines == 0 && scores.empty()) num_display_lines = 1; // Almeno una riga per "vuoto"

    int max_width_display = header_line.length();
    for(const auto& entry : scores) {
        size_t current_len = entry.name.length() + 1 + std::to_string(entry.score).length();
        if (current_len > max_width_display) {
            max_width_display = current_len;
        }
    }
    if (max_width_display == 0) max_width_display = 20; // Minima larghezza

    // Usa le tue funzioni Utils per creare la finestra
    // Le coordinate starty e startx per CreateTextBox sono fisse nel tuo codice originale.
    // Se vuoi centrarla, dovrai modificare CreateTextBox o calcolare starty/startx qui.
    // Per ora, uso i valori originali che hai passato.
    // Nota: CreateTextBox prende `characters` che non sembra usato per l'altezza/larghezza della finestra.
    // La tua CreateTextBox usa height=7, width=30 fissi.
    // Per visualizzare più righe, dovrai rendere CreateTextBox più flessibile
    // o usare un approccio diverso per la finestra.

    // Adattiamo per usare CreateTextBox con dimensioni fisse, ma InlinedTextWindow stamperà.
    // Se il testo è troppo lungo per 7x30, verrà troncato da InlinedTextWindow o non starà.
    // Sarebbe meglio che CreateTextBox prendesse altezza e larghezza.
    // Modifichiamo CreateTextBox per accettare altezza e larghezza:
    // WINDOW* Utils::CreateTextBox(WINDOW* boxForFile, int height, int width, int starty, int startx){...}
    // Per ora, assumo che Utils::CreateTextBox sia come l'hai data (7x30).
    // Se hai molte voci, questo non basterà.

    WINDOW * insideBox = nullptr; // Inizializza a nullptr
    // insideBox = Utils::CreateTextBox(insideBox, display_chNumber, 6, 4); // Vecchia chiamata

    // Calcoliamo la posizione centrale per la finestra
    int win_h = num_display_lines + 2; // +2 per i bordi
    int win_w = max_width_display + 4; // +2 per i bordi, +2 per padding interno
    int screen_h_ncurses, screen_w_ncurses;
    getmaxyx(stdscr, screen_h_ncurses, screen_w_ncurses);
    int start_y_ncurses = (screen_h_ncurses - win_h) / 2;
    int start_x_ncurses = (screen_w_ncurses - win_w) / 2;
    if (start_y_ncurses < 0) start_y_ncurses = 0;
    if (start_x_ncurses < 0) start_x_ncurses = 0;
    if (win_h > screen_h_ncurses) win_h = screen_h_ncurses;
    if (win_w > screen_w_ncurses) win_w = screen_w_ncurses;

    // insideBox = Utils::CreateTextBox(insideBox, display_chNumber, 6, 4); // La tua chiamata originale
    // Usiamo una finestra con dimensioni calcolate:
    insideBox = newwin(win_h, win_w, start_y_ncurses, start_x_ncurses);
    box(insideBox, 0, 0);
    refresh(); // Aggiorna stdscr
    wrefresh(insideBox); // Aggiorna la nuova finestra

    // Stampa il contenuto ordinato usando la tua Utils::InlinedTextWindow
    // Nota: InlinedTextWindow ha bisogno di sapere le dimensioni del box per il wrapping corretto.
    // La tua InlinedTextWindow attuale non prende le dimensioni del box come input per il wrapping,
    // ma le ottiene con getmaxyx(insideBox, ...). Questo va bene.
    Utils::InlinedTextWindow(insideBox, 2, 1, sorted_display_buffer); // x=1, y=1 per iniziare dentro i bordi
    fileManager.writeFile(sorted_display_buffer); // Scrive il file ordinato

    wrefresh(insideBox);

    delwin(insideBox);
    endwin();
}