//
// test.pwn
//

#include <a_samp>
#include "snapshots.inc"

new snap1;
new snap2;

main() {}

public OnGameModeInit() {
    snap1 = Snapshot_Create(0.00, 0.00, 5.00);
    snap2 = Snapshot_Create(0.00, 5.00, 5.00);
    return 1;
}

public OnGameModeExit() {
    Snapshot_Destroy(snap1);
    Snapshot_Destroy(snap2);
    return 1;
}

public OnPlayerSpawn(playerid) {
    SetPlayerPos(playerid, 0.00, 0.00, 5.00);
    GivePlayerWeapon(playerid, WEAPON_CAMERA, 100);
    return 1;
}

public OnPlayerConnect(playerid) {
    // test als
    return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    // test als
    return 1;
}

public Snapshot_OnPlayerAttempt(playerid) {
    SendClientMessage(playerid, 0x00FF00FF, "You attempted a snapshot!");
    return 1;
}
public Snapshot_OnPlayerHit(playerid, snapshotid) {
    new buffer[128];
    format(buffer, sizeof(buffer), "Successfully hit snapshot %i", snapshotid);
    SendClientMessage(playerid, 0x00FF00FF, buffer);
    return 1;
}