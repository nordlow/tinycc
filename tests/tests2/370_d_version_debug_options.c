#include <stdio.h>

int main(void)
{
    version(CmdVersion) printf("version id\n"); else printf("no version id\n");
    version(2) printf("version level 2\n"); else printf("no version level 2\n");
    version(3) printf("version level 3\n"); else printf("no version level 3\n");
    version(none) printf("version none\n"); else printf("no version none\n");
    debug printf("debug on\n"); else printf("debug off\n");
    debug(CmdDebug) printf("debug id\n"); else printf("no debug id\n");
    debug(2) printf("debug level 2\n"); else printf("no debug level 2\n");
    debug(3) printf("debug level 3\n"); else printf("no debug level 3\n");
    return 0;
}
