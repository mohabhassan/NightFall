

# NightFall Crash Reporter Documentation
The NightFall Crash Report is a program that runs alongside the MOHAA/SH/BT server to detect if game crashes or hangs.

If a hang/crash is found, the game process memory is dumped.

It allows developers to debug crashes via inspecting the crash dumps.

## Cvar Settings

#### sv_crashrpt_poll_delay
| Name | sv_crashrpt_poll_delay |
|--|--|
| Allowed values | Number of seconds, 0 or more. Typically, you should set it to 5 seconds.|
| Description | Amount in seconds to regularly check if MOHAA/SH/BT is hung. |
---
#### sv_crashrpt_hang_wait
| Name | sv_crashrpt_hang_wait |
|--|--|
| Allowed values | Number of seconds, 0 or more. Typically, you should set it to 30 seconds.|
| Description | Amount in seconds to comfirm that MOHAA/SH/BT is hung. |
---

## Crash Reporter Behaviour
### Initialization
Upon map load, crash reporter is started.

### Run-time
While the game is running, the crash reporter actively checks the MOHAA/SH/BT process for both hangs and crashes.

For hangs, the crash reporter polls every [sv_crashrpt_poll_delay](crash_reporter.md#sv_crashrpt_poll_delay) seconds to check if the game is hung. Hung behaviour happens when the game becomes "Not responding" (GUI thread is not processing messages).

If the game stays hung for [sv_crashrpt_hang_wait](crash_reporter.md#sv_crashrpt_hang_wait) seconds, the crash reporter deems the game as idefinetly hung and will begin the dumping process.

For crashes, the crash reporter gets automatically called once a crash event occurs (no polling happens).

Once the game is hung/crash, the crash reporter dumps full memory content, exception record, stack trace, and other information to a memory dump file name "dump.dmp".

The dump file, along with qconsole.log, along with crash reporter log file (named "crashlog.log") are stored inside a folder whose name is the date-time stamp of the crash stored inside the folder nightfall/crashes inside main, mainta, or maintt directory.

### Shutdown
At shutdown, crash log (crashlog.txt) is stored inside main/mainta/maintt directory.

---
### Developer Usage
To debug a crash/hang, use the pdbs, source code, and binaries inside the NightFall release package along with the memory dump file inside visual studio.

Check qconsole.log and crashlog.txt for extra, potentially useful, information.
