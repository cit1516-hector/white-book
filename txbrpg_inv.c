/*//
 //  txbrpg_inv.c
 //  TXBRPG
 //
 //  Created by Hector Denis on 20/06/2017.
 //  Copyright © 2017 Hector Denis. All rights reserved.
 //*/

#include "txbrpg_inv.h"
Inventory* rpg_InventoryAlloc(Inventory* next, Item* i) {
    Inventory* v = NULL;
    v = hpl_Malloc(sizeof(*v));
    v->next = next;
    v->item = i;
    return v;
}
int rpg_InventoryPrint(Inventory* head, FILE* stream) {
    Inventory* current = head;
    if (NULL == head) return -1;
    while (NULL != current) {
        rpg_ItemPrint(current->item, stream);
        current = current->next;
    }
    return 1;
}


int rpg_InventoryAdd(Inventory** head, Item* item) {
    Inventory* current = NULL;
    
    /* Bad pointer. */
    if (NULL == head || NULL == item) return -1;
    
    /* Linked list is empty / not initialised. */
    if (NULL == *head) {
        (*head) = hpl_Malloc(sizeof(**head));
        if (NULL == *head) return -2;
        (*head)->item = item;
        (*head)->next = NULL;
        return 1;
    }
    
    /* Contains some elements */
    current = *head;
    while (NULL != current->next) {
        current = current->next;
    }
    current->next = hpl_Malloc(sizeof(*(current->next)));
    if (NULL == current->next) return -3;
    current->next->item = item;
    current->next->next = NULL;
    return 1;
}

Item rpg_InventoryRemoveLast(Inventory** head) {
    Inventory* current = NULL;
    Item retitem;
    memset(&retitem, 0, sizeof(retitem));
    
    /* Bad pointer. */
    if (NULL == head) return retitem;
    
    /* Empty. */
    if (NULL == *head) return retitem;
    
    /* One item only. */
    if (NULL == (*head)->next) {
        if (NULL == (*head)->item) return retitem;
        retitem = *(*head)->item;
        rpg_ItemFree((*head)->item);
        (*head)->item = NULL;
        free((*head));
        *head = NULL;
        return retitem;
    }
    
    /* Set current to the penultimate item. */
    current = *head;
    while (NULL != current->next->next) {
        current = current->next;
    }
    
    /* Current->next points to the last item, so we can remove it. */
    if (NULL == current->next->item) return retitem;
    retitem = *(current->next->item);
    rpg_ItemFree((current->next->item));
    (current->next->item) = NULL;
    free(current->next);
    current->next = NULL;
    return retitem;
}

int rpg_InventoryPush(Inventory** head, Item* item) {
    Inventory* new = NULL;
    
    /* Bad pointer. */
    if (NULL == head || NULL == item) return -1;
    new = hpl_Malloc(sizeof(*new));
    if (NULL == new) return -2;
    new->item = item;
    new->next = *head;
    *head = new;
    
    return 1;
}

Item rpg_InventoryPop(Inventory** head) {
    Inventory* next = NULL;
    Item retitem;
    memset(&retitem, 0, sizeof(retitem));
    
    /* Bad pointer, points to naught. */
    if (NULL == head) return retitem;
    
    /* Inventory is empty OR item is NULL. */
    if (NULL == *head || NULL == (*head)->item) return retitem;
    retitem = *(*head)->item;
    rpg_ItemFree((*head)->item);
    next = (*head)->next;
    free(*head);
    *head = next;
    return retitem;
}

int rpg_InventoryDestroy(Inventory** head) {
    if (NULL == head) return -1;
    while (NULL != *head) {
        rpg_InventoryRemoveLast(head);
    }
    return 1;
}

int rpg_InventoryRemoveByItem(Inventory** head, const Item copy) {
    Inventory* current = NULL;
    Inventory* bridge = NULL;
    
    /* 1:Dad pointer; 2:Empty list; */
    if (NULL == head) return 0;
    if (NULL == *head) return 0;
    
    /* Test first item. */
    if (NULL == (*head)->item) return 0;
    if (1 == rpg_ItemCmp(copy, *(*head)->item)) {
        rpg_ItemFree((*head)->item);
        (*head)->item = NULL;
        
        bridge = (*head)->next;
        free(*head);
        *head = NULL;
        *head = bridge;
        return 1;
    }
    
    current = *head;
    while (NULL != current) {
        if (NULL == current->next) return 0;
        if (NULL == current->next->item) continue;
        
        if (1 == rpg_ItemCmp(copy, *(current->next->item))) {
            rpg_ItemFree((current->next->item));
            (current->next->item) = NULL;
            
            bridge = current->next->next;
            free(current->next);
            current->next = NULL;
            current->next = bridge;
            return 1;
        }
        current = current->next;
    }
    
    
    return 0;
}

















