#include <gtk/gtk.h>

#include "window.h"
#include "style_loader.h"

static void on_window_destroy(GtkWindow *window, bool *should_quit) {
    *should_quit = true;
}

int main() {
    gtk_init();

    GMainContext *main_context = g_main_context_default();

    GtkCssProvider *css_provider = load_css_provider();

    GtkWidget *window = create_main_window();

    bool should_quit = false;
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), &should_quit);

    gtk_window_present(GTK_WINDOW(window));

    while (!should_quit) {
        g_main_context_iteration(main_context, true);
    }

    g_object_unref(css_provider);
}

