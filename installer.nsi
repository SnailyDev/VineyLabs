!define APP_NAME "2D RPG Game"
!define APP_VERSION "1.0"
!define INSTALL_DIR "$PROGRAMFILES64\2D RPG Game"
!define EXE_NAME "rpg_game.exe"

OutFile "rpg_game_installer.exe"
InstallDir "${INSTALL_DIR}"
RequestExecutionLevel user

Section "Install"
    SetOutPath "$INSTDIR"
    File /r "dist\src\main.cpp" ; Include all files from the 'dist' folder

    ; Create shortcuts
    CreateShortcut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${EXE_NAME}"
    CreateShortcut "$SMPROGRAMS\${APP_NAME}\${APP_NAME}.lnk" "$INSTDIR\${EXE_NAME}"
SectionEnd

Section "Uninstall"
    Delete "$DESKTOP\${APP_NAME}.lnk"
    Delete "$SMPROGRAMS\${APP_NAME}\${APP_NAME}.lnk"
    Delete "$INSTDIR\*.*"
    RMDir "$INSTDIR"
SectionEnd
