#ifndef BUTTONS_H
#define BUTTONS_H

#include <gtk/gtk.h>
#include <math.h>
#include <string.h>
#include "state.h"
#include "mentat_app.h"
#include "state.h"
#include <gdk/gdk.h>
#include <glib.h>
#include <glibconfig.h>

#define NUM_BUTTON_CLICKED_DEF(N) \
void button_## N ##__clicked(GtkButton* button, gpointer data);


void button_0__clicked(GtkButton* button, gpointer data);

NUM_BUTTON_CLICKED_DEF(1);
NUM_BUTTON_CLICKED_DEF(2);
NUM_BUTTON_CLICKED_DEF(3);
NUM_BUTTON_CLICKED_DEF(4);
NUM_BUTTON_CLICKED_DEF(5);
NUM_BUTTON_CLICKED_DEF(6);
NUM_BUTTON_CLICKED_DEF(7);
NUM_BUTTON_CLICKED_DEF(8);
NUM_BUTTON_CLICKED_DEF(9);

#define NUM_BUTTON_CLICKED(N) \
void button_## N ##__clicked(GtkButton* button, gpointer data){\
    MentatAppState* state = mentat_state_ptr();\
    if(state->input_buffer[0] == '0'){\
        state->input_buffer_cursor--;\
        GtkTextIter iter;\
        GtkTextIter end_iter;\
        gtk_text_buffer_get_iter_at_line(state->text_buffer, &iter, gtk_text_buffer_get_line_count(state->text_buffer) -1 );\
        gtk_text_iter_backward_char(&iter);\
        gtk_text_buffer_get_end_iter(state->text_buffer, &end_iter);\
        gtk_text_buffer_delete(state->text_buffer, &iter, &end_iter);\
    }\
    state->input_buffer[state->input_buffer_cursor++] = '0' + N;\
    state->input_buffer[state->input_buffer_cursor] = '\0';\
    g_print("%s\n", state->input_buffer);\
    gtk_text_buffer_insert_at_cursor(state->text_buffer, #N, 1);\
}\

void button_enter__clicked(GtkButton* button, gpointer data);
void button_clear__clicked(GtkButton* button, gpointer data);
void button_dot__clicked(GtkButton* button, gpointer data);

#define OPERATOR_BUTTON_CLICKED_DEF(OP, NAME)\
void button_##NAME##__clicked(GtkButton* button, gpointer data);

OPERATOR_BUTTON_CLICKED_DEF('+', add);
OPERATOR_BUTTON_CLICKED_DEF('-', sub);
OPERATOR_BUTTON_CLICKED_DEF('*', mul);
OPERATOR_BUTTON_CLICKED_DEF('/', div);

#define OPERATOR_BUTTON_CLICKED(OP, NAME)\
void button_##NAME##__clicked(GtkButton* button, gpointer data){\
    MentatAppState* state = mentat_state_ptr();\
    if(state->input_buffer_cursor == 0 && isnan(state->result)) return;\
    if(isnan(state->argument)){\
        state->argument = atof(state->input_buffer);\
        g_print("%lf\n", state->argument);\
        state->input_buffer_cursor = 0;\
        state->input_buffer[state->input_buffer_cursor] = '\0';\
        gtk_text_buffer_insert_at_cursor(state->text_buffer, "\n", 1);\
    } else if (state->input_buffer_cursor > 0){\
        double arg_2 = atof(state->input_buffer);\
        state->input_buffer_cursor = 0;\
        state->input_buffer[state->input_buffer_cursor] = '\0';\
        gtk_text_buffer_insert_at_cursor(state->text_buffer, "\n", 1);\
        perform_operation(arg_2);\
    }\
    GtkTextIter iter;\
    GtkTextIter end_iter;\
    GtkTextBuffer* text_buffer = state->text_buffer;\
    char str[2] = { OP, '\n' };\
    switch (state->operator) {\
    case OP:\
        break;\
    default:\
        for(int i = 0; i < 2; i++){\
            gtk_text_buffer_get_iter_at_line(text_buffer, &iter, gtk_text_buffer_get_line_count(text_buffer) -1 );\
            gtk_text_iter_backward_char(&iter);\
            gtk_text_buffer_get_end_iter(text_buffer, &end_iter);\
            gtk_text_buffer_delete(text_buffer, &iter, &end_iter);\
        }\
    case '\0':\
        gtk_text_buffer_insert_at_cursor(state->text_buffer, str, 2);\
        state->operator = OP;\
    }\
}
#endif
