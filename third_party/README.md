# Third-party dependencies

This directory contains vendored copies of all third-party dependencies used by
Utility. They are consumed at configure time via `FetchContent` with a local
`SOURCE_DIR`, so no network access is required to build the project.

Each dependency is pinned to a specific upstream version. To update a
dependency, replace the contents of its directory with the new upstream release
and update the version recorded below.

| Directory              | Dependency          | Version / commit                          | Upstream                                                              | License |
| ---------------------- | ------------------- | ----------------------------------------- | --------------------------------------------------------------------- | ------- |
| `tinyobjloader/`       | tinyobjloader       | `45636bdcef1a4fec140346b90c0b50bf0bc3e23b` | https://github.com/tinyobjloader/tinyobjloader                        | MIT |
| `glm/`                 | GLM                 | `1.0.3`                                   | https://github.com/g-truc/glm                                         | MIT (Happy Bunny / MIT) |
| `freetype/`            | FreeType            | `VER-2-14-3`                              | https://gitlab.freedesktop.org/freetype/freetype                      | FTL / GPLv2 |
| `stb/`                 | stb                 | `2c980bb59875b0d32144a71867fbdebb2f77cd20` | https://github.com/nothings/stb                                       | MIT / Public Domain |
| `fmt/`                 | {fmt}               | `12.2.0`                                  | https://github.com/fmtlib/fmt                                         | MIT |
| `openal-soft/`         | OpenAL Soft         | `3f94a50884e2ae4963092fead7d299127e97e5d5` | https://github.com/kcat/openal-soft                                   | LGPL-2.0+ |
| `dr_libs/`             | dr_libs             | `b55a0d9a30b91ad8901f89ecf05f76a33186c185` | https://github.com/mackron/dr_libs                                    | Public Domain / MIT-0 |
| `googletest/`          | GoogleTest          | `v1.17.0`                                 | https://github.com/google/googletest                                  | BSD-3-Clause |
| `googlebenchmark/`     | Google Benchmark    | `v1.9.1`                                  | https://github.com/google/benchmark                                   | Apache-2.0 |
| `doxygen-awesome-css/` | Doxygen Awesome CSS | `v2.4.1`                                  | https://github.com/jothepro/doxygen-awesome-css                       | MIT |

## Notes

- The vendored copies are stripped of their `.git` directories and
  `.gitmodules` files to keep the repository lean.
- Each dependency retains its own license file; refer to the individual
  `LICENSE`/`COPYING` files for the exact terms.
