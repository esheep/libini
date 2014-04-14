#ifndef LIBINI_H_
#define LIBINI_H_

int read_profile_string(const char *appname, const char *keyname, const char *defval,
        char *value, unsigned int size, const char *filename);

int write_profile_string(const char *appname, const char *keyname, const char *value,
        const char *filename);
#endif
