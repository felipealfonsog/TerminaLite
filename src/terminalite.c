#include <gtk/gtk.h>
#include <vte/vte.h>

static void child_exited(VteTerminal *terminal) {
    gtk_main_quit();
}

int main(int argc, char **argv) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "TerminaLite");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    GtkWidget *terminal = vte_terminal_new();

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(terminal, "child-exited", G_CALLBACK(child_exited), NULL);

    gtk_container_add(GTK_CONTAINER(window), terminal);

    const char *cmd[] = {"/bin/zsh", NULL};
    vte_terminal_spawn_sync(VTE_TERMINAL(terminal), VTE_PTY_DEFAULT, NULL, (char **)cmd, NULL, 0, NULL, NULL, NULL, NULL, NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
