/* 
 * Extracts free text from an mdoc document.
 * dsp@2f30.org 03/11/20
 */
#include <assert.h>
#include <ctype.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

#include <mandoc.h> /* required by mandoc_parse */
#include <roff.h> /* required by mandoc_parse */
#include <mandoc_parse.h>

static void usage(char *);
static void scanmpage(struct mparse *, char *);
static void doroff(const struct roff_node *);
static void pstring(const char *);


static void
usage(char *progname)
{
	fprintf(stderr, "%s mdoc\n", progname);
	fprintf(stderr, "will parse the mdoc file and dump all free text.\n");
}

int
main(int argc, char *argv[])
{
	struct mparse *mp;
	int           fd;
	if (argc != 2) {
		usage(argv[0]);
		return 1;
	}
	/* initialize the mdoc parsing sequence */
        mchars_alloc();
        mp = mparse_alloc(MPARSE_SO | MPARSE_UTF8 | MPARSE_LATIN1 |
            MPARSE_VALIDATE, MANDOC_OS_OTHER, NULL);
        assert(mp);
	
	fd = mparse_open(mp, argv[1]);
	if (fd < 0 ) {
		fprintf(stderr, "error opening file :%s\n", argv[1]);
		return 1;
	}
	mparse_readfd(mp, fd, argv[1]);
	scanmpage(mp, argv[1]);
	close(fd);
	mparse_free(mp);
	mchars_free();
	fprintf(stdout, "exiting\n");
	return 0;
}

static void
scanmpage(struct mparse *mp, char *fname)
{
	fprintf(stdout, "operating on file %s\n", fname);
	struct roff_meta *meta;
	meta = mparse_result(mp); 
	doroff(meta->first->child);
	
}

/* bulk of code borrowed from demandoc */
static void
pstring(const char *p)
{
        enum mandoc_esc  esc;
        const char      *start, *end;
        int              emit;

again:
        if ('\0' != *p) {
                while (isspace((unsigned char)*p)) {
                        p++;
		}

                while ('\'' == *p || '"' == *p) {
                        p++;
		}

                emit = isalpha((unsigned char)p[0]) &&
                        isalpha((unsigned char)p[1]);

                for (start = p; '\0' != *p; p++) {
                        if ('\\' == *p) {
                                p++;
                                esc = mandoc_escape(&p, NULL, NULL);
                                if (ESCAPE_ERROR == esc) {
                                        return;
				}
                                emit = 0;
                        } else if (isspace((unsigned char)*p)) {
                                break; 
			}
		}

                end = p - 1;

                while (end > start)
                        if ('\'' == *end || '"' == *end ||
			    ',' == *end || '.' == *end)
                                end--;
                        else
                                break;

                if (emit && end - start >= 1) {
                        for ( ; start <= end; start++) {
                                if (ASCII_HYPH == *start) {
                                        putchar('-');
				}
                                else {
                                        putchar((unsigned char)*start);
				}
			}
                        putchar(' ');
                }

                if (isspace((unsigned char)*p))
                        goto again;

                return;
        }

        /*
         * Print the input word, skipping any special characters.
         */
        while ('\0' != *p) {
                if ('\\' == *p) {
                        p++;
                        esc = mandoc_escape(&p, NULL, NULL);
                        if (ESCAPE_ERROR == esc) {
                                break;
			}
                } else {
                        putchar((unsigned char )*p++);
                }
	}
}

static void
doroff(const struct roff_node *p)
{
        for ( ; p; p = p->next) {
                if (NODE_LINE & p->flags) {
		}
                if (ROFFT_TEXT == p->type) {
			pstring(p->string);
		}
                if (p->child) {
			/* fprintf(stdout, "RECURSING\n"); */
                        doroff(p->child);
		}
        }
}
