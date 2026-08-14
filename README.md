# Emerald City Roleplay — Client Plugin

Plugin client SA-MP buat server **Emerald City Roleplay**. HUD & fitur
tambahan di-load lewat `samp.exe` asli (bukan client baru dari nol).

## Struktur

```
.
├── .github/workflows/build.yml   # CI: compile DLL 32-bit via GitHub Actions
├── CMakeLists.txt                # Build config
├── include/plugin.h              # Skeleton export interface plugin client
├── src/
│   ├── main.cpp                  # Entry point (Supports/Load/Unload/ProcessTick)
│   ├── hook.h / hook.cpp         # D3D9 hook buat gambar HUD custom
└── README.md
```

## Cara kerja dari HP (Termux)

1. Clone / `cd` ke repo ini di Termux.
2. Edit file di `src/` atau `include/` pakai `nano`/`vim` seperti biasa.
3. `git add . && git commit -m "update hud" && git push`
4. GitHub Actions otomatis compile jadi `ecrp_client.dll` (32-bit).
5. Buka tab **Actions** di GitHub dari HP → download artifact `ecrp_client.dll`,
   atau kalau push tag (`git tag v0.1.0 && git push --tags`) DLL otomatis
   nempel di halaman **Release**.
6. DLL itu yang dikasih ke player, ditaruh di folder plugin client SA-MP
   mereka (bukan di server).

## ⚠️ Yang masih perlu lu lengkapi

Skeleton ini **belum lengkap** dan sengaja disederhanakan supaya bisa
langsung di-compile tanpa error, tapi belum benar-benar fungsional:

- `include/plugin.h` — ABI export plugin client SA-MP di sini masih
  perkiraan pola umum komunitas. **Cocokkan ulang** dengan SDK/header
  yang biasa dipakai project client-mod SA-MP open source (banyak
  beredar di GitHub), karena versi ABI bisa beda-beda.
- `src/hook.cpp` — `InstallD3D9Hook()` masih placeholder. Bagian
  "ambil pointer device D3D9 dari SA-MP yang lagi jalan" belum diisi
  (biasanya lewat hook `CreateDevice` atau pattern-scan memory).
- Belum ada logic komunikasi data server↔client (misal duit RP,
  level) — itu nanti nempel di `ProcessTick()`.

## Testing

Karena build cuma jalan di CI (runner Windows), lu gak bisa test run
langsung dari HP. Alur testing:
1. Compile lewat Actions.
2. Minta tester (staff/player) yang punya PC Windows + GTA:SA + SA-MP
   buat coba taruh DLL-nya dan kasih laporan (screenshot/log).
