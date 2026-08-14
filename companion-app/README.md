# Emerald City Roleplay — Companion App

App Android (bukan game) buat player Emerald City Roleplay: cek status
server, link Discord, panduan main, berita/event, dan top-up.

**App ini TIDAK berisi file GTA:SA apapun** — cuma info & link. Aman
secara hak cipta, gak nyentuh/redistribusi game Rockstar sama sekali.

## Struktur

```
companion-app/
├── package.json                  # Dependency Capacitor
├── capacitor.config.js           # Config app (nama, appId)
├── www/index.html                # Seluruh UI app (1 file: status,
│                                    discord, cara main, berita, donasi)
└── query-backend/ecrp-query.php  # Backend query status server SA-MP

# Workflow CI-nya ada di root repo: .github/workflows/build-companion.yml
# (terpisah dari workflow plugin Windows biar gak saling ganggu)
```

## Fitur

1. **Status Server** — online/offline, jumlah player, ping. Data diambil
   dari `query-backend/ecrp-query.php` yang di-hosting terpisah (lihat
   bagian Setup Backend di bawah).
2. **Komunitas** — link Discord (ganti dulu invite code-nya) + link
   Ahmad Store.
3. **Cara Main** — panduan 4 langkah buat player baru.
4. **Berita** — placeholder, edit manual di `www/index.html` bagian
   `#newsList`, atau sambungin ke backend kalau mau dinamis.
5. **Donasi** — daftar harga VIP + tombol ke Ahmad Store.

## Setup Backend Query (WAJIB biar status server jalan)

SA-MP pakai protokol query lewat **UDP**, bukan HTTP — jadi app mobile
gak bisa langsung nanya ke server game. `ecrp-query.php` adalah
jembatannya.

1. Upload `query-backend/ecrp-query.php` ke hosting Ahmad Store lu
   (folder publik, misal `https://ahmadstore.my.id/ecrp-query.php`).
2. Pastikan hosting itu **mengizinkan koneksi UDP outbound** — banyak
   shared hosting yang blokir ini, kalau kena, hasilnya selalu
   "offline" walau server sebenernya online. Kalau shared hosting lu
   gak support, alternatifnya jalanin script ini di VPS Ahmad Store
   (VPS lebih fleksibel soal koneksi keluar).
3. Buka `www/index.html`, cari baris:
   ```js
   const QUERY_BACKEND_URL = 'https://ahmadstore.my.id/ecrp-query.php';
   ```
   Ganti sesuai URL beneran tempat lu upload PHP-nya.

## Cara build dari Termux (sama kayak alur Pawn Studio)

```bash
cd emerald_city_roleplay   # root repo, bukan folder companion-app
git add companion-app .github/workflows/build-companion.yml
git commit -m "add companion app"
git push
```

GitHub Actions otomatis build APK (cuma jalan kalau ada perubahan di
folder `companion-app/`, gak ke-trigger pas lu edit plugin Windows).
Cek tab **Actions**, download artifact `ecrp-companion-app`, atau push
tag `app-v0.1.0` (`git tag app-v0.1.0 && git push --tags`) buat APK
otomatis nempel di halaman Release.

## Yang masih perlu lu lengkapi

- Ganti `GANTI-INVITE-CODE` di `www/index.html` dengan invite Discord
  beneran.
- Isi harga VIP & deskripsi sesuai paket Emerald City Roleplay
  beneran (sekarang masih contoh: Bronze Rp25rb, Gold Rp75rb).
- Isi konten `#newsList` dengan berita/event beneran.
- Icon app masih default Capacitor — ganti pakai logo Emerald City lu
  di `android/app/src/main/res/mipmap-*/` setelah `cap add android`
  pertama kali jalan (atau pakai tool `@capacitor/assets` buat
  generate otomatis dari satu file logo).
