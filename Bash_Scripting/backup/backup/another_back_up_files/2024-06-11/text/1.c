#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
void error_n_die(char *fmt, ...)
{
    int error_save;
    va_list ap;
    error_save = errno;
    va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    fprintf(stdout, "\n");
    fflush(stdout);
    if (error_save != 0)
    {
        fprintf(stdout, "(error = %d):%s \n", error_save, strerror(error_save));
        fprintf(stdout, "\n");
        fflush(stdout);
    }
    va_end(ap);
}
int main()
{
    error_n_die("hello .", 1, 2, 3);
}
