# NightFall Automated Test Suite

## Intro.

This is a suite of several tests to cover the functionality for most of NightFall features.
## Pre-requisites
 - `python 3.9+ environment`
 - `pip install pytest pytest-retry pytest-timeout requests`

## Running
### SpearHead 2.15:
`pytest ./tests --game sh --gamever 2.15 --gamepath 'D:/MOHAA_STUFF/nightfall/game/servers/SH215' --mode server --port 12204 -rA -s -x --retries 2 --timeout=120 > logsh215.txt 2>&1`
### BreakThrough 2.30:
`pytest ./tests --game bt --gamever 2.30 --gamepath 'D:/MOHAA_STUFF/nightfall/game/servers/BT230' --mode server --port 12203 -rA -s -x --retries 2 --timeout=120 > logbt230.txt 2>&1`
### BreakThrough 2.40:
`pytest ./tests --game bt --gamever 2.40 --gamepath 'D:/MOHAA_STUFF/nightfall/game/servers/BT240' --mode server --port 12203 -rA -s -x --retries 2 --timeout=120 > logbt240.txt 2>&1`
