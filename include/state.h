#ifndef STATE_H
#define STATE_H

#include <gtk/gtk.h>
enum STATE {
    MENTAT_ARG1_PENDING,
    MENTAT_OPERATOR_PENDING,
    MENTAT_ARG2_PENDING,
};
typedef struct _MentatAppState {
    enum STATE state;
    GtkTextBuffer* text_buffer;
    char* input_buffer;
    size_t input_buffer_len;
    size_t input_buffer_cursor;

    // size_t current_token_len;

    double result;
    double argument;
    char operator;
    char sep;
} MentatAppState;

void mentat_state_initialize(void);
MentatAppState* mentat_state_ptr(void);
void mentat_state_free(void);



#endif
