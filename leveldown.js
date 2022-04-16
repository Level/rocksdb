'use strict'

const util = require('util')
const { AbstractLevelDOWN } = require('abstract-leveldown')
const binding = require('./binding')
const ChainedBatch = require('./chained-batch')
const Iterator = require('./iterator')

function LevelDOWN (location) {
  if (!(this instanceof LevelDOWN)) {
    return new LevelDOWN(location)
  }

  if (typeof location !== 'string') {
    throw new Error('constructor requires a location string argument')
  }

  AbstractLevelDOWN.call(this, {
    bufferKeys: true,
    snapshots: true,
    permanence: true,
    seek: true,
    clear: true,
    getMany: true,
    createIfMissing: true,
    errorIfExists: true
  })

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
  const batch = new ChainedBatch(this)
  batch.put(key, value)
  batch.write(options, callback)
}

LevelDOWN.prototype._get = function (key, options, callback) {
  binding.db_get_many(this.context, [key], options, (err, val) => {
    if (err) {
      callback(err)
    } else if (!val[0]) {
      callback(new Error('NotFound'))
    } else {
      callback(null, val[0])
    }
  })
}

LevelDOWN.prototype._getMany = function (keys, options, callback) {
  binding.db_get_many(this.context, keys, options, callback)
}

LevelDOWN.prototype._del = function (key, options, callback) {
  const batch = new ChainedBatch(this)
  batch.del(key)
  batch.write(options, callback)
}

LevelDOWN.prototype._chainedBatch = function () {
  return new ChainedBatch(this)
}

LevelDOWN.prototype._batch = function (operations, options, callback) {
  let batch = null
  for (const op of operations) {
    if (op.type === 'del') {
      if (!('key' in op)) continue
      batch ??= this.batch()
      batch.del(op.key)
    } else if (op.type === 'put') {
      if (!('key' in op)) continue
      if (!('value' in op)) continue
      batch ??= this.batch()
      batch.put(op.key, op.value)
    }
  }
  if (batch) {
    batch.write(options, callback)
  } else {
    process.nextTick(callback)
  }
}

LevelDOWN.prototype._iterator = function (options) {
  if (this.status !== 'open') {
    // Prevent segfault
    throw new Error('cannot call iterator() before open()')
  }

  return new Iterator(this, options)
}

module.exports = LevelDOWN
