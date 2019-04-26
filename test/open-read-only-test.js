'use strict'

const test = require('tape')
const leveldown = require('..')
const tempy = require('tempy')
const fs = require('fs')
const path = require('path')

const location = tempy.directory()

// This is used because it's not sufficient on windows to set a parent folder as readonly
function chmodRecursive (mode) {
  fs.readdirSync(location).forEach(function (file) {
    fs.chmodSync(path.join(location, file), mode)
  })
  fs.chmodSync(location, mode)
}

function factory (mode) {
  if (mode != null) chmodRecursive(mode)
  return leveldown(location)
}

test('test write to read/write database', function (t) {
  const db = factory()

  db.open(function (err) {
    t.ifError(err, 'no error from open()')

    db.put('my key', 'my value', function (err) {
      t.ifError(err, 'no error from put()')
      db.get('my key', function (err, value) {
        t.ifError(err, 'no error from get()')
        t.equal(value.toString(), 'my value', 'correct value')
        db.close(t.end.bind(t))
      })
    })
  })
})

test('test throw error reading read-only database', function (t) {
  const db = factory(0o555)

  db.open(function (err) {
    t.ok(err, 'should get error reading read only database')
    t.ok(/IO Error/i.test(err && err.message), 'should get io error')
    db.close(t.end.bind(t))
  })
})

test('test read from a read-only database if readOnly is true', function (t) {
  const db = factory(0o555)

  db.open({ readOnly: true }, function (err) {
    t.ifError(err, 'no error from open()')

    db.get('my key', function (err, value) {
      t.ifError(err, 'no error from get()')
      t.equal(value.toString(), 'my value', 'correct value')
      db.close(t.end.bind(t))
    })
  })
})

test('test throw error reading read-only database if readOnly is false', function (t) {
  const db = factory(0o555)

  db.open({ readOnly: false }, function (err) {
    t.ok(err, 'should get error reading read only database')
    t.ok(/IO Error/i.test(err && err.message), 'should get io error')
    db.close(t.end.bind(t))
  })
})

test('test throw error putting data to read-only db if readOnly is true', function (t) {
  const db = factory(0o555)

  db.open({ readOnly: true }, function (err) {
    t.ifError(err, 'no error from open()')

    db.put('my key', 'my value', function (err) {
      t.ok(err, 'should get write error')
      t.ok(/Not supported operation in read only mode/i.test(err && err.message), 'should get io error')
      db.close(t.end.bind(t))
    })
  })
})

test('test throw error deleting data from read-only db if readOnly is true', function (t) {
  const db = factory(0o555)

  db.open({ readOnly: true }, function (err) {
    t.ifError(err, 'no error from open()')

    db.del('my key', function (err) {
      t.ok(err, 'should get write error')
      t.ok(/Not supported operation in read only mode/i.test(err && err.message), 'should get io error')
      db.close(t.end.bind(t))
    })
  })
})
