#include <stdio.h>

version = Foo;
version = 2;
version = none;
version = all;
debug = Bar;
debug = 3;
version = SpecOuter;

version(Foo) {
    static int file_value = 11;
    static int file_nested = 12;
} else {
    static int file_value = 99;
}

debug {
    static int file_debug = 13;
} else {
    static int file_debug = 98;
}

static int values[64];
static int nvalues;

static void put(int v)
{
    values[nvalues++] = v;
}

static void run_conditions(void)
{
    version(Foo) put(1); else put(2);
    version(Bar) put(3); else put(4);
    version(Nope) put(5); else put(6);
    version(0) put(7);
    version(2) put(8);
    version(3) put(9); else put(10);
    debug put(11); else put(12);
    debug(Bar) put(13); else put(14);
    debug(Nope) put(15); else put(16);
    debug(3) put(17); else put(18);
    debug(4) put(19); else put(20);
    debug(0) put(21);
    version(unittest) put(22); else put(23);
    version(assert) put(24); else put(25);
    version(D_Version2) put(26);
    version(Nope) { int bad = ; } else put(27);
    version(Nope) put(28); else version(Foo) put(29); else put(30);
    debug(Bar) { put(31); } else { put(32); }
    version(Foo) if (1) put(33); else put(34);
    else put(35);
    version(Foo) {
        version(Nope) put(36); else put(37);
        debug(Bar) put(38); else put(39);
    }
    debug = 0;
    debug put(40); else put(41);
    debug(Bar) put(42); else put(43);
    debug = 3;
    debug put(44); else put(45);
    version(all) put(46); else put(47);
    version(none) put(48); else put(49);
}

/* Specifications inside a compiled block are applied in order.  */
version(SpecOuter) {
    version = Late;
    version = 7;
    debug = LateDebug;
} else {
    version = NotLate;
}

version(Late) {
    static int late_value = 14;
} else {
    static int late_value = 98;
}

version(7) static int late_level = 15;
version(8) static int late_level8 = 16; else static int late_level8 = 99;
debug(LateDebug) static int late_debug = 17;

/* Specifications inside a skipped block must not be applied.  */
version(Skipped) {
    version = ShouldNotApply;
    debug = ShouldNotApplyDebug;
}

version(ShouldNotApply) static int skipped_version = 98;
else static int skipped_version = 18;
debug(ShouldNotApplyDebug) static int skipped_debug = 98;
else static int skipped_debug = 19;

int main(void)
{
    int i;
    run_conditions();
    printf("file %d %d %d\n", file_value, file_nested, file_debug);
    printf("late %d %d %d %d %d %d\n", late_value, late_level,
           late_level8, late_debug, skipped_version, skipped_debug);
    for (i = 0; i < nvalues; ++i)
        printf("%d%s", values[i], i + 1 == nvalues ? "\n" : " ");
    return 0;
}
