#ifndef PASSWORD_VALIDATOR_H
#define PASSWORD_VALIDATOR_H

    #define MAX_PASSWORD_LENGTH 100
    #define HISTORY_SIZE 3

    typedef enum e_pwstatus {
        VALID = 0,
        INVALID_WEAK = 1,
        INVALID_SIMILAR = 2
    } PwStatus;

    typedef struct s_password_history {
        char passwords[HISTORY_SIZE][MAX_PASSWORD_LENGTH + 1];
        int count; // quante password ci sono già (max 3)
        int index; // indice circolare (posizione della prossima da sovrascrivere)
    } PasswordHistory;

    PwStatus validate_password(const char *new_pw, PasswordHistory *history);
    int is_strong(const char *pw);
    int edit_distance(const char *s1, const char *s2);

#endif
