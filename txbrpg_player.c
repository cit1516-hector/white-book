/*//
//  txbrpg_player.c
//  TXBRPG
//
//  Created by Hector Denis on 29/04/17.
//  Copyright © 2017 Hector Denis. All rights reserved.
//*/

#include "txbrpg_player.h"

int rpg_PlayerGenerateStats(Player* plr) {
    if (NULL == plr) {
        return -1;
    }
    plr->hpa = plr->hpm = hpl_RandRange(10, 14);
    plr->lvl = 1;
    plr->exp = 0;
    plr->lck = 0;
    plr->gld = 0;
    plr->str = plr->dex = plr->con = plr->itl = plr->wis = plr->cha = 12;
    plr->spd = 8;
    
    switch (plr->race) {
        case race_human:
            plr->hpa = ++plr->hpm;
            plr->str++;
            break;
        case race_elf:
            plr->itl += 2;
            plr->dex++;
            plr->cha++;
            plr->str--;
            break;
        case race_dwarf:
            plr->hpa = ++plr->hpm;
            plr->con++;
            plr->dex++;
            plr->cha--;
            break;
        case race_gnome:
            plr->itl++;
            break;
        case race_orc:
            plr->str += 2;
            plr->itl--;
            plr->wis--;
            plr->cha -= 2;
            break;
        default:
            break;
    }
    switch (plr->gender) {
        case gender_male:
            plr->str++;
            break;
        case gender_female:
            plr->cha++;
            break;
        case gender_androgynous:
            plr->con++;
        default:
            break;
    }
    
    return 1;
}
int rpg_PlayerCreate(Player* plr) {
    if (NULL == plr) {
        return -1;
    }
    plr->race = rpg_PlayerChooseRace();
    plr->role = rpg_PlayerChooseRole();
    plr->gender = rpg_PlayerChooseGender();
    rpg_PlayerChooseString(plr->name_player, "How do you want to be called?");
    rpg_PlayerChooseString(plr->name_class, "What is your class name?");
    rpg_PlayerGenerateStats(plr);
    return 1;
}
Player* rpg_PlayerAlloc(void) {
    Player* plr = hpl_Malloc(sizeof(*plr));
    if (NULL == plr) return NULL;
    memset(plr, 0, sizeof(*plr));
    
    plr->name_player = hpl_StringAlloc(64);
    if (NULL == plr->name_player) return NULL;
    plr->name_class = hpl_StringAlloc(64);
    if (NULL == plr->name_class) return NULL;
    return plr;
}
int rpg_PlayerFree(Player* plr) {
    if (NULL == plr) {
        return -1;
    }
    hpl_StringFree(plr->name_class);
    plr->name_class = NULL;
    hpl_StringFree(plr->name_player);
    plr->name_player = NULL;
    free(plr);
    return 1;
}
int rpg_PlayerPrintf(Player* plr, FILE* stream) {
    if (NULL == plr || NULL == stream) {
        return -1;
    }
    fprintf(stream, "%s\n", plr->name_class->str);
    fprintf(stream, "%s\n", plr->name_player->str);
    fprintf(stream, "%u\n", plr->race);
    fprintf(stream, "%u\n", plr->gender);
    fprintf(stream, "%u\n", plr->role);
    fprintf(stream, "%ld\n", plr->hpm);
    fprintf(stream, "%ld\n", plr->hpa);
    fprintf(stream, "%ld\n", plr->lvl);
    fprintf(stream, "%ld\n", plr->exp);
    fprintf(stream, "%ld\n", plr->gld);
    fprintf(stream, "%ld\n", plr->str);
    fprintf(stream, "%ld\n", plr->dex);
    fprintf(stream, "%ld\n", plr->con);
    fprintf(stream, "%ld\n", plr->itl);
    fprintf(stream, "%ld\n", plr->wis);
    fprintf(stream, "%ld\n", plr->cha);
    fprintf(stream, "%ld\n", plr->spd);
    
    return 1;
}
int rpg_PlayerReadf(Player* plr, FILE* stream) {
    if (NULL == plr || NULL == stream) {
        return -1;
    }
    fscanf(stream, "%s", plr->name_class->str);
    fscanf(stream, "%s", plr->name_player->str);
    fscanf(stream, "%u", &plr->race);
    fscanf(stream, "%u", &plr->gender);
    fscanf(stream, "%u", &plr->role);
    fscanf(stream, "%ld", &plr->hpm);
    fscanf(stream, "%ld", &plr->hpa);
    fscanf(stream, "%ld", &plr->lvl);
    fscanf(stream, "%ld", &plr->exp);
    fscanf(stream, "%ld", &plr->gld);
    fscanf(stream, "%ld", &plr->str);
    fscanf(stream, "%ld", &plr->dex);
    fscanf(stream, "%ld", &plr->con);
    fscanf(stream, "%ld", &plr->itl);
    fscanf(stream, "%ld", &plr->wis);
    fscanf(stream, "%ld", &plr->cha);
    fscanf(stream, "%ld", &plr->spd);
    return 1;
}
int rpg_PlayerPrintReadable(Player* plr, FILE* stream) {
    if (NULL == plr || NULL == stream ) {
        return -1;
    }
    /*Keep order in sync with plrPrintf/scanf*/
    fprintf(stream, "Class: %s\n", plr->name_class->str);
    fprintf(stream, "Username: %s\n", plr->name_player->str);
    fprintf(stream, "Race: %u/%s\n", plr->race, rpg_RaceToString(plr->race));
    fprintf(stream, "Gender: %u/%s\n", plr->gender, rpg_GenderToString(plr->gender));
    fprintf(stream, "Role: %u/%s\n", plr->role, rpg_RoleToString(plr->role));
    fprintf(stream, "HPM: %ld\n", plr->hpm);
    fprintf(stream, "HPA: %ld\n", plr->hpa);
    fprintf(stream, "LVL: %ld\n", plr->lvl);
    fprintf(stream, "EXP: %ld\n", plr->exp);
    fprintf(stream, "GLD: %ld\n", plr->gld);
    fprintf(stream, "STR: %ld\n", plr->str);
    fprintf(stream, "DEX: %ld\n", plr->dex);
    fprintf(stream, "CON: %ld\n", plr->con);
    fprintf(stream, "ITL: %ld\n", plr->itl);
    fprintf(stream, "WIS: %ld\n", plr->wis);
    fprintf(stream, "CHA: %ld\n", plr->cha);
    fprintf(stream, "SPD: %ld\n", plr->spd);
    return 1;
}
int rpg_PlayerSave(Player* plr, const char* filename) {
    FILE* file_save = NULL;
    if (NULL == plr || NULL == filename) {
        return -1;
    }
    file_save = fopen(filename, "w+");
    if (NULL == file_save) {
        fprintf(stderr, "Couldnt open filesave for saving.");
        return -1;
    }
    rpg_PlayerPrintf(plr, file_save);
    fclose(file_save);
    return 1;
}

int rpg_PlayerRestore(Player* plr, const char* filename) {
    FILE* file_save = NULL;
    if (NULL == plr || NULL == filename) {
        return -1;
    }
    file_save = fopen(filename, "r");
    if (NULL == file_save) {
        fprintf(stderr, "Couldnt open filesave for restoring.");
        return -2;
    }
    rpg_PlayerReadf(plr, file_save);
    fclose(file_save);
    return 1;
}

Race rpg_PlayerChooseRace(void) {
    unsigned int new_race = race_unknown;
    long i = 1;
    
    while (1 != rpg_RaceValid((Race) new_race)) {
        fprintf(stdout, "What race do you choose:\n");
        for (i = 1; i < race_last; i++) {
            fprintf(stdout, "%s ", rpg_RaceToString((Race) i ));
        }
        fprintf(stdout, "? (%d-%d)\n", race_unknown + 1, race_last - 1);
        
        hpl_ReadUnsignedInt(&new_race, 10, stdin);
    }
    
    fprintf(stdout, "You chose: %d/%s.\n", new_race, rpg_RaceToString(new_race));
    return (Race) new_race;
}
Gender rpg_PlayerChooseGender(void) {
    unsigned int new_gender = gender_unknown;
    int i = 1;
    
    while (1 != rpg_GenderValid((Gender) new_gender)) {
        fprintf(stdout, "What gender do you choose:\n");
        for (i = 1; i < gender_last; i++) {
            fprintf(stdout, "%s ", rpg_GenderToString((Gender) i ));
        }
        fprintf(stdout, "? (%d-%d)\n", gender_unknown + 1, gender_last - 1);
        
        hpl_ReadUnsignedInt(&new_gender, 10, stdin);
    }
    
    fprintf(stdout, "You chose: %d/%s.\n", new_gender, rpg_GenderToString(new_gender));
    return (Gender) new_gender;
}
Role rpg_PlayerChooseRole(void) {
    unsigned int new_role = race_unknown;
    long i = 1;
    
    while (1 != rpg_RoleValid((Role) new_role)) {
        fprintf(stdout, "What role do you choose:\n");
        for (i = 1; i < role_last; i++) {
            fprintf(stdout, "%s ", rpg_RoleToString((Role) i ));
        }
        fprintf(stdout, "? (%d-%d)\n", role_unknown + 1, role_last - 1);
        
        hpl_ReadUnsignedInt(&new_role, 10, stdin);
    }
    
    fprintf(stdout, "You chose: %d/%s.\n", new_role, rpg_RoleToString(new_role));
    return (Role) new_role;
}


int rpg_PlayerChooseString(String* str, const char* tell) {
    size_t limit_lower = 1, limit_upper = 0;
    if (NULL == str) {
        return -1;
    }
    limit_upper = str->wri;
    do {
        fprintf(stdout, "%s ([%zu-%zu] letters)\n", tell, limit_lower, limit_upper);
        hpl_ReadString(str->str, (int)str->wri, stdin);
        str->cur = strlen(str->str);
        
    } while (str->cur < limit_lower || str->cur > limit_upper);
    
    fprintf(stdout, "You chose : %s.\n", str->str);
    return 1;
}

int rpg_RaceValid(Race race) {
    if (race_unknown < race && race < race_last) return 1;
    return 0;
}
int rpg_GenderValid(Gender gender) {
    if (gender_unknown < gender && gender < gender_last) return 1;
    return 0;
}
int rpg_RoleValid(Role role) {
    if (role_unknown < role && role < role_last) return 1;
    return 0;
}
const char* rpg_RaceToString(Race race) {
    if (1 != rpg_RaceValid(race)) {
        return "Unknown";
    }
    /*the above check is useless, as we ret "" at the end. */
    switch (race) {
        case race_human:
            return "Human";
            break;
        case race_elf:
            return "Elf";
            break;
        case race_dwarf:
            return "Dwarf";
            break;
        case race_gnome:
            return "Gnome";
            break;
        case race_orc:
            return "Orc";
            break;
        default:
            return "Unhandled";
            break;
    }
    return "Unknown";
}
const char* rpg_GenderToString(Gender gender) {
    if (1 != rpg_GenderValid(gender)) {
        return "Unknown";
    }
    /*the above check is useless, as we ret "" at the end. */
    switch (gender) {
        case gender_male:
            return "Male";
            break;
        case gender_female:
            return "Female";
            break;
        case gender_androgynous:
            return "Androgynous";
            break;
        default:
            return "Unhandled";
            break;
    }
    return "Unknown";
}
const char* rpg_RoleToString(Role role) {
    if (1 != rpg_RoleValid(role)) {
        return "Unknown";
    }
    /*the above check is useless, as we ret "" at the end. */
    switch (role) {
        case role_archeologist:
            return "Archeologist";
            break;
        case role_barbarian:
            return "Barbarian";
            break;
        case role_caveman:
            return "Caveman";
            break;
        case role_healer:
            return "Healer";
            break;
        case role_knight:
            return "Knight";
            break;
        case role_priest:
            return "Priest";
            break;
        case role_monk:
            return "Monk";
            break;
        case role_ranger:
            return "Ranger";
            break;
        case role_rogue:
            return "Rogue";
            break;
        case role_samurai:
            return "Samurai";
            break;
        case role_tourist:
            return "Tourist";
            break;
        case role_valkyrie:
            return "Valkyrie";
            break;
        case role_wizard:
            return "Wizard";
            break;
        default:
            return "Unhandled";
            break;
    }
    return "Unknown";
}
