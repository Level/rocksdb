# rocksdb

> A low-level Node.js RocksDB binding. An [`abstract-leveldown`](https://github.com/Level/abstract-leveldown) compliant store.

[![level badge][level-badge]](https://github.com/Level/awesome)
[![npm](https://img.shields.io/npm/v/rocksdb.svg?label=&logo=npm)](https://www.npmjs.com/package/rocksdb)
[![Node version](https://img.shields.io/node/v/rocksdb.svg)](https://www.npmjs.com/package/rocksdb)
[![Travis](https://img.shields.io/travis/Level/rocksdb.svg?logo=travis&label=)](https://travis-ci.org/Level/rocksdb)
[![AppVeyor](https://img.shields.io/appveyor/ci/Level/rocksdb.svg?logo=appveyor&label=)](https://ci.appveyor.com/project/Level/rocksdb)
[![npm downloads](https://img.shields.io/npm/dm/rocksdb.svg?label=dl)](https://www.npmjs.com/package/rocksdb)
[![Coverage Status](https://coveralls.io/repos/github/Level/rocksdb/badge.svg)](https://coveralls.io/github/Level/rocksdb)
[![JavaScript Style Guide](https://img.shields.io/badge/code_style-standard-brightgreen.svg)](https://standardjs.com)
[![Backers on Open Collective](https://opencollective.com/level/backers/badge.svg?color=orange)](#backers)
[![Sponsors on Open Collective](https://opencollective.com/level/sponsors/badge.svg?color=orange)](#sponsors)

## Table of Contents

<details><summary>Click to expand</summary>

- [Introduction](#introduction)
- [Supported Platforms](#supported-platforms)
- [API](#api)
- [Contributing](#contributing)
- [Donate](#donate)
- [License](#license)

</details>

## Introduction

This module closely follows [`leveldown`](https://github.com/Level/leveldown) and implements the same API. The difference is that `leveldown` is a binding for [LevelDB](https://github.com/google/leveldb) while `rocksdb` is a binding for [RocksDB, Facebook's fork of LevelDB](https://github.com/facebook/rocksdb).

It is **strongly recommended** that you use `levelup` in preference to `rocksdb` unless you have measurable performance reasons to do so. `levelup` is optimized for usability and safety. Although we are working to improve the safety of the `rocksdb` interface it is still easy to crash your Node process if you don't do things in just the right way.

**If you are upgrading:** please see [UPGRADING.md](UPGRADING.md).

## Supported Platforms

We aim to support _at least_ Active LTS and Current Node.js releases, Electron 4.0.0, as well as any future Node.js and Electron releases thanks to [N-API](https://nodejs.org/api/n-api.html). Because N-API has an experimental status in node 6 and early 8.x releases, the minimum node version for `rocksdb` is `8.6.0`.

The `rocksdb` npm package ships with prebuilt binaries for popular 64-bit platforms and is known to work on:

- **Linux** (including ARM platforms such as Raspberry Pi and Kindle)
- **Mac OS**
- **Solaris** (SmartOS & Nodejitsu)
- **FreeBSD**
- **Windows**

When installing `rocksdb`, [`node-gyp-build`](https://github.com/prebuild/node-gyp-build) will check if a compatible binary exists and fallback to a compile step if it doesn't. In that case you'll need a [valid `node-gyp` installation](https://github.com/nodejs/node-gyp#installation).

If you don't want to use the prebuilt binary for the platform you are installing on, specify the `--build-from-source` flag when you install. If you are working on `rocksdb` itself and want to re-compile the C++ code it's enough to do `npm install`.

## API

Please refer to [`leveldown`](https://github.com/Level/leveldown#api) for API documentation. The `db.open(options, callback)` method of `rocksdb` has a few additional options:

- `readOnly` (boolean, default `false`): open database in read-only mode.
- `infoLogLevel` (string, default `null`): verbosity of info log. One of `'debug'`, `'info'`, `'warn'`, `'error'`, `'fatal'`, `'header'` or `null` (disable).

## Contributing

[`Level/rocksdb`](https://github.com/Level/rocksdb) is an **OPEN Open Source Project**. This means that:

> Individuals making significant and valuable contributions are given commit-access to the project to contribute as they see fit. This project is more like an open wiki than a standard guarded open source project.

See the [Contribution Guide](https://github.com/Level/community/blob/master/CONTRIBUTING.md) for more details.

### Publishing

1. Increment the version: `npm version ..`
2. Push to GitHub: `git push --follow-tags`
3. Wait for Travis and AppVeyor builds to complete
4. Download prebuilds into `./prebuilds`: `npm run download-prebuilds`
5. Optionally verify loading a prebuild: `npm run test-prebuild`
6. Optionally verify which files npm will include: `canadian-pub`
7. Add changelog to the GitHub release
8. Finally: `npm publish`

## Donate

To sustain [`Level`](https://github.com/Level) and its activities, become a backer or sponsor on [Open Collective](https://opencollective.com/level). Your logo or avatar will be displayed on our 28+ [GitHub repositories](https://github.com/Level) and [npm](https://www.npmjs.com/) packages. 💖

### Backers

[![Open Collective backers](https://opencollective.com/level/backers.svg?width=890)](https://opencollective.com/level)

### Sponsors

[![Open Collective sponsors](https://opencollective.com/level/sponsors.svg?width=890)](https://opencollective.com/level)

## License

[MIT](LICENSE.md) © 2012-present Rod Vagg and [Contributors](CONTRIBUTORS.md).

_`rocksdb` builds on the excellent work of the LevelDB and Snappy teams from Google and additional contributors to the LevelDB fork by Facebook. LevelDB and Snappy are both issued under the [New BSD License](http://opensource.org/licenses/BSD-3-Clause). A large portion of `rocksdb` Windows support comes from the [Windows LevelDB port](http://code.google.com/r/kkowalczyk-leveldb/) (archived) by [Krzysztof Kowalczyk](http://blog.kowalczyk.info/) ([`@kjk`](https://twitter.com/kjk)). If you're using `rocksdb` on Windows, you should give him your thanks!_

[level-badge]: https://leveljs.org/img/badge.svg
