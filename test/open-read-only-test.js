'use strict'

const test = require('tape')
const leveldown = require('../')
const testCommon = require('abstract-leveldown/testCommon')
const fs = require('fs')
var location = testCommon.location()

test('setUp', function (t) {
  // just in case we thew an error last time and don't have perms to remove db
  if (fs.existsSync(location)) {
    fs.chmodSync(location, 0o755)
  }
  testCommon.setUp(t)
})

test('test write to read/write database', function (t) {
  var db = leveldown(location)
  db.open(function (err) {
    t.error(err)
    db.put('my key', 'my value', function (err) {
      t.error(err, 'no write error')
      db.get('my key', function (err, value) {
        t.error(err, 'no read error')
        t.equal(value.toString(), 'my value', 'correct value')
        db.close(t.end.bind(t))
      })
    })
  })
})

test('test throw error reading read-only database', function (t) {
  fs.chmodSync(location, 0o555)
  var db = leveldown(location)
  db.open(function (err) {
    t.ok(err, 'should get error reading read only database')
    t.ok(/IO Error/i.test(err && err.message), 'should get io error')
    db.close(t.end.bind(t))
  })
})

test('test read from a read-only database if readOnly is true', function (t) {
  fs.chmodSync(location, 0o555)
  var db = leveldown(location)
  db.open({ readOnly: true }, function (err) {
    t.error(err)
    db.get('my key', function (err, value) {
      t.error(err, 'no read error')
      t.equal(value.toString(), 'my value', 'correct value')
      db.close(t.end.bind(t))
    })
  })
})

test('test throw error reading read-only database if readOnly is false', function (t) {
  fs.chmodSync(location, 0o555)
  var db = leveldown(location)
  db.open({ readOnly: false }, function (err) {
    t.ok(err, 'should get error reading read only database')
    t.ok(/IO Error/i.test(err && err.message), 'should get io error')
    db.close(t.end.bind(t))
  })
})

test('test throw error putting data to read-only db if readOnly is true', function (t) {
  fs.chmodSync(location, 0o555)
  var db = leveldown(location)
  db.open({ readOnly: true }, function (err) {
    t.error(err)
    db.put('my key', 'my value', function (err) {
      t.ok(err, 'should get write error')
      t.ok(/Not supported operation in read only mode/i.test(err && err.message), 'should get io error')
      db.close(t.end.bind(t))
    })
  })
})

test('test throw error deleting data from read-only db if readOnly is true', function (t) {
  fs.chmodSync(location, 0o555)
  var db = leveldown(location)
  db.open({ readOnly: true }, function (err) {
    t.error(err)
    db.del('my key', function (err) {
      t.ok(err, 'should get write error')
      t.ok(/Not supported operation in read only mode/i.test(err && err.message), 'should get io error')
      db.close(t.end.bind(t))
    })
  })
})

test('test throw error with batch put from read-only db if readOnly is true', function (t) {
  fs.chmodSync(location, 0o555)
  var db = leveldown(location)
  db.open({ readOnly: true }, function (err) {
    t.error(err)
    db.batch([{ key: 'key 1', type: 'put', value: 'value 1' }], function (err) {
      t.ok(err, 'should get write error')
      t.ok(/Not supported operation in read only mode/i.test(err && err.message), 'should get io error')
      db.close(t.end.bind(t))
    })
  })
})

test('test throw error with batch del from read-only db if readOnly is true', function (t) {
  fs.chmodSync(location, 0o555)
  var db = leveldown(location)
  db.open({ readOnly: true }, function (err) {
    t.error(err)
    db.batch([{ key: 'my key', type: 'del' }], function (err) {
      t.ok(err, 'should get write error')
      t.ok(/Not supported operation in read only mode/i.test(err && err.message), 'should get io error')
      db.close(t.end.bind(t))
    })
  })
})

test('tearDown', function (t) {
  // just in case we thew an error last time and don't have perms to remove db
  if (fs.existsSync(location)) {
    fs.chmodSync(location, 0o755)
  }
  testCommon.tearDown(t)
})
