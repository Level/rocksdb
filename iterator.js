'use strict'

const { AbstractIterator } = require('abstract-leveldown')
const binding = require('./binding')

const kContext = Symbol('context')
const kFinalized = Symbol('finalized')

class Iterator extends AbstractIterator {
  constructor (db, options) {
    super(db)

    this[kContext] = binding.iterator_init(db.context, options)
    this[kFinalized] = false

    this.cache = null
  }

  _seek (target) {
    if (target.length === 0) {
      throw new Error('cannot seek() to an empty target')
    }

    this.cache = null
    binding.iterator_seek(this[kContext], target)
    this[kFinalized] = false
  }

  _next (callback) {
    if (this.cache && this.cache.length) {
      process.nextTick(callback, null, this.cache.pop(), this.cache.pop())
    } else if (this[kFinalized]) {
      process.nextTick(callback)
    } else {
      binding.iterator_nextv(this[kContext], 1000, (err, array, finished) => {
        if (err) {
          callback(err)
        } else {
          this.cache = array
          this[kFinalized] = finished
          this._next(callback)
        }
      })
    }

    return this
  }

  _end (callback) {
    this.cache = null
    binding.iterator_close(this[kContext], callback)
  }
}

module.exports = Iterator
