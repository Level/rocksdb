const util = require('util')
const AbstractLevelDOWN = require('abstract-leveldown').AbstractLevelDOWN
const binding = require('./binding')
const ChainedBatch = require('./chained-batch')
const Iterator = require('./iterator')
const fs = require('fs')

function LevelDOWN (location) {
  if (!(this instanceof LevelDOWN)) {
    return new LevelDOWN(location)
  }

  if (typeof location !== 'string') {
    throw new Error('constructor requires a location string argument')
  }

  AbstractLevelDOWN.call(this)

  this.location = location
  this.context = binding.db_init()
}

util.inherits(LevelDOWN, AbstractLevelDOWN)

LevelDOWN.prototype._open = function (options, callback) {
  binding.db_open(this.context, this.location, options, callback)
}

LevelDOWN.prototype._close = function (callback) {
  binding.db_close(this.context, callback)
}

LevelDOWN.prototype._serializeKey = function (key) {
  return Buffer.isBuffer(key) ? key : String(key)
}

LevelDOWN.prototype._serializeValue = function (value) {
  return Buffer.isBuffer(value) ? value : String(value)
}

LevelDOWN.prototype._put = function (key, value, options, callback) {
  binding.db_put(this.context, key, value, options, callback)
}

LevelDOWN.prototype._get = function (key, options, callback) {
  binding.db_get(this.context, key, options, callback)
}

LevelDOWN.prototype._del = function (key, options, callback) {
  binding.db_del(this.context, key, options, callback)
}

LevelDOWN.prototype._chainedBatch = function () {
  return new ChainedBatch(this)
}

LevelDOWN.prototype._batch = function (operations, options, callback) {
  binding.batch_do(this.context, operations, options, callback)
}

LevelDOWN.prototype.approximateSize = function (start, end, callback) {
  if (start == null ||
      end == null ||
      typeof start === 'function' ||
      typeof end === 'function') {
    throw new Error('approximateSize() requires valid `start` and `end` arguments')
  }

  if (typeof callback !== 'function') {
    throw new Error('approximateSize() requires a callback argument')
  }

  start = this._serializeKey(start)
  end = this._serializeKey(end)

  binding.db_approximate_size(this.context, start, end, callback)
}

LevelDOWN.prototype.compactRange = function (start, end, callback) {
  if (start == null ||
      end == null ||
      typeof start === 'function' ||
      typeof end === 'function') {
    throw new Error('compactRange() requires valid `start` and `end` arguments')
  }

  if (typeof callback !== 'function') {
    throw new Error('compactRange() requires a callback argument')
  }

  start = this._serializeKey(start)
  end = this._serializeKey(end)

  binding.db_compact_range(this.context, start, end, callback)
}

LevelDOWN.prototype.getProperty = function (property) {
  if (typeof property !== 'string') {
    throw new Error('getProperty() requires a valid `property` argument')
  }

  return binding.db_get_property(this.context, property)
}

LevelDOWN.prototype._iterator = function (options) {
  if (this.status !== 'open') {
    // Prevent segfault
    throw new Error('cannot call iterator() before open()')
  }

  return new Iterator(this, options)
}

LevelDOWN.destroy = function (location, callback) {
  if (arguments.length < 2) {
    throw new Error('destroy() requires `location` and `callback` arguments')
  }
  if (typeof location !== 'string') {
    throw new Error('destroy() requires a location string argument')
  }
  if (typeof callback !== 'function') {
    throw new Error('destroy() requires a callback function argument')
  }

  binding.destroy_db(location, function (err) {
    if (err) return callback(err)

    // On Windows, RocksDB silently fails to remove the directory because its
    // Logger, which is instantiated on destroy(), has an open file handle on a
    // LOG file. Destroy() removes this file but Windows won't actually delete
    // it until the handle is released. This happens when destroy() goes out of
    // scope, which disposes the Logger. So back in JS-land, we can again
    // attempt to remove the directory. This is merely a workaround because
    // arguably RocksDB should not instantiate a Logger or open a file at all.
    fs.rmdir(location, function (err) {
      if (err) {
        // Ignore this error in case there are non-RocksDB files left.
        if (err.code === 'ENOTEMPTY') return callback()
        if (err.code === 'ENOENT') return callback()

        return callback(err)
      }

      callback()
    })
  })
}

LevelDOWN.repair = function (location, callback) {
  if (arguments.length < 2) {
    throw new Error('repair() requires `location` and `callback` arguments')
  }
  if (typeof location !== 'string') {
    throw new Error('repair() requires a location string argument')
  }
  if (typeof callback !== 'function') {
    throw new Error('repair() requires a callback function argument')
  }

  binding.repair_db(location, callback)
}

module.exports = LevelDOWN.default = LevelDOWN
