/*//
//  txbrpg_inv.h
//  TXBRPG
//
//  Created by Hector Denis on 20/06/2017.
//  Copyright © 2017 Hector Denis. All rights reserved.
//*/

#ifndef txbrpg_inv_h
#define txbrpg_inv_h

#include "txbrpg_item.h"
typedef struct Inventory Inventory;
struct Inventory {
    Item* item;
    Inventory* next;
};

Inventory* rpg_InventoryAlloc(Inventory* next, Item* i);
/*
 Version: 1.0.0
 Changes: None.
 Goal: Print whole inventory by iterating over elements.
 Params: Head, stream.
 Modif: Stream status.
 Return: -1 if null params, 1 on success.
 Comment:
 */
int rpg_InventoryPrint(Inventory* head, FILE* stream);

int rpg_InventoryAdd(Inventory** head, Item* item);
Item rpg_InventoryRemoveLast(Inventory** head);

int rpg_InventoryPush(Inventory** head, Item* item);
Item rpg_InventoryPop(Inventory** head);

int rpg_InventoryDestroy(Inventory** head);
int rpg_InventoryRemoveByItem(Inventory** head, const Item copy);

#endif /* txbrpg_inv_h */
