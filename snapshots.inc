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

enum eSnapshot_data {
    bool: eSnapshot_Created,
    Float: eSnapshot_X,
    Float: eSnapshot_Y,
    Float: eSnapshot_Z,
    eSnapshot_Object
};

static gSnapshot_Data[SNAPSHOT_MAX_SNAPSHOTS][eSnapshot_data];

stock Snapshot_Create(Float: x, Float: y, Float: z) {
    new idx = GetEmptySlot();
    if(idx == SNAPSHOT_INVALID)
        return 0;

    gSnapshot_Data[idx][eSnapshot_Created] = true;
    gSnapshot_Data[idx][eSnapshot_X] = x;
    gSnapshot_Data[idx][eSnapshot_Y] = y;
    gSnapshot_Data[idx][eSnapshot_Z] = z;
    gSnapshot_Data[idx][eSnapshot_Object] = CreateObject(SNAPSHOT_OBJECTID, x, y, z, 0.0, 0.0, 0.0, 0.0);
    return 1;
}

stock Snapshot_Destroy(id) {
    if((0 < id < SNAPSHOT_MAX_SNAPSHOTS) && gSnapshot_Data[id][eSnapshot_Created]) {
        gSnapshot_Data[id][eSnapshot_Created] = false;

        if(gSnapshot_Data[id][eSnapshot_Object]) {
            DestroyObject(gSnapshot_Data[id][eSnapshot_Object]);
            gSnapshot_Data[id][eSnapshot_Object] = 0;
        }
        return 1;
    }
    return 0;
}

static GetEmptySlot() {
    for(new i = 0; i < SNAPSHOT_MAX_SNAPSHOTS; i++) {
        if(!gSnapshot_Data[i][eSnapshot_Created]) {
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
                    if(gSnapshot_Data[i][eSnapshot_Object] == object) {
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