/*//
//  txbrpg_unit_test.c
//  TXBRPG
//
//  Created by Hector Denis on 14/06/2017.
//  Copyright © 2017 Hector Denis. All rights reserved.
//*/

#include "txbrpg_unit_test.h"

static char* rpg_UnitTestPlayer(void) {
    Player* p = NULL;
    mu_assert("p alloc", NULL != (p = rpg_PlayerAlloc()));
    mu_assert("p creation", 1 == rpg_PlayerCreate(p));
    mu_assert("p printFF", 1 == rpg_PlayerPrintf(p, stdout));
    mu_assert("p print readable", 1 == rpg_PlayerPrintReadable(p, stdout));
    mu_assert("p save", 1 == rpg_PlayerSave(p, "save.txt"));
    mu_assert("p free", 1 == rpg_PlayerFree(p));
    mu_assert("p free", NULL != (p = rpg_PlayerAlloc()));
    mu_assert("p free", 1 == rpg_PlayerRestore(p, "save.txt"));
    mu_assert("p print readable", 1 == rpg_PlayerPrintReadable(p, stdout));
    mu_assert("p free", 1 == rpg_PlayerFree(p));
    return NULL;
}

static char* rpg_UnitTestAll(void) {
    /*Keep order in sync with actual code.*/
    /*mu_run_test(rpg_UnitTestPlayer);*/
    return NULL;
}

int rpg_UnitTestMain(void) {
    char *error = NULL;
    
    error = rpg_UnitTestAll();
    if (NULL != error) {
        fprintf(stdout, "ERROR: %s.\n", error);
    }
    else {
        fprintf(stdout, "ALL TESTS PASSED SUCCESSFULLY.\n");
    }
    fprintf(stdout, "Tests run: %d\n", mu_tests_run);
    
    return NULL != error;
    /*error == NULL ? 0 : 1*/
}
