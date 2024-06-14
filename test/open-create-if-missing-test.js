'use strict'

exports.setUp = function (test, testCommon) {
  test('setUp', testCommon.setUp)
}

exports.createIfMissing = function (test, testCommon) {
  test('test database open createIfMissing:false', function (t) {
    const db = testCommon.factory()
    let async = false

    db.open({ createIfMissing: false }, function (err) {
      t.ok(err, 'error')
      t.comment(err.message)
      t.ok(/CLOUDMANIFEST not found/.test(err.message), 'error is about CLOUDMANIFEST not existing')
      t.ok(async, 'callback is asynchronous')
      t.end()
    })

    async = true
  })
}

exports.tearDown = function (test, testCommon) {
  test('tearDown', testCommon.tearDown)
}

exports.all = function (test, testCommon) {
  exports.setUp(test, testCommon)
  exports.createIfMissing(test, testCommon)
  exports.tearDown(test, testCommon)
}
