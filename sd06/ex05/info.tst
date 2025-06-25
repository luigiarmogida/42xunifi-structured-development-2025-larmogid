Obiettivo dell’Analisi Strutturata
Estendere il Contact Manager (ex02) mantenendo compatibilità con il formato precedente, aggiungendo:

Gruppi utente-definiti (es. “Team”, “Vendors”)

Compleanni opzionali, con filtro “entro un mese”

📁 Nuovo formato dei contatti (CSV)
Estensione delle righe CSV:

php-template
Copy
Edit
<name>,<email>,<phone>,<address>,<city>,<zip>[,<group>[,<birthdate>]]
<group> → stringa libera, anche vuota

<birthdate> → formato YYYY-MM-DD (validato)

📌 Data Structures
c
Copy
Edit
typedef struct s_contact {
    char *name;
    char *email;
    char *phone;
    char *address;
    char *city;
    char *zip;

    // Estensioni bonus:
    char *group;        // default: NULL
    char *birthdate;    // default: NULL (YYYY-MM-DD)
} t_contact;

typedef struct s_contact_list {
    t_contact **contacts;
    int count;
} t_contact_list;
🧭 Functional Breakdown (modulare)
1. Input/Output
load_contacts_from_csv(const char *filename)

gestisce vecchi e nuovi formati

save_contacts_to_csv(const char *filename)

salva sempre con tutti i campi (vuoti se assenti)

2. Gestione CRUD base
add_contact(), delete_contact(), edit_contact()

print_all_contacts()

3. Gruppi
list_contacts_by_group()

assign_group_to_contact()

list_groups() (opzionale)

4. Compleanni
show_upcoming_birthdays()

mostra contatti con compleanno nei prossimi 30 giorni

🧪 Validazione
Validazione dei nuovi campi
is_valid_group(char *group) → può anche accettare qualsiasi stringa

is_valid_birthdate(char *date) → formato YYYY-MM-DD, plausibilità (no 2024-02-30)

📜 Menu esteso
text
Copy
Edit
1. View all contacts
2. Add new contact
3. Edit contact
4. Delete contact
5. Search contact
6. Assign or change group
7. List contacts by group
8. Show upcoming birthdays
9. Save and Exit
📈 Structure Chart (livello alto)
scss
Copy
Edit
main()
│
├── load_contacts_from_csv()
├── show_main_menu()
│   ├── handle_add_contact()
│   ├── handle_edit_contact()
│   ├── handle_group_assign()
│   ├── handle_birthdays()
│   └── ...
└── save_contacts_to_csv()
🗓 Bonus: gestione date
Puoi scrivere un parser semplice per YYYY-MM-DD oppure usare un modulo esterno come ft_split + verifica numerica per anno, mese, giorno. Per calcolare i compleanni futuri:

c
Copy
Edit
int is_birthday_within_next_30_days(const char *birthdate);
✅ Prossimi Passi
Definire l’header (contact.h) con tutte le strutture e prototipi

Disegnare lo structure chart

Scrivere file .md o .txt con spiegazione dell’analisi (come sopra)

Iniziare implementazione modulare (con test progressivi)

ex05/
├── contact.h              # Strutture dati e prototipi
├── csv_parser.c          # Caricamento e salvataggio CSV
├── contact_utils.c       # Creazione, stampa, modifica, ecc.
├── group.c               # Funzioni sui gruppi
├── birthday.c            # Funzioni sui compleanni
├── main.c                # Interfaccia utente e menu
