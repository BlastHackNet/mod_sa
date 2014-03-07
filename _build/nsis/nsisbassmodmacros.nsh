; NSIS frontend to bassmod (NSISBASSMOD)
; Macros and ´System::Call´ definitions required
; to use BASSMOD Sound System
;
; Written by nuckfuts
; Original BASS version by Saivert
;
; Dependencies: System.dll - NSIS plugin
;               Bass.dll - BASSMOD Sound System library
;
; Define BASSMOD_LOCATION to the location of BASSMOD.DLL on
; the compiler system if it is located somewhere else.
; '${NSISDIR}\Contrib\nsisbassmod\bassmod.dll' is the default.

!ifndef nsisbassmodmacros.NSH.Included
!verbose push
!verbose 3
!define nsisbassmodmacros.NSH.Included

; Where will we find bassmod.dll?
!ifndef BASSMOD_NAME
	!define BASSMOD_NAME "bassmod.dll"
!endif
!ifndef BASSMOD_PATH
	!define BASSMOD_PATH ".\"
!endif
!ifndef BASSMOD_LOCATION_PLUGINSDIR
	!define BASSMOD_LOCATION_PLUGINSDIR "$PLUGINSDIR\${BASSMOD_NAME}"
!endif

; Include the function prototypes for bassmod.dll
!include "${BASSMOD_PATH}\nsisbassmod.nsh"


; 1st. Use the NSISBASSMOD_Init
; macro to initialize BASSMod
!macro NSISBASSMOD_Init
!verbose push
!verbose 3

	!ifdef BASSMOD_LOCATION
		ReserveFile "${BASSMOD_LOCATION}"
	!else
		ReserveFile "${NSISDIR}\contrib\nsisbassmod\bassmod.dll"
	!endif
	ReserveFile "${NSISDIR}\Plugins\system.dll"
	InitPluginsDir
	!ifndef BASSMOD_LOCATION
		File "/oname=$PLUGINSDIR\bassmod.dll" "${NSISDIR}\contrib\nsisbassmod\bassmod.dll"
	!else
		File "/oname=$PLUGINSDIR\bassmod.dll" "${BASSMOD_LOCATION}"
	!endif
	; Open device
	System::Call /NOUNLOAD '${bfnInit} (-1,44100,0,0) .r0'

!verbose pop
!macroend

; 2nd. Now it's time to ouptut some sound.
; The macro will leave "failed" at the top of the stack if it
; couldn't load the song or if sound card init failed.
!macro NSISBASSMOD_MusicPlay SONG
!verbose push
!verbose 3
; Save registers
Push $0
Push $1
Push $2

	Push "${SONG}"
	Call NSISBASSMODMusicPlay

; Restore registers
Pop $2
Pop $1
Pop $0
!verbose pop
!macroend

Function NSISBASSMODMusicPlay
	Pop $2 ; Filename
	StrCpy $0 "" ; Clear
	StrCpy $1 "" ;   all

	System::Call /NOUNLOAD '${bfnMusicLoad} (0,s,0,0,5) .r1' '$2'
	StrCmp $1 "0" NSISBASSMOD_FAIL
	System::Call /NOUNLOAD '${bfnMusicPlay} (r1) .r0'
	Goto NSISBASSMOD_EXIT

	NSISBASSMOD_FAIL:
		StrCmp $1 "0" 0 +2
		System::Call /NOUNLOAD "${bfnMusicFree} .r0"
		Push "failed"
	NSISBASSMOD_EXIT:
FunctionEnd

!macro NSISBASSMOD_MusicStop
!verbose push
!verbose 3
	System::Call /NOUNLOAD "${bfnMusicStop} .r0"
!verbose pop
!macroend



; 3rd. and final: These are simple ones.

!macro NSISBASSMOD_MusicFree
!verbose push
!verbose 3
	System::Call "${bfnMusicFree} .r0" ; Also unloads the music
!verbose pop
!macroend

!macro NSISBASSMOD_Free
!verbose push
!verbose 3
	System::Call "${bfnFree} .r0" ; Also unloads bassmod.dll
!verbose pop
!macroend

!verbose pop
!endif
