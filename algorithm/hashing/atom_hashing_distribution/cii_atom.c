// This file is modified from: https://github.com/drh/cii/blob/master/src/atom.c
#include "cii_atom.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef BUCKET_SIZE
# include "cii_atom_config.h"
#endif

#define NELEMS(x) ((sizeof (x))/(sizeof ((x)[0])))
#define ALLOC(nbytes) malloc((nbytes))
#define FREE(p) free((p))
#define UNUSED(arg) ((void)(arg))

static struct atom {
    struct atom *link;
    int len;
    char *str;
} *buckets[BUCKET_SIZE];

static unsigned long scatter[] = {
2078917053, 143302914, 1027100827, 1953210302, 755253631, 2002600785,
1405390230, 45248011, 1099951567, 433832350, 2018585307, 438263339,
813528929, 1703199216, 618906479, 573714703, 766270699, 275680090,
1510320440, 1583583926, 1723401032, 1965443329, 1098183682, 1636505764,
980071615, 1011597961, 643279273, 1315461275, 157584038, 1069844923,
471560540, 89017443, 1213147837, 1498661368, 2042227746, 1968401469,
1353778505, 1300134328, 2013649480, 306246424, 1733966678, 1884751139,
744509763, 400011959, 1440466707, 1363416242, 973726663, 59253759,
1639096332, 336563455, 1642837685, 1215013716, 154523136, 593537720,
704035832, 1134594751, 1605135681, 1347315106, 302572379, 1762719719,
269676381, 774132919, 1851737163, 1482824219, 125310639, 1746481261,
1303742040, 1479089144, 899131941, 1169907872, 1785335569, 485614972,
907175364, 382361684, 885626931, 200158423, 1745777927, 1859353594,
259412182, 1237390611, 48433401, 1902249868, 304920680, 202956538,
348303940, 1008956512, 1337551289, 1953439621, 208787970, 1640123668,
1568675693, 478464352, 266772940, 1272929208, 1961288571, 392083579,
871926821, 1117546963, 1871172724, 1771058762, 139971187, 1509024645,
109190086, 1047146551, 1891386329, 994817018, 1247304975, 1489680608,
706686964, 1506717157, 579587572, 755120366, 1261483377, 884508252,
958076904, 1609787317, 1893464764, 148144545, 1415743291, 2102252735,
1788268214, 836935336, 433233439, 2055041154, 2109864544, 247038362,
299641085, 834307717, 1364585325, 23330161, 457882831, 1504556512,
1532354806, 567072918, 404219416, 1276257488, 1561889936, 1651524391,
618454448, 121093252, 1010757900, 1198042020, 876213618, 124757630,
2082550272, 1834290522, 1734544947, 1828531389, 1982435068, 1002804590,
1783300476, 1623219634, 1839739926, 69050267, 1530777140, 1802120822,
316088629, 1830418225, 488944891, 1680673954, 1853748387, 946827723,
1037746818, 1238619545, 1513900641, 1441966234, 367393385, 928306929,
946006977, 985847834, 1049400181, 1956764878, 36406206, 1925613800,
2081522508, 2118956479, 1612420674, 1668583807, 1800004220, 1447372094,
523904750, 1435821048, 923108080, 216161028, 1504871315, 306401572,
2018281851, 1820959944, 2136819798, 359743094, 1354150250, 1843084537,
1306570817, 244413420, 934220434, 672987810, 1686379655, 1301613820,
1601294739, 484902984, 139978006, 503211273, 294184214, 176384212,
281341425, 228223074, 147857043, 1893762099, 1896806882, 1947861263,
1193650546, 273227984, 1236198663, 2116758626, 489389012, 593586330,
275676551, 360187215, 267062626, 265012701, 719930310, 1621212876,
2108097238, 2026501127, 1865626297, 894834024, 552005290, 1404522304,
48964196, 5816381, 1889425288, 188942202, 509027654, 36125855,
365326415, 790369079, 264348929, 513183458, 536647531, 13672163,
313561074, 1730298077, 286900147, 1549759737, 1699573055, 776289160,
2143346068, 1975249606, 1136476375, 262925046, 92778659, 1856406685,
1884137923, 53392249, 1735424165, 1602280572
};

const char *Atom_string(const char *str) {
    assert(str);
    return Atom_new(str, (int)strlen(str));
}

const char *Atom_int(long n) {
    char str[43];
    char *s = str + sizeof str;
    unsigned long m;
    if (n == LONG_MIN)
        m = LONG_MAX + 1UL;
    else if (n < 0)
        m = -n;
    else
        m = n;
    do
        *--s = m%10 + '0';
    while ((m /= 10) > 0);
    if (n < 0)
        *--s = '-';
    return Atom_new(s, (int)((str + sizeof str) - s));
}

unsigned long Atom_hash(const char *str, int len) {
    unsigned long h;
    int i;

    assert(str);
    assert(len >= 0);

    for (h = 0, i = 0; i < len; i++)
        h = (h<<1) + scatter[(unsigned char)str[i]];

    return h;    
}

#if 0
# define HASH_STR(str, len) (Atom_hash((str), (len)) & (NELEMS(buckets) - 1))
#else
# define HASH_STR(str, len) (Atom_hash((str), (len)) % NELEMS(buckets))
#endif

const char *Atom_new(const char *str, int len) {
    unsigned long h;
    int i;
    struct atom *p;
    assert(str);
    assert(len >= 0);

    h = HASH_STR(str, len);

    for (p = buckets[h]; p; p = p->link)
        if (len == p->len) {
#if 0
            for (i = 0; i < len && p->str[i] == str[i]; )
                i++;
            if (i == len)
                return p->str;
#else
            UNUSED(i);
            if (memcmp(p->str, str, len) == 0)
                return p->str;
#endif
        }

    p = ALLOC(sizeof (*p) + len + 1);
    p->len = len;
    p->str = (char *)(p + 1);
    if (len > 0)
        memcpy(p->str, str, len);
    p->str[len] = '\0';
    p->link = buckets[h];
    buckets[h] = p;
    return p->str;
}


typedef struct atom_pos_t {
    struct atom **bucket;
    struct atom *prev;
    struct atom *pos; // atom position
} atom_pos_t;


// Find specified atom
atom_pos_t Atom_find(const char *str)
{
    struct atom *p;
    struct atom *prev;
    atom_pos_t pos = { NULL, NULL, NULL };
    unsigned long h;

    assert(str);

    h = HASH_STR(str, (int)strlen(str));

    prev = NULL;
    p = buckets[h];

    while (p != NULL) {
        if (p->str == str) {
            pos.bucket = buckets + h;
            pos.prev = prev;
            pos.pos = p;
            return pos;
        }

        prev = p;
        p = p->link;
    }

    return pos;
}


int Atom_length(const char *str) {
    struct atom *p = Atom_find(str).pos;
    if (p != NULL)
        return p->len;

    assert(0);
    return 0;
}


int Atom_contains(const char *str)
{
    return Atom_find(str).pos != NULL;
}


void Atom_free(const char *str)
{
    atom_pos_t p = Atom_find(str);

    if (p.pos == NULL) {
        assert(p.bucket = NULL);
        assert(p.prev == NULL);
        assert(0);
        return;
    }

    assert(p.bucket != NULL);

    if (p.prev == NULL)
        *p.bucket = p.pos->link;
    else
        p.prev->link = p.pos->link;
    FREE(p.pos);
}

void Atom_free_bucket(size_t bucket_no)
{
    struct atom *p, *q;

    assert(bucket_no < NELEMS(buckets));

    p = buckets[bucket_no];

    while (p) {
        q = p;
        p = p->link;
        FREE(q);
    }

    buckets[bucket_no] = NULL;
}

void Atom_reset(void)
{
    for (size_t i = 0; i < NELEMS(buckets); ++i)
        Atom_free_bucket(i);
}

size_t Atom_bench_buckets_size(void)
{
    return BUCKET_SIZE;
}

int Atom_bench_bucket_len(size_t bucket_no)
{
    struct atom *p = NULL;
    int len = 0;

    assert(bucket_no < BUCKET_SIZE);
    if (bucket_no >= BUCKET_SIZE)
        return -1;

    p = buckets[bucket_no];
    while (p != NULL) {
        p = p->link;
        ++len;
    }

    return len;
}


// References:
// https://github.com/sheredom/hashmap.h
