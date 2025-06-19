#ifndef PASSWORD_VALIDATOR_H
#define PASSWORD_VALIDATOR_H

typedef enum e_pwstatus {
	VALID = 0,
	INVALID = 1
} PwStatus;

PwStatus validate_password(const char *new_pw, const char *curr_pw);

#endif

