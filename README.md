# samp-snapshots

[![sampctl](https://img.shields.io/badge/sampctl-samp--snapshots-2f2f2f.svg?style=for-the-badge)](https://github.com/bwhitmire55/samp-snapshots)

<!--
Short description of your library, why it's useful, some examples, pictures or
videos. Link to your forum release thread too.

Remember: You can use "forumfmt" to convert this readme to forum BBCode!

What the sections below should be used for:

`## Installation`: Leave this section un-edited unless you have some specific
additional installation procedure.

`## Testing`: Whether your library is tested with a simple `main()` and `print`,
unit-tested, or demonstrated via prompting the player to connect, you should
include some basic information for users to try out your code in some way.

And finally, maintaining your version number`:

* Follow [Semantic Versioning](https://semver.org/)
* When you release a new version, update `VERSION` and `git tag` it
* Versioning is important for sampctl to use the version control features

Happy Pawning!
-->

Functional snapshots as seen in the single player

## Installation

Simply install to your project:

```bash
sampctl package install bwhitmire55/samp-snapshots
```

Include in your code and begin using the library:

```pawn
#include <snapshots>
```

## Functions

```pawn
/*
PARAMS:
    Float: x    - x coordinate of snapshot
    Float: y    - y coordinate of snapshot
    Float: z    - z coordinate of snapshot

RETURNS:
    1 on success, otherwise 0
*/
stock Snapshot_Create(Float: x, Float: y, Float: z);
```

```pawn
/*
PARAMS:
    id  - The snapshot ID to destroy

RETURNS:
    1 on success, otherwise 0
*/
stock Snapshot_Destroy(id);
```

## Callbacks

```pawn
/*
PARAMS:
    playerid    - The player ID who attempted a snapshot (took a picture with a camera)
*/
public Snapshot_OnPlayerAttempt(playerid);
```

```pawn
/*
PARAMS:
    playerid    - The player ID who hit a snapshot
    snapshotid  - The snapshot hit
*/
public Snapshot_OnPlayerHit(playerid, snapshotid);
```

## Macros

```pawn
// Maximum number of snapshots
#if !defined SNAPSHOT_MAX_SNAPSHOTS
    #define SNAPSHOT_MAX_SNAPSHOTS      (10)
#endif
```

## Testing

<!--
Depending on whether your package is tested via in-game "demo tests" or
y_testing unit-tests, you should indicate to readers what to expect below here.
-->

To test, simply run the package:

```bash
sampctl package run
```
