#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#else
#include <strings.h>
#endif

#include "internal.h"
#include "die.h"
#include "strlimcpy.h"
#include "token.h"
#include "ruby_res.h"

#define MAXCOMPLETENAME 1024            /* max size of complete name of class */
#define MAXCLASSSTACK   100             /* max size of class stack */

void
ruby(const struct parser_param *param)
{
        int c;
        int level;                                      /* brace level */
        const char *interested = NULL;

        if (!opentoken(param->file))
                die("'%s' cannot open.", param->file);
        while ((c = nexttoken(interested, ruby_reserved_word)) != EOF) {
                switch (c) {
                case SYMBOL:
                        PUT(PARSER_REF_SYM, token, lineno, sp);
                        break;
                case RUBY_CLASS:
                case RUBY_MODULE:
                case RUBY_DEF:
                        if ((c = nexttoken(interested, ruby_reserved_word)) == SYMBOL) {
                                PUT(PARSER_DEF, token, lineno, sp);
                        }
                        break;
                default:
                        break;
                }
        }
        closetoken();
}
