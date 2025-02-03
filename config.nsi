; Define the name and output of the installer
Name "Blappy Fird"
OutFile "blappy-fird-installer-1.0.0.exe"

; Define the default installation directory
InstallDir "$PROGRAMFILES\BlappyFird"

; Set the installer icon (optional)
Icon "icon_64x64.ico"

; Request administrative privileges
RequestExecutionLevel admin

; Define the files and directories to include
Section "MainSection"
    ; Create the installation directory
    SetOutPath "$INSTDIR"

    ; Copy application files
    File /r "build\blappy-fird.exe"
    File /r "resources\bird.png"

    ; Create shortcuts
    CreateShortcut "$DESKTOP\BlappyFird.lnk" "$INSTDIR\blappy-fird.exe"
    CreateShortcut "$SMPROGRAMS\BlappyFird\Uninstall.lnk" "$INSTDIR\uninstall.exe"

    ; Write uninstall information
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

; Uninstaller Section
Section "Uninstall"
    ; Remove installed files
    Delete "$INSTDIR\blappy-fird.exe"
    Delete "$INSTDIR\bird.png"

    ; Remove shortcuts
    Delete "$DESKTOP\BlappyFird.lnk"
    Delete "$SMPROGRAMS\BlappyFird\Uninstall.lnk"

    ; Remove directories
    RMDir "$INSTDIR"

    ; Delete uninstaller
    Delete "$INSTDIR\uninstall.exe"
SectionEnd

; Installer User Interface
Page Directory
Page InstFiles
UninstPage InstFiles

; Set installer messages
LangString DESC_Section1 1033 "Installs the game Blappy Fird."