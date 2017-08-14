rocksdb
=========

<img alt="LevelDB Logo" height="100" src="http://leveldb.org/img/logo.svg">

**A Low-level Node.js RocksDB binding**

[![Build Status](https://secure.travis-ci.org/Level/rocksdb.png)](http://travis-ci.org/Level/rocksdb)
[![AppVeyor build status](https://img.shields.io/appveyor/ci/Level/rocksdb.svg)](https://ci.appveyor.com/project/Level/rocksdb)
[![dependencies](https://david-dm.org/Level/rocksdb.svg)](https://david-dm.org/level/rocksdb)
[![Greenkeeper badge](https://badges.greenkeeper.io/Level/rocksdb.svg)](https://greenkeeper.io/)

[![NPM](https://nodei.co/npm/rocksdb.png?stars&downloads&downloadRank)](https://nodei.co/npm/rocksdb/) [![NPM](https://nodei.co/npm-dl/rocksdb.png?months=6&height=3)](https://nodei.co/npm/rocksdb/)

`rocksdb` is based on the [LevelDown](https://github.com/level/leveldown) code, which it was extracted from [LevelUP](https://github.com/level/levelup) and now serves as a stand-alone binding for LevelDB.

It is **strongly recommended** that you use LevelUP in preference to `rocksdb` unless you have measurable performance reasons to do so. LevelUP is optimised for usability and safety. Although we are working to improve the safety of the `rocksdb` interface it is still easy to crash your Node process if you don't do things in just the right way.

<a name="platforms"></a>
Tested & supported platforms
----------------------------

  * **Linux** (including ARM platforms such as Raspberry Pi *and Kindle!*)
  * **Mac OS**
  * **Solaris** (SmartOS & Nodejitsu)
  * **FreeBSD**
  * **Windows**
    * See installation instructions for *node-gyp* dependencies [here](https://github.com/TooTallNate/node-gyp#installation), you'll need these (free) components from Microsoft to compile and run any native Node add-on in Windows.

<a name="api"></a>
## API

`rocksdb` implements the same API of [LevelDown](https://github.com/level/leveldown#api).

<a name="support"></a>
Getting support
---------------

There are multiple ways you can find help in using LevelDB in Node.js:

 * **IRC:** you'll find an active group of LevelUP users in the **##leveldb** channel on Freenode, including most of the contributors to this project.
 * **Mailing list:** there is an active [Node.js LevelDB](https://groups.google.com/forum/#!forum/node-levelup) Google Group.
 * **GitHub:** you're welcome to open an issue here on this GitHub repository if you have a question.

<a name="contributing"></a>
Contributing
------------

rocksdb is an **OPEN Open Source Project**. This means that:

> Individuals making significant and valuable contributions are given commit-access to the project to contribute as they see fit. This project is more like an open wiki than a standard guarded open source project.

See the [contribution guide](https://github.com/Level/community/blob/master/CONTRIBUTING.md) for more details.

### Windows

A large portion of the Windows support comes from code by [Krzysztof Kowalczyk](http://blog.kowalczyk.info/) [@kjk](https://twitter.com/kjk), see his Windows LevelDB port [here](http://code.google.com/r/kkowalczyk-leveldb/). If you're using LevelUP on Windows, you should give him your thanks!

Prebuilt binaries
-----------------

`rocksdb` uses `prebuild` and `prebuild-install` for handling prebuilt binaries. See [this list](https://github.com/Level/rocksdb/releases) of supported prebuilt platform binaries. When installing rocksdb `prebuild-install` will install prebuilt binaries from GitHub if they exist and fallback to a compile step if they don't.

If you are working on `rocksdb` and want to re-compile the C++ code it's enough to do `npm install`.

If you don't want to use the `prebuild` for the platform you are installing on, specify the `--build-from-source` flag when you install.

<a name="license"></a>
License &amp; copyright
-------------------

Copyright &copy; 2012-2017 **LevelDown** [contributors](https://github.com/level/community#contributors).

**rocksdb** is licensed under the MIT license. All rights not explicitly granted in the MIT license are reserved. See the included `LICENSE.md` file for more details.

*LevelDOWN builds on the excellent work of the LevelDB and Snappy teams from Google and additional contributors. LevelDB and Snappy are both issued under the [New BSD Licence](http://opensource.org/licenses/BSD-3-Clause).*
