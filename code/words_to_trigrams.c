#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Trigram {
	char c[3];
};

struct Trigram_list {
	size_t nelem;
	struct Trigram *tgrams;
};

struct Trigram_list *
makeTrigramList(size_t len)
{
	int i = 0;
	if (len == 0) {
		fprintf(stderr, "word is too small for trigram creation\n");
		return NULL;
	}
	/* alloc the head and the required number of nodes */
	struct Trigram_list *tl = malloc(sizeof(struct Trigram_list));
	struct Trigram *tn = malloc(len*sizeof(struct Trigram));
	if (tl == NULL | tn == NULL) {
		fprintf(stderr, "could not allocate Trigram list\n");
		return NULL;
	}
	tl->nelem = len;
	tl->tgrams = tn;
	return tl;
}

void
populateTrigrams(struct Trigram_list *l, char *w)
{
	int i = 0, j = 0, ind=-2;
	/* last trigram */
	for (i = 0; i < l->nelem; i++) {
		for (j = 0; j < 3; j++) {
			if (ind < 0 || ind >= l->nelem-2) {
				l->tgrams[i].c[j] = '_';
			} else {
				l->tgrams[i].c[j] = w[ind];
			}
			ind++;
		}
		ind-=2;
	}
}

void
freeTrigramList(struct Trigram_list *a)
{
	free(a->tgrams);
	free(a);
}

void
printTrigrams(struct Trigram_list *a)
{
	int i=0;
	for (i=0;i<a->nelem;i++)
		printf(" [%c %c %c] ", a->tgrams[i].c[0], a->tgrams[i].c[1], a->tgrams[i].c[2]);
	printf("\n");
}

/*
 * word becomes __w, _wo, wor
 * ord, rd_, d__
 * foobar becomes __f, _fo, foo
 * oob, oba, bar, ar_, r__
 * a gives __a, _a_, a__
 * 4->6 , 6->8, 
 */
size_t
wordToTrigramsNum(char *w)
{
	return strlen(w)+2;
}

int
main(int argc, char *argv[])
{
	int i;
	struct Trigram_list *tl;
	for (i=1; i<argc; i++) {
		tl = makeTrigramList(wordToTrigramsNum(argv[i]));
		populateTrigrams(tl, argv[i]);
		printf("arg: %s trigrams ", argv[i]);
		printTrigrams(tl);
		freeTrigramList(tl);
	}
	return 0;
}
