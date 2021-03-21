//
// snapshots.inc
//

/**
    TO-DO:
        Add rotation to the snapshot icons
 */

#if defined SNAPSHOT_INC
    #endinput
#endif
#define SNAPSHOT_INC

#if !defined SNAPSHOT_MAX_SNAPSHOTS
    #define SNAPSHOT_MAX_SNAPSHOTS      (10)
#endif

#define SNAPSHOT_INVALID    (-1)
#define SNAPSHOT_OBJECTID   (1253)

static gSnapshot_Object[SNAPSHOT_MAX_SNAPSHOTS];

stock Snapshot_Create(Float: x, Float: y, Float: z) {
    new idx = GetEmptySlot();
    if(idx == SNAPSHOT_INVALID)
        return 0;

    gSnapshot_Object[idx] = CreateObject(SNAPSHOT_OBJECTID, x, y, z, 0.0, 0.0, 0.0, 0.0);
    return idx;
}

stock Snapshot_Destroy(id) {
    if((0 < id < SNAPSHOT_MAX_SNAPSHOTS) && gSnapshot_Object[id] != 0) {
        DestroyObject(gSnapshot_Object[id]);
        return 1;
    }
    return 0;
}

static GetEmptySlot() {
    for(new i = 0; i < SNAPSHOT_MAX_SNAPSHOTS; i++) {
        if(!gSnapshot_Object[i]) {
            return i;
        }
    }
    return SNAPSHOT_INVALID;
}

public OnPlayerConnect(playerid) {
    EnablePlayerCameraTarget(playerid, true);
    return CallLocalFunction("snap_OnPlayerConnect", "i", playerid);
}

#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else 
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect snap_OnPlayerConnect
forward snap_OnPlayerConnect(playerid);

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if(newkeys & KEY_FIRE) {
        if(GetPlayerCameraMode(playerid) == 46) {
            CallLocalFunction("Snapshot_OnPlayerAttempt", "i", playerid);
            new object = GetPlayerCameraTargetObject(playerid);
            if(object != INVALID_OBJECT_ID) {
                for(new i = 0; i < SNAPSHOT_MAX_SNAPSHOTS; i++) {
                    if(gSnapshot_Object[i] == object) {
                        CallLocalFunction("Snapshot_OnPlayerHit", "ii", playerid, i);
                        break;
                    }
                }
            }
        }
    }
    return CallLocalFunction("snap_OnPlayerKeyStateChange", "iii", playerid, newkeys, oldkeys);
}

#if defined _ALS_OnPlayerKeyStateChange
    #undef OnPlayerKeyStateChange
#else 
    #define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange snap_OnPlayerKeyStateChange
forward snap_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);

forward Snapshot_OnPlayerAttempt(playerid);
forward Snapshot_OnPlayerHit(playerid, snapshotid);