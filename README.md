# UTAR Accommodation Management System 🏠

[![Language](https://img.shields.io/badge/language-C%2B%2B-00599C?logo=cplusplus)](https://en.wikipedia.org/wiki/C%2B%2B)
[![Platform](https://img.shields.io/badge/platform-Windows%20CLI-0078D6?logo=windows)](#)
[![Status](https://img.shields.io/badge/status-active-brightgreen)](#)
[![License](https://img.shields.io/badge/license-MIT-yellow)](#license)

A **C++ console-based Accommodation Management System** built for the **UTAR (Universiti Tunku Abdul Rahman) Sungai Long campus**, developed as part of the Programming and Problem Solving course. This student accommodation platform lets **property owners list rentals** and **students search, shortlist, enquire, and apply** for off-campus housing near UTAR — all through a structured, menu-driven C++ CLI backed by flat-file (`.txt`) storage.

> Keywords: UTAR accommodation system, C++ console application, student housing management system, campus rental listing platform, property management CLI project, flat-file data persistence C++, OOP mini project, university assignment source code.

---

## 📖 Table of contents

- [Overview](#overview)
- [Features](#features)
- [System architecture](#system-architecture)
- [Tech stack](#tech-stack)
- [Project structure](#project-structure)
- [Getting started](#getting-started)
- [Usage](#usage)
- [Data storage format](#data-storage-format)
- [Contributors](#contributors)
- [License](#license)

---

## Overview

The **UTAR Accommodation Management System** solves a real problem for students at the Sungai Long campus: finding and managing off-campus rentals without relying on scattered social media posts. The system models two user roles — **Student** and **Owner** — and covers the full rental lifecycle: **listing → searching → shortlisting → enquiry → application → analytics**.

Built entirely in **C++** with **struct-based data modelling** and **flat-text file persistence** (no external database or JSON library), this project demonstrates core computer science fundamentals: file I/O, structs, modular program design, and menu-driven CLI architecture — making it a strong reference for anyone studying **C++ console application development** or working on a similar **university programming assignment**.

## Features

- 🔐 **Authentication** — separate registration/login flows for Students and Owners
- 🏘️ **Accommodation listing & search** — owners add/update/delete properties; students search and filter by price, type, and **distance from UTAR**
- ⭐ **Shortlisting** — students bookmark properties of interest for later comparison
- 💬 **Communication & appointment module** — students send enquiries to owners, owners reply, both sides can view enquiry history
- 📄 **Rental management** — full application lifecycle (apply, approve/reject, active rental records)
- 📊 **Property insights & analytics** — total listings, average price, property-type breakdown, distance statistics, and shortlist popularity stats
- 🗂️ **Flat-file persistence** — all data stored in structured, human-readable `.txt` files, no external database required

## System architecture

The system follows a top-down modular structure: `main.cpp` routes into four core modules — **Auth & Login**, **Listings**, **Communication**, and **Rental Management** (which itself contains the **Analytics** sub-module) — all sharing a single header, `accomedation.h`, for struct and function declarations.

```
main.cpp
 ├── Auth & Login          (student / owner registration + login)
 ├── Listings              (add / update / delete / search / shortlist)
 ├── Communication         (send / view / reply to enquiries)
 └── Rental Management     (apply / approve / track rentals)
      └── Analytics        (5 reporting functions)
```

## Tech stack

| Layer | Technology |
|---|---|
| Language | C++ (`bits/stdc++.h`, MSVC) |
| Interface | Windows console (CLI, menu-driven) |
| Data persistence | Flat `.txt` files, label-prefixed block format |
| Build | Multiple `.cpp` files compiled into a single `main.exe` |
| Version control | Git & GitHub (team collaboration) |
| IDE | Visual Studio Code |

## Project structure

```
Accommodation App in CLI/
├── accomendation listing and search/
│   ├── data/
│   │   ├── owner.txt
│   │   ├── property.txt
│   │   ├── shortlist.txt
│   │   ├── student.txt
│   │   └── temp_property.txt
│   ├── output/
│   ├── acoomendation_listing_searching.cpp
│   ├── Owner.cpp
│   └── student.cpp
├── communication apoitment/
│   ├── data/
│   │   └── communication.txt
│   ├── output/
│   │   ├── main.exe
│   │   └── test.exe
│   ├── communication_appoitment.cpp
│   ├── owner_enquiry.cpp
│   └── student_enquiry.cpp
├── rental management/
│   └── data/
│       └── rental_applications.txt
├── Rental Management & Analytics/
│   ├── analytics_part.cpp
│   ├── main_Rental_analysisarea.cpp
│   └── rental_management.cpp
├── accomedation.h               # Shared struct & function declarations
├── main.cpp                     # Entry point — routes to all modules
├── .editorconfig
└── README.md
```

> Note: folder names above (e.g. `accomendation listing and search`, `communication apoitment`) match the actual repo layout, including their original spelling — kept as-is for consistency with existing `#include` paths.

## Getting started

### Prerequisites
- A C++ compiler (MinGW / MSVC)
- Windows (uses `system("mkdir ...")` for directory setup)

### Build & run

```bash
git clone https://github.com/<your-org>/utar-accommodation-management-system.git
cd utar-accommodation-management-system

g++ main.cpp ^
    "accomendation listing and search/acoomendation_listing_searching.cpp" ^
    "accomendation listing and search/Owner.cpp" ^
    "accomendation listing and search/student.cpp" ^
    "communication apoitment/communication_appoitment.cpp" ^
    "communication apoitment/owner_enquiry.cpp" ^
    "communication apoitment/student_enquiry.cpp" ^
    "Rental Management & Analytics/analytics_part.cpp" ^
    "Rental Management & Analytics/main_Rental_analysisarea.cpp" ^
    "Rental Management & Analytics/rental_management.cpp" ^
    -o main.exe

main.exe
```

> On Windows `cmd`/PowerShell, quote every path containing spaces (as above). On a Unix-like shell, replace the `^` line continuations with `\`.

## Usage

1. Launch `main.exe`.
2. Choose to register or log in as a **Student** or **Owner**.
3. **Owners**: add, update, or remove property listings.
4. **Students**: search listings, shortlist favourites, send enquiries, and apply for a rental.
5. Both roles can view and reply to enquiries via the **Communication** menu.
6. Rental applications and the **Analytics** dashboard are accessible from the Rental Management menu.

## Data storage format

All records are stored as label-prefixed blocks separated by a dashed line, keeping the files human-readable and easy to debug:

```
Property ID : P001
Owner ID    : O003
Address     : Jalan Sungai Long, Bandar Sungai Long
Price       : 650
Distance    : 2.3
----------------------
```

## Contributors

This is a **team project** built collaboratively via GitHub. Contributions were split across modules (Auth, Listings, Communication, Rental & Analytics).

| Name 
|---|---|
| Ayon | WHY-0318 | Kenneth Chua | Backham Lim

> Contributions welcome via pull request — please follow the existing flat-file I/O and struct conventions described above.

## License

This project was developed for academic purposes as part of the UTAR Programming and Problem Solving course. Released under the [MIT License](LICENSE) unless your course requires otherwise — check with your lecturer before reusing for another assignment.

---

**Topics:** `cpp` `c-plus-plus` `console-application` `accommodation-management-system` `student-housing` `property-management` `file-handling` `struct` `utar` `university-project` `crud-application` `cli-app`
