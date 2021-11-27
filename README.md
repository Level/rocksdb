# rocksdb

> A low-level Node.js RocksDB binding. An [`abstract-leveldown`](https://github.com/Level/abstract-leveldown) compliant store.

[![level badge][level-badge]](https://github.com/Level/awesome)
[![npm](https://img.shields.io/npm/v/rocksdb.svg)](https://www.npmjs.com/package/rocksdb)
[![Node version](https://img.shields.io/node/v/rocksdb.svg)](https://www.npmjs.com/package/rocksdb)
[![Test](https://img.shields.io/github/workflow/status/Level/rocksdb/Test?label=test)](https://github.com/Level/rocksdb/actions/workflows/test.yml)
[![Coverage](https://img.shields.io/codecov/c/github/Level/rocksdb?label=\&logo=codecov\&logoColor=fff)](https://codecov.io/gh/Level/rocksdb)
[![Standard](https://img.shields.io/badge/standard-informational?logo=javascript\&logoColor=fff)](https://standardjs.com)
[![Common Changelog](https://common-changelog.org/badge.svg)](https://common-changelog.org)
[![Donate](https://img.shields.io/badge/donate-orange?logo=open-collective\&logoColor=fff)](https://opencollective.com/level)

## Table of Contents

<details><summary>Click to expand</summary>

- [Introduction](#introduction)
- [Supported Platforms](#supported-platforms)
- [API](#api)
- [Contributing](#contributing)
  - [Git Submodules](#git-submodules)
  - [Publishing](#publishing)
- [Donate](#donate)
- [License](#license)

</details>

## Introduction

This module closely follows [`leveldown`](https://github.com/Level/leveldown) and implements the same API. The difference is that `leveldown` is a binding for [LevelDB](https://github.com/google/leveldb) while `rocksdb` is a binding for [RocksDB, Facebook's fork of LevelDB](https://github.com/facebook/rocksdb).

It is **strongly recommended** that you use `levelup` in preference to `rocksdb` unless you have measurable performance reasons to do so. `levelup` is optimized for usability and safety. Although we are working to improve the safety of the `rocksdb` interface it is still easy to crash your Node process if you don't do things in just the right way.

**If you are upgrading:** please see [UPGRADING.md](UPGRADING.md).

## Supported Platforms

We aim to support _at least_ Active LTS and Current Node.js releases, Electron 5.0.0, as well as any future Node.js and Electron releases thanks to [N-API](https://nodejs.org/api/n-api.html). The minimum node version for `rocksdb` is `10.12.0`.

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

### Git Submodules

This project uses Git Submodules. This means that you should clone it recursively if you're planning on working on it:

```bash
$ git clone --recurse-submodules https://github.com/Level/rocksdb.git
```

Alternatively, you can initialize submodules after cloning:

```bash
$ git submodule update --init --recursive
```

### Publishing

1. Increment the version: `npm version ..`
2. Push to GitHub: `git push --follow-tags`
3. Wait for CI to complete
4. Download prebuilds into `./prebuilds`: `npm run download-prebuilds`
5. Optionally verify loading a prebuild: `npm run test-prebuild`
6. Optionally verify which files npm will include: `canadian-pub`
7. Finally: `npm publish`

## Donate

Support us with a monthly donation on [Open Collective](https://opencollective.com/level) and help us continue our work.

## License

[MIT](LICENSE)

_`rocksdb` builds on the excellent work of the LevelDB and Snappy teams from Google and additional contributors to the LevelDB fork by Facebook. LevelDB and Snappy are both issued under the [New BSD License](http://opensource.org/licenses/BSD-3-Clause). A large portion of `rocksdb` Windows support comes from the [Windows LevelDB port](http://code.google.com/r/kkowalczyk-leveldb/) (archived) by [Krzysztof Kowalczyk](http://blog.kowalczyk.info/) ([`@kjk`](https://twitter.com/kjk)). If you're using `rocksdb` on Windows, you should give him your thanks!_

[level-badge]: https://leveljs.org/img/badge.svg
