# Changelog

## [Unreleased]

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

[Unreleased]: https://github.com/level/rocksdb/compare/v3.0.3...HEAD

[3.0.3]: https://github.com/level/rocksdb/compare/v3.0.2...v3.0.3

[3.0.2]: https://github.com/level/rocksdb/compare/v3.0.1...v3.0.2

[3.0.1]: https://github.com/level/rocksdb/compare/v3.0.0...v3.0.1

[3.0.0]: https://github.com/level/rocksdb/compare/v2.0.0...v3.0.0

[2.0.0]: https://github.com/level/rocksdb/compare/v1.1.0...v2.0.0

[1.1.0]: https://github.com/level/rocksdb/compare/v1.0.1...v1.1.0

[1.0.1]: https://github.com/level/rocksdb/compare/v1.0.0...v1.0.1
