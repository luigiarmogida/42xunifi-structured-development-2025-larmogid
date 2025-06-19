# Community Digital Library – Structured Analysis

## Obiettivo

Progettare un programma a riga di comando che:
- Legga un file di catalogo con libri (ID, titolo, autore)
- Ignori righe malformate
- Offra ricerche per titolo o autore (case-insensitive)
- Visualizzi i risultati all’utente
- Pulisca la memoria prima di uscire

---

## Strutture Dati

### Book
Un singolo libro:
- ID numerico
- Titolo
- Autore

### Library
Un contenitore di massimo 1000 `Book` caricati da file.

---

## Funzioni Principali

### Parsing
- `load_catalog`: legge il file e popola la libreria
- `parse_line`: estrae i campi da una singola riga

### Ricerca
- `search_by_title`, `search_by_author`: stampa i risultati

### Input/Output
- `prompt_search_mode`, `prompt_search_query`: interazione utente
- `print_book`: stampa formattata

---

## Flusso del Programma

1. Riceve il nome file da argv
2. Tenta di aprire il file
3. Per ogni riga:
   - La valida e la carica (se possibile)
4. Mostra menu utente:
   - [1] Cerca per titolo
   - [2] Cerca per autore
5. Stampa i risultati
6. Libera le risorse e termina

---

## Diagramma a Blocchi (semplificato)

[START]
   |
[open file] --X--> [Errore e termina]
   |
[leggi riga]
   |
[valida riga?] --NO--> [skippa]
   | YES
[aggiungi a struct]
   |
[fine file]
   |
[menu: 1 o 2?]
   |
[query utente]
   |
[stampa risultati]
   |
[free memoria]
   |
[END]

---

## Conclusioni

Il progetto è pensato in modo modulare e chiaro:
- Ogni modulo ha responsabilità unica
- Le strutture dati sono semplici ma estensibili
- L'interazione utente è robusta e guidata
