#include "cfgopts.h"

#ifdef S_SPLINT_S
#include "splint.h"
#endif

/**
 * Read the private key from the blow.ini file
 * @param section section target "servertag:nick/#channel"
 * @param key key - normaly is "key"
 * @param default_value default value to write in buffer if something bad happens
 * @param buffer value buffer destination
 * @param buflen length of the destination buffer
 * @param filepath file path to blow.ini
 * @return the length of the buffer
 */
int GetPrivateProfileString(const char *section, const char *key, const char *default_value, char *buffer, int buflen, const char *filepath)
{
    GKeyFile *key_file;
    GError *error = NULL;
    gchar *value = NULL;

    key_file = g_key_file_new();

    // If file was read OK...
    if ((int) g_key_file_load_from_file(key_file, filepath, G_KEY_FILE_NONE, NULL)==1) {
        // If the record was found...
        value = g_key_file_get_string(key_file, section, key, &error);
        if (value != NULL && error == NULL) {
            strncpy(buffer, value, (size_t)buflen);
        }
    }

    g_free(value);
    g_key_file_free(key_file);

    // In case of any error...
    if (error != NULL) {
        strncpy(buffer, default_value, (size_t)buflen);
    }

    return (int) strlen(buffer);
}

/**
 * Write the private key to the blow.ini file
 * @param section section target "servertag:nick/#channel"
 * @param key key - normaly is "key"
 * @param value value to write
 * @param filepath file path to blow.ini
 * @return 1 if everything is ok -1 if not
 */
int WritePrivateProfileString(const char *section, const char *key, const char *value, const char *filepath)
{
    GKeyFile *key_file;
    GError *error = NULL;
    FILE *outfile = NULL;
    gsize length = 0;
    gchar *config = NULL;

    key_file = g_key_file_new();

    (void) g_key_file_load_from_file(key_file, filepath, G_KEY_FILE_NONE, NULL);
    g_key_file_set_string(key_file, section, key, value);

    // Get the content of the config to a string...
    config = g_key_file_to_data(key_file, &length, &error);
    if (error == NULL) { // If everything is ok...
        outfile = fopen(filepath, "w");
        if (outfile != NULL) {
            (void) fwrite(config, sizeof(gchar), (size_t) length, outfile);
            (void) fclose(outfile);
        }
    }

    g_free(config);
    g_key_file_free(key_file);

    if ((error != NULL) || (outfile == NULL)) {
        return -1;
    }

    return 1;
}
