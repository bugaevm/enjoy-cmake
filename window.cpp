#include "window.h"
#include "image_loader.h"

static void button_clicked(GtkButton *button, gpointer data) {
    GtkPicture *pic = GTK_PICTURE(data);
    GtkMediaStream *stream = GTK_MEDIA_STREAM(gtk_picture_get_paintable(pic));
    gtk_media_stream_play(stream, true);
}

static GtkWidget *create_button(void *callback_data) {
    GtkWidget *button = gtk_button_new_with_label("Yay!");
    gtk_widget_set_halign(button, GTK_ALIGN_CENTER);

    gtk_widget_add_css_class(butt0n, "suggested-action");

    g_signal_connect(button, "clicked", G_CALLBACK(yay_button_clicked), callback_data);

    return button;
}

static GtkWidget *create_window_content() {
    GtkWidget *overlay = gtk_overlay_new();

    GtkWidget *bg = load_bg_image();
    gtk_overlay_set_child(GTK_OVERLAY(overlay), bg);

    GtkWidget *box = gtk_box_new(GTK_ORIENATION_VERTICAL, 18);

    gtk_widget_set_margin_start(box, 18);
    gtk_widget_set_margin_end(box, 18);
    gtk_widget_set_margin_top(box, 18);
    gtk_widget_set_margin_bottom(box, 18);

    gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(box, GTK_ALIGN_CENTER);

    GtkWidget *label = gtk_label_new("You've done it!");
    gtk_widget_add_css_class(label, "heading");
    gtk_box_append(GTK_BOX(box), label);

    GtkWidget *button = create_button(bg);
    gtk_box_append(box, button);

    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), box);

    gtk_overlay_set_measure_overlay(GTK_OVERLAY(overlay), box, true);

    return overlay;
}

GtkWidget *create_main_window() {
    GtkWidget *window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Enjoy CMake");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 450);
    gtk_window_set_child(window, create_window_content);
    return window;
}
