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

!ifndef nsisbassmod.NSH.Included
!verbose push
!verbose 3
!define nsisbassmod.NSH.Included

; Function defines
; Note: Only those who are required to playback a MP3 and MOD (modules)
; files is defined. You can define more if you like.

; BOOL WINAPI BASSMOD_Init(int device, DWORD freq, DWORD flags, HWND win);
!define bfnInit "${BASSMOD_LOCATION_PLUGINSDIR}::BASSMOD_Init(i,i,i,i) b"

; HMUSIC WINAPI BASSMOD_MusicLoad(BOOL mem, void *file, DWORD offset, DWORD length, DWORD flags);
!define bfnMusicLoad "${BASSMOD_LOCATION_PLUGINSDIR}::BASSMOD_MusicLoad(b,t,i,i,i) i"

; BOOL WINAPI BASSMOD_MusicPlay(HMUSIC handle);
!define bfnMusicPlay "${BASSMOD_LOCATION_PLUGINSDIR}::BASSMOD_MusicPlay() b"

; BOOL WINAPI BASSMOD_MusicStop();
!define bfnMusicStop "${BASSMOD_LOCATION_PLUGINSDIR}::BASSMOD_MusicStop() b"

; void WINAPI BASSMOD_MusicFree(HMUSIC handle);
!define bfnMusicFree "${BASSMOD_LOCATION_PLUGINSDIR}::BASSMOD_MusicFree() v"

; void WINAPI BASSMOD_Free();
!define bfnFree "${BASSMOD_LOCATION_PLUGINSDIR}::BASSMOD_Free() v"


!verbose pop
!endif
