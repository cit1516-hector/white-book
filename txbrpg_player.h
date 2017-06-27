/*//
//  txbrpg_player.h
//  TXBRPG
//
//  Created by Hector Denis on 29/04/17.
//  Copyright © 2017 Hector Denis. All rights reserved.
//*/

#ifndef txbrpg_player_h
#define txbrpg_player_h

/* http://www.steelypips.org/nethack/343/stat-343.txt */
#include "hpl_alloc.h"
#include "hpl_struct_string.h"
#include "hpl_iohandler.h"
#include "hpl_rand.h"

/* /!\ This creates version incompatibility, by letting think that race_abc (a new race of a hypothetical future version) is not a valid role, since it takes the place of race_last. Same for others.*/
enum Race {
    race_unknown = 0,
    race_human,
    race_elf,
    race_dwarf,
    race_gnome,
    race_orc,
    race_last
};
typedef enum Race Race;

enum Gender {
    gender_unknown = 0,
    gender_male,
    gender_female,
    gender_androgynous,
    gender_last
};
typedef enum Gender Gender;

enum Role {
    role_unknown = 0,
    role_archeologist,
    role_barbarian,
    role_caveman,
    role_healer,
    role_knight,
    role_priest,
    role_monk,
    role_ranger,
    role_rogue,
    role_samurai,
    role_tourist,
    role_valkyrie,
    role_wizard,
    role_last
};
typedef enum Role Role;

typedef struct Player Player;
struct Player {
    String *name_class;
    String *name_player;
    Race race;
    Gender gender;
    Role role;
    
    long hpm;
    long hpa;
    
    long lvl;
    long exp;
    long lck;
    long gld;
    
    long str;
    long dex;
    long con;
    long itl;
    long wis;
    long cha;
    long spd;
};

/*
 Version: 1.0.0
 Changes: Plr status.
 Goal: Generate stats with randomization.
 Params: None.
 Modif: Stats.
 Return: -1 if null params, 1 on success.
 Comment:
 */
int rpg_PlayerGenerateStats(Player* plr);

/*
 Version: 1.0.0
 Changes: None.
 Goal: Wrapper for multiple generations/ choose.
 Params: None.
 Modif: all structure.
 Return: -1 if null params, 1 on success.
 Comment:
 */
int rpg_PlayerCreate(Player* plr);

/*
 Version: 1.0.0
 Changes: None.
 Goal: Allocate player and strings and set it to 0 with memset.
 Params: None.
 Modif: Allocations on heap.
 Return: NULL on fail, plr pointer on success.
 Comment:
 */
Player* rpg_PlayerAlloc(void);

/*
 Version: 1.0.0
 Changes: None.
 Goal: Free player and strings.
 Params: None.
 Modif: Player ptr left with bad value (dangling).
 Return: -1 if null params, 1 for success.
 Comment:
 */
int rpg_PlayerFree(Player* plr);

/*
 Version: 1.0.0
 Changes: None.
 Goal: Write plr info to FILE.
 Params: #1 plr: who to print.
         #2 stream: where to print.
 Modif: file content, stream status.
 Return: -1 if null params, 1 for success.
 Comment: Readable is for user interaction.
 */
int rpg_PlayerPrintf(Player* plr, FILE* stream);
int rpg_PlayerReadf(Player* plr, FILE* stream);
int rpg_PlayerPrintReadable(Player* plr, FILE* stream);

/*
 Version: 1.0.0
 Changes: None.
 Goal: Wrapper for printf and readf to r/w file.
 Params: #1 plr: who to store.
         #2 fname: where to store.
 Modif: file content
 Return: -1 if null params, 1 for success.
 Comment:
 */
int rpg_PlayerSave(Player* plr, const char* filename);
int rpg_PlayerRestore(Player* plr, const char* filename);

/*
 Version: 1.0.0
 Changes: None.
 Goal: Present list of possible options as numbers, user chooses, loops until good value.
 Params: None.
 Modif: None.
 Return: (typeof) variable (see func name). The default is x_unknown
 Comment: Keep in sync.
 */
Race rpg_PlayerChooseRace(void);
Gender rpg_PlayerChooseGender(void);
Role rpg_PlayerChooseRole(void);

/*
 Version: 1.0.0
 Changes: None.
 Goal: User chooses name between 2 sizes.
 Params: #1 str: string to store the name.
         #2 tell: what to tell to the player.
 Modif: str->str.
 Return: -1 if null params, 1 for success.
 Comment:
 */
int rpg_PlayerChooseString(String* str, const char* tell);

/*
 Version: 1.0.0
 Changes: None.
 Goal: Check if number is valid.
 Params: #1: enum number.
 Modif: None.
 Return: 0 on fail, 1 for success.
 Comment:
 */
int rpg_RaceValid(Race race);
int rpg_GenderValid(Gender gender);
int rpg_RoleValid(Role role);

/*
 Version: 1.0.0
 Changes: None.
 Goal: Convert a number to a string litteral.
 Params: #1 r/g/r: enum number to convert.
 Modif: None.
 Return: Corresponding string litt, with a uppercase.
 Comment: Keep in sync between themselves and the enumerations.
 */
const char* rpg_RaceToString(Race race);
const char* rpg_GenderToString(Gender gender);
const char* rpg_RoleToString(Role role);

#endif /* txbrpg_player_h */
