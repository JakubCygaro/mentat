#include "mentat_app.h"
#include <glib.h>
#include <gtk/gtk.h>
#include "mentatui.h"
#include "state.h"


// static char css[] =
// "#text_box{ font: 48px; color: magenta; }";
//


static GtkWindow* mentat_window_new(MentatApp* app) {
    GtkBuilder* builder = gtk_builder_new_from_string(UI_STRING, strlen(UI_STRING));
    GtkCssProvider* provider = gtk_css_provider_new();

    GObject* window = gtk_builder_get_object(builder, "mentat_window");
    gtk_window_set_application(GTK_WINDOW(window), GTK_APPLICATION(app));
    GObject* text_view = gtk_builder_get_object(builder, "text_box");
    GtkTextBuffer* text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    GdkDisplay* display = gdk_display_get_default();
    gtk_style_context_add_provider_for_display(display, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // GBytes* css_bytes = g_bytes_new(css, strlen(css));
    // gtk_css_provider_load_from_bytes(provider, css_bytes);
    //

    app->state->text_buffer = text_buffer;

    gtk_widget_set_visible(GTK_WIDGET(window), TRUE);
    g_object_unref(builder);
    g_object_unref(provider);
    return GTK_WINDOW(window);
}

G_DEFINE_TYPE(MentatApp, mentat_app, GTK_TYPE_APPLICATION);

static void mentat_app_init(MentatApp* app){

}

static void mentat_app_activate(GApplication* app){
    MentatApp* app_m = MENTAT_APP(app);
    mentat_state_initialize();
    MentatAppState* state = mentat_state_ptr();
    app_m->state = state;
    GtkWindow* window = mentat_window_new(app_m);
    // state->input_str = malloc(1);
    // state->input_str[0] = '\0';
    gtk_window_present(GTK_WINDOW(window));
}

static void mentat_app_open(GApplication* app, GFile** files, int n_files, const char* hint){
    GtkWindow* window;
    window = mentat_window_new(MENTAT_APP(app));
    gtk_window_present(GTK_WINDOW(window));
}

static void mentat_app_class_init(MentatAppClass* class){
    G_APPLICATION_CLASS(class)->activate = mentat_app_activate;
    G_APPLICATION_CLASS(class)->open = mentat_app_open;
}

MentatApp* mentat_app_new (void){
    return g_object_new (mentat_app_get_type(),
                       "application-id", "org.papieros.mentat",
                       "flags", G_APPLICATION_HANDLES_OPEN,
                       NULL);
}
