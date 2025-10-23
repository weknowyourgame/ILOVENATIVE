# ILOVENATIVE

A powerful cross-platform tool for converting websites into native desktop applications using the Chromium Embedded Framework (CEF).

## Overview

ILOVENATIVE enables developers to wrap any website in a native desktop application shell, providing users with a seamless native experience while leveraging web technologies. The generated applications run with the full power of Chromium, ensuring compatibility and performance.

## Features

- Generate native applications for Windows, macOS, and Linux
- Built on the Chromium Embedded Framework for reliable web content rendering
- Simple CLI for specifying website URLs and target platforms
- Applications integrate seamlessly with the host operating system
- Supports both CMake and Bazel build configurations

## Architecture

ILOVENATIVE consists of two main components:

### CEF Component (`/cef`)
The core native application wrapper that:
- Provides the Chromium Embedded Framework integration
- Handles platform-specific application lifecycle
- Manages browser window creation and management
- Implements native OS integration (menus, dock, taskbar, etc.)

### CLI Component (`/cli`)
The command-line interface that:
- Accepts website URLs and target platforms as input
- Validates user input (URL format, platform selection)
- Orchestrates the native application generation process
- Provides a user-friendly interface for the conversion workflow

## Supported Platforms

| Platform | Status | Build System |
|----------|--------|--------------|
| Windows  | ✅ Supported | CMake, Bazel |
| macOS    | ✅ Supported | CMake, Bazel |
| Linux    | ✅ Supported | CMake, Bazel |

## Requirements

### System Requirements
- **Windows**: Windows 10 or later (64-bit)
- **macOS**: macOS 10.15 or later (64-bit)
- **Linux**: Modern 64-bit distributions with GLIBC 2.17+

### Build Requirements
- **CMake** 3.16 or later
- **C++17** compatible compiler
- **Chromium Embedded Framework** libraries
- **Platform-specific SDKs** (Windows SDK, Xcode command line tools, etc.)

## Installation

### From Source

1. **Clone the repository**
   ```bash
   git clone https://github.com/weknowyourgame/ILOVENATIVE
   cd ILOVENATIVE
   ```

2. **Build the CLI tool**
   ```bash
   cd cli
   mkdir build && cd build
   cmake ..
   make
   ```

3. **Install CLI globally** (optional)
   ```bash
   sudo cp bin/ILOVENATIVE /usr/local/bin/ilovenative
   ```

## Usage

### Example Workflow

```bash
$ ./cli/build/bin/ILOVENATIVE

  //               ,--,                                                                          ,----,                               
  //            ,---.'|       ,----..                                  ,--.                    ,/   .`|                               
  //       ,---,|   | :      /   /   \                  ,---,.       ,--.'|   ,---,          ,`   .'  :   ,---,                ,---,. 
  //    ,`--.' |:   : |     /   .     :        ,---.  ,'  .' |   ,--,:  : |  '  .' \       ;    ;     /,`--.' |       ,---.  ,'  .' | 
  //    |   :  :|   ' :    .   /   ;.  \      /__./|,---.'   |,`--.'`|  ' : /  ;    '.   .'___,/    ,' |   :  :      /__./|,---.'   | 
  //    :   |  ';   ; '   .   ;   /  ` ; ,---.;  ; ||   |   .'|   :  :  | |:  :       \  |    :     |  :   |  ' ,---.;  ; ||   |   .' 
  //    |   :  |'   | |__ ;   |  ; \ ; |/___/ \  | |:   :  |-,:   |   \ | ::  |   /\   \ ;    |.';  ;  |   :  |/___/ \  | |:   :  |-, 
  //    '   '  ;|   | :.'||   :  | ; | '\   ;  \ ' |:   |  ;/||   : '  '; ||  :  ' ;.   :`----'  |  |  '   '  ;\   ;  \ ' |:   |  ;/| 
  //    |   |  |'   :    ;.   |  ' ' ' : \   \  \: ||   :   .''   ' ;.    ;|  |  ;/  \   \   '   :  ;  |   |  | \   \  \: ||   :   .' 
  //    '   :  ;|   |  ./ '   ;  \; /  |  ;   \  ' .|   |  |-,|   | | \   |'  :  | \  \ ,'   |   |  '  '   :  ;  ;   \  ' .|   |  |-, 
  //    |   |  ';   : ;    \   \  ',  /    \   \   ''   :  ;/|'   : |  ; .'|  |  '  '--'     '   :  |  |   |  '   \   \   ''   :  ;/| 
  //    '   :  ||   ,/      ;   :    /      \   `  ;|   |    \|   | '`--'  |  :  :           ;   |.'   '   :  |    \   `  ;|   |    \ 
  //    ;   |.' '---'        \   \ .'        :   \ ||   :   .''   : |      |  | ,'           '---'     ;   |.'      :   \ ||   :   .' 
  //    '---'                 `---`           '---" |   | ,'  ;   |.'      `--''                       '---'         '---" |   | ,'   
  //                                                `----'    '---'                                                        `----'     
  //    

Welcome to ILOVENATIVE CLI
Convert any website to native app

Enter the website URL
https://example.com

Choose target Platform[Win/Mac/Linux]
macos

Please confirm the following details[Y/n]:
Website: https://example.com
Platform: macos
Y

Details confirmed. Proceeding...
Processing conversion for: https://example.com on macos
```

## Build Configuration

### CMake Build (CEF Component)

```bash
cd cef
mkdir build && cd build
cmake ..
make
```

### Bazel Build (Alternative)

```bash
cd cef
bazel build //:ILOVENATIVE
```

## Technical Details

### CEF Integration
ILOVENATIVE leverages CEF's multi-process architecture to provide:
- Secure sandboxed web content rendering
- Native window management integration
- Platform-specific feature support (notifications, file dialogs, etc.)
- Hardware-accelerated graphics when available

### Application Architecture
- **Browser Process**: Main application logic and window management
- **Render Process**: Isolated web content rendering
- **Platform Abstraction**: Consistent API across Windows, macOS, and Linux

## Support

For issues, feature requests, or questions:
1. Check the existing issue tracker
2. Create a new issue with detailed information
3. Include platform details, CEF version, and reproduction steps
