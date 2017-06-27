/*//
 //  main.c
 //  TXBRPG
 //
 //  Created by Hector Denis on 29/04/17.
 //  Copyright © 2017 Hector Denis. All rights reserved.
 //*/

#include "hpl_unit_test.h"

#include "txbrpg_player.h"
#include "txbrpg_item.h"
#include "txbrpg_inv.h"
#include "txbrpg_unit_test.h"

typedef struct User User;
struct User{
    Player* p;
    Inventory* v;
};
User* rpg_UserAlloc(Player* p, Inventory* v) {
    User* u = NULL;
    u = hpl_Malloc(sizeof(*u));
    
    if (NULL == u) return NULL;
    u->p = p;
    u->v = v;
    return u;
}
int rpg_UserFree(User* u) {
    if (NULL == u) return -1;
    rpg_InventoryDestroy(&(u->v));
    rpg_PlayerFree(u->p);
    u->p = NULL;
    free(u);
    return 1;
}

int rpg_UserPrint(User* u, FILE* out) {
    if (NULL == u) return -1;
    rpg_PlayerPrintReadable(u->p, out);
    rpg_InventoryPrint(u->v, out);
    return 1;
}

int main(void) {
    User* u = NULL;
    u = rpg_UserAlloc(rpg_PlayerAlloc(),
                  rpg_InventoryAlloc(NULL,
                                     rpg_ItemAlloc("Sword", "Grey Sword", 50, 42, beatitude_uncursed, itemtype_weapon,
                                                 rpg_WeaponCreate(2, +2, 1, material_bronze))));
    
    rpg_UserPrint(u, stdout);
    rpg_UserFree(u);
    return 0;
}

/*Compilation options:
 -Wall -Wextra -std=c99 -pedantic -pedantic-errors -g -O0 -Winit-self -Wuninitialized -Wold-style-cast -Wold-style-definition -Woverloaded-virtual -Wuninitialized -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wshadow -Wconversion -Wunused-result
 */
