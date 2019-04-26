# rocksdb

> A Low-level Node.js RocksDB binding

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

**If you are upgrading:** please see [UPGRADING.md](UPGRADING.md).

`rocksdb` is based on the [LevelDown](https://github.com/Level/leveldown) code, which was extracted from [LevelUP](https://github.com/Level/levelup) and now serves as a stand-alone binding for LevelDB. The native code in `rocksdb` is based on [Facebooks fork of LevelDB](https://github.com/facebook/rocksdb).

It is **strongly recommended** that you use LevelUP in preference to `rocksdb` unless you have measurable performance reasons to do so. LevelUP is optimised for usability and safety. Although we are working to improve the safety of the `rocksdb` interface it is still easy to crash your Node process if you don't do things in just the right way.

<a name="platforms"></a>
## Supported Platforms

  * **Linux** (including ARM platforms such as Raspberry Pi *and Kindle!*)
  * **Mac OS**
  * **Solaris** (SmartOS & Nodejitsu)
  * **FreeBSD**
  * **Windows**
    * See installation instructions for *node-gyp* dependencies [here](https://github.com/TooTallNate/node-gyp#installation), you'll need these (free) components from Microsoft to compile and run any native Node add-on in Windows.

<a name="api"></a>
## API

`rocksdb` implements the same API of [LevelDown](https://github.com/Level/leveldown#api).

<a name="support"></a>
## Getting Support

There are multiple ways you can find help in using LevelDB in Node.js:

 * **IRC:** you'll find an active group of LevelUP users in the **##leveldb** channel on Freenode, including most of the contributors to this project.
 * **Mailing list:** there is an active [Node.js LevelDB](https://groups.google.com/forum/#!forum/node-levelup) Google Group.
 * **GitHub:** you're welcome to open an issue here on this GitHub repository if you have a question.

## Contributing

[`Level/rocksdb`](https://github.com/Level/rocksdb) is an **OPEN Open Source Project**. This means that:

> Individuals making significant and valuable contributions are given commit-access to the project to contribute as they see fit. This project is more like an open wiki than a standard guarded open source project.

See the [Contribution Guide](https://github.com/Level/community/blob/master/CONTRIBUTING.md) for more details.

## Prebuilt Binaries

`rocksdb` uses `prebuild` and `prebuild-install` for handling prebuilt binaries. See [this list](https://github.com/Level/rocksdb/releases) of supported prebuilt platform binaries. When installing rocksdb `prebuild-install` will install prebuilt binaries from GitHub if they exist and fallback to a compile step if they don't.

If you are working on `rocksdb` and want to re-compile the C++ code it's enough to do `npm install`.

If you don't want to use the `prebuild` for the platform you are installing on, specify the `--build-from-source` flag when you install.

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
