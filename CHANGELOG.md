# Changelog

_**If you are upgrading:** please see [`UPGRADING.md`](UPGRADING.md)._

## [Unreleased][unreleased]

## [4.0.0] - 2019-06-08

### Changed

- Replace source with N-API binding and JS from [`leveldown`](https://github.com/Level/leveldown) ([`c6957d0`](https://github.com/level/rocksdb/commit/c6957d0)) ([#111](https://github.com/level/rocksdb/issues/111)) ([**@vweevers**](https://github.com/vweevers))
- Restore RocksDB includes and options ([`3843dc0`](https://github.com/level/rocksdb/commit/3843dc0)) ([#111](https://github.com/level/rocksdb/issues/111)) ([**@vweevers**](https://github.com/vweevers))
- Restore RocksDB test specifics ([`334af2c`](https://github.com/level/rocksdb/commit/334af2c)) ([#111](https://github.com/level/rocksdb/issues/111)) ([**@vweevers**](https://github.com/vweevers))
- Setup [`prebuildify`](https://github.com/prebuild/prebuildify) and Electron tests ([`69f5f66`](https://github.com/level/rocksdb/commit/69f5f66), [`ea6d0df`](https://github.com/level/rocksdb/commit/ea6d0df)) ([#111](https://github.com/level/rocksdb/issues/111)) ([**@vweevers**](https://github.com/vweevers))
- Disable info log by default and add `infoLogLevel` option ([#114](https://github.com/level/rocksdb/issues/114)) ([`002d836`](https://github.com/level/rocksdb/commit/002d836)) ([**@vweevers**](https://github.com/vweevers)) (this removed the need for [`53599da`](https://github.com/level/rocksdb/commit/53599da))
- Replace `async` devDependency with `async-each` ([#116](https://github.com/level/rocksdb/issues/116)) ([`5678c16`](https://github.com/level/rocksdb/commit/5678c16)) ([**@vweevers**](https://github.com/vweevers))
- Tweak `README.md` and package description ([#112](https://github.com/level/rocksdb/issues/112)) ([`a0f6ace`](https://github.com/level/rocksdb/commit/a0f6ace)) ([**@vweevers**](https://github.com/vweevers))
- Remove outdated `Getting Support` section from `README.md` ([`2c2ebc5`](https://github.com/level/rocksdb/commit/2c2ebc5)) ([**@vweevers**](https://github.com/vweevers))
- Upgrade `tempy` devDependency from `^0.2.1` to `^0.3.0` ([`66f16bd`](https://github.com/level/rocksdb/commit/66f16bd)) ([**@vweevers**](https://github.com/vweevers))
- Upgrade `nyc` devDependency from `^13.2.0` to `^14.0.0` ([#104](https://github.com/level/rocksdb/issues/104)) ([`03746d0`](https://github.com/level/rocksdb/commit/03746d0)) ([**@vweevers**](https://github.com/vweevers))

### Removed

- Drop node &lt; 8.6.0 ([`b294106`](https://github.com/level/rocksdb/commit/b294106)) ([#111](https://github.com/level/rocksdb/issues/111)) ([**@vweevers**](https://github.com/vweevers))
- Remove outdated `Dockerfile` and `.dntrc` ([`fab2d10`](https://github.com/level/rocksdb/commit/fab2d10)) ([**@vweevers**](https://github.com/vweevers))
- Remove benchmarks ([#77](https://github.com/level/rocksdb/issues/77)) ([**@vweevers**](https://github.com/vweevers)) (since moved to [`level-bench`](https://github.com/Level/bench))
- Remove 32 bits from AppVeyor ([#77](https://github.com/level/rocksdb/issues/77)) ([**@ralphtheninja**](https://github.com/ralphtheninja))

### Fixed

- Fix Level badge ([`84bc345`](https://github.com/level/rocksdb/commit/84bc345)) ([**@vweevers**](https://github.com/vweevers))

**Historical Note** Many commits between 3.1.0 and 4.0.0 are not listed here, because they became irrelevant once we rewrote `rocksdb` as an N-API addon by importing code from `leveldown` - essentially starting from scratch. This version of `rocksdb` includes all relevant changes and bugfixes of (up to and including) [`leveldown@5.1.0`](https://github.com/Level/leveldown/blob/master/CHANGELOG.md). Please refer to [`UPGRADING.md`](UPGRADING.md) for a complete description of breaking changes in the context of `rocksdb`.

## [3.1.0] - 2019-04-21

### Changed

- Upgrade `bindings` from `~1.3.0` to `~1.5.0` ([#95](https://github.com/level/rocksdb/issues/95)) ([**@vweevers**](https://github.com/vweevers))
- Upgrade `nan` from `~2.11.0` to `~2.13.2` ([#89](https://github.com/level/rocksdb/issues/89), [#97](https://github.com/level/rocksdb/issues/97)) ([**@vweevers**](https://github.com/vweevers))
- Upgrade `nyc` devDependency from `^12.0.2` to `^13.2.0` ([#92](https://github.com/level/rocksdb/issues/92)) ([**@vweevers**](https://github.com/vweevers))
- Apply common project tweaks ([#90](https://github.com/level/rocksdb/issues/90), [#91](https://github.com/level/rocksdb/issues/91)) ([**@vweevers**](https://github.com/vweevers))

### Added

- Add `readOnly` option ([#98](https://github.com/level/rocksdb/issues/98)) ([**@eugeneware**](https://github.com/eugeneware))

### Removed

- Remove `prebuild` script from `package.json` ([#102](https://github.com/level/rocksdb/issues/102)) ([**@vweevers**](https://github.com/vweevers))
- Remove link to dead website ([`2430b09`](https://github.com/level/rocksdb/commit/2430b09)) ([**@vweevers**](https://github.com/vweevers))

### Fixed

- Fix subtests by adding `t.plan()` ([#94](https://github.com/level/rocksdb/issues/94)) ([**@vweevers**](https://github.com/vweevers))
- Gitignore debug builds of dependencies ([#101](https://github.com/level/rocksdb/issues/101)) ([**@vweevers**](https://github.com/vweevers))
- Npmignore Windows builds, RocksDB docs, tools and more ([#101](https://github.com/level/rocksdb/issues/101)) ([**@vweevers**](https://github.com/vweevers))

## [3.0.3] - 2018-12-09

### Changed

- Upgrade `slump` devDependency from `~2.0.0` to `~3.0.0` ([#76](https://github.com/level/rocksdb/issues/76)) ([**@vweevers**](https://github.com/vweevers))

### Fixed

- Add `sys/sysmacros.h` for build on modern glibc ([#86](https://github.com/level/rocksdb/issues/86)) ([**@lachesis**](https://github.com/lachesis))

### Removed

- Remove unused `port-libuv` directory ([#81](https://github.com/level/rocksdb/issues/81)) ([**@filoozom**](https://github.com/filoozom))

## [3.0.2] - 2018-10-25

### Changed

- Upgrade `Snappy` to `1.1.7` ([**@filoozom**](https://github.com/filoozom))

## [3.0.1] - 2018-05-22

### Added

- Add upgrade guide ([**@ralphtheninja**](https://github.com/ralphtheninja))

### Changed

- Upgrade to `abstract-leveldown@~5.0.0` ([**@ralphtheninja**](https://github.com/ralphtheninja))

## [3.0.0] - 2018-05-21

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

## 1.0.0 - 2017-07-01

**Historical Note** Earlier versions were published before `v1.0.0` but the code was then a branch inside [`leveldown`](https://github.com/level/leveldown). This version marks the point where that code was extracted into its own repository thanks to the work of [`@mcollina`](https://github.com/mcollina).

[unreleased]: https://github.com/level/rocksdb/compare/v4.0.0...HEAD

[4.0.0]: https://github.com/level/rocksdb/compare/v3.1.0...v4.0.0

[3.1.0]: https://github.com/level/rocksdb/compare/v3.0.3...v3.1.0

[3.0.3]: https://github.com/level/rocksdb/compare/v3.0.2...v3.0.3

[3.0.2]: https://github.com/level/rocksdb/compare/v3.0.1...v3.0.2

[3.0.1]: https://github.com/level/rocksdb/compare/v3.0.0...v3.0.1

[3.0.0]: https://github.com/level/rocksdb/compare/v2.0.0...v3.0.0

[2.0.0]: https://github.com/level/rocksdb/compare/v1.1.0...v2.0.0

[1.1.0]: https://github.com/level/rocksdb/compare/v1.0.1...v1.1.0

[1.0.1]: https://github.com/level/rocksdb/compare/v1.0.0...v1.0.1
