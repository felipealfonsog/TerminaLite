#include <gtk/gtk.h>
#include <vte/vte.h>

static void
on_ready_callback(VteTerminal *terminal, gpointer user_data) {
    // Callback when the terminal is ready
}

int main(int argc, char **argv) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "TerminaLite");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    GtkWidget *terminal = vte_terminal_new();
    gtk_container_add(GTK_CONTAINER(window), terminal);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Prepare the command to run in the terminal
    gchar *argv_cmd[] = { g_strdup("/bin/zsh"), NULL };

    // Start the terminal with the command
    vte_terminal_spawn_async(
        VTE_TERMINAL(terminal),
        VTE_PTY_DEFAULT, // Use default pseudoterminal
        NULL,            // Working directory (NULL for default)
        argv_cmd,        // Command to run
        NULL,            // Environment variables (NULL for default)
        NULL,            // Cancellable (NULL for no cancellation)
        NULL,            // Async ready callback
        on_ready_callback, // Callback function
        NULL             // User data for callback
    );

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
