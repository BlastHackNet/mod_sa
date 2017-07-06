# Changelog

## Version 4.4.1.3
* Fixed player invulnerability activation via menu
* Fixed debug mode feature crash
* Window mode compatibility with other mods

## Version 4.4.1.2
* Fixed SA-MP anticheat patch

## Version 4.4.1.1
* Fixed SA-MP incoming packet hook

## Version 4.4.1.0
* Common optimization
* Prevented 5 detection ways:
 - Added custom ClientCheck handler to prevent invulnerability detection
 - Disabled loading all weapon models on game start
 - Disabled Free paint and spray patch by default
 - Disabled Anti Derail patch by default
 - Removed built-in samp-patch "no car color resetting"
* Added cheat-panic check in network patch handlers
* Renamed FastWarp to QuickWarp
* Improved weapon hack stability
* Extra SA-MP invulnerability is now disabled by default
* Request spawn function was replaced with more correct method (fixes possible detection)
* Fixed camera glitching on scoreboard activation when cursor is active
* Fixed SA-MP structures: stRemotePlayerData, stSAMPVehicle, stObject
* Fixed 3D-map sigle player crash
* Fixed player tags position calculation

## Version 4.4.0.3
* Added VS2013 and VS2015 compatibility

## Version 4.4.0.2
* Fixed PrintShadow function
* Updated SA-MP structures: stBulletData, stRemotePlayerData, stChatInfo

## Version 4.4.0.1
* Improved aimbot
* Fixed stServerPresets and stRemotePlayerData structs

## Version 4.4.0.0
* Fully updated to 0.3.7
* New function FastWarp
* New function FreezeRot
* New function Surf
* New keyboard shortcuts
* New Aimbot
* Menu which you can control by a cursor
* Menu of the RakNet patches
* Improved some render functions: map, nametags, vehicletags
* A lot of fixes
* Map teleport settings

## Version 4.3.3.3
* Updated on 0.3z R1
* mod's chat now more colorful
* Fixed crash when exiting the game

## Version 4.3.3.2
* Fixed issues with the FPS (caused by the Window Mode).
* Fixed issues with the Camera looking upwards if you're freezed.
* Removed "Disable Loading Screen Patch" (it's actually useless.)
* Added Anticrash & Godmode Patch

## Version 4.3.3.1
* Fixed SA-MP Patch "NOP SetEngineState", thanks to povargek for this.
* Fixed issue with connecting to servers from mod_sa's favorite server list.
* Added more anticheat-patches.

## Version 4.3.3.0
* Fixed SA-MP Patch "Disable unoccupied data", and added new:
NOP SetPlayerSkin, NOP SetPlayerSkillLevel, NOP StopAudioStream, NOP EditObject
* Added RakClient hook and receiving RPC hook
* New feature - "Extra invincibility", if Invincibility is set on, server can't drop your HP. You can enable/disable it in "SA:MP Misc. -> Extra godmode" or in mod_sa.ini
* Fixed problem with sticking keys after losing focus

## Version 4.3.2.2
* Updated all SA-MP Patches and added new:
SetPlayerTime, TogglePlayerSpectating, PlayerSpectatePlayer, PlayerSpectateVehicle, SetPlayerFightingStyle

## Version 4.3.2.1
* Updated some SA-MP Patches
* Fixed some bugs and problems
* s0beit's directory moved to <GTA Folder>\mod_sa
* Windows XP support
* Windowed mode disabled by default

## Version 4.3.2.0
* Full support for SA-MP 0.3x (updated by FYP)
* Improved fakekill function
* Added 2 special actions:
Special action cuffed, Special action carry

## Version 4.3.1.4
* Full support for SA-MP 0.3e (updated by FYP)
* Added samp-patches (by FYP):
NOP SetVehicleZAngle, NOP SetVehicleInterior, NOP PlayAudioStream, NOP RemoveBuilding,
NOP InterpolateCamera, NOP InitGame, NOP SetMapIcon, NOP DisableMapIcon, NOP SetPlayerName,
NOP RespawnVehicle, NOP SendDeath, NOP SpawnPlayer, Debug mode, Disable spec data,
Disable help dialog, Disable vehicle info (/dl) distance limit, Disable weapon data,
Disable remote driver data, Disable vehicle surfing

## Version 4.3.1.2
* Really smooth player flying in samp.

## Version 4.3.1.1
* Support for SA-MP 0.3d

## Version 4.3.1.0
* Final version for SA-MP 0.3c R3
* jflm did some stuff. (you gotta add stuff here bro -nf)

## Version 4.3.0.1
* Many bugs fixed.
* Slightly unsmooth but awesome enough to use new beta camera for Player Fly

## Version 4.3.0.0
* Added new menu AntTweakBar (http://www.antisphere.com/Wiki/tools:anttweakbar).

## Version 4.2.4.1
* Added Player Fly fast turning animations.
* Support for SA-MP 0.3c R3

## Version 4.2.4.0
* Added RakNet voice support for SA-MP.

## Version 4.2.3.2
* Added Player Fly deceleration animation.

## Version 4.2.3.1
* Added mute-player function to anti-spam.
* Added Player Fly acceleration/deceleration multipliers to INI.
* Disabled loading screen, thanks to MTA.
* Fixed Player Fly animation bugs.

## Version 4.2.3.0
* Added speed setting for Player Fly to the INI and Cheats menu.
* Added default keys for Stick - NumPad 4 7 8 9
* Added default key for disable wall collisions - NumPad 6

## Version 4.2.2.1
* Added ClickWarp.  Default: Middle Mouse & Left Mouse
* Improved Fly Player.
* Fixed Fast Exit.

## Version 4.2.2.0
* Added text label rendering.
* Added left/right/up strafing to Fly Player.
* Improved Fly Player.
* Improved vehicle HP cheat.
* Improved actor HP cheat (parachute death fixed).

## Version 4.2.1.2
* Fixed single player crash.
* Fixed keys setting/sticking during menu & alt-tab.
* Removed custom screenshots.

## Version 4.2.1.1
* Improved Fly Player.

## Version 4.2.1.0
* Added Fly Player, Default: .
* Removed Sacky's scripting hook.

## Version 4.2.0.0
* Support for SA-MP 0.3c.
* Project renamed to mod_sa.

## Version 4.1.0.0
* Support for SA-MP 0.3a.
* This is the only official version of m0d_s0beit_sa for SA-MP 0.3a.
* Fixed so many things that it's retarded to list them here.
* Added menu to add upgrades (Wangs/etc) to your vehicle anywhere.
* Added SpiderWheels, drive on anything! Default: Numpad 5
* Added new Method to fly vehicles (allows 'helicoptering') Default: .
* Added toggleable infinite NOS. Default: Numpad 0
* Added switchable car lights. Default: F2 to switch modes.
* Added toggleable vehicle collisions except for your vehicle.
* Added ability to walk/drive through walls.
* Added left & right 90 degree buttons to Quick Turn. Default: [ and ]
* Added function in menu (GTA->Cheats) to avoid loosing Trailer.
* Added option in menu (GTA->Misc) to toggle windowed mode.
* Added Nitro/Brake & 180 degree quick turn ability to trains.

## Version 4.0.5.0
* Final version for SA:MP v0.2.XU1_2 & U:MP vT3
* Added our new "AirRide ESP" to m0d's player ESP which prevents ESP collisions
  so you can always see everyone's name easily.  No more jumble-fudge of names.
* Added "esp_players_airride" to the INI, to turn that on or off.
* Added "screenshot_clean" to the INI, takes screenshots without m0d's GUI/ESP.

## Version 4.0.4.1
* Fixed failures on custom screenshot.

## Version 4.0.4.0
* Added "Teleports -> Teleport to interior" and removed "SA:MP Misc -> Change interior".
* Lag-free screenshots (screenshot_enable, key_screenshot, jpg_quality, jpg_chrominancetable, jpg_luminancetable).
* Changed the font size and ESP stuff.
* Added option to enable/disable clouds.

## Version 4.0.3.2
* Added mouse_4 and mouse_5 keybinds.

## Version 4.0.3.1
* Fixed spectator mode bug.

## Version 4.0.3.0
* Removed the hook version.
* Fixes to the windowed mode.
* Support for GTA:U-MP.
* Added option "Weapons -> Randomize the ammo values".

## Version 4.0.2.0
* Added ingame vehicle handling (Cheats -> Change vehicle handling).
* Added key_respawn.
* Added SA:MP Misc -> Change interior.
* Randomize ammo values for each weapon.

## Version 4.0.1.0
* Readded custom sendrates and init screen.
* Added car jacking prevention (should put you back to the vehicle you were in) (anti_carjacking).
* Added toggleable GUI from the menu (Misc -> Toggle HUD indicators).
* Added text in dynamic teleport locations if they are set.
* Added Set(Vehicle|Player)Health hook to make invulnerability harder to detect.
* Added delay before rejoining or joining a server (rejoin_delay).
* Added server password field to the favorite server list.
* Added SA:MP Misc. -> Teleport to object & pickup.
* Added text in objects and pickups (shows server ID and model ID).
* Added Patches:
  Cars hover over water, NOP ShowGameText, NOP ShowTextDraw, NOP SetPlayerCameraPos,
  NOP SetPlayerCameraLookAt, NOP SetCameraBehindPlayer, NOP SetPlayerFacingAngle
  NOP GivePlayerWeapon, NOP TogglePlayerSpectating, Don't notify vehicle enter/exits,
  NOP SetVehicleParamsForPlayer.
* Fixed a malformed position exploit.
* Fixed default SA:MP player tags and it now uses default settings.
* Fixed engine toggleing, it now works with Inv enabled.

## Version 4.0.0.3
* INI: spec_data, read the note above.
* INI: use_gta_autoaim.

## Version 4.0.0.2
* Fix for menu and loading screen flickering on some video cards (flickering_problem).
* Readded the custom autoaim.
* Improved ESP layout.

## Version 4.0.0.1
* Added default ESP states for INI (esp_vehicles_defaulton, esp_players_defaulton).
* Fixes to Jumper vehicle teleporting.

## Version 4.0.0.0
* Added a hook version with injector.
* Fixes to the spectator mode.
* Custom player and vehicle tags (key_render_player_tags, key_render_vehicle_tags).
* Chat keybinder (chat[]).
* Text shadows (render_text_shadows).
* Keep the nickname when connecting with the favorite list (use_current_name).
* GUI settings format (gui[]).
* m0d_s0beit_sa_all.log contains logs of all sessions and m0d_s0beit_sa.log contains logs of the last session.

## Version 3.9.1.3
* Added "Jumper" unified to-vehicle teleporting.
* Added nearest vehicle jumping (key_vehicle_jumper / key_vehicle_occupied_jumper).
* Fixed Breakdance as airplane passenger crash.
* Fixed possible crash in "Warp instantly to vehicle" menu.
* Removed the samp hooks.

## Version 3.9.1.2
* fixed Breakdance directions, again
* updated "SA:MP v0.2.X.U1_1 Original" link location

## Version 3.9.1.1
* Fixed sneaker list bug.
* logo_intro_enable and logo_enable.
* Onfoot HP regeneration (hp_regen_onfoot).

## Version 3.9.1.0
* Support for SA:MP 0.2.X.1

## Version 3.9.0.2
* fixed Breakdance directions

## Version 3.9.0.1
* Readded the old speedometer (speedometer_old_enable).
* hud_bar_color.

## Version 3.9.0.0
### Added
* Few custom GUI settings (hud_draw_bar, ...).
* basic_mode setting, used to initialize with no SA-MP cheats.
* In-game "favorite" server list, used to connect to servers from the in-game menu.
* instagib and friendly_fire settings.
* HUD indicator settings (hud_indicator_inv, ...).
* Custom syncing settings (key_onfoot_data, ...). spec_data is enabled by default,
  the client will not send spectate data to the server.
* Added distance value to the player info list.
* ammo_random setting.
* i_have_edited_the_ini_file has been added back.
* Graphic speedometer (speedometer_enable, ...).
* SA:MP Misc. -> Log gamemode infos.
* secondary_key, merged with SA-MP cheat keys.
* Patches:
  "NOP CreateExplosion"
  "NOP RemoveCarComponent"
* brkdance_velocity setting.
* freeze_hp_values setting.
* RPC scripting function hooking.

### Changed
* Output error messages to the chatbox if the cheat is SA-MP related.
* GTA/SA-MP changes in the menu. Patches have been splitted (sampPatch[]).
* Turn the HUD bar to red when there are players spectating.
* Removed "Reconnect" from the menu and auto-rejoin patch. Added key_rejoin.
* Server RPC scripting function patches can be toggled.
* Updated the logo and added "Misc -> Toggle logo".
* nametags_dist has been renamed to line_of_sight_dist.
* Removed blur_remove and intro_remove.

### Fixed
* Crash when sticking then teleporting directly to a vehicle.
* Automatically go back to the original position when turning off spectator mode.
* Invulnerability and HP regen issues.

## Version 3.82
* Removed custom netcode rate functions.
* Optimized for speed, now with SSE2.

## Version 3.81
* Fix body panels on repair key.
* Changes to the HUD.
* Removed the old keyhook code.

## Version 3.8
* Full support for SA:MP 0.2.X
* Patches:
  "SA-MP 0.2.X: Remote client crash"
  "SA-MP 0.2.X: Remote client crash...fix"
* Added new file patch: surface mod by Kosty@n, disabled by default.

## Version 3.72
* Custom chat "scrolling".
* Updated the TroyRulz007 logo and added the MTAVCSUX.net logo (both made by Nuckfuts).
* Minor changes.

## Version 3.71
* Handle vehicle spectating.
* Added more debug info in the exception filter.
* Settings: nametags_show, nametags_dist, nametags_see_through_walls, markers_show.
* Custom sendrates: onfoot_idle_sendrate, onfoot_normal_sendrate, incar_idle_sendrate,
  incar_normal_sendrate, headsync_sendrate.
* Added a player list that shows only whose are spectating (Miscellaneous -> Sneakers list).
* Inverted the custom chat order.
* Car repair kit (key_repair_car, disabled by default)
* Patch: "SA-MP 0.2.2R3: Prevent Carjacking"

## Version 3.7
* Players menu reorganized:
  "Players -> Warp to player"
  "Players -> Warp instantly to player's vehicle" (new)
  "Players -> Spectate player" (new)
  "Players -> Remove player" (fixed)
  "Players -> Restore player" (new)
* Menu: "Vehicles -> Warp instantly to vehicle"
* Miscellaneous: "Change virtual world", "Dance", "Use CJ running style".
* Breakdance mod ("p" key to toggle it, key_brkd_toggle).
* Fast exit from a vehicle ("n" key by default, key_fast_exit).
* GTA Auto-aim with mouse control patch made by Nuckfuts. (Added as internal, "z" key to toggle).
* Added vehicles to the mini-map, hold the "x" key to show them (key_map_show_vehicles).
* Custom init screen from coords in the .ini file (samp_init_screen_cam_pos, samp_init_screen_cam_look_at).
* Custom GUI has been removed. It caused some crashes.
* Fixed possible crash in the mini-map.

## Version 3.6
* Player list warp from the menu.
* Cheats -> Fake kill.
* Custom rendering: chatbox, and killwindow.
* Fixed player names in the mini-map.
* Misc:
  "-> Change game state"
  "-> Reconnect", press the unfreeze key after reconnecting to recover the camera.
  (Also go to Area 69 where the jetpack is in Single Player and shit brix).
  "-> Remove player"
  "-> Player info list"
* Vehicle engine toggleling ("end" key)
* Patches:
  "SA:MP 0.2.2R3: Debug mode"
  "SA:MP 0.2.2R3: No head movement delay"
  "SA-MP 0.2.2R3: NOP Local player handling"
  "SA-MP 0.2.2R3: NOP Remote player processing"
  "SA-MP 0.2.2R3: NOP IsFriendlyFire and Instagib"
  "SA-MP 0.2.2R3: NOP ProcessCollision hook"
  "SA-MP 0.2.2R3: NOP ResetPlayerWeapons"
  "SA-MP 0.2.2R3: NOP GetOptimumInCarSendRate"
  "SA-MP 0.2.2R3: NOP GetOptimumOnFootSendRate"
  "SA-MP 0.2.2R3: NOP SendStatsUpdate"
  "SA-MP 0.2.2R3: NOP CheckWeapons"
  "SA-MP 0.2.2R3: NOP On foot worldbounds"
  "SA-MP 0.2.2R3: NOP In car worldbounds"
* Added custom data files (Transfender Overhaul V2 by Offroader23).

## Version 3.57d
* Category "Show only occupied vehicles" in Cheats -> Vehicles.
* Readded the debug window in Miscellaneous.
* Readded the map.
* TroyRulz007 logo by Pilot.
* Patches:
  "GTA: Free paint and spray"
  "GTA: Infinite run"
  "GTA: Autoaim"
  "SA-MP: Save snapshots as JPG"

## Version 3.57c
* Right click teleport from gtasa's map menu; patch "No map warp processing".
* Patches:
  "SA-MP: Custom carmods.dat (data/carmods.two)"
  "SA-MP: Custom weapon.dat (data/weapon.two)"
  "SA-MP: Custom ar_stats.dat (data/ar_stats.two)"
  "SA-MP: Custom gta.dat (data/gta.two)"
  "SA-MP: Custom melee.dat (data/melee.two)"
  "SA-MP: Custom object.dat (data/object.two)"
  "SA-MP: Custom ped.dat (data/ped.two)"
  "SA-MP: Custom default.dat (data/default.two)"
* Readded some options that used to be in Miscellaneous.
* Readded a stable SCM hook and "key_anti_freeze".

## Version 3.57b
* Spoof weapon readded.
* Custom ammo, ammo in clip, and money value settings (ammo, ammo_clip, money_value).
* Hardware or software vertex rendering ini setting.
* Patches:
  "SA-MP: No connecting delay"
  "SA-MP: Prevent lagged car jacking"
  "SA-MP: Custom vehicle.txd (models/generic/vehicle.two)"
  "SA-MP: Custom shopping.dat (data/shopping.two)"
  "SA-MP: NOP TogglePlayerControllable"
* Allow car spawning if the vehicle is occupied.

## Version 3.57a
* Some more patches:
  "Auto-rejoin on kick"
  "Custom data files (handling, timecyc)" by nuckfuts.
  "Enable vehicle name rendering"
  "Disable anti-pause"
  "Enable speed blur"

## Version 3.57
* The sa-mp DLL can now be edited/accessed from s0beit's patcher.
* Some sa-mp patches added.

## Version 3.56
* Speedometer (not)
* Auto-aim readded
* Patch "Scale down the HUD"
* Added a cracked samp DLL (NorpcsArjoin). This cracked client will giveafuck about almost every
  server scripting functions (no RPC server-side scripting registry), and auto-rejoin on kick.
* SCM hook and key_antifreeze removed. Use the cracked samp.

## Version 3.55b
* Patch "Toggle radar"
* Patch "Toggle gtasa's HUD"
* GUI Options "menu_rows" and "menu_width"
* FPS Counter

## Version 3.55a
* Custom GUI options from the ini file.
* Readded the cracked samp_a.dll in case you get an internal error.

## Version 3.55
### Added
* Patch "Prevent SetPlayerPos" by alibaba.
* Patch "Air Superiority" by nuckfuts.
* Patch "Colored HP Bar".
* Patch "Colored Money HUD".
* 'b' key will unfreeze you. ini:"key_anti_freeze = b" (SCM Hook).

### Changed
* Removed all samp.dll-accessing related stuff.
* Changed some of texts/menus colors. WUT.

### Fixed
* samp_is_chatting (Chat support).

## Version 3.54 (REALfreaky's Edit)
### Added
* Support for tires
* Support for trailers
* Added mini-map support for single player (and MTA).
* Added a new category for the Vehicles menu: Trailers

### Changed
* Reduced the default hp_minimum to 0.0. This should
  prevent you from getting banned by the new v0.2
  anti vehicle HP cheat scripts.

### Fixed
* Fixed the SA-MP v0.2 crash, but some features will
  be disabled until the new addresses are found.
* Fixed spelling error: Break -> Brake
* Fixed several vehicles being in the wrong category.

## Version 3.53
### Added
* Added a patch that disables the internal "extra actor
  invincibility" patch

### Fixed
* Air break / vehicle freeze bug fixed

## Version 3.52
### Added
* F7/F9 now cycles through SA:MP rendering, m0d_s0beit rendering,
  and disabled.

### Changed
* Panic key now disables the HUD text.

### Fixed
* Panic key now remembers map state

## Version 3.51
### Added
* Fake death by run over / fall
* HUD indicator for freeze nearby vehicles

### Changed
* Don't render chat text and kill messages while in the menu

### Fixed
* Continuously load weapon models to fix single player crash

## Version 3.5
### Added
* Weather and time can be configured from the menu.
* Freeze nearby cars (oem_2 (one of the keys near return))
  Vehicle teleporter will teleport occupied vehicles
  if this is enabled.
* Reintroduced disallow bad weapons. :p
* s0beit_hack_a3v5.raw sprite texture. Make sure you
  copy this to your GTA directory.
* "Reimplementation" of SA:MP chat text, kill msg, and
  "name tag" rendering. (some help from s0beit and jac0b)
  (d3dtext_chat, d3dtext_kill, d3dtext_tag)
* Quick turn around (backspace key)
* Teleport history. Press P to go back to the location you
  were at prior to teleporting.
* Game speed
* More static teleports (cereal)
* Break (key_break_mod, break_mult)
* Vehicle hop (oem_3 (one of the keys near return))

### Changed
* The map now displays the players' name and color, etc.
* Nitro deceleration will only reduce speed if needed
* Reduced the default hp_minimum to 1000.0.
* Better way to detect chatting (wax)
* The inchat_disable setting has been removed
* Disabled money cheat, weapon cheat, and unlock vehicles
  by default in cereal's ini
* Air breaking works differently when the parachute is selected

### Fixed
* Fixed nitro acceleration bug (RaFFeR)
* Fix freeing of invalid memory pointer in ini_free()
* Reduced size of font renderer texture size (512^2 -> 256^2)
* Air break on foot forces your character to stand up

## Version 3.4
### Added
* HP cheats configurable from the menu
* Bike fall-off no damage patch
* Vehicle teleport error messages
* Menu entries to restore HP and Armor
* Money cheat configurable from the menu
* Added some of the teleport locations from cereal's ini
  file to the default ini file.
* "i_have_edited_the_ini_file" must be set to true in the
  ini file, otherwise the game will not start.
* Panic key (disables most cheats)
* Two new menu keys to increase and decrease values (numpad +/-)
* Previous log file is moved to s0beit_hack_old.log on start up
* Vehicle HP bar
* Give HP/Armor
* Change gravity

### Fixed
* Hex viewer no longer crashes in single player mode
* GTA cheat patches are now persistent
* Fixed "perfect handling" memory address
* Fixed force_hour menu toggle

## Version 3.3b
* "anti admin freezing" patch disabled by default

## Version 3.3a
* Fixed ini parsing for patch[] entries (playa')
* Included a copy of cereal's ini file

## Version 3.3
### Added
* Anti bike fall off (CrazyT)
* Put the minimum height checks back in :p
* GTA cheats can be toggled from the .ini
* Reintroduced a hotkey for fly mode (F10)
* Simple memory patcher (see .ini: patch[])
* foo[] now assigns to the first free array index
* HUD text rendering can now be toggled from the menu

### Changed
* Moved GTA cheats, "Allow weapons inside", and "Walk under water"
  to the "Patches" menu.
* Removed the ini reload hotkey
* Moved some memory patches to the .ini file
* d3dtext_enabled option replaced by d3dtext_hud
* Removed a whole bunch of useless GTA cheats (you can add them
  back through the ini file)

### Fixed
* Fixed some default .ini entries
* Fixed some .ini parsing bugs
* Other minor bug fixes

## Version 3.2
### Added
* Re-enabled the checkpoint warp keys. They are disabled by default, though
* Warp vehicles to your location
* The default setting for some menu items can now be set in the .ini file
* Vehicles are now visible when teleported into another "interior"
* Fake kill (use in combination with "fake weapon kill")
* Freeze weather/time can be toggle from the menu
* ScrTogglePlayerControllable is disabled (prevents admins from freezing you)

### Changed
* Improved the hex viewer
* Invulnerability now unsets the "freeze" flag
* Minor menu improvements
* All weapon models are loaded on startup to prevent some weapon crashes
* Disallow weapons feature removed
* Removed all minimum height checks + related .ini entries
* "Anti-cheat revenge" renamed to "Fake weapon kill"
* Removed force weather hotkey (can be configured through the menu)
* Window mode disabled by default
* Etc...

### Fixed
* Fixed speed vector when sticking to actors (REALfreaky)
* Sped up hex viewer rendering slightly
* (Hopefully) Fixed "teleport to player" coordinates (REALfreaky, me)
* Force weather can actually be disabled now (yay!)
* Lots of other minor fixes...

## Version 3.1
### Added
* Walk / drive / fly under water (s0beit)
* Give jetpack (s0beit)
* Menu to warp to any vehicle or player.
* Disallow weapons (prevents crashing from molotov cocktails, etc)
* Added Brass Knuckles to .ini file, and the weapon menu
* Added 8 Ball Auto as a static teleport location
* Unlock vehicles cheat. Automatically unlocks vehicle doors,
  and allows entry to "locked" vehicles (such as the Hunters on
  Novocaine's LS Gang War).
* "Allow weapons inside" is now disabled by default.
* (In game memory hex viewer)

### Fixed
* Fixes to the D3D rendering stuff, should be both
  faster (not that it was ever slow), and cause fewer
  crashes.
* Fixed coords for "Pay 'n' Spray near Wang Cars in Doherty"
* "Stick" now ignores players who are in the same car as you
* Fixed actor/vehicle dead/destroyed detection
* Fixed spelling error: Heat Seaking -> Heat Seeking RPG ...

### Changed
* Changed the default menu key to F11 (cereal)
  (SA:MP was using F9, oops.)
* Moved the weapon menu to the main menu
* Made the font bold. Made the cheat message text dark red.
  Should be easier to read now.
* Moved the menu down a bit, and made it slightly transparent.
* Pressing left in the main menu exits the menu
* You can now tweak the "anti-cheat revenge"

## Version 3.0 (supah beta):
### Added
* .ini format changed slightly, you will need to update
  your .ini file, or replace it with the default one
* In-game menu (F9,up,down,left,right,return)
  Can be used to toggle cheats, warp to static coords,
  configure the weapon cheat, etc.
* The return key can be used as a hotkey
* Static teleports - only configurable in the .ini
* Ability to use the old keyhook (see the .ini file)
* Warp to the nearest empty car (in-game menu)
* Anti-Cheat Revenge - when people kill you, the kill will register
  as a miningun kill: they'll either get banned by the AdminSweep or
  DAntiCheat script, or simply look like a cheater. (REALfreaky, etc)
* God mode is disabled by default
* New .ini settings:
  weapon_allow_inside=true
  money_amount_max=100000
  money_amount_rand_min=500
  money_amount_rand_max=5000
  money_interval_rand_min=10
  money_interval_rand_max=30
  key_cheat_list=f9
  key_cheat_list_up=up
  key_cheat_list_down=down
  key_cheat_list_left=left
  key_cheat_list_right=right
  key_cheat_list_toggle=return
  static_teleport_name[]
  static_teleport_pos[]
  old_keyhook=false

### Changed
* Removed fly mode key (now accessible through the in-game menu)
* Removed perfect handling (accessible through the in-game menu)
* Increased the number of teleports to 10
* Removed the alt-tabbing poo-code
* Removed .ini settings:
  key_fly_mode
  money_amount

### Fixed
* Minor keyhook bugfix
* Removed default settings for weapons (DeN00b)

## Version 2:
* Fixed exit crash bug
* Ignore dead actors

## Version 1 Test 3 / Version 2 Test 1:
* HP no longer continiously set to 100.0. The invulnerability
  cheat is still there, though. This should prevent you from
  get banned by the anti HP cheat script. (Untested; don't know which
  servers have the script running)
* The protection mode thingy now enables the perfect handling cheat.
* Fly mode activates flying boats in addition to flying cars.
* Stick mode now works when on foot.
* Fixed invulnerability flags (REALfreaky)
* Additional HP h4x0ring when on foot (s0beit)
  (You will no longer be decapitated by helicopter rotor blades)
* Semi-working aimbot code, but it's pretty useless atm because:
  1. You can't really hit anything in SA:MP, even if your ping is 1 ms.
  2. There's no movement prediction
  3. The aim is slightly off, and you have to correct it manually
* New key handling code. Keystrokes will no longer be missed
  when your FPS is low. Might have bugs.
* Alt-tabbing out of the game won't halt the game.
* You can use weapons inside stores, casinos, etc...
* Teleporting now also uses the interior ID... which means that you
  can warp cars into stores, etc. (They won't be visible, however)

* Removed intro removal code (sa:mp removes the intro for us)
* Safe haven HP cheat - just an idea I had to defeat the
  anti HP cheat... it's disabled by default, and has not been
  tested much.
* Fixed a long standing bug in the d3d text renderer (Thanks to caytchen)
* Window mode disabled by default
* Min height values set to -1000.0 (ie. disabled) in the .ini file
  since they are useless in SA:MP.
* Renamed ped_* to actor_*
* Minor fixes
