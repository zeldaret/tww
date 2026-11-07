#include "dolphin/dvd/dvdidutils.h"
#include "dolphin/os/OS.h"
#include <string.h>

static u32 strnlen(const char* str, u32 maxlen) {
    u32 i;

    for (i = 0; i < maxlen; i++) {
        if (*str++ == 0) {
            return i;
        }
    }

    return maxlen;
}

int DVDCompareDiskID(DVDDiskID* id1, DVDDiskID* id2) {
#ifdef DEBUG
    const char* game1;
    const char* game2;
    const char* company1;
    const char* company2;
    u8 diskNum1;
    u8 diskNum2;
    u8 version1;
    u8 version2;
    u32 length;

    ASSERTMSGLINE(64, id1, "DVDCompareDiskID(): Specified id1 is NULL\n");
    ASSERTMSGLINE(65, id2, "DVDCompareDiskID(): Specified id2 is NULL\n");

    game1 = id1->game_name;
    game2 = id2->game_name;
    company1 = id1->company;
    company2 = id2->company;
    diskNum1 = id1->disk_number;
    diskNum2 = id2->disk_number;
    version1 = id1->game_version;
    version2 = id2->game_version;

    length = strnlen(game1, sizeof(game1));
    ASSERTMSGLINE(78, length == 0 || length == 4, "DVDCompareDiskID(): Specified game name for id1 is neither NULL nor 4 character long\n");
    ASSERTMSGLINE(79, company1, "DVDCompareDiskID(): Specified company name for id1 is NULL\n");
    ASSERTMSGLINE(80, company1[1] != 0, "DVDCompareDiskID(): Specified company name for id1 is not 2 character long\n");
    ASSERTMSGLINE(81, diskNum1 == 0xFF || ((diskNum1 / 16) < 10 && diskNum1 % 16 < 10), "DVDCompareDiskID(): Specified disk number for id1 is neither 0xff nor a BCD number");
    ASSERTMSGLINE(82, version1 == 0xFF || ((version1 / 16) < 10 && version1 % 16 < 10), "DVDCompareDiskID(): Specified version number for id1 is neither 0xff nor a BCD number");

    length = strnlen(game2, sizeof(game2));
    ASSERTMSGLINE(85, length == 0 || length == 4, "DVDCompareDiskID(): Specified game name for id2 is neither NULL nor 4 character long\n");
    ASSERTMSGLINE(86, company2, "DVDCompareDiskID(): Specified company name for id2 is NULL\n");
    ASSERTMSGLINE(87, company2[1] != 0, "DVDCompareDiskID(): Specified company name for id2 is not 2 character long\n");
    ASSERTMSGLINE(88, diskNum2 == 0xFF || ((diskNum2 / 16) < 10 && diskNum2 % 16 < 10), "DVDCompareDiskID(): Specified disk number for id2 is neither 0xff nor a BCD number");
    ASSERTMSGLINE(89, version2 == 0xFF || ((version2 / 16) < 10 && version2 % 16 < 10), "DVDCompareDiskID(): Specified version number for id2 is neither 0xff nor a BCD number");
#endif

    if (id1->game_name[0] != 0 && id2->game_name[0] != 0 && strncmp(id1->game_name, id2->game_name, 4) != 0) {
        return 0;
    }

    if (id1->company[0] == 0 || id2->company[0] == 0 || strncmp(id1->company, id2->company, 2) != 0) {
        return 0;
    }

    if (id1->disk_number != 0xFF && id2->disk_number != 0xFF && id1->disk_number != id2->disk_number) {
        return 0;
    }

    if (id1->game_version != 0xFF && id2->game_version != 0xFF && id1->game_version != id2->game_version) {
        return 0;
    }

    return 1;
}

DVDDiskID* DVDGenerateDiskID(DVDDiskID* id, const char* game, const char* company, u8 diskNum, u8 version) {
    ASSERTMSGLINE(123, id, "DVDGenerateDiskID(): Specified id is NULL\n");
    ASSERTMSGLINE(124, game == NULL || strlen(game) == 4, "DVDGenerateDiskID(): Specified game name is neither NULL nor 4 character long\n");
    ASSERTMSGLINE(125, company, "DVDGenerateDiskID(): Specified company name is NULL\n");
    ASSERTMSGLINE(126, strlen(company) == 2, "DVDGenerateDiskID(): Specified company name is not 2 character long\n");
    ASSERTMSGLINE(127, diskNum == 0xFF || ((diskNum / 16) < 10 && diskNum % 16 < 10), "DVDGenerateDiskID(): Specified disk number is neither 0xff nor a BCD number");
    ASSERTMSGLINE(128, version == 0xFF || ((version / 16) < 10 && version % 16 < 10), "DVDGenerateDiskID(): Specified version number is neither 0xff nor a BCD number");

    memset(id, 0, sizeof(DVDDiskID));

    if (game != NULL) {
        strncpy(id->game_name, game, 4);
    }

    if (company != NULL) {
        strncpy(id->company, company, 2);
    }

    id->disk_number = diskNum;
    id->game_version = version;
    return id;
}
