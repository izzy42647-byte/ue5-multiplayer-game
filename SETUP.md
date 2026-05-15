# UE5 Multiplayer Game - Development Setup

## System Requirements

### Minimum
- **CPU**: Intel i7-9700K / AMD Ryzen 5 3600
- **RAM**: 32GB
- **GPU**: RTX 2080 / RTX 5700 XT
- **Storage**: 500GB SSD
- **OS**: Windows 10/11

### Recommended
- **CPU**: Intel i9-13900K / AMD Ryzen 9 7950X
- **RAM**: 64GB
- **GPU**: RTX 4090
- **Storage**: 1TB NVMe SSD
- **OS**: Windows 11

## Installation Guide

### 1. Install Unreal Engine 5.3+

```bash
# Download from Epic Games Launcher
# Install to default location: C:\Program Files\Epic Games\UE_5.3
```

### 2. Install Required Tools

#### Visual Studio 2022
```bash
# Download: https://visualstudio.microsoft.com/downloads/
# Required components:
# - C++ Desktop Development
# - Game Development with C++
```

#### Git
```bash
# https://git-scm.com/download/win
```

### 3. Clone Repository

```bash
git clone https://github.com/izzy42647-byte/ue5-multiplayer-game.git
cd ue5-multiplayer-game
```

### 4. Generate Project Files

**Windows:**
```bash
.\GenerateProjectFiles.bat
```

**Mac/Linux:**
```bash
./GenerateProjectFiles.sh
chmod +x GenerateProjectFiles.sh
```

### 5. Open in Visual Studio

```bash
# Windows
start ue5-multiplayer-game.sln

# Then compile in Visual Studio
# Build > Rebuild Solution (or Ctrl+Alt+F7)
```

### 6. Open in Unreal Editor

```bash
# Method 1: Double-click project file
ue5-multiplayer-game.uproject

# Method 2: From Epic Games Launcher
# Select project > Open in Unreal Engine
```

**First launch will:**
- Compile C++ code (~5-15 minutes)
- Compile shaders (~20-30 minutes)
- Create Intermediate/Binaries folders

## Project Structure

```
ue5-multiplayer-game/
├── Source/
│   └── Game/
│       ├── Character/          # PlayerCharacter system
│       ├── Combat/             # WeaponBase, damage
│       ├── Building/           # BuildingSystem, structures
│       ├── Networking/         # GameMode, networking
│       ├── Economy/            # Shop, cosmetics
│       └── UI/                 # UMG widgets
├── Content/
│   ├── Characters/             # Character models, animations
│   ├── Weapons/                # Weapon meshes
│   ├── Structures/             # Building meshes
│   ├── UI/                     # UI assets
│   ├── Materials/              # Nanite + Lumen materials
│   └── Maps/                   # Game maps
├── Plugins/
├── Binaries/
├── Intermediate/
├── Saved/
└── ue5-multiplayer-game.uproject
```

## Building & Compiling

### Compile C++ Code

**In Visual Studio:**
```
Build > Rebuild Solution
```

**Or from Command Line:**
```bash
cd Source
cd Game
# Uses UBT (Unreal Build Tool)
```

**In Unreal Editor:**
```
Tools > Compile
```

### Cook Content for Shipping

```bash
# Windows
Engine\Build\BatchFiles\RunUAT.bat BuildCookRun -project="ue5-multiplayer-game.uproject" -platform=Win64 -configuration=Shipping
```

## Network Configuration

### Replication Graph Setup

Located in: `Source/Game/Networking/GameNetworkManager.h`

Key features:
- 100 concurrent players
- 120 Hz tick rate
- Optimized priority culling
- Player location-based replication

### Dedicated Server

```bash
# Package dedicated server binary
# Edit DefaultEngine.ini:
[/Script/Engine.Engine]
+ServerNetworkTickRate=120
+NetClientTicksPerSecond=60
```

## Testing Locally

### PIE (Play In Editor)
- Editor > Play
- Default: 1 player
- For multiplayer testing, enable "Net Mode: Simulate"

### Standalone Game
- Editor > Launch (Default Player)
- Runs standalone executable

### Multiple Instances
```bash
# Launch multiple instances for testing
ue5-multiplayer-game.exe -netmode=listen -port=7777
ue5-multiplayer-game.exe -netmode=client -url=localhost:7777
```

## Packaging for Distribution

### Windows Shipping Build

```bash
1. File > Project Settings > Project > Supported Platforms
   - Enable Windows 64-bit

2. File > Package Project > Windows (64-bit)

3. Select output folder

4. Wait for packaging (~30 minutes for first build)

5. Navigate to: Binaries > Win64 > ue5-multiplayer-game.exe
```

### PlayStation 5 (Requires Dev Kit)

```bash
1. Register with Sony/Epic for SDK
2. Install PS5 SDK in: C:\Program Files\SCE
3. File > Package Project > PlayStation 5
4. Follow Sony's submission guidelines
```

### Xbox Series X|S (Requires Dev Kit)

```bash
1. Register with Microsoft for Xbox SDK
2. Install Xbox SDK
3. File > Package Project > Xbox
4. Follow Microsoft's submission guidelines
```

## Common Issues & Solutions

### "Missing .dll files"
```
Solution: Visual Studio C++ Redistributable
Download: https://support.microsoft.com/en-us/help/2977003
```

### "Shader compilation failures"
```
Solution: 
- Delete Intermediate/ShaderCache folder
- Restart editor
- Let shaders recompile
```

### "Module not found" error
```
Solution:
1. Delete Binaries, Intermediate, Saved folders
2. Right-click .uproject > Generate Visual Studio project files
3. Rebuild in Visual Studio
```

### Networking not working in PIE
```
Solution:
1. Editor > Editor Preferences > Network
2. Enable "Allow Network Emulation"
3. Set players to spawn: 4+ for testing
```

## Performance Optimization

### Profiling Tools

**Stat Commands (In-game console `~`):**
```
stat unit              # Frame time breakdown
stat fps               # Current FPS
stat unitgraph         # Visual FPS graph
stat memory            # Memory usage
stat game              # Game thread stats
stat render            # Render thread stats
stat rhi               # GPU stats
```

### Nanite Settings

- Automatically virtualizes geometry
- Target: <100MB of memory per 100 players
- Configured in: `Content > Materials > Nanite_Settings`

### Lumen Settings

- Real-time global illumination
- Quality: Scalable based on hardware
- Set in: `Project Settings > Rendering > Global Illumination`

## Continuous Integration

### GitHub Actions (Optional)

Set up automated builds:

```yaml
# .github/workflows/build.yml
name: Build UE5 Game
on: [push, pull_request]

jobs:
  build:
    runs-on: [ubuntu-latest, windows-latest]
    steps:
      - uses: actions/checkout@v2
      - name: Compile
        run: ./Scripts/build.sh
```

## Next Steps

1. ✅ Compile project successfully
2. ✅ Launch in editor
3. ✅ Test multiplayer in PIE
4. ✅ Add custom content (characters, maps)
5. ✅ Package for distribution
6. ✅ Deploy to servers

## Resources

- **UE5 Documentation**: https://docs.unrealengine.com/
- **Multiplayer Tutorials**: https://www.youtube.com/watch?v=X6NJkjVrMLQ
- **Networking Guide**: https://docs.unrealengine.com/en-US/Gameplay/Networking/
- **Community**: https://forums.unrealengine.com/

## Support

For issues:
1. Check GitHub Issues
2. Post on UE Forums
3. Check your Local Logs: `Saved/Logs/`

---

**You're ready to build an AAA game!** 🚀
