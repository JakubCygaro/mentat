#include <gtk/gtk.h>
#include "mentat_app.h"
#include "state.h"
int main(void){
    MentatApp* app;
    int status;

    app = mentat_app_new();
    status = g_application_run(G_APPLICATION(app), 0, NULL);
    mentat_state_free();
    g_object_unref(app);

    return status;
}
