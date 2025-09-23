#include <gtk/gtk.h>
#include <math.h>
#include <string.h>
#include "state.h"

#define NUM_BUTTON_CLICKED(N) \
void button_## N ##__clicked(GtkButton* button, gpointer data){\
    MentatAppState* state = mentat_state_ptr();\
    state->input_buffer[state->input_buffer_cursor++] = '0' + N;\
    state->input_buffer[state->input_buffer_cursor] = '\0';\
    g_print("%s\n", state->input_buffer);\
    gtk_text_buffer_insert_at_cursor(state->text_buffer, #N, 1);\
}\

void button_0__clicked(GtkButton* button, gpointer data){
    MentatAppState* state = mentat_state_ptr();
    if((state->input_buffer_cursor == 0) || (state->input_buffer_cursor > 0 && state->input_buffer[0] != '0')){
        state->input_buffer[state->input_buffer_cursor++] = '0';
        state->input_buffer[state->input_buffer_cursor] = '\0';
        g_print("%s\n", state->input_buffer);
        gtk_text_buffer_insert_at_cursor(state->text_buffer, "0", 1);
    }
}

NUM_BUTTON_CLICKED(1);
NUM_BUTTON_CLICKED(2);
NUM_BUTTON_CLICKED(3);
NUM_BUTTON_CLICKED(4);
NUM_BUTTON_CLICKED(5);
NUM_BUTTON_CLICKED(6);
NUM_BUTTON_CLICKED(7);
NUM_BUTTON_CLICKED(8);
NUM_BUTTON_CLICKED(9);

void perform_operation(double arg_2){
    MentatAppState* state = mentat_state_ptr();
    switch (state->operator){
    case '+':{
        state->result = state->argument + arg_2;
    }break;
    case '-':{
        state->result = state->argument - arg_2;
    }break;
    case '*':{
        state->result = state->argument * arg_2;
    }break;
    case '/':{
        state->result = state->argument / arg_2;
    }break;
    default:{}
    }
    state->argument = NAN;
    char str[512] = { 0 };
    sprintf(str, "%.4lf\n", state->result);
    GtkTextIter start;
    GtkTextIter end;
    gtk_text_buffer_get_start_iter(state->text_buffer, &start);
    gtk_text_buffer_get_end_iter(state->text_buffer, &end);
    gtk_text_buffer_delete(state->text_buffer, &start, &end);
    gtk_text_buffer_insert_at_cursor(state->text_buffer, str, strlen(str));
    state->argument = state->result;
    state->operator = '\0';
}

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

void button_enter__clicked(GtkButton* button, gpointer data){
    MentatAppState* state = mentat_state_ptr();
    if(state->operator == '\0') return;
    if (!isnan(state->argument) && state->input_buffer_cursor > 0){
        double arg_2 = atof(state->input_buffer);
        state->input_buffer_cursor = 0;
        state->input_buffer[state->input_buffer_cursor] = '\0';
        gtk_text_buffer_insert_at_cursor(state->text_buffer, "\n", 1);
        perform_operation(arg_2);
        state->operator = '\0';
    } else if (!isnan(state->argument) && !isnan(state->result) && state->input_buffer_cursor == 0){
        double arg_2 = state->result;
        // char op = state->operator;
        perform_operation(arg_2);
        // state->operator = op;
        // char str[1] = { op };
        // gtk_text_buffer_insert_at_cursor(state->text_buffer, str, 1);
        // state->operator = '\0';
    }
}
void button_clear__clicked(GtkButton* button, gpointer data){
    MentatAppState* state = mentat_state_ptr();
    state->operator = '\0';
    state->result = NAN;
    state->argument = NAN;
    state->input_buffer_cursor = 0;
    state->input_buffer[0] = '\0';

    GtkTextIter start;
    GtkTextIter end;
    gtk_text_buffer_get_start_iter(state->text_buffer, &start);
    gtk_text_buffer_get_end_iter(state->text_buffer, &end);
    gtk_text_buffer_delete(state->text_buffer, &start, &end);
}
void button_dot__clicked(GtkButton* button, gpointer data){
    MentatAppState* state = mentat_state_ptr();
    if(state->input_buffer_cursor == 0){
        state->input_buffer[state->input_buffer_cursor++] = '0';
        state->input_buffer[state->input_buffer_cursor++] = state->sep;
        state->input_buffer[state->input_buffer_cursor] = '\0';
        gtk_text_buffer_insert_at_cursor(state->text_buffer, state->input_buffer, 2);
    } else if (state->input_buffer_cursor > 0){
        for(size_t i = 0; i < state->input_buffer_cursor; i++){
            if(state->input_buffer[i] == state->sep) return;
        }
        state->input_buffer[state->input_buffer_cursor++] = state->sep;
        state->input_buffer[state->input_buffer_cursor] = '\0';
        gtk_text_buffer_insert_at_cursor(state->text_buffer, &state->sep, 1);
    }
}

OPERATOR_BUTTON_CLICKED('+', add);
OPERATOR_BUTTON_CLICKED('-', sub);
OPERATOR_BUTTON_CLICKED('*', mul);
OPERATOR_BUTTON_CLICKED('/', div);
