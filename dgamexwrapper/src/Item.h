#pragma once
#include "Trigger.h"
#include "Sentient.h"
#ifdef MOHAA
class Item : public Trigger
{
    SafePtr<Sentient> owner; /* bitsize 128, bitpos 7968 */
    qboolean respawnable; /* bitsize 32, bitpos 8096 */
    qboolean playrespawn; /* bitsize 32, bitpos 8128 */
    float respawntime; /* bitsize 32, bitpos 8160 */
    str dialog_needed; /* bitsize 32, bitpos 8192 */
    int item_index; /* bitsize 32, bitpos 8224 */
    str item_name; /* bitsize 32, bitpos 8256 */
    int maximum_amount; /* bitsize 32, bitpos 8288 */
    int amount; /* bitsize 32, bitpos 8320 */
    str sPickupSound; /* bitsize 32, bitpos 8352 */
    qboolean no_remove; /* bitsize 32, bitpos 8384 */
};
#endif // MOHAA