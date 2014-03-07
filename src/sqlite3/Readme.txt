
You need SQLite and you will have to recompile mod_sa with __CHEAT_VEHRECORDING_H__ defined
to use the vehicle recording system.


Download latest SQLite Amalgamation from:
http://www.sqlite.org/download.html

Place headers, source, and library files in this folder.


It says it is missing a lib file.
 - If you are using the precompiled dll you will have to manually create the lib file for SQLite
   by running 'vcvars32.bat' and 'lib.exe /DEF:sqlite3.def' (located in your VisualC/bin folder).
 - The lib file needs to be in this folder.
It says it is missing a dll.
 - You need to have the sqlite3.dll in the same folder as gta or mod_sa.

---------------------------------------------------------------------------
---------------------------------------------------------------------------
		Ini file settings for vehicle recording system:
---------------------------------------------------------------------------
---------------------------------------------------------------------------

# ========================
# Vehicle Recording System
# ========================
#
# this is NOT part of mod_sa by default
# you need to recompile it with __CHEAT_VEHRECORDING_H__ defined
#
# Note: Need to set recording_activated to true before being able to use the keys.
#  (Can also activate via menu 'Misc' > 'Routes' > 'Enable Routes Functionality'
#  Playing a record is time related so make sure you deactivate the record playing
#  before pausing/minimizing the game, if you don't want to look like you teleported.
#
recording_activated = false
key_recording_record = r

# Set recording_maxDistToEntryPoint to 0.0, to deactivate it.
# When activated it will check, if you are within the maxDist to the starting position
# if you arn't it will automatically search for the closest point to your position
# and start playing from that point on (you need to be in maxDist range to route).
recording_maxDistToEntryPoint = 0.0

# If continuous-mode is activated it will repeat the recording over and over again
# (make sure maxDist is either deactivated, or the last point is within the maxDist
#  to the first point)
key_recording_continueAfterFinish = k

# To use the customSpeed multiplier use the customSpeed keys to start playing the record.
recording_play_customSpeed = 2.0
key_recording_play = p
key_recording_customSpeed = b

# Play the record in reverse order.
key_recording_rev = o
key_recording_rev_customSpeed = &0
