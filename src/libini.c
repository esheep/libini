#include <libini.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct _key_tag key_tag_t;
struct _key_tag
{
    char *keyname;
    char *value;
    key_tag_t *next;
};

typedef struct _section_tag section_tag_t;
struct _section_tag
{
    char *appname;
    key_tag_t *key;
    section_tag_t *next;
};

int add_section(section_tag_t *section, const char *appname, key_tag_t *key)
{
    int n;

    if (!section->appname)
    {
        n = strlen(appname) + 1;
        section->appname = (char *)malloc(n);
        snprintf(section->appname, n, "%s", appname);
    }

    section->key = key;
    section->next = NULL;

    return (0);
}

int add_key(key_tag_t *key, const char *keyname, const char *value)
{
    int n;

    if (!key->keyname)
    {
        n = strlen(keyname) + 1;
        key->keyname = (char *)malloc(n);
        snprintf(key->keyname, n, "%s", keyname);
    }

    if (!key->value)
    {
        n = strlen(value) + 1;
        key->value = (char *)malloc(n);
        snprintf(key->value, n, "%s", value ? value : "");
    }

    key->next = NULL;

    return (0);
}

int fill_result(char *result, unsigned int size, const char *value)
{
    const char *tval = value ? value : "";

    if (!result)
    {
        size = strlen(tval) + 1;
        result = (char *)malloc(size);
    }

    snprintf(result, size, "%s", tval);
    return (0);
}

section_tag_t *parse_ini(const char *filename)
{
    section_tag_t *section;

    //TODO parse ini file
    section = NULL;

    return (section);
}

int read_profile_string(const char *appname, const char *keyname, const char *defval,
        char *value, unsigned int size, const char *filename)
{
    section_tag_t *head_section, *prev_section, *psection;
    key_tag_t *prev_key, *pkey;
    bool find_section, find_key;
    int n;

    if (!appname || appname[0] == '\0' || !keyname || keyname[0] == '\0' ||
            !filename || filename[0] == '\0')
        return -1;

    find_section = false;
    find_key = false;
    n = 0;

    head_section = parse_ini(filename);
    if (!head_section)
        return -1;

    prev_section = head_section;

    while ((psection = prev_section->next))
    {
        if (strcmp(psection->appname, appname) == 0)
        {
            find_section = true;
            prev_key = psection->key;

            while ((pkey = prev_key->next))
            {
                if (strcmp(pkey->keyname, keyname) == 0)
                {
                    find_key = true;

                    if (pkey->value)
                    {
                        fill_result(value, size, pkey->value);
                    }
                    else
                    {

                        fill_result(value, size, defval);
                    }

                    break;
                }

                prev_key = prev_key->next;
            }

            if (!find_key)
            {
                key_tag_t *tkey = (key_tag_t *)malloc(sizeof(key_tag_t));
                add_key(tkey, keyname, defval);
                prev_key->next = tkey;
            }

            break;
        }

        prev_section = prev_section->next;
    }

    if (!find_section)
    {
        section_tag_t *tsection = (section_tag_t *)malloc(sizeof(section_tag_t));
        key_tag_t *tkey = (key_tag_t *)malloc(sizeof(key_tag_t));

        add_key(tkey, keyname, defval ? defval : "");
        add_section(tsection, appname, tkey);
        prev_section = tsection;
    }

    return (n);
}

int write_profile_string(const char *appname, const char *keyname, const char *value,
        const char *filename)
{
    //TODO write profile
    return (0);
}
