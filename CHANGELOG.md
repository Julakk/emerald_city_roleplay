# 📋 Emerald City Roleplay — Changelog

All notable changes, fixes, security updates, and improvements to Emerald City Roleplay are documented here.

---

## 🔧 Patch 0.0.1 — 09 AUG 2026

- 🔒 **Security — UCP Discord (`!register`)**
  - Fixed SQL Injection vulnerability.
  - UCP name & Discord ID search queries are now escaped using `%e`.
  - Prevents dangerous characters from being injected into queries.

- 📝 **UCP Registration**
  - Fixed UCP name length validation.
  - Names are now strictly limited to **3–8 characters**.
  - Fixed error messages to match the active validation rules.

- 🎥 **Streamer Plugin**
  - Updated Streamer Plugin to **v2.9.6**.
  - Updated `streamer.dll` & `streamer.inc`.
  - Include File Version: `0x296`.

- 🌦️ **`/setweather`**
  - Fixed message color parameter conflict with inline color codes.
  - Added weather ID validation: **0–255**.

- 🎁 **`/claimsp` — StarterPack**
  - Fixed VIP duration calculation from 9 days to the intended **7 days**.
  - Fixed incorrect StarterPack vehicle model; now uses a motorcycle as intended.

---

## 🔧 Patch 0.0.2 — 10 AUG 2026

- 🎁 **`/claimsp` — StarterPack**
  - Fixed VIP duration to **7 days**.
  - Fixed StarterPack vehicle model to the intended motorcycle.

- 🚛 **`/newtrucklic`**
  - Fixed incorrect displayed price.
  - Charge is `$5,000`, and the message now displays the correct amount.

- 💰 **`/buy` — Private Farmer & Dealer**
  - Fixed reversed `Server_AddMoney` operation.
  - Server money now increases correctly when a purchase is made.

- 🔍 **`/accept inspect`**
  - Fixed incorrect player connection validation.
  - Changed target check from `pFriskOffer` to `pInsOffer`.

- 🎲 **`/accept dicebet`**
  - Fixed incorrect balance validation target.
  - The second check now correctly validates the bet requester (`offeredby`).

- 🛡️ **Faction Vehicle Respawn Security**
  - Fixed missing permission checks on:
    - `/frespawnveh`
    - `/respawnsags`
    - `/respawnsapd`
    - `/respawnsamd`
    - `/respawnsacf`
    - `/respawnsana`
  - Commands are now restricted to **Admin/Helper**.

- 🚫 **`/ban`**
  - Fixed negative ban time validation.
  - Invalid negative values now correctly stop the process.

- 🔓 **`/unban`**
  - Fixed incomplete staff message arguments.
  - Admin name now displays correctly.

- 🔫 **`/takeweapon`**
  - Fixed reversed permission logic.
  - Fixed incorrect target; weapon is now taken from the suspect instead of the officer.

- 🌿 **`/takemarijuana`**
  - Fixed incorrect target; marijuana is now removed from the suspect instead of the officer.

- 🏥 **`/salve` & `/treatment`**
  - Fixed health validation targeting the medic instead of the patient.

---

## 🔧 Patch 0.0.3 — 10 AUG 2026

- ⛏️ **Miner System**
  - Fixed operator precedence in Miner job conditions.
  - Players can no longer trigger mining actions while inside a vehicle when `ONFOOT` is required.

- 🏭 **Production System**
  - Fixed `/createproduct` production timer not repeating.
  - Production now progresses every **1 second** until completion in **10 seconds**.
  - Fixed Equipment crafting removing **40 Components** instead of the intended **20**.

- 🪵 **Lumber System**
  - Fixed missing quantity parameter in `Inventory_Remove` during the "Kayu Kemas" → "Material" process.

- 🧵 **Tailor System**
  - Fixed a duplication exploit caused by overlapping Thread & Fabric stations.
  - A single action can no longer trigger both stations and produce double items.

- 🚗 **Faction Garage — SACF, SAGS, SAMD**
  - Removed duplicate garage coordinate checks.
  - Simplified repeated checks into a single validation.
  - Fixed stray backslash in SAMD vehicle spawn message.

---

## 🔧 Patch 0.0.4 — 11 AUG 2026

- ⚙️ **Function.inc**
  - Fixed `PlayerIP` not being populated before IP-range ban checks.
  - IP-range ban validation now functions correctly.
  - Removed unused `type` parameter from `cookingsacf` for consistency.

- 🪟 **Dialog.inc**
  - Fixed SQL Injection vulnerabilities in:
    - Twitter name changes
    - Business names
    - Phonebook contacts
  - Queries are now escaped using `%e`.
  - Fixed duplication exploit in `DIALOG_PAY`.
  - Transfer now validates sender balance before completing the transaction.
  - Fixed incorrect Cocaine & Meth dealer stock error message displaying "marijuana".

---

## 🔧 Patch 0.0.5 — 11 AUG 2026

- 💾 **Native.inc**
  - Increased `cQuery` buffer in `UpdatePlayerData`.
  - Buffer increased from `3048` to `8000`.
  - Prevents large UPDATE queries involving 155 columns from being truncated, reducing the risk of failed or corrupted player data saves.

- 🖱️ **OnClick.inc**
  - Fixed vehicle garage health display for slots 2, 3, and 4.
  - Health values are now correctly divided by 10.
  - Fixed `OnLoadCarStorage` being called twice when retrieving a vehicle from the garage.
  - Fixed incorrect port landing message displaying "Bandara".
  - Fixed clothing purchase (`$500`) not validating sufficient balance before transaction.

---

## 🔧 Patch 0.0.6 — 11 AUG 2026

- 🚗 **PlayerVehicle.inc**
  - Fixed duplicate function definitions `OnVehBuyVIPPV` & `OnVehRentPV`.
  - Renamed functions to `OnVehBuyDealerPV` & `OnVehRentDealerPV`.
  - Synchronized function names with `Dialog.inc`.
  - Fixed reversed `/aeject` permission check.
  - Fixed `/aeject` message format string missing an argument.
  - Fixed format string vulnerability in `/vname`.
  - Fixed `/givepv` vehicle plate index confusion.

- 👨‍👩‍👧 **Family.inc**
  - Fixed format string vulnerabilities affecting family name, leader name, and MOTD.
  - Fixed `/fedit material` writing to the marijuana field instead of material.
  - Fixed incorrect `%s` → `%d` format types in marijuana, component, and material edit confirmation messages.
  - Fixed `/f` chat text length validation using `strval` instead of `strlen`.

---

## 🔧 Patch 0.0.7 — 11 AUG 2026

- 🏢 **Bisnis.inc**
  - Fixed `ReturnPlayerBisnisID` slot validation.
  - Fixed `GetOwnedBisnis` not returning `-1`, causing incorrect ownership checks in `/sellbusiness` & `/mybis`.
  - Fixed `/sellbusiness` & `/mybis` reading lock status from the House array instead of Bisnis.
  - Fixed reversed color labels.
  - Fixed owner name buffer overflow risk in `LoadBisnis` & `/createbiz`.
  - Fixed `/editbiz` owner `-1` reset not being saved to the database.

- 🚪 **Door.inc**
  - Fixed `/editdoor garage` saving/refreshing with `gid` instead of `did`.
  - Prevents unintended overwriting of door data IDs 0/1.

- ⛽ **Fuel.inc**
  - Fixed `ReturnGStationNearestID` slot validation.
  - Fixed `/editgs delete` failing to reset `gsPosZ` correctly.

- 🪖 **Helmet.inc**
  - Fixed helmet scale state leaking between players/skins.
  - Static helmet variables are now properly reset.

- 🏠 **House.inc**
  - Fixed `ReturnPlayerHousesID` slot validation.
  - Fixed `/sellhouse` checking `GetOwnedHouses == -1` even though the function returns 0 or higher.
  - Fixed owner/owner2 name buffer overflow risks in `LoadHouses` & `/createhouse`.
  - Fixed `/edithouse` using an oversized `sscanf s[32]` buffer for a `MAX_PLAYER_NAME` field.

---

## 🔧 Patch 0.0.8 — 11 AUG 2026

- 🎵 **Audio.inc**
  - Added bounds validation for `stationNames` array access.
  - Prevents potential crashes when the audio plugin sends an out-of-range station value.

- ❓ **Ask.inc**
  - Fixed `/asks` stopping at the first empty slot.
  - `/asks` now displays all active questions.
  - Fixed dialog being opened multiple times inside the loop.
  - Dialog now opens once after processing the list.
  - Changed `Ask_GetCount() > 1` to `>= 1`.
  - Players with one active question can no longer create another.

- 📝 **Report.inc**
  - Fixed `/reports` with the same empty-slot and repeated-dialog issues as `/asks`.
  - Fixed `Report_GetCount() > 1` to `>= 1`.
  - Players with one active report can no longer submit another.

---

## 🔧 Patch 0.0.9 — 15 AUG 2026

- 🖥️ **TextDraw.inc**
  - Fixed posisi teks **"OVERDOSIS"** pada RedScreen yang berada di luar layar karena posisi Y bernilai minus.
  - Teks overdosis sekarang tampil dengan benar pada RedScreen.

- 🎒 **Inventory.inc**
  - Fixed `BukaInven` yang tidak di-reset ke `0` saat backpack ditutup.
  - Mencegah backpack terkunci permanen setelah dibuka sekali.
  - Fixed inkonsistensi penggunaan Meth pada cabang overdosis berdasarkan health.
  - Sebelumnya terdapat `return` dini yang menyebabkan item tidak terkonsumsi dan backpack tidak tertutup otomatis.
  - Sekarang alurnya disamakan dengan cabang overdosis berdasarkan armor.

- 🖱️ **OnClick.inc**
  - Fixed pengecekan `pGender == 0` yang salah tercampur pada pembatasan lokasi spawn **BANDARA & PELABUHAN**.
  - Karakter baru yang gender-nya belum diset sekarang tetap dapat memilih kedua lokasi tersebut.
  - Mencegah proses spawn menjadi macet permanen.

---

## 🚀 Patch 0.1.0 — 16 AUG 2026

- 🌾 **PrivateFarm.inc**
  - Fixed seluruh sistem dialog Private Farm (`/pfmenu` & `/pfarm plant`) yang sebelumnya tidak pernah berfungsi karena kode terkubur di dalam blok komentar.
  - Fixed field `pfMarijuana` yang belum dideklarasikan di enum.
  - Fixed deposit Wheat yang salah membaca jumlah Orange milik pemain.
  - Fixed pengecekan batas slot vault agar menggunakan jumlah item yang tersimpan di vault farm.
  - Fixed dialog tanam yang hanya dapat digunakan apabila Private Farm ID 0 dimiliki pemain.
  - Fixed 3 dialog ID sistem vault Marijuana yang gagal di-compile.
  - Fixed penggunaan data Marijuana pemain yang salah mengacu ke sistem Seed/Potato/Orange/Wheat.

- 🏪 **Pedagang.inc**
  - Fixed callback penyimpanan gudang pedagang baru yang salah nama fungsi.
  - Fixed perintah edit lokasi & tipe gudang pedagang yang salah memanggil fungsi save sistem lain.

- 🌿 **ProsesKanabis.inc**
  - Fixed flag `pProgress` yang tidak pernah di-set saat proses kanabis dimulai.
  - Mencegah potensi exploit duplikasi Marijuana melalui spam tombol `[Y]`.

- 🛣️ **PayToll.inc**
  - Fixed index array `PaytollAreaid` yang terlewat sehingga index 1 tidak pernah terisi.

---

## 🚀 Patch 0.1.1 — 16 AUG 2026

- 🧹 **Sweeper.inc**
  - Fixed ukuran array `SweepVeh` yang tidak sesuai jumlah kendaraan terisi.
  - Mencegah `IsASweeperVeh(0)` salah mengembalikan `true`.

- 🏧 **Reflenish.inc**
  - Fixed validasi slot ATM yang mustahil terpenuhi (`&&` menjadi `||`).

- 🚕 **Taxi.inc**
  - Fixed penyalahgunaan `GetVehicleParamsEx` sebagai pengganti ID penumpang.
  - Sekarang menggunakan fungsi `GetTaxiPassenger()`.

- 🐔 **TukangAyam.inc**
  - Fixed pesan error batas maksimal ayam yang tidak sesuai dengan validasi kode.
  - Batas sekarang konsisten dari **70 menjadi 100**.

- 🚚 **Trucker.inc**
  - Fixed validasi slot dealer & workshop nearest ID yang mustahil terpenuhi (`&&` menjadi `||`).

- 🗑️ **Trashmaster.inc**
  - Fixed koordinat rotasi trash baru yang salah menimpa `tmRX` dua kali.
  - `tmRZ` sekarang di-set dengan benar.
  - Fixed permission `/gototrash` yang tidak menggunakan `return`.
  - Fixed ukuran array `TrashVeh` yang tidak sesuai jumlah kendaraan terisi.

- 🥛 **Susu.inc**
  - Fixed fungsi `takemilk5` yang hilang.
  - Sapi #5 sekarang dapat diperah kembali.
  - Fixed operator precedence pada sistem duty & pemerahan susu (`&&`/`||`).
  - Sistem sekarang hanya terpicu oleh event tombol yang sesuai.

---

## 🚀 Patch 0.1.2 — 16 AUG 2026

- 💥 **DamageLog.inc**
  - Fixed validasi slot damage log yang mustahil terpenuhi (`&&` menjadi `||`).
  - Fixed format string vulnerability pada `CreateDamageLog`.
  - Nama player tidak lagi digunakan langsung sebagai format string.

- 🔊 **BoomBox.inc**
  - Fixed format string vulnerability pada `/boombox place`.
  - Fixed validasi slot boombox penuh.
  - Mencegah akses array index invalid ketika mencapai batas maksimal.

- 🕳️ **BlackMarket.inc**
  - Fixed `SuccesMsg` pada `CreateGun` & `CreateBomb` yang salah menggunakan `pLoading`.
  - Sekarang menggunakan `playerid` sehingga pesan sukses crafting dapat terkirim dengan benar.
  - Fixed pesan syarat level minimal `/crafting`.
  - Persyaratan sekarang sesuai dengan validasi kode, yaitu **level 3**.

---

## 📊 Patch Summary

| Patch | Date | Focus |
|---|---|---|
| 🔧 0.0.1 | 09 AUG 2026 | Security, Registration, Streamer, Weather, StarterPack |
| 🔧 0.0.2 | 10 AUG 2026 | Commands, Security, Permissions, Faction Systems |
| 🔧 0.0.3 | 10 AUG 2026 | Jobs, Production, Lumber, Tailor, Garages |
| 🔧 0.0.4 | 11 AUG 2026 | SQL Injection, Payment Security, Dialog |
| 🔧 0.0.5 | 11 AUG 2026 | Database Safety, Garage, Purchases |
| 🔧 0.0.6 | 11 AUG 2026 | Vehicle, Family, Permission & Format Security |
| 🔧 0.0.7 | 11 AUG 2026 | Business, Door, Fuel, Helmet, House |
| 🔧 0.0.8 | 11 AUG 2026 | Audio, Ask & Report Systems |
| 🔧 0.0.9 | 15 AUG 2026 | Overdose, Inventory, Spawn & TextDraw Fixes |
| 🚀 0.1.0 | 16 AUG 2026 | Private Farm, Pedagang, Kanabis & PayToll |
| 🚀 0.1.1 | 16 AUG 2026 | Sweeper, ATM, Taxi, Trucker, Trashmaster & Susu |
| 🚀 0.1.2 | 16 AUG 2026 | DamageLog, BoomBox & BlackMarket |

---

> 🌆 **Emerald City Roleplay**
> *Build Your Story. Become Part of Emerald City.*
