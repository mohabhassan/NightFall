#pragma once
#include "Animate.h"

#ifndef MOHAA
class ScriptThreadLabel
{
    void* m_Script;//FIXME: GameScript*
    const_str m_Label;
};

class Trigger :	public Animate
{
protected:
    float wait; /* bitsize 32, bitpos 7200 */
    float delay; /* bitsize 32, bitpos 7232 */
    float trigger_time; /* bitsize 32, bitpos 7264 */
    qboolean triggerActivated; /* bitsize 32, bitpos 7296 */
    int count; /* bitsize 32, bitpos 7328 */
    const_str noise; /* bitsize 32, bitpos 7360 */
    const_str message; /* bitsize 32, bitpos 7392 */
    ScriptThreadLabel /* id 260 */ m_Thread; /* bitsize 64, bitpos 7424 */
    SafePtr<Entity> activator; /* bitsize 128, bitpos 7488 */
    int respondto; /* bitsize 32, bitpos 7616 */
    qboolean useTriggerDir; /* bitsize 32, bitpos 7648 */
    float triggerCone; /* bitsize 32, bitpos 7680 */
    Vector triggerDir; /* bitsize 96, bitpos 7712 */
    float triggerDirYaw; /* bitsize 32, bitpos 7808 */
    qboolean triggerable; /* bitsize 32, bitpos 7840 */
    qboolean removable; /* bitsize 32, bitpos 7872 */
    qboolean edgeTriggered; /* bitsize 32, bitpos 7904 */
    int multiFaceted; /* bitsize 32, bitpos 7936 */
};
#endif // MOHAA

