# Contact Manager - Requisiti Riformulati

## ✅ Caricamento Dati
- Aprire il file CSV fornito come argomento da linea di comando.
- Gestire errori in apertura (es. file inesistente).
- Leggere il file riga per riga.
- Per ogni riga:
  - Rimuovere spazi bianchi attorno ai campi.
  - Validare i campi secondo le seguenti regole:
    - **ID**:
      - Deve essere un intero positivo.
      - Non deve essere già presente tra i contatti caricati.
    - **Name** e **City**:
      - Non devono essere vuoti dopo il trim.
    - **Phone**:
      - Deve contenere solo cifre e simboli ammessi (+, -, (, )).
      - Deve contenere almeno una cifra.
    - **Email**:
      - Deve contenere esattamente un `@`.
      - Parti locale e dominio devono essere non vuote.
      - Il dominio deve contenere almeno un punto `.`.
    - **Address**:
      - Può essere vuoto.
  - Segnalare le righe malformate con un warning.
  - Memorizzare solo i contatti validi.

## ✅ Menu Operativo
Dopo il caricamento, il programma entra in un ciclo con le seguenti opzioni:
- Elencare tutti i contatti.
- Cercare per sottostringa nel campo `name`.
- Cercare per sottostringa nel campo `city`.
- Aggiungere un nuovo contatto.
- Modificare un contatto esistente (ricerca per ID).
- Eliminare un contatto (ricerca per ID).
- Salvare e uscire.

## ✅ Salvataggio
- Scrivere i contatti su file temporaneo.
- Rinominare il file temporaneo sul nome originale.
- Gestire eventuali errori in scrittura.
- Uscire dal programma dopo il salvataggio.

## ✅ UX e Robustezza
- Prompt ripetuti in caso di input non valido.
- Dopo ogni operazione, ritornare al menu principale (tranne in caso di uscita).