# Changelog

## [5.2.1] - 2022-03-25

### Fixed

- Fix `getMany()` memory leak ([#193](https://github.com/Level/rocksdb/issues/193)) ([`680f94b`](https://github.com/Level/rocksdb/commit/680f94b)) (Vincent Weevers).

## [5.2.0] - 2021-11-27

### Changed

- Refactor: add Entry struct to abstract away key-value pairs ([`f9f99ec`](https://github.com/Level/rocksdb/commit/f9f99ec)) (Meirion Hughes, Vincent Weevers)
- Refactor: avoid storing `napi_env` ([`efb5721`](https://github.com/Level/rocksdb/commit/efb5721)) (Meirion Hughes, Vincent Weevers)
- Refactor: move CheckEndCallback to Iterator ([`caa28a5`](https://github.com/Level/rocksdb/commit/caa28a5)) (Meirion Hughes, Vincent Weevers)

### Added

- Add `db.getMany(keys)` ([`e6ae598`](https://github.com/Level/rocksdb/commit/e6ae598)) (Meirion Hughes, Vincent Weevers)

### Fixed

- Optimize `db.iterator()` ([`9f9b13c`](https://github.com/Level/rocksdb/commit/9f9b13c)) (Meirion Hughes, Vincent Weevers)
- Cleanup hanging iterator also when `next()` errored ([`b67bfe7`](https://github.com/Level/rocksdb/commit/b67bfe7)) (Meirion Hughes, Vincent Weevers)
- Prevent GC of db during `clear()` and other operations ([`b9878e8`](https://github.com/Level/rocksdb/commit/b9878e8)) (Meirion Hughes, Vincent Weevers)
- Make `db.clear()` 27x faster by doing it natively ([`32e9b5d`](https://github.com/Level/rocksdb/commit/32e9b5d)) (Meirion Hughes, Vincent Weevers)
- Close database on environment exit ([`54fc5df`](https://github.com/Level/rocksdb/commit/54fc5df)) (Meirion Hughes, Vincent Weevers).

## [5.1.1] - 2021-09-28

### Fixed

- Build a universal binary to support M1 (Apple silicon) ([#181](https://github.com/Level/rocksdb/issues/181)) ([`0bda9ba`](https://github.com/Level/rocksdb/commit/0bda9ba)) (Juan Gonzalez).

## [5.1.0] - 2021-08-28

### Added

- Add prebuilt binary for Alpine ([#174](https://github.com/Level/rocksdb/issues/174)) ([`185951d`](https://github.com/Level/rocksdb/commit/185951d)) (Vincent Weevers)

### Fixed

- Support `approximateSize()` on db bigger than 4 GB ([#175](https://github.com/Level/rocksdb/issues/175)) ([`891bb7a`](https://github.com/Level/rocksdb/commit/891bb7a)) (Lars Kuhtz)
- Remove `march=native` flag for Apple silicon compatibility ([#171](https://github.com/Level/rocksdb/issues/171)) ([`f945be6`](https://github.com/Level/rocksdb/commit/f945be6)) (Juan Gonzalez)

## [5.0.0] - 2021-04-17

_If you are upgrading: please see [`UPGRADING.md`](UPGRADING.md)._

### Changed

- **Breaking:** bump `abstract-leveldown` ([`e6b9182`](https://github.com/Level/rocksdb/commit/e6b9182), [`271894f`](https://github.com/Level/rocksdb/commit/271894f)) (Vincent Weevers)
- **Breaking:** upgrade to RocksDB 6.17.3 ([`060d182`](https://github.com/Level/rocksdb/commit/060d182)) (Denis Yaremov)
- Move RocksDB to git submodule ([`1b6ea11`](https://github.com/Level/rocksdb/commit/1b6ea11), [`28b37fa`](https://github.com/Level/rocksdb/commit/28b37fa)) (Philippe Schommers)
- Replace Ubuntu 16.04 with CentOS 7 for prebuilds ([#153](https://github.com/Level/rocksdb/issues/153)) ([`6b2ebb7`](https://github.com/Level/rocksdb/commit/6b2ebb7)) (Vincent Weevers). This makes the prebuilt binary for linux compatible with Debian 8, Ubuntu 14.04, RHEL 7, CentOS 7 and other flavors with an old glibc.
- Bump `node-gyp` from 5.x to 7.x ([`2d20d18`](https://github.com/Level/rocksdb/commit/2d20d18), [`9d36809`](https://github.com/Level/rocksdb/commit/9d36809)) (Vincent Weevers)
- Bump `node-gyp-build` and unlock `napi-macros` ([`4c45b5f`](https://github.com/Level/rocksdb/commit/4c45b5f)) (Vincent Weevers)
- Skip stack exhaustion test ([`69e3dcb`](https://github.com/Level/rocksdb/commit/69e3dcb)) (Vincent Weevers)
- Refactor initial seek ([`949afd2`](https://github.com/Level/rocksdb/commit/949afd2)) (Vincent Weevers)
- Make iterator seek target a local variable ([`9b08726`](https://github.com/Level/rocksdb/commit/9b08726)) (Vincent Weevers)
- Refactor initialization of range options ([`99918c5`](https://github.com/Level/rocksdb/commit/99918c5)) (Vincent Weevers)

### Added

- Add manifest ([Level/community#83](https://github.com/Level/community/issues/83)) ([`5eee577`](https://github.com/Level/rocksdb/commit/5eee577)) (Vincent Weevers)
- Test that empty range options are ignored ([`4888b97`](https://github.com/Level/rocksdb/commit/4888b97)) (Vincent Weevers)

### Removed

- **Breaking:** drop node 8 ([Level/community#98](https://github.com/Level/community/issues/98)) ([`05aefaa`](https://github.com/Level/rocksdb/commit/05aefaa), [`fd69183`](https://github.com/Level/rocksdb/commit/fd69183)) (Vincent Weevers)
- Remove default export ([Level/community#87](https://github.com/Level/community/issues/87)) ([`43c1544`](https://github.com/Level/rocksdb/commit/43c1544)) (Vincent Weevers)

### Fixed

- Hide symbols on mac with `-fvisibility=hidden` ([#150](https://github.com/Level/rocksdb/issues/150)) ([`e2e09c9`](https://github.com/Level/rocksdb/commit/e2e09c9)) (Vincent Weevers)
- Close db in `stack-blower` test ([`1925392`](https://github.com/Level/rocksdb/commit/1925392)) (Vincent Weevers)
- Fix `test-gc` script ([`2c41d3b`](https://github.com/Level/rocksdb/commit/2c41d3b)) (Vincent Weevers)

## [4.1.0] - 2019-09-20

### Added

- Support clear() ([Level/community#79](https://github.com/Level/community/issues/79)) ([`b9d58fb`](https://github.com/Level/rocksdb/commit/b9d58fb)) ([**@vweevers**](https://github.com/vweevers))

## [4.0.1] - 2019-09-07

### Changed

- Remove `fast-future` in favor of native cache limit ([#133](https://github.com/Level/rocksdb/issues/133)) ([**@vweevers**](https://github.com/vweevers))
- Upgrade `napi-macros` from `~1.8.1` to `~2.0.0` ([#132](https://github.com/Level/rocksdb/issues/132)) ([**@vweevers**](https://github.com/vweevers))
- Upgrade `hallmark` devDependency from `^0.1.0` to `^2.0.0` ([#127](https://github.com/Level/rocksdb/issues/127), [#138](https://github.com/Level/rocksdb/issues/138)) ([**@vweevers**](https://github.com/vweevers))
- Upgrade `standard` devDependency from `^12.0.0` to `^14.0.0` ([#126](https://github.com/Level/rocksdb/issues/126), [#137](https://github.com/Level/rocksdb/issues/137)) ([**@vweevers**](https://github.com/vweevers))
- Upgrade `rimraf` devDependency from `^2.6.1` to `^3.0.0` ([#135](https://github.com/Level/rocksdb/issues/135)) ([**@vweevers**](https://github.com/vweevers))
- Upgrade `electron` devDependency from `^5.0.1` to `^6.0.0` ([#130](https://github.com/Level/rocksdb/issues/130)) ([**@vweevers**](https://github.com/vweevers))
- Upgrade `delayed` devDependency from `^1.0.1` to `^2.0.0` ([#124](https://github.com/Level/rocksdb/issues/124)) ([**@vweevers**](https://github.com/vweevers))
- Upgrade `readfiletree` devDependency from `~0.0.1` to `^1.0.0` ([#122](https://github.com/Level/rocksdb/issues/122)) ([**@vweevers**](https://github.com/vweevers))
- Upgrade `du` devDependency from `~0.1.0` to `^1.0.0` ([#123](https://github.com/Level/rocksdb/issues/123)) ([**@vweevers**](https://github.com/vweevers))
- Upgrade `mkfiletree` devDependency from `^1.0.1` to `^2.0.0` ([#121](https://github.com/Level/rocksdb/issues/121)) ([**@vweevers**](https://github.com/vweevers))
- Upgrade `node-gyp` devDependency from `^4.0.0` to `^5.0.0` ([#119](https://github.com/Level/rocksdb/issues/119)) ([**@vweevers**](https://github.com/vweevers))

### Fixed

- Fix batch compression test to actually compress ([#134](https://github.com/Level/rocksdb/issues/134)) ([**@vweevers**](https://github.com/vweevers))

## [4.0.0] - 2019-06-08

_Many commits between 3.1.0 and 4.0.0 are not listed here, because they became irrelevant once we rewrote `rocksdb` as an N-API addon by importing code from `leveldown` - essentially starting from scratch. This version of `rocksdb` includes all relevant changes and bugfixes of (up to and including) [`leveldown@5.1.0`](https://github.com/Level/leveldown/blob/master/CHANGELOG.md). Please refer to [`UPGRADING.md`](UPGRADING.md) for a complete description of breaking changes in the context of `rocksdb`._

### Changed

- Replace source with N-API binding and JS from [`leveldown`](https://github.com/Level/leveldown) ([`c6957d0`](https://github.com/Level/rocksdb/commit/c6957d0)) ([#111](https://github.com/Level/rocksdb/issues/111)) ([**@vweevers**](https://github.com/vweevers))
- Restore RocksDB includes and options ([`3843dc0`](https://github.com/Level/rocksdb/commit/3843dc0)) ([#111](https://github.com/Level/rocksdb/issues/111)) ([**@vweevers**](https://github.com/vweevers))
- Restore RocksDB test specifics ([`334af2c`](https://github.com/Level/rocksdb/commit/334af2c)) ([#111](https://github.com/Level/rocksdb/issues/111)) ([**@vweevers**](https://github.com/vweevers))
- Setup [`prebuildify`](https://github.com/prebuild/prebuildify) and Electron tests ([`69f5f66`](https://github.com/Level/rocksdb/commit/69f5f66), [`ea6d0df`](https://github.com/Level/rocksdb/commit/ea6d0df)) ([#111](https://github.com/Level/rocksdb/issues/111)) ([**@vweevers**](https://github.com/vweevers))
- Disable info log by default and add `infoLogLevel` option ([#114](https://github.com/Level/rocksdb/issues/114)) ([`002d836`](https://github.com/Level/rocksdb/commit/002d836)) ([**@vweevers**](https://github.com/vweevers)) (this removed the need for [`53599da`](https://github.com/Level/rocksdb/commit/53599da))
- Replace `async` devDependency with `async-each` ([#116](https://github.com/Level/rocksdb/issues/116)) ([`5678c16`](https://github.com/Level/rocksdb/commit/5678c16)) ([**@vweevers**](https://github.com/vweevers))
- Tweak `README.md` and package description ([#112](https://github.com/Level/rocksdb/issues/112)) ([`a0f6ace`](https://github.com/Level/rocksdb/commit/a0f6ace)) ([**@vweevers**](https://github.com/vweevers))
- Remove outdated `Getting Support` section from `README.md` ([`2c2ebc5`](https://github.com/Level/rocksdb/commit/2c2ebc5)) ([**@vweevers**](https://github.com/vweevers))
- Upgrade `tempy` devDependency from `^0.2.1` to `^0.3.0` ([`66f16bd`](https://github.com/Level/rocksdb/commit/66f16bd)) ([**@vweevers**](https://github.com/vweevers))
- Upgrade `nyc` devDependency from `^13.2.0` to `^14.0.0` ([#104](https://github.com/Level/rocksdb/issues/104)) ([`03746d0`](https://github.com/Level/rocksdb/commit/03746d0)) ([**@vweevers**](https://github.com/vweevers))

### Removed

- Drop node < 8.6.0 ([`b294106`](https://github.com/Level/rocksdb/commit/b294106)) ([#111](https://github.com/Level/rocksdb/issues/111)) ([**@vweevers**](https://github.com/vweevers))
- Remove outdated `Dockerfile` and `.dntrc` ([`fab2d10`](https://github.com/Level/rocksdb/commit/fab2d10)) ([**@vweevers**](https://github.com/vweevers))
- Remove benchmarks ([#77](https://github.com/Level/rocksdb/issues/77)) ([**@vweevers**](https://github.com/vweevers)) (since moved to [`level-bench`](https://github.com/Level/bench))
- Remove 32 bits from AppVeyor ([#77](https://github.com/Level/rocksdb/issues/77)) ([**@ralphtheninja**](https://github.com/ralphtheninja))

### Fixed

- Fix Level badge ([`84bc345`](https://github.com/Level/rocksdb/commit/84bc345)) ([**@vweevers**](https://github.com/vweevers))

## [3.1.0] - 2019-04-21

### Changed

- Upgrade `bindings` from `~1.3.0` to `~1.5.0` ([#95](https://github.com/Level/rocksdb/issues/95)) ([**@vweevers**](https://github.com/vweevers))
- Upgrade `nan` from `~2.11.0` to `~2.13.2` ([#89](https://github.com/Level/rocksdb/issues/89), [#97](https://github.com/Level/rocksdb/issues/97)) ([**@vweevers**](https://github.com/vweevers))
- Upgrade `nyc` devDependency from `^12.0.2` to `^13.2.0` ([#92](https://github.com/Level/rocksdb/issues/92)) ([**@vweevers**](https://github.com/vweevers))
- Apply common project tweaks ([#90](https://github.com/Level/rocksdb/issues/90), [#91](https://github.com/Level/rocksdb/issues/91)) ([**@vweevers**](https://github.com/vweevers))

### Added

- Add `readOnly` option ([#98](https://github.com/Level/rocksdb/issues/98)) ([**@eugeneware**](https://github.com/eugeneware))

### Removed

- Remove `prebuild` script from `package.json` ([#102](https://github.com/Level/rocksdb/issues/102)) ([**@vweevers**](https://github.com/vweevers))
- Remove link to dead website ([`2430b09`](https://github.com/Level/rocksdb/commit/2430b09)) ([**@vweevers**](https://github.com/vweevers))

### Fixed

- Fix subtests by adding `t.plan()` ([#94](https://github.com/Level/rocksdb/issues/94)) ([**@vweevers**](https://github.com/vweevers))
- Gitignore debug builds of dependencies ([#101](https://github.com/Level/rocksdb/issues/101)) ([**@vweevers**](https://github.com/vweevers))
- Npmignore Windows builds, RocksDB docs, tools and more ([#101](https://github.com/Level/rocksdb/issues/101)) ([**@vweevers**](https://github.com/vweevers))

## [3.0.3] - 2018-12-09

### Changed

- Upgrade `slump` devDependency from `~2.0.0` to `~3.0.0` ([#76](https://github.com/Level/rocksdb/issues/76)) ([**@vweevers**](https://github.com/vweevers))

### Fixed

- Add `sys/sysmacros.h` for build on modern glibc ([#86](https://github.com/Level/rocksdb/issues/86)) ([**@lachesis**](https://github.com/lachesis))

### Removed

- Remove unused `port-libuv` directory ([#81](https://github.com/Level/rocksdb/issues/81)) ([**@filoozom**](https://github.com/filoozom))

## [3.0.2] - 2018-10-25

### Changed

- Upgrade `Snappy` to `1.1.7` ([**@filoozom**](https://github.com/filoozom))

## [3.0.1] - 2018-05-22

### Added

- Add upgrade guide ([**@ralphtheninja**](https://github.com/ralphtheninja))

### Changed

- Upgrade to `abstract-leveldown@~5.0.0` ([**@ralphtheninja**](https://github.com/ralphtheninja))

## [3.0.0] - 2018-05-21

_If you are upgrading: please see [`UPGRADING.md`](UPGRADING.md)._

### Added

- Add node 10 to Travis and AppVeyor ([**@ralphtheninja**](https://github.com/ralphtheninja))
- Add default export ([**@meirionhughes**](https://github.com/meirionhughes))
- Add `standard` ([**@ralphtheninja**](https://github.com/ralphtheninja))

### Changed

- Upgrade to `nan@2.10.0` ([**@ralphtheninja**](https://github.com/ralphtheninja))
- Upgrade to `prebuild-install@4.0.0` ([**@ralphtheninja**](https://github.com/ralphtheninja))
- Upgrade to `verify-travis-appveyor@3.0.0` ([**@ralphtheninja**](https://github.com/ralphtheninja))
- Replace deprecated `node-uuid` with `uuid` ([**@ralphtheninja**](https://github.com/ralphtheninja))

### Fixed

- Fix nan deprecation warnings ([**@ralphtheninja**](https://github.com/ralphtheninja))

### Removed

- Remove node 4 from Travis and AppVeyor ([**@ralphtheninja**](https://github.com/ralphtheninja))
- Remove TypeScript typings ([**@meirionhughes**](https://github.com/meirionhughes), [**@ralphtheninja**](https://github.com/ralphtheninja))

## [2.0.0] - 2018-02-12

### Added

- Add `verify-travis-appveyor` to tests ([**@ralphtheninja**](https://github.com/ralphtheninja))
- Add node 9 to Travis and AppVeyor ([**@ralphtheninja**](https://github.com/ralphtheninja))

### Changed

- Upgrade to `abstract-leveldown@3.0.0` ([**@ralphtheninja**](https://github.com/ralphtheninja))
- Tweak badges in README ([**@vweevers**](https://github.com/vweevers))
- Simplify AppVeyor configuration ([**@vweevers**](https://github.com/vweevers))
- Upgrade to `nan@2.8.0` ([**@ralphtheninja**](https://github.com/ralphtheninja))
- Upgrade to `prebuild@7.0.0` ([**@ralphtheninja**](https://github.com/ralphtheninja))
- Upgrade to `abstract-leveldown@4.0.0` ([**@ralphtheninja**](https://github.com/ralphtheninja))

### Fixed

- Fix destroy on Windows ([**@vweevers**](https://github.com/vweevers))

### Removed

- Remove node 7 from Travis and AppVeyor ([**@ralphtheninja**](https://github.com/ralphtheninja))

## [1.1.0] - 2017-09-16

### Added

- Add TypeScript typings ([**@meirionhughes**](https://github.com/meirionhughes))

### Changed

- Upgrade to `nan@2.7.0` ([**@ralphtheninja**](https://github.com/ralphtheninja))
- Upgrade to `abstract-leveldown@2.7.0` ([**@ralphtheninja**](https://github.com/ralphtheninja))

## [1.0.1] - 2017-08-27

### Added

- Add Greenkeeper badge ([**@ralphtheninja**](https://github.com/ralphtheninja))

### Changed

- Update dependencies ([**@ralphtheninja**](https://github.com/ralphtheninja))

## [1.0.0] - 2017-07-01

_Earlier versions were published before `v1.0.0` but the code was then a branch inside [`leveldown`](https://github.com/Level/leveldown). This version marks the point where that code was extracted into its own repository thanks to the work of [`@mcollina`](https://github.com/mcollina)._

[5.2.1]: https://github.com/Level/rocksdb/releases/tag/v5.2.1

[5.2.0]: https://github.com/Level/rocksdb/releases/tag/v5.2.0

[5.1.1]: https://github.com/Level/rocksdb/compare/v5.1.0...v5.1.1

[5.1.0]: https://github.com/Level/rocksdb/releases/tag/v5.1.0

[5.0.0]: https://github.com/Level/rocksdb/releases/tag/v5.0.0

[4.1.0]: https://github.com/Level/rocksdb/releases/tag/v4.1.0

[4.0.1]: https://github.com/Level/rocksdb/releases/tag/v4.0.1

[4.0.0]: https://github.com/Level/rocksdb/releases/tag/v4.0.0

[3.1.0]: https://github.com/Level/rocksdb/releases/tag/v3.1.0

[3.0.3]: https://github.com/Level/rocksdb/releases/tag/v3.0.3

[3.0.2]: https://github.com/Level/rocksdb/releases/tag/v3.0.2

[3.0.1]: https://github.com/Level/rocksdb/releases/tag/v3.0.1

[3.0.0]: https://github.com/Level/rocksdb/releases/tag/v3.0.0

[2.0.0]: https://github.com/Level/rocksdb/releases/tag/v2.0.0

[1.1.0]: https://github.com/Level/rocksdb/releases/tag/v1.1.0

[1.0.1]: https://github.com/Level/rocksdb/releases/tag/v1.0.1

[1.0.0]: https://github.com/Level/rocksdb/releases/tag/v1.0.0
