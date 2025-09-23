#include <gtk/gtk.h>
#include <stdio.h>
#include "mentat_app.h"
#include "state.h"

// this sucks ass
char get_decimal_separator(){
    char test_str[9] = { 0 };
    sprintf(test_str, "%f", 0.0);
    printf("%s\n", test_str);
    return 0;
}


int main(void){
    MentatApp* app;
    int status;

    app = mentat_app_new();
    status = g_application_run(G_APPLICATION(app), 0, NULL);
    mentat_state_free();
    g_object_unref(app);

    return status;
}
